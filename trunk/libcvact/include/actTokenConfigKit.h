// ---------------------------------------------------------------------------
// Name:      actTokenConfigKit.h
// Product:   cv act library
// Purpose:   Common ITokenConfig factory methods for 'actInit.h'.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  08/15/2013
// ---------------------------------------------------------------------------

#ifndef ACT_TokenConfigKit_h
#define ACT_TokenConfigKit_h

#include "actEnv.h"

namespace act
{
	class Blob;
	class ITokenConfig;

	ITokenConfig* ACT_FACTORY(mEACConfig)(const char*, const Blob&);	//!< mEAC specific
	ITokenConfig* ACT_FACTORY(TokenConfig)(const char*, const Blob&);	//!< Default
	ITokenConfig* ACT_FACTORY(NIMC01Config)(const char*, const Blob&);

}		// namespace act
#endif	// ACT_TokenConfigKit_h
