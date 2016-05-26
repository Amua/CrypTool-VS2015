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
#include <iostream>
#include "FileTools.h"
#include "DlgRandomGenerator.h"
#include "Cryptography.h"
#include "CryptDoc.h"
#include "DlgPrimesGeneratorDemo.h"
#include "DlgShowProgress.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgRandomGenerator::CDlgRandomGenerator(CWnd* pParent) :
	CDialog(CDlgRandomGenerator::IDD, pParent),
	m_PrintInternalStates(0),
	m_randomGeneratorParameters(0) {
	m_SelGenerator = 0;
	m_seed = _T("314159");
	m_DataSize = 2500;
	// create random generator parameters (deleted by thread function)
	m_randomGeneratorParameters = new RandomGeneratorParameters();
}

CDlgRandomGenerator::~CDlgRandomGenerator() {
	
}

BOOL CDlgRandomGenerator::OnInitDialog() {
	CDialog::OnInitDialog();
	if (CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "RandomGenerator") == ERROR_SUCCESS)
	{
		char tmpStr1[2048], tmpStr2[2048], tmpStr3[2048];
		unsigned long dataSize, outputInternalState, randomGeneratorTypeID, l;

		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "RandSeed", "314159", l);
		dataSize = 2500;
		CT_READ_REGISTRY_DEFAULT(dataSize, "GenerateBytes", 2500);
		outputInternalState = 1;
		CT_READ_REGISTRY_DEFAULT(outputInternalState, "ShowInternalRandState", 1);
		randomGeneratorTypeID = 0;
		CT_READ_REGISTRY_DEFAULT(randomGeneratorTypeID, "SelGenerator", 0);
		UpdateData(true);
		m_seed = tmpStr1;
		m_DataSize = dataSize;
		m_PrintInternalStates = outputInternalState;
		m_SelGenerator = randomGeneratorTypeID;

		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamX2MODN_N", STANDARD_X2MOD_N_MODUL, l);
		m_randomGeneratorParameters->DRPXN.SetModul(CString(tmpStr1));

		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamLCG_P1", "23", l);
		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr2, "ParamLCG_P2", "0", l);
		l = 2047;
		CT_READ_REGISTRY_DEFAULT(tmpStr3, "ParamLCG_N", "100000001", l);
		// LCG-Parameter nach Lehmer
		m_randomGeneratorParameters->DRP_LCG.m_LinParam_a = tmpStr1;
		m_randomGeneratorParameters->DRP_LCG.m_LinParam_b = tmpStr2;
		m_randomGeneratorParameters->DRP_LCG.m_LinParam_N = tmpStr3;

		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr1, "ParamICG_P1", "22211", l);
		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr2, "ParamICG_P2", "11926380", l);
		l = 2047; CT_READ_REGISTRY_DEFAULT(tmpStr3, "ParamICG_N", "2147483053", l);
		// ICG-Parameter nach ???
		m_randomGeneratorParameters->DRP_ICG.m_Param_a = tmpStr1;
		m_randomGeneratorParameters->DRP_ICG.m_Param_b = tmpStr2;
		m_randomGeneratorParameters->DRP_ICG.m_Param_N = tmpStr3;

		UpdateData(false);
		CT_CLOSE_REGISTRY();
	}
	UpdateData(false);
	return TRUE;
}

void CDlgRandomGenerator::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_seed_ctrl);
	DDX_Radio(pDX, IDC_RADIO1, m_SelGenerator);
	DDX_Text(pDX, IDC_EDIT1, m_seed);
	DDX_Text(pDX, IDC_EDIT2, m_DataSize);
	DDV_MinMaxLong(pDX, m_DataSize, 1, 1048576);
	DDX_Check(pDX, IDC_CHECK1, m_PrintInternalStates);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlSetInternalStates);
}

void CDlgRandomGenerator::OnSelGenParam() {
	UpdateData(TRUE);
	// DRPXN
	if (m_SelGenerator == 0) {
		if (m_randomGeneratorParameters->DRPXN.DoModal() == IDOK) {
			m_randomGeneratorParameters->rnd_x2modN.setModul(m_randomGeneratorParameters->DRPXN.GetModul());
		}
	}
	// DRPLCG
	else if (m_SelGenerator == 1) {
		if (m_randomGeneratorParameters->DRP_LCG.DoModal() == IDOK) {
			m_randomGeneratorParameters->DLCG.SetParameter(m_randomGeneratorParameters->DRP_LCG.Get_a(), m_randomGeneratorParameters->DRP_LCG.Get_b(), m_randomGeneratorParameters->DRP_LCG.Get_N());
		}
	}
	// DRPICG
	else if (m_SelGenerator == 2) {
		if (m_randomGeneratorParameters->DRP_ICG.DoModal()) {
			m_randomGeneratorParameters->DICG.SetParameter(m_randomGeneratorParameters->DRP_ICG.Get_a(), m_randomGeneratorParameters->DRP_ICG.Get_b(), m_randomGeneratorParameters->DRP_ICG.Get_N());
		}
	}
	UpdateData(false);
}

void CDlgRandomGenerator::OnGenRandomData() {
	UpdateData(TRUE);
	m_randomGeneratorParameters->m_DataSize = m_DataSize;
	m_randomGeneratorParameters->m_SelGenerator = m_SelGenerator;
	m_randomGeneratorParameters->m_seed = m_seed;
	m_randomGeneratorParameters->m_PrintInternalStates = m_PrintInternalStates;
	UpdateData(FALSE);
	if (m_DataSize >= 1 && m_DataSize < 1048576) {
		AfxBeginThread(GenRandomDataThread, m_randomGeneratorParameters);
		CDialog::OnOK();
	}
	else {
		// Fehlermeldung erscheint aufgrund der RessourcenSchranken :)
	}
}

void CDlgRandomGenerator::OnCancel() {
	CDialog::OnCancel();
	delete m_randomGeneratorParameters;
}

BEGIN_MESSAGE_MAP(CDlgRandomGenerator, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelGenParam)
	ON_BN_CLICKED(IDOK, OnGenRandomData)
END_MESSAGE_MAP()

UINT GenRandomDataThread(PVOID pParam) {
	BOOL Out;
	CString title;
	CString progress;
	char	outfile[256], outfile2[256];
	RandomGeneratorParameters *par = static_cast<RandomGeneratorParameters*>(pParam);
	GetTmpName(outfile, "cry", ".hex");
	ofstream rndData(outfile, ios::binary);
	ofstream rndState;
	CString  rndStateStr;

	if (par->m_PrintInternalStates)
	{
		GetTmpName(outfile2, "cry", ".txt");
		rndState.open(outfile2);
	}
	unsigned char	o;
	long			i, j, k(0), l;
	progress.LoadString(IDS_RAND_PROGRESS);

	switch (par->m_SelGenerator) {
	case 0:
	{
		title.Format(IDS_RAND_GEN_PARAM, "X^2 (mod N)", par->m_DataSize);
		theApp.fs.Display(LPCTSTR(title));
		par->rnd_x2modN.setSeed(par->m_seed);
		if (par->m_PrintInternalStates)
		{
			par->rnd_x2modN.randIntStr(rndStateStr);
			rndState << rndStateStr << " ";
		}
		for (j = 0; j<par->m_DataSize; j++)
		{
			o = 0;
			for (i = 0; i<8; i++) {
				par->rnd_x2modN.randomize();
				o |= par->rnd_x2modN.randBit() << (7 - i);
				if (par->m_PrintInternalStates)
				{
					par->rnd_x2modN.randIntStr(rndStateStr);
					rndState << rndStateStr << " ";
				}
			}
			rndData << o;
			if (theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				return 0;
			}
			if ((l = (j * 100) / par->m_DataSize)>k)            // nur einmal für jedes Prozent
			{
				theApp.fs.Set(k = l, "", progress);
			}
		}
	}
	title.Format(IDS_STRING_RAND_DATA_PARAM, "X^2 (mod N)", par->m_DataSize);
	break;
	case 1:
	{
		title.Format(IDS_RAND_GEN_PARAM, "LCG", par->m_DataSize);
		theApp.fs.Display(LPCTSTR(title));
		Out = par->DLCG.setSeed(par->m_seed);
		if (par->m_PrintInternalStates)
		{
			par->DLCG.randIntStr(rndStateStr);
			rndState << rndStateStr << " ";
		}
		for (j = 0; j<par->m_DataSize; j++)
		{
			o = 0;
			for (i = 0; i<8; i++) {
				par->DLCG.randomize();
				o |= par->DLCG.randBit() << (7 - i);
				if (par->m_PrintInternalStates)
				{
					par->DLCG.randIntStr(rndStateStr);
					rndState << rndStateStr << " ";
				}
			}
			rndData << o;
			if (theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				return 0;
			}
			if ((l = (j * 100) / par->m_DataSize)>k)            // nur einmal für jedes Prozent
			{
				theApp.fs.Set(k = l, "", progress);
			}
		}
	}
	title.Format(IDS_STRING_RAND_DATA_PARAM, "LCG", par->m_DataSize);
	break;
	case 2:
	{
		title.Format(IDS_RAND_GEN_PARAM, "ICG", par->m_DataSize);
		theApp.fs.Display(LPCTSTR(title));
		Out = par->DICG.setSeed(par->m_seed);
		if (par->m_PrintInternalStates)
		{
			par->DICG.randIntStr(rndStateStr);
			rndState << rndStateStr << " ";
		}
		for (j = 0; j<par->m_DataSize * 9; j++)
		{
			o = 0;
			for (i = 0; i<8; i++)
			{
				par->DICG.randomize();
				o |= par->DICG.randBit() << (7 - i);
				if (par->m_PrintInternalStates)
				{
					par->DICG.randIntStr(rndStateStr);
					rndState << rndStateStr << " ";
				}
				par->DICG.SetCount(j + i);
			}
			rndData << o;
			j += i; //weil j+i als SetCount gestellt wird, und m_DataSize*9 genommen ist
					//d.h. counter soll immer um 1 erhöht sein
			if (theApp.fs.m_canceled)
			{
				theApp.fs.cancel();
				return 0;
			}
			if ((l = (j * 100) / (par->m_DataSize * 9))>k)            // nur einmal für jedes Prozent
			{
				theApp.fs.Set(k = l, "", progress);
			}
		}
	}
	title.Format(IDS_STRING_RAND_DATA_PARAM, "ICG", par->m_DataSize);
	break;
	}
	rndData.close();
	if (par->m_PrintInternalStates)
		rndState.close();

	if (!theApp.fs.m_canceled)
	{
		if (par->m_PrintInternalStates)
			theApp.ThreadOpenDocumentFileNoMRU(outfile2, title);
		theApp.ThreadOpenDocumentFileNoMRU(outfile, title);
	}
	theApp.fs.cancel();

	if (CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "RandomGenerator") == ERROR_SUCCESS)
	{
		CT_WRITE_REGISTRY(par->m_seed.GetBuffer(), "RandSeed");
		CT_WRITE_REGISTRY((unsigned int)par->m_DataSize, "GenerateBytes");
		CT_WRITE_REGISTRY((unsigned int)par->m_PrintInternalStates, "ShowInternalRandState");
		CT_WRITE_REGISTRY((unsigned int)par->m_SelGenerator, "SelGenerator");

		CT_WRITE_REGISTRY(par->DRPXN.m_EditModul_N.GetBuffer(), "ParamX2MODN_N");

		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_a.GetBuffer(), "ParamLCG_P1");
		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_b.GetBuffer(), "ParamLCG_P2");
		CT_WRITE_REGISTRY(par->DRP_LCG.m_LinParam_N.GetBuffer(), "ParamLCG_N");

		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_a.GetBuffer(), "ParamICG_P1");
		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_b.GetBuffer(), "ParamICG_P2");
		CT_WRITE_REGISTRY(par->DRP_ICG.m_Param_N.GetBuffer(), "ParamICG_N");

		CT_CLOSE_REGISTRY();
	}
	delete par;
	par = 0;
	return 0;
}
