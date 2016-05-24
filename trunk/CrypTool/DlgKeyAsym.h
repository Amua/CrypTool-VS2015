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

// original implementation: Bartol Filipovic, 2000

#ifndef _DLGKEYASYM_H_
#define _DLGKEYASYM_H_

#include "KeyFileHandling.h"

class CDlgKeyAsym : public CDialog {
	enum { IDD = IDD_KEY_ASYM };
public:
	CDlgKeyAsym(CWnd* pParent = NULL);
	virtual ~CDlgKeyAsym();
public:
	bool AreThereRSAKeys();
	void setKeyID(const CString &userKeyId);
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnShowPubParamButton();
	afx_msg void OnShowAllParamButton();
	afx_msg void OnDeleteEntryButton();
	afx_msg void OnButtonShowCert();
	afx_msg void OnButtonExportCert();
	afx_msg void OnCheckRsaKey();
	afx_msg void OnCheckDsaKey();
	afx_msg void OnCheckEcKey();
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList3(NMHDR* pNMHDR, LRESULT* pResult);
private:
	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);
	int FindRow(CString pattern);
private:
	CButton	m_RemoveItem;
	CButton	m_CheckEC;
	CButton	m_CheckDSA;
	CButton	m_CheckRSA;
	CButton	m_show_cert_button;
	CButton	m_export_cert_button;
	CListCtrl m_listview;
	CButton	m_secret_param_button;
	CButton	m_pub_param_button;
	CSortAsymKeyList sortedAsymKeyList;
private:
	CString Name;
	CString Firstname;
	CString KeyType;
	CString KeyInfo;
	CString CreatTimeUTC;
	CString CreatTime;
	CString UserKeyId;
private:
	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	DECLARE_MESSAGE_MAP()
};

#endif
