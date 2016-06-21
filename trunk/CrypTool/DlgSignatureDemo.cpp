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
#include "DlgSignatureDemo.h"

#include "FileTools.h"
#include "DlgSignature.h"
#include "DlgDemoRSAKeyGeneration.h"
#include "DlgCertificateGeneration.h"
#include "DlgSelectHashFunction.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char button1, button2, button3, button4;

CDlgSignatureDemo::CDlgSignatureDemo(const CString &_documentFileName, const CString &_documentTitle, CWnd* pParent) :
	CDialog(CDlgSignatureDemo::IDD, pParent),
	m_documentFileName(_documentFileName),
	m_documentTitle(_documentTitle),
	m_hashAlgorihmType(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL),
	m_nCols(18),
	m_NewDoc(0),  
	m_bUpdateHsh(TRUE),
	m_bUpdateEnc(TRUE),
	m_bUpdateSgn(TRUE),
	m_bUpdateCrt(TRUE) {
	
}

CDlgSignatureDemo::~CDlgSignatureDemo() {

}

BOOL CDlgSignatureDemo::OnInitDialog() {
	CDialog::OnInitDialog();

	// Fonts initialisieren:
	m_Font1.CreatePointFont(80, "Courier");
	m_DisplayInfoCtrl.SetFont(&m_Font1);

	// BitmapButtons laden:	
	m_ButtonSelectDoc.AutoLoad(IDC_SELECT_DOCUMENT, this);
	m_ButtonSelectHashAlg.AutoLoad(IDC_SELECT_HASHALG, this);
	m_ButtonSelectKey.AutoLoad(IDC_SELECT_KEY, this);
	m_ButtonSelectCert.AutoLoad(IDC_SELECT_CERT, this);

	m_ButtonInfoDoc.AutoLoad(IDC_INFO_DOCUMENT, this);
	m_ButtonInfoHashAlg.AutoLoad(IDC_INFO_HASHALG, this);
	m_ButtonInfoKey.AutoLoad(IDC_INFO_KEY, this);
	m_ButtonInfoCert.AutoLoad(IDC_INFO_CERT, this);

	m_ButtonCompute.AutoLoad(IDC_COMPUTE, this);
	m_ButtonEncrypt.AutoLoad(IDC_ENCRYPT, this);
	m_ButtonCombine.AutoLoad(IDC_COMBINE, this);

	m_ButtonInfoHash.AutoLoad(IDC_INFO_HASH, this);
	m_ButtonInfoHashEnc.AutoLoad(IDC_INFO_HASH_ENC, this);
	m_ButtonInfoSign.AutoLoad(IDC_INFO_SIGN, this);

	m_ButtonCancel.AutoLoad(IDCANCEL, this);
	m_ButtonOK.AutoLoad(IDOK, this);

	if (!m_documentFileName.IsEmpty()) {
		m_byteStringMessage.readFromFile(m_documentFileName);
		OnInfoDocument();
		m_ButtonInfoDoc.SetFocus();
		button1 = -1;
	}
	else {
		button1 = 0;
	}
	button2 = button3 = button4;
	EnableButtons();

	return FALSE;
}

void CDlgSignatureDemo::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DISPLAY_CONTENT, m_DisplayContentCtrl);
	DDX_Control(pDX, IDC_DISPLAY_INFO, m_DisplayInfoCtrl);
	DDX_Text(pDX, IDC_DISPLAY_INFO, m_DisplayInfo);
	DDX_Text(pDX, IDC_DISPLAY_CONTENT, m_DisplayContent);
}

void CDlgSignatureDemo::OnSelectDocument() {
	CFileDialog dlgFile(TRUE);
	if (dlgFile.DoModal() == IDOK) {
		m_documentFileName = dlgFile.GetPathName();
		m_documentTitle = dlgFile.GetFileName();
		m_byteStringMessage.readFromFile(m_documentFileName);
		m_bUpdateHsh = TRUE;
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		button1 = -1;
		EnableButtons();
		m_ButtonInfoDoc.SetFocus();
		ClearInfo();
	}
}

void CDlgSignatureDemo::OnInfoDocument() {
	m_DisplayContent.LoadString(IDS_CONTENT_DOCUMENT);
	m_DisplayInfo = m_byteStringMessage.toHexDump(19);
	m_DisplayContent += m_documentTitle;
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnSelectHashAlg() {
	CDlgSelectHashFunction dlgSelectHashFunction;
	dlgSelectHashFunction.enableSignatureMode();
	if (dlgSelectHashFunction.DoModal() == IDOK) {
		m_hashAlgorihmType = dlgSelectHashFunction.getHashAlgorithmType();
		m_bUpdateHsh = TRUE;
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		button2 = -1;
		EnableButtons();
		m_ButtonInfoHashAlg.SetFocus();
		ClearInfo();
	}
}

void CDlgSignatureDemo::OnInfoAlg() {
	m_DisplayContent.Format(IDS_CONTENT_ALG);
	m_DisplayInfo = CrypTool::Cryptography::Hash::getHashAlgorithmName(m_hashAlgorihmType);
	UpdateData(false);
}

void CDlgSignatureDemo::OnCompute() {
	CrypTool::Cryptography::Hash::HashOperation hashOperation(m_hashAlgorihmType);
	hashOperation.executeOnByteStrings(m_byteStringMessage, m_byteStringHash);
	m_bUpdateHsh = FALSE;
	EnableButtons();
	m_ButtonInfoHash.SetFocus();
}

void CDlgSignatureDemo::OnInfoHash() {
	m_DisplayContent.Format(IDS_STRING_HASH_VALUE_OF, CrypTool::Cryptography::Hash::getHashAlgorithmName(m_hashAlgorihmType), m_documentTitle);
	m_DisplayInfo = m_byteStringHash.toHexDump(19);
	UpdateData(FALSE);
}



void CDlgSignatureDemo::OnSelectKey() {
#ifndef _UNSTABLE
	CDlgDemoRSAKeyGeneration* KeyDialog;
	KeyDialog = new CDlgDemoRSAKeyGeneration(this);

	KeyDialog->InitRSA(m_Cert);
	if(KeyDialog->DoModal()==IDOK) 
	{
		m_bUpdateEnc = TRUE;
		m_bUpdateSgn = TRUE;
		m_bUpdateCrt = TRUE;
		button3 = -1;
		button4 = -1;
		EnableButtons();
		//OnInfoKey();
		m_ButtonInfoKey.SetFocus();	
		ClearInfo();
	}
	delete KeyDialog;
#endif
}

void CDlgSignatureDemo::OnInfoKey() {
#ifndef _UNSTABLE
	if(!m_Cert->IsInitialized()) return;

	CString sModN, sPhiN, sKeyPublic, sKeyPrivate, sOutput;
	m_Cert->GetParameter(sModN, sPhiN,sKeyPublic,sKeyPrivate);

	ClearInfo();
	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_KEY);
	sOutput.Format(IDS_BITLENGTH_MODN, m_Cert->GetBitLength());
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_MOD_N, sModN);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_PHI_N, sPhiN);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_KEY_PUBLIC, sKeyPublic);
	m_DisplayInfo += sOutput;
	sOutput.Format(IDS_KEY_PRIVATE, sKeyPrivate);
	m_DisplayInfo += sOutput;
	UpdateData(FALSE);
#endif
}

void CDlgSignatureDemo::EnableButtons() {
	m_hFocus = GetFocus();
	unsigned long newsdStatus = 0;
	UpdateData(TRUE);

	if (m_byteStringSignature.getByteLength() && !m_bUpdateSgn) {
		m_ButtonOK.EnableWindow(TRUE);
		m_ButtonInfoSign.EnableWindow(TRUE);
		m_ButtonCombine.LoadBitmaps("COMBINE_G_U", "COMBINE_G_D", "COMBINE_G_F", "COMBINE_R_X");
		m_ButtonCombine.ShowWindow(SW_HIDE);
		m_ButtonCombine.ShowWindow(SW_SHOW);
	}
	else {
		m_ButtonOK.EnableWindow(FALSE);
		m_ButtonInfoSign.EnableWindow(FALSE);
		m_ButtonCombine.LoadBitmaps("COMBINE_R_U", "COMBINE_R_D", "COMBINE_R_F", "COMBINE_R_X");
		m_ButtonCombine.ShowWindow(SW_HIDE);
		m_ButtonCombine.ShowWindow(SW_SHOW);
	}	

	if (m_byteStringHash.getByteLength() && !m_bUpdateHsh) {
		m_ButtonInfoHash.EnableWindow(TRUE);
		m_ButtonCompute.LoadBitmaps("COMPUTE_G_U", "COMPUTE_G_D", "COMPUTE_G_F", "COMPUTE_R_X");
		m_ButtonCompute.ShowWindow(SW_HIDE);
		m_ButtonCompute.ShowWindow(SW_SHOW);
	}
	else {
		m_ButtonInfoHash.EnableWindow(FALSE);
		m_ButtonCompute.LoadBitmaps("COMPUTE_R_U", "COMPUTE_R_D", "COMPUTE_R_F", "COMPUTE_R_X");
		m_ButtonCompute.ShowWindow(SW_HIDE);
		m_ButtonCompute.ShowWindow(SW_SHOW);
	}

	if (m_byteStringHashEncrypted.getByteLength() && !m_bUpdateEnc) {
		m_ButtonInfoHashEnc.EnableWindow(TRUE);
		m_ButtonEncrypt.LoadBitmaps("ENCRYPT_G_U", "ENCRYPT_G_D", "ENCRYPT_G_F", "ENCRYPT_R_X");
		m_ButtonEncrypt.ShowWindow(SW_HIDE);
		m_ButtonEncrypt.ShowWindow(SW_SHOW);
	}
	else {
		m_ButtonInfoHashEnc.EnableWindow(FALSE);
		m_ButtonEncrypt.LoadBitmaps("ENCRYPT_R_U", "ENCRYPT_R_D", "ENCRYPT_R_F", "ENCRYPT_R_X");
		m_ButtonEncrypt.ShowWindow(SW_HIDE);
		m_ButtonEncrypt.ShowWindow(SW_SHOW);
	}
	
	if (m_byteStringMessage.getByteLength() && m_hashAlgorihmType != CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL) {
		m_ButtonCompute.EnableWindow(TRUE);
	}
	else {
		m_ButtonCompute.EnableWindow(FALSE);
	}

	if (m_byteStringHash.getByteLength() && !m_bUpdateHsh) {
		m_ButtonEncrypt.EnableWindow(TRUE);
	}
	else {
		m_ButtonEncrypt.EnableWindow(FALSE);
	}

	if (!m_bUpdateEnc &&  !m_bUpdateCrt) {
		m_ButtonCombine.EnableWindow(TRUE);
	}
	else {
		m_ButtonCombine.EnableWindow(FALSE);
	}
	
	if (!m_documentFileName.IsEmpty())
		m_ButtonInfoDoc.EnableWindow(TRUE);
	else
		m_ButtonInfoDoc.EnableWindow(FALSE);

	if (button1 == -1) {
		if( !m_documentFileName.IsEmpty()) {
			m_ButtonSelectDoc.LoadBitmaps("OPENDOC_G_U", "OPENDOC_G_D", "OPENDOC_G_F", NULL);
			m_ButtonSelectDoc.ShowWindow(SW_HIDE);
			m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		}
		else {
			m_ButtonSelectDoc.LoadBitmaps("OPENDOC_R_U", "OPENDOC_R_D", "OPENDOC_R_F", NULL);
			m_ButtonSelectDoc.ShowWindow(SW_HIDE);
			m_ButtonSelectDoc.ShowWindow(SW_SHOW);
		}
		button1 = 1;
	}

	// TODO/FIXME
	if (m_hashAlgorihmType != CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL)
		m_ButtonInfoHashAlg.EnableWindow(TRUE);
	else
		m_ButtonInfoHashAlg.EnableWindow(FALSE);

	if (button2 == -1) {
		if (m_hashAlgorihmType != CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL) {
			m_ButtonSelectHashAlg.LoadBitmaps("SELECTALG_G_U", "SELECTALG_G_D", "SELECTALG_G_F", NULL);
			m_ButtonSelectHashAlg.ShowWindow(SW_HIDE);
			m_ButtonSelectHashAlg.ShowWindow(SW_SHOW);
		}
		else {
			m_ButtonSelectHashAlg.LoadBitmaps("SELECTALG_R_U", "SELECTALG_R_D", "SELECTALG_R_F", NULL);
			m_ButtonSelectHashAlg.ShowWindow(SW_HIDE);
			m_ButtonSelectHashAlg.ShowWindow(SW_SHOW);
		}
		button2 = 1;
	}

	// TODO/FIXME
	//m_ButtonInfoKey.EnableWindow(TRUE);
	m_ButtonInfoKey.EnableWindow(FALSE);

	if (button3 == -1) {
		// TODO/FIXME
		//m_ButtonSelectKey.LoadBitmaps("GENKEY_G_U", "GENKEY_G_D", "GENKEY_G_F", NULL);
		//m_ButtonSelectKey.ShowWindow(SW_HIDE);
		//m_ButtonSelectKey.ShowWindow(SW_SHOW);
		m_ButtonSelectKey.LoadBitmaps("GENKEY_R_U", "GENKEY_R_D", "GENKEY_R_F", NULL);
		m_ButtonSelectKey.ShowWindow(SW_HIDE);
		m_ButtonSelectKey.ShowWindow(SW_SHOW);
		button3 = 1;
	}

	// TODO/FIXME
	if (!m_bUpdateCrt)
		m_ButtonInfoCert.EnableWindow(TRUE);
	else
		m_ButtonInfoCert.EnableWindow(FALSE);

	if (button4 == -1) {
		// TODO/FIXME
		if (!m_bUpdateCrt) {
			m_ButtonSelectCert.LoadBitmaps("GENCERT_G_U", "GENCERT_G_D", "GENCERT_G_F", NULL);
			m_ButtonSelectCert.ShowWindow(SW_HIDE);
			m_ButtonSelectCert.ShowWindow(SW_SHOW);	
		}
		else {
			m_ButtonSelectCert.LoadBitmaps("GENCERT_R_U", "GENCERT_R_D", "GENCERT_R_F", NULL);
			m_ButtonSelectCert.ShowWindow(SW_HIDE);
			m_ButtonSelectCert.ShowWindow(SW_SHOW);
		}
		button4 = 1;
	}

	UpdateData(FALSE);

	if (m_hFocus)
		m_hFocus->SetFocus();
}

void CDlgSignatureDemo::OnEncrypt() 
{
#ifndef _UNSTABLE
	if(!m_osHash.noctets) return;

	memset(&m_osHashDER, 0, sizeof(OctetString));
	if(!m_Cert->Encode(m_osHash, m_osHashDER)) return;
	Big C, N, p, D, e;
	if(!m_Cert->GetParameter(N, p, e, D)) return;		
	Big Hash = from_binary(m_osHashDER.noctets, m_osHashDER.octets);
	Hash %= N;
	C = pow(Hash, D, N);

	delete[] m_osHashEnc.octets;
	memset(&m_osHashEnc, 0, sizeof(OctetString));	
	OctetString osC;
	osC.noctets = (bits(C)+7)/8;	
	osC.octets = new char[osC.noctets];
	to_binary(C, osC.noctets, osC.octets);
	m_osHashEnc.noctets = (bits(N)+7)/8 - osC.noctets;
	if(m_osHashEnc.noctets) 
	{
		m_osHashEnc.octets = new char[m_osHashEnc.noctets];
		memset(m_osHashEnc.octets, 0, m_osHashEnc.noctets);
	}
	Add2OString(&m_osHashEnc, osC.octets, osC.noctets);
	delete[] osC.octets;	
	m_bUpdateEnc = FALSE; 
	EnableButtons();
	//OnInfoHashEnc();
	m_ButtonInfoHashEnc.SetFocus();
#endif
}

void CDlgSignatureDemo::OnInfoHashEnc() 
{
#ifndef _UNSTABLE
	if (!m_osHashEnc.noctets || m_bUpdateEnc) return;

	CString Text;
	CString Encoding;
	CString Padding;
	CString Hash;
	CString HashDER;
	CString HashEnc;
	OctetString DER_Encoding;
	memset(&DER_Encoding, 0, sizeof(OctetString));
	m_Cert->GetDER_Encoding(DER_Encoding);
	dataToHexDump(DER_Encoding.octets, DER_Encoding.noctets, Encoding);
	dataToHexDump(m_osHashDER.octets, strlen(m_osHashDER.octets)+1, Padding);
	dataToHexDump(m_osHash.octets, m_osHash.noctets, Hash);
	dataToHexDump(m_osHashDER.octets, m_osHashDER.noctets, HashDER);
	dataToHexDump(m_osHashEnc.octets, m_osHashEnc.noctets, HashEnc);	

	UpdateData(TRUE);
	m_DisplayInfo.Empty();
	m_DisplayContent.LoadString(IDS_CONTENT_HASH_ENC);
	Text.Format(IDS_PADDING, Padding);
	m_DisplayInfo += Text;
	Text.Format(IDS_DERCODE, Encoding);
	m_DisplayInfo += Text;
	Text.Format(IDS_HASHVALUE, Hash);
	m_DisplayInfo += Text+"\r\n";
	Text.Format(IDS_HASHDER, HashDER);
	m_DisplayInfo += Text;
	Text.Format(IDS_BITLENGTH, m_osHashDER.noctets*8);
	m_DisplayInfo += Text+"\r\n";
	Text.Format(IDS_HASHENC, HashEnc);
	m_DisplayInfo += Text;
	Text.Format(IDS_BITLENGTH, m_osHashEnc.noctets*8);
	m_DisplayInfo += Text+"\r\n";
	UpdateData(FALSE);

	delete[] DER_Encoding.octets;
#endif
}

void CDlgSignatureDemo::OnSelectCert() 
{
#ifndef _UNSTABLE
	CDlgCertificateGeneration* CertDialog;
	CertDialog = new CDlgCertificateGeneration(this);

	CertDialog->InitRSA(m_Cert);
	if(CertDialog->DoModal()==IDOK) 
	{
		m_bUpdateSgn=TRUE;
		if(CertDialog->m_PSEIsExtern)
		{
			m_bUpdateEnc = TRUE;
			m_bUpdateCrt = FALSE;
		}
		else if(m_Cert->CreatePSE())
		{
			m_bUpdateCrt=FALSE;
		}
		button4 = button3 = -1;
		EnableButtons();
		//OnInfoCert();
		m_ButtonInfoCert.SetFocus();	
		ClearInfo();
	}
	m_bPSEIsExtern = CertDialog->m_PSEIsExtern;

	delete CertDialog;
#endif
}

void CDlgSignatureDemo::OnCombine() 
{
#ifndef _UNSTABLE
	if(!m_Message || !m_Message->noctets) return;
	delete[] m_SignText.octets;
	memset(&m_SignText, 0, sizeof(OctetString));
	CString UserKeyId;
	UserKeyId = m_Cert->CreateUserKeyID();
	if(PrintSignature(m_SignText, m_osHashEnc, "RSA", m_Cert->GetHashAlg(),UserKeyId))
	{
		m_bUpdateSgn = FALSE;
	}
	EnableButtons();
	//OnInfoSign();
	m_ButtonInfoSign.SetFocus();
#endif
}

void CDlgSignatureDemo::OnOK() 
{
#ifndef _UNSTABLE
	if(m_Message && m_SignText.noctets)
	{
		char outfile[128];
		CAppDocument* NewDoc;
		GetTmpName(outfile,"cry",".hex");
		Add2OString(&m_SignText, m_Message->octets, m_Message->noctets);
		theApp.SecudeLib.aux_OctetString2file(&m_SignText, outfile,2);
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		remove(outfile);
		m_sFileNameNew.Format(IDS_RSA_SIGNATURE_OF, m_Cert->GetHashAlg(), m_sFileName);
		NewDoc->SetTitle(m_sFileNameNew);

		CString Text;
		CString Msg;
		Msg.LoadString(IDS_CONGRATULATIONS);
		Text.Format(IDS_RSASGN_DOCNAME, m_sFileName);
		Msg += Text;		
		Text.Format(m_bPSEIsExtern? IDS_RSASGN_PSE_IMP: IDS_RSASGN_PSE, m_Cert->CreateUserKeyID());
		Msg += Text;
		Text.Format(IDS_RSASGN_ALG, m_Cert->GetHashAlg());
		Msg += Text;
		AfxMessageBox(Msg, MB_OK | MB_ICONINFORMATION);
	}
#endif
	CDialog::OnOK();
}

void CDlgSignatureDemo::ClearInfo() {
	UpdateData(TRUE);
	m_DisplayContent.Empty();
	m_DisplayInfo.Empty();	
	UpdateData(FALSE);
}

void CDlgSignatureDemo::OnInfoCert() 
{
#ifndef _UNSTABLE
	if(!m_Cert->PSEIsInitialized()) return;

	UpdateData(TRUE);
	m_DisplayContent.LoadString(IDS_CONTENT_CERT);
	m_DisplayInfo = m_Cert->GetCert();
	UpdateData(FALSE);
#endif
}

void CDlgSignatureDemo::OnInfoSign() 
{
#ifndef _UNSTABLE
	int srcSize = m_SignText.noctets;
	int destSize = (srcSize+m_nCols-1)/m_nCols * (11+m_nCols*4) - (srcSize % m_nCols? m_nCols - srcSize % m_nCols: 0);
	char *msgdata = new char[destSize+1];
	if (!HexDumpMem(msgdata, destSize, reinterpret_cast<unsigned char*>(m_SignText.octets), srcSize, m_nCols)) return;

	UpdateData(TRUE);
	m_DisplayContent.Format(IDS_CONTENT_SIGN, m_Cert->GetHashAlg(), m_sFileName);
	m_DisplayInfo = static_cast<CString>(msgdata);
	UpdateData(FALSE);
#endif
}


void CDlgSignatureDemo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen
		// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen
	dc.FillSolidRect(0,0,800,700,0x00C6C3C6);
	// Kein Aufruf von CDialog::OnPaint() f�r Zeichnungsnachrichten
}

BEGIN_MESSAGE_MAP(CDlgSignatureDemo, CDialog)
	ON_BN_CLICKED(IDC_SELECT_DOCUMENT, OnSelectDocument)
	ON_BN_CLICKED(IDC_INFO_DOCUMENT, OnInfoDocument)
	ON_BN_CLICKED(IDC_SELECT_KEY, OnSelectKey)
	ON_BN_CLICKED(IDC_INFO_KEY, OnInfoKey)
	ON_BN_CLICKED(IDC_SELECT_HASHALG, OnSelectHashAlg)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	ON_BN_CLICKED(IDC_INFO_HASH, OnInfoHash)
	ON_BN_CLICKED(IDC_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(IDC_INFO_HASH_ENC, OnInfoHashEnc)
	ON_BN_CLICKED(IDC_SELECT_CERT, OnSelectCert)
	ON_BN_CLICKED(IDC_INFO_ALG, OnInfoAlg)
	ON_BN_CLICKED(IDC_COMBINE, OnCombine)
	ON_BN_CLICKED(IDC_INFO_CERT, OnInfoCert)
	ON_BN_CLICKED(IDC_INFO_SIGN, OnInfoSign)
	ON_WM_PAINT()
END_MESSAGE_MAP()