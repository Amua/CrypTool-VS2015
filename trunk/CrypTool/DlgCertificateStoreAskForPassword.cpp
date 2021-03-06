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
#include "DlgCertificateStoreAskForPassword.h"

CDlgCertificateStoreAskForPassword::CDlgCertificateStoreAskForPassword(const long _serial, CWnd *_parent) :
	CDialog(CDlgCertificateStoreAskForPassword::IDD, _parent),
	m_editCertificateSerial(""),
	m_editCertificatePassword("") {
	m_editCertificateSerial.Format("%d", _serial);
}

CDlgCertificateStoreAskForPassword::~CDlgCertificateStoreAskForPassword() {

}

BOOL CDlgCertificateStoreAskForPassword::OnInitDialog() {
	CDialog::OnInitDialog();
	return TRUE;
}

void CDlgCertificateStoreAskForPassword::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Text(_pDX, IDC_EDIT_CERTIFICATE_SERIAL, m_editCertificateSerial);
	DDX_Text(_pDX, IDC_EDIT_CERTIFICATE_PASSWORD, m_editCertificatePassword);
}

void CDlgCertificateStoreAskForPassword::clickedButtonOK() {
	UpdateData(true);
	EndDialog(IDOK);
}

void CDlgCertificateStoreAskForPassword::clickedButtonCancel() {
	UpdateData(true);
	EndDialog(IDCANCEL);
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreAskForPassword, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgCertificateStoreAskForPassword::clickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreAskForPassword::clickedButtonCancel)
END_MESSAGE_MAP()