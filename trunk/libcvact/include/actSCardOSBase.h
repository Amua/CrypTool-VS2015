// ---------------------------------------------------------------------------
// Name:      actSCardOSBase.h
// Product:   cv act library
// Purpose:   Declares common ISCardOS enums and constants.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  01/22/2013
// ---------------------------------------------------------------------------

#ifndef ACT_SCardOSBase_h
#define ACT_SCardOSBase_h

#include "actEnv.h"
#include "actBasics.h"

namespace act
{
	class Blob;
	class ISCardOS;

	// -----------------------------------------------------------------------
	typedef ulong	IDType;
	typedef ushort	FIDType;

	const IDType	ID_INVALID				=  0;
	const FIDType	FID_INVALID				=  0;
	const FIDType	FID_DEFAULT				=  FID_INVALID;
	const FIDType	FID_NOT_INITIALIZED		= ~FID_INVALID;

	const FIDType	FID_EF_DIR				= 0x2F00;
	const FIDType	FID_EF_ATR				= 0x2F01;
	const FIDType	FID_EF_SN				= 0x2F02;

	const int		SIZE_INVALID			= -1;
	const ushort	SIZE_NOT_INITIALIZED	= ushort(SIZE_INVALID);

	const int		UC_UNKNOWN				= -1;			//!< Usage counter is unknown, may not obtainable
	const int		RC_UNKNOWN				= -1;			//!< Data requested is not obtainable
	const int		RC_COUNT_LOW			= -2;			//!< Unspecified count, but lower than maximum (e.g. PIN after a failed login attempt)

	const size_t	SIZE_UNKNOWN			= size_t(-1);	//!< Data requested is not obtainable

	//
	// ISO 7816-4 APDU constants
	// -----------------------------------------------------------------------
	enum
	{
		APDU_NO_LE					= size_t(-1),
		APDU_OFFSET_CLA				= 0,
		APDU_OFFSET_INS				= 1,
		APDU_OFFSET_P1				= 2,
		APDU_OFFSET_P2				= 3,
		APDU_LENGTH_HEADER			= 4,
		APDU_OFFSET_LC				= APDU_LENGTH_HEADER,
		APDU_LENGTH_LC				= 1,
		APDU_LENGTH_HEADER_LC		= APDU_LENGTH_HEADER + APDU_LENGTH_LC,
		APDU_OFFSET_DATA			= APDU_LENGTH_HEADER_LC,
		APDU_OFFSET_LE				= APDU_OFFSET_LC,
		APDU_LENGTH_LE				= 1,
		APDU_LENGTH_HEADER_LC_LE	= APDU_LENGTH_HEADER_LC + APDU_LENGTH_LE,
		APDU_MAX_RECEIVE			= 0x100,
		APDU_MAX_SEND				= 0xFF,
		APDU_LENGTH_MAX_SEND		= APDU_MAX_SEND + APDU_LENGTH_HEADER_LC_LE,
		APDU_EXTENDED_MAX_SEND		= 0xFFFF,
		APDU_CHAINING_SEND			= 0xC0,
		APDU_BUFFER_SIZE			= 1462,
		APDU_MAX_LE_BYTE			= 0xFF,
		APDU_MAX_LE_SHORT			= 0xFFFF,
		APDU_MAX_OFFSET				= 0x7FFF,
		APDU_CLA_DEFAULT			= 0x00,
		APDU_CLA_PROPRIETARY		= 0x80,
		APDU_CLA_CHAINING			= 0x20,
	};

	//
	// ISO 7816-4
	// -----------------------------------------------------------------------
	enum SCardFileType
	{
		UNKNOWN_FILE_TYPE					= 0x00,

		// EF types
		BINARY								= 0x01,
		LINEAR_FIXED						= 0x02,
		LINEAR_FIXED_TLV					= 0x03,
		LINEAR_VARIABLE						= 0x04,
		LINEAR_TLV							= 0x05,
		CYCLIC_FIXED						= 0x06,

		// DF type
		DF									= 0x38,

		// additional masks and flags
		EF_TYPE_MASK						= 0x07,
		EF_LOCAL							= 0x10,
		SHAREABLE							= 0x40,

		// additional security flags
		EF_SECURITY_DEFAULT					= 0x00,
		EF_SECURITY_RELATED					= 0x20,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(SCardFileType);

	//
	// ISO 7816 Tags
	// -----------------------------------------------------------------------
	enum ISO7816_Tags
	{
		ISO7816_8_TAG_PUBKEY_DO				= 0x7F49,
	};

	//
	// ISO 7816-4
	// -----------------------------------------------------------------------
	enum SCardRecordMode
	{
		ABSOLUTE_MODE						= 0x04
	};

	//
	// ISO 7816-9
	// -----------------------------------------------------------------------
	enum SCardDeleteType
	{
		CURRENT_FILE						= 0x00,
		CHILD_DF							= 0x01,
		CHILD_EF							= 0x02,
	};

	// -----------------------------------------------------------------------
	enum SCardSelectMode
	{
		FCI									= 0x00,		//!< FCI template
		FCP									= 0x04,		//!< FCP template
		FMD									= 0x08,		//!< FMD template
		NoData								= 0x0c,		//!< No response data
	};

	//!
	//! \brief ISO 7816-4
	// -----------------------------------------------------------------------
	enum FileType							ACT_ENUM_TYPE(byte)
	{
		UKType								= 0xff,
		MFType								= 0x00,
		DFType								= 0x01,
		EFType								= 0x02,
		DFParent							= 0x03,
		AIDType								= 0x04,
		PathType							= 0x08
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(FileType);

	// -----------------------------------------------------------------------
	enum OSFeatureFlags
	{
		OSFF_APDU_EXTENDED					= 0,		//!< bit 0
		OSFF_PRECONF_KEYS					= 1,		//!< bit 1
		OSFF_IS_MOC_VALID					= 2,		//!< bit 2
		OSFF_IS_MOC							= 3,		//!< bit 3
		OSFF_IS_ECC							= 4,		//!< bit 4
		OSFF_IS_AES							= 5,		//!< bit 5
		OSFF_FLAG_06						= 6,		//!< bit 6
		OSFF_FLAG_07						= 7,		//!< bit 7
		OSFF_HAS_CARDID						= 8,		//!< bit 8	
		OSFF_HAS_CARDCF						= 9,		//!< bit 9
		// flag_10 to flag_15 currently unused
		OSFF_CAN_ECDSA_PLAIN				= 16,		//!< bit 16
		OSFF_CAN_ECDSA_SHA1					= 17,		//!< bit 17
		OSFF_CAN_ECDSA_SHA224				= 18,		//!< bit 18
		OSFF_CAN_ECDSA_SHA256				= 19,		//!< bit 19
		OSFF_CAN_ECDSA_SHA384				= 20,		//!< bit 20
		OSFF_CAN_ECDSA_SHA512				= 21,		//!< bit 21
		OSFF_CAN_ECDH_PLAIN					= 22,		//!< bit 22
		// flag_23 to flag_31 currently unused
	};

	// -----------------------------------------------------------------------
	enum
	{
		SCARD_SUCCESS						=  0,
		SCARD_FUNCTION_NOT_SUPPORTED		= -1,
		SCARD_FUNCTION_FAILED				= -2
	};

	// 
	//! \brief secure messaging levels
	// -----------------------------------------------------------------------
	enum OSSMLevel							ACT_ENUM_TYPE(byte)
	{
		SM_LEVEL_DEFAULT					= 0xEE,
		SM_LEVEL_NONE						= 0xFF,
		SM_LEVEL_AUTHENTICATED				= 0x00,
		SM_LEVEL_SIGN						= 0x01,
		SM_LEVEL_ENCRYPT					= 0x02,
		SM_LEVEL_SIGN_AND_ENCRYPT			= SM_LEVEL_SIGN | SM_LEVEL_ENCRYPT,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(OSSMLevel);

	// 
	//! \brief secure messaging key identifier
	// -----------------------------------------------------------------------
	enum OSSecureMessagingKeyID				ACT_ENUM_TYPE(byte)
	{
		SM_KEY_DEFAULT						= 0x00,
		SM_KEY_VERSION_DEFAULT				= SM_KEY_DEFAULT,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(OSSecureMessagingKeyID);

	// 
	//! \brief secure messaging info
	// ---------------------------------------------------------------------------
	struct OSSecureMessagingInfo
	{
		OSSecureMessagingInfo()
			: macKeyId(SM_KEY_DEFAULT)
			, encKeyId(SM_KEY_DEFAULT)
			, keyVersion(SM_KEY_VERSION_DEFAULT)
			, level(SM_LEVEL_SIGN_AND_ENCRYPT)
		{ }

		OSSecureMessagingKeyID	macKeyId;
		OSSecureMessagingKeyID	encKeyId;
		OSSecureMessagingKeyID	keyVersion;

		OSSMLevel				level;
	};

	//!
	//! \brief Security context index.
	// -----------------------------------------------------------------------
	enum SCIndex							ACT_ENUM_TYPE(byte)
	{
		SC_BEGIN							= 0,				//!< First security context index.
		SC_USER								= SC_BEGIN,			//!< User context, default
		SC_ADMIN,												//!< Administration context, like system object creation or special commands.
		SC_SYSTEM,												//!< System context, like booting cardos, mostly inaccessable!
		// ... add additional types here
		SC_END,
		SC_LENGTH							= SC_END,
	};

	// ---------------------------------------------------------------------------
	enum CmdIndex
	{
		CI_SELECT_OBJECT					= 0,
		CI_CREATE_OBJECT					= 1,
		CI_DELETE_OBJECT					= 2,
		CI_RESET_SECSTATE					= 3,
		CI_GARBAGE_COLLECT					= 4,
		CI_GET_FREE_MEMORY					= 5,
	};

	typedef word (FSendSC)(ISCardOS*, CmdIndex, SCIndex, const Blob&, Blob*);

	// ---------------------------------------------------------------------------
	struct OSFileInfo
	{
		OSFileInfo()
			: type(UNKNOWN_FILE_TYPE)
			, size(SIZE_NOT_INITIALIZED)
			, readSize(SIZE_NOT_INITIALIZED)
			, records(SIZE_NOT_INITIALIZED)
			, recordSize(SIZE_NOT_INITIALIZED)
		{ }

		void reset();
		void swap(OSFileInfo& other);

		ushort			size;
		ushort			readSize;			//!< may differ from size for logical end of file support
		ushort			records;
		ushort			recordSize;
		SCardFileType	type;
	};

	// ---------------------------------------------------------------------------
	struct OSKeyInfo
	{
		OSKeyInfo(ushort _id, ulong _usage, size_t _sizeInBits = 0)
			: id(_id)
			, usage(_usage)
			, sizeInBits(_sizeInBits)
			, nonRepudiation(false)
		{ }

		void setNonRepudiation(bool nr) { nonRepudiation = nr; }

		ushort		id;
		ulong		usage;
		size_t		sizeInBits;
		bool		nonRepudiation;
	};

} // namespace act

#endif // ACT_SCardOSBase_h
