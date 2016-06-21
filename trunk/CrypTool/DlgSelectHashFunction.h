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

#ifndef _DLGSELECTHASHFUNCTION_H_
#define _DLGSELECTHASHFUNCTION_H_

#include "CrypToolBase.h"

class CDlgSelectHashFunction : public CDialog {
	enum { IDD = IDD_SELECT_HASHFUNCTION };
public:
	CDlgSelectHashFunction(CWnd* pParent = NULL);
public:
	void enableSignatureMode();
public:
	CrypTool::Cryptography::Hash::HashAlgorithmType getHashAlgorithmType() const;
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	void deselectAllHashFunctions();
protected:
	afx_msg void OnSelectedHashFunctionMD4();
	afx_msg void OnSelectedHashFunctionMD5();
	afx_msg void OnSelectedHashFunctionSHA();
	afx_msg void OnSelectedHashFunctionSHA1();
	afx_msg void OnSelectedHashFunctionSHA256();
	afx_msg void OnSelectedHashFunctionSHA512();
	afx_msg void OnSelectedHashFunctionRIPEMD160();
protected:
	virtual void OnOK();
protected:
	bool m_enabledSignatureMode;
private:
	int selectedHashFunctionMD4;
	int selectedHashFunctionMD5;
	int selectedHashFunctionSHA;
	int selectedHashFunctionSHA1;
	int selectedHashFunctionSHA256;
	int selectedHashFunctionSHA512;
	int selectedHashFunctionRIPEMD160;

	DECLARE_MESSAGE_MAP()
};

#endif
