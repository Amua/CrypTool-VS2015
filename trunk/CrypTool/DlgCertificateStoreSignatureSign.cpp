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
#include "DlgCertificateStoreSignatureSign.h"

CDlgCertificateStoreSignatureSign::CDlgCertificateStoreSignatureSign(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent) :
	CDialog(CDlgCertificateStoreSignatureSign::IDD, _parent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle) {

}

CDlgCertificateStoreSignatureSign::~CDlgCertificateStoreSignatureSign() {

}

BOOL CDlgCertificateStoreSignatureSign::OnInitDialog() {
	CDialog::OnInitDialog();
	return TRUE;
}

void CDlgCertificateStoreSignatureSign::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
}

void CDlgCertificateStoreSignatureSign::clickedButtonOK() {
	UpdateData(true);
	EndDialog(IDOK);
}

void CDlgCertificateStoreSignatureSign::clickedButtonCancel() {
	UpdateData(true);
	EndDialog(IDCANCEL);
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreSignatureSign, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgCertificateStoreSignatureSign::clickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreSignatureSign::clickedButtonCancel)
END_MESSAGE_MAP()