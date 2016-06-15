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
	
	// MÖGLICHKEIT [1]
	// ===============
	//	Benutzer hat beim Öffnen des SCA-Dialogs noch keine Datei geöffnet. Folglich gibt es zwei
	//	Möglichkeiten: Zum einen (a) die Hybridverschlüsselung selbst durchführen oder (b) eine
	//	bereits hybridverschlüsselte Datei für einen schon angelegten Benutzer verwenden.
	if(initMode & SCA_MODE_NO_FILE)
	{
		CDlgSideChannelAttackVisualizationHEPreparationsRequest1 dlg;
		if(dlg.DoModal() == IDOK)
		{
			// Fall (a)
			if(dlg.getRadioChoice1())
			{
				// Benutzer möchte eine Datei wählen und hybridverschlüsseln
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
				// ACHTUNG!!! Hier möchte der Benutzer die Hybridverschlüsselung NICHT SELBST durchführen,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
				CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CrypTool::Utilities::parseHybridEncryptedFile(finalHybEncFile, certificateSerial, asymmetricAlgorithmType, symmetricAlgorithmType, byteStringSessionKeyEncrypted, byteStringCipherText)) {
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
	// MÖGLICHKEIT [2]
	// ===============
	//	Benutzer hat beim Öffnen des SCA-Dialogs schon eine Datei geöffnet. Folglich gibt es drei
	//	Möglichkeiten: (a) Die Hybridverschlüsselung mit der geöffneten Datei selbst durchführen
	//	oder (b) die Hybridverschlüsselung mit einer anderen Datei durchführen oder (c) eine
	//	bereits hybridverschlüsselte Datei für einen schon angelegten Benutzer verwenden.
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
				// Benutzer möchte andere Datei wählen und hybridverschlüsseln
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
				// ACHTUNG!!! Hier möchte der Benutzer die Hybridverschlüsselung NICHT SELBST durchführen,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
				CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CrypTool::Utilities::parseHybridEncryptedFile(finalHybEncFile, certificateSerial, asymmetricAlgorithmType, symmetricAlgorithmType, byteStringSessionKeyEncrypted, byteStringCipherText)) {
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
	// MÖGLICHKEIT [3]
	// ===============
	//	Benutzer hat beim Öffnen des SCA-Dialogs schon eine hybridverschlüsselte Datei geöffnet.
	//	Folglich gibt es drei Möglichkeiten: (a) Die geöffnete hybridverschlüsselte Datei verwenden
	//	oder (b) die Hybridverschlüsselung mit einer anderen Datei durchführen oder (c) eine
	//	bereits hybridverschlüsselte Datei für einen schon angelegten Benutzer verwenden.
	else if(initMode & SCA_MODE_VALID_FILE)
	{
		CDlgSideChannelAttackVisualizationHEPreparationsRequest3 dlg;
		if(dlg.DoModal() == IDOK)
		{
			// Fall (a)
			if(dlg.getRadioChoice1())
			{
				// Benutzer möchte eine bereits existente und hybridverschlüsselte
				// Datei, die geöffnet ist, als Basis für Angriff verwenden
				useExistingHybEncFile = true;
				finalHybEncFile = initFile;
				// Zertifikatsinformationen ermitteln
				CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
				CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CrypTool::Utilities::parseHybridEncryptedFile(finalHybEncFile, certificateSerial, asymmetricAlgorithmType, symmetricAlgorithmType, byteStringSessionKeyEncrypted, byteStringCipherText)) {
					CString message;
					message.Format(IDS_SCA_ERROR_CERTINFOEXTRACTION, finalHybEncFile);
					MessageBox(message, "CrypTool", MB_OK);
					return;
				}
				// ORIGINAL-Session-Key ermitteln nicht möglich, da Datei bereits verschlüsselt
				LoadString(AfxGetInstanceHandle(), IDS_SCA_CLIENT_SESSIONKEYUNKNOWN, pc_str, STR_LAENGE_STRING_TABLE);
				originalSessionKey = pc_str;
				CDialog::OnOK();
				return;
			}
			// Fall (b)
			if(dlg.getRadioChoice2())
			{
				// Benutzer möchte andere Datei wählen und hybridverschlüsseln
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
				// ACHTUNG!!! Hier möchte der Benutzer die Hybridverschlüsselung NICHT SELBST durchführen,
				useExistingHybEncFile = true;
				// Default-PSE-Datei verwenden
				LoadString(AfxGetInstanceHandle(), IDS_SCA_HYBRIDENCRYPTEDFILE_DEFAULT_PSEFILE, pc_str, STR_LAENGE_STRING_TABLE);
				// Dateinamen setzen (VOLLER PFAD!)
				finalHybEncFile = CrypTool::getCrypToolPath() + "\\" + pc_str;
				// Zertifikatsinformationen ermitteln
				CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
				CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
				CrypTool::ByteString byteStringSessionKeyEncrypted;
				CrypTool::ByteString byteStringCipherText;
				if (!CrypTool::Utilities::parseHybridEncryptedFile(finalHybEncFile, certificateSerial, asymmetricAlgorithmType, symmetricAlgorithmType, byteStringSessionKeyEncrypted, byteStringCipherText)) {
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