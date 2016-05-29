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
#include "DlgCertificateStoreDisplayOrExport.h"
#include "DlgCertificateStoreAskForPassword.h"
#include "DlgCertificateStoreShowCertificateParametersAll.h"
#include "DlgCertificateStoreShowCertificateParametersPublic.h"

CDlgCertificateStoreDisplayOrExport::CDlgCertificateStoreDisplayOrExport(CWnd *_parent) :
	CDialog(CDlgCertificateStoreDisplayOrExport::IDD, _parent),
	m_checkRSA(1),
	m_checkDSA(1),
	m_checkECC(1) {

}

CDlgCertificateStoreDisplayOrExport::~CDlgCertificateStoreDisplayOrExport() {

}

BOOL CDlgCertificateStoreDisplayOrExport::OnInitDialog() {
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

void CDlgCertificateStoreDisplayOrExport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Control(_pDX, IDC_BUTTON_SHOW_PUBLIC_PARAMETERS, m_buttonShowPublicParameters);
	DDX_Control(_pDX, IDC_BUTTON_SHOW_ALL_PARAMETERS, m_buttonShowAllParameters);
	DDX_Control(_pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(_pDX, IDC_BUTTON_EXPORT, m_buttonExport);
	DDX_Check(_pDX, IDC_CHECK_RSA, m_checkRSA);
	DDX_Check(_pDX, IDC_CHECK_DSA, m_checkDSA);
	DDX_Check(_pDX, IDC_CHECK_ECC, m_checkECC);
}

void CDlgCertificateStoreDisplayOrExport::changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult) {
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

void CDlgCertificateStoreDisplayOrExport::clickedButtonShowPublicParameters() {
	// acquire the serial of the selected certificate
	const long serial = getSerialOfSelectedCertificate();
	if (!serial) {
		return;
	}
	// try to acquire the public parameters
	CString publicParameters;
	if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificatePublicParameters(serial, publicParameters)) {
		AfxMessageBox("CRYPTOOL_BASE: public certificate parameters could NOT be retrieved");
		return;
	}
	// show the public parameters
	CDlgCertificateStoreShowCertificateParametersPublic dlgCertificateStoreShowCertificateParametersPublic;
	dlgCertificateStoreShowCertificateParametersPublic.setPublicParameters(publicParameters);
	dlgCertificateStoreShowCertificateParametersPublic.DoModal();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonShowAllParameters() {
	// acquire the serial of the selected certificate
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	if (!serialOfSelectedCertificate) return;
	// ask the user for a password to access private parameters
	CDlgCertificateStoreAskForPassword dlgCertificateStoreAskForPassword(serialOfSelectedCertificate);
	if (dlgCertificateStoreAskForPassword.DoModal() != IDOK) return;
	// try to acquire the public parameters
	CString publicParameters;
	if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificatePublicParameters(serialOfSelectedCertificate, publicParameters)) {
		AfxMessageBox("CRYPTOOL_BASE: public certificate parameters could NOT be retrieved");
		return;
	}
	// try to acquire the private parameters
	CString privateParameters;
	if (!CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificatePrivateParameters(serialOfSelectedCertificate, dlgCertificateStoreAskForPassword.getCertificatePassword(), privateParameters)) {
		AfxMessageBox("CRYPTOOL_BASE: private certificate parameters could NOT be retrieved");
		return;
	}
	// show the public parameters and the private parameters
	CDlgCertificateStoreShowCertificateParametersAll dlgCertificateStoreShowCertificateParametersAll;
	dlgCertificateStoreShowCertificateParametersAll.setPublicParameters(publicParameters);
	dlgCertificateStoreShowCertificateParametersAll.setPrivateParameters(privateParameters);
	dlgCertificateStoreShowCertificateParametersAll.DoModal();
	// don't forget to update the buttons
	updateButtons();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonDelete() {
	// acquire the serial of the selected certificate
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	if (!serialOfSelectedCertificate) return;
	// try to delete the selected certificate
	CDlgCertificateStoreAskForPassword dlgCertificateStoreAskForPassword(serialOfSelectedCertificate);
	if (dlgCertificateStoreAskForPassword.DoModal() == IDOK) {
		if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().deleteUserCertificate(serialOfSelectedCertificate, dlgCertificateStoreAskForPassword.getCertificatePassword())) {
			AfxMessageBox("CRYPTOOL_BASE: the selected certificate was deleted");
			updateListCertificates();
		}
		else {
			AfxMessageBox("CRYPTOOL_BASE: the selected certificate was NOT deleted");
		}
	}
	// don't forget to update the buttons
	updateButtons();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonExport() {
	// TODO/FIXME
	AfxMessageBox("CRYPTOOL_BASE: implement me");

	// don't forget to update the buttons
	updateButtons();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckRSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckDSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckECC() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonClose() {
	EndDialog(IDOK);
}

void CDlgCertificateStoreDisplayOrExport::updateListCertificates() {
	// clear the existing contents of the list
	m_listCertificates.DeleteAllItems();
	// acquire certificate serials from the certificate store; the types of user certificates 
	// for which serials are to be fetched depend on status of the check boxes (RSA, DSA, ECC)
	const std::vector<long> vectorUserCertificateSerials = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateSerials(m_checkRSA == 1, m_checkDSA == 1, m_checkECC == 1);
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

void CDlgCertificateStoreDisplayOrExport::updateButtons() {
	// enable/disbale buttons depending on whether a certificate is selected
	const long serialOfSelectedCertificate = getSerialOfSelectedCertificate();
	m_buttonShowPublicParameters.EnableWindow(serialOfSelectedCertificate > 0);
	m_buttonShowAllParameters.EnableWindow(serialOfSelectedCertificate > 0);
	m_buttonDelete.EnableWindow(serialOfSelectedCertificate > 0);
	m_buttonExport.EnableWindow(serialOfSelectedCertificate > 0);
}

long CDlgCertificateStoreDisplayOrExport::getSerialOfSelectedCertificate() const {
	long serial = 0;
	const int selectedItem = m_listCertificates.GetSelectionMark();
	if (selectedItem != -1) {
		const CString stringSerial = m_listCertificates.GetItemText(selectedItem, 0);
		serial = atol(stringSerial);
	}
	return serial;
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreDisplayOrExport, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CERTIFICATES, &CDlgCertificateStoreDisplayOrExport::changedSelectionListCertificates)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PUBLIC_PARAMETERS, &CDlgCertificateStoreDisplayOrExport::clickedButtonShowPublicParameters)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ALL_PARAMETERS, &CDlgCertificateStoreDisplayOrExport::clickedButtonShowAllParameters)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgCertificateStoreDisplayOrExport::clickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgCertificateStoreDisplayOrExport::clickedButtonExport)
	ON_BN_CLICKED(IDC_CHECK_RSA, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckRSA)
	ON_BN_CLICKED(IDC_CHECK_DSA, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckDSA)
	ON_BN_CLICKED(IDC_CHECK_ECC, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckECC)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificateStoreDisplayOrExport::clickedButtonClose)
END_MESSAGE_MAP()
