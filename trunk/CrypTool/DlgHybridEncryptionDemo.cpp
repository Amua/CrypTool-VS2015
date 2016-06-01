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
	m_selectedCertificateSerial(0) {

	this->scaCertInfo.firstname = "";
	this->scaCertInfo.lastname = "";
	this->scaCertInfo.keytype = "";
	this->scaCertInfo.time = "";
	this->scaCertInfo.keyid = "";
	this->isSCABehaviourActivated = false;
	this->scaFile = "";

	//{{AFX_DATA_INIT(CDlgHybridEncryptionDemo)
	m_strEdit = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT

	int i;
	for (i = 0; i<11; i++)
	{
		m_ButtonStatus[i] = inactive;
		m_ActionPerformed[i] = false;
	}

	m_ButtonStatus[0] = active_not_pressed;		// diese drei Buttons können am Anfang schon gedrückt werden, daher
	m_ButtonStatus[1] = active_not_pressed;		// werden sie auf active_not_pressed gesetzt
	m_ButtonStatus[3] = active_not_pressed;

	//Array mit den Voraussetzungen

	for (i = 0; i<NO_BUTTONS; i++)
		g_Status[i] = m_ButtonStatus[i];

	for (i = 0; i<11; i++)
	{
		for (int j = 0; j<11; j++)
		{
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

	// initialize symmetric key to 16 bytes (128 bits)
	m_byteStringSymmetricKey.reset(16);
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

	//Laden der Bitmaps und als Steuerelemte anzeigen

	if (!m_bAuswahlDat)
	{
		m_ActionPerformed[0] = true;
	}
	//wenn m_bAuswahlDat auf false gesetzt ist, wurde Text aus dem CrypTool-Editor in das Editfeld des 
	//HybridverfahrenDialogs geladen, d.h. es muss keine Datei mehr ausgewählt werden.
	//Der Button um den Text anzuzeigen wird aktiviert indem m_ActionPerformed[0]auf true gesetzt wird
	EnDisButtons();
	//Aktualisieren der gegebenen Voraussetzungen
	ShowButtons();
	//Aktivieren /Deaktivieren der Buttons


	// Schriftart im Textfeld "aktuelle Datei", Felder in denen die Hashwerte und die Differenz angezeigt 
	// werden, "Courier" definieren
	LOGFONT lf = { 14,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Courier" };
	//Struktur lf wird deklariert und initialisiert
	m_font.CreateFontIndirect(&lf);
	//Objekt der Klasse CFont (m_font) wird gesetzt initialisiert
	CWnd* pStatic = GetDlgItem(IDC_EDIT_TXT);
	pStatic->SetFont(&m_font, false);


	// Falls ein Dokument vorliegt, wird es initial im Demo-Dialog angezeigt
	if (!m_documentFileName.IsEmpty())
	{
		// Den Fokus _nur_ dann auf den Button "Dokument" legen (und deshalb FALSE zurückgeben),
		// wenn auch wirklich ein Dokument vorliegt; für diesen Fall liefert DateiOeffnen(...) TRUE zurück!
		if (DateiOeffnen(m_documentFileName))
		{
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
	m_ButtonStatus[0]=active_pressed;
	// Attributwerte sichern
	CString s_strBuffTitle, s_strEdit, s_strTitle;
	s_strBuffTitle = m_documentTitle;
	s_strEdit = m_strEdit;
	s_strTitle = m_strTitle;

	m_documentTitle = "";
	m_strEdit = "";
	m_strTitle = "";

	CFileDialog m_dlgFile( TRUE ); // TRUE = Datei öffnen,FALSE = Datei speichern 
	if( m_dlgFile.DoModal() == IDOK ) 
	{
	//wenn auf den OK Button geklickt wird, wird der Pfadname und der Titel der gewählten Datei in 
	//lokale Variablen geschrieben
	//ausserdem wird die Dateigröße ermittelt und ebenfalls in eine Variable geschrieben
		CString loc_filename = "";
		UpdateData(false);
		loc_filename = m_dlgFile.GetPathName();
		m_documentTitle = m_dlgFile.GetFileName();
		DateiOeffnen(loc_filename);
		m_documentFileName = loc_filename;
		ShowButtons();
 	} 
	else
	//wenn auf Abbrechen geklickt wurde, wird abgebrochen
	{
		// Attribute zurücksetzen (siehe oben)
		m_documentTitle = s_strBuffTitle;
		m_strEdit = s_strEdit;
		m_strTitle = s_strTitle;

		UpdateData(false);

		return;
	}
}

void CDlgHybridEncryptionDemo::OnButtonGenSymKey() {
	m_ButtonStatus[1]=active_pressed;
	UpdateData(true);
	m_strEdit = "";
	m_strTitle="";
	// generate a random symmetric key
	m_byteStringSymmetricKey.randomize(m_byteStringSymmetricKey.getByteLength());
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
#ifndef _UNSTABLE
	// *** SCA-SPECIFIC BEGIN ***
	// für den Seitenkanalangriff: testen, ob die ausgewählte Datei
	// das Schlüsselwort enthält, anhand dessen Bob erkennt, ob die Nachricht
	// wirklich von Alice kommt; wenn nicht, dann dem Benutzer anbieten,
	// das Schlüsselwort an die Datei anzufügen
	if(this->isSCABehaviourActivated) {
		CString keyword;
		// retrieve keyword from registry (if unsuccessful, go with "Alice" by default)
		if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "SideChannelAttack") == ERROR_SUCCESS) {
			unsigned long u_length = 1024;
			char c_SCA_keyWord[1025];
			if(CT_READ_REGISTRY(c_SCA_keyWord, "Keyword", u_length))
				keyword = c_SCA_keyWord;
			else
				keyword.LoadStringA(IDS_SCA_KEYWORD);
			CT_CLOSE_REGISTRY();
		}
		bool keywordFound = false;
		// flomar, 07/15/2010
		// the latest bug fix: we read in BINARY mode instead of TEXT mode, and we're using 
		// "memcmp" instead of a normal string find; this way we can deal with binary zeros
		CFile infile;
		infile.Open(m_strPathSelDoc, CFile::modeRead | CFile::typeBinary);
		unsigned long lengthBuffer = infile.GetLength();
		unsigned int lengthKeyword = keyword.GetLength();
		char *bufferFile = new char[lengthBuffer + 1];
		char *bufferKeyword = keyword.GetBuffer();
		memset(bufferFile, 0, lengthBuffer + 1);
		infile.Read(bufferFile, lengthBuffer);
		for(unsigned int i=0; i<=(lengthBuffer - lengthKeyword); i++) {
			if(memcmp(bufferFile + i, bufferKeyword, lengthKeyword) == 0) {
				keywordFound = true;
			}
		}
		infile.Close();
		delete bufferFile;

		if(!keywordFound)
		{
			// Schlüsselwort NICHT enthalten! Benutzer informieren und fragen...
			LoadString(AfxGetInstanceHandle(),IDS_SCA_KEYWORDPROBLEM,pc_str,STR_LAENGE_STRING_TABLE);
			char temp[STR_LAENGE_STRING_TABLE+1];
			memset(temp, 0, STR_LAENGE_STRING_TABLE+1);
			sprintf(temp, pc_str, keyword);

			if(AfxMessageBox(temp, MB_YESNO) == IDYES)
			{
				// Schlüsselwort anfügen
				std::ofstream outfile(this->m_strPathSelDoc, ios::app);
				outfile.write(keyword, keyword.GetLength());
				outfile.close();
			}
		}
	}
	// *** SCA-SPECIFIC END ***
#endif
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
	// execute RSA encryption
	SHOW_HOUR_GLASS
	CrypTool::Cryptography::Asymmetric::AsymmetricOperationEncryptOrDecrypt operation(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, CrypTool::Cryptography::Asymmetric::ASYMMETRIC_OPERATION_TYPE_ENCRYPTION);
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
		lines = (m_iDocSize + INFO_TEXT_COLUMNS - 1) / INFO_TEXT_COLUMNS;
		rest = (m_iDocSize) % INFO_TEXT_COLUMNS;
		destSize = lines * linelen; // - INFO_TEXT_COLUMNS + rest;
	}
	char *dest = new char[destSize + 1];
	SHOW_HOUR_GLASS
		int err = HexDumpMem(dest, destSize, (unsigned char*)m_byteStringPlainText.getByteData(), m_iDocSize, INFO_TEXT_COLUMNS);
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
	// declare temporary variable
	CString stringTemp;
	// this byte string will hold all the result data to be written
	CrypTool::ByteString byteStringResult;

	SHOW_HOUR_GLASS

		// write receiver
		stringTemp.LoadString(IDS_STRING_HYBRID_RECIEVER);
	byteStringResult += stringTemp;
	stringTemp.Format("%d", m_selectedCertificateSerial);
	byteStringResult += stringTemp;

	// write asymmetric algorithm
	stringTemp.LoadString(IDS_STRING_HYBRID_ASYM_METHOD);
	byteStringResult += stringTemp;
	stringTemp = "RSA";
	byteStringResult += stringTemp;

	// write symmetric algorithm
	stringTemp.LoadString(IDS_STRING_HYBRID_SYM_METHOD);
	byteStringResult += stringTemp;
	stringTemp = "AES";
	byteStringResult += stringTemp;

	// write length of encrypted session key
	stringTemp.LoadString(IDS_STRING_HYBRID_LENGTH_ENC_KEY);
	byteStringResult += stringTemp;
	stringTemp.Format("%d", m_byteStringSymmetricKeyEncrypted.getByteLength() * 8);
	byteStringResult += stringTemp;

	// write encrypted session key
	stringTemp.LoadString(IDS_STRING_HYBRID_ENC_KEY);
	byteStringResult += stringTemp;
	byteStringResult += m_byteStringSymmetricKeyEncrypted;

	// write cipher text
	stringTemp.LoadString(IDS_STRING_HYBRID_CIPHERTEXT);
	byteStringResult += stringTemp;
	byteStringResult += m_byteStringCipherText;

	// create a file for the result (with the .hex suffix)
	const CString fileNameResult = CrypTool::Utilities::createTemporaryFile(".hex");
	// write result byte string to temporary file
	byteStringResult.writeToFile(fileNameResult);

	HIDE_HOUR_GLASS

		// open result file in new document
		CAppDocument *document = theApp.OpenDocumentFileNoMRU(fileNameResult);
	if (document) {
		// create a meaningful title
		CString receiverName;
		if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringName(m_selectedCertificateSerial, receiverName)) {
			CString title;
			title.Format(IDS_STRING_HYBRID_ENC_TITLE, m_documentTitle, receiverName);
			document->SetTitle(title);
		}
	}

	// if the SCA behavior is active, store the result file name in scaFile 
	// and don't remove the result file
	if (isSCABehaviourActivated) {
		scaFile = fileNameResult;
	}
	else {
		remove(fileNameResult);
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
	// assign the document size, and return false if empty
	m_iDocSize = m_byteStringPlainText.getByteLength();
	if (m_iDocSize == 0) {
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

void CDlgHybridEncryptionDemo::activateSCABehaviour() {
	this->isSCABehaviourActivated = true;
}

CString CDlgHybridEncryptionDemo::getSCAFile() {
	return this->scaFile;
}

SCACertificateInformation CDlgHybridEncryptionDemo::getCertInfo() {
	return this->scaCertInfo;
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
