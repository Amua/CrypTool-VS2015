//////////////////////////////////////////////////////////////////////////////////
// Name:      actLogger.h
// Product:   cv act library
// Purpose:   Logger
//
// Copyright: (c) 2000-2001 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Logger_h
#define ACT_Logger_h

#include "actEnv.h"
#include "actBlob.h"
#include "actDebug.h"

// for convenience
#if defined(ACT_MSC)
#	define	ACT_SNPRINTF _snprintf
#	define	ACT_VSNPRINTF _vsnprintf
#else
#	define	ACT_SNPRINTF snprintf
#	define	ACT_VSNPRINTF vsnprintf
#	include <cstdio>
#endif

#if !defined(ACT_DEBUGLOG)
#	if defined(ACT_DEBUG)
#		define ACT_DEBUGLOG 1
#	else
#		define ACT_DEBUGLOG 0
#	endif
#endif

//
// NOTE: [11/1/2006 MTE]: Added accessor.
// NOTE: Redefine to use another Logger.
#define	ACT_LOGGER(x)						act::Logger::x

// NOTE: [9/17/2013 MTE]: Allocate log output buffer on stack (default).
#define ACT_LOGALLOC_STACK(size)			char __log_buffer[size]

// NOTE: [9/17/2013 MTE]: Allocate log output buffer on stack (default).
#define ACT_LOGLOCK_SCOPE()					const ACT_LOGGER(LogGuard)& __log_lock(ACT_LOGGER(ScopeLock)())

#define ACT_LOGINIT(size)					ACT_LOGALLOC_STACK(size); \
											ACT_LOGLOCK_SCOPE()

// 
// NOTE: [11/1/2006 MTE]: Added to replace direct usage of ACT_LOGGER(LogInit)().
#define ACT_LOGISENABLED(level)				(ACT_DEBUGLOG != 0 || ACT_LOGGER(LogInit)(ACT_LOGGER(level)))

//
// NOTE: [9/17/2013 MTE]: Use without ACT_LOGINIT!
#define ACT_LOGEXCEPTION(e)																							\
	do	{	if(ACT_LOGISENABLED(LEVEL_ERROR))																		\
		{	ACT_LOGINIT(256);																						\
			ACT_SNPRINTF(__log_buffer, sizeof(__log_buffer), "Exception:\t '%s' in '%s'", e.what(), e.where());		\
			ACT_LOGERROR(__log_buffer);																				\
		} } while(false)

#define ACT_LOGVAL(name, val, fmtval)																				\
	do	{	ACT_SNPRINTF(__log_buffer, sizeof(__log_buffer), name " :\t " fmtval, val);								\
			ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ANY), __log_buffer);													\
		}	while(false)

#define ACT_LOGV2FUN(name, val, fmtval, fun, fmtfun)																\
	do	{	ACT_SNPRINTF(__log_buffer, sizeof(__log_buffer), name " :\t " fmtval " [" fmtfun "]", val, fun(val));	\
			ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ANY), __log_buffer);													\
		}	while(false)

#define ACT_LOGINFO(info)						ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO),  info)
#define ACT_LOGWARN(warn)						ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_WARN),  warn)
#define ACT_LOGERROR(error)						ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ERROR), error)
#define ACT_LOGINFODATA(info, data)				ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO),  info,  data)
#define ACT_LOGWARNDATA(warn, data)				ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_WARN),  warn,  data)
#define ACT_LOGERRORDATA(error, data)			ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_ERROR), error, data)

#define ACT_LOGNAMEDINT(name, val)				ACT_LOGVAL(name, int(val), "%i")
#define ACT_LOGNAMEDINTV2STR(name, val, fun)	ACT_LOGV2FUN(name, int(val), "%i", fun, "%s")

#define ACT_LOGNAMEDHEX(name, val)				ACT_LOGVAL(name, act::ulong(val), "0x%08x")
#define ACT_LOGNAMEDHEXV2STR(name, val, fun)	ACT_LOGV2FUN(name, act::ulong(val), "0x%08x", fun, "%s")

#define ACT_LOGNAMEDSTR(name, val)				ACT_LOGVAL(name, val, "%s")
#define ACT_LOGNAMEDSTRV2STR(name, val, fun)	ACT_LOGV2FUN(name, val, "%s", fun, "%s")

#define ACT_LOGNAMEDPTR(name, val)				ACT_LOGVAL(name, val, "0x%p")
#define ACT_LOGNAMEDPTRV2INT(name, val, fun)	ACT_LOGV2FUN(name, val, "0x%p", fun, "%i")
#define ACT_LOGNAMEDPTRV2HEX(name, val, fun)	ACT_LOGV2FUN(name, val, "0x%p", fun, "0x%08x")
#define ACT_LOGNAMEDPTRV2STR(name, val, fun)	ACT_LOGV2FUN(name, val, "0x%p", fun, "%s")
#define ACT_LOGNAMEDPTRV2PTR(name, val, fun)	ACT_LOGV2FUN(name, val, "0x%p", fun, "0x%p")

#define ACT_LOGINTV2STR(val, fun)				ACT_LOGNAMEDINTV2STR(ACT_STRING(val), val, fun)
#define ACT_LOGHEXV2STR(val, fun)				ACT_LOGNAMEDHEXV2STR(ACT_STRING(val), val, fun)
#define ACT_LOGSTRV2STR(val, fun)				ACT_LOGNAMEDSTRV2STR(ACT_STRING(val), val, fun)

#define ACT_LOGPTRV2INT(ptr, fun)				ACT_LOGNAMEDPTRV2INT(ACT_STRING(ptr), ptr, fun)
#define ACT_LOGPTRV2HEX(ptr, fun)				ACT_LOGNAMEDPTRV2HEX(ACT_STRING(ptr), ptr, fun)
#define ACT_LOGPTRV2STR(ptr, fun)				ACT_LOGNAMEDPTRV2STR(ACT_STRING(ptr), ptr, fun)
#define ACT_LOGPTRV2PTR(ptr, fun)				ACT_LOGNAMEDPTRV2PTR(ACT_STRING(ptr), ptr, fun)

#define ACT_LOGINT(val)							ACT_LOGNAMEDINT(ACT_STRING(val), val)
#define ACT_LOGHEX(val)							ACT_LOGNAMEDHEX(ACT_STRING(val), val)
#define ACT_LOGSTR(val)							ACT_LOGNAMEDSTR(ACT_STRING(val), val)
#define ACT_LOGPTR(val)							ACT_LOGNAMEDPTR(ACT_STRING(val), val)
#define ACT_LOGBLOB(val)						ACT_LOGGER(Log)(ACT_LOGGER(LEVEL_INFO), ACT_STRING(val), val)

// TODO: MTE: What about this "nice" construct ?
#define ACT_LOGPOINTER(p)						do { if(p != 0) ACT_LOGINT(*p); else ACT_LOGHEX(0); } while(false)
#define ACT_LOGISNULL(p)						ACT_LOGVAL(ACT_STRING(p), p != 0 ? "*" : "0", "%s")

namespace act
{
	class Logger
	{
	private:
		Logger(const Logger&);
		Logger& operator=(const Logger&);

	protected:
		Logger() { }
		virtual ~Logger() { }

	public:
		enum Level
		{
			LEVEL_ANY		= 0,
			LEVEL_OFF		= LEVEL_ANY,
			LEVEL_ERROR		= 30,
			LEVEL_WARNING	= 50,
			LEVEL_WARN		= LEVEL_WARNING,
			LEVEL_INFO		= 80,
			LEVEL_MAX		= 99
		};

		class LogGuard
		{
		public:
			LogGuard(const LogGuard&);
			~LogGuard();
		private:
			LogGuard(bool);
			const bool m_bLock;
			friend class Logger;
		};

		static LogGuard		ScopeLock() { return false; }
		static void			SetLogger(Logger* pLogger);
		static void			FreeLogger();
		static void			Log(Level level, const char* msg);
		static void			Log(Level level, const Blob& blobmsg);
		static void			Log(Level level, const char* msg, const Blob& blobmsg);
		static void			SetLoglevel(Level level);
		static bool			LogInit(Level level);

	protected:
		virtual void		doLog(const char* msg) = 0;

	private:
		static volatile Logger* s_pLogger;
		static volatile Level	s_level;
	};

} // namespace act

#endif // ACT_Logger_h
