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

#ifndef _DLGHYBRIDDECRYPTIONDEMO_H_
#define _DLGHYBRIDDECRYPTIONDEMO_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgHybridDecryptionDemo : public CDialog {
	enum { IDD = IDD_HYBRID_DECRYPTION_DEMO };
public:
	CDlgHybridDecryptionDemo(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent = NULL);
	virtual ~CDlgHybridDecryptionDemo();
public:
	static bool isDocumentHybridEncrypted(const CString &_documentFileName);
	static bool parseHybridEncryptedDocument(const CString &_documentFileName, long &_serial, CrypTool::ByteString &_sessionKeyEncrypted, CrypTool::ByteString &_cipherText);
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnOK();
	afx_msg void OnCancel();
	afx_msg void OnButtonContinue();
	afx_msg void OnButtonShowCertificate();
private:
	CString m_documentFileName;
	CString m_documentTitle;
private:
	CrypTool::ByteString m_byteStringPlainText;
	CrypTool::ByteString m_byteStringCipherText;
	CrypTool::ByteString m_byteStringSymmetricKey;
	CrypTool::ByteString m_byteStringSymmetricKeyEncrypted;
private:
	long m_selectedCertificateSerial;
	CString m_selectedCertificatePassword;
private:
	int UpdateDataDisplay();
private:
	CString sKeyPrivate;
	int nFirstVisibleLine;
	int step;
private:
	CFont m_Font;
	CFont m_Font2;
private:
	CEdit m_DisplayDataCtrl;
	CEdit m_StepCtrl;
	CEdit m_TextSignStepsCtrl;
	CButton	m_FlushDecDataCtrl;
	CButton	m_ContinueButtonCtrl;
	CString	m_TextSignSteps;
	CString	m_Step;
	CString	m_DisplayData;
	CButton m_ShowCertificate;

	DECLARE_MESSAGE_MAP()
};

#endif
