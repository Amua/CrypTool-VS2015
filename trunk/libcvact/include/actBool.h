// ---------------------------------------------------------------------------
// Name:      actBool.h
// Product:   cv act library
// Purpose:   Simple boolean which supports not initialized.
//
// Copyright: (c) 2012 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/19/2012
// ---------------------------------------------------------------------------

#ifndef ACT_Bool_h
#define ACT_Bool_h

#include "actLocation.h"

namespace act
{
	enum BOOLean
	{
		True					=  1L,
		False					=  0L,
		NotInitialized			= -1L,
		NotEvaluable			= -2L,
		NotSupported			= -3L,
		AlreadyShutdown			= -4L,

		BOOL_True				=  True,
		BOOL_False				=  False,
		BOOL_NotInitialized		=  NotInitialized,
		BOOL_NotEvaluable		=  NotEvaluable,
		BOOL_NotSupported		=  NotSupported,
		BOOL_AlreadyShutdown	=  AlreadyShutdown,
	};

	template<typename value_type, typename target_type>
	struct convert;

	template<typename value_type>
	struct convert<value_type, BOOLean>
	{
		static const BOOLean value = value_type::value ? True : False;
	};

	template<typename OnError, typename T>
	BOOLean BOOLerror(BOOLean value, const Location<T>& location)
	{
		const char* what = 0;
		switch(value)
		{
		case True:			 /* fall through */
		case False:			 return value;
		default:			 what = "undefined";		break;
		case NotSupported:	 what = "not supported";	break;
		case NotEvaluable:	 what = "not evaluable";	break;
		case NotInitialized: what = "not initialized";	break;
		}
		OnError::Throw(what, value, location);
		return False;
	}

	template<typename OnError, typename T>
	bool BOOLval(BOOLean value, const Location<T>& location)
	{
		switch(value)
		{
		case True:		return true;
		case False:		return false;
		default:		BOOLerror<OnError>(value, location);
		}
		return false;
	}

	template<typename OnError>
	bool BOOLval(BOOLean value)
	{
		switch(value)
		{
		case True:		return true;
		case False:		return false;
		default:		BOOLerror<OnError>(value, Location<>("unknown"));
		}
		return false;
	}

	inline BOOLean BOOLval(bool value)    { return value ? True : False; }
	inline BOOLean BOOLval(BOOLean value) { return value; }

} // namspace act

#endif // ACT_Bool_h
