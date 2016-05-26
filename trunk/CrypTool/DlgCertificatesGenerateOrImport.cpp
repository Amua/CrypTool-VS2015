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
	CDialog(CDlgCertificatesGenerateOrImport::IDD, _parent) {

}

CDlgCertificatesGenerateOrImport::~CDlgCertificatesGenerateOrImport() {

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
