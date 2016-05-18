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

#ifndef _DLGKEYFROMPASSWORD_H_
#define _DLGKEYFROMPASSWORD_H_

#include "stdafx.h"

class CDlgKeyFromPassword : public CDialog {
	enum { IDD = IDD_KEY_FROM_PASSWORD };
public:
	CDlgKeyFromPassword(CWnd* pParent = NULL);
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	CEdit m_control_zaehler;
	CEdit m_control_dkLen;
	CEdit m_control_schluessel;
	CEdit m_control_passwort;
	CString	m_schluessel;
	CString	m_passwort;
	int m_radio1;
	CString	m_salt;
	CString	m_dkLen;
	CString	m_zaehler;
protected:
	afx_msg void OnBUTTONGenerieren();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnUpdateEdit4();
	afx_msg void OnUpdateEdit5();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBUTTONcancel();
	afx_msg void OnBUTTONUebernehmen();
private:
	void CheckEdit(CString & m_edit, int & sels, int & sele);

	DECLARE_MESSAGE_MAP()
};

#endif
