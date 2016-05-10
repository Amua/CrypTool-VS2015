// ---------------------------------------------------------------------------
// Name:      actEAC.h
// Product:   cv act library
// Purpose:   Modular EAC common header.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Ulrich Birkenhauer (UBR)
//			  Markus Tesche (MTE)
// Date:	  10/27/2009
// ---------------------------------------------------------------------------

#ifndef ACT_EAC_h
#define ACT_EAC_h

#include "actBlob.h"
#include "actTokenBase.h"

namespace act
{
	const FIDType					FID_EF_CARD_ACCESS		= 0x011C;
	extern const byte_array			EF_CARD_ACCESS_PATH;

	const FIDType					FID_EF_CARD_SECURITY	= 0x011D;
	const FIDType					FID_EF_CHIP_SECURITY	= 0x011B;

	const FIDType					EF_CVCA_FID				= 0x011C;
	const byte						EF_CVCA_TAG				= 0x42;
	const ushort					EF_CVCA_SIZE			= 36;

	const byte						EAC_MAC_LEN				= 0x08; 	//! 8 byte MAC in SM commands and authentication tokens

	extern const byte_array&		EPA_DF;
	extern const byte_array&		EPA_JC_AID;

	extern const byte_array&		PACE_DF;
	extern const byte_array&		PACE_JC_AID;

	//!
	//! \brief PACE mapping modes
	// -----------------------------------------------------------------------
	enum PACEMapping
	{
		PACE_MAPPING_INVALID		= -1,
		PACE_MAPPING_GENERIC		=  0,		//!< EAC 2.01, B.1.2
		PACE_MAPPING_INTEGRATED
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(PACEMapping);

	//!
	//! \brief EAC object references
	//! \see   TR-03110
	// -----------------------------------------------------------------------
	enum EACObjRef
	{
		REF_EAC_PACE_MRZ			= 0x01,					//!< MRZ-Password
		REF_EAC_PACE_CAN			= 0x02,					//!< Card Access Number
		REF_EAC_PACE_PIN			= 0x03,					//!< Personal Identification Number
		REF_EAC_PACE_PUK			= 0x04,					//!< PIN Unblock Key
		REF_EAC_TA					= 0x07,
		REF_EAC_TA_IS				= REF_EAC_TA,
		REF_EAC_TA_ST				= REF_EAC_TA,
		REF_EAC_TA_AT				= REF_EAC_TA,
		REF_EAC_CA					= 0x08,
	};

	//!
	//! \brief EAC protocol versions
	// -----------------------------------------------------------------------
	enum EACVersions
	{
		EAC_TAP_UNKNOWN				= 0,
		EAC_TAP_V1					= 1,
		EAC_TAP_V2					= 2
	};

	//!
	//! \brief EAC 201 authentication-id's
	// -----------------------------------------------------------------------
	enum EACAuthIds
	{
		AUTHID_EAC_PACE_MRZ			= REF_EAC_PACE_MRZ,
		AUTHID_EAC_PACE_CAN			= REF_EAC_PACE_CAN,
		AUTHID_EAC_PACE_PIN			= REF_EAC_PACE_PIN,
		AUTHID_EAC_PACE_PUK			= REF_EAC_PACE_PUK,
		AUTHID_EAC_TA_IS			= 0x16,					//!< Inspection System
		AUTHID_EAC_TA_ST			= 0x18,					//!< Signature Terminal
		AUTHID_EAC_TA_AT			= 0x17,					//!< Authentication Terminal
		AUTHID_EAC_CA				= REF_EAC_CA
	};

	//!
	//! \brief Default EAC Id's
	// -----------------------------------------------------------------------
	enum EACId
	{
		EAC_ID_INVALID				= 0,
		EAC_ID_BEGIN				= 1,
			EAC_ID_PACE_BEGIN		= EAC_ID_BEGIN,
	/*  MRZ  */ EAC_ID_PACE_MRZ		= EAC_ID_PACE_BEGIN,
	/*  CAN  */ EAC_ID_PACE_CAN,
	/*  PIN  */ EAC_ID_PACE_PIN,
	/*  PUK  */ EAC_ID_PACE_PUK,
			EAC_ID_PACE_END,
			EAC_ID_PACE_LENGTH		= EAC_ID_PACE_END,
			EAC_ID_TA_BEGIN			= EAC_ID_PACE_END,
	/* TA_IS */ EAC_ID_TA_IS		= EAC_ID_TA_BEGIN,
	/* TA_ST */ EAC_ID_TA_ST,
	/* TA_AT */ EAC_ID_TA_AT,
			EAC_ID_TA_END,
			EAC_ID_TA_LENGTH		= EAC_ID_TA_END,
			EAC_ID_CA_BEGIN			= EAC_ID_TA_END,
	/* CA    */ EAC_ID_CA			= EAC_ID_CA_BEGIN,
			EAC_ID_CA_END,
			EAC_ID_CA_LENGTH		= EAC_ID_CA_END,
		EAC_ID_END,
		EAC_ID_LENGTH				= EAC_ID_END,
	};

	//!
	//! \brief Key derivation counters (EAC 2.01, A.2.3)
	// -----------------------------------------------------------------------
	enum EACDerivationCounters		ACT_ENUM_TYPE(byte)
	{
		EAC_KDF_KENC_COUNTER		= 1,
		EAC_KDF_KMAC_COUNTER		= 2,
		EAC_KDF_KPI_COUNTER			= 3
	};

	//!
	//! \brief MSE: Set AT modes (set Authentication Template)
	// -----------------------------------------------------------------------
	enum MSESetATModes				ACT_ENUM_TYPE(ushort)
	{
		MSE_SET_AT_PACE				= 0xC1A4,
		MSE_SET_AT_CA				= 0x41A4,
		MSE_SET_AT_TA				= 0x81A4,
		MSE_SET_AT_RI				= 0x41A4
	};

	//
	// Comp() function (EAC 2.01, Table A.2)
	// -----------------------------------------------------------------------
	enum EACCompTypes				ACT_ENUM_TYPE(byte)
	{
		EAC_COMP_ECDH				= 0,
		EAC_COMP_DH					= 1
	};

	//
	// BACNotifications
	// -----------------------------------------------------------------------
	enum BACNotifications			ACT_ENUM_TYPE(ushort)
	{
		TAP_BAC_EXECUTE			= 1,
		TAP_BAC_IN_MRZ,										//!< input, mandatory

		TAP_BAC_LAST										//!< has to be always last !
	};

	//
	// PACENotifications
	// -----------------------------------------------------------------------
	enum PACENotifications
	{
		TAP_PACE_EXECUTE = TAP_BAC_LAST,					//!< starts with BAC last
		TAP_PACE_IN_CHAT,									//!< input, optional (mandatory if TA after PACE (v2))

		TAP_PACE_OUT_NONCE,									//!< output, optional (challenge notification for ExAuth PACE PINs)

		TAP_PACE_OUT_RECENT_CA_REF,							//!< output, always (empty if no CHAT)
		TAP_PACE_OUT_PREVIOUS_CA_REF,						//!< output, always (empty if no CHAT)
		TAP_PACE_OUT_COMP_MRTD_EPHEMERAL_PUBKEY,			//!< output, always

		TAP_PACE_LAST										//!< has to be always last !
	};

	//
	// TANotifications
	// -----------------------------------------------------------------------
	enum TANotifications
	{
		TAP_TA_EXECUTE = TAP_PACE_LAST,						//!< starts with PACE last

		// for ID PICC
		TAP_TA_IN_COMP_MRTD_EPHEMERAL_PUBKEY_FROM_PACE,		//!< v2: input, mandatory
		TAP_TA_IN_MRTD_DOCUMENT_NUMBER_MRZ,					//!< v1: input, mandatory

		// for certificate chain verification
		TAP_TA_IN_RECENT_CA_REF_FROM_PACE,					//!< v2: input, mandatory
		TAP_TA_IN_PREVIOUS_CA_REF_FROM_PACE,				//!< v2: input, mandatory
		TAP_TA_OUT_RECENT_CA_REF_EFCVCA,					//!< v1: output, always
		TAP_TA_OUT_PREVIOUS_CA_REF_EFCVCA,					//!< v1: output, always
		TAP_TA_IN_CERT_OF_CHAIN,							//!< v1/2: input, mandatory

		// for previous CA
		TAP_TA_IN_EPHEMERAL_PUBKEY_FROM_CA,					//!< v1: input, mandatory

		// for authentication
		TAP_TA_IN_AUX_DATA,									//!< v2: input, optional
		TAP_TA_OUT_SIGN_DATA,								//!< v1/2: output, always
		TAP_TA_IN_SIGNATURE,								//!< v1/2: input, mandatory

		// for following CA
		TAP_TA_OUT_EPHEMERAL_PRIVKEY_FOR_CA,				//!< v2: output, always

		TAP_TA_LAST											//!< has to be always last !
	};

	//
	// CANotifications
	// -----------------------------------------------------------------------
	enum CANotifications
	{
		TAP_CA_EXECUTE = TAP_TA_LAST,						//!< starts with TA last - 1

		TAP_CA_IN_EPHEMERAL_PRIVKEY_FROM_TA,				//!< v2: input, mandatory
		TAP_CA_OUT_EPHEMERAL_PUBKEY_FOR_TA,					//!< v1: output, always

		TAP_CA_LAST											//!< has to be always last !
	};

	// -----------------------------------------------------------------------
#	include "actPackOn.h"

	//!
	//! \brief Simplified structure used during profile creation.
	//! \note  Fields where the content equals to those of \a GenericPinInfo have to be named accordingly.
	//! \sa    GenericPinInfo
	// -----------------------------------------------------------------------
	struct EACPinInfo
	{
		byte						id;
		const char*					name;
		const byte_array			typeSpecific;
		const byte_array			constraints;
		ushort						type;
		ushort						usage;
		ulong						flags;
		byte						parentId;				//!< parent authentication-id.
		byte						authId;					//!< authentication-id.
		byte						objRef;
		byte						minLen;
		byte						maxLen;
	};

	extern const EACPinInfo			PACEPinInfos[];
	extern const size_t				PACEPinInfoSize;

	extern const EACPinInfo			EACPinInfos[];
	extern const size_t				EACPinInfoSize;

	extern const EACPinInfo			EACPinInvalid;

#	include "actPackOff.h"

	// -----------------------------------------------------------------------
	class IAgreementKey;
	class SmartcardException;
	struct AuthProtocolState;

	namespace eac
	{
		//!
		//! \brief   Update EAC password state.
		//! \details Translate protocol specific card errors and update \a state.
		//! \par     Used during protocol execution to update:
		//!          - \a SmartcardException, encapsulated status word \see APDUResponse.
		//!          - \a authprotocolstate, depending on status word.
		//! \return  \a true if handled or \a false which may indicate an error.
		// -------------------------------------------------------------------
		bool set_password_state(SmartcardException& e, AuthProtocolState& state);

		// -------------------------------------------------------------------
		bool map_password_state(SmartcardException& e, AuthProtocolState& ps, const Blob& sm);

		//
		// protocol_state_to_string
		const char* protocol_state_to_string(int state);
		const char* protocol_state_to_string(const AuthProtocolState& ps);

		//
		// compress_pubkey
		void compress_pubkey(Blob& pubkey, int comp_type);

		//
		// GetStandardizedDomainParams
		void standardized_domain_parameters(Blob& params, const Blob& id);

	}	// namespace eac
}		// namespace act

#endif	// ACT_EAC_h
