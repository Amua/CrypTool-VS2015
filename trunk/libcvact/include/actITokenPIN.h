// ---------------------------------------------------------------------------
// Name:      actITokenPIN.h
// Product:   cv act library
// Purpose:   Defines the interfaces for authentication object operations.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Xiangdong Wang
//            Ullrich Birkenhauer
//            Markus Tesche
//            Thomas Mai
// Date:	  04/05/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenPIN_h
#define ACT_ITokenPIN_h

#include "actBool.h"
#include "actBlob.h"
#include "actDate.h"
#include "actBasics.h"
#include "actTokenBase.h"

#include "actIRefCounted.h"

#include "actITokenAuth.h"
#include "actITokenFileOwner.h"
#include "actIAccessCondition.h"

namespace act
{
	class IKey;
	class IToken;
	class ISCardOS;
	class AuthInfo;
	class ITokenPIN;
	class ITokenFile;
	class IAuthIdRef;
	class ISCardAccess;

	// ---------------------------------------------------------------------------
	bool IsTransacted(const ITokenPIN*);
	const ISCardAccess*	GetAccess(const ITokenPIN*);

	//!
	//! \brief ITokenPIN
	// ---------------------------------------------------------------------------
	class ITokenPIN 
		: public IRefCounted
		, public ITokenFileOwner
		, public IAuthContextOwner
	{
	public:
		virtual ITokenPIN*		Clone() const = 0;
		virtual bool			Equals(const ITokenPIN* other) const = 0;
		virtual int				Compare(const ITokenPIN* other) const = 0;

		// TODO: MTE: Tempoaray only (!) removed if respective constraint is implemented!
		virtual bool			CheckConstraints(const IKey* key) = 0;

		virtual Blob			GetUid() const = 0;
		virtual PinType			GetType() const = 0;
		virtual PinRole			GetRole() const = 0;
		virtual PinUsage		GetUsage() const = 0;
		virtual IToken*			GetToken() const = 0;
		virtual byte			GetObjRef() const = 0;
		virtual byte 			GetRecNum() const = 0;
		virtual EncodingType	GetEncoding() const = 0;
		virtual const Blob&		GetAuthId(AIType ai = AI_SELF) const = 0;

		virtual const char*		GetName() const = 0;
		virtual void			SetName(const AuthInfo& ai) = 0;

		virtual const AuthInfo*	GetInfo() const  = 0;
		virtual void			SetInfo(const AuthInfo& ai) = 0;

		virtual bool			IsInitialized() const = 0;
		virtual bool			IsAuthenticated() const = 0;
		virtual bool			IsCompatible(PinType type) const = 0;
		virtual bool			IsSuiteable(const AuthInfo& ai, const IAuthIdRef* parent) const = 0;

		virtual bool			IsDefault() const = 0;
		virtual bool			SetDefault(bool val) = 0;

		virtual bool			NeedsUpdate() const = 0;
		virtual bool			NeedsPINValue() const = 0;

		virtual bool			GetLengthInfo(LengthInfo& info) const = 0;
		virtual bool			CheckPinLength(const Blob& pin) const = 0;
		virtual bool			GetLastChange(Date& date, bool& supported) const = 0;

		virtual int				GetTriesRemaining() const = 0;		//!< Returns RC_COUNT_LOW, RC_UNKNOWN or >= 0
		virtual int				GetUsageCounter() const = 0;		//!< Returns UC_UNKNOWN or >= 0

		virtual void			VerifyPin(const Blob& pin) = 0;

		//! \note required to preserves the authentication state if successfull
		virtual void			ChangePin(const Blob& oldpin, const Blob& newpin) = 0;

		//! \note requiered to preserve the authentication state if successfull
		virtual void			UnlockPin(ITokenPIN* so, const Blob& pin, const Blob& newpin) = 0;

		//! \note requiered to preserve the authentication state if successfull
		virtual void			SetPinValue(ITokenPIN* so, const Blob& so_pin, const Blob& newpin) = 0;

		virtual bool			ResumePin(ITokenPIN* parent, const Blob& parent_pin, const Blob& pin) = 0;

		virtual void			Select(ISCardOS* os = 0) const = 0;

		virtual ITokenPIN*		GetParent() const = 0;
		virtual IAuthIdRef*		GetAuthIdRef() const = 0;
		virtual IAuthIdRef*		GetAuthIdRefParent() const = 0;

		// Bio extensions
		virtual byte			GetFinger() const = 0;
		virtual bool			GetBioHeader(Blob& bioheader) = 0;

		// ExternalAuth Key extensions
		virtual Blob			GetChallenge() const = 0;
		virtual void			ResetChallenge() = 0;
		virtual Blob			ComputeResponse(const Blob& auth_key, const Blob& challenge) const = 0;

		// Certificate based authentication extensions
		virtual void			SetCHAT(const Blob& chat) = 0;
		virtual void			SetCHAT(move_from<Blob> chat) = 0;
		virtual void			SetCHAT(const AuthInfo& ai) = 0;
		virtual Blob			GetCHAT() const = 0;

		// Type specific parameter.
		virtual int				GetParam(paramid_t id) const = 0;
		virtual void			SetParam(paramid_t id, int value) = 0;

	protected:
		virtual Blob			doGetChallenge() const = 0;
		virtual void			doResetChallenge() const = 0;
		virtual BOOLean			doResetSecState() const = 0;			//<! \req Selected \a ITokenFile NOT to be changed!
		virtual SecStatus		doGetSecState(Blob&) const = 0;			//<! \req Selected \a ITokenFile NOT to be changed!
		virtual bool			doVerify(const Blob& pin) const = 0;

	private:
		friend class TokenAuth;
	};

} // namespace act

#endif	// ACT_ITokenPIN_h
