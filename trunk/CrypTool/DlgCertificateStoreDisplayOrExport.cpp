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

CDlgCertificateStoreDisplayOrExport::CDlgCertificateStoreDisplayOrExport(CWnd *_parent) :
	CDialog(CDlgCertificateStoreDisplayOrExport::IDD, _parent),
	m_checkRSA(1),
	m_checkDSA(1),
	m_checkEC(1) {

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
	m_listCertificates.InsertColumn(1, header, LVCFMT_LEFT, 100, 0);
	header.Format("%s", "LASTNAME");
	m_listCertificates.InsertColumn(2, header, LVCFMT_LEFT, 100, 0);
	header.Format("%s", "REMARKS");
	m_listCertificates.InsertColumn(3, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "TYPE");
	m_listCertificates.InsertColumn(4, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "VALIDFROM");
	m_listCertificates.InsertColumn(5, header, LVCFMT_LEFT, 75, 0);
	header.Format("%s", "VALIDTO");
	m_listCertificates.InsertColumn(6, header, LVCFMT_LEFT, 75, 0);
	// initial update for the list of certificates
	updateListCertificates();
	return TRUE;
}

void CDlgCertificateStoreDisplayOrExport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Check(_pDX, IDC_CHECK_RSA, m_checkRSA);
	DDX_Check(_pDX, IDC_CHECK_DSA, m_checkDSA);
	DDX_Check(_pDX, IDC_CHECK_EC, m_checkEC);
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonShowPublicParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonShowAllParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonDelete() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonExport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckRSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckDSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificateStoreDisplayOrExport::clickedButtonCheckEC() {
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
	// for which serials are to be fetched depend on status of the check boxes (RSA, DSA, EC)
	const std::vector<long> vectorUserCertificateSerials = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateSerials(m_checkRSA == 1, m_checkDSA == 1, m_checkEC == 1);
	// now that we have the serials for all user certificates we're interested in, we 
	// can go through all the serials and fill the certificate list with some information
	CString stringSerial;
	CString stringFirstName;
	CString stringLastName;
	CString stringRemarks;
	CString stringType;
	CString stringValidFrom;
	CString stringValidTo;
	for (size_t indexSerial = 0; indexSerial < vectorUserCertificateSerials.size(); indexSerial++) {
		const long serial = vectorUserCertificateSerials[indexSerial];
		stringSerial.Format("%d", serial);
		if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateInformation(serial, stringFirstName, stringLastName, stringRemarks, stringType, stringValidFrom, stringValidTo)) {
			const int row = m_listCertificates.GetItemCount();
			m_listCertificates.InsertItem(row, stringSerial);
			m_listCertificates.SetItemText(row, 1, stringFirstName);
			m_listCertificates.SetItemText(row, 2, stringLastName);
			m_listCertificates.SetItemText(row, 3, stringRemarks);
			m_listCertificates.SetItemText(row, 4, stringType);
			m_listCertificates.SetItemText(row, 5, stringValidFrom);
			m_listCertificates.SetItemText(row, 6, stringValidTo);
		}
	}
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreDisplayOrExport, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PUBLIC_PARAMETERS, &CDlgCertificateStoreDisplayOrExport::clickedButtonShowPublicParameters)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ALL_PARAMETERS, &CDlgCertificateStoreDisplayOrExport::clickedButtonShowAllParameters)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgCertificateStoreDisplayOrExport::clickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgCertificateStoreDisplayOrExport::clickedButtonExport)
	ON_BN_CLICKED(IDC_CHECK_RSA, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckRSA)
	ON_BN_CLICKED(IDC_CHECK_DSA, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckDSA)
	ON_BN_CLICKED(IDC_CHECK_EC, &CDlgCertificateStoreDisplayOrExport::clickedButtonCheckEC)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificateStoreDisplayOrExport::clickedButtonClose)
END_MESSAGE_MAP()