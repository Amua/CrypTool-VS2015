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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolBase.h"
#include "DlgCertificateStoreSignatureExtracted.h"

CDlgCertificateStoreSignatureExtracted::CDlgCertificateStoreSignatureExtracted(const CString &_documentFileName, const CString &_documentTitle, CWnd *_parent) :
	CDialog(CDlgCertificateStoreSignatureExtracted::IDD, _parent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle) {

}

CDlgCertificateStoreSignatureExtracted::~CDlgCertificateStoreSignatureExtracted() {

}

BOOL CDlgCertificateStoreSignatureExtracted::OnInitDialog() {
	CDialog::OnInitDialog();
	// try to parse specified document as signature file
	if (!CrypTool::Utilities::parseSignatureFile(m_documentFileName, m_serial, m_hashAlgorithmType, m_asymmetricAlgorithmType, m_message, m_signature)) {
		AfxMessageBox("CRYPTOOL_BASE: error parsing signature file");
		EndDialog(IDOK);
		return TRUE;
	}
	// assign internal variables for signer name
	CrypTool::Cryptography::Asymmetric::CertificateStore::instance().getUserCertificateStringName(m_serial, m_signerName);
	// assign internal variable for signature type
	m_signatureType = CrypTool::Cryptography::Signature::getSignatureType(m_asymmetricAlgorithmType, m_hashAlgorithmType);
	if (m_signatureType == CrypTool::Cryptography::Signature::SIGNATURE_TYPE_NULL) {
		AfxMessageBox("CRYPTOOL_BASE: error parsing signature file");
		EndDialog(IDOK);
		return TRUE;
	}
	// assign internal variable for signer key
	m_signerKey.Format("%d", m_serial);
	// assign internal variable for signature name
	m_signatureName = CrypTool::Cryptography::Signature::getSignatureName(m_signatureType);
	// initial update
	UpdateData(false);
	return TRUE;
}

void CDlgCertificateStoreSignatureExtracted::DoDataExchange(CDataExchange *_pDX) {
	CDialog::DoDataExchange(_pDX);
	DDX_Text(_pDX, IDC_STATIC_SIGNER, m_signerName);
	DDX_Text(_pDX, IDC_STATIC_KEY, m_signerKey);
	DDX_Text(_pDX, IDC_STATIC_SIGNATURE, m_signatureName);
}

void CDlgCertificateStoreSignatureExtracted::clickedButtonVerify() {
	UpdateData(true);
}

void CDlgCertificateStoreSignatureExtracted::clickedButtonCancel() {
	UpdateData(true);
	EndDialog(IDCANCEL);
}

BEGIN_MESSAGE_MAP(CDlgCertificateStoreSignatureExtracted, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_VERIFY, &CDlgCertificateStoreSignatureExtracted::clickedButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CDlgCertificateStoreSignatureExtracted::clickedButtonCancel)
END_MESSAGE_MAP()