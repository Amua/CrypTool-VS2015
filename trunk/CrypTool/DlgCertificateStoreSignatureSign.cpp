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
#include "DlgCertificateStoreSignatureSign.h"

#include "DlgCertificateStoreAskForPassword.h"

CDlgCertificateStoreSignatureSign::CDlgCertificateStoreSignatureSign(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent) :
	CDialog(CDlgCertificateStoreSignatureSign::IDD, _parent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle),
	m_radioHashFunction(0),
	m_radioAsymmetricAlgorithm(0) {

}

CDlgCertificateStoreSignatureSign::~CDlgCertificateStoreSignatureSign() {

}

BOOL CDlgCertificateStoreSignatureSign::OnInitDialog() {
	CDialog::OnInitDialog();
	// initialize list of certificates
	m_listCertificates.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// initialize headers
	CString header;
	header.Format("%s", "SERIAL");
	m_listCertificates.InsertColumn(0, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "FIRSTNAME");
	m_listCertificates.InsertColumn(1, header, LVCFMT_LEFT, 95, 0);
	header.Format("%s", "LASTNAME");
	m_listCertificates.InsertColumn(2, header, LVCFMT_LEFT, 95, 0);
	header.Format("%s", "REMARKS");
	m_listCertificates.InsertColumn(3, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "TYPE");
	m_listCertificates.InsertColumn(4, header, LVCFMT_LEFT, 85, 0);
	header.Format("%s", "NOTBEFORE");
	m_listCertificates.InsertColumn(5, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "NOTAFTER");
	m_listCertificates.InsertColumn(6, header, LVCFMT_LEFT, 75, 0);
	// initial update for the list of certificates
	updateListCertificates();
	// initial update for the buttons
	updateButtons();
	// initial update
	UpdateData(false);
	return TRUE;
}

void CDlgCertificateStoreSignatureSign::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Radio(_pDX, IDC_RADIO_HASH_FUNCTION_MD5, m_radioHashFunction);
	DDX_Radio(_pDX, IDC_RADIO_RSA, m_radioAsymmetricAlgorithm);
	DDX_Control(_pDX, IDC_RADIO_HASH_FUNCTION_MD5, m_buttonRadioHashFunctionMD5);
	DDX_Control(_pDX, IDC_RADIO_HASH_FUNCTION_RIPEMD160, m_buttonRadioHashFunctionRIPEMD160);
	DDX_Control(_pDX, IDC_RADIO_HASH_FUNCTION_SHA, m_buttonRadioHashFunctionSHA);
	DDX_Control(_pDX, IDC_RADIO_HASH_FUNCTION_SHA1, m_buttonRadioHashFunctionSHA1);
	DDX_Control(_pDX, IDC_RADIO_RSA, m_buttonRadioRSA);
	DDX_Control(_pDX, IDC_RADIO_DSA, m_buttonRadioDSA);
	DDX_Control(_pDX, IDC_RADIO_ECC, m_buttonRadioECC);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Control(_pDX, IDC_BUTTON_OK, m_buttonOK);
	DDX_Control(_pDX, IDC_BUTTON_CANCEL, m_buttonCancel);
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionMD5() {
	// don't do anything here
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionRIPEMD160() {
	// don't do anything here
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionSHA() {
	// don't do anything here
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionSHA1() {
	// don't do anything here
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioRSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioDSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreSignatureSign::clickedButtonRadioECC() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreSignatureSign::changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult) {
	// for some reason the selection mark of the list doesn't change if the user 
	// deselects an item by clicking somewhere else-- therefore we have to do 
	// this manually, and then we can invoke the "updateButtons" method as usual
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)(_pNMHDR);
	if (pNMListView->uOldState & LVIS_FOCUSED || pNMListView->uOldState & LVIS_SELECTED) {
		m_listCertificates.SetSelectionMark(-1);
	}
	// whenever the selection changes, we need to update the buttons
	updateButtons();
}

void CDlgCertificateStoreSignatureSign::clickedButtonOK() {
	UpdateData(true);
	// acquire serial of selected certificate
	const long serial = getSerialOfSelectedCertificate();
	// acquire hash function type and asymmetric algorithm type
	const CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType = m_radioHashFunction == 0 ? CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD5 : m_radioHashFunction == 1 ? CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_RIPEMD160 : m_radioHashFunction == 2 ? CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA : m_radioHashFunction == 3 ? CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA1 : CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL;
	const CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType = m_radioAsymmetricAlgorithm == 0 ? CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA : m_radioAsymmetricAlgorithm == 1 ? CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_DSA : m_radioAsymmetricAlgorithm == 2 ? CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_ECC : CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_NULL;
	// acquire the signature type
	const CrypTool::Cryptography::Signature::SignatureType signatureType = CrypTool::Cryptography::Signature::getSignatureType(asymmetricAlgorithmType, hashAlgorithmType);
	// make sure the signature type is valid
	if (signatureType == CrypTool::Cryptography::Signature::SIGNATURE_TYPE_NULL) {
		AfxMessageBox("CRYPTOOL_BASE: invalid signature type");
		return;
	}
	// ask the user for the password of the private key
	CDlgCertificateStoreAskForPassword dlgCertificateStoreAskForPassword(serial);
	if (dlgCertificateStoreAskForPassword.DoModal() != IDOK) {
		return;
	}
	// read document into byte string
	CrypTool::ByteString message;
	if (!message.readFromFile(m_documentFileName)) {
		return;
	}
	// create signature using the parameters specified through the GUI
	CrypTool::ByteString signature;
	CrypTool::Cryptography::Signature::OperationSign operationSign(signatureType);
	if (!operationSign.executeOnByteStrings(message, signature, serial, dlgCertificateStoreAskForPassword.getCertificatePassword())) {
		AfxMessageBox("CRYPTOOL_BASE: signature failed");
		return;
	}
	// create a name for the signature file
	const CString signatureFileName = CrypTool::Utilities::createTemporaryFile(".hex");
	// try to write the signature file
	if (!CrypTool::Utilities::createSignatureFile(signatureFileName, serial, hashAlgorithmType, asymmetricAlgorithmType, message, signature)) {
		AfxMessageBox("CRYPTOOL_BASE: signature file failed");
		return;
	}
	// open the signature file in new document
	CAppDocument *document = theApp.OpenDocumentFileNoMRU(signatureFileName);
	if (document) {
		// create a meaningful title
		const CString signatureName = CrypTool::Cryptography::Signature::getSignatureName(signatureType);
		CString title;
		title.Format(IDS_STRING_ASYMKEY_SIGNATURE_OF, signatureName, m_documentTitle);
		document->SetTitle(title);
	}
	EndDialog(IDOK);
}

void CDlgCertificateStoreSignatureSign::clickedButtonCancel() {
	UpdateData(true);
	EndDialog(IDCANCEL);
}

void CDlgCertificateStoreSignatureSign::updateListCertificates() {
	// clear the existing contents of the list
	m_listCertificates.DeleteAllItems();
	// acquire certificate serials from the certificate store; the types of user certificates 
	// for which serials are to be fetched depend on status of the check boxes (RSA, DSA, ECC)
	const std::vector<long> vectorUserCertificateSerials = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateSerials(m_radioAsymmetricAlgorithm == 0, m_radioAsymmetricAlgorithm == 1, m_radioAsymmetricAlgorithm == 2);
	// now that we have the serials for all user certificates we're interested in, we 
	// can go through all the serials and fill the certificate list with some information
	CString stringSerial;
	CString stringFirstName;
	CString stringLastName;
	CString stringRemarks;
	CString stringType;
	CString stringNotBefore;
	CString stringNotAfter;
	for (size_t indexSerial = 0; indexSerial < vectorUserCertificateSerials.size(); indexSerial++) {
		const long serial = vectorUserCertificateSerials[indexSerial];
		stringSerial.Format("%d", serial);
		if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateInformation(serial, stringFirstName, stringLastName, stringRemarks, stringType, stringNotBefore, stringNotAfter)) {
			const int row = m_listCertificates.GetItemCount();
			m_listCertificates.InsertItem(row, stringSerial);
			m_listCertificates.SetItemText(row, 1, stringFirstName);
			m_listCertificates.SetItemText(row, 2, stringLastName);
			m_listCertificates.SetItemText(row, 3, stringRemarks);
			m_listCertificates.SetItemText(row, 4, stringType);
			m_listCertificates.SetItemText(row, 5, stringNotBefore);
			m_listCertificates.SetItemText(row, 6, stringNotAfter);
		}
	}
	// very important: after the list has been updated, naturally the user selection 
	// must be reset, otherwise any operations might point to the wrong certificate; 
	// so we manually reset the selection mark, and then we update the buttons
	m_listCertificates.SetSelectionMark(-1);
	updateButtons();
}

void CDlgCertificateStoreSignatureSign::updateButtons() {
	// enable/disable buttons depending on the selected asymmetric algorithm
	m_buttonRadioHashFunctionMD5.EnableWindow(m_radioAsymmetricAlgorithm == 0);
	m_buttonRadioHashFunctionRIPEMD160.EnableWindow(m_radioAsymmetricAlgorithm == 0 || m_radioAsymmetricAlgorithm == 2);
	m_buttonRadioHashFunctionSHA.EnableWindow(m_radioAsymmetricAlgorithm == 0 || m_radioAsymmetricAlgorithm == 1);
	m_buttonRadioHashFunctionSHA1.EnableWindow(m_radioAsymmetricAlgorithm == 0 || m_radioAsymmetricAlgorithm == 1 || m_radioAsymmetricAlgorithm == 2);
	// enable/disable buttons
	m_buttonRadioRSA.EnableWindow(true);
	m_buttonRadioDSA.EnableWindow(true);
	m_buttonRadioECC.EnableWindow(true);
	// enable/disable buttons depending on whether a certificate is selected
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	m_buttonOK.EnableWindow(serialOfSelectedCertificate > 0);
	m_buttonCancel.EnableWindow(true);
	// override hash function selection depending on selected asymmetric algorithm (DSA)
	if (m_radioAsymmetricAlgorithm == 1) {
		if (m_radioHashFunction != 2 && m_radioHashFunction != 3) {
			m_radioHashFunction = 2;
			UpdateData(false);
		}
	}
	// override hash function selection depending on selected asymmetric algorithm (ECC)
	if (m_radioAsymmetricAlgorithm == 2) {
		if (m_radioHashFunction != 1 && m_radioHashFunction != 3) {
			m_radioHashFunction = 1;
			UpdateData(false);
		}
	}
}

long CDlgCertificateStoreSignatureSign::getSerialOfSelectedCertificate() const {
	long serial = 0;
	const int selectedItem = m_listCertificates.GetSelectionMark();
	if (selectedItem != -1) {
		const CString stringSerial = m_listCertificates.GetItemText(selectedItem, 0);
		serial = atol(stringSerial);
	}
	return serial;
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreSignatureSign, CDialog)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_MD5, &CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionMD5)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_RIPEMD160, &CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionRIPEMD160)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA, &CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionSHA)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA1, &CDlgCertificateStoreSignatureSign::clickedButtonRadioHashFunctionSHA1)
	ON_BN_CLICKED(IDC_RADIO_RSA, &CDlgCertificateStoreSignatureSign::clickedButtonRadioRSA)
	ON_BN_CLICKED(IDC_RADIO_DSA, &CDlgCertificateStoreSignatureSign::clickedButtonRadioDSA)
	ON_BN_CLICKED(IDC_RADIO_ECC, &CDlgCertificateStoreSignatureSign::clickedButtonRadioECC)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CERTIFICATES, &CDlgCertificateStoreSignatureSign::changedSelectionListCertificates)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgCertificateStoreSignatureSign::clickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreSignatureSign::clickedButtonCancel)
END_MESSAGE_MAP()