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
	// initialize combo box (RSA)
	m_comboRSA.AddString("512");
	m_comboRSA.AddString("768");
	m_comboRSA.AddString("1024");
	m_comboRSA.AddString("2048");
	m_comboRSA.AddString("4096");
	// initialize combo box (DSA)
	m_comboDSA.AddString("512");
	m_comboDSA.AddString("768");
	m_comboDSA.AddString("1024");
	m_comboDSA.AddString("2048");
	m_comboDSA.AddString("4096");
	// initialize combo box (EC)
	m_comboEC.AddString("prime192v1");
	m_comboEC.AddString("prime192v2");
	m_comboEC.AddString("prime192v3");
	m_comboEC.AddString("prime239v1");
	m_comboEC.AddString("prime239v2");
	m_comboEC.AddString("prime239v3");
	m_comboEC.AddString("prime256v1");
	// set initial combo box values (RSA, DSA, EC)
	m_comboRSA.SetCurSel(0);
	m_comboDSA.SetCurSel(0);
	m_comboEC.SetCurSel(0);
	// initial update for the combo boxes (only one can be active at any given time)
	updateComboBoxes();
	return TRUE;
}

void CDlgCertificatesGenerateOrImport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Radio(_pDX, IDC_RADIO_RSA, m_radioAlgorithm);
	DDX_Control(_pDX, IDC_COMBO_RSA, m_comboRSA);
	DDX_Control(_pDX, IDC_COMBO_DSA, m_comboDSA);
	DDX_Control(_pDX, IDC_COMBO_EC, m_comboEC);
	DDX_Text(_pDX, IDC_EDIT_FIRST_NAME, m_editFirstName);
	DDX_Text(_pDX, IDC_EDIT_LAST_NAME, m_editLastName);
	DDX_Text(_pDX, IDC_EDIT_REMARKS, m_editRemarks);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_1, m_editPassword1);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_2, m_editPassword2);
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioRSA() {
	updateComboBoxes();
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioDSA() {
	updateComboBoxes();
}

void CDlgCertificatesGenerateOrImport::clickedButtonRadioEC() {
	updateComboBoxes();
}

void CDlgCertificatesGenerateOrImport::clickedButtonCreate() {
	UpdateData(true);
	// make sure all the required user information is there: the first name, the last name, 
	// the remarks, and the password (where both password fields must be identical)
	if (m_editFirstName.IsEmpty() || m_editLastName.IsEmpty() || m_editRemarks.IsEmpty() || m_editPassword1.IsEmpty() || m_editPassword2.IsEmpty() || m_editPassword1 != m_editPassword2) {
		AfxMessageBox("CRYPTOOL_BASE: supply user information");
		return;
	}
	// acquire desired certificate type and certificate parameters through current state 
	// of the corresponding radio buttons and combo boxes
	CrypTool::Cryptography::Asymmetric::CertificateType certificateType = CrypTool::Cryptography::Asymmetric::CERTIFICATE_TYPE_NULL;
	CString certificateParameters;
	if (m_radioAlgorithm == 0) {
		certificateType = CrypTool::Cryptography::Asymmetric::CERTIFICATE_TYPE_RSA;
		m_comboRSA.GetLBText(m_comboRSA.GetCurSel(), certificateParameters);
	}
	if (m_radioAlgorithm == 1) {
		certificateType = CrypTool::Cryptography::Asymmetric::CERTIFICATE_TYPE_DSA;
		m_comboDSA.GetLBText(m_comboDSA.GetCurSel(), certificateParameters);
	}
	if (m_radioAlgorithm == 2) {
		certificateType = CrypTool::Cryptography::Asymmetric::CERTIFICATE_TYPE_EC;
		m_comboEC.GetLBText(m_comboEC.GetCurSel(), certificateParameters);
	}
	// try to create the user certificate
	SHOW_HOUR_GLASS
	const bool result = CrypTool::Cryptography::Asymmetric::CertificateStore::instance().createUserCertificate(certificateType, certificateParameters, m_editFirstName, m_editLastName, m_editRemarks, m_editPassword1);
	HIDE_HOUR_GLASS
	// notify user about result of creation
	if(result) {
		AfxMessageBox("CRYPTOOL_BASE: user certificate was created");
	}
	else {
		AfxMessageBox("CRYPTOOL_BASE: user certificate was NOT created");
	}
}

void CDlgCertificatesGenerateOrImport::clickedButtonImport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesGenerateOrImport::clickedButtonClose() {
	EndDialog(IDOK);
}

void CDlgCertificatesGenerateOrImport::updateComboBoxes() {
	UpdateData(true);
	m_comboRSA.EnableWindow(m_radioAlgorithm == 0);
	m_comboDSA.EnableWindow(m_radioAlgorithm == 1);
	m_comboEC.EnableWindow(m_radioAlgorithm == 2);
}

BEGIN_MESSAGE_MAP(CDlgCertificatesGenerateOrImport, CDialog)
	ON_BN_CLICKED(IDC_RADIO_RSA, &CDlgCertificatesGenerateOrImport::clickedButtonRadioRSA)
	ON_BN_CLICKED(IDC_RADIO_DSA, &CDlgCertificatesGenerateOrImport::clickedButtonRadioDSA)
	ON_BN_CLICKED(IDC_RADIO_EC, &CDlgCertificatesGenerateOrImport::clickedButtonRadioEC)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CDlgCertificatesGenerateOrImport::clickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgCertificatesGenerateOrImport::clickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificatesGenerateOrImport::clickedButtonClose)
END_MESSAGE_MAP()
