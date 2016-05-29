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
#include "DlgCertificateStoreSelectCertificate.h"
#include "DlgCertificateStoreAskForPassword.h"

CDlgCertificateStoreSelectCertificate::CDlgCertificateStoreSelectCertificate(CWnd *_parent) :
	CDialog(CDlgCertificateStoreSelectCertificate::IDD, _parent),
	m_showCertificatesRSA(true),
	m_showCertificatesDSA(true),
	m_showCertificatesECC(true),
	m_selectedCertificateSerial(0) {

}

CDlgCertificateStoreSelectCertificate::~CDlgCertificateStoreSelectCertificate() {

}

void CDlgCertificateStoreSelectCertificate::showCertificateTypes(const bool _rsa, const bool _dsa, const bool _ecc) {
	m_showCertificatesRSA = _rsa;
	m_showCertificatesDSA = _dsa;
	m_showCertificatesECC = _ecc;
}

BOOL CDlgCertificateStoreSelectCertificate::OnInitDialog() {
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
	return TRUE;
}

void CDlgCertificateStoreSelectCertificate::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Control(_pDX, IDC_BUTTON_OK, m_buttonOK);
}

void CDlgCertificateStoreSelectCertificate::changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult) {
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

void CDlgCertificateStoreSelectCertificate::clickedButtonOK() {
	m_selectedCertificateSerial = getSerialOfSelectedCertificate();
	if (m_selectedCertificateSerial > 0) {
		EndDialog(IDOK);
	}
}

void CDlgCertificateStoreSelectCertificate::clickedButtonCancel() {
	EndDialog(IDCANCEL);
}

void CDlgCertificateStoreSelectCertificate::updateListCertificates() {
	// clear the existing contents of the list
	m_listCertificates.DeleteAllItems();
	// acquire certificate serials from the certificate store; the types of user certificates 
	// for which serials are to be fetched depend on status of the check boxes (RSA, DSA, ECC)
	const std::vector<long> vectorUserCertificateSerials = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateSerials(m_showCertificatesRSA, m_showCertificatesDSA, m_showCertificatesECC);
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
	// must be reset, otherwise any operations (like exporting, deleting, etc.) might 
	// point to the wrong certificate; so we manually reset the selection mark, and 
	// then we update the buttons
	m_listCertificates.SetSelectionMark(-1);
	updateButtons();
}

void CDlgCertificateStoreSelectCertificate::updateButtons() {
	// enable/disbale buttons depending on whether a certificate is selected
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	m_buttonOK.EnableWindow(serialOfSelectedCertificate > 0);
}

long CDlgCertificateStoreSelectCertificate::getSerialOfSelectedCertificate() const {
	long serial = 0;
	const int selectedItem = m_listCertificates.GetSelectionMark();
	if (selectedItem != -1) {
		const CString stringSerial = m_listCertificates.GetItemText(selectedItem, 0);
		serial = atol(stringSerial);
	}
	return serial;
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreSelectCertificate, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CERTIFICATES, &CDlgCertificateStoreSelectCertificate::changedSelectionListCertificates)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgCertificateStoreSelectCertificate::clickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreSelectCertificate::clickedButtonCancel)
END_MESSAGE_MAP()
