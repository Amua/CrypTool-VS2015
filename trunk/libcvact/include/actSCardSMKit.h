// ---------------------------------------------------------------------------
// Name:      actSCardSMKit.h
// Product:   cv act library
// Purpose:   Secure messaging factory methods.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  01/22/2013
// ---------------------------------------------------------------------------

#ifndef ACT_SCardSMKit_h
#define ACT_SCardSMKit_h

namespace act
{
	class ISCardSM;

	ISCardSM* CreateSMmEAC(const char*, const ITokenPIN*);
	ISCardSM* CreateSMTripleDES(const char*, const ITokenPIN*);

} // namespace act

#endif // ACT_SCardSMKit_h
