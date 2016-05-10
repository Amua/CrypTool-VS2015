// ---------------------------------------------------------------------------
// Name:      actITokenFileMap.h
// Product:   cv act library
// Purpose:   ITokenFileMap interface declaration.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/22/2010
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenFileMap_h
#define ACT_ITokenFileMap_h

#include "actBlob.h"
#include "actIRefCounted.h"

namespace act
{
	class ITokenFile;

	//
	// ITokenFileMap
	class ITokenFileMap : public IRefCounted
	{
	public:
		virtual ITokenFileMap* Clone() const = 0;

		virtual ITokenFile* GetPath() const = 0;
		virtual ITokenFile* GetTokenFile(const Blob& path) = 0;
		virtual ITokenFile* GetRelativeTo(const Blob& path, ITokenFile* parent) = 0;
	};

} // namespace act

#endif // ACT_ITokenFileMap_h
