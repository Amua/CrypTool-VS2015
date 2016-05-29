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

#ifndef _DLGCERTIFICATESTOREASKFORPASSWORD_H_
#define _DLGCERTIFICATESTOREASKFORPASSWORD_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreAskForPassword : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_ASK_FOR_PASSWORD };
public:
	CDlgCertificateStoreAskForPassword(const long _serial, CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreAskForPassword();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonOK();
	afx_msg void clickedButtonCancel();
protected:
	CString m_editCertificateSerial;
	CString m_editCertificatePassword;
public:
	const CString getCertificateSerial() const { return m_editCertificateSerial; }
	const CString getCertificatePassword() const { return m_editCertificatePassword; }

	DECLARE_MESSAGE_MAP()
};

#endif
