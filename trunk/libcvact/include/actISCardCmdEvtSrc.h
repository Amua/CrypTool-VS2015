// ---------------------------------------------------------------------------
// Name:      actISCardCmdEvtSrc.h
// Product:   cv act library
// Purpose:   SCardCmd event source.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  11/02/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardCmdEvtSrc_h
#define ACT_ISCardCmdEvtSrc_h

#include "actObserver.h"

namespace act
{
	//
	// ISCardCmdEvtSrc
	class ISCardCmdEvtSrc
		: virtual public IRefCounted
		, public Observable<ISCardCmdEvtSrc, size_t, Blob>
		, public Observable<ISCardCmdEvtSrc, size_t, ushort>
	{
	public:
		virtual const char* GetName() const = 0;
	};

	//
	// ISCardCmdObserver
	class ISCardCmdObserver
		: public Observer<ISCardCmdEvtSrc, size_t, Blob>
		, public Observer<ISCardCmdEvtSrc, size_t, ushort>
	{ };

} // namespace act

#endif // ACT_ISCardCmdEvtSrc_h
