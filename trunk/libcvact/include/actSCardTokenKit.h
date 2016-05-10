// ---------------------------------------------------------------------------
// Name:      actSCardTokenKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS and SCardToken objects
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/14/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardTokenKit_h
#define ACT_SCardTokenKit_h

namespace act
{
	class ISCardOS;
	class SCardToken;

	bool IsV4cvProfile(ISCardOS* os);
	SCardToken* CreateV4cvProfile(ISCardOS* os, SCardToken* prev);

	bool IsV4cvECProfile(ISCardOS* os);
	SCardToken* CreateV4cvECProfile(ISCardOS* os, SCardToken* prev);

	bool IsSigntrustToken(ISCardOS* os);
	SCardToken* CreateSigntrustToken(ISCardOS* os, SCardToken* prev);

	bool IsM4cvProfile(ISCardOS* os);
	SCardToken* CreateM4cvProfile(ISCardOS* os, SCardToken* prev);

	bool IsACOScvProfile(ISCardOS* os);
	SCardToken* CreateACOScvProfile(ISCardOS* os, SCardToken* prev);

	bool IsM4cvECProfile(ISCardOS* os);
	SCardToken* CreateM4cvECProfile(ISCardOS* os, SCardToken* prev);

	bool IsM4cvMoCProfile(ISCardOS* os);
	SCardToken* CreateM4cvMoCProfile(ISCardOS* os, SCardToken* prev);

	bool IsJavaCardAppletManager(ISCardOS* os);
	SCardToken* CreateJavaCardAppletManager(ISCardOS* os, SCardToken* prev);

	bool IsJCProfile(ISCardOS* os);
	SCardToken* CreateJCProfile(ISCardOS* os, SCardToken* prev);

	// PKCS#15 Profiles
	bool IsM4PKCS15Profile(ISCardOS* os);
	SCardToken* CreateM4PKCS15Profile(ISCardOS* os, SCardToken* prev);

	bool IsV4PKCS15Profile(ISCardOS* os);
	SCardToken* CreateV4PKCS15Profile(ISCardOS* os, SCardToken* prev);

	bool IsV4PKCS15ECProfile(ISCardOS* os);
	SCardToken* CreateV4PKCS15ECProfile(ISCardOS* os, SCardToken* prev);

	bool IsJCPKCS15Profile(ISCardOS* os);
	SCardToken* CreateJCPKCS15Profile(ISCardOS* os, SCardToken* prev);

	bool IsJCPKCS15v2Profile(ISCardOS* os);
	SCardToken* CreateJCPKCS15v2Profile(ISCardOS* os, SCardToken* prev);

	bool IsJCPKCS15ECProfile(ISCardOS* os);
	SCardToken* CreateJCPKCS15ECProfile(ISCardOS* os, SCardToken* prev);

	bool IsJCPKCS15v2ECProfile(ISCardOS* os);
	SCardToken* CreateJCPKCS15v2ECProfile(ISCardOS* os, SCardToken* prev);

	bool IsACOSPKCS15Profile(ISCardOS* os);
	SCardToken* CreateACOSPKCS15Profile(ISCardOS* os, SCardToken* prev);

	bool IsStarCOSPKCS15Profile(ISCardOS* os);
	SCardToken* CreateStarCOSPKCS15Profile(ISCardOS* os, SCardToken* prev);

	bool IsStudentCardProfile(ISCardOS* os);
	SCardToken* CreateStudentCardProfile(ISCardOS* os, SCardToken* prev);

	bool IsTCOSPKCS15Profile(ISCardOS* os);
	SCardToken* CreateTCOSPKCS15Profile(ISCardOS* os, SCardToken* prev);

	// PACE
	SCardToken* CreatePACEToken(ISCardOS* os, SCardToken* prev);

	bool IsMDPACEToken(ISCardOS* os);
	SCardToken* CreateMDPACEToken(ISCardOS* os, SCardToken* prev);

	// Passport
	bool IsEPAProfile(ISCardOS* os);
	SCardToken* CreateEPAToken(ISCardOS* os, SCardToken* prev);
	bool IsEBAProfile(ISCardOS* os);
	SCardToken* CreateEBAToken(ISCardOS* os, SCardToken* prev);

} // namespace act

#endif // ACT_SCardTokenKit_h
