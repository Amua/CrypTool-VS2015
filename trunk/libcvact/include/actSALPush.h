//////////////////////////////////////////////////////////////////////////
// Name:      actSALPush.h
// Product:   cv act library
// Purpose:   Disables code analysis options.
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
#	pragma push_macro("ACT_SAL_PUSH")
#	if !defined(ACT_SAL_PUSH)
#		define  ACT_SAL_PUSH
#	endif
#	if defined(ACT_SAL)
#		pragma	warning(push)
#		if !defined(ALL_CODE_ANALYSIS_WARNINGS)
#			include <codeanalysis\warnings.h>
#			pragma	warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#		endif
#	endif
#endif
