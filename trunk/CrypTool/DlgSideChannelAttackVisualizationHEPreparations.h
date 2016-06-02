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

#ifndef _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONS_H_
#define _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONS_H_

#include "DlgSideChannelAttackVisualizationHE.h"
#include "DlgHybridEncryptionDemo.h"

class CDlgSideChannelAttackVisualizationHEPreparations : public CDialog {
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_PREPARATIONS };
public:
	CDlgSideChannelAttackVisualizationHEPreparations(CWnd* pParent = NULL);
	virtual ~CDlgSideChannelAttackVisualizationHEPreparations();
public:
	void setInitFile(CString);
	void setInitFileTitle(CString);
	void setInitMode(int);
public:
	bool isExistingHybEncFileUsed() { return useExistingHybEncFile; };
	CString getOriginalSessionKey();
	CString getFinalHybEncFile();
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	virtual void OnOK();
protected:
	bool useExistingHybEncFile;
private:
	CString originalSessionKey;
	CString certFilename;
	CString finalHybEncFile;
	CString initFile;
	CString initFileTitle;
	int initMode;

	DECLARE_MESSAGE_MAP()
};

#endif
