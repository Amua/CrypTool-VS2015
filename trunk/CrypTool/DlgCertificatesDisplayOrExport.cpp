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
	CDialog(CDlgCertificatesDisplayOrExport::IDD, _parent) {

}

CDlgCertificatesDisplayOrExport::~CDlgCertificatesDisplayOrExport() {

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
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonCheckDSA() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonCheckEC() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::clickedButtonClose() {
	EndDialog(IDOK);
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