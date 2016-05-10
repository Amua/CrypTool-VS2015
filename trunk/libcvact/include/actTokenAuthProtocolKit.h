// ---------------------------------------------------------------------------
// Name:      actTokenAuthProtocolKit.h
// Product:   cv act library
// Purpose:   Factory functions to create specific ITokenAuthProtocol objects.
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  14/10/2008
// ---------------------------------------------------------------------------

#ifndef ACT_TokenAuthProtocolKit_h
#define ACT_TokenAuthProtocolKit_h

namespace act
{
	class ITokenAuthProtocol;

	ITokenAuthProtocol* CreatePACEPkiMD(const char*);		// mEACv2 base PACE with MD compatible configuration.

	ITokenAuthProtocol* CreatePACEmEACv2x(const char*);		// mEACv2-PACE
	ITokenAuthProtocol* CreatePCSCPACEmEACv2x(const char*);	// mEACv2-PCSC-PACE
	ITokenAuthProtocol* CreateTAmEACv201(const char*);		// mEACv2-TA
	ITokenAuthProtocol* CreateCAmEACv201(const char*);		// mEACv2-CA

	ITokenAuthProtocol* CreateBACmEACv1x(const char*);		// mEACv1-BAC

	ITokenAuthProtocol* CreateTokenAuthTCOSv301QES(const char* name);	// TCOS 3.0.1 SM for QES

} // namespace act

#endif // ACT_TokenAuthProtocolKit_h
