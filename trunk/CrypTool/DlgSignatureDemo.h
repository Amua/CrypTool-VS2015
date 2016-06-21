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

#ifndef _DLGSIGNATUREDEMO_H_
#define _DLGSIGNATUREDEMO_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

#include "PSEDemo.h"

class CDlgSignatureDemo : public CDialog {
	enum { IDD = IDD_SIGNATURE_DEMO };
public:
	CDlgSignatureDemo(const CString &_documentFileName = "", const CString &_documentTitle = "", CWnd* pParent = NULL);
	virtual ~CDlgSignatureDemo();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	CString m_documentFileName;
	CString m_documentTitle;
protected:
	CrypTool::ByteString m_byteStringMessage;
	CrypTool::ByteString m_byteStringHash;
	CrypTool::ByteString m_byteStringHashEncrypted;
	CrypTool::ByteString m_byteStringSignature;
protected:
	CrypTool::Cryptography::Hash::HashAlgorithmType m_hashAlgorihmType;

protected:
	int				m_nCols;
	CFont			m_Font1;	
	BOOL			m_bUpdateHsh;
	BOOL			m_bUpdateEnc;
	BOOL			m_bUpdateSgn;
	BOOL			m_bUpdateCrt;
	BOOL			m_bPSEIsExtern;

	CAppDocument*	m_NewDoc;
	CWnd*			m_hFocus;

	CBitmapButton m_ButtonSelectDoc;
	CBitmapButton m_ButtonSelectHashAlg;
	CBitmapButton m_ButtonSelectKey;
	CBitmapButton m_ButtonSelectCert;

	CBitmapButton m_ButtonInfoDoc;
	CBitmapButton m_ButtonInfoHashAlg;
	CBitmapButton m_ButtonInfoKey;
	CBitmapButton m_ButtonInfoCert;

	CBitmapButton m_ButtonCompute;
	CBitmapButton m_ButtonEncrypt;
	CBitmapButton m_ButtonCombine;

	CBitmapButton m_ButtonInfoHash;
	CBitmapButton m_ButtonInfoHashEnc;
	CBitmapButton m_ButtonInfoSign;

	CBitmapButton m_ButtonCancel;
	CBitmapButton m_ButtonOK;

	CStatic	m_DisplayContentCtrl;
	CEdit	m_DisplayInfoCtrl;
	CString	m_DisplayInfo;
	CString	m_DisplayContent;

protected:
	void EnableButtons();
	void ClearInfo();

protected:
	afx_msg void OnSelectDocument();
	afx_msg void OnInfoDocument();
	afx_msg void OnSelectKey();
	afx_msg void OnInfoKey();
	afx_msg void OnSelectHashAlg();
	afx_msg void OnCompute();
	afx_msg void OnInfoHash();
	afx_msg void OnEncrypt();
	afx_msg void OnInfoHashEnc();
	afx_msg void OnSelectCert();
	afx_msg void OnInfoAlg();
	afx_msg void OnCombine();
	virtual void OnOK();
	afx_msg void OnInfoCert();
	afx_msg void OnInfoSign();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

#endif
