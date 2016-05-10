// ---------------------------------------------------------------------------
// Name:      actTokenFileCacheKit.h
// Product:   cv act library
// Purpose:   Common ITokenFileCache factory methods for 'actInit.h'.
//
// Copyright: (c) 2015 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  02/06/2015
// ---------------------------------------------------------------------------

#ifndef ACT_TokenFileCacheKit_h
#define ACT_TokenFileCacheKit_h

#include "actEnv.h"

namespace act
{
	class Blob;
	class ITokenFileCache;

	ITokenFileCache* ACT_FACTORY(TokenFileCache)(const char*, ISCardOS*);	//!< Default
	ITokenFileCache* ACT_FACTORY(TCOSSigCardV2)(const char*, ISCardOS*);	//!< TCOS 3.0 Signature Card V2.0 R1 with Netkey application
	ITokenFileCache* ACT_FACTORY(TCOSSigCardV1)(const char*, ISCardOS*);	//!< TCOS 3.0 Signature Card V1.0 with Netkey application

}		// namespace act
#endif	// ACT_TokenFileCacheKit_h
