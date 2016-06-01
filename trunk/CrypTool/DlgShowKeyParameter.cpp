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
#include "DlgShowKeyParameter.h"

CDlgShowKeyParameter::CDlgShowKeyParameter(const long _serial, CWnd *_parent) :
	CDialog(CDlgShowKeyParameter::IDD, _parent),
	m_exponent(""),
	m_modul(""),
	m_radio(1),
	m_serial(_serial) {

}

CDlgShowKeyParameter::~CDlgShowKeyParameter() {

}

BOOL CDlgShowKeyParameter::OnInitDialog() {
	CDialog::OnInitDialog();
	// set dialog title depending on the certificate serial
	CString title;
	title.Format(IDS_STRING_HYBRID_ENC_PUBLIC_KEY_OF);
	CString ownerName = "?";
	if (CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringName(m_serial, ownerName)) {
		title.Append(ownerName);
	}
	SetWindowText(title);
	// initial update
	OnUpdate();
	return TRUE;
}

void CDlgShowKeyParameter::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXPONENT, m_exponent);
	DDX_Text(pDX, IDC_EDIT_MODUL, m_modul);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
}

void CDlgShowKeyParameter::OnUpdate() {
	UpdateData(TRUE);
	// update exponent and modul depending on the chosen representation (base8, base10, base16)
	unsigned int base = 0;
	if (m_radio == 0) base = 8;
	if (m_radio == 1) base = 10;
	if (m_radio == 2) base = 16;
	// acquire both exponent e and modul n
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPublicKeyE(m_serial, base, m_exponent);
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringRSAPublicKeyN(m_serial, base, m_modul);
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CDlgShowKeyParameter, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO2, OnUpdate)
	ON_BN_CLICKED(IDC_RADIO3, OnUpdate)
END_MESSAGE_MAP()
