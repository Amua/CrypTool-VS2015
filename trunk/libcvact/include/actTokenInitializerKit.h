// ---------------------------------------------------------------------------
// Name:      actTokenInitializerKit.h
// Product:   cv act library
// Purpose:   Factory functions to create specific ITokenInitializer instances.
//
// Copyright: (c) 2012 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/21/2012
// ---------------------------------------------------------------------------

#ifndef ACT_TokenInitializerKit_h
#define ACT_TokenInitializerKit_h

namespace act
{
	class ITokenInitializer;

	ITokenInitializer* CreateJCInitializer(ISCardOS*);
	ITokenInitializer* CreateV4Initializer(ISCardOS*);
	ITokenInitializer* CreateM4Initializer(ISCardOS*);
	ITokenInitializer* CreateACOSInitializer(ISCardOS*);
	ITokenInitializer* CreateStarCOSInitializer(ISCardOS*);
	ITokenInitializer* CreateSECCOSInitializer(ISCardOS*);

} // namespace act

#endif // ACT_TokenInitializerKit_h
