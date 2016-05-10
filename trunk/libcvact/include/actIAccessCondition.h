// ---------------------------------------------------------------------------
// Name:      actIAccessConditions.h
// Product:   cv act library
// Purpose:   The IAccessCondition interface is used to map access conditions for
//			  Files, Keys etc. on specific smartcard's
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/29/2008
// ---------------------------------------------------------------------------

#ifndef ACT_IAccessConditions_h
#define ACT_IAccessConditions_h

#include "actEnv.h"
#include "actBlob.h"
#include "actIRefCounted.h"

namespace act
{
	class IToken;
	class ISCardOS;

	// -----------------------------------------------------------------------
	enum AIType
	{
		AI_MASK						= 0x7f,				//!< auth-id mask
		AI_SELF						= 0,				//!< Refers to own auth-id
		AI_PARENT					= 1,				//!< Refers to parent auth-id
	};

	// -----------------------------------------------------------------------
	enum ACType
	{
		AC_TYPE_UNKNOWN				= 0,
		AC_TYPE_RAW					= 1,				//!< Already transformed for specific OS
		AC_TYPE_GENERIC				= 2,				//!< OS independant, requires to be transformed before used
	};

	//!
	//! \brief Card object specific rights by type.
	// -----------------------------------------------------------------------
	enum ACObjType ACT_ENUM_TYPE(byte)					//!< use C++0x strongly typed enum if available.
	{
		AC_OBJ_BEGIN				= 0x00,				//!< { AC_TOKEN_USER, AC_TOKEN_SO, AC_TOKEN_USER_OR_SO }
		AC_OBJ_MAP					= AC_OBJ_BEGIN,		//!< Used for access condition (f.e. tag 0x86)
		AC_OBJREF_MAP				= 0x01,				//!< Used as object reference for access condition
		AC_KEY_MAP					= 0x02,				//!< \sa AC_OBJ_MAP
		AC_KEYREF_MAP				= 0x03,				//!< \sa AC_REFOBJ_MAP
		//
		AC_OBJ_ANY					= 0x03,				//!< Access Rights not further defined
		AC_RIGHTS_EF				= 0x04, 			//!< Access Rights for EF's
		AC_RIGHTS_DF				= 0x05, 			//!< Access Rights for DF's
		AC_RIGHTS_KEY				= 0x06, 			//!< Access Rights for Key Objects
		AC_RIGHTS_AUTH				= 0x07,				//!< Access Rights for Authentication Objects
		AC_RIGHTS_DO				= 0x08,				//!< Access Rights for Data Objects
		AC_RIGHTS_SYS				= 0x09,				//!< Access Rights for System Files
		// ... add additional types here
		AC_RIGHTS_END,
		AC_RIGHTS_LENGTH			= AC_RIGHTS_END,
	};

	//!
	//! \brief Card specific rights.
	// -----------------------------------------------------------------------
	enum ACSCard
	{
		AC_ALWAYS					= 0x00,
		// Any other from 0x01..0x7f
		AC_NEVER					= 0xff
	};

	//!
	//! \brief   Generic token authentication ids / references.
	//! \details Will be \b transformed to token specific values!
	// -----------------------------------------------------------------------
	enum ACToken
	{
		AC_TOKEN_CARD				= 0x8000,
		AC_TOKEN_FLAG				= 0x80,
		AC_TOKEN_USER				= AC_TOKEN_FLAG | 0,
		AC_TOKEN_SO					= AC_TOKEN_FLAG | 1,
		AC_TOKEN_USER_OR_SO			= AC_TOKEN_FLAG | 2,
		AC_TOKEN_USER_AND_SO		= AC_TOKEN_FLAG | 3,
		AC_TOKEN_ADMIN				= AC_TOKEN_FLAG | 4,
		AC_TOKEN_SIGN				= AC_TOKEN_FLAG | 5,
		AC_TOKEN_UNBLOCK			= AC_TOKEN_FLAG | 6,
		/* ... */
	};

	//!
	//! \brief Index for known authentication-id's.
	// -----------------------------------------------------------------------
	enum AIIndex
	{
		AI_INVALID					= -1,
		AI_CARD						= AC_TOKEN_CARD			& ~AC_TOKEN_FLAG,
		AI_USER						= AC_TOKEN_USER			& ~AC_TOKEN_FLAG,
		AI_SO						= AC_TOKEN_SO			& ~AC_TOKEN_FLAG,
		AI_USER_OR_SO				= AC_TOKEN_USER_OR_SO	& ~AC_TOKEN_FLAG,
		AI_USER_AND_SO				= AC_TOKEN_USER_AND_SO	& ~AC_TOKEN_FLAG,
		AI_ADMIN					= AC_TOKEN_ADMIN		& ~AC_TOKEN_FLAG,
		AI_SIGN						= AC_TOKEN_SIGN			& ~AC_TOKEN_FLAG,
		AI_UNBLOCK					= AC_TOKEN_UNBLOCK		& ~AC_TOKEN_FLAG,
		//							...
		// Also known as
		AI_PIN						= AI_USER,
		AI_PUK						= AI_SO,
		AI_PIN_OR_PUK				= AI_USER_OR_SO,
		AI_PIN_AND_PUK				= AI_USER_AND_SO,
		//							...
	};

	enum ACOperation				ACT_ENUM_TYPE(byte)
	{
		AC_OR						= 0x00,
		AC_AND						= 0x01,
	};

	enum ACMode						ACT_ENUM_TYPE(byte)
	{
		AC_MODE_READ				= 0,
		AC_MODE_UPDATE				= 1,
		AC_MODE_EXECUTE				= 2,
		AC_MODE_DELETE				= 3,
	};

	enum ACRight					ACT_ENUM_TYPE(byte)
	{
		// Used for EF/DF or Objects
		AC_NONE						= 0xff,
		AC_INVALID					= AC_NONE,

		// Used for duplicates
		AC_ANY_08					= 0x08,
		AC_ANY_09					= 0x09,
		AC_ANY_10					= 0x0a,

		// Used for EF/DF
		AC_READ						= 0x00,
		AC_LCYCLE					= 0x00,
		AC_WRITE					= 0x01,
		AC_UPDATE					= 0x01,
		AC_APPEND					= 0x02,
		AC_DEACTIVATE				= 0x03,
		AC_LOCK						= 0x03,
		AC_ACTIVATE					= 0x04,
		AC_UNLOCK					= 0x04,
		AC_DELETE					= 0x05,
		AC_ADMIN					= 0x06,
		AC_CREATE					= 0x07,
		AC_INCREASE					= AC_ANY_08,
		AC_DECREASE					= AC_ANY_09,
		AC_TERMINATE				= AC_ANY_10,

		// Used for Objects
		AC_USE						= 0x00,
		AC_CHANGE					= 0x01,
		AC_UNBLOCK					= 0x02,
		AC_PUT_DATA					= 0x03,
		AC_GET_DATA					= 0x04,
		AC_GENKEY					= 0x07,
		AC_SIGN						= AC_ANY_08,
		AC_DECENC					= AC_ANY_09,
		AC_DEC						= AC_ANY_09,
		AC_ENC						= AC_ANY_10,
	};

	enum ACRange					ACT_ENUM_TYPE(byte)
	{
		AC_FIRST					= AC_READ,
		AC_LAST						= AC_ENC,
	};

	//!
	//! \brief IAccessCondition
	// -----------------------------------------------------------------------
	class IAccessCondition : public IRefCounted
	{
	public:
		virtual IAccessCondition*	Clone() const = 0;

		virtual const char*			GetName() const = 0;
		virtual ACType				GetAcType() const = 0;
		virtual ACObjType			GetAcObjType() const = 0;
		virtual const Blob&			GetAccessRights() const = 0;

		virtual IAccessCondition*	SetAccessRights(move_from<Blob> ac, ACObjType acObjType) = 0;
		virtual IAccessCondition*	ConvertAc(const IToken* token, ACType acType) const = 0;
	};

	//!
	//! \brief IAcConverter
	// -----------------------------------------------------------------------
	class IAcConverter
	{
	protected:
		virtual ~IAcConverter() { }

	public:
		virtual IAccessCondition*	ConvertAc(const Blob& ac) const = 0;
		virtual Blob				ConvertAc(const IAccessCondition* ac) const = 0;
		virtual IAccessCondition*	ConvertAc(const IAccessCondition* ac, ACType acType) const = 0;
	};

} // namespace act

#endif	// ACT_IAccessConditions_h
