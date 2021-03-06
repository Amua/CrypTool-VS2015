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
#include "DlgHybridDecryptionDemo.h"

#include "DlgCertificateStoreAskForPassword.h"
#include "DlgCertificateStoreShowCertificateParametersAll.h"

#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgHybridDecryptionDemo::CDlgHybridDecryptionDemo(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent) : 
	CDialog(CDlgHybridDecryptionDemo::IDD, pParent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle),
	m_byteLengthSessionKey(16),
	m_selectedCertificateSerial(0),
	m_selectedCertificatePassword(""),
	step(0) {

}

CDlgHybridDecryptionDemo::~CDlgHybridDecryptionDemo() {

}

BOOL CDlgHybridDecryptionDemo::OnInitDialog() {
	CDialog::OnInitDialog();
	// the first thing we want to do is parse the document specified at construction 
	// for hybrid-encrypted data; if the following function returns false (which is 
	// indicating the data could not be extracted), we dump and error and close the 
	// dialog on the spot
	CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
	CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
	if(!CrypTool::Utilities::parseHybridEncryptedFile(m_documentFileName, m_selectedCertificateSerial, asymmetricAlgorithmType, symmetricAlgorithmType, m_byteStringSymmetricKeyEncrypted, m_byteStringCipherText)) {
		Message(IDS_STRING_HYBRID_DEC_MSG9, MB_ICONSTOP);
		EndDialog(IDOK);
	}
	// initialize user interface
	m_FlushDecDataCtrl.EnableWindow(FALSE);
	m_ShowCertificate.EnableWindow(FALSE);
	LOGFONT LogFont;
	char DefaultFontName[32];
	LONG defaultFontWeight;
	CFont *defaultFont = m_ContinueButtonCtrl.GetFont();
	defaultFont->GetLogFont(&LogFont); // Default Systemschrift ermitteln
	strncpy(DefaultFontName, LogFont.lfFaceName, 32); // Default Wert sichern
	defaultFontWeight = LogFont.lfWeight; // Default Wert sichern
	LogFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	m_Font.CreateFontIndirect(&LogFont); // Font initialisieren
	m_TextSignStepsCtrl.SetFont(&m_Font);
	m_StepCtrl.SetFont(&m_Font);
	LogFont.lfWeight = defaultFontWeight; // Auf default Wert zurückstellen
	strncpy(LogFont.lfFaceName, "Courier", 32); // Auf Courier umstellen	
	m_Font2.CreateFontIndirect(&LogFont); // Font2 initialisieren
	m_DisplayDataCtrl.SetFont(&m_Font2);
	m_TextSignSteps.LoadString(IDS_STRING_HYBRID_DEC_STEP);
	UpdateDataDisplay();
	UpdateData(FALSE);
	return TRUE;
}

void CDlgHybridDecryptionDemo::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW_STEPS, m_DisplayDataCtrl);
	DDX_Control(pDX, IDC_EDIT4, m_StepCtrl);
	DDX_Control(pDX, IDC_EDIT3, m_TextSignStepsCtrl);
	DDX_Control(pDX, IDOK, m_FlushDecDataCtrl);
	DDX_Control(pDX, IDC_BUTTON_CONTINUE, m_ContinueButtonCtrl);
	DDX_Control(pDX, IDC_SHOW_CERTIFICATE, m_ShowCertificate);
	DDX_Text(pDX, IDC_EDIT3, m_TextSignSteps);
	DDX_Text(pDX, IDC_EDIT4, m_Step);
	DDX_Text(pDX, IDC_EDIT_SHOW_STEPS, m_DisplayData);
}

void CDlgHybridDecryptionDemo::OnOK() {
	// here we decrypt the cipher text using the symmetric key
	SHOW_HOUR_GLASS
	CrypTool::Cryptography::Symmetric::SymmetricOperation operation(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES, CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_DECRYPTION);
	operation.executeOnByteStrings(m_byteStringCipherText, m_byteStringSymmetricKey, m_byteStringPlainText);
	// create a temporary file name for the plain text
	const CString documentFileName = CrypTool::Utilities::createTemporaryFile();
	// write plain text to the created file
	m_byteStringPlainText.writeToFile(documentFileName);
	// fire up new document
	CString title;
	title.Format(IDS_STRING_HYBRID_DEC_TITLE, m_documentFileName);
	theApp.ThreadOpenDocumentFileNoMRU(documentFileName, title, (char*)(LPCTSTR)(m_byteStringSymmetricKey.toString(16)));
	HIDE_HOUR_GLASS
	CDialog::OnOK();
}

void CDlgHybridDecryptionDemo::OnCancel() {
	CDialog::OnCancel();
}

void CDlgHybridDecryptionDemo::OnButtonContinue() {
	nFirstVisibleLine = m_DisplayDataCtrl.GetFirstVisibleLine();
	UpdateDataDisplay();
}

void CDlgHybridDecryptionDemo::OnButtonShowCertificate() {
	// retrieve both public and private parameters for the certificate
	CString publicParameters;
	CString privateParameters;
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificatePublicParameters(m_selectedCertificateSerial, publicParameters);
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificatePrivateParameters(m_selectedCertificateSerial, m_selectedCertificatePassword, privateParameters);
	// show all parameters to the user
	CDlgCertificateStoreShowCertificateParametersAll dlgCertificateStoreShowCertificateParametersAll;
	dlgCertificateStoreShowCertificateParametersAll.setPublicParameters(publicParameters);
	dlgCertificateStoreShowCertificateParametersAll.setPrivateParameters(privateParameters);
	dlgCertificateStoreShowCertificateParametersAll.DoModal();
}

int CDlgHybridDecryptionDemo::UpdateDataDisplay() {
	// newline string for convenience
	const CString nl = "\r\n";
	// inherent step limit
	const int maxsteps = 3;

	if (step == 0) {
		// here the user is prompted to proceed with continue
		if (m_DisplayData="") {
			CString temp;
			temp.Format(IDS_STRING_HYBRID_DEC_MSG2);
			m_DisplayData += temp + nl;
			temp.Format(IDS_STRING_HYBRID_DEC_MSG12);
			m_DisplayData += temp + nl + nl;
		}
		nFirstVisibleLine = 0;
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
	}
	else if (step == 1) {
		// here the user is prompted to enter the password for the private key of the receiver
		CDlgCertificateStoreAskForPassword dlgCertificateStoreAskForPassword(m_selectedCertificateSerial);
		if (dlgCertificateStoreAskForPassword.DoModal() == IDOK) {
			m_selectedCertificatePassword = dlgCertificateStoreAskForPassword.getCertificatePassword();
			// here we try to acquire the private key (d) of the specified certificate 
			// using the password the user was prompted to supply
			if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPrivateKeyD(m_selectedCertificateSerial, m_selectedCertificatePassword, 10, sKeyPrivate)) {
				// update user interface
				CString temp;
				temp.Format(IDS_STRING_HYBRID_DEC_MSG13);
				m_DisplayData += temp + nl;
				temp.Format(IDS_STRING_HYBRID_DEC_MSG12);
				m_DisplayData += temp + nl;
				temp.Format(IDS_STRING_HYBRID_STEP_BY_STEP, step, maxsteps);
				m_Step = temp;
				step++;
				UpdateData(false);
				m_DisplayDataCtrl.LineScroll(step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */);
				UpdateData(true);
				// enable the button for showing the certificate
				m_ShowCertificate.EnableWindow(true);
			}
		}
	}
	else if (step == 2) {
		// update user interface
		CString temp;
		temp.Format(IDS_STRING_HYBRID_DEC_MSG4);
		m_DisplayData += temp + sKeyPrivate + nl + nl + nl;
		temp.Format(IDS_STRING_HYBRID_DEC_MSG5);
		m_DisplayData += temp + nl;
		temp.Format(IDS_STRING_HYBRID_DEC_MSG12);
		m_DisplayData += temp;
		temp.Format(IDS_STRING_HYBRID_STEP_BY_STEP, step, maxsteps);
		m_Step = temp;
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
	}
	else if (step == 3) {
		// here we try to decrypt the encrypted session key (NO PADDING!)
		SHOW_HOUR_GLASS
		const bool padding = false;
		CrypTool::Cryptography::Asymmetric::AsymmetricOperationEncryptOrDecrypt operation(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, CrypTool::Cryptography::Asymmetric::ASYMMETRIC_OPERATION_TYPE_DECRYPTION, padding);
		const bool result = operation.executeOnByteStrings(m_byteStringSymmetricKeyEncrypted, m_selectedCertificateSerial, m_selectedCertificatePassword, m_byteStringSymmetricKey);
		HIDE_HOUR_GLASS
		// truncate session key to appropriate size (depends on the padding option)
		if (padding) m_byteStringSymmetricKey.truncateRight(m_byteLengthSessionKey);
		else m_byteStringSymmetricKey.truncateLeft(m_byteLengthSessionKey);
		// update user interface
		CString temp;
		temp.Format(IDS_STRING_HYBRID_DEC_MSG6);
		m_DisplayData += temp + m_byteStringSymmetricKey.toString(16, " ") + nl + nl;
		temp.Format(IDS_STRING_HYBRID_DEC_MSG7);
		m_DisplayData += temp + nl + nl;
		temp.Format(IDS_STRING_HYBRID_STEP_BY_STEP, step, maxsteps);
		m_Step = temp;
		m_ContinueButtonCtrl.EnableWindow(FALSE);
		m_FlushDecDataCtrl.EnableWindow(TRUE);
		m_FlushDecDataCtrl.SetFocus();		
		step++;
		UpdateData(false);
		m_DisplayDataCtrl.LineScroll( step ? m_DisplayDataCtrl.GetLineCount() : 0 /* nFirstVisibleLine */ );
		UpdateData(true);
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CDlgHybridDecryptionDemo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, OnButtonContinue)
	ON_BN_CLICKED(IDC_SHOW_CERTIFICATE, OnButtonShowCertificate)
END_MESSAGE_MAP()
