// ---------------------------------------------------------------------------
// Name:      actTokenBase.h
// Product:   cv act library
// Purpose:   Declares common token enums and constants.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/24/2010
// ---------------------------------------------------------------------------

#ifndef ACT_TokenBase_h
#define ACT_TokenBase_h

#include "actBlob.h"
#include "actSCardOSBase.h"

namespace act
{
	enum TokenError
	{
		TOKEN_SUCCESS					=  0,
		TOKEN_FUNCTION_NOT_SUPPORTED	= -1,
		TOKEN_FUNCTION_FAILED			= -2,
		TOKEN_LOCKED					= -3
	};

	enum TokenType						ACT_ENUM_TYPE(ushort)
	{
		TOKEN_NOT_INITIALIZED			= 0xffff,
		TOKEN_UNKNOWN					= 0x0000,

		TOKEN_RSA						= 0x0001,
		TOKEN_DSA						= 0x0002,
		TOKEN_DH						= 0x0004,
		TOKEN_ECDSA						= 0x0008,
		TOKEN_ECDH						= 0x0010,
		TOKEN_SECRET					= 0x0080,

		TOKEN_BAC						= 0x0100,
		TOKEN_EAC						= 0x0200,
		TOKEN_EPA						= 0x0400,
		TOKEN_PACE						= 0x0800,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(TokenType);

	enum TokenStatusCode				ACT_ENUM_TYPE(ulong)
	{
		TOKEN_EMPTY						= 0x0000,
		TOKEN_INITIALIZED				= 0x0001,
		TOKEN_PERSONALIZED				= 0x0002
	};

	enum TokenReset						ACT_ENUM_TYPE(ushort)
	{
		TOKEN_RESET_LOGOUT				= 0x3F0C,
		TOKEN_RESET_CARD				= 0x95A6,
		TOKEN_RESET_SM					= 0xD4B3,
		TOKEN_RESET_DEFAULT				= TOKEN_RESET_LOGOUT,
	};

	enum ProfileType					ACT_ENUM_TYPE(byte)
	{
		PROFILE_EMPTY					= 0x00,
		PROFILE_CV						= 0x01,
		PROFILE_CNS						= 0x02,
		PROFILE_GDO						= 0x03,
		PROFILE_CVEC					= 0x04,
		PROFILE_SIGG					= 0x05,
		PROFILE_JC						= 0x06,
		PROFILE_MICARDOEC				= 0x07,
		PROFILE_SIGNTRUST				= 0x08,
		PROFILE_NETKEY					= 0x09,
		PROFILE_CVMOC					= 0x0a,

		PROFILE_PKCS15					= 0x0f,		//<! Includes \a ePasslet-Suite based PACE-Pin's and PACE-C/R, etc.

		PROFILE_PKCS15_mEAC				= 0x40,		//<! Includes PACE-Pin's
		PROFILE_PKCS15_mEAC_TA			= 0x41,		//<! Includes PACE-Pin's and TA-IS, TA-ST, TA-AT

		PROFILE_BAC						= 0x80,
		PROFILE_EAC						= 0x81,
		PROFILE_EAC201					= 0x82,
		PROFILE_EAC210					= 0x83,
		PROFILE_EPA						= 0x84,
		PROFILE_PACE					= 0x85,		//!< Implements PACEv2 only functionality.

		PROFILE_PKCS11					= 0xa0,		//!< Used by \a PKCS11Token.
		PROFILE_CSP						= 0xa1,		//!< Used by \a CSPToken.
		PROFILE_MD						= 0xa2,		//!< RFU - MDToken.
		PROFILE_RFU_TOKEN_03			= 0xa3,		//!< RFU
		PROFILE_RFU_TOKEN_04			= 0xa4,		//!< RFU
		PROFILE_RFU_TOKEN_05			= 0xa5,		//!< RFU
		PROFILE_RFU_TOKEN_06			= 0xa6,		//!< RFU
		PROFILE_RFU_TOKEN_07			= 0xa7,		//!< RFU

		PROFILE_ANY						= 0xfe,
		PROFILE_UNKNOWN					= 0xff
	};

	// -----------------------------------------------------------------------
	enum KeyType						ACT_ENUM_TYPE(ulong)
	{
		KEY_UNKNOWN						= 0xffff,
		//! NOTE: Never change (!), used for serialization.
		KEY_RSA							= 0x0000,
		KEY_DSA							= 0x0001,
		KEY_DH							= 0x0002,
		KEY_ECDSA						= 0x0003,
		KEY_ECDH						= 0x0004,
		KEY_EC							= 0x0005,

		KEY_SECRET						= 0x0010,
		KEY_DES							= 0x0001 + KEY_SECRET,
		KEY_DES3						= 0x0003 + KEY_SECRET,
		KEY_AES							= 0x0004 + KEY_SECRET,

		KEY_TYPE_MASK					= 0x001f
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(KeyType);

	// -----------------------------------------------------------------------
	enum KeyUsage							ACT_ENUM_TYPE(ulong)
	{
		UNUSABLE							= 0x0000,
		//! NOTE: Never change (!), used for serialization.
		KEY_EMPTY							= UNUSABLE,
		SIGN_DATA							= 0x0001,
		DEC_DATA							= 0x0002,
		AGREE_KEY							= 0x0004,
		AUTH_DATA							= 0x0008,
		BLOCKCIPHER_KEY						= 0x0010,
		VERIFY_DATA							= 0x0020,
		ENC_DATA							= 0x0040,
		UNLOCK_PIN							= 0x0100,
		UPDATE_BINARY						= 0x0200,
		DELETE_BINARY						= 0x0400,
		ALL_USAGE							= 0xffff,

		// custom usage
		SIGN_HASH							= 0x00010000,
		CUSTOM_USAGE_MASK					= 0xffff0000,

		// combined usage
		ENC_DEC_DATA						= DEC_DATA  | ENC_DATA,
		SIGN_DEC_DATA						= DEC_DATA  | SIGN_DATA,
		SIGN_HASH_DATA						= SIGN_HASH | SIGN_DATA,
		SIGN_AGREE							= SIGN_DATA  | AGREE_KEY,
		SIGN_DEC_AGREE						= SIGN_DEC_DATA  | AGREE_KEY, //!< For PIN objects only.
	};

	// -----------------------------------------------------------------------
	enum
	{
		PACE_USAGE_USER						= (SIGN_DEC_AGREE  | UNLOCK_PIN),
		PACE_USAGE_SESSION					= (PACE_USAGE_USER ^ UNLOCK_PIN),
		PACE_USAGE_SO						= (PACE_USAGE_USER ^ SIGN_DEC_AGREE),
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(KeyUsage);

	// -----------------------------------------------------------------------
	typedef KeyUsage					PinUsage;

	// -----------------------------------------------------------------------
	enum PaddingMode					ACT_ENUM_TYPE(ulong)
	{
		PADDING_OFF_CARD				= 0x0000,
		PADDING_ON_CARD					= 0x0001,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(PaddingMode);

	// -----------------------------------------------------------------------
	enum EncodingMode					ACT_ENUM_TYPE(ulong)
	{
		HASH_OFF_CARD					= 0x0000,
		HASH_PUT_VALUE					= 0x0001,
		HASH_LAST_ROUND_ON_CARD			= 0x0002,
		HASH_ON_CARD					= 0x0004,

		ENCODING_OFF_CARD				= HASH_OFF_CARD,
		ENCODING_ON_CARD				= HASH_ON_CARD,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(EncodingMode);

	// -----------------------------------------------------------------------
	enum PinType						ACT_ENUM_TYPE(ulong)
	{
		// role definitions.
		UNKNOWN_PIN						= 0x0000,
		SO_PIN							= 0x0001, 
		USER_PIN						= 0x0002,
		UNBLOCK_PIN						= 0x0003,

		PIN_ROLE_MASK					= 0x000f,
		PIN_ROLE_ANY					= 0x0000,

		//! Type definitions.
		STANDARD_PIN					= 0x0000,
		EXAUTH_PIN						= 0x0010,
		BIOMETRIC_PIN					= 0x0020,
		CERTBASED_PIN					= 0x0030,

		//! Special EAC type flags - used by \a ePAProfile.
		//! Encoded to profile, requires non standard PKCS#15 extensions!
		EAC_PACE_PIN					= 0x0040,	//!< EACv2 PACEv2.x Password, TR-03110 compliant (like EPA).
		EAC_TA_PIN						= 0x0050,	//!< EACv2 Terminal Authentication compatible with TR-03110, \sa TokenAuthTA.
		EAC_CA_PIN						= 0x0060,	//!< EACv2 Chip Authentication compatible with TR-03110, \sa TokenAuthCA. 

		PIN_TYPE_MASK					= 0x00f0,
		PIN_TYPE_ANY					= 0x0000,

		PIN_ROLE_TYPE_MASK				= PIN_ROLE_MASK    | PIN_TYPE_MASK,
		PIN_ROLE_TYPE_ANY				= PIN_ROLE_ANY     | PIN_TYPE_ANY,

		//! Additional flags.
		//! Only valid during runtime, never encoded!
		DEFAULT_PIN						= 0x0000,	//!< Default type flags.
		SESSION_PIN						= 0x0100,	//!< Can't be set as default, \sa cvProfile::CreatePin.
		PACE_PIN						= 0x0200,	//!< Indicates a PACEv2.x Password, compatible but not used in
													//!< TR-03110 context, \sa PACEToken \sa TokenAuthPACE.
		PIN_TYPE_FLAGS					= 0x7f00,

		PIN_MASK						= PIN_TYPE_FLAGS   | PIN_ROLE_TYPE_MASK,

		AUTHENTICATED_PIN				= 0x8000,	//!< Authentication state.

		// type masks
		PIN_TYPE_PACE_MASK				= PACE_PIN         | EAC_PACE_PIN,

		// known role / type combinations
		EXAUTH_SO_PIN					= EXAUTH_PIN       | SO_PIN,
		EXAUTH_UNBLOCK_PIN				= EXAUTH_PIN       | UNBLOCK_PIN,

		BIOMETRIC_SO_PIN				= BIOMETRIC_PIN    | SO_PIN,
		BIOMETRIC_USER_PIN				= BIOMETRIC_PIN    | USER_PIN,

		SESSION_USER_PIN				= SESSION_PIN      | USER_PIN,

		PACE_SO_PIN						= PACE_PIN         | SO_PIN,
		PACE_USER_PIN					= PACE_PIN         | USER_PIN,
		PACE_UNBLOCK_PIN				= PACE_PIN         | UNBLOCK_PIN,
		PACE_UNKNOWN_PIN				= PACE_PIN         | UNKNOWN_PIN,

		PACE_EXAUTH_PIN					= PACE_PIN         | EXAUTH_PIN,
		PACE_EXAUTH_SO_PIN				= PACE_EXAUTH_PIN  | SO_PIN,

		PACE_SESSION_PIN				= PACE_PIN         | SESSION_PIN,
		PACE_SESSION_USER_PIN		    = PACE_SESSION_PIN | SESSION_USER_PIN,

		EAC_PACE_SO_PIN					= EAC_PACE_PIN     | SO_PIN,
		EAC_PACE_USER_PIN				= EAC_PACE_PIN     | USER_PIN,
		EAC_PACE_UNBLOCK_PIN			= EAC_PACE_PIN     | UNBLOCK_PIN,
		EAC_PACE_UNKNOWN_PIN			= EAC_PACE_PIN     | UNKNOWN_PIN,

		EAC_TA_SO_PIN					= EAC_TA_PIN       | SO_PIN,
		EAC_TA_USER_PIN					= EAC_TA_PIN       | USER_PIN,
		EAC_TA_UNKNOWN_PIN				= EAC_TA_PIN       | UNKNOWN_PIN,

		EAC_CA_SO_PIN					= EAC_CA_PIN       | SO_PIN,
		EAC_CA_USER_PIN					= EAC_CA_PIN       | USER_PIN,
		EAC_CA_UNKNOWN_PIN				= EAC_CA_PIN       | UNKNOWN_PIN,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(PinType);
	typedef PinType PinRole;

	// -----------------------------------------------------------------------
	enum PinFlags						ACT_ENUM_TYPE(ulong)
	{
		PIN_FLAGS_INVALID				= 0,
		PIN_INITIALIZED					= (1 <<  0),
		PIN_IS_LOCAL					= (1 <<  1),
		PIN_CASE_SENSITIVE				= (1 <<  2),
		PIN_CHANGE_DISABLED				= (1 <<  3),
		PIN_UNBLOCK_DISABLED			= (1 <<  4),
		PIN_DISABLE_ALLOWED				= (1 <<  5),
		PIN_NEEDS_PADDING				= (1 <<  6),
		PIN_NEEDS_UPDATE				= (1 <<  7),
		PIN_REQUIRES_SM					= (1 <<  8),
		PIN_REQUIRES_NO_DATA			= (1 <<  9),
		PIN_REQUIRES_ENCRYPTION			= (1 << 10),
		PIN_CHANGE_REQUIRES_OLD			= (1 << 11),
		PIN_RESET_RETRY_COUNTER_1		= (1 << 12),
		PIN_RESET_RETRY_COUNTER_2		= (1 << 13),
		PIN_CONTEXT_DEPENDENT			= (1 << 14),
		PIN_MULTI_STEP_PROTOCOL			= (1 << 15),
		PIN_IS_DEFAULT					= (1 << 16),	// marks the one and only default pin

		PIN_FLAGS_MASK					= (1 << 17) - 1,

		// combined flags - global
		PIN_FLAGS						= PIN_INITIALIZED | PIN_CASE_SENSITIVE,
		PIN_FLAGS_SO					= PIN_FLAGS       | PIN_UNBLOCK_DISABLED,
		PIN_FLAGS_PACE					= PIN_FLAGS       | PIN_REQUIRES_ENCRYPTION,
		PIN_FLAGS_CERTBASED				= PIN_INITIALIZED | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED,
		PIN_FLAGS_DEFAULT				= PIN_FLAGS       | PIN_IS_DEFAULT,
		PIN_FLAGS_BIOMETRIC				= PIN_INITIALIZED,
		PIN_FLAGS_EXAUTH				= PIN_INITIALIZED,

		// combined flags - local
		PIN_LOCAL						= PIN_IS_LOCAL    | PIN_FLAGS,
		PIN_LOCAL_SO					= PIN_IS_LOCAL    | PIN_FLAGS_SO,
		PIN_LOCAL_DEFAULT				= PIN_IS_LOCAL    | PIN_FLAGS_DEFAULT,
		PIN_LOCAL_EXAUTH				= PIN_IS_LOCAL    | PIN_FLAGS_EXAUTH,
		PIN_LOCAL_BIOMETRIC				= PIN_IS_LOCAL    | PIN_FLAGS_BIOMETRIC,
		PIN_LOCAL_CERTBASED				= PIN_IS_LOCAL    | PIN_FLAGS_CERTBASED,
	};

	// -----------------------------------------------------------------------
	enum
	{
		PACE_FLAGS_SESSION				= PIN_FLAGS_PACE  | PIN_DISABLE_ALLOWED,
		PACE_FLAGS_DEFAULT				= PIN_IS_DEFAULT  | PACE_FLAGS_SESSION,
		PACE_FLAGS_SO					= PIN_FLAGS_PACE  | PIN_UNBLOCK_DISABLED,
	};

	enum
	{
		PACE_PIN_FLAGS					= PIN_INITIALIZED | PIN_CASE_SENSITIVE   | PIN_DISABLE_ALLOWED | PIN_MULTI_STEP_PROTOCOL,
		PACE_PUK_FLAGS					= PIN_INITIALIZED | PIN_CASE_SENSITIVE   | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_MULTI_STEP_PROTOCOL,
		PACE_CAN_FLAGS					= PIN_INITIALIZED | PIN_CASE_SENSITIVE   | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_MULTI_STEP_PROTOCOL,
		PACE_MRZ_FLAGS					= PIN_INITIALIZED | PIN_CASE_SENSITIVE   | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_MULTI_STEP_PROTOCOL,
		TA_IS_FLAGS						= PIN_INITIALIZED | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_REQUIRES_SM,
		TA_ST_FLAGS						= PIN_INITIALIZED | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_REQUIRES_SM,
		TA_AT_FLAGS						= PIN_INITIALIZED | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_REQUIRES_SM,
		CA_FLAGS						= PIN_INITIALIZED | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED | PIN_REQUIRES_SM,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(PinFlags);

	// -----------------------------------------------------------------------
	enum AuthId							ACT_ENUM_TYPE(byte)
	{
		AUTHID_INVALID					= 0x00,
		AUTHID_SIZE						= 0x01,		//!< size of authid in bytes
	};

	// -----------------------------------------------------------------------
	enum BioFinger						ACT_ENUM_TYPE(byte)
	{
		FINGER_UNKNOWN					= 0,
		FINGER_RIGHT_THUMB				= 1,
		FINGER_RIGHT_INDEX				= 2,
		FINGER_RIGHT_MIDDLE				= 3,
		FINGER_RIGHT_RING				= 4,
		FINGER_RIGHT_LITTLE				= 5,
		FINGER_LEFT_THUMB				= 6,
		FINGER_LEFT_INDEX				= 7,
		FINGER_LEFT_MIDDLE				= 8,
		FINGER_LEFT_RING				= 9,
		FINGER_LEFT_LITTLE				= 10
	};

	// -----------------------------------------------------------------------
	enum CertificateType				ACT_ENUM_TYPE(ushort)
	{
		CERT_UNKNOWN					= 0xffff,
		//! NOTE: Never change (!), used for serialization.
		CERT_X509						= 0x0000,
		CERT_CV							= 0x0001
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(CertificateType);

	// -----------------------------------------------------------------------
	enum CertificateUsage				ACT_ENUM_TYPE(ushort)
	{
		EMPTY_CERT						= 0x0000, 
		SIGN_CERT						= 0x0001, 
		DEC_CERT						= 0x0002, 
		ROOT_CERT						= 0x0004, 
		AUTH_CERT						= 0x0008, 
		CA_CERT							= 0x0010,
		SMARTCARD_LOGON_CERT			= 0x0100,	//!< lib version >= 1.5
		UNSPECIFIED_CERT				= 0xffff
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(CertificateUsage);

	// -----------------------------------------------------------------------
	enum SecStatus						ACT_ENUM_TYPE(ushort)
	{
		SS_INVALID						= 0x0000,
		SS_AUTHENTICATED				= 0x0001,
		SS_UNKNOWN						= 0xffff,
	};

	enum AuthObjType					ACT_ENUM_TYPE(byte)
	{
		AUTH_OBJ_PIN					= 0xff,		// -1
		AUTH_OBJ_BIOMETRIC				= 0xfe,		// -2
	};

	enum EncodingType
	{
		ENCODING_UNKNOWN				= -1,
		ENCODING_BINARY					=  0,
		ENCODING_ASCII_NUMERIC			=  1,
		ENCODING_UTF8					=  2,
		ENCODING_BCD					=  3,
		ENCODING_HALF_NIBBLE_BCD		=  4,
		ENCODING_ISO9564_1				=  5,

		ENCODING_DEFAULT				= ENCODING_ASCII_NUMERIC,
	};

	// ---------------------------------------------------------------------------
	template<typename value_type>
	struct Compare
	{
		Compare(value_type value_) : value(value_) { }

		bool operator==(const value_type& other) const { return (value & other) == other; }
		bool operator!=(const value_type& other) const { return (value & other) != other; }

		bool operator==(const Compare<value_type>& other) const
		{
			return *this == other.value;
		}

		bool operator!=(const Compare<value_type>& other) const
		{
			return *this != other.value;
		}

		const value_type value;
	};

#	include "actPackOn.h"

	//
	// FileInfo
	// ---------------------------------------------------------------------------
	struct FileInfo
	{
		enum { invalid = FID_INVALID };

		explicit FileInfo(FIDType val_fid = invalid, IDType val_rec = invalid)
			: rec_nr(val_rec), fid(val_fid)
		{ }

		FIDType	fid;
		IDType	rec_nr;
	};

	inline bool Equals(const FileInfo& left, const FileInfo& right)
	{
		return left.fid == right.fid
			&& left.rec_nr == right.rec_nr;
	}

	//
	// LengthInfo
	// ---------------------------------------------------------------------------
	struct LengthInfo
	{
		LengthInfo(ulong minLen_ = 0, ulong maxLen_ = 0, ulong storedLen_ = 0)
			: minLen(minLen_)
			, maxLen(maxLen_)
			, storedLen(storedLen_)
		{ }

		void swap(LengthInfo& other)
		{
			ulong val;
			val = other.minLen;    other.minLen = minLen;       minLen = val;
			val = other.maxLen;    other.maxLen = maxLen;       maxLen = val;
			val = other.storedLen; other.storedLen = storedLen; storedLen = val;
		}

		ulong minLen;
		ulong maxLen;
		ulong storedLen;
	};

	//
	// GenericAuthInfo
	// ---------------------------------------------------------------------------
	struct GenericAuthInfo
	{
		const char*		name;
		cbyte_array		chat;
		cbyte_array		constraints;
		ushort			type;
		ushort			usage;
		PinFlags		flags;
		EncodingType	encodig;
		byte			authId;
		byte			parentId;
		byte			objRef;
		byte			minLen;
		byte			maxLen;		// NOTE: maxLen is used as storedLen if PIN padding enabled
		byte			padChar;
		byte			finger;
		byte			rc;
	};

#	include "actPackOff.h"

} // namespace act

#endif // ACT_TokenBase_h
