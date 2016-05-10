// ---------------------------------------------------------------------------
// Name:      actISCardSM.h
// Product:   cv act library
// Purpose:   Interface for Secure Messaging 
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/27/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardSM_h
#define ACT_ISCardSM_h

#include "actBool.h"
#include "actBlob.h"

#include "actIRefCounted.h"
#include "actSCardSMReg.h"

namespace act
{
	class IMACKey;
	class IBlockCipherKey;

	class ISCardOS;
	class ITokenPIN;

	//!
	//! \brief Secure Messaging Interface
	// ---------------------------------------------------------------------------
	class ISCardSM : public IRefCounted
	{
	public:
		virtual ~ISCardSM() { }

		virtual const char* GetName() const = 0;
		virtual CreateSCardSMPtr GetCreatePtr() const = 0;

		virtual const ITokenPIN* GetOwner() const = 0;
		virtual BOOLean IsOwner(const ITokenPIN*) const = 0;

		virtual const char* GetCipherName() const = 0;
		virtual const char* GetMACKeyName() const = 0;

		virtual void Reset(const ISCardOS* owner) = 0;
		virtual BOOLean Initialize(IBlockCipherKey* encKey, IMACKey* macKey) = 0;
		virtual BOOLean Initialize(const ISCardOS* owner, const Blob& enc, const Blob& mac) = 0;

		virtual const Blob&	WrapCommand(const Blob& command, int le) = 0;
		virtual void UnwrapResponse(Blob& response, word sw) = 0;

		virtual void SendSequenceCounter(const Blob& ssc) = 0;

		// maximum length of a wrapped command send to the token
		// (equals token's buffer size for extended APDUs)
		virtual void MaxSendLength(ushort max_extended_length) = 0;

		// maximum LC in an APDU send to the token
		// (equals maximum length of plain data payload in an unwrapped command)
		virtual ushort GetMaxLC(bool extended_apdu = false) const = 0;

		// maximum LE in an APDU send to the token
		// (equals maximum length of plain data payload in a wrapped response)
		virtual ushort GetMaxLE(bool extended_apdu = false) const = 0;
	};

} // namespace act

#endif	// ACT_ISCardSM_h
