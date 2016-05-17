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

// DlgShowHash.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowHash.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgShowHash::CDlgShowHash(CWnd* pParent) :
	CDialog(CDlgShowHash::IDD, pParent),
	stringTitle(""),
	stringHash("") {

}

void CDlgShowHash::initialize(const CString &_title, const CString &_hash) {
	stringTitle = _title;
	stringHash = _hash;
}

BOOL CDlgShowHash::OnInitDialog() {
	CDialog::OnInitDialog();
	SetWindowText(stringTitle);
	return TRUE;
}

void CDlgShowHash::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, stringHash);
}

BEGIN_MESSAGE_MAP(CDlgShowHash, CDialog)
	ON_BN_CLICKED(IDOK, OnOK)
END_MESSAGE_MAP()
