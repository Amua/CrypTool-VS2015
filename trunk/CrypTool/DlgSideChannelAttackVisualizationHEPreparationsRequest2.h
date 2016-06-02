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

#ifndef _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONSREQUEST2_H_
#define _DLGSIDECHANNELATTACKVISUALIZATIONHEPREPARATIONSREQUEST2_H_

class CDlgSideChannelAttackVisualizationHEPreparationsRequest2 : public CDialog {
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_PREPARATIONS_REQUEST_2 };
public:
	CDlgSideChannelAttackVisualizationHEPreparationsRequest2(CWnd* pParent = NULL);
	virtual ~CDlgSideChannelAttackVisualizationHEPreparationsRequest2();
public:
	bool getRadioChoice1() const { return radioChoice1; }
	bool getRadioChoice2() const { return radioChoice2; }
	bool getRadioChoice3() const { return radioChoice3; }
protected:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnBnClickedRadioChoice1();
	virtual void OnBnClickedRadioChoice2();
	virtual void OnBnClickedRadioChoice3();
	virtual void OnBnClickedOK();
	virtual void OnBnClickedCancel();
protected:
	bool radioChoice1;
	bool radioChoice2;
	bool radioChoice3;

	DECLARE_MESSAGE_MAP()
};

#endif