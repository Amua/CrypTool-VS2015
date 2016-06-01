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
#include "DlgHybridEncryptionDemoSCA.h"

#include "DialogeMessage.h"
#include "FileTools.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgHybridEncryptionDemoSCA::CDlgHybridEncryptionDemoSCA(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent) :
	CDlgHybridEncryptionDemo(_documentFileName, _documentTitle, pParent) {

}

CDlgHybridEncryptionDemoSCA::~CDlgHybridEncryptionDemoSCA() {

}

void CDlgHybridEncryptionDemoSCA::OnButtonEncDocumentSym() {
	// this function implements SCA-specific behavior: we need to make sure the 
	// file chosen by the user contains a keyword based on which Bob can determine 
	// whether a message has indeed been sent by Alice; if the file does not contain 
	// such a keyword, ask the user whether he wants to append it to the file, because 
	// otherwise the side-channel attack won't work

	// retrieve keyword from registry (if unsuccessful, go with "Alice" by default)
	CString keyword;
	if (CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "SideChannelAttack") == ERROR_SUCCESS) {
		unsigned long u_length = 1024;
		char c_SCA_keyWord[1025];
		if (CT_READ_REGISTRY(c_SCA_keyWord, "Keyword", u_length))
			keyword = c_SCA_keyWord;
		else
			keyword.Format(IDS_SCA_KEYWORD);
		CT_CLOSE_REGISTRY();
	}

	// now that we have the aforementioned keyword, check whether it's contained 
	// in the plain text corresponding to the file the user chose at the beginning
	CrypTool::ByteString byteStringKeyword;
	byteStringKeyword = keyword;
	size_t start;
	size_t end;
	const bool keywordFound = m_byteStringPlainText.findPattern(byteStringKeyword, start, end);

	// if the keyword could not be found, ask the user to append it to the plain text
	if (!keywordFound) {
		CString temp;
		temp.Format(IDS_SCA_KEYWORDPROBLEM, keyword);
		if (AfxMessageBox(temp, MB_YESNO) == IDYES) {
			// add the keyword to the plain text
			m_byteStringPlainText += keyword;
			// also re-write the plain text, because the user may re-read it from disk
			m_byteStringPlainText.writeToFile(m_documentFileName);
		}
	}

	// invoke base class implementation after SCA-specific behavior has been handled
	CDlgHybridEncryptionDemo::OnButtonEncDocumentSym();
}
