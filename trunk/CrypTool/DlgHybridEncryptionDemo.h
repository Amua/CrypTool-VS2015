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

#ifndef _DLGHYBRIDENCRYPTIONDEMO_H_
#define _DLGHYBRIDENCRYPTIONDEMO_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

#define INFO_TEXT_COLUMNS 20

// Falls der SCA-Modus aktiviert ist, werden in folgender Struktur Informationen
// über das ausgewählte Zertifikat/RSA-Schlüsselpaar abgelegt:
struct SCACertificateInformation {
	CString firstname;
	CString lastname;
	CString keytype;
	CString time;
	CString keyid;
};

class CDlgHybridEncryptionDemo : public CDialog {
	enum { IDD = IDD_HYBRID_ENCRYPTION_DEMO };
public:
	CDlgHybridEncryptionDemo(const CString &_documentFileName = "", const CString &_documentTitle = "", CWnd* pParent = NULL);
	virtual ~CDlgHybridEncryptionDemo();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnButtonGetDocument();
	afx_msg void OnButtonGenSymKey();
	afx_msg void OnButtonShowSymKey();
	afx_msg void OnButtonEncDocumentSym();
	afx_msg void OnButtonGetAsymKey();
	afx_msg void OnButtonEncKeyAsym();
	afx_msg void OnButtonShowAsymKey();
	afx_msg void OnButtonShowDocument();
	afx_msg void OnButtonShowEncDocument();
	afx_msg void OnButtonShowEncSymKey();
	afx_msg void OnButtonDatenausgabe();
	afx_msg void OnPaint();
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
private:
	bool DateiOeffnen(const CString &DateiPfadName);
	void EnDisButtons();
	void ShowButtons();
	void SetCondition(int button, bool state);
	void ResetDependent(int button);
private:
	enum ButtonStatus { inactive, active_not_pressed, active_pressed };
	int m_ButtonStatus[11];
	bool m_ActionPerformed[11];
	bool m_setMatrix[11][11];
private:
	CFont m_font;
	int m_iDocSize;
	bool m_bAuswahlDat;
	CWnd *m_hFocus;
	CStatic	m_ctrlBG;
	CString	m_strEdit;
	CString	m_strTitle;
	CBitmapButton m_ctrlBmpRaute1;
	CBitmapButton m_ctrlBmpRaute2;
	CBitmapButton m_ctrlBmpRaute3;
	CBitmapButton m_ctrlBmpRaute4;
	CBitmapButton m_ctrlBmpRaute5;
	CBitmapButton m_ctrlBmpSechseck1;
	CBitmapButton m_ctrlBmpSechseck2;
	CBitmapButton m_ctrlBmpSechseck3;
	CBitmapButton m_ctrlBmpRechteck1;
	CBitmapButton m_ctrlBmpRechteck2;
	CBitmapButton m_ctrlBmpOval1;
	CBitmapButton m_ctrlBmpOval2;
public:





	// TODO/FIXME/DITCHME
	SCACertificateInformation getCertInfo();
	CString getSCAFile();
	void activateSCABehaviour();
	SCACertificateInformation scaCertInfo;
	CString scaFile;
	bool isSCABehaviourActivated;
	
	DECLARE_MESSAGE_MAP()
};

#endif
