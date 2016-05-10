// ---------------------------------------------------------------------------
// Name:      actIToken.h
// Product:   cv act library
// Purpose:   The IToken interface represents the profile and the application 
//			  supported by a token.
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/22/2002
// ---------------------------------------------------------------------------

#ifndef ACT_IToken_h
#define ACT_IToken_h

#include "actBlob.h"
#include "actBasics.h"
#include "actTokenBase.h"

#include "actISynchronize.h"
#include "actITokenFileCache.h"
#include "actIAccessCondition.h"

namespace act
{
	class IKey;
	class IEMSAAlg;
	class IAuthIdRef;
	class ICertificate;
	class IKeyFactoryChain;
	class ISecurityManager;
	class IToken;
	class ITokenPIN;
	class ITokenAuth;
	class ITokenView;
	class ITokenFile;
	class ITokenConfig;
	class ITokenFileMap;
	class ITokenKeyIterator;
	class ITokenAuthIterator;
	class ISCardAccess;

	struct CertEntry
	{
		CertEntry()
			: type(CERT_UNKNOWN)
			, usage(EMPTY_CERT)
		{ }

		ulong	type;
		ulong	usage;
		Blob	certblob;
	};

	// ---------------------------------------------------------------------------
	bool IsTransacted(const IToken* token);
	bool ResetSecurityState(const IToken* token);
	const ISCardAccess* GetAccess(const IToken* token);
	const ITokenConfig* GetTokenConfig(const IToken* token);
	const ITokenConfig* GetTokenConfig(const ITokenView* view);

	//!
	//! \brief Interface definition ITokenView
	// ---------------------------------------------------------------------------
	class ITokenView
	{
	protected:
		virtual ~ITokenView() { }

	public:
		virtual IToken*				GetToken() = 0;
		virtual ITokenConfig*		GetTokenConfig() const = 0;

		virtual ISCardOS*			GetOS() const = 0;

		virtual ITokenView*			GetPrev() const = 0;
		virtual ITokenView*			GetNext() const = 0;

		virtual ITokenFile*			GetPath() const = 0;
		virtual ITokenFileMap*		GetFileMap() const = 0;
		virtual ITokenFile*			GetRelativeTo(const Blob& path, ITokenFile* parent = 0) = 0;

		virtual bool				Equals(const ITokenView* other) const = 0;
		virtual size_t				Split(paramid_t type) = 0;
		virtual ITokenView*			SetDefault() = 0;

		virtual void				ResetView() = 0;
	};

	//!
	//! \brief Interface definition IToken.
	// ---------------------------------------------------------------------------
	class IToken
		: public IRefCounted
		, public IAcConverter
		, public ISynchronize
	{
	protected:
		virtual ~IToken() { }

	public:
		virtual ITokenView*			GetView() const = 0;
		virtual ITokenConfig*		GetTokenConfig() const = 0;
		virtual ITokenFile*			GetTokenFile(const Blob& path) = 0;

		virtual int					GetStatus() const = 0;
		virtual TokenType			GetType() const = 0;
		virtual ProfileType			GetProfileType() = 0;
		virtual const char*			GetName() const = 0;

		// Returns the personalized token profile serial number, 
		// which may (!) be empty or equal the hardware serial!
		virtual Blob				GetSerialNumber() const = 0;
		virtual Blob				GetCardholderName() const = 0;
		virtual Blob				GetRandom(const ulong count) const = 0;
		virtual void				SetSeed(const Blob& seed) = 0;

		// Generate a new key
		virtual IKey*				NewKey(int key_type) = 0;

		// Add key instance, takes ownership - even on exception!
		virtual void				AddKey(IKey* key) = 0;

		// Replace existing key with given key instance, takes ownership - even on exception!
		virtual bool				ReplaceKey(IKey* key) = 0;
		virtual bool				RemoveKey(IKey* key) = 0;

		// Write/Import a (soft) key to token
		virtual IKey*				WriteKey(const IKey* key, ulong usage) = 0;

		// Get a token key instance from matching certificate
		virtual IKey*				CreateKey(const Blob& cert) const = 0;
		virtual IKey*				CreateKey(const ICertificate* cert) const = 0;
		virtual void				DeleteKeyPair(const IKey* key) = 0;		//!< Delete key pair from token with matching key.
		virtual void				DeleteKeyPair(const Blob& cert) = 0;	//!< Delete key pair from token with matching certificate.

		// Key Objects
		virtual int					GetKeyNumber() const = 0;
		virtual IKey*				CreateKey(ulong pos) = 0;
		virtual IKey*				GetKey(int pos) const = 0;
		virtual IKeyFactoryChain*	GetKeyFactory() const = 0;
		virtual ITokenKeyIterator*	GetKeyIterator(KeyType type, const Blob& authId = Blob()) = 0;

		// Certificate Objects
		virtual int					GetCertificateNumber() const = 0;
		virtual CertEntry			GetCertificate(int pos) const = 0;

		// Write/Delete a certificate (corresponding to a key) to token
		virtual void				WriteCertificate(const Blob& cert, IKey* key = 0) = 0;
		virtual void				DeleteCertificate(const Blob& cert, IKey* key = 0) = 0;

		// Authentication Objects
		virtual ITokenAuth*			GetAuth() const = 0;
		virtual ISecurityManager*	SecurityManager(int authManagerType) = 0;
		virtual ITokenAuthIterator*	GetAuthIterator(PinType type, const Blob& authId = Blob()) = 0;

		virtual int					GetPinNumber() const = 0;
		virtual ITokenPIN*			GetPin(const IAuthIdRef* authIdRef, const ITokenFile* location) const = 0;
		virtual ITokenPIN*			GetPin(int pos, const ITokenFile* location) const = 0;
		virtual ITokenPIN*			GetPin(const char* pin_name) const = 0;
		virtual ITokenPIN*			GetPin(const Blob& authId) const = 0;

		virtual ITokenPIN*			GetUserPin() const = 0;
		virtual ITokenPIN*			GetSOPin() const = 0;
		virtual void				VerifyUserPin(const Blob& pinvalue) = 0;
		virtual void				ChangeUserPin(const Blob& oldpin, const Blob& newpin) = 0;
		virtual void				UnlockUserPin(const Blob& so_pin, const Blob& new_userpin) = 0;
		virtual void				VerifySOPin(const Blob& pinvalue) = 0;
		virtual void				ChangeSOPin(const Blob& oldpin, const Blob& newpin) = 0;

		virtual bool				ResetSecurityState(bool enforce = true) const = 0;

		// Token specific
		virtual bool				IsLocked() const = 0;
		virtual bool				IsPKCS15() const = 0;
		virtual bool				IsReadOnly() const = 0;
		virtual bool				IsMoCEnabled() const = 0;
		virtual bool				IsMiniDriverEnabled() const = 0;
		virtual bool				LoginRequired() const = 0;

		virtual Blob				GetCardId() const = 0;
		virtual Blob				GetCardCF() const = 0;

		virtual ISCardOS*			GetOS() const = 0;		// TODO: MTE: To be removed soon!
		virtual void				SelectDataPath() const = 0;
	};

} // namespace act

#endif // ACT_IToken_h
