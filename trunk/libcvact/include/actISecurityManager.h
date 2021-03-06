// ---------------------------------------------------------------------------
// Name:      actISecurityManager.h
// Product:   cv act library
// Purpose:   ISecurityManager used to manage the token authentication objects.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  08/05/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ISecurityManager_h
#define ACT_ISecurityManager_h

#include "actBasics.h"
#include "actIRefCounted.h"

namespace act
{
	class ITokenPIN;
	class IAuthIdRef;

	enum SecManType
	{
		SecManUnknown = 0,
		SecManPIN,
		SecManBio,
	};

	//!
	//! \brief Interface definition ISecurityManager.
	//! \todo  Add missing access control management.
	// ---------------------------------------------------------------------------
	class ISecurityManager : public IRefCounted
	{
	public:
		virtual SecManType	GetType() const = 0;
		virtual const char*	GetName() const = 0;
		virtual void		SetName(const char* name)   = 0;
		virtual void		Delete(ITokenPIN* auth_obj) = 0;
	};

	//!
	//! \brief Specialized \a ISecurityManager for PIN manangement.
	// ---------------------------------------------------------------------------
	class IPINManager : public ISecurityManager
	{
	public:
		// NOTE: MTE: pin can be empty!
		virtual ITokenPIN* Create(IAuthIdRef*, IAuthIdRef*, int, const Blob&) = 0;
	};

	//!
	//! \brief Specialized \a ISecurityManager for biometric data manangement.
	// ---------------------------------------------------------------------------
	class IBioManager : public ISecurityManager
	{
	public:
		virtual ITokenPIN* Create(IAuthIdRef*, IAuthIdRef*, int, int) = 0;
	};

} // namespace act

#endif	// ACT_ISecurityManager_h
