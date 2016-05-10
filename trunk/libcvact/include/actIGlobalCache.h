// ---------------------------------------------------------------------------
// Name:		actIGlobalCache.h
// Product:		cv act library
// Purpose:		Interface for subsystem global cache.
//
// Copyright:	(c) 2011 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche (MTE)
// Date:		09/16/2011
// ---------------------------------------------------------------------------

#ifndef ACT_IGlobalCache_h
#define ACT_IGlobalCache_h

#include "actBlob.h"

namespace act
{
	class IEventHandler;

	//
	// GlobalCacheMode
	enum GlobalCacheMode
	{
		CACHE_OFF							= 0x00,
		CACHE_R								= 0x01,
		CACHE_W								= 0x02,
		CACHE_RW							= CACHE_R | CACHE_W,
		CACHE_CLEAN							= 0x10 | CACHE_W,
	};

	//
	// IGlobalCache
	class IGlobalCache
	{
	public:
		virtual ~IGlobalCache() { }

		virtual bool  CacheSupported() const = 0;
		virtual ulong CacheRead(byte_array& cardid, ulong freshness, const char* name, Blob& value) const = 0;
		virtual ulong CacheWrite(byte_array& cardid, ulong freshness, const char* name, const Blob& value) = 0;
	};

} // namespace act

#endif // ACT_IGlobalCache_h
