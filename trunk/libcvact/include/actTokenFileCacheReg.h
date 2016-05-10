// ---------------------------------------------------------------------------
// Name:      actTokenFileCacheReg.h
// Product:   cv act library
// Purpose:   Registry for ITokenFileCache factory methods.
//
// Copyright: (c) 2015 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  02/06/2015
// ---------------------------------------------------------------------------

#ifndef ACT_TokenFileCacheReg_h
#define ACT_TokenFileCacheReg_h

#include "actFactoryReg.h"

namespace act
{
	class	Blob;
	class	ISCardOS;
	class	ITokenFileCache;

	typedef ITokenFileCache*(*CreateTokenFileCachePtr)(const char*, ISCardOS*);
	typedef FactoryRegistry<ITokenFileCache, CreateTokenFileCachePtr> TokenFileCacheReg;

} // namespace act

#endif // ACT_TokenFileCacheReg_h
