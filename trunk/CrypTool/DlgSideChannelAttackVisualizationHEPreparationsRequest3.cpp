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

#include "DlgSideChannelAttackVisualizationHEPreparationsRequest3.h"

CDlgSideChannelAttackVisualizationHEPreparationsRequest3::CDlgSideChannelAttackVisualizationHEPreparationsRequest3(CWnd* pParent) : 
	CDialog(CDlgSideChannelAttackVisualizationHEPreparationsRequest3::IDD, pParent),
	radioChoice1(false),
	radioChoice2(false),
	radioChoice3(false) {

}

CDlgSideChannelAttackVisualizationHEPreparationsRequest3::~CDlgSideChannelAttackVisualizationHEPreparationsRequest3() {

}

BOOL CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnInitDialog() {
	CDialog::OnInitDialog();
	// check first radio button initially
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_1);
	// set booleans accordingly for later usage (after dialog is closed)
	radioChoice1 = true;
	radioChoice2 = false;
	radioChoice3 = false;
	return TRUE;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice1() {
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_1);
	radioChoice1 = true;
	radioChoice2 = false;
	radioChoice3 = false;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice2() {
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_2);
	radioChoice1 = false;
	radioChoice2 = true;
	radioChoice3 = false;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedRadioChoice3() {
	CheckRadioButton(IDC_RADIO_CHOICE_1, IDC_RADIO_CHOICE_3, IDC_RADIO_CHOICE_3);
	radioChoice1 = false;
	radioChoice2 = false;
	radioChoice3 = true;
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedOK() {
	CDialog::OnOK();
}

void CDlgSideChannelAttackVisualizationHEPreparationsRequest3::OnBnClickedCancel() {
	CDialog::OnCancel();
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEPreparationsRequest3, CDialog)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_1, OnBnClickedRadioChoice1)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_2, OnBnClickedRadioChoice2)
	ON_BN_CLICKED(IDC_RADIO_CHOICE_3, OnBnClickedRadioChoice3)
	ON_BN_CLICKED(IDOK, OnBnClickedOK)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()
