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
#include "DlgCertificatesDisplayOrExport.h"

CDlgCertificatesDisplayOrExport::CDlgCertificatesDisplayOrExport(CWnd *_parent) :
	CDialog(CDlgCertificatesDisplayOrExport::IDD, _parent),
	m_checkRSA(1),
	m_checkDSA(1),
	m_checkEC(1) {

}

CDlgCertificatesDisplayOrExport::~CDlgCertificatesDisplayOrExport() {

}

BOOL CDlgCertificatesDisplayOrExport::OnInitDialog() {
	CDialog::OnInitDialog();
	// initialize list of certificates
	m_listCertificates.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// add header for first name
	CString headerFirstName;
	headerFirstName.Format("%s", "FIRST NAME");
	m_listCertificates.InsertColumn(0, headerFirstName, LVCFMT_LEFT, 100, 0);
	// add header for last name
	CString headerLastName;
	headerLastName.Format("%s", "LAST NAME");
	m_listCertificates.InsertColumn(1, headerLastName, LVCFMT_LEFT, 100, 1);
	// add header for remarks
	CString headerRemarks;
	headerRemarks.Format("%s", "REMARKS");
	m_listCertificates.InsertColumn(2, headerRemarks, LVCFMT_LEFT, 100, 2);
	// add header for type
	CString headerType;
	headerType.Format("%s", "TYPE");
	m_listCertificates.InsertColumn(3, headerType, LVCFMT_LEFT, 65, 3);
	// add header for serial number
	CString headerSerialNumber;
	headerSerialNumber.Format("%s", "SERIAL NUMBER");
	m_listCertificates.InsertColumn(4, headerSerialNumber, LVCFMT_LEFT, 100, 4);
	// add header for time of creation
	CString headerTimeOfCreation;
	headerTimeOfCreation.Format("%s", "TIME OF CREATION");
	m_listCertificates.InsertColumn(5, headerTimeOfCreation, LVCFMT_LEFT, 100, 5);
	// initial update for the list of certificates
	updateListCertificates();
	return TRUE;
}

void CDlgCertificatesDisplayOrExport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Control(_pDX, IDC_LIST_CERTIFICATES, m_listCertificates);
	DDX_Check(_pDX, IDC_CHECK_RSA, m_checkRSA);
	DDX_Check(_pDX, IDC_CHECK_DSA, m_checkDSA);
	DDX_Check(_pDX, IDC_CHECK_EC, m_checkEC);
}

void CDlgCertificatesDisplayOrExport::clickedButtonShowPublicParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonShowAllParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonDelete() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonExport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonCheckRSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificatesDisplayOrExport::clickedButtonCheckDSA() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificatesDisplayOrExport::clickedButtonCheckEC() {
	UpdateData(true);
	updateListCertificates();
}

void CDlgCertificatesDisplayOrExport::clickedButtonClose() {
	EndDialog(IDOK);
}

void CDlgCertificatesDisplayOrExport::updateListCertificates() {
	// clear the existing contents of the list
	m_listCertificates.DeleteAllItems();

	// TODO/FIXME: insert a dummy item
	const int row = 0;
	m_listCertificates.InsertItem(row, "first");
	m_listCertificates.SetItemText(row, 1, "last");
	m_listCertificates.SetItemText(row, 2, "remarks");
	m_listCertificates.SetItemText(row, 3, "type");
	m_listCertificates.SetItemText(row, 4, "serial");
	m_listCertificates.SetItemText(row, 5, "time");
}

BEGIN_MESSAGE_MAP(CDlgCertificatesDisplayOrExport, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PUBLIC_PARAMETERS, &CDlgCertificatesDisplayOrExport::clickedButtonShowPublicParameters)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ALL_PARAMETERS, &CDlgCertificatesDisplayOrExport::clickedButtonShowAllParameters)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgCertificatesDisplayOrExport::clickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgCertificatesDisplayOrExport::clickedButtonExport)
	ON_BN_CLICKED(IDC_CHECK_RSA, &CDlgCertificatesDisplayOrExport::clickedButtonCheckRSA)
	ON_BN_CLICKED(IDC_CHECK_DSA, &CDlgCertificatesDisplayOrExport::clickedButtonCheckDSA)
	ON_BN_CLICKED(IDC_CHECK_EC, &CDlgCertificatesDisplayOrExport::clickedButtonCheckEC)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificatesDisplayOrExport::clickedButtonClose)
END_MESSAGE_MAP()