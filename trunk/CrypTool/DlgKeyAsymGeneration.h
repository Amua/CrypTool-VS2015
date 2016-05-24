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

#ifndef _DLGKEYASYMGENERATION_H_
#define _DLGKEYASYMGENERATION_H_

#include "resource.h"
#include "AsymmetricEncryption.h"
#include "afxwin.h"

#define EC_KEYFILE_IDSTRING "EC"
#define RSA_KEYFILE_IDSTRING "RSA"
#define DSA_KEYFILE_IDSTRING "DSA"

#define MAX_RSA_MODULSIZE theApp.SecudeLib.MaxBits
#define MIN_RSA_MODULSIZE 301

#define PSEUDO_MASTER_CA_PINNR "3.14159265358979323844"
#define DN_SUFFIX "DC=cryptool, DC=org"

class CDlgKeyAsymGeneration : public CDialog {
	enum { IDD = IDD_KEYASYM_GENERATION };
public:
	CDlgKeyAsymGeneration(CWnd* pParent = NULL);
	virtual ~CDlgKeyAsymGeneration();
public:
	void showRSAKeysOnly();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	virtual void OnOK();
	afx_msg void OnRSARadio();
	afx_msg void OnDSARadio();
	afx_msg void OnECRadio();
	afx_msg void OnOctalRadio();
	afx_msg void OnDecimalRadio();
	afx_msg void OnHexRadio();
	afx_msg void OnButtonP12import();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditLv();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnSelchangeEcCombo();
protected:
	void CreateAsymKeys();
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
protected:
	CStatic	m_RSATextInfo;
	CStatic	m_DSATextInfo;
	CStatic	m_ECTextInfo;
	CListCtrl m_dom_param_listview;
	CEdit m_ctrl5;
	CButton	m_hexadecimal_radio;
	CButton	m_decimal_radio;
	CButton	m_octal_radio;
	CButton	m_RSARadio;
	CButton	m_DSARadio;
	CButton	m_ECRadio;
	CComboBox m_rsa_combo;
	CComboBox m_dsa_combo;
	CComboBox m_ec_combo;
	CEdit m_ctrl4;
	CEdit m_ctrl3;
	CEdit m_ctrl2;
	CEdit m_ctrl1;
	CString	m_edit1;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_rsa_modul_str;
	CString	m_dsa_prime_str;
	CString	m_ec_dom_par_str;
	int m_verfahren;
	int m_zahlensystem;
	CString	m_user_keyinfo;
	CString	m_ec_dom_par_description;
	CButton m_ctrlShowKeyPair;
	int rsa_modul;
	int dsa_prime;
	int base;
	CString curveID;
	CString UserKeyId;
	bool m_showRSAKeysOnly;
	
#ifndef _UNSTABLE
	EcDomParamAcAsString ecParamString;
	EcDomParam_ac_ptr curveParameter; // The Domain Parameter of the selected elliptic Curve
	void UpdateEcListBox(EcDomParam_ac_ptr curveParameterPtr, EcDomParamAcAsString *ecParamString, 
	                     CString curveID, BOOL WindowActive = TRUE);
#endif

	DECLARE_MESSAGE_MAP()
};

#endif
