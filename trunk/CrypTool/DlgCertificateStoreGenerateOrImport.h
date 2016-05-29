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

#ifndef _DLGCERTIFICATESTOREGENERATEORIMPORT_H_
#define _DLGCERTIFICATESTOREGENERATEORIMPORT_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreGenerateOrImport : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_GENERATE_OR_IMPORT };
public:
	CDlgCertificateStoreGenerateOrImport(CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreGenerateOrImport();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonRadioRSA();
	afx_msg void clickedButtonRadioDSA();
	afx_msg void clickedButtonRadioECC();
	afx_msg void clickedButtonCreate();
	afx_msg void clickedButtonImport();
	afx_msg void clickedButtonClose();
protected:
	int m_radioAlgorithm;
	CComboBox m_comboRSA;
	CComboBox m_comboDSA;
	CComboBox m_comboECC;
	CString m_editFirstName;
	CString m_editLastName;
	CString m_editRemarks;
	CString m_editPassword1;
	CString m_editPassword2;
private:
	void updateComboBoxes();

	DECLARE_MESSAGE_MAP()
};

#endif
