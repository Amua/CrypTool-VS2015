//////////////////////////////////////////////////////////////////////////////////
// Name:      actITokenKey.h
// Product:   cv act library
// Purpose:   The interface ITokenKey enables access to a key stored in a secure token.
//
// Copyright: (c) 2003 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ITokenKey_h
#define ACT_ITokenKey_h

#include "actIRefCounted.h"
#include "actISignatureKey.h"
#include "actITokenAuthOwner.h"
#include "actITokenFileOwner.h"

#include "actTokenBase.h"

namespace act
{
	class IToken;
	class ITokenConfig;

	//!
	//! \brief Interface definition ITokenKeyIterator.
	// ---------------------------------------------------------------------------
	class ITokenKeyIterator : public IRefCounted
	{
	public:
		virtual void Reset(ITokenFile* parent = 0) = 0;
		virtual IKey* Next() = 0;
	};

	//!
	//! \brief Interface definition ITokenKey.
	// ---------------------------------------------------------------------------
	class ITokenKey 
		: public ISignatureKey
		, public ITokenAuthOwner
		, public ITokenFileOwner
	{
	protected:
		virtual void		Destruct() = 0;

	public:
		virtual ITokenKey*	Clone() const = 0;

		virtual KeyType		GetType() const = 0;
		virtual IToken*		GetToken() const = 0;
		virtual const char* GetName() const = 0;
		virtual void		Configure(const ITokenConfig*) = 0;

		virtual Blob		GetCertificate(bool readfromcard = true) const = 0;
		virtual Blob		GetCertificate(int index) const = 0;
		virtual int			GetCertificateNumber() const = 0;

		virtual IKey*		GetPublicKey(bool readfromcard = true) const = 0;

		virtual void		VerifyPin(const Blob& pin) = 0;

		virtual Blob		GetID() const = 0;
		virtual Blob		GetSubject(bool readfromcard = true) const = 0;

		virtual ITokenKeyIterator* Iterator(KeyType type, const Blob& authId = Blob()) const = 0;
	};

} // namespace act

#endif // ACT_ITokenKey_h
