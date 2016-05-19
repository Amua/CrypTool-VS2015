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

#ifndef _DLGHASHDEMO_H_
#define _DLGHASHDEMO_H_

#include "CrypToolBase.h"

#define MAX_LAENGE_STRTEXT 16000

class CDlgHashDemo : public CDialog {
	enum { IDD = IDD_HASH_DEMO };
public:
	CDlgHashDemo(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent = NULL);
	~CDlgHashDemo();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnRadioBin();
	afx_msg void OnRadioDec();
	afx_msg void OnRadioHex();
	afx_msg void OnChangeEditText();
	afx_msg void OnSelendokComboSelectHashFunction();
private:
	void SetRed();
	void SetHashDiff(CrypTool::ByteString &hash1, CrypTool::ByteString &hash2);
private:
	void ComputeHash(CrypTool::ByteString *data, CrypTool::ByteString *hashValue);
private:
	CrypTool::Cryptography::Hash::HashAlgorithmType getHashAlgorithmType() const;
private:
	const CString m_documentFileName;
	const CString m_documentTitle;
private:
	CString	m_strHashDiffRE;
	CString m_strNewHashBin;
	CString m_strOrigHashBin;
	CrypTool::ByteString m_hash;
	CrypTool::ByteString m_newHash;
	CrypTool::ByteString m_dataOrig; 
private:
	CString m_strHashFunctionMD4;
	CString m_strHashFunctionMD5;
	CString m_strHashFunctionSHA;
	CString m_strHashFunctionSHA1;
	CString m_strHashFunctionSHA256;
	CString m_strHashFunctionSHA512;
	CString m_strHashFunctionRIPEMD160;
private:
	CComboBox m_comboCtrlSelectHashFunction;
	CEdit m_ctrlText;
	CRichEditCtrl m_ctrlHashDiff;
	CFont m_font;
	int m_rb_DarstHW;
	CString	m_strOrigHash;
	CString	m_strNewHash;

	DECLARE_MESSAGE_MAP()
};

#endif
