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

#ifndef _DLGCERTIFICATESTORESELECTCERTIFICATE_H_
#define _DLGCERTIFICATESTORESELECTCERTIFICATE_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreSelectCertificate : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_SELECT_CERTIFICATE };
public:
	CDlgCertificateStoreSelectCertificate(CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreSelectCertificate();
public:
	void showCertificateTypes(const bool _rsa, const bool _dsa, const bool _ecc);
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult);
	afx_msg void clickedButtonOK();
	afx_msg void clickedButtonCancel();
protected:
	CListCtrl m_listCertificates;
	CButton m_buttonOK;
private:
	void updateListCertificates();
	void updateButtons();
private:
	long getSerialOfSelectedCertificate() const;
private:
	bool m_showCertificatesRSA;
	bool m_showCertificatesDSA;
	bool m_showCertificatesECC;
private:
	long m_selectedCertificateSerial;
public:
	long getSelectedCertificateSerial() const { return m_selectedCertificateSerial; }

	DECLARE_MESSAGE_MAP()
};

#endif
