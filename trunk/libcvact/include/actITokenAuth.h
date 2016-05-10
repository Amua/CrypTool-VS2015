// ---------------------------------------------------------------------------
// Name:      actITokenAuth.h
// Product:   cv act library
// Purpose:   The interface \ref ITokenAuth manages the authentication state
//			  of a token. Therefore the authentication objects will be monitored
//			  and their contraints ensured.
//
// Copyright: (c) 2007 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  11/09/2007
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenAuth_h
#define ACT_ITokenAuth_h

#include "actBlob.h"
#include "actBool.h"
#include "actBasics.h"
#include "actTokenBase.h"

#include "actIIterator.h"

namespace act
{
	class AuthInfo;
	class AuthConstraintsViolation;

	class IToken;
	class ITokenPIN;
	class ITokenFile;
	class ITokenAuth;
	class IAuthIdRef;
	class IAuthConstraints;

	// ---------------------------------------------------------------------------
	enum AuthContext
	{
		AUTH_DEFAULT				= 0,
		AUTH_OWNER,
	};

	// ---------------------------------------------------------------------------
	enum AuthConstrainedMode
	{
		ACM_BEGIN,

		ACM_READ					= ACM_BEGIN,
		ACM_UPDATE,
		ACM_EXECUTE,
		ACM_AUTH					= ACM_EXECUTE,
		ACM_DELETE,

		ACM_END,
		ACM_SIZE					= ACM_END - ACM_BEGIN
	};

	// ---------------------------------------------------------------------------
	enum AuthConstrainedType
	{
		AUTHCT_ANY					= -1,

		// Logic operations
		AUTHCT_ALWAYS				= 0,	//!< needs to be zero!
		AUTHCT_NOT					= 1,
		AUTHCT_AND					= 2,
		AUTHCT_OR					= 4,
		AUTHCT_AUTHID				= 8,
		AUTHCT_MASK					= 15,

		// Dependency bound, combineable
		AUTHCT_BOUND_KEY			= 8,
	};

	//!
	//! \brief   IAuthContextOwner
	//! \details If a token conatins more than one profile, like the PKCS#15-Profile
	//!          with PACE, authentication objects are shared between all referencing
	//!          tokens, like the default PKCS#15 token.
	//!          As a result the authentication has to be done using the ITokenAuth
	//!          instance of this token! This contract has not been honored by the
	//!          \a TokenAuthGuard which is used widely, f.e. in \a ITokenPIN::ChangePin
	//!          and \a IToken::SetPinValue.
	//!          To prevent the \a TokenAuthGuard to login using the wrong context
	//!          this interface adds the additional \a AuthContext as a parameter.
	//!          1. \a AUTH_DEFAULT: The default context, used by \a TokenAuthGuard
	//!          and everyone to login etc.
	//!          2. \a AUTH_OWNER: The owning context will primarily be used by the
	//!          \a ITokenAuth implementation (\a TokenAuth) to direct method calls
	//!          to the owning context.
	// ---------------------------------------------------------------------------
	class IAuthContextOwner
	{
	public:
		virtual ITokenAuth& RefAuth(AuthContext ac/* = AUTH_DEFAULT*/) const = 0;
		virtual ITokenAuth*	GetAuth(AuthContext ac/* = AUTH_DEFAULT*/) const = 0;
		virtual ITokenAuth*	SetContext(ITokenAuth* auth, AuthContext ac) = 0;

	protected:
		virtual ~IAuthContextOwner() { }
	};

	//!
	//! \brief IAuthFactory
	// ---------------------------------------------------------------------------
	class IAuthFactory
	{
	public:
		virtual IAuthIdRef* CreateAuthIdRef(const Blob& authId, ITokenFile* path, const Blob& constraints_types) = 0;

		// create and configure new instance
		virtual ITokenPIN* CreatePin(const AuthInfo& authInfo, byte objRef, ITokenFile* path, IAuthIdRef* authIdRef, IAuthIdRef* parentIdRef) = 0;

	protected:
		// create new instance, no additional configuration
		virtual ITokenPIN* NewPin(const AuthInfo& authInfo, byte objRef, IAuthIdRef* authIdRef, const char* name = 0) = 0;

		virtual ~IAuthFactory() { }
	};

	//!
	//! \brief IAuthIdRef
	// ---------------------------------------------------------------------------
	class IAuthIdRef : public IRefCounted
	{
	public:
		virtual byte GetAuthIdByte() const = 0;
		virtual const Blob& GetAuthId() const = 0;
		virtual IAuthConstraints* GetAuthConstraints() = 0;

		virtual bool Equals(const Blob& authId) const = 0;
		virtual bool Equals(IAuthIdRef* authIdRef) const = 0;
	};

	//!
	//! \brief IAuthIdRefIterator
	// ---------------------------------------------------------------------------
	class IAuthIdRefIterator : public IIterator<IAuthIdRef> { };

	//!
	//! \brief ITokenAuthIterator
	// ---------------------------------------------------------------------------
	class ITokenAuthIterator : public IIterator<ITokenPIN, ITokenFile> { };

	//!
	//! \brief ITokenAuth
	// ---------------------------------------------------------------------------
	class ITokenAuth : public IRefCounted
	{
	public:
		typedef ITokenAuthIterator IIterator;

		virtual bool Login(ITokenPIN* auth_obj, const Blob& pin) = 0;

		virtual bool Logout() = 0;
		virtual BOOLean Logout(const ITokenPIN* auth_obj, bool permit_security_state_reset = true) = 0;
		virtual bool LogoutEx(bool enforce_security_state_reset) = 0;

		virtual Blob GetChallenge(const ITokenPIN* auth_obj) = 0;

		virtual IToken* GetToken() const = 0;
		virtual ITokenPIN* GetAuthenticated() const = 0;
		virtual ITokenPIN* GetAuthenticated(size_t index) const = 0;

		virtual bool NeedsPINValue() const = 0;
		virtual bool HasChallenge() const = 0;
		virtual bool HasChallenge(const ITokenPIN* auth_obj) const = 0;
		virtual bool IsAuthenticated(const ITokenPIN* auth_obj) const = 0;
		virtual bool IsAuthenticated(bool verify_security_state = false) const = 0;

		/*!
		 * Clears the internal authentication state for given auth_obj.
		 *
		 * If auth_obj is not authenticated:
		 * - do nothing
		 * - return false
		 *
		 * If auth_obj is authenticated:
		 * - remove auth_obj from authenticated-list.
		 * - return true
		 *
		 * \note	does NOT reset the card's authentication state!
		 *
		 * \param	auth_obj \a ITokenPIN 
		 * \return	true if succeeded, false if not
		 */
		virtual bool Invalidate(ITokenPIN* auth_obj) = 0;
		virtual bool InvalidateChallenge(ITokenPIN* auth_obj) = 0;
		virtual bool ResetChallenge(const ITokenPIN* auth_obj) = 0;
		virtual bool Select(const ITokenPIN* auth_obj, bool force) = 0;

		virtual IIterator* Resolve(const AuthConstraintsViolation&) = 0;
		virtual IIterator* Iterator(PinType type, const Blob& authId = Blob()) const = 0;

	protected:
		virtual const ITokenPIN* setChallenge(const ITokenPIN* challenge) = 0;
		virtual const ITokenPIN* getEqualAuthenticated(const ITokenPIN* auth_obj) const = 0;

	private:
		friend class TokenAuth;
	};

} // namespace act

#endif	// ACT_ITokenAuth_h
