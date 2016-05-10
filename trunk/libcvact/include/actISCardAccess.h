// ---------------------------------------------------------------------------
// Name:      actISCardAccess.h
// Product:   cv act library
// Purpose:   The class ISCardAccess manages the operations with the smartcards and readers
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/21/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardAccess_h
#define ACT_ISCardAccess_h

#include "actBlob.h"
#include "actObserver.h"
#include "actTokenBase.h"

#include "actISynchronize.h"
#include "actIEventHandler.h"

namespace act
{
	const ushort RESPONSE_MAXLEN		= 2048;

	enum SCardReturnCode				ACT_ENUM_TYPE(ushort)
	{
		APDU_RESPONSE_MASK				= 0xFFFF,
		APDU_NO_RETRY_MASK				= 0xFFF0,

		APDU_OK							= 0x9000,
		APDU_OK1						= 0x9001,

		// error codes defined in ISO7816-4
		APDU_STATE_UNCHANGED			= 0x6200,
		APDU_RETURN_CORRUPTED			= 0x6281,
		APDU_END_REACHED				= 0x6282,
		APDU_SELECTFILE_INVALID			= 0x6283,
		APDU_FCI_FORMAT					= 0x6284,

		APDU_AUTHEN_FAILED				= 0x6300,
		APDU_RETRY_COUNTER				= 0x63C0,
		APDU_FILE_FILLED_UP				= 0x6381,

		APDU_PINENTRY_TIMEOUT			= 0x6400,
		APDU_PINENTRY_CANCELLED			= 0x6401,
		APDU_PINENTRY_MISMATCH			= 0x6402,
		APDU_PINENTRY_WRONG_LEN			= 0x6403,
		APDU_PINENTRY_ABORT				= 0x6480,
		APDU_PINENTRY_WRONG_DATA		= 0x6B80,

		APDU_DATA_INCONSISTENT			= 0x6400,

		APDU_STATE_UNCHANGED2			= 0x6400,
		APDU_STATE_CHANGED				= 0x6500,
		APDU_MEMORY_FAILURE				= 0x6581,

		APDU_SECURITY_ERROR				= 0x6600,	// not defined in ISO7816

		APDU_WRONG_LEN					= 0x6700,

		APDU_NO_CLA_FUNCTION			= 0x6800,
		APDU_NO_LOGICAL_CHANNEL			= 0x6881,
		APDU_NO_SECURE_MESSAGING		= 0x6882,
		APDU_NO_CHAINING_SUPPORTED		= 0x6884,
		APDU_LAST_COMMAND_EXPECTED		= 0x6883,

		APDU_CMD_NOT_ALLOWED			= 0x6900,
		APDU_CMD_INCOMPATIBLE			= 0x6981,
		APDU_SECURITY_STATE				= 0x6982,
		APDU_AUTHEN_BLOCKED				= 0x6983,
		APDU_REF_DATA_INVALID			= 0x6984,
		APDU_NO_CONDITION				= 0x6985,
		APDU_CMD_EF_NOT_ALLOWED			= 0x6986,
		APDU_SM_DATA_MISSING			= 0x6987,
		APDU_SM_DATA_INCORRECT			= 0x6988,

		APDU_WRONG_PARAMETER			= 0x6A00,
		APDU_WRONG_DATA					= 0x6A80,
		APDU_FUNCTION_NOT_SUPPORTED		= 0x6A81,
		APDU_FILE_NOT_FOUND				= 0x6A82,
		APDU_RECORD_NOT_FOUND			= 0x6A83,
		APDU_NOT_ENOUGH_MEMORY			= 0x6A84,
		APDU_LC_TLV_INCONSISTENT		= 0x6A85,
		APDU_INVALID_P1P2				= 0x6A86,
		APDU_LC_P1P2_INCONSISTENT		= 0x6A87,
		APDU_REF_DATA_NOT_FOUND			= 0x6A88,
		APDU_FILE_ALREADY_EXISTS		= 0x6A89,

		APDU_WRONG_PARAMETER2			= 0x6B00,

		APDU_WRONG_LE					= 0x6C00,

		APDU_INS_INVALID				= 0x6D00,

		APDU_CLA_INVALID				= 0x6E00,

		APDU_TECHNICAL_ERROR			= 0x6F00,


		// other error codes depend on card OS
		APDU_NO_ICC						= 0x64A1,
		APDU_PROTOCOL_ERROR				= 0x64A8,
		
		APDU_NO_AC_RIGHT				= APDU_SECURITY_STATE,
		APDU_PIN_LOCKED					= APDU_AUTHEN_BLOCKED,
		APDU_PIN_FORMAT_ERROR			= APDU_REF_DATA_INVALID,

		APDU_OBJECT_NOT_FOUND			= APDU_REF_DATA_NOT_FOUND,

		APDU_KEYGEN_FAILED				= 0x6F83, // ACOS


		// JavaCardOS
		APDU_MORE_DATA_AVAILABLE		= 0x6310,	
		APDU_APPLET_SELECTION_FAILED	= 0x6999,
		APDU_PIN_FAILED					= 0x69C0,
		APDU_ASSERT						= 0x6FFF,
		APDU_ASSERT_NOTRANSACTION		= 0x6FFE,
	};

	enum SCardSyncMode
	{
		None,
		Transact,
		Recurse,
	};

	enum ScopeType
	{
		SCOPE_INVALID					= -1,
		SCOPE_USER						=  0,		//!< Equals SCARD_SCOPE_USER
		SCOPE_TERMINAL					=  1,		//!< Equals SCARD_SCOPE_TERMINAL
		SCOPE_SYSTEM					=  2,		//!< Equals SCARD_SCOPE_SYSTEM
	};

	enum ShareType
	{
		SHARE_INVALID					= -1,
		SHARE_EXCLUSIVE					=  1,		//!< Equals SCARD_SHARE_EXCLUSIVE
		SHARE_SHARED					=  2,		//!< Equals SCARD_SHARE_SHARED
		SHARE_DIRECT					=  3		//!< Equals SCARD_SHARE_DIRECT
	};

	enum ProtocolType
	{
		PROTOCOL_UNDEFINED				= 0x00000,	//!< There is no active protocol.
		PROTOCOL_T0						= 0x00001,	//!< T=0 is the active protocol.
		PROTOCOL_T1						= 0x00002,	//!< T=1 is the active protocol.
		PROTOCOL_ANY					= PROTOCOL_T0 | PROTOCOL_T1,
		PROTOCOL_RAW					= 0x10000	//!< Raw is the active protocol.
	};

	enum DispositionType
	{
		LEAVE_CARD						= 0x0000,	//!< Don't do anything special. 
		RESET_CARD						= 0x0001,	//!< Reset the card. 
		UNPOWER_CARD					= 0x0002,	//!< Power down the card. 
		EJECT_CARD						= 0x0003,	//!< Eject the card.

		DISPOSITION_MASK				= 0x000f,	//!< Mask to remove the disposition flags.
		DISPOSITION_SHUTDOWN			= 0x0010	//!< Shutdown Bit 
	};

	inline bool APDUSUCCESS(word sw1sw2)
	{
		return sw1sw2 == APDU_OK
			|| sw1sw2 == APDU_OK1;
	}

	//
	// extract status word
	template<typename ExceptionT>
	inline word APDUResponse(const ExceptionT& e)
	{
		return word(e.code() & APDU_RESPONSE_MASK);
	}

	//
	// VerifyInfo
	// ---------------------------------------------------------------------------
	struct VerifyInfo
	{
		explicit VerifyInfo(const LengthInfo& lengthInfo_,
			EncodingType encoding_ = ENCODING_DEFAULT)
			: lengthInfo(lengthInfo_)
			, encoding(encoding_)
			, langId(0x0409)
			, numMsg(0xff)
			, idxMsg(0x00)
			, timeout(30)
			, rfu(0)
		{ }

		inline void swap(VerifyInfo& other)
		{
			if(&other == this) return;
			std::swap(*this, other);
		}

		LengthInfo		lengthInfo;
		EncodingType	encoding;
		word			langId;						//<! Language for messages.
		byte			numMsg;						//<! Number of messages to display for verification.
		byte			idxMsg;						//<! Message index (should be 00).
		byte			timeout;					//<! Timeout in seconds
		byte			rfu;
	};

	//
	// ModifyInfo
	// ---------------------------------------------------------------------------
	struct ModifyInfo : VerifyInfo
	{
		explicit ModifyInfo(const LengthInfo& lengthInfo,
			EncodingType encoding = ENCODING_DEFAULT)
			: VerifyInfo(lengthInfo, encoding)
		{ }
	};

	//
	// Index of PACE function
	// ---------------------------------------------------------------------------
	enum PaceFunction
	{
		GetReaderPACECapabilities		= 1,
		EstablishPACEChannel			= 2,
		DestroyPACEChannel				= 3,
	};

	struct PaceVerifyInfo;
	struct PaceModifyInfo;
	struct PaceResetInfo;

	//
	// PaceInfo
	// ---------------------------------------------------------------------------
	struct PaceInfo
	{
		PaceInfo(PaceFunction value)
			: idx(value)
		{ }

		PaceFunction idx;
		Blob		 inout;
	};

	//
	// PaceVerifyInfo
	// ---------------------------------------------------------------------------
	struct PaceVerifyInfo
	{
		PaceVerifyInfo(byte _pin_ref, const Blob& _pin_value, const Blob& _chat)
			: idx(EstablishPACEChannel)
			, pin_ref(_pin_ref)
			, pin_value(_pin_value)
			, chat(_chat)
		{ }

		PaceFunction	idx;
		byte			pin_ref;	//<! object ref of PIN, PUK...
		const Blob&		pin_value;	//<! send to PACE-reader if not empty
		const Blob&		chat;		//<! RFU
	};

	//
	// PaceModifyInfo
	// ---------------------------------------------------------------------------
	struct PaceModifyInfo : PaceVerifyInfo
	{
		PaceModifyInfo(byte pin_ref, const Blob& pin_value, const Blob& chat)
			: PaceVerifyInfo(pin_ref, pin_value, chat)
		{ }
	};

	// ---------------------------------------------------------------------------
	enum SendType
	{
		SEND_ERROR							= 0x1000,
		SEND_EXTENDED						= 0x0100,
		SEND_RESEND_T0						= 0x0200,
		SEND_SECURE_CHANNEL					= 0x0010,
		SEND_COMMAND						= 0x0001,
		SEND_RECEIVE						= 0x0002,
		SEND_SECURE_COMMAND					= SEND_COMMAND | SEND_SECURE_CHANNEL,
		SEND_SECURE_RECEIVE					= SEND_RECEIVE | SEND_SECURE_CHANNEL,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(SendType);

	// ---------------------------------------------------------------------------
	enum PinEntry
	{
		PIN_ENTRY_KEY_NO_KEY				= 0x0000,
		PIN_ENTRY_KEY_BACKSPACE				= 0x0008,
		PIN_ENTRY_KEY_CLEAR					= 0x000a,
		PIN_ENTRY_KEY_ENTER					= 0x000d,
		PIN_ENTRY_KEY_CANCEL				= 0x001b,
		PIN_ENTRY_KEY_VALID					= 0x002b,		//!< by default 0-9
		PIN_ENTRY_KEY_ABORT					= 0x0040,		//!< including timeout
		PIN_ENTRY_KEY_MASK					= 0x00ff,

		PIN_ENTRY_START						= 0x0100,
		PIN_ENTRY_FINISH					= 0x0200,
	};

	// ---------------------------------------------------------------------------
	enum OptionType
	{
		OPTION_NONE							= 0,
		OPTION_ABORT						= 1,
		OPTION_RETRY						= 2,
		OPTION_HANDLED						= 4,
		OPTION_REQUIRED						= 8,
		/* ... */
		OPTION_DEFAULT						= OPTION_ABORT,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(OptionType);

	// ---------------------------------------------------------------------------
	enum SCardChangedMask
	{
		DefaultCount						= 0,			//!< ChangedCount | ReconnectCount
		ChangeCount							= 1,			//!< Increaed everytime the card has been changed
		ReconnectCount						= 2,			//!< Increaed everytime the card has been reconnected
	};

	// ---------------------------------------------------------------------------
	class ISlot;
	class ISCardSM;
	class ISCardAccess;

	// ---------------------------------------------------------------------------
	template
	<
		typename EventT,
		typename InfoInT,
		typename InfoOutT = InfoInT
	>
	struct SCAEvent
	{
		template<typename T>
		SCAEvent(EventT event_type, InfoInT event_info, const Location<T>& source)
			: type(event_type)
			, info(event_info)
			, location(source)
		{ }

		typedef EventT		EventType;
		typedef InfoOutT	InfoType;

		const EventT		type;
		const InfoInT		info;
		const Location<>	location;
	};

	// ---------------------------------------------------------------------------
	typedef SCAEvent<PinEntry,  OptionType>			SCAPinEntryEvent;
	typedef SCAEvent<EventCode, ulong, OptionType>	SCAStatusEvent;
	typedef SCAEvent<SendType,  word, Blob>			SCASendEvent;

	// ---------------------------------------------------------------------------
	class ISCASendHandler : public Observer<ISCardAccess, SCASendEvent>
	{
	public:
		typedef SCASendEvent		Event;
		typedef Event::InfoType		Status;

		virtual const char* GetName() const = 0;		
	};

	// ---------------------------------------------------------------------------
	class ISCAStatusHandler : public Observer<ISCardAccess, SCAStatusEvent>
	{
	public:
		typedef SCAStatusEvent		Event;
		typedef Event::InfoType		Option;

		virtual const char* GetName() const = 0;		
	};

	// ---------------------------------------------------------------------------
	class ISCAPinEntryHandler : public Observer<ISCardAccess, SCAPinEntryEvent>
	{
	public:
		typedef SCAPinEntryEvent	Event;
		typedef Event::InfoType		Option;

		virtual const char* GetName() const = 0;		
	};

	// ---------------------------------------------------------------------------
	bool IsTransacted(const ISCardAccess* ac);

	// ---------------------------------------------------------------------------
	class ISCardAccess
		: public IRefCounted
		, public ISynchronize
		, public Observable<ISCardAccess, SCASendEvent, Blob>
		, public Observable<ISCardAccess, SCAStatusEvent, OptionType>
		, public Observable<ISCardAccess, SCAPinEntryEvent, OptionType>
	{
	public:
		virtual ~ISCardAccess()
		{ }

		virtual void			CheckConfig() = 0;

		virtual ProtocolType	GetProtocol() const = 0;
		virtual void			SetProtocol(ProtocolType protocol) = 0;

		virtual ulong			GetTimeout() const = 0;
		virtual bool			SetTimeout(ulong timeout_msec) = 0;

		virtual SCardSyncMode	GetSyncMode() const = 0;
		virtual void			SetSyncMode(SCardSyncMode mode) = 0;

		virtual bool			IsTokenPresent() const = 0;

		virtual void			Open() = 0;
		virtual void			Close() = 0;
		virtual void			Reset() = 0;
		virtual ulong			Cancel() = 0;
		virtual ulong			Reconnect(DispositionType initialization) = 0;

		virtual ulong			BeginTransaction() = 0;
		virtual ulong			EndTransaction(DispositionType disposition = LEAVE_CARD) = 0;
		virtual void			RequiresTransaction(const Location<>& location) const = 0;
		virtual ulong			GetTransactionDepth() const = 0;

		virtual bool			HasAccessChanged(SCardChangedMask mask) = 0;
		virtual uint32			GetAccessChangeCount(SCardChangedMask mask) const = 0;

		virtual ISlot*			GetSlot() const = 0;

		virtual Blob			GetResponse() const = 0;
		virtual Blob&			GetResponse(Blob& response) const = 0;
		virtual size_t			GetResponseSize() const = 0;
		
		virtual word			SendCard(const Blob& cmd, Blob& response, ushort response_len = RESPONSE_MAXLEN) = 0;

		virtual word			Send(const Blob& cmd) = 0;
		virtual word			Send(const Blob& header, const Blob& data) = 0;
		virtual word			Send(const Blob& header, const Blob& data, byte le) = 0;

		// extended APDU
		virtual word			SendX(const Blob& header, const Blob& data) = 0;
		virtual word			SendX(const Blob& header, const Blob& data, ushort le) = 0;

		// secure pin entry
		virtual bool			HasSecurePinEntry() = 0;
		virtual word			SendVerifyToReader(const Blob& apdu, const VerifyInfo& info) = 0;

		virtual bool			HasSecurePinChange() = 0;
		virtual word			SendModifyToReader(const Blob& apdu, const ModifyInfo& info) = 0;

		// secure PACE pin entry
		virtual bool			HasPacePinEntry() = 0;
		virtual SCardReturnCode	SendPaceVerifyToReader(const PaceVerifyInfo& info) = 0;

		virtual bool			HasPacePinChange() = 0;
		virtual SCardReturnCode	SendPaceModifyToReader(const PaceModifyInfo& info) = 0;

		virtual SCardReturnCode	SendPaceInfoToReader(PaceInfo& info) = 0;
		virtual SCardReturnCode	SendPaceInfoToReader(const PaceInfo& info) = 0;		//!< \note discard output

		// secure messaging
		virtual ISCardSM*		GetSM() const = 0;
		virtual void			SetSM(ISCardSM* sm) = 0;
	};

} // namespace act

#endif	// ACT_ISCardAccess_h
