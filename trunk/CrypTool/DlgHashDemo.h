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

#define MAX_LAENGE_STRTEXT 16000

class CDlgHashDemo : public CDialog {
	enum { IDD = IDD_HASH_DEMO };
public:
	CDlgHashDemo(CWnd* pParent = NULL);
	~CDlgHashDemo();
public:
	unsigned long loadData(const char *infile, const char *title, unsigned long filesize, unsigned long max_filesize = MAX_LAENGE_STRTEXT);
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
	void SetHashDiff(OctetString &hash1, OctetString &hash2);
	void showDiffOrigHashBin(OctetString &hash);
	void showDiffNewHashBin(OctetString &hash);
	void showHashBin(OctetString &hash);
	void showHashDec(OctetString &hash);
	void showHashHex(OctetString &hash);
	void showNewHashBin(OctetString &hash);
	void showNewHashDec(OctetString &hash);
	void showNewHashHex(OctetString &hash);
private:
	void getNextBlock(CString &dispByte, unsigned char inByte, unsigned short numberBase, char seperator = '\0');
	void ComputeHash(OctetString *data, OctetString *hashValue);
private:
	CString	m_strHashDiffRE;
	CString m_strNewHashBin;
	CString m_strOrigHashBin;
	CString m_strTitle;
	OctetString m_hash, m_newHash; 
	OctetString m_dataOrig; 
	CString m_strText;
private:
	CString m_strHashFunctionMD2;
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
