//////////////////////////////////////////////////////////////////////////
// Name:      actEnv.h
// Product:   cv act library
// Purpose:   Operating System environment
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/23/2009
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Env_h
#define ACT_Env_h
#pragma once

//! \brief 64-Bit detection
// ---------------------------------------------------------------------------
#if		defined(_WIN64) || \
		defined(__LP64__) || \
		defined(__alpha__) || \
		defined(__ia64__) || \
		defined(__ppc64__) || \
		defined(__s390x__) || \
		defined(__x86_64__)
#		define	ACT_64
#endif

//! \brief cygwin
// ---------------------------------------------------------------------------
#if		defined(__CYGWIN__)
#		define  ACT_CYGWIN
#endif

//! \brief mingw
// ---------------------------------------------------------------------------
#if		defined(__MINGW32__)
#		define	ACT_MINGW
#endif

//! \brief Platform detection
// ---------------------------------------------------------------------------
#if		defined(ACT_WIN32) || \
		defined(ACT_POSIX) || \
		defined(ACT_SOLARIS) || \
		defined(ACT_MACOSX) || \
		defined(ACT_IOS) || \
		defined(ACT_WIN32_WCE)
//		do nothing

#elif	defined(_WIN32_WCE) && _WIN32_WCE >= 0x500
#		define  ACT_WIN32
#		define  ACT_WIN32_WCE

#elif	defined(WIN32) && !defined(__CYGWIN__)
#		define  ACT_WIN32

#elif	defined(_MSC_VER) || \
		defined(__BORLANDC__) || \
		defined(__BCPLUSPLUS__) || \
		defined(__MINGW32__)
#		define  ACT_WIN32

#elif	defined(__ANDROID__)
#		define  ACT_POSIX
#		define  ACT_ANDROID
#		define	ACT_LINUX

#elif	defined(__linux__)
#		define  ACT_POSIX
#		define	ACT_LINUX

#elif	defined(__CYGWIN__) || \
		defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
		defined(__hpux) || \
		defined(__sgi)
#		define  ACT_POSIX

#elif	defined(_POSIX_SOURCE) || \
		defined(_XOPEN_SOURCE) 
#		define  ACT_POSIX

#elif	defined(__sun)
#		define	ACT_POSIX
#		define  ACT_SOLARIS

#elif	defined(__APPLE__)			/* From here the real agony begins. */
#		define	ACT_POSIX
#		define	ACT_MACOSX
#	include "TargetConditionals.h"
#	if (TARGET_OS_IPHONE == 1)
#		define	ACT_IOS				/* Treat iOS as a flavor of MacOSX, just as 'they' wish to advertise it */
#	elif (TARGET_IPHONE_SIMULATOR == 1)
#		define	ACT_IOS
#		define	ACT_IPHONE_SIM
#	else							/* vanilla MacOSX */
		/* Broken PCSC under MacOSX 10.10. Just until (cr)Apple fixed it. Which will be never, I'd say. */
#		define	ACT_MAC_BROKEN_PCSC
#	endif

#else
#		error	unable to deteced system environment

#endif

enum	timeout_t
		{
			WAIT_DONT_WAIT					=  0,
			WAIT_INFINITE					= -1,
			WAIT_FOR_REFRESH				=  1000,
			WAIT_FOR_SERVICE_START			=  1000,
			WAIT_FOR_THREAD_START			=  50,
			WAIT_FOR_THREAD_STOP			=  100,
		};

//
//! \brief Common
// ---------------------------------------------------------------------------
#if !defined(ACT_CPP_VER)
#	 define  ACT_CPP_VER(major, minor, pl)	(((major) << 24) + ((minor) << 16) + (pl))
#endif
#if !defined(ACT_STRING)
#    define  ACT_STRING(x)					#x
#    define  ACT2STRING(x)					ACT_STRING(x)
#endif
#if !defined(ACT_CAT)
#	 define  ACT_CAT__(a, b)				a ## b
#	 define  ACT_CAT(a, b)					ACT_CAT__(a, b)
#endif

//
//! \brief Initialize supported compiler version with 0
// ---------------------------------------------------------------------------
#ifndef			ACT_CPP_ENV
#	define		ACT_CPP_ENV
#	define      ACT_MSC_VER					0
#	define      ACT_GCC_VER					0
#	define      ACT_CLANG_VER				0
#endif

//
//! \brief Compiler definition
// ---------------------------------------------------------------------------
#if	defined(_MSC_VER)
#	define		ACT_MSC
#	undef		ACT_MSC_VER					//!< clear version
#	define		ACT_MSC_VER					ACT_CPP_VER(_MSC_FULL_VER / 10000000, (_MSC_FULL_VER / 100000) % 100, _MSC_FULL_VER % 1000000)
#	if		(	ACT_MSC_VER				<	ACT_CPP_VER(14, 0, 0)) //!< min. version
#		error	min. visual studio 2008 required
#	endif
#	define		ACT_STDEXT_NS				std
#	define		ACT_STDEXT_INC(file)		<file>
#	if		(	ACT_MSC_VER				>=	ACT_CPP_VER(14, 0, 50320))
#		define	ACT_DEPRECATED(msg)			__declspec(deprecated(msg))
#	else
#		define	ACT_DEPRECATED(msg)			__declspec(deprecated)
#	endif
#	if	defined(ACT_EMPTY_TEMPLATE)
#	elif	(	ACT_MSC_VER				<	ACT_CPP_VER(14, 0, 0))
#		define	ACT_EMPTY_TEMPLATE			template<>
#	endif

#elif defined(__clang__)
#	define		ACT_CLANG
#	undef		ACT_CLANG_VER				//!< clear version
#	define		ACT_CLANG_VER				ACT_CPP_VER(__clang_major__, __clang_minor__, __clang_patchlevel__)
#	if		(	ACT_CLANG_VER			<	ACT_CPP_VER(3, 0, 0)) //!< min. version
#		error	min. clang version 3.0.0 required
#	endif
#	define		ACT_STDEXT_NS				__gnu_cxx
#	define		ACT_STDEXT_INC(file)		<ext/file>

#elif defined(__GNUC__)
#	define		ACT_GCC
#	undef		ACT_GCC_VER					//!< clear version
#	define		ACT_GCC_VER					ACT_CPP_VER(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#	if		(	ACT_GCC_VER				<	ACT_CPP_VER(4, 2, 1)) //!< min. version
#		error	min. gcc version 4.2.1 required
#	endif
#	define		ACT_STDEXT_NS				__gnu_cxx
#	define		ACT_STDEXT_INC(file)		<ext/file>
#	if		(	ACT_GCC_VER				>=	ACT_CPP_VER(3, 1, 0))
#		define	ACT_DEPRECATED(msg)			__attribute__((__deprecated__))
#	endif

#else
#	define		ACT_STDEXT_NS
#	define		ACT_STDEXT_INC(file)

#endif

//! \brief Ensure availability of required macros.
// ---------------------------------------------------------------------------
#ifndef			ACT_FACTORY
#	define		ACT_FACTORY(Type)			Create##Type
#endif
#ifndef			ACT_DEPRECATED
#	define		ACT_DEPRECATED(msg)
#endif
#ifndef			ACT_UNSUED_PARAM
#	define		ACT_UNSUED_PARAM(p)			do { (p) = (p); } while(false)
#endif
#ifndef			ACT_EMPTY_TEMPLATE
#	define		ACT_EMPTY_TEMPLATE		/*	template<> */
#endif

//! \brief Win32 calling conventions
// ---------------------------------------------------------------------------
#ifdef			ACT_WIN32
#	define		ACT_CDECL					__cdecl
#	define		ACT_STDCALL					__stdcall
#else
#	define		ACT_CDECL
#	define		ACT_STDCALL
#endif

//! \brief MSVC++ special
// ---------------------------------------------------------------------------
#ifdef			ACT_MSC
#	define		ACT_MSC_WARNING_POP()		__pragma(warning(pop))
#	define		ACT_MSC_WARNING_PUSH()		__pragma(warning(push))
#	define		ACT_MSC_WARNING_DISABLE(w)	  ACT_MSC_WARNING_PUSH() \
											__pragma(warning(disable : w))
//	Avoid MSVC++ warning LNK4221.
#	define		ACT_MSC_NO_LNK4221			namespace { char act_lnk4221##__LINE__; }

#else
#	define		ACT_MSC_WARNING_POP()
#	define		ACT_MSC_WARNING_PUSH()
#	define		ACT_MSC_WARNING_DISABLE(w)
#	define		ACT_MSC_NO_LNK4221

#endif

//
//! \brief Markers for API semantics, default enabled
// ---------------------------------------------------------------------------
#define			ACT_SAL_ENABLED				1
#define			ACT_SAL_DISABLED			0
#ifndef			ACT_SAL_DEFAULT
#	define		ACT_SAL_DEFAULT				ACT_SAL_ENABLED
#endif
#if				ACT_SAL_DEFAULT != ACT_SAL_ENABLED && \
				ACT_SAL_DEFAULT != ACT_SAL_DISABLED
#	undef		ACT_SAL_DEFAULT
#	define		ACT_SAL_DEFAULT				ACT_SAL_DISABLED
#endif
#if			(	ACT_MSC_VER				>=	ACT_CPP_VER(14, 0, 0))
#	if ( ACT_MSC_VER < ACT_CPP_VER(19, 0, 0))
		// Leave selection of SAL flavor to IDE for 2015 and up.
#		if !defined(_USE_ATTRIBUTES_FOR_SAL)
#			define	_USE_ATTRIBUTES_FOR_SAL		ACT_SAL_DEFAULT
#		endif
#	endif
#	include		<sal.h>
#	define		ACT_SAL						ACT_SAL_DEFAULT
#	if  defined(ACT_SAL)
#		pragma	warning						(disable : 6011 6246)
#	endif
#	define		ACT_IN						__in
#	define		ACT_OUT						__out
#	define		ACT_INOUT					__inout
#	define		ACT_IN_OPT					__in_opt
#	define		ACT_OUT_OPT					__out_opt
#	define		ACT_INOUT_OPT				__inout_opt
#	define		ACT_IN_BC(size)				__in_bcount(size)
#	define		ACT_IN_BC_OPT(size)			__in_bcount_opt(size)
#	define		ACT_IN_EC_OPT(size)			__in_ecount_opt(size)
#	define		ACT_OUT_BC(size)			__out_bcount(size)
#	define		ACT_OUT_BC_OPT(size)		__out_bcount_opt(size)
#	define		ACT_OUT_EC_OPT(size)		__out_ecount_opt(size)
#	define		ACT_INOUT_BC(size)			__inout_bcount(size)
#	define		ACT_INOUT_BC_OPT(size)		__inout_bcount_opt(size)
#	define		ACT_INOUT_EC_OPT(size)		__inout_ecount_opt(size)
#	define		ACT_RESERVED				__reserved
#	define		ACT_NULL_TERMINATED			__nullnullterminated
#	if defined(_Printf_format_string_)
#		define	ACT_PRINTF_FORMAT_STRING	_Printf_format_string_
#	else
#		define	ACT_PRINTF_FORMAT_STRING	__format_string
#	endif
#else
#	define		ACT_SAL						ACT_SAL_DISABLED
#	define		ACT_IN
#	define		ACT_OUT
#	define		ACT_INOUT
#	define		ACT_IN_OPT
#	define		ACT_OUT_OPT
#	define		ACT_INOUT_OPT
#	define		ACT_IN_BC(size)
#	define		ACT_IN_BC_OPT(size)
#	define		ACT_IN_EC_OPT(size)
#	define		ACT_OUT_BC(size)
#	define		ACT_OUT_BC_OPT(size)
#	define		ACT_OUT_EC_OPT(size)
#	define		ACT_INOUT_BC(size)
#	define		ACT_INOUT_BC_OPT(size)
#	define		ACT_INOUT_EC_OPT(size)
#	define		ACT_RESERVED
#	define		ACT_NULL_TERMINATED
#	define		ACT_PRINTF_FORMAT_STRING
#endif

//
//! \brief DLL/Shared Object symbol export/import attribte
// ---------------------------------------------------------------------------
#if defined(ACT_MSC)
#	define		ACT_DYNLIB_EXPORT			_declspec(dllexport)
#	define		ACT_DYNLIB_IMPORT			_declspec(dllimport)

#elif defined(ACT_GCC) && !defined(ACT_MINGW)
#	define		ACT_DYNLIB_EXPORT			__attribute__((visibility("default")))
#	define		ACT_DYNLIB_IMPORT

#else
#	define		ACT_DYNLIB_EXPORT
#	define		ACT_DYNLIB_IMPORT

#endif

#if  defined(__cplusplus)
//
//! \brief   ACT_STRONGLY_TYPED_ENUM
//! \details Defined if the "C++0x" compiler supports strongly typed enumerations.
// ---------------------------------------------------------------------------
#	if !defined(ACT_STRONGLY_TYPED_ENUM) && !defined(ACT_MACOSX)
		// TODO: MTE: set to gcc 4.4 again!
#		if(ACT_MSC_VER   >= ACT_CPP_VER(16, 0, 0)	/* VS 2010		*/ \
		|| ACT_GCC_VER   >= ACT_CPP_VER( 8, 4, 0)	/* GCC   4.4	*/ \
		|| ACT_CLANG_VER >= ACT_CPP_VER( 3, 0, 0))	/* CLang 3.0	*/
#		define  ACT_STRONGLY_TYPED_ENUM
#		endif
#	endif
//
//! \brief   ACT_ENUM_TYPE
//! \details Postfix for enum declarations specifying the type.
// ---------------------------------------------------------------------------
#	if !defined(ACT_STRONGLY_TYPED_ENUM)
#		define  ACT_ENUM_TYPE(type)
#	else
#		define  ACT_ENUM_TYPE(type)			: type
#	endif

#if !defined(ACT_DEFINE_ENUM_FLAG_OPERATORS)
//
//! \brief	 DEFINE_ENUM_FLAG_OPERATORS
//! \details Define operator overloads to enable bit operations on enum
//!          values that are used to define flags.
//!          Use \ref ACT_DEFINE_ENUM_FLAG_OPERATORS(T) to enable these
//!          operators on type T.
//! \since	 Microsoft Windows SDK for Windows 7
//! \sa		 "winnt.h"
// ---------------------------------------------------------------------------
#		define	ACT_DEFINE_ENUM_FLAG_OPERATORS(enum_t) extern "C++" \
		{ \
			inline enum_t  operator |  (enum_t  a, enum_t b) { return  enum_t(((int) a)    |  ((int) b)); } \
			inline enum_t& operator |= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) |= ((int) b)); } \
			inline enum_t  operator &  (enum_t  a, enum_t b) { return  enum_t(((int) a)    &  ((int) b)); } \
			inline enum_t& operator &= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) &= ((int) b)); } \
			inline enum_t  operator ^  (enum_t  a, enum_t b) { return  enum_t(((int) a)    ^  ((int) b)); } \
			inline enum_t& operator ^= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) ^= ((int) b)); } \
			inline enum_t  operator ~  (enum_t  a) { return  enum_t(~((int) a)); } \
		}
#	endif

#else
#	if !defined(ACT_DEFINE_ENUM_FLAG_OPERATORS)
#		define	ACT_DEFINE_ENUM_FLAG_OPERATORS(enum_t)
#	endif
#	if !defined(ACT_STRONGLY_TYPED_ENUM)
#		define  ACT_ENUM_TYPE(type)
#	endif

#endif	// __cplusplus
#endif	// ACT_Env_h
