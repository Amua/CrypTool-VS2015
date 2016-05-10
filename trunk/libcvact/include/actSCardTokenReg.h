// ---------------------------------------------------------------------------
// Name:      actSCardTokenReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create SCardToken objects.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/13/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardTokenReg_h
#define ACT_SCardTokenReg_h

#include "actFactoryReg.h"
#include "actTokenExtensionReg.h"

namespace act
{
	class ISCardOS;
	class SCardToken;

	typedef bool		(*CheckSCardTokenPtr)(ISCardOS*);
	typedef SCardToken* (*CreateSCardTokenPtr)(ISCardOS*, SCardToken*);

	struct SCardTokenMapEntry
	{
		CheckSCardTokenPtr	CheckPtr;
		CreateSCardTokenPtr CreatePtr;
	};

	class SCardTokenReg
	{
	public:
		static SCardToken* CreateSCardToken(ISCardOS*);
		static SCardToken* CreateSCardToken(ISCardOS*, const AttachTokenExtensionPtr);

		static void Insert(CheckSCardTokenPtr, CreateSCardTokenPtr);
		static void Insert(const SCardTokenMapEntry*);
	};

	typedef FactoryMapEntry
		<	CreateSCardTokenPtr
		>	SCardTokenNameMapEntry;

	typedef FactoryReg
		<	SCardToken, CreateSCardTokenPtr, SCardTokenNameMapEntry
		>	SCardTokenNameReg;

} // namespace act

#endif // ACT_SCardTokenReg_h
