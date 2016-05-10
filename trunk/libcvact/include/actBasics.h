//////////////////////////////////////////////////////////////////////////////////
// Name:      actBasics.h
// Product:   cv act library
// Purpose:   integration of globally available identifiers
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

//
//! NOTE: MTE: Types (especially 'ulong') redefined to ensure required size and sign!
//! TODO: MTE: UBR: Ensure all required platforms are suppotred and tested BEFORE NEXT DELIVERY!

#ifndef ACT_Basics_h
#define ACT_Basics_h

#include "actEnv.h"

// Modern compilers make the distinction using __BYTE_ORDER__, define for backwards compatiblity if not given
#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) && defined(__BYTE_ORDER__)
#	if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#		define __LITTLE_ENDIAN__
#	elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#		define __BIG_ENDIAN__
#	endif
#endif


#if !defined(ACT_LITTLE_ENDIAN)
#	 define	 ACT_LITTLE_ENDIAN
#endif

#if defined(__BIG_ENDIAN__) \
||	defined(__sun__)   \
||	defined(__sparc)   \
||	defined(__sparc__) \
||	defined(__ppc__)   \
||	defined(__ppc64__)
#	undef	ACT_LITTLE_ENDIAN
#endif	// __sun__

#if !defined(NO_STL_SUPPORT)
#	 include <cstddef>							// used for ptrdiff_t, size_t
#else
#	if !defined(_PTRDIFF_T_DEFINED)
#		define  _PTRDIFF_T_DEFINED
		typedef int				ptrdiff_t;
#	endif
#	if !defined(_SIZE_T_DEFINED)
#		define  _SIZE_T_DEFINED
		typedef unsigned int	size_t;
#	endif
#endif

#if !defined(ACT_MSC)
#	include <sys/types.h>
#	include <inttypes.h>
#endif

#include <actTypeTags.h>

namespace act
{
#	if defined(__MWERKS__)
		using					std::size_t;
		using					std::ptrdiff_t;
#	else
		using					::size_t;
		using					::ptrdiff_t;
#	endif

#	if defined(ACT_MSC)
		typedef unsigned short	ushort;
		typedef unsigned long	ulong;			//!< has to be a 32bit unsigned integer type!
#	else
		typedef uint16_t		ushort;
		typedef	uint32_t		ulong;			//!< has to be a 32bit unsigned integer type!
#	endif

	typedef unsigned char		uchar;
	typedef unsigned int		uint;

	typedef uchar				uint8;
	typedef ushort				uint16;
	typedef ulong				uint32;

	typedef uchar				byte;			//!< has to be compatible with \a uchar!
	typedef ushort				word;			//!< has to be compatible with \a ushort!
	typedef ulong				dword;			//!< has to be compatible with \a ulong!

	typedef int					paramid_t;
	typedef int					status_t;
	typedef int					mode_t;
	typedef int					export_t;

#if defined(__GNUC__) \
||	defined(__clang__) \
||	defined(__MWERKS__)
	typedef unsigned long long	uint64;
#	define U64(x)				x##ULL
#else
	typedef unsigned __int64	uint64;
#	define U64(x)				x##ui64
#endif

	const export_t				DEFAULT = 0;

	//
	// scoped_delete<>
	template
	<
		typename TypeT,
		typename ContextT = void,				//!< BaseT, DestructF, depending on spezialization.
		typename TypeTagT = TypeTag<ContextT>	//!< Always TypeTag<> for implicit / explicit specialization selection.
	>
	struct scoped_delete
	{ };

	struct null_type  { };						//!< Default empty, unsued template parameter, etc.

	template<class>
	struct null_type1 { };						//!< \sa null_type

} // namespace act

#endif // ACT_Basics_h
