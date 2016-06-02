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

#include "DlgSideChannelAttackVisualizationHEPreparations.h"
#include "DlgSideChannelAttackVisualizationHEPreparationsRequest1.h"
#include "DlgSideChannelAttackVisualizationHEPreparationsRequest2.h"
#include "DlgSideChannelAttackVisualizationHEPreparationsRequest3.h"

#include "DlgHybridEncryptionDemoSCA.h"
#include "DlgHybridDecryptionDemo.h"

#include "FileTools.h"
#include "CryptDoc.h"
#include "KeyFileHandling.h"
#include "DlgKeyAsymGeneration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgSideChannelAttackVisualizationHEPreparations::CDlgSideChannelAttackVisualizationHEPreparations(CWnd* pParent) :
	CDialog(CDlgSideChannelAttackVisualizationHEPreparations::IDD, pParent),
	initMode(0),
	initFile(""),
	initFileTitle(""),
	useExistingHybEncFile(false),
	finalHybEncFile(""),
	certificateSerial(0),
	originalSessionKey("") {
	
}

CDlgSideChannelAttackVisualizationHEPreparations::~CDlgSideChannelAttackVisualizationHEPreparations() {

}

BOOL CDlgSideChannelAttackVisualizationHEPreparations::OnInitDialog() {
	CDialog::OnInitDialog();
	return TRUE;
}

void CDlgSideChannelAttackVisualizationHEPreparations::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

void CDlgSideChannelAttackVisualizationHEPreparations::OnOK() {
	//CDialog::OnOK();
	
	int result = 0;
	
	// M�GLICHKEIT [1]
	// ===============
	//	Benutzer hat beim �ffnen des SCA-Dialogs noch keine Datei ge�ffnet. Folglich gibt es zwei
	//	M�glichkeiten: Zum einen (a) die Hybridverschl�sselung selbst durchf�hren oder (b) eine
	//	bereits hybridverschl�sselte Datei f�r einen schon angelegten Benutzer verwenden.
	if(initMode & SCA_MODE_NO_FILE)
	{
		CDlgSideChannelAttackVisualizationHEPreparationsRequest1 dlg;
		if(dlg.DoModal() == IDOK)
		{
			// Fall (a)
			if(dlg.getRadioChoice1())
			{
				// Benutzer m�chte eine Datei w�hlen und hybridverschl�sseln
				CDlgHybridEncryptionDemoSCA dlg;
				if(dlg.DoModal() == IDOK)
				{
					certificateSerial = dlg.getSelectedCertificateSerial();
					finalHybEncFile = dlg.getDocumentFileNameResult();
					originalSessionKey = dlg.getByteStringSymmetricKey().toString(16);
					CDialog::OnOK();
				}
				return;
			}
			// Fall (b)
			if(dlg.getRadioChoice2())
			{
				// ACHTUNG!!! Hier m�chte der Benutzer die Hybridverschl�sselung NICHT SELBST durchf�hren,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CDlgHybridDecryptionDemo::parseHybridEncryptedDocument(finalHybEncFile, certificateSerial, byteStringSessionKeyEncrypted, byteStringCipherText)) {
					CString message;
					message.Format(IDS_SCA_ERROR_CERTINFOEXTRACTION, finalHybEncFile);
					MessageBox(message, "CrypTool", MB_OK);
					return;
				}
				CDialog::OnOK();
				return;
			}
		}
	}
	// M�GLICHKEIT [2]
	// ===============
	//	Benutzer hat beim �ffnen des SCA-Dialogs schon eine Datei ge�ffnet. Folglich gibt es drei
	//	M�glichkeiten: (a) Die Hybridverschl�sselung mit der ge�ffneten Datei selbst durchf�hren
	//	oder (b) die Hybridverschl�sselung mit einer anderen Datei durchf�hren oder (c) eine
	//	bereits hybridverschl�sselte Datei f�r einen schon angelegten Benutzer verwenden.
	else if(initMode & SCA_MODE_INVALID_FILE)
	{
		CDlgSideChannelAttackVisualizationHEPreparationsRequest2 dlg;
		if(dlg.DoModal() == IDOK)
		{
			// Fall (a)
			if(dlg.getRadioChoice1())
			{
				CDlgHybridEncryptionDemoSCA dlg(initFile, initFileTitle);
				if(dlg.DoModal() == IDOK)
				{
					certificateSerial = dlg.getSelectedCertificateSerial();
					finalHybEncFile = dlg.getDocumentFileNameResult();
					originalSessionKey = dlg.getByteStringSymmetricKey().toString(16);
					CDialog::OnOK();
				}
				return;
			}
			// Fall (b)
			if(dlg.getRadioChoice2())
			{
				// Benutzer m�chte andere Datei w�hlen und hybridverschl�sseln
				CDlgHybridEncryptionDemoSCA dlg;
				if(dlg.DoModal() == IDOK)
				{
					certificateSerial = dlg.getSelectedCertificateSerial();
					finalHybEncFile = dlg.getDocumentFileNameResult();
					originalSessionKey = dlg.getByteStringSymmetricKey().toString(16);
					CDialog::OnOK();
				}
				return;
			}
			// Fall (c)
			if(dlg.getRadioChoice3())
			{
				// ACHTUNG!!! Hier m�chte der Benutzer die Hybridverschl�sselung NICHT SELBST durchf�hren,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CDlgHybridDecryptionDemo::parseHybridEncryptedDocument(finalHybEncFile, certificateSerial, byteStringSessionKeyEncrypted, byteStringCipherText)) {
					CString message;
					message.Format(IDS_SCA_ERROR_CERTINFOEXTRACTION, finalHybEncFile);
					MessageBox(message, "CrypTool", MB_OK);
					return;
				}
				CDialog::OnOK();
				return;
			}
		}
	}
	// M�GLICHKEIT [3]
	// ===============
	//	Benutzer hat beim �ffnen des SCA-Dialogs schon eine hybridverschl�sselte Datei ge�ffnet.
	//	Folglich gibt es drei M�glichkeiten: (a) Die ge�ffnete hybridverschl�sselte Datei verwenden
	//	oder (b) die Hybridverschl�sselung mit einer anderen Datei durchf�hren oder (c) eine
	//	bereits hybridverschl�sselte Datei f�r einen schon angelegten Benutzer verwenden.
	else if(initMode & SCA_MODE_VALID_FILE)
	{
		CDlgSideChannelAttackVisualizationHEPreparationsRequest3 dlg;
		if(dlg.DoModal() == IDOK)
		{
			// Fall (a)
			if(dlg.getRadioChoice1())
			{
				// Benutzer m�chte eine bereits existente und hybridverschl�sselte
				// Datei, die ge�ffnet ist, als Basis f�r Angriff verwenden
				useExistingHybEncFile = true;
				finalHybEncFile = initFile;
				// Zertifikatsinformationen ermitteln
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CDlgHybridDecryptionDemo::parseHybridEncryptedDocument(finalHybEncFile, certificateSerial, byteStringSessionKeyEncrypted, byteStringCipherText)) {
					CString message;
					message.Format(IDS_SCA_ERROR_CERTINFOEXTRACTION, finalHybEncFile);
					MessageBox(message, "CrypTool", MB_OK);
					return;
				}
				// ORIGINAL-Session-Key ermitteln nicht m�glich, da Datei bereits verschl�sselt
				LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_SESSIONKEYUNKNOWN, pc_str, STR_LAENGE_STRING_TABLE);
				originalSessionKey = pc_str;
				CDialog::OnOK();
				return;
			}
			// Fall (b)
			if(dlg.getRadioChoice2())
			{
				// Benutzer m�chte andere Datei w�hlen und hybridverschl�sseln
				CDlgHybridEncryptionDemoSCA dlg;
				if (dlg.DoModal() == IDOK)
				{
					certificateSerial = dlg.getSelectedCertificateSerial();
					finalHybEncFile = dlg.getDocumentFileNameResult();
					originalSessionKey = dlg.getByteStringSymmetricKey().toString(16);
					CDialog::OnOK();
				}
				return;
			}
			// Fall (c)
			if(dlg.getRadioChoice3())
			{
				// ACHTUNG!!! Hier m�chte der Benutzer die Hybridverschl�sselung NICHT SELBST durchf�hren,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CDlgHybridDecryptionDemo::parseHybridEncryptedDocument(finalHybEncFile, certificateSerial, byteStringSessionKeyEncrypted, byteStringCipherText)) {
					CString message;
					message.Format(IDS_SCA_ERROR_CERTINFOEXTRACTION, finalHybEncFile);
					MessageBox(message, "CrypTool", MB_OK);
					return;
				}
				CDialog::OnOK();
				return;
			}
		}
	}

	return;
}

void CDlgSideChannelAttackVisualizationHEPreparations::setInitMode(int i) {
	initMode = i;
}


void CDlgSideChannelAttackVisualizationHEPreparations::setInitFile(CString i) {
	initFile = i;
}

void CDlgSideChannelAttackVisualizationHEPreparations::setInitFileTitle(CString t) {
	initFileTitle = t;
}

CString CDlgSideChannelAttackVisualizationHEPreparations::getFinalHybEncFile() {
	return finalHybEncFile;
}

CString CDlgSideChannelAttackVisualizationHEPreparations::getOriginalSessionKey() {
	return originalSessionKey;
}

BEGIN_MESSAGE_MAP(CDlgSideChannelAttackVisualizationHEPreparations, CDialog)

END_MESSAGE_MAP()