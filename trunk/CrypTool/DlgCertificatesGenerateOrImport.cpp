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
#include "DlgCertificatesGenerateOrImport.h"

CDlgCertificatesGenerateOrImport::CDlgCertificatesGenerateOrImport(CWnd *_parent) :
	CDialog(CDlgCertificatesGenerateOrImport::IDD, _parent),
	m_radioAlgorithm(0),
	m_comboRSA(""),
	m_comboDSA(""),
	m_comboEC(""),
	m_editFirstName(""),
	m_editLastName(""),
	m_editRemarks(""),
	m_editPassword1(""),
	m_editPassword2("") {

}

CDlgCertificatesGenerateOrImport::~CDlgCertificatesGenerateOrImport() {

}

BOOL CDlgCertificatesGenerateOrImport::OnInitDialog() {
	CDialog::OnInitDialog();
	// TODO/FIXME
	return TRUE;
}

void CDlgCertificatesGenerateOrImport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Radio(_pDX, IDC_RADIO_RSA, m_radioAlgorithm);
	DDX_CBString(_pDX, IDC_COMBO_RSA, m_comboRSA);
	DDX_CBString(_pDX, IDC_COMBO_DSA, m_comboDSA);
	DDX_CBString(_pDX, IDC_COMBO_EC, m_comboEC);
	DDX_Text(_pDX, IDC_EDIT_FIRST_NAME, m_editFirstName);
	DDX_Text(_pDX, IDC_EDIT_LAST_NAME, m_editLastName);
	DDX_Text(_pDX, IDC_EDIT_REMARKS, m_editRemarks);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_1, m_editPassword1);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_2, m_editPassword2);
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioRSA() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioDSA() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioEC() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesGenerateOrImport::clickedButtonCreate() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}


void CDlgCertificatesGenerateOrImport::clickedButtonImport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}


void CDlgCertificatesGenerateOrImport::clickedButtonClose() {
	EndDialog(IDOK);
}

BEGIN_MESSAGE_MAP(CDlgCertificatesGenerateOrImport, CDialog)
	ON_BN_CLICKED(IDC_RADIO_RSA, &CDlgCertificatesGenerateOrImport::clickedButtonRadioRSA)
	ON_BN_CLICKED(IDC_RADIO_DSA, &CDlgCertificatesGenerateOrImport::clickedButtonRadioDSA)
	ON_BN_CLICKED(IDC_RADIO_EC, &CDlgCertificatesGenerateOrImport::clickedButtonRadioEC)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CDlgCertificatesGenerateOrImport::clickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgCertificatesGenerateOrImport::clickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificatesGenerateOrImport::clickedButtonClose)
END_MESSAGE_MAP()
