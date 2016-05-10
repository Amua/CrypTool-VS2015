//////////////////////////////////////////////////////////////////////////
// Name:      actSALPop.h
// Product:   cv act library
// Purpose:   Reenables code analysis options, requires previous include 
//            of "actSALPush.h".
//
// Copyright: (c) 2012 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/22/2012
//////////////////////////////////////////////////////////////////////////

#include <actEnv.h>

#if defined(ACT_MSC)
#	if defined(ACT_SAL_PUSH)
#		undef	ACT_SAL_PUSH
#		pragma pop_macro("ACT_SAL_PUSH")
#		if defined(ACT_SAL)
#			pragma	warning(pop)
#		endif

#	else
#		error requires actSALPush.h included before!

#	endif
#endif
