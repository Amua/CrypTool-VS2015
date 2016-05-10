// ---------------------------------------------------------------------------
// Name:      actRefMethods.h
// Product:   cv act library
// Purpose:   Predeclares the act::refmethods. Needed for GCC.
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  1/18/2006
// ---------------------------------------------------------------------------

#ifndef ACT_RefMethods_H
#define ACT_RefMethods_H

#include "actEnv.h"
#if !defined(ACT_MSC)

namespace act
{
	class Reference;
	class IRefCounted;

	//
	// act::refmethods
	// Holds addRef and release methods for different reference counted types.
	namespace refmethods
	{
		void addRef(Reference&);
		void release(Reference&);

		void addRef(IRefCounted&);
		void release(IRefCounted&);

	} // namespace refmethods

} // namespace act

#endif // ACT_GCC
#endif // ACT_RefMethods_H
