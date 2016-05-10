// ---------------------------------------------------------------------------
// Name:		actITokenFileCache.h
// Product:		cv act library
// Purpose:		Interface used for FID based binary cache.
//            
// Copyright:	(c) 2008 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche
// Date:		11/07/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenFileCache_h
#define ACT_ITokenFileCache_h

#include "actIRefCounted.h"

#include "actMove.h"
#include "actBlob.h"

#include <string>

namespace act
{
	class Blob;
	class ISCardOS;

	enum CFType						//!< card freshness type
	{
		CF_NONE				= -1,

		CF_PIN				= 0,	//!< pin change count
		CF_CONTAINER		= 1,	//!< change count for container
		CF_FILES			= 2,	//!< change count everthing else ...
	};

	//
	// ITokenFileCache
	// -----------------------------------------------------------------------
	class ITokenFileCache : public IRefCounted
	{
	public:
		virtual bool		InitCache(ISCardOS* os) = 0;
		virtual void		Reset() = 0;

		virtual void		SetRootPath(const std::string& path) = 0;		//!< root path of global file system cache

		virtual void		EnableGlobalCache() = 0;
		virtual void		DisableGlobalCache() = 0;
		virtual bool		GlobalCacheEnabled() const = 0;

		virtual const Blob&	GetCardID() const = 0;
		virtual const Blob&	GetCardCF() const = 0;

		virtual Blob		GetCache(const Blob& filepath, CFType cache_type) const = 0;
		virtual Blob&		RefCache(const Blob& filepath, CFType cache_type) const = 0;

		virtual void		PutCache(const Blob& filepath, const Blob& value, CFType cache_type) const = 0;
		virtual void		PutCache(const Blob& filepath, move_from<Blob> value, CFType cache_type) const = 0;
	};

} // namespace act

#endif // ACT_ITokenFileCache_h
