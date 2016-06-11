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
#include "DlgSideChannelAttackVisualizationHEBob.h"

#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSideChannelAttackVisualizationHEBob::CDlgSideChannelAttackVisualizationHEBob(CWnd* pParent)
	: CDialog(CDlgSideChannelAttackVisualizationHEBob::IDD, pParent) {
	
}

CDlgSideChannelAttackVisualizationHEBob::~CDlgSideChannelAttackVisualizationHEBob() {

}

BOOL CDlgSideChannelAttackVisualizationHEBob::OnInitDialog() {
	CDialog::OnInitDialog();
	// load the keyword from the registry
	CrypTool::Utilities::registryReadStringDefault("SideChannelAttack", "Keyword", IDS_SCA_KEYWORD, keyword);
	updateDisplay();
	return TRUE;
}

void CDlgSideChannelAttackVisualizationHEBob::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Control(pDX, IDC_LIST_RECEIVEDSESSIONKEYS, m_ListReceivedSessionKeys);
	DDX_Text(pDX, IDC_EDIT_KEYWORD, keyword);
}

void CDlgSideChannelAttackVisualizationHEBob::OnOK() {
	UpdateData(true);
	// store the current keyword in the registry
	CrypTool::Utilities::registryWriteString("SideChannelAttack", "Keyword", keyword);
	UpdateData(false);
	CDialog::OnOK();
}

void CDlgSideChannelAttackVisualizationHEBob::updateDisplay() {
	// inits
	char temp[STR_LAENGE_STRING_TABLE+20];
	m_ControlTasks.ResetContent();
		
	// AKTUELLEN Zeiger auf entsprechendes SCA-Objekt holen
	ASSERT(GetParent());
	SCA_Server *bob = (SCA_Server*)((CDlgSideChannelAttackVisualizationHE*)(GetParent()))->getSCAServer();
	
	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	if(bob->getResponses().size() > 0) {
		// ** Wie viele Nachrichten hat Bob bisher empfangen? **
		// Unterscheidung zwischen Singular und Plural
		// (vgl. DlgSideChannelAttackVisualizationHEAlice::updateDisplay)
		if(bob->getResponses().size() == 1) {
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);
		}
		else if(bob->getResponses().size() > 1) {
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDMESSAGES, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(temp, pc_str, bob->getResponses().size());
			m_ControlTasks.AddString(temp);
		}
			
		// ** Wie viele positive Antworten hat Bob gegeben ? **
		// ** (oder: wie viele Nachrichten konnte Bob erfolgreich entschlüsseln ? **
		// Unterscheidung zwischen Singular und Plural (s.o.)
		if(bob->getResponses().size() == 1 && bob->getNumberOfPositiveResponses() == 1) {
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_SUCCESSRESPONSE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);
		}
		else if(bob->getResponses().size() == 1 && bob->getNumberOfPositiveResponses() == 0) {
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_FAILURERESPONSE, pc_str, STR_LAENGE_STRING_TABLE);
			m_ControlTasks.AddString(pc_str);

		}
		else if(bob->getNumberOfPositiveResponses() > 1) {
			LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_SUCCESSRESPONSES, pc_str, STR_LAENGE_STRING_TABLE);
			sprintf(temp, pc_str, bob->getNumberOfPositiveResponses(), bob->getResponses().size());
			m_ControlTasks.AddString(temp);
		}
	}
	else {
		// Bob hat bisher keinerlei Nachrichten empfangen
		LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDNOMESSAGES, temp, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(temp);
	}

	// *** SESSION KEY TABELLE FÜLLEN ***
	// m_listview in Report-Mode initialisieren!!!
	m_ListReceivedSessionKeys.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	// laufende Nummer des Eintrags
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SESSIONKEYNUMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(0, pc_str, LVCFMT_LEFT, 30, 0);
	// Antwort des Servers: JA | NEIN
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_ANSWER, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(1, pc_str, LVCFMT_LEFT, 95, 1);
	// Vom Server empfangener Session Key (128 Bit, Hexadezimal)
	LoadString(AfxGetInstanceHandle(), IDS_SCA_SERVER_RECEIVEDSESSIONKEYHEX, pc_str, STR_LAENGE_STRING_TABLE);
	m_ListReceivedSessionKeys.InsertColumn(2, pc_str, LVCFMT_LEFT, 240, 2);

	// alle vorher vorhandenen Informationen löschen
	m_ListReceivedSessionKeys.DeleteAllItems();

	// Tabelle mit Informationen füllen...
	CString number;
	CrypTool::ByteString sessionKey;
	bool response;
	CString boolString;

	for(size_t i=0; i<bob->getResponses().size(); i++) {
		// note: sequence number is not zero-based
		number.Format("%d", i + 1);
		// acquire session key and response
		sessionKey = bob->getReceivedHybridEncryptedFiles().at(i).sessionKey.toString(16);
		response = bob->getResponses().at(i);
		if (response) boolString.Format(IDS_SCA_SERVER_ANSWER_SUCCESS);
		else boolString.Format(IDS_SCA_SERVER_ANSWER_FAILURE);
		// Zeile füllen
		m_ListReceivedSessionKeys.InsertItem(i, number);
		m_ListReceivedSessionKeys.SetItemText(i,1, boolString);
		m_ListReceivedSessionKeys.SetItemText(i, 2, sessionKey.toString());
	}

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEBob, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()
