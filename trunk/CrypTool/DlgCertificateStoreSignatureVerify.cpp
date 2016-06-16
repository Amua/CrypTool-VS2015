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
#include "DlgCertificateStoreSignatureVerify.h"

CDlgCertificateStoreSignatureVerify::CDlgCertificateStoreSignatureVerify(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent) :
	CDialog(CDlgCertificateStoreSignatureVerify::IDD, _parent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle),
	m_hashAlgorithmType(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL),
	m_asymmetricAlgorithmType(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_NULL) {

}

CDlgCertificateStoreSignatureVerify::~CDlgCertificateStoreSignatureVerify() {

}

BOOL CDlgCertificateStoreSignatureVerify::OnInitDialog() {
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
	// try to parse specified document as signature file
	if (!CrypTool::Utilities::parseSignatureFile(m_documentFileName, m_serial, m_hashAlgorithmType, m_asymmetricAlgorithmType, m_message, m_signature)) {
		AfxMessageBox("CRYPTOOL_BASE: error parsing signature file");
		EndDialog(IDOK);
		return TRUE;
	}
	// assign internal variables for signer name, hash algorithm name, and asymmetric algorithm name
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringName(m_serial, m_signerName);
	m_hashAlgorithmName = CrypTool::Cryptography::Hash::getHashAlgorithmName(m_hashAlgorithmType);
	m_asymmetricAlgorithmName = CrypTool::Cryptography::Asymmetric::getAsymmetricAlgorithmName(m_asymmetricAlgorithmType);
	// assign internal variable for signature type
	m_signatureType = CrypTool::Cryptography::Signature::getSignatureType(m_asymmetricAlgorithmType, m_hashAlgorithmType);
	if (m_signatureType == CrypTool::Cryptography::Signature::SIGNATURE_TYPE_NULL) {
		AfxMessageBox("CRYPTOOL_BASE: error parsing signature file");
		EndDialog(IDOK);
		return TRUE;
	}
	// initial update for the list of certificates
	updateListCertificates();
	// try to select the certificate corresponding to the signature
	selectCertificate(m_serial);
	// initial update for the buttons
	updateButtons();
	// initial update
	UpdateData(false);
	return TRUE;
}

void CDlgCertificateStoreSignatureVerify::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Text(_pDX, IDC_STATIC_SIGNER, m_signerName);
	DDX_Text(_pDX, IDC_STATIC_HASH_ALGORITHM, m_hashAlgorithmName);
	DDX_Text(_pDX, IDC_STATIC_ASYMMETRIC_ALGORITHM, m_asymmetricAlgorithmName);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Control(_pDX, IDC_BUTTON_OK, m_buttonOK);
	DDX_Control(_pDX, IDC_BUTTON_CANCEL, m_buttonCancel);
}

void CDlgCertificateStoreSignatureVerify::changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult) {
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

void CDlgCertificateStoreSignatureVerify::clickedButtonOK() {
	UpdateData(true);
	EndDialog(IDOK);
	// try to verify the signature
	CrypTool::Cryptography::Signature::OperationVerify operationVerify(m_signatureType);
	const bool result = operationVerify.executeOnByteStrings(m_message, m_signature, m_serial);
	// notify the user
	if (result) {
		AfxMessageBox("CRYPTOOL_BASE: signature verificated SUCCEEDED!");
	}
	else {
		AfxMessageBox("CRYPTOOL_BASE: signature verificated FAILED!");
	}
}

void CDlgCertificateStoreSignatureVerify::clickedButtonCancel() {
	UpdateData(true);
	EndDialog(IDCANCEL);
}

void CDlgCertificateStoreSignatureVerify::updateListCertificates() {
	// clear the existing contents of the list
	m_listCertificates.DeleteAllItems();
	// acquire certificate serials from the certificate store; the types of user certificates 
	// for which serials are to be fetched depend on the data extracted from the signature
	const std::vector<long> vectorUserCertificateSerials = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateSerials(m_asymmetricAlgorithmType == CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, m_asymmetricAlgorithmType == CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_DSA, m_asymmetricAlgorithmType == CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_ECC);
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

void CDlgCertificateStoreSignatureVerify::updateButtons() {
	// enable/disable buttons depending on whether a certificate is selected
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	m_buttonOK.EnableWindow(serialOfSelectedCertificate > 0);
	m_buttonCancel.EnableWindow(true);
}

long CDlgCertificateStoreSignatureVerify::getSerialOfSelectedCertificate() const {
	long serial = 0;
	const int selectedItem = m_listCertificates.GetSelectionMark();
	if (selectedItem != -1) {
		const CString stringSerial = m_listCertificates.GetItemText(selectedItem, 0);
		serial = atol(stringSerial);
	}
	return serial;
}

void CDlgCertificateStoreSignatureVerify::selectCertificate(const long _serial) {
	for (int index = 0; index < m_listCertificates.GetItemCount(); index++) {
		const CString serial = m_listCertificates.GetItemText(index, 0);
		if (atol(serial) == _serial) {
			m_listCertificates.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED);
			m_listCertificates.SetSelectionMark(index);
			return;
		}
	}
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreSignatureVerify, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CERTIFICATES, &CDlgCertificateStoreSignatureVerify::changedSelectionListCertificates)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgCertificateStoreSignatureVerify::clickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreSignatureVerify::clickedButtonCancel)
END_MESSAGE_MAP()

