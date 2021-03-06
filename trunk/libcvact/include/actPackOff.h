//////////////////////////////////////////////////////////////////////////
// Name:      actPackOff.h
// Product:   cv act library
// Purpose:   Enables automatic alignment of structure fields.
//
// Copyright: (c) 2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  11/05/2011
//////////////////////////////////////////////////////////////////////////

#include "actEnv.h"

#if defined(ACT_MACOSX) || defined(ACT_SOLARIS)
#	pragma pack()

#elif defined(ACT_WIN32) || defined(ACT_POSIX)
#	if(ACT_MSC_VER >= ACT_CPP_VER(8, 0, 0))
#		pragma warning(disable:4103)
#	endif
#	pragma pack(pop)

#else
#	error no compiler structure alignment

#endif
