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

#ifndef _DLGCERTIFICATESDISPLAYOREXPORT_H_
#define _DLGCERTIFICATESDISPLAYOREXPORT_H_

class CDlgCertificatesDisplayOrExport : public CDialog {
	enum { IDD = IDD_CERTIFICATES_DISPLAY_OR_EXPORT };
public:
	CDlgCertificatesDisplayOrExport(CWnd *_parent = 0);
	virtual ~CDlgCertificatesDisplayOrExport();
protected:
	afx_msg void OnBnClickedButtonShowPublicParameters();
	afx_msg void OnBnClickedButtonShowAllParameters();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonExport();

	DECLARE_MESSAGE_MAP()
};

#endif
