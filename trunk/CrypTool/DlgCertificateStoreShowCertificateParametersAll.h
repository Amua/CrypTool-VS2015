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

#ifndef _DLGCERTIFICATESTORESHOWCERTIFICATEPARAMETERSALL_H_
#define _DLGCERTIFICATESTORESHOWCERTIFICATEPARAMETERSALL_H_

class CDlgCertificateStoreShowCertificateParametersAll : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_SHOW_CERTIFICATE_PARAMETERS_ALL };
public:
	CDlgCertificateStoreShowCertificateParametersAll(CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreShowCertificateParametersAll();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonClose();
protected:
	CString m_editPublicParameters;
	CString m_editPrivateParameters;
public:
	void setPublicParameters(const CString &_publicParameters) { m_editPublicParameters = _publicParameters; }
	void setPrivateParameters(const CString &_privateParameters) { m_editPrivateParameters = _privateParameters; }

	DECLARE_MESSAGE_MAP()
};

#endif
