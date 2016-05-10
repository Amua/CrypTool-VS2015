// ---------------------------------------------------------------------------
// Name:      actThread.h
// Product:   cv act library
// Purpose:   Declares thread helper macros used inside slot monitors
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/14/2009
// ---------------------------------------------------------------------------

#ifndef actThread_h
#define actThread_h

#include "actEnv.h"
#include "actSALPush.h"

#if defined(ACT_WIN32) && !defined(ACT_WIN32_WCE)
#	pragma  warning(disable : 6385 6326 6320 6246)
#	include <windows.h>
#	include <process.h>

#	define	ACT_THREAD_FUNC			unsigned int ACT_STDCALL
#	define	ACT_THREAD_HANDLE		HANDLE
#	define	ACT_THREAD_ID			unsigned int
#	define	ACT_HMODULE				HINSTANCE
#	define	ACT_HEVENT				HANDLE

#elif defined(ACT_WIN32_WCE)
#	pragma  warning(disable : 6385 6326 6320 6246)
#	include <windows.h>

#	define	ACT_THREAD_FUNC			DWORD ACT_STDCALL
#	define	ACT_THREAD_HANDLE		HANDLE
#	define	ACT_THREAD_ID			DWORD
#	define	ACT_HMODULE				HINSTANCE
#	define	ACT_HEVENT				HANDLE

#elif defined(ACT_MACOSX)
#	include <pthread.h>
#	include <semaphore.h>

#	define ACT_THREAD_FUNC			void*
#	define ACT_THREAD_HANDLE		pthread_t
#	define ACT_THREAD_ID			uint64
#	define ACT_HMODULE			void*
#	define ACT_HEVENT			void*

#elif defined(ACT_POSIX)
#	include <pthread.h>
#	include <semaphore.h>

#	define	ACT_THREAD_FUNC			void*
#	define	ACT_THREAD_HANDLE		pthread_t
#	define	ACT_THREAD_ID			uint32
#	define	ACT_HMODULE				void*
#	define	ACT_HEVENT				void*

#elif defined(ACT_IOS)
// No threading, just dummy types
#	define	ACT_THREAD_FUNC			void*
#	define	ACT_THREAD_HANDLE		void*
#	define	ACT_THREAD_ID			uint32
#	define	ACT_HMODULE				void*
#	define	ACT_HEVENT				void*

#else
#	error thread-handling not implemented for this platform

#endif

#include "actSALPop.h"
#include "actTypeTags.h"
#include "actLocation.h"

namespace act
{
	//
	//! \brief ThreadState<>
	template<typename Tag, typename BaseT = void>
	struct ThreadState;

	//
	//! \brief ThreadState<TagExcept, void>
	template<>
	struct ThreadState<TagExcept, void>
	{
		ACT_THREAD_ID		thread_id;
		union
		{	ulong			state;
			struct
			{	ushort		has_exception	: 1;	//!< bit 0
				ushort		has_location	: 1;	//!< bit 1
				ushort		has_context		: 1;	//!< bit 2
				/*			...				*/
			};
		};
	};

	//
	//! \brief ThreadState<TagExcept, Location<SourceT> >
	template<typename SourceT>
	struct	ThreadState<TagExcept, Location<SourceT> >
		:	ThreadState<TagExcept, void>
	{
		ThreadState(const Location<SourceT>& location_)
			: location(location_)
		{
			state = 0;
		}

		Location<SourceT> location;
	};

}		// namespace act
#endif	// actThread_h
