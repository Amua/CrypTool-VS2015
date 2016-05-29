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
#include "DlgCertificateStoreGenerateOrImport.h"

CDlgCertificateStoreGenerateOrImport::CDlgCertificateStoreGenerateOrImport(CWnd *_parent) :
	CDialog(CDlgCertificateStoreGenerateOrImport::IDD, _parent),
	m_radioAlgorithm(0),
	m_editFirstName(""),
	m_editLastName(""),
	m_editRemarks(""),
	m_editPassword1(""),
	m_editPassword2("") {

}

CDlgCertificateStoreGenerateOrImport::~CDlgCertificateStoreGenerateOrImport() {

}

BOOL CDlgCertificateStoreGenerateOrImport::OnInitDialog() {
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
	// initialize combo box (ECC)
	m_comboECC.AddString("prime192v1");
	m_comboECC.AddString("prime192v2");
	m_comboECC.AddString("prime192v3");
	m_comboECC.AddString("prime239v1");
	m_comboECC.AddString("prime239v2");
	m_comboECC.AddString("prime239v3");
	m_comboECC.AddString("prime256v1");
	// set initial combo box values (RSA, DSA, ECC)
	m_comboRSA.SetCurSel(0);
	m_comboDSA.SetCurSel(0);
	m_comboECC.SetCurSel(0);
	// initial update for the combo boxes (only one can be active at any given time)
	updateComboBoxes();
	return TRUE;
}

void CDlgCertificateStoreGenerateOrImport::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Radio(_pDX, IDC_RADIO_RSA, m_radioAlgorithm);
	DDX_Control(_pDX, IDC_COMBO_RSA, m_comboRSA);
	DDX_Control(_pDX, IDC_COMBO_DSA, m_comboDSA);
	DDX_Control(_pDX, IDC_COMBO_ECC, m_comboECC);
	DDX_Text(_pDX, IDC_EDIT_FIRST_NAME, m_editFirstName);
	DDX_Text(_pDX, IDC_EDIT_LAST_NAME, m_editLastName);
	DDX_Text(_pDX, IDC_EDIT_REMARKS, m_editRemarks);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_1, m_editPassword1);
	DDX_Text(_pDX, IDC_EDIT_PASSWORD_2, m_editPassword2);
}

void CDlgCertificateStoreGenerateOrImport::clickedButtonRadioRSA() {
	updateComboBoxes();
}

void CDlgCertificateStoreGenerateOrImport::clickedButtonRadioDSA() {
	updateComboBoxes();
}

void CDlgCertificateStoreGenerateOrImport::clickedButtonRadioECC() {
	updateComboBoxes();
}

void CDlgCertificateStoreGenerateOrImport::clickedButtonCreate() {
	UpdateData(true);
	// make sure all the required user information is there: the first name, the last name, 
	// and the password (where both password fields must be identical); the remarks field 
	// is optional, so the user may leave it empty
	if (m_editFirstName.IsEmpty() || m_editLastName.IsEmpty() || m_editPassword1.IsEmpty() || m_editPassword2.IsEmpty() || m_editPassword1 != m_editPassword2) {
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
		certificateType = CrypTool::Cryptography::Asymmetric::CERTIFICATE_TYPE_ECC;
		m_comboECC.GetLBText(m_comboECC.GetCurSel(), certificateParameters);
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

void CDlgCertificateStoreGenerateOrImport::clickedButtonImport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificateStoreGenerateOrImport::clickedButtonClose() {
	EndDialog(IDOK);
}

void CDlgCertificateStoreGenerateOrImport::updateComboBoxes() {
	UpdateData(true);
	m_comboRSA.EnableWindow(m_radioAlgorithm == 0);
	m_comboDSA.EnableWindow(m_radioAlgorithm == 1);
	m_comboECC.EnableWindow(m_radioAlgorithm == 2);
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreGenerateOrImport, CDialog)
	ON_BN_CLICKED(IDC_RADIO_RSA, &CDlgCertificateStoreGenerateOrImport::clickedButtonRadioRSA)
	ON_BN_CLICKED(IDC_RADIO_DSA, &CDlgCertificateStoreGenerateOrImport::clickedButtonRadioDSA)
	ON_BN_CLICKED(IDC_RADIO_ECC, &CDlgCertificateStoreGenerateOrImport::clickedButtonRadioECC)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CDlgCertificateStoreGenerateOrImport::clickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CDlgCertificateStoreGenerateOrImport::clickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificateStoreGenerateOrImport::clickedButtonClose)
END_MESSAGE_MAP()
