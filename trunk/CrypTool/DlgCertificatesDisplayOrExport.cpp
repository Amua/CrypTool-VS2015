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

void CDlgCertificatesDisplayOrExport::OnBnClickedButtonShowPublicParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::OnBnClickedButtonShowAllParameters() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::OnBnClickedButtonDelete() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

void CDlgCertificatesDisplayOrExport::OnBnClickedButtonExport() {
	AfxMessageBox("CRYPTOOL_BASE: implement me");
}

BEGIN_MESSAGE_MAP(CDlgCertificatesDisplayOrExport, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PUBLIC_PARAMETERS, &CDlgCertificatesDisplayOrExport::OnBnClickedButtonShowPublicParameters)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ALL_PARAMETERS, &CDlgCertificatesDisplayOrExport::OnBnClickedButtonShowAllParameters)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgCertificatesDisplayOrExport::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgCertificatesDisplayOrExport::OnBnClickedButtonExport)
END_MESSAGE_MAP()