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
#include "DlgHMAC.h"
#include "CrypToolTools.h"
#include "FileTools.h"
#include "ChrTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgHMAC::CDlgHMAC(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent) :
	CDialog(CDlgHMAC::IDD, pParent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle) {
	m_position = -1;
	m_key = _T("");
	m_secondkey = _T("");
	m_str_outer_input = _T("");
}

BOOL CDlgHMAC::OnInitDialog() {
	CDialog::OnInitDialog();

	// load document specified at construction into temporary byte string
	CrypTool::ByteString byteStringTemporary;
	byteStringTemporary.readFromFile(m_documentFileName);
	// try to truncate the temporary byte string to the specified length limit, 
	// and also remove all bytes (including and) beyond the first null byte; if 
	// the byte string is modified in any way, the user is notified; if the 
	// resulting byte string is empty, the user is notified again and then the 
	// dialog is cancelled
	const unsigned int truncateAtLength = 16000;
	const bool truncateAtFirstNullByte = true;
	if (CrypTool::Utilities::truncateByteString(byteStringTemporary, truncateAtLength, truncateAtFirstNullByte) == 0) {
		CString message;
		message.Format(IDS_STRING_Hashdemo_KeineWerteGefunden);
		AfxMessageBox(message, MB_ICONEXCLAMATION);
		EndDialog(IDCANCEL);
	}
	// assign the temporary byte string to the internal CString variable
	strText = byteStringTemporary.toString();
	m_originalMessage = strText;
	
	LOGFONT lf = { 8,0,0,0,FW_NORMAL,false,false,false,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Courier" };
	m_font.CreateFontIndirect(&lf);
	CWnd* pStatic1 = GetDlgItem(IDC_EDIT_KEY);
	CWnd* pStatic2 = GetDlgItem(IDC_EDIT_KEY2);
	CWnd* pStatic = GetDlgItem(IDC_SHOW_TEXT);
	CWnd* pStatic3 = GetDlgItem(IDC_SHOW_MAC);
	CWnd* pStatic4 = GetDlgItem(IDC_SHOW_HASH);

	pStatic->SetFont(&m_font, false);
	pStatic1->SetFont(&m_font, false);
	pStatic2->SetFont(&m_font, false);
	pStatic3->SetFont(&m_font, false);
	pStatic4->SetFont(&m_font, false);

	// initialize the supported hash algorithm types
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD4);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD5);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA1);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA256);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA512);
	vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_RIPEMD160);

	// initialize combo box with supported hash algorithm types
	for (size_t index = 0; index < vectorHashAlgorithmTypes.size(); index++) {
		const CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType = vectorHashAlgorithmTypes[index];
		m_comboCtrlSelectHashFunction.AddString(CrypTool::Cryptography::Hash::getHashAlgorithmName(hashAlgorithmType));
	}

	// initialize combox box with supported HMAC variants
	CString str;
	str.LoadStringA(IDS_HMAC_ALGORITHM_HKM);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HMK);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HKMK);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_HK1MK2);		m_comboCtrlSelectHMACFunction.AddString(str);
	str.LoadStringA(IDS_HMAC_ALGORITHM_RFC2104);	m_comboCtrlSelectHMACFunction.AddString(str);

	// flomar, 08/13/2015: here we try to select some meaningful default values for both algorithms 
	// (SHA256 and HKM) and the key-- this may be useful for inexperienced users; please note that this
	// extension might be ignored if someone tampers with the algorithms above, which in turn might 
	// cause assertions
	m_comboCtrlSelectHashFunction.SetCurSel(4);
	m_comboCtrlSelectHMACFunction.SetCurSel(0);
	m_key = "foobar";
	UpdateData(false);
	OnCbnSelendokComboSelectHashFunction();
	OnCbnSelendokComboSelectHmacAlgorithm();

	// flomar, 01/20/2010
	shownInfoMessageNoKey = false;
	shownInfoMessageOneKey = false;
	shownInfoMessageDouble = false;

	UpdateData(true);
	m_text.SetWindowText(strText);
	m_originalMessage = strText;
	UpdateData(false);

	return TRUE;
}

void CDlgHMAC::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY2, m_ctrl_secondkey);
	DDX_Control(pDX, IDC_EDIT_KEY, m_ctrl_key);
	DDX_Control(pDX, IDC_SHOW_MAC, m_mac);
	DDX_Control(pDX, IDC_SHOW_TEXT, m_text);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
	DDX_Text(pDX, IDC_EDIT_KEY2, m_secondkey);
	DDX_Text(pDX, IDC_SHOW_MAC, m_str_mac);
	DDX_Text(pDX, IDC_SHOW_TEXT, m_str_outer_input);
	DDX_Text(pDX, IDC_EDIT_ORIGINAL_MESSAGE, m_originalMessage);
	DDX_Text(pDX, IDC_SHOW_HASH, m_innerHash);
	DDX_Control(pDX, IDC_COMBO_SELECT_HASH_FUNCTION, m_comboCtrlSelectHashFunction);
	DDX_Control(pDX, IDC_COMBO_SELECT_HMAC_ALGORITHM, m_comboCtrlSelectHMACFunction);
}

void CDlgHMAC::OnBUTTONSecondKey() {
	UpdateData(true);
	m_ctrl_secondkey.EnableWindow(TRUE);
	UpdateData(false);

	calculateMACAndUpdateGUI();

	// if there is no key selected, set focus to first key
	if (m_key.GetLength() == 0 && m_secondkey.GetLength() == 0)
		this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
	// if there is the first key selected, set focus to second key
	if (m_key.GetLength() > 0)
		this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
}

void CDlgHMAC::OnEditText() {
	UpdateData(true);
	m_text.GetWindowText(strText);
	UpdateData(false);
}

void CDlgHMAC::OnEditKey() {
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnEditOriginalMessage() {
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnEditSecondKey() {
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnCbnSelendokComboSelectHashFunction() {
	UpdateData(true);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::OnCbnSelendokComboSelectHmacAlgorithm() {
	UpdateData(true);
	m_position = m_comboCtrlSelectHMACFunction.GetCurSel();

	switch (m_position) {
	case 0: // H(m, k)
	case 1: // H(k, m)
	case 2: // H(k,m,k)
	case 4: // H(k,H(m,k))
		m_ctrl_secondkey.EnableWindow(FALSE);
		if (m_key.GetLength() == 0)
			this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
		break;
	case 3: // H(k,m,k')
		m_ctrl_secondkey.EnableWindow(TRUE);
		if (m_key.GetLength() == 0)
			this->GetDlgItem(IDC_EDIT_KEY)->SetFocus();
		else if (m_secondkey.GetLength() == 0)
			this->GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
		break;
	}
	UpdateData(false);
	calculateMACAndUpdateGUI();
}

void CDlgHMAC::keyEmpty(int IDS) {
	// flomar, 01/20/2010
	// this is dirty, but I don't want to dig any deeper than necessary before the beta release;
	// what we're doing here is making sure the info messages for certain events are not displayed 
	// over and over again, but only once during dialog lifetime
	if (IDS == IDS_STRING_MAC_NoKey) {
		if (!shownInfoMessageNoKey) shownInfoMessageNoKey = true;
		else return;
	}
	if (IDS == IDS_STRING_MAC_OnlyOneKey) {
		if (!shownInfoMessageOneKey) shownInfoMessageOneKey = true;
		else return;
	}
	if (IDS == IDS_STRING_MAC_Double) {
		if (!shownInfoMessageDouble) shownInfoMessageDouble = true;
		else return;
	}
	LoadString(AfxGetInstanceHandle(), IDS, pc_str, 150);
	AfxMessageBox(pc_str, MB_ICONINFORMATION | MB_OK);
}

void CDlgHMAC::SetMac(CString input) {
	CrypTool::ByteString byteStringInput;
	CrypTool::ByteString byteStringOutput;
	byteStringInput.fromString(input);
	CrypTool::Cryptography::Hash::HashOperation hashOperation(getHashAlgorithmType());
	hashOperation.executeOnByteStrings(byteStringInput, byteStringOutput);
	m_str_mac = byteStringOutput.toString(16, " ");
}

void CDlgHMAC::calculateMACAndUpdateGUI() {
	UpdateData(true);

	m_str_mac = _T("");
	m_innerHash = _T("");
	m_str_outer_input = _T("");

	switch (m_position)
	{
		case 0: if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_key + m_originalMessage;
				break;//Schlüssel vorne
		case 1:	if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_originalMessage + m_key;
				break;//Schlüssel hinten
		case 2:	if (m_key == "") keyEmpty(IDS_STRING_MAC_NoKey);
				m_str_outer_input = m_key + m_originalMessage + m_key;
				break;//Schlüssel vorne und hinten
		case 3: if ((m_key == "") && (m_secondkey == ""))		keyEmpty(IDS_STRING_MAC_NoKey);
				else if ((m_key == "") && (m_secondkey != ""))  keyEmpty(IDS_STRING_MAC_OnlyOneKey);
				else if ((m_key != "") && (m_secondkey == ""))  keyEmpty(IDS_STRING_MAC_OnlyOneKey);
				m_str_outer_input = m_key + m_originalMessage + m_secondkey;
				break;//zwei Schlüssel
		case 4: 
				{
					if (m_key == "") keyEmpty(IDS_STRING_MAC_Double);

					// flomar, 01/31/2012: the old RFC2104 implementation assumed a block size of 
					// 64 bytes; that's fine for all the hash functions we use in this dialog except 
					// SHA512, which operates with 128 bytes; the old implementation with SHA512 did 
					// not produce the expected test vectors (see http://tools.ietf.org/html/rfc4231);
					// thanks to peter.brand@haw-hamburg.de for noticing and reporting this bug

					// determine the block size (see above)
					const size_t blockSize = getHashAlgorithmType() == CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA512 ? 128 : 64;

					// declare byte strings
					CrypTool::ByteString byteStringIPad;
					CrypTool::ByteString byteStringIPadAndMessage;
					CrypTool::ByteString byteStringOPad;
					CrypTool::ByteString byteStringOPadAndHashValueInner;
					CrypTool::ByteString byteStringKey;
					CrypTool::ByteString byteStringKeyOriginal;
					CrypTool::ByteString byteStringMessage;
					CrypTool::ByteString byteStringHashValueInner;
					CrypTool::ByteString byteStringHashValueOuter;
					// initialize byte strings
					byteStringIPad.reset(blockSize);
					byteStringOPad.reset(blockSize);
					byteStringKey.reset(blockSize);
					// initialize the key
					byteStringKeyOriginal.fromString(m_key);
					// copy key into k_ipad and k_opad
					memcpy(byteStringIPad.getByteData(), byteStringKeyOriginal.getByteData(), byteStringKeyOriginal.getByteLength());
					memcpy(byteStringOPad.getByteData(), byteStringKeyOriginal.getByteData(), byteStringKeyOriginal.getByteLength());
					// initialize k_ipad and k_opad according to RFC2104
					for (size_t index = 0; index < blockSize; index++) {
						byteStringIPad.getByteData()[index] ^= 0x36;
						byteStringOPad.getByteData()[index] ^= 0x5c;
					}
					// hash the key
					CrypTool::Cryptography::Hash::HashOperation hashOperationKey(getHashAlgorithmType());
					hashOperationKey.executeOnByteStrings(byteStringKeyOriginal, byteStringKey);
					// initialize the message byte string
					byteStringMessage.fromString(m_originalMessage);
					// initialize the ipad and message byte string
					byteStringIPadAndMessage += byteStringIPad;
					byteStringIPadAndMessage += byteStringMessage;
					// inner hash
					CrypTool::Cryptography::Hash::HashOperation hashOperationInner(getHashAlgorithmType());
					hashOperationInner.executeOnByteStrings(byteStringIPadAndMessage, byteStringHashValueInner);
					// initialize the opad and hash value inner byte string
					byteStringOPadAndHashValueInner += byteStringOPad;
					byteStringOPadAndHashValueInner += byteStringHashValueInner;
					// update display variables
					m_innerHash = byteStringHashValueInner.toString(16, " ");
					m_str_outer_input = byteStringOPadAndHashValueInner.toString(16, " ");
					// outer hash
					CrypTool::Cryptography::Hash::HashOperation hashOperationOuter(getHashAlgorithmType());
					hashOperationOuter.executeOnByteStrings(byteStringOPadAndHashValueInner, byteStringHashValueOuter);
					// update display variables
					m_str_mac = byteStringHashValueOuter.toString(16, " ");
				}
				break;
	}
	if ( m_position != 4 )
	{
		SetMac(m_str_outer_input);
	}
	UpdateData(false);	
}

CrypTool::Cryptography::Hash::HashAlgorithmType CDlgHMAC::getHashAlgorithmType() const {
	CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType = CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL;
	const int currentSelection = m_comboCtrlSelectHashFunction.GetCurSel();
	if (currentSelection >= 0 && currentSelection < vectorHashAlgorithmTypes.size())
		hashAlgorithmType = vectorHashAlgorithmTypes[currentSelection];
	return hashAlgorithmType;
}

BEGIN_MESSAGE_MAP(CDlgHMAC, CDialog)
	ON_EN_CHANGE(IDC_SHOW_TEXT, OnEditText)
	ON_EN_CHANGE(IDC_EDIT_KEY, OnEditKey)
	ON_EN_CHANGE(IDC_EDIT_ORIGINAL_MESSAGE, OnEditOriginalMessage)
	ON_EN_CHANGE(IDC_EDIT_KEY2, OnEditSecondKey)
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_HASH_FUNCTION, &CDlgHMAC::OnCbnSelendokComboSelectHashFunction)
	ON_CBN_SELENDOK(IDC_COMBO_SELECT_HMAC_ALGORITHM, &CDlgHMAC::OnCbnSelendokComboSelectHmacAlgorithm)
END_MESSAGE_MAP()