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

#ifndef _DLGCERTIFICATESTORESIGNATURESIGN_H_
#define _DLGCERTIFICATESTORESIGNATURESIGN_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreSignatureSign : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_SIGNATURE_SIGN };
public:
	CDlgCertificateStoreSignatureSign(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreSignatureSign();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonRadioHashFunctionMD5();
	afx_msg void clickedButtonRadioHashFunctionRIPEMD160();
	afx_msg void clickedButtonRadioHashFunctionSHA();
	afx_msg void clickedButtonRadioHashFunctionSHA1();
	afx_msg void clickedButtonRadioRSA();
	afx_msg void clickedButtonRadioDSA();
	afx_msg void clickedButtonRadioECC();
	afx_msg void changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult);
	afx_msg void clickedButtonOK();
	afx_msg void clickedButtonCancel();
protected:
	const CString m_documentFileName;
	const CString m_documentTitle;
protected:
	int m_radioHashFunction;
	int m_radioAsymmetricAlgorithm;
	CListCtrl m_listCertificates;
	CButton m_buttonRadioHashFunctionMD5;
	CButton m_buttonRadioHashFunctionRIPEMD160;
	CButton m_buttonRadioHashFunctionSHA;
	CButton m_buttonRadioHashFunctionSHA1;
	CButton m_buttonRadioRSA;
	CButton m_buttonRadioDSA;
	CButton m_buttonRadioECC;
	CButton m_buttonOK;
	CButton m_buttonCancel;
private:
	void updateListCertificates();
	void updateButtons();
private:
	long getSerialOfSelectedCertificate() const;

	DECLARE_MESSAGE_MAP()
};

#endif
