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
#include "DlgHybridEncryptionDemo.h"

#include "DlgShowKeyParameter.h"
#include "DlgCertificateStoreSelectCertificate.h"

#include "DialogeMessage.h"
#include "FileTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NO_BUTTONS 11
int g_Status[NO_BUTTONS];

CDlgHybridEncryptionDemo::CDlgHybridEncryptionDemo(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent) :
	CDialog(CDlgHybridEncryptionDemo::IDD, pParent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle),
	m_byteLengthSessionKey(16),
	m_selectedCertificateSerial(0),
	m_documentFileNameResult("") {
	for (int i = 0; i<11; i++) {
		m_ButtonStatus[i] = inactive;
		m_ActionPerformed[i] = false;
	}
	m_ButtonStatus[0] = active_not_pressed;
	m_ButtonStatus[1] = active_not_pressed;
	m_ButtonStatus[3] = active_not_pressed;
	for (int i = 0; i < NO_BUTTONS; i++) {
		g_Status[i] = m_ButtonStatus[i];
	}
	for (int i = 0; i<11; i++) {
		for (int j = 0; j<11; j++) {
			m_setMatrix[i][j] = false;
		}
	}
	m_setMatrix[2][1] = true;
	m_setMatrix[4][3] = true;
	m_setMatrix[5][0] = true;
	m_setMatrix[5][1] = true;
	m_setMatrix[6][1] = true;
	m_setMatrix[6][3] = true;
	m_setMatrix[7][0] = true;
	m_setMatrix[8][5] = true;
	m_setMatrix[9][6] = true;
	m_setMatrix[10][0] = true;
	m_setMatrix[10][1] = true;
	m_setMatrix[10][3] = true;
	m_setMatrix[10][5] = true;
	m_setMatrix[10][6] = true;
	m_bAuswahlDat = true;
	// initialize symmetric key to specified byte length
	m_byteStringSymmetricKey.reset(m_byteLengthSessionKey);
}

CDlgHybridEncryptionDemo::~CDlgHybridEncryptionDemo() {

}

BOOL CDlgHybridEncryptionDemo::OnInitDialog() {
	CDialog::OnInitDialog();
	m_ctrlBmpSechseck1.AutoLoad(IDC_BUTTON1_TXT_EINFUEGEN, this);
	m_ctrlBmpSechseck2.AutoLoad(IDC_BUTTON_GEN_SYM_KEY, this);
	m_ctrlBmpSechseck3.AutoLoad(IDC_BUTTON_GET_ASYM_KEY, this);
	m_ctrlBmpRaute1.AutoLoad(IDC_BUTTON_SHOWTXT, this);
	m_ctrlBmpRaute2.AutoLoad(IDC_BUTTON_SHOW_SYM_KEY, this);
	m_ctrlBmpRaute3.AutoLoad(IDC_BUTTON_SHOW_ASYM_KEY, this);
	m_ctrlBmpRaute4.AutoLoad(IDC_BUTTON2, this);
	m_ctrlBmpRaute5.AutoLoad(IDC_BUTTON3, this);
	m_ctrlBmpRechteck1.AutoLoad(IDC_BUTTON_ENC_TXT_SYM, this);
	m_ctrlBmpRechteck2.AutoLoad(IDC_BUTTON_ENC_KEY_ASYM, this);
	m_ctrlBmpOval1.AutoLoad(IDCANCEL, this);
	m_ctrlBmpOval2.AutoLoad(IDC_BUTTON_DATENAUSGABE, this);
	if (!m_bAuswahlDat) {
		m_ActionPerformed[0] = true;
	}
	EnDisButtons();
	ShowButtons();
	LOGFONT lf = { 14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Courier" };
	m_font.CreateFontIndirect(&lf);
	CWnd* pStatic = GetDlgItem(IDC_EDIT_TXT);
	pStatic->SetFont(&m_font, false);
	if (!m_documentFileName.IsEmpty()) {
		if (DateiOeffnen(m_documentFileName)) {
			EnDisButtons();
			ShowButtons();
			OnButtonShowDocument();
			m_ctrlBmpRaute1.SetFocus();
			return FALSE;
		}
	}
	return TRUE;
}

void CDlgHybridEncryptionDemo::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TXT, m_strEdit);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
}

void CDlgHybridEncryptionDemo::OnButtonGetDocument() {
	m_ButtonStatus[0] = active_pressed;
	CString s_strBuffTitle, s_strEdit, s_strTitle;
	s_strBuffTitle = m_documentTitle;
	s_strEdit = m_strEdit;
	s_strTitle = m_strTitle;
	m_documentTitle = "";
	m_strEdit = "";
	m_strTitle = "";
	CFileDialog m_dlgFile(TRUE);
	if( m_dlgFile.DoModal() == IDOK ) {
		CString loc_filename = "";
		UpdateData(false);
		loc_filename = m_dlgFile.GetPathName();
		m_documentTitle = m_dlgFile.GetFileName();
		DateiOeffnen(loc_filename);
		m_documentFileName = loc_filename;
		ShowButtons();
 	} 
	else {
		m_documentTitle = s_strBuffTitle;
		m_strEdit = s_strEdit;
		m_strTitle = s_strTitle;
		UpdateData(false);
	}
}

void CDlgHybridEncryptionDemo::OnButtonGenSymKey() {
	m_ButtonStatus[1]=active_pressed;
	UpdateData(true);
	m_strEdit = "";
	m_strTitle="";
	// generate a random symmetric key
	m_byteStringSymmetricKey.randomize(m_byteLengthSessionKey);
	SetCondition(1,true);
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowSymKey() {
	if (inactive==m_ButtonStatus[2]) {
		Message( IDS_STRING_HYB_SHOW_SYM_KEY, MB_ICONEXCLAMATION );
		return;
	}
	m_strEdit = m_byteStringSymmetricKey.toString(16, " ");
	m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_SYM_KEY);
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonEncDocumentSym() {
	// check user interface
	if (inactive == m_ButtonStatus[5]) {
		Message(IDS_STRING_HYB_ENC_DOC_SYM, MB_ICONEXCLAMATION);
		return;
	}
	// update user interface
	m_ButtonStatus[5]=active_pressed;
	// execute AES encryption
	SHOW_HOUR_GLASS
	CrypTool::Cryptography::Symmetric::SymmetricOperation operation(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES, CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_ENCRYPTION);
	const bool result = operation.executeOnByteStrings(m_byteStringPlainText, m_byteStringSymmetricKey, m_byteStringCipherText);
	HIDE_HOUR_GLASS
	if (!result) return;
	// update user interface
	SetCondition(5,true);
	m_strTitle = "";
	m_strEdit = "";
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonGetAsymKey() {
	// let the user pick an RSA certificate
	CDlgCertificateStoreSelectCertificate dlgCertificateStoreSelectCertificate;
	dlgCertificateStoreSelectCertificate.showCertificateTypes(true, false, false);
	if (dlgCertificateStoreSelectCertificate.DoModal() != IDOK) return;
	m_selectedCertificateSerial = dlgCertificateStoreSelectCertificate.getSelectedCertificateSerial();
	if (m_selectedCertificateSerial > 0) {
		m_ButtonStatus[3] = active_pressed;
		SetCondition(3, true);
	}
	else {
		SetCondition(3, false);
	}
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonEncKeyAsym() {
	// check user interface
	if (inactive == m_ButtonStatus[6]) {
		Message(IDS_STRING_HYB_ENC_KEY_ASYM, MB_ICONEXCLAMATION);
		return;
	}
	// update user interface
	m_ButtonStatus[6] = active_pressed;
	// execute RSA encryption (NO PADDING!)
	SHOW_HOUR_GLASS
	const bool padding = false;
	CrypTool::Cryptography::Asymmetric::AsymmetricOperationEncryptOrDecrypt operation(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, CrypTool::Cryptography::Asymmetric::ASYMMETRIC_OPERATION_TYPE_ENCRYPTION, padding);
	const bool result = operation.executeOnByteStrings(m_byteStringSymmetricKey, m_selectedCertificateSerial, "", m_byteStringSymmetricKeyEncrypted);
	HIDE_HOUR_GLASS
	if (!result) return;
	// update user interface
	SetCondition(6, true);
	m_strTitle = "";
	m_strEdit = "";
	UpdateData(false); 
}

void CDlgHybridEncryptionDemo::OnButtonShowAsymKey() {
	// create the dialog, and then display it
	CDlgShowKeyParameter dlgShowKeyParameter(m_selectedCertificateSerial);
	dlgShowKeyParameter.DoModal();
}

void CDlgHybridEncryptionDemo::OnButtonShowDocument() {
	if (inactive == m_ButtonStatus[7]) {
		Message(IDS_STRING_HYB_SHOW_DOC, MB_ICONEXCLAMATION);
		return;
	}
	m_strTitle = m_documentTitle;
	int destSize;
	{
		int linelen;
		int lines, rest;

		linelen = 11 + INFO_TEXT_COLUMNS * 4;
		lines = (m_byteStringPlainText.getByteLength() + INFO_TEXT_COLUMNS - 1) / INFO_TEXT_COLUMNS;
		rest = (m_byteStringPlainText.getByteLength()) % INFO_TEXT_COLUMNS;
		destSize = lines * linelen; // - INFO_TEXT_COLUMNS + rest;
	}
	char *dest = new char[destSize + 1];
	SHOW_HOUR_GLASS
	int err = HexDumpMem(dest, destSize, (unsigned char*)m_byteStringPlainText.getByteData(), m_byteStringPlainText.getByteLength(), INFO_TEXT_COLUMNS);
	HIDE_HOUR_GLASS
	m_strEdit = dest;
	delete[]dest;
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowEncDocument() {
	if (inactive == m_ButtonStatus[8]) {
		Message(IDS_STRING_HYB_SHOW_ENC_DOC, MB_ICONEXCLAMATION);
		return;
	}
	m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_SYM_ENC_DOC);
	int destSize;
	{
		int linelen;
		int lines, rest;

		linelen = 11 + INFO_TEXT_COLUMNS * 4;
		lines = (m_byteStringCipherText.getByteLength() + INFO_TEXT_COLUMNS - 1) / INFO_TEXT_COLUMNS;
		rest = (m_byteStringCipherText.getByteLength()) % INFO_TEXT_COLUMNS;
		destSize = lines * linelen; // - INFO_TEXT_COLUMNS + rest;
	}
	char *dest = new char[destSize + 1];
	SHOW_HOUR_GLASS
		int err = HexDumpMem(dest, destSize, (unsigned char*)m_byteStringCipherText.getByteData(), m_byteStringCipherText.getByteLength(), INFO_TEXT_COLUMNS);
	HIDE_HOUR_GLASS
		m_strEdit = dest;
	delete[]dest;
	UpdateData(false);
}

void CDlgHybridEncryptionDemo::OnButtonShowEncSymKey() {
	if (inactive == m_ButtonStatus[9]) {
		Message(IDS_STRING_HYB_ENC_SYM_KEY, MB_ICONEXCLAMATION);
		return;
	}
	SHOW_HOUR_GLASS
		m_strTitle.LoadString(IDS_STRING_HYBRID_ENC_ASYM_ENC_KEY);
	m_strEdit = m_byteStringSymmetricKeyEncrypted.toString(16, " ");
	UpdateData(false);
	HIDE_HOUR_GLASS
}

void CDlgHybridEncryptionDemo::OnButtonDatenausgabe() {
	// check user interface
	if (!m_ButtonStatus[10]) {
		Message(IDS_STRING_HYB_SHOW_DATA, MB_ICONEXCLAMATION);
		return;
	}

	SHOW_HOUR_GLASS

	// create result file name (with the .hex suffix)
	m_documentFileNameResult = CrypTool::Utilities::createTemporaryFile(".hex");
	// create result file
	CrypTool::Utilities::createHybridEncryptedFile(m_documentFileNameResult, m_selectedCertificateSerial, CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES, m_byteStringSymmetricKeyEncrypted, m_byteStringCipherText);

	HIDE_HOUR_GLASS

	// open result file in new document
	CAppDocument *document = theApp.OpenDocumentFileNoMRU(m_documentFileNameResult);
	if (document) {
		// create a meaningful title
		CString receiverName;
		if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringName(m_selectedCertificateSerial, receiverName)) {
			CString title;
			title.Format(IDS_STRING_HYBRID_ENC_TITLE, m_documentTitle, receiverName);
			document->SetTitle(title);
		}
	}
	CDialog::OnOK();
}

void CDlgHybridEncryptionDemo::OnPaint() {
	CPaintDC dc(this);
	CBitmap bmp, *poldbmp;
	CDC memdc;
	// Load the bitmap resource
	bmp.LoadBitmap(IDB_HYBRID_BACK);
	// Create a compatible memory DC
	memdc.CreateCompatibleDC(&dc);
	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject(&bmp);
	// Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt(0, 0, 838, 730, &memdc, 0, 0, SRCCOPY);
	memdc.SelectObject(poldbmp);
}

void CDlgHybridEncryptionDemo::SetCondition(int button,bool state) {
	m_ActionPerformed[button] = state;
	ResetDependent(button);
	EnDisButtons();
	ShowButtons();
}

void CDlgHybridEncryptionDemo::ResetDependent(int button) {
	int i;
	for (i = 0; i < 11; i++) {
		if (m_setMatrix[i][button] && m_ActionPerformed[i]) {
			m_ActionPerformed[i] = false;
			ResetDependent(i);
		}
	}
}

bool CDlgHybridEncryptionDemo::DateiOeffnen(const CString &DateiPfadName) {
	SHOW_HOUR_GLASS
	// try to read plain text from the specified file
	if (!m_byteStringPlainText.readFromFile(DateiPfadName)) {
		return false;
	}
	// return false if plain text is empty
	if (m_byteStringPlainText.getByteLength() == 0) {
		return false;
	}
	m_bAuswahlDat = false;
	m_documentFileName = DateiPfadName;
	HIDE_HOUR_GLASS
	SetCondition(0, true);
	return true;
}

void CDlgHybridEncryptionDemo::EnDisButtons() {
	for(int i=0;i<11;i++) {
		if(!m_ActionPerformed[i]) {
			m_ButtonStatus[i]=active_not_pressed;
		}
		else {
			m_ButtonStatus[i]=active_pressed;
		}
		for(int j=0;j<11;j++) {
			if(m_setMatrix[i][j]) {
				if(!m_ActionPerformed[j]) {
					m_ButtonStatus[i]=inactive;
					break;
				}
			}
		}
	}
}

void CDlgHybridEncryptionDemo::ShowButtons() {
	m_hFocus = GetFocus();
	for(int i=0;i<11;i++) {
		if (g_Status[i] != m_ButtonStatus[i]) {
			switch(i) {
			case 0:
				if (active_not_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck1.LoadBitmaps("SECHSECK1_R_U", "SECHSECK1_R_D", "SECHSECK1_R_F", NULL);
					m_ctrlBmpSechseck1.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck1.ShowWindow(SW_SHOW);
				}
				else if (active_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck1.LoadBitmaps("SECHSECK1_G_U", "SECHSECK1_G_D", "SECHSECK1_G_F", NULL);
					m_ctrlBmpSechseck1.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck1.ShowWindow(SW_SHOW);
				}
				break;
			case 1:
				if (active_not_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck2.LoadBitmaps("SECHSECK2_R_U", "SECHSECK2_R_D", "SECHSECK2_R_F", NULL);
					m_ctrlBmpSechseck2.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck2.ShowWindow(SW_SHOW);
				}
				else if (active_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck2.LoadBitmaps("SECHSECK2_G_U", "SECHSECK2_G_D", "SECHSECK2_G_F", NULL);
					m_ctrlBmpSechseck2.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck2.ShowWindow(SW_SHOW);
				}
				break;
			case 2:
				if (m_ButtonStatus[i]) {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2_B_U", "RAUTE2_B_D", "RAUTE2_B_F", NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRaute2.LoadBitmaps("RAUTE2_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute2.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute2.ShowWindow(SW_SHOW);
				}
				break;
			case 3:
				if (active_not_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck3.LoadBitmaps("SECHSECK3_R_U", "SECHSECK3_R_D", "SECHSECK3_R_F", NULL);
					m_ctrlBmpSechseck3.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck3.ShowWindow(SW_SHOW);
				}
				else if(active_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpSechseck3.LoadBitmaps("SECHSECK3_G_U", "SECHSECK3_G_D", "SECHSECK3_G_F", NULL);
					m_ctrlBmpSechseck3.ShowWindow(SW_HIDE);
					m_ctrlBmpSechseck3.ShowWindow(SW_SHOW);
				}
				break;
			case 4:
				if (m_ButtonStatus[i]) {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3_B_U", "RAUTE3_B_D", "RAUTE3_B_F", NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRaute3.LoadBitmaps("RAUTE3_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute3.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute3.ShowWindow(SW_SHOW);
				}
				break;
			case 5:
				if (active_not_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_R_U", "RECHTECK1_R_D", "RECHTECK1_R_F", NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
				}
				else if (active_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_G_U", "RECHTECK1_G_D", "RECHTECK1_G_F", NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRechteck1.LoadBitmaps("RECHTECK1_X_U", NULL, NULL, NULL);
					m_ctrlBmpRechteck1.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck1.ShowWindow(SW_SHOW);
				}
				break;
			case 6:
				if (active_not_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_R_U", "RECHTECK2_R_D", "RECHTECK2_R_F", NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
				}
				else if (active_pressed == m_ButtonStatus[i]) {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_G_U", "RECHTECK2_G_D", "RECHTECK2_G_F", NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRechteck2.LoadBitmaps("RECHTECK2_X_U", NULL, NULL, NULL);
					m_ctrlBmpRechteck2.ShowWindow(SW_HIDE);
					m_ctrlBmpRechteck2.ShowWindow(SW_SHOW);
				}
				break;
			case 7:
				if (m_ButtonStatus[i]) {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1_B_U", "RAUTE1_B_D", "RAUTE1_B_F", NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRaute1.LoadBitmaps("RAUTE1_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute1.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute1.ShowWindow(SW_SHOW);
				}
				break;
			case 8:
				if (m_ButtonStatus[i]) {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4_B_U", "RAUTE4_B_D", "RAUTE4_B_F", NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRaute4.LoadBitmaps("RAUTE4_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute4.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute4.ShowWindow(SW_SHOW);
				}
				break;
			case 9:
				if (m_ButtonStatus[i]) {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5_B_U", "RAUTE5_B_D", "RAUTE5_B_F", NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
				}
				else {
					m_ctrlBmpRaute5.LoadBitmaps("RAUTE5_X_U", NULL, NULL, NULL);
					m_ctrlBmpRaute5.ShowWindow(SW_HIDE);
					m_ctrlBmpRaute5.ShowWindow(SW_SHOW);
				}
				break;
   		   case 10:
			   if (m_ButtonStatus[i]) {
					m_ctrlBmpOval2.LoadBitmaps("OVAL2_G_U", "OVAL2_G_D", "OVAL2_G_F", NULL);
					m_ctrlBmpOval2.ShowWindow(SW_HIDE);
					m_ctrlBmpOval2.ShowWindow(SW_SHOW);
			   }
			   else {
					m_ctrlBmpOval2.LoadBitmaps("OVAL2_X_U", NULL, NULL, NULL);
					m_ctrlBmpOval2.ShowWindow(SW_HIDE);
					m_ctrlBmpOval2.ShowWindow(SW_SHOW);
			   }
			   break;
			}
		}
		g_Status[i] = m_ButtonStatus[i];
	}
	m_hFocus->SetFocus();
}

BEGIN_MESSAGE_MAP(CDlgHybridEncryptionDemo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1_TXT_EINFUEGEN, OnButtonGetDocument)
	ON_BN_CLICKED(IDC_BUTTON_ENC_KEY_ASYM, OnButtonEncKeyAsym)
	ON_BN_CLICKED(IDC_BUTTON_ENC_TXT_SYM, OnButtonEncDocumentSym)
	ON_BN_CLICKED(IDC_BUTTON_GEN_SYM_KEY, OnButtonGenSymKey)
	ON_BN_CLICKED(IDC_BUTTON_GET_ASYM_KEY, OnButtonGetAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_SYM_KEY, OnButtonShowSymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ASYM_KEY, OnButtonShowAsymKey)
	ON_BN_CLICKED(IDC_BUTTON_SHOWTXT, OnButtonShowDocument)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonShowEncDocument)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonShowEncSymKey)
	ON_BN_CLICKED(IDC_BUTTON_DATENAUSGABE, OnButtonDatenausgabe)
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()
