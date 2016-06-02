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

#include "DlgSideChannelAttackVisualizationHEAlice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSideChannelAttackVisualizationHEAlice::CDlgSideChannelAttackVisualizationHEAlice(CWnd* pParent) : 
	CDialog(CDlgSideChannelAttackVisualizationHEAlice::IDD, pParent) {
	
}

CDlgSideChannelAttackVisualizationHEAlice::~CDlgSideChannelAttackVisualizationHEAlice() {

}

BOOL CDlgSideChannelAttackVisualizationHEAlice::OnInitDialog() {
	CDialog::OnInitDialog();
	updateDisplay();
	return TRUE;
}

void CDlgSideChannelAttackVisualizationHEAlice::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASKS, m_ControlTasks);
	DDX_Text(pDX, IDC_EDIT_ORIGINALSESSIONKEY, m_OriginalSessionKey);
}

void CDlgSideChannelAttackVisualizationHEAlice::OnOK() {
	CDialog::OnOK();
}

void CDlgSideChannelAttackVisualizationHEAlice::updateDisplay() {
	// inits
	m_ControlTasks.ResetContent();
	m_OriginalSessionKey = "";
		
	// *** AKTUELLEN ZEIGER AUF SCA-OBJEKT HOLEN ***
	ASSERT(GetParent());
	SCA_Client *alice = ((CDlgSideChannelAttackVisualizationHE*)(GetParent()))->getSCAClient();

	// Status holen
	SCA_ClientStatusInfo status = alice->getStatusInfo();

	// *** TASK-TABELLE MIT INFOS FÜLLEN ***
	// wenn noch gar keine hybridverschlüsselte Datei gewählt wurde,
	// entsprechende Nachricht erzeugen, Anzeige aktualisieren und return
	if(!status.isHybEncFileDefined)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_NOHYBENCFILEDEFINED, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
		UpdateData(false);
		return;
	}
	// wurde die hybridverschlüsselte DATEI VON ALICE ERSTELLT...
	if(status.hasCreatedMessage)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CREATEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CHOSESESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_ENCRYPTEDMESSAGE, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_GOTPUBLICKEY, pc_str, STR_LAENGE_STRING_TABLE);	
		m_ControlTasks.AddString(pc_str);
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_ENCRYPTSESSIONKEY, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}
	// oder wurde eine BEREITS EXISTENTE DATEI GEWÄHLT?
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_CHOSEEXISTINGHYBENCFILE, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}
	// wurde die hybridverschlüsselte Datei schon übertragen?
	if(status.hasTransmittedMessage)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_TRANSMITTEDHYBENCFILE, pc_str, STR_LAENGE_STRING_TABLE);
		m_ControlTasks.AddString(pc_str);
	}


	// *** ÜBRIGE FELDER FÜLLEN ***
	if(status.hasCreatedMessage)
	{
		m_OriginalSessionKey = alice->getSessionKey().c_str();
	}
	else
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_SESSIONKEYUNKNOWN, pc_str, STR_LAENGE_STRING_TABLE);
		m_OriginalSessionKey = pc_str;
	}

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEAlice, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()