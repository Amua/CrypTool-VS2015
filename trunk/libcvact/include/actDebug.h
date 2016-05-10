//////////////////////////////////////////////////////////////////////////
// Name:      actDebug.h
// Product:   cv act library
// Purpose:   Integration of globally available debug macros and functions
//
// Copyright: (c) 2005 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  12/15/2005
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Debug_h
#define ACT_Debug_h

#include "actEnv.h"
#include "actBasics.h"
#include "actThread.h"
#include "actLocation.h"

#include <cstdarg>

#if defined(_DEBUG)
#	define		ACT_DEBUG								_DEBUG
#endif

//
// ACT_NOOP use for semicolon terminated non operating macros.
// ---------------------------------------------------------------------------
#if defined(ACT_MSC)
#	if	(	ACT_MSC_VER								>=	ACT_CPP_VER(12, 10, 0))
#		define	ACT_NOOP(...)							__noop
#	else
#		define	ACT_NOOP								((void) 0)
#	endif
// MSVC specific
#	if !defined(ACT_DEBUG_NEW)
#		if defined(ACT_DEBUG) && !defined(ACT_WIN32_WCE)
#			include <crtdbg.h>
#			define	ACT_DEBUG_MEMORY_TYPE				0xAFEC
#			define	ACT_DEBUG_MEMORY_BLOCK				((ACT_DEBUG_MEMORY_TYPE << 16) | _CLIENT_BLOCK)
#			define	ACT_DEBUG_NEW						new(ACT_DEBUG_MEMORY_BLOCK, __FILE__, __LINE__)
#		else
#			define	ACT_DEBUG_NEW						new
#		endif
#	endif
#else
#	define		ACT_NOOP(...)							((void) 0)
#	define		ACT_DEBUG_NEW							new
#endif

//
// Declare all debug macros for release builds.
// ---------------------------------------------------------------------------
#if defined(ACT_DEBUG)
#	if !defined(ACT_DEBUG_NS)
#		define	ACT_DEBUG_NS							dbg
#	endif
#	if defined(ACT_UNDER_CE)
#		define	ACT_ASSERT								ACT_NOOP
#		define	ACT_ASSERT_ALWAYS(msg, line, file)		ACT_NOOP
#	endif
#	define		ACT_DEBUG_STRING(str)					str
#	define		ACT_DEBUG_PARAM(param)					param
#	define		ACT_DEBUG_NAME(name)					ACT_CAT(ACT_DEBUG_NS, ACT_CAT(_, name))
#	define		ACT_DEBUG_SOURCE						act::FileAndLine(__FILE__, __LINE__)
#	define		ACT_NOT_IMPLEMENTED(where)				throw act::NotImplementedException(0, where) << ACT_DEBUG_SOURCE()
#else
#	define		ACT_DEBUG_NAME(name)					ACT_NOOP
#	define		ACT_DEBUG_OUTPUT(trace, location)		ACT_NOOP
#	define		ACT_DEBUG_SOURCE						act::Location<>::Unknown
#	define		ACT_NOT_IMPLEMENTED(where)				throw act::NotImplementedException(0, where)
#	define		ACT_DEBUG_STRING(str)					""
#	define		ACT_DEBUG_PARAM(param)
#	define		ACT_TRACE								ACT_NOOP
#	define		ACT_TRACELOG							ACT_NOOP
#	define		ACT_ASSERT								ACT_NOOP
#	define		ACT_ASSERT_ALWAYS						ACT_NOOP
#	define		ACT_ASSERT_ON_THROW						ACT_NOOP
#endif // ACT_DEBUG

//
// Assertion Macros for ACT_ASSERT.
// ---------------------------------------------------------------------------
#if !defined(UNREACHED)
#    define  UNREACHED									(0)
#endif
#if !defined(UNEXPECTED)
#    define  UNEXPECTED									(0)
#endif
#if !defined(NOT_SUPPORTED)
#    define  NOT_SUPPORTED								(0)
#endif
#if !defined(NOT_IMPLEMENTED)
#    define  NOT_IMPLEMENTED							(0)
#endif
#if !defined(UNEXPECTED_EXCEPTION)
#    define  UNEXPECTED_EXCEPTION						(0)
#endif

//
// ACT_ASSERT
// ---------------------------------------------------------------------------
#if !defined(ACT_ASSERT)
#	if defined(ACT_MSC)
#		include <crtdbg.h>
#		define	ACT_ASSERT								_ASSERTE
#	elif defined(ACT_USE_ASSERT_ON_POSIX)
#		include <assert.h>
#		define	ACT_ASSERT								assert
#	else
#		define	ACT_ASSERT								ACT_NOOP
#	endif
#endif // ACT_ASSERT

//!
//! \brief ACT_ASSERT_ALWAYS
// ---------------------------------------------------------------------------
#if !defined(ACT_ASSERT_ALWAYS)
#	if defined(ACT_MSC)
#		include <crtdbg.h>
#		define	ACT_ASSERT_ALWAYS(msg, file, line)		_RPT_BASE((_CRT_ASSERT, file, line, 0, msg))
#	else
#		include <assert.h>
#		define	ACT_ASSERT_ALWAYS(msg, file, line)		assert(f == 0)
#	endif
#endif // ACT_ASSERT_ALWAYS

//!
//! \brief   ACT_DEFAULT_TRACE
//! \details Force definition of ACT_TRACE, ACT_TRACELOG and ACT_DEBUG_OUTPUT
// ---------------------------------------------------------------------------
#if defined(ACT_DEFAULT_TRACE)
#	ifdef		ACT_TRACE
#		undef	ACT_TRACE
#	endif
#	ifdef		ACT_TRACELOG
#		undef	ACT_TRACELOG
#	endif
#	ifdef		ACT_DEBUG_OUTPUT
#		undef	ACT_DEBUG_OUTPUT
#	endif
#endif // ACT_ENABLE_TRACE

//!
//! \brief ACT_TRACE
// ---------------------------------------------------------------------------
#if !defined(ACT_TRACE)
#	if !defined(ACT_POSIX) \
	&& !defined(ACT_WIN32) \
	&& !defined(ACT_WIN32_WCE)
#		error	act::Trace not implemented for this platform
#	endif
#	ifndef		ACT_TRACE_BUFFER						// default trace output buffer size
#		define	ACT_TRACE_BUFFER						2048
#	endif
#	ifndef		ACT_ASSERT_ON_THROW
#		define	ACT_ASSERT_ON_THROW						act::CheckNoThrow ACT_DEBUG_NAME(check_nothrow__)
#	endif
#	define		ACT_DEBUG_OUTPUT(trace, location)		(act::Debug<act::trace>() << location)
#	define		ACT_TRACELOG							act::Debug<act::Trace>()
#	define		ACT_TRACE								act::Debug<act::Trace>(__FILE__, __LINE__)
#endif // ACT_TRACE

// ---------------------------------------------------------------------------
namespace act
{
	class Exception;

	struct TraceContext
	{
		ushort			flags;
		ushort			indent;
		ulong			sid;
		ulong			pid;
		ulong			tid;
		const char*		name;
		char*			szBuf;
		size_t			leBuf;
		void*			owner;
		void			(*notify)(const TraceContext* const context);
		int				(*describe)(const TraceContext* const context, char* szBuf, size_t leBuf);
	};

	class Trace
	{
	public:
		Trace();

		Trace& operator()(TraceContext* context);
		virtual void ACT_CDECL operator()(ACT_PRINTF_FORMAT_STRING const char* format,
			va_list ptr, const char* file = 0, int line = 0) const;

		typedef TraceContext*	(*ContextProvider)();
		static ContextProvider	SetContextProvider(ContextProvider provider);

		static int				Timestamp(const TraceContext* const context, char* szBuf, size_t leBuf);

	protected:
		TraceContext* mContext;
	};

	class Report : public Trace
	{
	public:
		using Trace::operator();
		virtual void ACT_CDECL operator()(ACT_PRINTF_FORMAT_STRING const char* format,
			va_list ptr, const char* file = 0, int line = 0) const;
	};

	class OutputFormatter : public FileAndLine
	{
	public:
		void setFileAndLine(const FileAndLine* fl)
		{
			if(fl != 0) *static_cast<FileAndLine*>(this) = *fl;
		}

		OutputFormatter& operator<<(const FileAndLine& fl)
		{
			*static_cast<FileAndLine*>(this) = fl;
			return *this;
		}

		// exception trace.
		void operator()(const Exception& e);
		void operator()(const Exception& e, const char* where);
		void operator()(const Exception& e, const Location<>& location);

		virtual void operator()(ACT_PRINTF_FORMAT_STRING const char* format, ...) = 0;
		virtual void operator()(TraceContext* context, ACT_PRINTF_FORMAT_STRING const char* format, ...) = 0;

	protected:
		void output(const Exception& e, const char* where);
	};

	template<typename TraceT>
	class Debug : public OutputFormatter
	{
	public:
		Debug() { }
		Debug(const FileAndLine& fl) { *this << fl; }
		Debug(const char* file, int line) { *this << FileAndLine(file, line); }

		using OutputFormatter::operator();

		virtual void operator()(ACT_PRINTF_FORMAT_STRING const char* format, ...)
		{
			va_list ptr; va_start(ptr, format);
			TraceT()(format, ptr, file(), line());
			va_end(ptr);
		}

		virtual void operator()(TraceContext* context, ACT_PRINTF_FORMAT_STRING const char* format, ...)
		{
			va_list ptr; va_start(ptr, format);
			TraceT()(context)(format, ptr, file(), line());
			va_end(ptr);
		}
	};

	class CheckNoThrow
	{
	private:
		CheckNoThrow(const CheckNoThrow&) throw();
		CheckNoThrow& operator=(const CheckNoThrow&) throw();

	public:
		~CheckNoThrow();

		CheckNoThrow(const Location<>& location, const char* msg = 0)
			: m_state(location)
		{
			initialize(msg);
		}

		template<typename SourceT>
		CheckNoThrow(const Location<SourceT>& location, const char* msg = 0)
			: m_state(Location<>(location))
		{
			initialize(msg);
		}

		const Location<>& location() const;
		bool exception() const;

	private:
		void initialize(const char* msg);

	private:
		const char* m_msg;
		ThreadState<TagExcept, Location<> > m_state;
	};

	namespace ContextProviders
	{
		TraceContext* nullContextProvider();
		TraceContext* basicContextProvider();

		void SetFriendlyName(const char* fn);
	}
}	// namespace act

#endif // ACT_Debug_h
