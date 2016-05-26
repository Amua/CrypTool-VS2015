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

#ifndef _DLGRANDOMGENERATOR_H_
#define _DLGRANDOMGENERATOR_H_

#include "HexEdit.h"
#include "IntegerArithmetic.h"
#include "DlgX2ModNRandomParamater.h"
#include "DlgLCGRandomParameter.h"
#include "DlgICGRandomParamater.h"
#include "DlgShowProgress.h"
#include "afxwin.h"

// internal struct for random generator parameters
struct RandomGeneratorParameters {
	int		m_SelGenerator;
	long	m_DataSize;
	CString m_seed;
	int     m_PrintInternalStates;
	// X^2 (mod N) Generator
	CX2ModNGenerator rnd_x2modN;
	CDlgX2ModNRandomParamater DRPXN;
	// LCG Generator
	LinearCongruenceGenerator DLCG;
	CDlgLCGRandomParameter DRP_LCG;
	// EICG Generator
	InverseCongruenceGenerator DICG;
	CDlgICGRandomParamater DRP_ICG;
	// construction
	RandomGeneratorParameters() : m_SelGenerator(0), m_DataSize(0), m_seed(""), m_PrintInternalStates(0) { }
};

// this function will generate random data in its own thread
UINT GenRandomDataThread(PVOID pParam);

class CDlgRandomGenerator : public CDialog {
	enum { IDD = IDD_RANDOM_GENERATOR };
public:
	CDlgRandomGenerator(CWnd* pParent = NULL);
	virtual ~CDlgRandomGenerator();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	afx_msg void OnSelGenParam();
	afx_msg void OnGenRandomData();
	virtual void OnCancel();
protected:
	CButton m_ctrlSetInternalStates;
	CHexEdit m_seed_ctrl;
	int m_SelGenerator;
	CString m_seed;
	long m_DataSize;
	int m_PrintInternalStates;
protected:
	RandomGeneratorParameters *m_randomGeneratorParameters;

	DECLARE_MESSAGE_MAP()
};

#endif
