// ---------------------------------------------------------------------------
// Name:      actISlot.h
// Product:   cv act library
// Purpose:   The class ISlot manages the Tokens
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISlot_h
#define ACT_ISlot_h

#include "actMode.h"
#include "actBlob.h"
#include "actBasics.h"
#include "actIParam.h"

#include "actIRefCounted.h"
#include "actISynchronize.h"
#include "actIEventMonitoring.h"

#include "actSCardOSReg.h"

namespace act
{
	class IToken;
	class ITokenConfig;
	class ISCardOS;
	class ISCardAccess;
	class ISubsystem;
	class ISlot;

	// ---------------------------------------------------------------------------
	enum slot_paramid_t
	{
		SLOT_PARAM_BEGIN		= 0,
		SLOT_PARAM_END			= SLOT_RANGE_SIZE,
		// Parameter
		SLOT_PARAM_FEATURE		= SLOT_PARAM_BEGIN,
		SLOT_PARAM_CARD_ID,		//!< Card identification data if card detection function has been called.
		SLOT_PARAM_INITIALIZER,	//!< Name of token initializer to used instead of OS-Name.
		SLOT_PARAM_NO_RESET,	//!< Set to \a PARAM_FALSE to disable \a Reset implemented by \a ISCardAccess.
		// RFU					: 4 - 7
		// Custom				: 7 - 15
	};

	// ---------------------------------------------------------------------------
	enum SlotStatus
	{
		SLOT_STATE_UNAWARE		= 0x00000000,	//!< \sa SCARD_STATE_UNAWARE
		SLOT_STATE_IGNORE		= 0x00000001,
		SLOT_STATE_CHANGED		= 0x00000002,
		SLOT_STATE_UNKNOWN		= 0x00000004,
		SLOT_STATE_UNAVAILABLE	= 0x00000008,
		SLOT_STATE_EMPTY		= 0x00000010,
		SLOT_STATE_PRESENT		= 0x00000020,
		SLOT_STATE_ATRMATCH		= 0x00000040,
		SLOT_STATE_EXCLUSIVE	= 0x00000080,
		SLOT_STATE_INUSE		= 0x00000100,
		SLOT_STATE_MUTE			= 0x00000200,
		SLOT_STATE_UNPOWERED	= 0x00000400,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(SlotStatus);

	//
	// ISlot
	// ---------------------------------------------------------------------------
	class ISlot
		: public IRefCounted
		, public ISynchronize
		, public IEventMonitoring
	{
	protected:
		virtual ~ISlot() { }

	public:
		virtual ISlot*			Clone() const = 0;

		virtual Blob			GetATR() const = 0;
		virtual const char*		GetName() const = 0;
		virtual ISubsystem*		GetSystem() const = 0;
		virtual const char*		GetReaderName() const = 0;
		virtual Blob			GetHistoricalBytes() const = 0;
		virtual bool			GetStatus(SlotStatus&) const = 0;

		virtual bool			IsTokenPresent() const = 0;

		virtual IToken*			CreateToken(ISCardOS* os = 0) = 0;
		virtual IToken*			CreateToken(ISCardOS* os) const = 0;

		virtual ISCardOS*		CreateOS(const SCardOSRegInfo& info = SCardOSRegInfo()) = 0;
		virtual ISCardOS*		CreateOS(ISCardAccess* ac, const SCardOSRegInfo& info = SCardOSRegInfo()) const = 0;

		virtual ISCardAccess*	CreateAccess() = 0;

		virtual ITokenConfig*	GetTokenConfig() const = 0;
		virtual void			SetTokenConfig(ITokenConfig* tkcfg) = 0;

		virtual bool			HasSecurePinEntry(ISCardAccess* ac = 0)  const = 0;
		virtual bool			HasSecurePinChange(ISCardAccess* ac = 0) const = 0;

		virtual bool			HasPacePinVerify(ISCardAccess* ac = 0) const = 0;
		virtual bool			HasPacePinChange(ISCardAccess* ac = 0) const = 0;

		virtual void			SetParam(paramid_t id, int val) = 0;
		virtual int				GetParam(paramid_t id) const = 0;

		static slot_paramid_t	Param(paramid_t id, const ISlot* reserved = 0);
		static paramid_t		Param(slot_paramid_t id, const ISlot* reserved = 0);
	};

	// ---------------------------------------------------------------------------
	struct ATRCardInfo
	{
		const char* name;
		const char* atr;
		const char* atr_mask;
	};

	// ---------------------------------------------------------------------------
	void				InitCardInfoMap(const ATRCardInfo* mapCardInfo);
	const ATRCardInfo*	GetATRCardInfo(const Blob& atr);
	const char*			GetOSName(const Blob& atr);
	Blob				GetHistoricalBytes(const Blob& atr);
	size_t				GetHistoricalBytes(const Blob& atr, Blob& historical_bytes);
	bool				GetATRStructInfo(const Blob& atr, size_t& his_pos, size_t& his_len, bool& has_tck);

} // namespace act

#endif	// ACT_ISlot_h
