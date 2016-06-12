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

#include "DlgSideChannelAttackVisualizationHE.h"

#include "DlgHybridDecryptionDemo.h"

#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "FileTools.h"
#include "CrypToolTools.h"

CDlgSideChannelAttackVisualizationHE::CDlgSideChannelAttackVisualizationHE(CWnd* pParent) :
	CDialog(CDlgSideChannelAttackVisualizationHE::IDD, pParent),
	significantBits(128),
	showInfoDialogs(false),
	scaClient(0),
	scaServer(0),
	scaAttacker(0),
	pButtonControl(0) {
	// initialization
	this->initMode = 0;
	this->initFile = "";
	this->isFileDeclared = false;
	this->certFilename = "";
	this->currentStep = 0;
	this->isHybridEncryptedFileDeclared = false;
}

CDlgSideChannelAttackVisualizationHE::~CDlgSideChannelAttackVisualizationHE() {
	delete scaClient;
	delete scaServer;
	delete scaAttacker;
	delete pButtonControl;
}

void CDlgSideChannelAttackVisualizationHE::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ATTACKCONTROL, m_AttackControl);
	DDX_Control(pDX, IDC_BUTTON_ALLREMAININGSTEPS, m_ControlButtonAllSteps);
	DDX_Control(pDX, IDC_BUTTON_NEXTSINGLESTEP, m_ControlButtonNextStep);
	DDX_Control(pDX, IDC_PROGRESS_ATTACK, m_ControlAttackProgress);
	DDX_Control(pDX, IDC_ABARROW, m_ControlABArrow);
	DDX_Control(pDX, IDC_LIGHTS, m_ControlLights);
	DDX_Check(pDX, IDC_CHECK_DISABLEHELP, showInfoDialogs);
}

BOOL CDlgSideChannelAttackVisualizationHE::OnInitDialog() {
	try {
		CDialog::OnInitDialog();
		// set init mode (one of three options)
		if (!isFileDeclared) {
			initMode = initMode | SCA_MODE_NO_FILE;
		}
		else if (isFileDeclared && !isDocumentHybridEncrypted(initFile)) {
			initMode = initMode | SCA_MODE_INVALID_FILE;
		}
		else {
			initMode = initMode | SCA_MODE_VALID_FILE;
		}
		// query registry
		CrypTool::Utilities::registryReadNumberDefault("SideChannelAttack", "ShowInfoDialogs", 1, showInfoDialogs);
		// create button control
		pButtonControl = new SideChannelAttackBitmapButtonControl(this);
		// initialize user interface colors
		m_greycolor= 0x00C0C0C0;
		m_greybrush.CreateSolidBrush(m_greycolor);
		m_blackcolor= RGB(0,0,0);
		m_blackbrush.CreateSolidBrush(m_blackcolor);
		// update user interface
		setLights(SCA_LIGHTS_NORMAL);
		setABArrow(SCA_ABARROW_NORMAL);
		m_ControlAttackProgress.SetRange((short)(0), (short)(significantBits + 2));
		m_ControlAttackProgress.SetStep(1);
		cancelAttackCycle();
		UpdateData(false);
		return TRUE;
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return true; }
}

void CDlgSideChannelAttackVisualizationHE::OnPaint() {
	CPaintDC dc(this);
	CBitmap bmp, *poldbmp;
	CDC memdc;
	bmp.LoadBitmap(IDB_SCA_MAINBACKGROUND);
	memdc.CreateCompatibleDC(&dc);
	poldbmp = memdc.SelectObject(&bmp);
	dc.BitBlt(0, 0, 981, 658, &memdc, 0, 0, SRCCOPY);
	memdc.SelectObject(poldbmp);
}

HBRUSH CDlgSideChannelAttackVisualizationHE::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr;
	switch (nCtlColor) 
	{ 
		case CTLCOLOR_MSGBOX: 
		case CTLCOLOR_EDIT: 
		case CTLCOLOR_BTN:
		case CTLCOLOR_STATIC:
		switch (pWnd->GetDlgCtrlID())  
		{     
			case IDC_CONTROLFRAME:
			case IDC_ALICEFRAME:
			case IDC_BOBFRAME:
			case IDC_TRUDYFRAME:
			case IDC_ATTACKCONTROL:
			case IDC_ATTACKPROGRESSLABEL:
			case IDC_PROGRESS_ATTACK:
			case IDC_BUTTON_NEXTSINGLESTEP:
			case IDC_BUTTON_ALLREMAININGSTEPS:
			case IDCLOSE:
			case IDC_CHECK_DISABLEHELP:
			case IDOK:
				pDC->SetBkColor(m_greycolor);
				pDC->SetTextColor(m_blackcolor);
				hbr = (HBRUSH)(m_greybrush);
				break;
			default:    
				hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
			break;
		}
		break;
	default:  
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
	}
	return hbr;
}

void CDlgSideChannelAttackVisualizationHE::updateGUI(int b) {
	try {
		pButtonControl->PerformAction(b);
		UpdateData(false);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::setEncryptedFile(const char *file) {
	try {
		initFile = file;
		// set file as declared only if it's not empty
		CrypTool::ByteString byteStringTemp;
		byteStringTemp.readFromFile(file);
		isFileDeclared = (byteStringTemp.getByteLength() > 0);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::setInitFileTitle(const char *title) {
	try {
		this->initFileTitle = title;
	}
	catch(SCA_Error &e) { CreateErrorMessage(e); return; };	
}

bool CDlgSideChannelAttackVisualizationHE::isDocumentHybridEncrypted(const char *infile) {
	return CDlgHybridDecryptionDemo::isDocumentHybridEncrypted(infile);
}

void CDlgSideChannelAttackVisualizationHE::OnIntroduction() {
	try {
		if (showInfoDialogs) {
			CDlgSideChannelAttackVisualizationHEIntroduction dlg;
			if (dlg.DoModal() != IDOK) {
				return;
			}
		}
		// query registry
		CString keyword;
		CrypTool::Utilities::registryReadStringDefault("SideChannelAttack", "Keyword", IDS_SCA_KEYWORD, keyword);
		// delete old actors if necessary
		if (scaClient) delete scaClient;
		if (scaServer) delete scaServer;
		if (scaAttacker) delete scaAttacker;
		// create new actors
		scaClient = new SCA_Client();
		scaServer = new SCA_Server(significantBits, keyword);
		scaAttacker = new SCA_Attacker(significantBits);
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		cancelAttackCycle();
		setABArrow(SCA_ABARROW_NORMAL);
		updateGUI(0);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnPreparations() {
	try {
		// initialize and display preparations dialog
		CDlgSideChannelAttackVisualizationHEPreparations dlg;
		dlg.setInitMode(initMode);
		dlg.setInitFile(initFile);
		dlg.setInitFileTitle(initFileTitle);
		if (dlg.DoModal() != IDOK) {
			return;
		}
		// try to parse the hybrid-encrypted document and extract the certificate 
		// serial number, the encrypted session key, and the cipher text; put all 
		// this information into the "hybridEncryptedFile" structure
		if (!CDlgHybridDecryptionDemo::parseHybridEncryptedDocument(dlg.getFinalHybEncFile(), hybridEncryptedFile.certificateSerial, hybridEncryptedFile.sessionKeyEncrypted, hybridEncryptedFile.cipherText)) {
			throw SCA_Error(E_SCA_HYBENCFILE_EXTRACTION);
		}
		// depending on whether the user executed the hybrid encryption himself 
		// or relied on a document encrypted by someone else, the session key 
		// needs to be specified as well; note: the session key is initialized 
		// either way, but in the latter case the session key is set to zero 
		// because the user has no knowledge of the key
		if (dlg.isExistingHybEncFileUsed()) hybridEncryptedFile.sessionKey.reset();
		else hybridEncryptedFile.sessionKey = dlg.getOriginalSessionKey();
		// try to acquire server exponent e and server modulus n
		CString stringPublicKeyE;
		CString stringPublicKeyN;
		if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPublicKeyE(hybridEncryptedFile.certificateSerial, 10, stringPublicKeyE)) {
			throw SCA_Error(E_SCA_INTERNAL_ERROR);
		}
		if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPublicKeyN(hybridEncryptedFile.certificateSerial, 10, stringPublicKeyN)) {
			throw SCA_Error(E_SCA_INTERNAL_ERROR);
		}
		CrypTool::ByteString e;
		CrypTool::ByteString n;
		e = stringPublicKeyE;
		n = stringPublicKeyN;
		// reset all involved parties
		scaClient->resetTransmittedHybridEncryptedFile();
		scaServer->resetReceivedHybridEncryptedFiles();
		scaAttacker->resetInterceptedHybridEncryptedFile();
		scaAttacker->resetAttack();
		// update all involved parties
		scaClient->setHybridEncryptedFile(hybridEncryptedFile);
		scaServer->setPublicKey(e, n);
		scaAttacker->setPublicKey(e, n);
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		cancelAttackCycle();
		setABArrow(SCA_ABARROW_NORMAL);
		updateGUI(1);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnMessagetransmission() {
	try {
		if (showInfoDialogs) {
			CDlgSideChannelAttackVisualizationHEMessageTransmission dlg;
			if (dlg.DoModal() != IDOK) {
				return;
			}
		}
		// reset all involved parties
		scaClient->resetTransmittedHybridEncryptedFile();
		scaServer->resetReceivedHybridEncryptedFiles();
		scaAttacker->resetInterceptedHybridEncryptedFile();
		scaAttacker->resetAttack();
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		cancelAttackCycle();
		setABArrow(SCA_ABARROW_TRANSMISSION);
		if (!SetTimer(SCA_TIMEREVENT_AB_TRANSMISSION, 50, 0)) {
			throw SCA_Error(E_SCA_TIMER_NOT_AVAILABLE);
		}
		updateGUI(2);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnMessagereception() {
	try {
		// temporary variables
		CString password;
		CString stringPrivateKeyD;
		// prompt user to enter the password for the private key of the certificate
		while(1) {
			CDlgSideChannelAttackVisualizationHEPSEPINPrompt dlg;
			if (dlg.DoModal() != IDOK) {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_PSE_IS_NEEDED, pc_str, STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str, "CrypTool", MB_OK);
				return;
			}
			// assign the password entered by the user
			password = dlg.getPin();
			// try to acquire the private key (in decimal format) using the provided password
			if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPrivateKeyD(hybridEncryptedFile.certificateSerial, password, 10, stringPrivateKeyD)) {
				LoadString(AfxGetInstanceHandle(), IDS_SCA_PSE_WRONG_PIN, pc_str, STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str, "CrypTool", MB_OK);
			}
			else {
				break;
			}
		}
		// reset all involved parties
		scaClient->resetTransmittedHybridEncryptedFile();
		scaServer->resetReceivedHybridEncryptedFiles();
		scaAttacker->resetInterceptedHybridEncryptedFile();
		scaAttacker->resetAttack();
		// update all involved parties
		CrypTool::ByteString d;
		d = stringPrivateKeyD;
		scaServer->setPrivateKey(d, password);
		// execute the actual message transmission between client and server
		scaClient->transmitHybridEncryptedFile();
		scaServer->receiveHybridEncryptedFile(scaClient->getTransmittedHybridEncryptedFile());
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		updateGUI(9);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnMessageinterception() {
	try {
		if (showInfoDialogs) {
			CDlgSideChannelAttackVisualizationHEMessageInterception dlg;
			if (dlg.DoModal() != IDOK) {
				return;
			}
		}
		// reset all involved parties
		scaServer->resetReceivedModifiedHybridEncryptedFiles();
		scaAttacker->resetInterceptedHybridEncryptedFile();
		scaAttacker->resetAttack();
		// update all involved parties
		scaAttacker->setInterceptedHybridEncryptedFile(scaClient->getTransmittedHybridEncryptedFile());
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		cancelAttackCycle();
		setABArrow(SCA_ABARROW_INTERCEPTION);
		updateGUI(3);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnAttackcycle() {
	try {
		// ATTENTION: the attack does not work for session keys which are null
		if (hybridEncryptedFile.sessionKeyEncrypted.isNull()) {
			CString message;
			message.Format(IDS_SCA_SESSIONKEYISNULL);
			MessageBox(message, "CrypTool", MB_OK);
			return;
		}
		// show info dialog
		if (showInfoDialogs) {
			CDlgSideChannelAttackVisualizationHEAttackCycle dlg;
			if (dlg.DoModal() != IDOK) {
				return;
			}
		}
		// this variable decides whether the attack is executed in single-step mode 
		// or if all steps are executed at once; the default is single-step mode, 
		// and the user is only asked if info dialogs are active
		int singleStepMode = IDYES;
		// now fire up a dialog to ask the user if desired
		if (showInfoDialogs) {
			CString message;
			message.Format(IDS_SCA_ASKFORATTACKMODE);
			singleStepMode = AfxMessageBox(message, MB_YESNO);
		}
		// reset all involved parties
		scaServer->resetReceivedModifiedHybridEncryptedFiles();
		scaAttacker->resetAttack();
		// update user interface
		m_ControlAttackProgress.SetPos(0);
		cancelAttackCycle();
		setABArrow(SCA_ABARROW_NORMAL);
		updateGUI(4);
		// if we're in single-step mode, we simply start the attack cycle and return
		if (singleStepMode == IDYES) {
			startAttackCycle();
			return;
		}
		// otherwise we execute all attack steps at once
		else {
			SHOW_HOUR_GLASS
			while (!scaAttacker->isDone()) {
				const HybridEncryptedFile nextHybridEncryptedFile = scaAttacker->createNextHybridEncryptedFile();
				if (scaAttacker->isDone()) {
					break;
				}
				const bool response = scaServer->receiveHybridEncryptedFile(nextHybridEncryptedFile);
				scaAttacker->processServerResponse(response);
				// update user interface
				m_ControlAttackProgress.StepIt();
			}
			HIDE_HOUR_GLASS
			// in case ALL answers by the server were negative, obviously the attack failed;
			// the reason probably is the fact that the keyword ("Alice" by default) was not
			// part of the file that was attacked
			if (scaServer->getNumberOfPositiveResponses() == 0) {
				// first of all, get the current keyword from the registry
				CString keyword;
				CrypTool::Utilities::registryReadStringDefault("SideChannelAttack", "Keyword", IDS_SCA_KEYWORD, keyword);
				// now let the user know why the attack probably failed
				CString message;
				message.Format(IDS_SCA_ATTACK_FAILED_BECAUSE_OF_MISSING_KEYWORD, keyword);
				MessageBox(message, "CrypTool");
			}
			// notify user that the attack was successful
			else {
				CDlgSideChannelAttackVisualizationHEFinished dlg;
				dlg.DoModal();
			}
		}
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnReport() {
	try {
		// to avoid inconsistencies during report generation, 
		// do not let the user generate the report until the 
		// attack is completed
		if (!scaAttacker->isDone()) {
			CString message;
			message.Format(IDS_SCA_REPORTNOTYETGENERATED);
			MessageBox(message, "CrypTool");
			return;
		}
		// show info dialog
		if (showInfoDialogs) {
			CDlgSideChannelAttackVisualizationHEReport dlg;
			if (dlg.DoModal() != IDOK) {
				return;
			}
		}
		// generate the report
		const CString fileName = CrypTool::Utilities::createTemporaryFile(".txt");
		generateReport(scaClient, scaServer, scaAttacker, fileName);
		CAppDocument *document = theApp.OpenDocumentFileNoMRU(fileName);
		// notify user about successful generation
		CString message;
		message.Format(IDS_SCA_REPORTGENERATED);
		MessageBox(message, "CrypTool");
		// update user interface
		updateGUI(5);
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnAlice() {
	try {
		CDlgSideChannelAttackVisualizationHEAlice dlg(this);
		dlg.DoModal();
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnBob() {
	try {
		CDlgSideChannelAttackVisualizationHEBob dlg(this);
		dlg.DoModal();
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnTrudy() {
	try {
		CDlgSideChannelAttackVisualizationHETrudy dlg(this);
		dlg.DoModal();
	}
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::CreateErrorMessage(SCA_Error &e) {
	int errorCode = e.getErrorCode();
	// handle exception codes
	if (errorCode == E_SCA_INTERNAL_ERROR) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_INTERNAL_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
		return;
	}
	if (errorCode == E_SCA_MEMORY_ALLOCATION) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_MEMORY_ALLOCATION, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
		return;
	}
	if (errorCode == E_SCA_HYBENCFILE_EXTRACTION) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_HYBENCFILE_EXTRACTION, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
		return;
	}
	if (errorCode == E_SCA_ATTACK_CONDITIONS_NOT_MET) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_ATTACK_CONDITIONS_NOT_MET, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}
	if (errorCode == E_SCA_MIRACL_ERROR) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_MIRACL_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
		return;
	}
	if (errorCode == E_SCA_WRONG_PSE_PIN) {
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_WRONG_PIN, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}	
	if (errorCode == E_SCA_TIMER_NOT_AVAILABLE)
	{
		LoadString(AfxGetInstanceHandle(), IDS_SCA_E_TIMER_NOT_AVAILABLE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}
	// handle unknown exception codes
	LoadString(AfxGetInstanceHandle(), IDS_SCA_E_UNKNOWN_ERROR, pc_str, STR_LAENGE_STRING_TABLE);
	MessageBox(pc_str, "CrypTool", MB_ICONWARNING);
	return;
}

void CDlgSideChannelAttackVisualizationHE::setLights(int _mode) {
	if (_mode == SCA_LIGHTS_NORMAL) {
		m_ControlLights.UnLoad();
		m_ControlLights.Load(MAKEINTRESOURCE(IDR_SCA_LIGHTS_NORMAL), _T("GIF"));
		m_ControlLights.Stop();
		m_ControlLights.Draw();
	}
	if (_mode == SCA_LIGHTS_GREEN) {
		m_ControlLights.UnLoad();
		m_ControlLights.Load(MAKEINTRESOURCE(IDR_SCA_LIGHTS_GREEN), _T("GIF"));
		m_ControlLights.Stop();
		m_ControlLights.Draw();
	}
	if (_mode == SCA_LIGHTS_RED) {
		m_ControlLights.UnLoad();
		m_ControlLights.Load(MAKEINTRESOURCE(IDR_SCA_LIGHTS_RED), _T("GIF"));
		m_ControlLights.Stop();
		m_ControlLights.Draw();
	}
}

void CDlgSideChannelAttackVisualizationHE::setABArrow(int _mode) {
	if (_mode == SCA_ABARROW_NORMAL) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWSTATIC), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
	if (_mode == SCA_ABARROW_TRANSMISSION) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWTRANSMISSION), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
	if (_mode == SCA_ABARROW_INTERCEPTION) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWINTERCEPTION), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
	if (_mode == SCA_ABARROW_FAILURE) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWFAILURE), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
	if (_mode == SCA_ABARROW_SUCCESS) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWSUCCESS), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
	if (_mode == SCA_ABARROW_TRANSMISSION_TRUDYBOB) {
		m_ControlABArrow.UnLoad();
		m_ControlABArrow.Load(MAKEINTRESOURCE(IDR_SCA_ABARROWTRANSMISSION_TRUDYBOB), _T("GIF"));
		m_ControlABArrow.Stop();
		m_ControlABArrow.Draw();
	}
}

void CDlgSideChannelAttackVisualizationHE::OnClose() {
	EndDialog(IDCLOSE);	
}

void CDlgSideChannelAttackVisualizationHE::OnTimer(UINT nIDEvent) {
	// TRANSMISSION from ALICE to BOB
	if (nIDEvent == SCA_TIMEREVENT_AB_TRANSMISSION) {
		if (!m_ControlABArrow.IsPlaying()) {
			// Falls Berechnung auf Serverseite noch nicht beendet,
			// noch KEINE Ampel anzeigen
			if (scaServer->getReceivedHybridEncryptedFiles().size() <= 0)
				return;
			// ansonsten Timer löschen und Ampel anzeigen (s.u.)
			else
				KillTimer(SCA_TIMEREVENT_AB_TRANSMISSION);
			// falls der Server die ERSTE Nachricht entschlüsseln konnte,
			// die Ampel GRÜN leuchten lassen; andernfalls ROT
			if (scaServer->getResponses().at(0))
				setLights(SCA_LIGHTS_GREEN);
			else
				setLights(SCA_LIGHTS_RED);
		}
	}
	// TRANSMISSION from TRUDY to BOB
	if (nIDEvent == SCA_TIMEREVENT_TB_TRANSMISSION) {
		if (!m_ControlABArrow.IsPlaying()) {
			KillTimer(SCA_TIMEREVENT_TB_TRANSMISSION);
			if (scaServer->getResponses().at(scaServer->getResponses().size() - 1)) {
				// Positive Antwort signalisieren
				setLights(SCA_LIGHTS_GREEN);
				// Antwort GRÜN
				setABArrow(SCA_ABARROW_SUCCESS);
			}
			else {
				// negative Antwort signalisieren
				setLights(SCA_LIGHTS_RED);
				// Antwort ROT
				setABArrow(SCA_ABARROW_FAILURE);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgSideChannelAttackVisualizationHE::startAttackCycle() {
	m_ControlButtonNextStep.EnableWindow(true);
	m_ControlButtonNextStep.ShowWindow(SW_SHOW);
	m_ControlButtonAllSteps.EnableWindow(true);
	m_ControlButtonAllSteps.ShowWindow(SW_SHOW);
	m_AttackControl.EnableWindow(true);
	m_AttackControl.ShowWindow(SW_SHOW);
	m_ControlButtonNextStep.SetFocus();
}

void CDlgSideChannelAttackVisualizationHE::cancelAttackCycle() {
	m_ControlButtonNextStep.EnableWindow(false);
	m_ControlButtonNextStep.ShowWindow(SW_HIDE);
	m_ControlButtonAllSteps.EnableWindow(false);
	m_ControlButtonAllSteps.ShowWindow(SW_HIDE);
	m_AttackControl.EnableWindow(false);
	m_AttackControl.ShowWindow(SW_HIDE);
}

void CDlgSideChannelAttackVisualizationHE::generateReport(SCA_Client *_scaClient, SCA_Server *_scaServer, SCA_Attacker *_scaAttacker, const CString &_fileName) {
	CString result;
	CString temp;

	// *** PREPARATIONS ***
	temp.Format(IDS_SCA_REPORT_HEADINGPREPARATIONS);
	result += temp;
	// differentiate whether Alice has hybrid-encrypted the original file herself or not
	if (!_scaClient->getSessionKey().isNull()) {
		temp.Format(IDS_SCA_REPORT_ALICECREATEDMESSAGE);
		result += temp;
		temp.Format(IDS_SCA_REPORT_ALICECHOSESESSIONKEY);
		result += temp;
		result += _scaClient->getSessionKey().toString();
		temp.Format(IDS_SCA_REPORT_ALICEENCRYPTEDMESSAGE);
		result += temp;
		temp.Format(IDS_SCA_REPORT_ALICECHOSEPUBLICKEY);
		result += temp;
		result += _scaServer->getPublicKeyE().toString();
		temp.Format(IDS_SCA_REPORT_ALICEENCRYPTEDSESSIONKEY);
		result += temp;
		result += _scaClient->getTransmittedHybridEncryptedFile().sessionKeyEncrypted.toString();
		result += "\n";
	}
	// at this point Alice has not hybrid-encrypted the file herself
	else {
		temp.Format(IDS_SCA_REPORT_ALICETOOKEXISTINGFILE);
		result += temp;
	}
	// *** MESSAGE TRANSMISSION ***
	temp.Format(IDS_SCA_REPORT_HEADINGMESSAGETRANSMISSION);
	result += temp;
	temp.Format(IDS_SCA_REPORT_ALICETRANSMITTEDMESSAGE);
	result += temp;
	// *** MESSAGE INTERCEPTION ***
	temp.Format(IDS_SCA_REPORT_HEADINGMESSAGEINTERCEPTION);
	result += temp;
	temp.Format(IDS_SCA_REPORT_TRUDYINTERCEPTEDMESSAGE);
	result += temp;
	result += _scaAttacker->getInterceptedHybridEncryptedFile().sessionKeyEncrypted.toString();
	// *** ATTACK CYCLE ***
	temp.Format(IDS_SCA_REPORT_HEADINGATTACKCYCLE);
	result += temp;
	temp.Format(IDS_SCA_REPORT_TRUDYMODIFIEDSESSIONKEYS);
	result += temp;
	temp.Format(IDS_SCA_REPORT_TRUDYREPEATSMODIFICATION, _scaAttacker->getModifiedHybridEncryptedFiles().size());
	result += temp;

	// write result into specified file
	CrypTool::ByteString byteStringFile;
	byteStringFile = result;
	byteStringFile.writeToFile(_fileName);
}

void CDlgSideChannelAttackVisualizationHE::OnButtonNextsinglestep() {
	try {
		if (!scaAttacker->isDone())
		{
			SHOW_HOUR_GLASS
			const HybridEncryptedFile nextHybridEncryptedFile = scaAttacker->createNextHybridEncryptedFile();
			if (scaAttacker->isDone()) {
				// Steuerelemente für Angriff "ausblenden"
				cancelAttackCycle();
				// in case ALL answers by the server were negative, obviously the attack failed;
				// the reason probably is the fact that the keyword ("Alice" by default) was not
				// part of the file that was attacked
				if (scaServer->getNumberOfPositiveResponses() == 0) {
					// first of all, get the current keyword from the registry
					CString keyword;
					CrypTool::Utilities::registryReadStringDefault("SideChannelAttack", "Keyword", IDS_SCA_KEYWORD, keyword);
					// now let the user know why the attack probably failed
					CString message;
					message.Format(IDS_SCA_ATTACK_FAILED_BECAUSE_OF_MISSING_KEYWORD, keyword);
					MessageBox(message, "CrypTool");
				}
				// notify user that the attack was successful
				else {
					CDlgSideChannelAttackVisualizationHEFinished dlg;
					dlg.DoModal();
				}
				// Anzeige aktualisieren
				updateGUI(4);
				return;
			}
			bool response = scaServer->receiveHybridEncryptedFile(nextHybridEncryptedFile);
			scaAttacker->processServerResponse(response);
			// Fortschrittsanzeige "updaten"
			m_ControlAttackProgress.StepIt();
			HIDE_HOUR_GLASS
			// Animation abspielen: Übertragung Trudy->Bob
			setABArrow(SCA_ABARROW_TRANSMISSION_TRUDYBOB);
			// Timer für Animationsabläufe setzen (siehe Funktion OnTimer)
			if (!SetTimer(SCA_TIMEREVENT_TB_TRANSMISSION, 50, 0)) {
				throw SCA_Error(E_SCA_TIMER_NOT_AVAILABLE);
			}
		}
	}
	// handle exceptions
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnButtonAllremainingsteps() {
	try {
		SHOW_HOUR_GLASS
		while(!scaAttacker->isDone()) {
			const HybridEncryptedFile nextHybridEncryptedFile = scaAttacker->createNextHybridEncryptedFile();
			if (scaAttacker->isDone()) break;
			bool response = scaServer->receiveHybridEncryptedFile(nextHybridEncryptedFile);
			scaAttacker->processServerResponse(response);
			// Fortschrittsanzeige "updaten"
			m_ControlAttackProgress.StepIt();
		}
		HIDE_HOUR_GLASS
		// Steuerelemente für Angriff "ausblenden"
		cancelAttackCycle();
		// in case ALL answers by the server were negative, obviously the attack failed;
		// the reason probably is the fact that the keyword ("Alice" by default) was not
		// part of the file that was attacked
		if (scaServer->getNumberOfPositiveResponses() == 0) {
			// first of all, get the current keyword from the registry
			CString keyword;
			CrypTool::Utilities::registryReadStringDefault("SideChannelAttack", "Keyword", IDS_SCA_KEYWORD, keyword);
			// now let the user know why the attack probably failed
			CString message;
			message.Format(IDS_SCA_ATTACK_FAILED_BECAUSE_OF_MISSING_KEYWORD, keyword);
			MessageBox(message, "CrypTool");
		}
		// notify user that the attack was successful
		else {
			CDlgSideChannelAttackVisualizationHEFinished dlg;
			dlg.DoModal();
		}
		// Anzeige aktualisieren
		updateGUI(4);
		return;
	}
	// handle exceptions
	catch(SCA_Error& e) { CreateErrorMessage(e); return; }
}

void CDlgSideChannelAttackVisualizationHE::OnCheckDisablehelp() {
	UpdateData(true);
	CrypTool::Utilities::registryWriteNumber("SideChannelAttack", "ShowInfoDialogs", (long)(showInfoDialogs));
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHE, CDialog)
	ON_BN_CLICKED(IDC_INTRODUCTION, OnIntroduction)
	ON_BN_CLICKED(IDC_PREPARATIONS, OnPreparations)
	ON_BN_CLICKED(IDC_MESSAGETRANSMISSION, OnMessagetransmission)
	ON_BN_CLICKED(IDC_MESSAGEINTERCEPTION, OnMessageinterception)
	ON_BN_CLICKED(IDC_ATTACKCYCLE, OnAttackcycle)
	ON_BN_CLICKED(IDC_REPORT, OnReport)
	ON_BN_CLICKED(IDC_ALICE, OnAlice)
	ON_BN_CLICKED(IDC_BOB, OnBob)
	ON_BN_CLICKED(IDC_TRUDY, OnTrudy)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_NEXTSINGLESTEP, OnButtonNextsinglestep)
	ON_BN_CLICKED(IDC_BUTTON_ALLREMAININGSTEPS, OnButtonAllremainingsteps)
	ON_BN_CLICKED(IDC_MESSAGERECEPTION, OnMessagereception)
	ON_BN_CLICKED(IDC_CHECK_DISABLEHELP, OnCheckDisablehelp)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
