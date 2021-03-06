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

#ifndef _DLGCERTIFICATESTOREDISPLAYOREXPORT_H_
#define _DLGCERTIFICATESTOREDISPLAYOREXPORT_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreDisplayOrExport : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_DISPLAY_OR_EXPORT };
public:
	CDlgCertificateStoreDisplayOrExport(CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreDisplayOrExport();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void changedSelectionListCertificates(NMHDR *_pNMHDR, LRESULT *_pResult);
	afx_msg void clickedButtonShowPublicParameters();
	afx_msg void clickedButtonShowAllParameters();
	afx_msg void clickedButtonDelete();
	afx_msg void clickedButtonExport();
	afx_msg void clickedButtonCheckRSA();
	afx_msg void clickedButtonCheckDSA();
	afx_msg void clickedButtonCheckECC();
	afx_msg void clickedButtonClose();
protected:
	CListCtrl m_listCertificates;
	CButton m_buttonShowPublicParameters;
	CButton m_buttonShowAllParameters;
	CButton m_buttonDelete;
	CButton m_buttonExport;
	int m_checkRSA;
	int m_checkDSA;
	int m_checkECC;
private:
	void updateListCertificates();
	void updateButtons();
private:
	long getSerialOfSelectedCertificate() const;

	DECLARE_MESSAGE_MAP()
};

#endif
