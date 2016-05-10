// ---------------------------------------------------------------------------
// Name:      actSCardSMReg.h
// Product:   cv act library
// Purpose:   Registry for ISCardSM factory functions.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  22/01/2013
// ---------------------------------------------------------------------------

#ifndef ACT_SCardSMReg_h
#define ACT_SCardSMReg_h

#include "actFactoryReg.h"

namespace act
{
	class ISCardSM;
	class ITokenPIN;

	typedef ISCardSM*          (*CreateSCardSMPtr)(const char*, const ITokenPIN*);
	typedef FactoryMapEntry<     CreateSCardSMPtr> SCardSMMapEntry;
	typedef FactoryReg<ISCardSM, CreateSCardSMPtr, SCardSMMapEntry> SCardSMReg;

} // namespace act

#endif // ACT_SCardSMReg_h
