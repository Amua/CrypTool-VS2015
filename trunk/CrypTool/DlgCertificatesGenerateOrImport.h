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

#ifndef _DLGCERTIFICATESGENERATEORIMPORT_H_
#define _DLGCERTIFICATESGENERATEORIMPORT_H_

class CDlgCertificatesGenerateOrImport : public CDialog {
	enum { IDD = IDD_CERTIFICATES_GENERATE_OR_IMPORT };
public:
	CDlgCertificatesGenerateOrImport(CWnd *_parent = 0);
	virtual ~CDlgCertificatesGenerateOrImport();
protected:
	afx_msg void clickedButtonRadioRSA();
	afx_msg void clickedButtonRadioDSA();
	afx_msg void clickedButtonRadioEC();
	afx_msg void clickedButtonCreate();
	afx_msg void clickedButtonImport();
	afx_msg void clickedButtonClose();

	DECLARE_MESSAGE_MAP()
};

#endif
