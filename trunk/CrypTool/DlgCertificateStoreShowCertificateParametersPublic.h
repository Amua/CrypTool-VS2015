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

#ifndef _DLGCERTIFICATESTORESHOWCERTIFICATEPARAMETERSPUBLIC_H_
#define _DLGCERTIFICATESTORESHOWCERTIFICATEPARAMETERSPUBLIC_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreShowCertificateParametersPublic : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_SHOW_CERTIFICATE_PARAMETERS_PUBLIC };
public:
	CDlgCertificateStoreShowCertificateParametersPublic(CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreShowCertificateParametersPublic();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonClose();
protected:
	CString m_editPublicParameters;
public:
	void setPublicParameters(const CString &_publicParameters) { m_editPublicParameters = _publicParameters; }

	DECLARE_MESSAGE_MAP()
};

#endif
