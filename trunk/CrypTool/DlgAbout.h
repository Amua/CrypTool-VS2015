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

#ifndef _DLGABOUT_H_
#define _DLGABOUT_H_

class CDlgAbout : public CDialog {
	enum { IDD = IDD_ABOUT };
public:
	CDlgAbout(CWnd* pParent = NULL);
	virtual ~CDlgAbout();
protected:
	afx_msg BOOL OnInitDialog();
	afx_msg void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnPaint();
protected:
	afx_msg void OnBnClickedContributors();
	afx_msg void OnBnClickedTranslations();
private:
	void determineLibraryVersions();
private:
	CString stringCrypToolVersion;
private:
	CString strVersionMiracl;
	CString strVersionOpenSSL;
	CString strVersionNTL;
	CString strVersionScintilla;
	CString strVersionCryptovision;
	CString strVersionGMP;
	CString strVersionCracklib;
	CString strVersionApfloat;
private:
	CFont font;

	DECLARE_MESSAGE_MAP()
};

#endif
