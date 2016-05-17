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
#include "DlgSelectHashFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSelectHashFunction::CDlgSelectHashFunction(CWnd* pParent) :
	CDialog(CDlgSelectHashFunction::IDD, pParent) {
	
}

CrypTool::Cryptography::Hash::HashAlgorithmType CDlgSelectHashFunction::getHashAlgorithmType() const {
	if (selectedHashFunctionMD4 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD4;
	else if (selectedHashFunctionMD5 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD5;
	else if (selectedHashFunctionSHA == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA;
	else if (selectedHashFunctionSHA1 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA1;
	else if (selectedHashFunctionSHA256 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA256;
	else if (selectedHashFunctionSHA512 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA512;
	else if (selectedHashFunctionRIPEMD160 == 0) return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_RIPEMD160;
	else return CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL;
}

BOOL CDlgSelectHashFunction::OnInitDialog() {
	CDialog::OnInitDialog();
	OnSelectedHashFunctionMD4();
	return FALSE;
}

void CDlgSelectHashFunction::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_MD4, selectedHashFunctionMD4);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_MD5, selectedHashFunctionMD5);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_SHA, selectedHashFunctionSHA);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_SHA1, selectedHashFunctionSHA1);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_SHA256, selectedHashFunctionSHA256);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_SHA512, selectedHashFunctionSHA512);
	DDX_Radio(pDX, IDC_RADIO_HASH_FUNCTION_RIPEMD160, selectedHashFunctionRIPEMD160);
}

void CDlgSelectHashFunction::deselectAllHashFunctions() {
	selectedHashFunctionMD4 = -1;
	selectedHashFunctionMD5 = -1;
	selectedHashFunctionSHA = -1;
	selectedHashFunctionSHA1 = -1;
	selectedHashFunctionSHA256 = -1;
	selectedHashFunctionSHA512 = -1;
	selectedHashFunctionRIPEMD160 = -1;
}

void CDlgSelectHashFunction::OnSelectedHashFunctionMD4() {
	deselectAllHashFunctions();
	selectedHashFunctionMD4 = 0;
	UpdateData(false);		
}

void CDlgSelectHashFunction::OnSelectedHashFunctionMD5() {
	deselectAllHashFunctions();
	selectedHashFunctionMD5 = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnSelectedHashFunctionSHA() {
	deselectAllHashFunctions();
	selectedHashFunctionSHA = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnSelectedHashFunctionSHA1() {
	deselectAllHashFunctions();
	selectedHashFunctionSHA1 = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnSelectedHashFunctionSHA256() {
	deselectAllHashFunctions();
	selectedHashFunctionSHA256 = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnSelectedHashFunctionSHA512() {
	deselectAllHashFunctions();
	selectedHashFunctionSHA512 = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnSelectedHashFunctionRIPEMD160() {
	deselectAllHashFunctions();
	selectedHashFunctionRIPEMD160 = 0;
	UpdateData(false);
}

void CDlgSelectHashFunction::OnOK() {
	CDialog::OnOK();
}

BEGIN_MESSAGE_MAP(CDlgSelectHashFunction, CDialog)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_MD4, OnSelectedHashFunctionMD4)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_MD5, OnSelectedHashFunctionMD5)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA, OnSelectedHashFunctionSHA)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA1, OnSelectedHashFunctionSHA1)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA256, OnSelectedHashFunctionSHA256)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_SHA512, OnSelectedHashFunctionSHA512)
	ON_BN_CLICKED(IDC_RADIO_HASH_FUNCTION_RIPEMD160, OnSelectedHashFunctionRIPEMD160)
END_MESSAGE_MAP()
