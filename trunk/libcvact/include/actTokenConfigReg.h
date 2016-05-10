// ---------------------------------------------------------------------------
// Name:      actTokenConfigReg.h
// Product:   cv act library
// Purpose:   Registry for ITokenConfig factory methods.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  08/15/2013
// ---------------------------------------------------------------------------

#ifndef ACT_TokenConfigReg_h
#define ACT_TokenConfigReg_h

#include "actFactoryReg.h"

namespace act
{
	class	Blob;
	class	ITokenConfig;

	typedef ITokenConfig*(*CreateTokenConfigPtr)(const char*, const Blob&);
	typedef FactoryRegistry<ITokenConfig, CreateTokenConfigPtr>	TokenConfigReg;

} // namespace act

#endif // ACT_TokenConfigReg_h
