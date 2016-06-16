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

#ifndef _DLGCERTIFICATESTORESIGNATUREEXTRACTED_H_
#define _DLGCERTIFICATESTORESIGNATUREEXTRACTED_H_

#include <afxwin.h>
#include <afxcmn.h>
#include <resource.h>

class CDlgCertificateStoreSignatureExtracted : public CDialog {
	enum { IDD = IDD_CERTIFICATE_STORE_SIGNATURE_EXTRACTED };
public:
	CDlgCertificateStoreSignatureExtracted(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent = 0);
	virtual ~CDlgCertificateStoreSignatureExtracted();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange *_pDX);
protected:
	afx_msg void clickedButtonVerify();
	afx_msg void clickedButtonCancel();
protected:
	const CString m_documentFileName;
	const CString m_documentTitle;
protected:
	long m_serial;
	CrypTool::Cryptography::Hash::HashAlgorithmType m_hashAlgorithmType;
	CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType m_asymmetricAlgorithmType;
	CrypTool::Cryptography::Signature::SignatureType m_signatureType;
	CrypTool::ByteString m_message;
	CrypTool::ByteString m_signature;
	CString m_signerName;
	CString m_signerKey;
	CString m_signatureName;

	DECLARE_MESSAGE_MAP()
};

#endif
