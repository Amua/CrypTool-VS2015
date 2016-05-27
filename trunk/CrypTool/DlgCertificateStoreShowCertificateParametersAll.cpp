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
#include "DlgCertificateStoreShowCertificateParametersAll.h"

CDlgCertificateStoreShowCertificateParametersAll::CDlgCertificateStoreShowCertificateParametersAll(CWnd *_parent) :
	CDialog(CDlgCertificateStoreShowCertificateParametersAll::IDD, _parent),
	m_editPublicParameters(""),
	m_editPrivateParameters("") {

}

CDlgCertificateStoreShowCertificateParametersAll::~CDlgCertificateStoreShowCertificateParametersAll() {

}

BOOL CDlgCertificateStoreShowCertificateParametersAll::OnInitDialog() {
	CDialog::OnInitDialog();
	return TRUE;
}

void CDlgCertificateStoreShowCertificateParametersAll::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Text(_pDX, IDC_EDIT_PUBLIC_PARAMETERS, m_editPublicParameters);
	DDX_Text(_pDX, IDC_EDIT_PRIVATE_PARAMETERS, m_editPrivateParameters);
}

void CDlgCertificateStoreShowCertificateParametersAll::clickedButtonClose() {
	EndDialog(IDOK);
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreShowCertificateParametersAll, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgCertificateStoreShowCertificateParametersAll::clickedButtonClose)
END_MESSAGE_MAP()
