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

#include "DlgSideChannelAttackVisualizationHEPSEPINPrompt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSideChannelAttackVisualizationHEPSEPINPrompt::CDlgSideChannelAttackVisualizationHEPSEPINPrompt(CWnd* pParent) :
	CDialog(CDlgSideChannelAttackVisualizationHEPSEPINPrompt::IDD, pParent) {

}

CDlgSideChannelAttackVisualizationHEPSEPINPrompt::~CDlgSideChannelAttackVisualizationHEPSEPINPrompt() {

}

void CDlgSideChannelAttackVisualizationHEPSEPINPrompt::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PIN, m_pin);
}
