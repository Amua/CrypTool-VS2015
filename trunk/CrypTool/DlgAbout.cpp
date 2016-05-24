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
#include "DlgAbout.h"
#include "DlgAuthors.h"
#include "DlgTranslations.h"
#include "..\libNTL\include\NTL\version.h"
#include "crypto.h"
#include "gmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgAbout::CDlgAbout(CWnd* pParent) :
	CDialog(CDlgAbout::IDD, pParent) {
	
}

CDlgAbout::~CDlgAbout() {

}

BOOL CDlgAbout::OnInitDialog() {
	CDialog::OnInitDialog();
	// create font for dialog heading
	font.CreateFontA(34, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, "Arial");
	// get CrypTool version for dialog heading
	stringCrypToolVersion.LoadString(IDR_MAINFRAME);
	// determine individual library versions
	determineLibraryVersions();
	// release information as well as contact information is
	// displayed in a text field now to allow copy-and-paste
	CWnd *windowReleaseInformation = GetDlgItem(IDC_EDIT_RELEASE_INFORMATION);
	CWnd *windowContactInformation = GetDlgItem(IDC_EDIT_CONTACT_INFORMATION);
	// check if window for release information is valid
	if (windowReleaseInformation) {
		// construct build information
		CString stringCrypToolBuildTime;
		CString stringCrypToolBuildVersion;
		stringCrypToolBuildTime.LoadString(IDS_CRYPTOOL_BUILD_TIME);
		stringCrypToolBuildVersion.Format("MSC %d.%02d", _MSC_VER / 100, _MSC_VER % 100);
		// construct git information
		CString stringCrypToolGitInformation;
		CString stringCrypToolGitBranch;
		CString stringCrypToolGitCommit;
		stringCrypToolGitBranch.LoadString(IDS_CRYPTOOL_GIT_BRANCH);
		stringCrypToolGitCommit.LoadString(IDS_CRYPTOOL_GIT_COMMIT);
		if (stringCrypToolGitBranch.GetLength() > 0 && stringCrypToolGitCommit.GetLength() > 0) {
			stringCrypToolGitInformation.Format("[%s %s]", stringCrypToolGitBranch, stringCrypToolGitCommit);
		}
		// construct release information
		CString stringReleaseInformation;
		stringReleaseInformation.Format(IDS_CRYPTOOL_RELEASE_INFORMATION, stringCrypToolVersion, stringCrypToolBuildTime, stringCrypToolBuildVersion, stringCrypToolGitInformation);
		stringReleaseInformation.Append(strVersionApfloat); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionCracklib); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionCryptovision); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionGMP); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionMiracl); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionNTL); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionOpenSSL); stringReleaseInformation.Append(", ");
		stringReleaseInformation.Append(strVersionScintilla); stringReleaseInformation.Append(".");
		// display information
		windowReleaseInformation->SetWindowText(stringReleaseInformation);
	}
	// check if window for contact information is valid
	if (windowContactInformation) {
		CString stringContactInformation;
		// get contact information
		LoadString(AfxGetInstanceHandle(), IDS_STRING_ABOUT_CONTACT_INFORMATION, pc_str, STR_LAENGE_STRING_TABLE);
		stringContactInformation.Append(pc_str);
		// display information
		windowContactInformation->SetWindowText(stringContactInformation);
	}
	UpdateData(false);
	return TRUE;
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

void CDlgAbout::OnPaint() {
	CDialog::OnPaint();
	// display CrypTool version
	CDC *pDC = GetDC();
	CRect rect;
	GetClientRect(rect);
	// just use a portion of the rect for the heading
	rect.top = 10;
	rect.bottom = 50;
	// fill background with Windows system color (grey)
	pDC->FillSolidRect(rect, GetSysColor(COLOR_3DFACE));
	// display text
	pDC->SelectObject(&font);
	pDC->DrawText(stringCrypToolVersion, stringCrypToolVersion.GetLength(), rect, DT_CENTER | DT_VCENTER);
}

void CDlgAbout::OnBnClickedContributors() {
	// open authors dialog
	CDlgAuthors dlg;
	dlg.DoModal();
}

void CDlgAbout::OnBnClickedTranslations() {
	// open translations dialog
	CDlgTranslations dlg;
	dlg.DoModal();
}

void CDlgAbout::determineLibraryVersions() {
	// MIRACL (STATIC)
	this->strVersionMiracl = "4.4.3";
	this->strVersionMiracl.Insert(0, "Miracl ");
	// OPENSSL
	this->strVersionOpenSSL = OpenSSL::SSLeay_version(SSLEAY_VERSION);
	// NTL
	this->strVersionNTL = NTL_VERSION;
	this->strVersionNTL.Insert(0, "NTL ");
	// SCINTILLA
	int scv =
#include "../scintilla/version.txt"
	;
	this->strVersionScintilla.Format("%d.%d.%d",scv/100, (scv/10)%10, scv%10);
	this->strVersionScintilla.Insert(0, "Scintilla ");
	// GMP/MPIR
	CString StrGMPWindowText;
	StrGMPWindowText.Format("MPIR %s", mpir_version);
	this->strVersionGMP = StrGMPWindowText;
	// CRACKLIB (STATIC)
	this->strVersionCracklib = "2.7";
	this->strVersionCracklib.Insert(0, "cracklib ");
	// CRYPTOVISION (STATIC)
	this->strVersionCryptovision = "1.4.18";
	this->strVersionCryptovision.Insert(0, "cv cryptovision (tm) cv act library ");
	// APFLOAT (STATIC)
	this->strVersionApfloat = "2.41";
	this->strVersionApfloat.Insert(0, "apfloat ");
}

BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CONTRIBUTORS, OnBnClickedContributors)
	ON_BN_CLICKED(ID_TRANSLATIONS, OnBnClickedTranslations)
END_MESSAGE_MAP()
