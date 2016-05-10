// ---------------------------------------------------------------------------
// Name:      actSCardError.h
// Product:   cv act library
// Purpose:   Smartcard Error definitions and functions
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  12/09/2009
// ---------------------------------------------------------------------------

#ifndef ACT_SCardError_h
#define ACT_SCardError_h

#include "actBasics.h"

namespace act
{
	enum SCardOSErrorCodes
	{
		SCARD_ERR_MASK						= 0xffff0000,
		SCARD_ERR_OS_FIRST					= 0x00010000,

		SCARD_ERR_OS_RESIZE_FAILED			= SCARD_ERR_OS_FIRST + (0 << 16),		// "resize file failed"
		SCARD_ERR_OS_RESTORE_FAILED			= SCARD_ERR_OS_FIRST + (1 << 16),		// "restore file failed"

		// Add additional SmartcardException error codes here
		SCARD_ERR_OS_LAST					= SCARD_ERR_OS_FIRST + (256 << 16),
	};

	enum SCardTokenErrorCodes
	{
		SCARD_ERR_TK_FIRST					= SCARD_ERR_OS_LAST,

		SCARD_ERR_TK_INVALID_FID			= SCARD_ERR_TK_FIRST + (0 << 16),		// "invalid fid"
		SCARD_ERR_TK_NO_FID_LEFT			= SCARD_ERR_TK_FIRST + (1 << 16),		// "no object or file identifier left"
		SCARD_ERR_TK_NO_PUBKEY_REC_FOUND	= SCARD_ERR_TK_FIRST + (2 << 16),		// "no public key record found"

		// Add additional SmartcardException error codes here

		SCARD_ERR_TK_LAST					= SCARD_ERR_TK_FIRST + (256 << 16),
	};

	// extract
	inline ulong scard_err(ulong code)		{ return code & SCARD_ERR_MASK; }

	template<typename ExceptionT>
	inline ulong scard_err(ExceptionT& e)	{ return scard_err(e.code());	}

	// combine
	inline ulong scard_err(word sw1sw2, ulong code) { return code | sw1sw2; }

	template<typename ExceptionT>
	inline ulong scard_err(ExceptionT& e, ulong code)
	{
		return scard_err(word(e.code() & ~SCARD_ERR_MASK), code);
	}

} // namespace act

#endif	// ACT_SCardError_h
