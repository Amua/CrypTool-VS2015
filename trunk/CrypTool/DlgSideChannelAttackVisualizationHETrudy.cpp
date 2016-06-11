/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolBase.h"

#include "DlgSideChannelAttackVisualizationHETrudy.h"

#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSideChannelAttackVisualizationHETrudy::CDlgSideChannelAttackVisualizationHETrudy(CWnd* pParent) : 
	CDialog(CDlgSideChannelAttackVisualizationHETrudy::IDD, pParent) {
	m_DeterminedSessionKey = _T("");
	m_InterceptedEncryptedSessionKey = _T("");
	m_ComputedMessage = _T("");
}

CDlgSideChannelAttackVisualizationHETrudy::~CDlgSideChannelAttackVisualizationHETrudy() {

}

BOOL CDlgSideChannelAttackVisualizationHETrudy::OnInitDialog() {
	CDialog::OnInitDialog();
	updateDisplay();
	return TRUE;
}

void CDlgSideChannelAttackVisualizationHETrudy::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Control(pDX, IDC_LIST_MODIFIEDSESSIONKEYS, m_ListModifiedSessionKeys);
	DDX_Text(pDX, IDC_EDIT_DETERMINEDSESSIONKEY, m_DeterminedSessionKey);
	DDX_Text(pDX, IDC_EDIT_INTERCEPTEDENCRYPTEDSESSIONKEY, m_InterceptedEncryptedSessionKey);
	DDX_Text(pDX, IDC_EDIT_COMPUTEDMESSAGE, m_ComputedMessage);
}

void CDlgSideChannelAttackVisualizationHETrudy::updateDisplay() {
	// inits
	char temp[STR_LAENGE_STRING_TABLE+20];
	m_ControlTasks.ResetContent();
		
	// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
	ASSERT(GetParent());
	const SCA_Attacker *trudy = ((CDlgSideChannelAttackVisualizationHE*)(GetParent()))->getSCAAttacker();

	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	if(!trudy->getInterceptedHybridEncryptedFile().isReset()) {
		// hat Trudy schon die Nachricht von A->B abgefangen?
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MESSAGEINTERCEPTED,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
		// Trudy hat den Session Key aus der Nachricht "extrahiert"
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_HASEXTRACTEDDENCSESSIONKEY,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);

		if(trudy->getModifiedHybridEncryptedFiles().size() > 0) {
			// ** Wie viele modifizierte Sessionkeys hat Trudy bisher erstellt? **
			// Unterscheidung zwischen Singular und Plural
			// IDS_SCA_ATTACKER_MODIFICATIONSMADE_S:
			//		"Trudy hat 1 modifizierten Sessionkey erstellt"
			//	IDS_SCA_ATTACKER_MODIFICATIONSMADE
			//		"Trudy hat n modfizierte Sessionkeys erstellt.
			if(trudy->getModifiedHybridEncryptedFiles().size() == 1) {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFICATIONSMADE_S, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFICATIONSMADE, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, trudy->getModifiedHybridEncryptedFiles().size());
				m_ControlTasks.AddString(temp);
			}
	
			// ** Wie viele SUCCESS-Antworten hat Trudy von Bobs Server erhalten? ** 
			// Unterscheidung zwischen Singular und Plural (s.o.)
			if(	trudy->getModifiedHybridEncryptedFiles().size() == 1 && trudy->getServerResponses().size() == 1) {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSE_TRUE, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else if(trudy->getModifiedHybridEncryptedFiles().size() == 1 && trudy->getServerResponses().size() == 0) {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSE_FALSE, pc_str, STR_LAENGE_STRING_TABLE);
				m_ControlTasks.AddString(pc_str);
			}
			else {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SUCCESSRESPONSES, pc_str, STR_LAENGE_STRING_TABLE);
				sprintf(temp, pc_str, trudy->getServerResponses().size(), trudy->getModifiedHybridEncryptedFiles().size());
				m_ControlTasks.AddString(temp);
			}
		}
		else {
			// Trudy hat noch KEINE modifizierten Session Keys erstellt
			LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_NOMODIFICATIONSYET, temp ,STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(temp);
		}
	}
	else {
		// Trudy hat bisher KEINE Nachricht abgefangen
		LoadString(AfxGetInstanceHandle(),IDS_SCA_ATTACKER_MESSAGENOTINTERCEPTEDYET,temp,STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
	}
	// *** MODIFIZIERTE SESSION KEYS TABELLE FÜLLEN ***
	// m_listview in Report-Mode initialisieren!!!
	m_ListModifiedSessionKeys.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// *** Beschriftung der Tabelle ***
	// vom Angreifer modifizierter Session Key
	LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_MODIFIEDSESSIONKEY, temp, STR_LAENGE_STRING_TABLE);
	m_ListModifiedSessionKeys.InsertColumn(0, temp, LVCFMT_LEFT, 520, 0);
	// alle vorher vorhandenen Informationen löschen
	m_ListModifiedSessionKeys.DeleteAllItems();
	// Tabelle mit Informationen füllen...
	for (size_t index = 0; index < trudy->getModifiedHybridEncryptedFiles().size(); index++) {
		m_ListModifiedSessionKeys.InsertItem(index, trudy->getModifiedHybridEncryptedFiles().at(index).sessionKeyEncrypted.toString(16));
	}
	// *** VERSCHLÜSSELTER SESSION KEY (ORIGINAL) ***
	if(!trudy->getInterceptedHybridEncryptedFile().isReset()) {
		m_InterceptedEncryptedSessionKey = trudy->getInterceptedHybridEncryptedFile().sessionKeyEncrypted.toString(16);
	}
	else {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SESSIONKEYNOTINTERCEPTEDYET, temp, STR_LAENGE_STRING_TABLE);
		this->m_InterceptedEncryptedSessionKey = temp;
	}
	// *** DURCH ANGRIFF ERMITTELTER SESSION KEY ***
	if(trudy->isDone()) {
		// this variable will hold the plain text
		CrypTool::ByteString plainText;
		// acquire calculated session key
		CrypTool::ByteString calculatedSessionKey;
		calculatedSessionKey = trudy->getCalculatedSessionKey();
		// decrypt the cipher text
		SHOW_HOUR_GLASS
		CrypTool::Cryptography::Symmetric::SymmetricOperation operationSymmetric(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES, CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_DECRYPTION);
		operationSymmetric.executeOnByteStrings(trudy->getInterceptedHybridEncryptedFile().cipherText, calculatedSessionKey, plainText);
		HIDE_HOUR_GLASS
		// make dertmined session key and plain text visible
		m_DeterminedSessionKey = calculatedSessionKey.toString(16);
		m_ComputedMessage = plainText.toString();
	}
	else {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_ATTACKER_SESSIONKEYNOTDETERMINEDYET, temp, STR_LAENGE_STRING_TABLE);
		this->m_DeterminedSessionKey = temp;
	}
	UpdateData(false);
}

void CDlgSideChannelAttackVisualizationHETrudy::OnOK() {
	CDialog::OnOK();
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHETrudy, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()