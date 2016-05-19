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

#ifndef _DLGHMAC_H_
#define _DLGHMAC_H_

#include "CrypToolBase.h"

class CDlgHMAC : public CDialog {
	enum { IDD = IDD_HMAC };
public:
	CDlgHMAC(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent = NULL);
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnBUTTONSecondKey();
	afx_msg void OnEditText();
	afx_msg void OnEditKey();
	afx_msg void OnEditOriginalMessage();
	afx_msg void OnEditSecondKey();
	afx_msg void OnCbnSelendokComboSelectHashFunction();
	afx_msg void OnCbnSelendokComboSelectHmacAlgorithm();
protected:
	CEdit m_ctrl_secondkey;
	CEdit m_ctrl_key;
	CEdit m_mac;
	CEdit m_text;
	int m_alg;
	int m_position;
	CComboBox m_comboCtrlSelectHashFunction;
	CComboBox m_comboCtrlSelectHMACFunction;
private:
	void hash(char *data, int data_len, char *digest, int &len);
	void hash(CString &data, char *digest, int &len);
	CString hex_dump(const char *data, int len);
	void keyEmpty(int IDS);
	void SetMac(CString input);
	CString CalculateMac(CString tmpStr);
private:
	// this function is used for the live-update functionality of this dialog; as soon as a dialog 
	// control is invoked that changes a variable, use this function to both re-calculate the MAC and 
	// update the user interface accordingly
	void calculateMACAndUpdateGUI();
private:
	const CString m_documentFileName;
	const CString m_documentTitle;
private:
	// flomar, 01/20/2010
	bool shownInfoMessageNoKey;
	bool shownInfoMessageOneKey;
	bool shownInfoMessageDouble;
private:
	CString strText;
private:
	CString	m_key;
	CString	m_secondkey;
	CString	m_str_mac;
	CString m_originalMessage;
	CString m_innerHash;
	CString m_str_outer_input;
	CFont   m_font;

	DECLARE_MESSAGE_MAP()
};

#endif
