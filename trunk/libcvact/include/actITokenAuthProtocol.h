// ---------------------------------------------------------------------------
// Name:      actITokenAuthProtocol.h
// Product:   cv act library
// Purpose:   ITokenAuthProtocol interface for smartcard authentication protocols
//			  like PACE, TA, CA. A scuccessfull execution normally ends with the
//			  establishment of an SM channel.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/14/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenAuthProtocol_h
#define ACT_ITokenAuthProtocol_h

#include "actObserver.h"

#include "actITokenPIN.h"
#include "actIRefCounted.h"

namespace act
{
	class ISCardSM;

	//
	// AuthProtocolStatusValues
	enum AuthProtocolStatusValues				ACT_ENUM_TYPE(byte)
	{
		TAP_STATE_NOT_INITIALIZED				= 0,
		TAP_STATE_BEGIN							= 1,

			TAP_PACE_PASSWORD_BEGIN				/*!< PACE						*/	= TAP_STATE_BEGIN,
				TAP_PACE_PASSWORD_VERIFIED		/*!< state authenticated.		*/	= TAP_PACE_PASSWORD_BEGIN,
				TAP_PACE_PASSWORD_DEACTIVATED,	//!< 
				TAP_PACE_PASSWORD_SUSPENDED,	//!< 
				TAP_PACE_PASSWORD_BLOCKED,		//!< 
				TAP_PACE_PASSWORD_RETRIES,		//!< 
				// Additional states here ...
				TAP_PACE_PASSWORD_NONCE,
			TAP_PACE_PASSWORD_END,				//!< End of PACE states.
			TAP_PACE_PASSWORD_SIZE				/*!< Number of PACE states.		*/	= TAP_PACE_PASSWORD_END - TAP_PACE_PASSWORD_BEGIN,

			TAP_TA_BEGIN						= TAP_PACE_PASSWORD_END,
				TAP_TA_SUCCESSFUL				= TAP_TA_BEGIN,
				// Additional states here ...
			TAP_TA_END,
			TAP_TA_SIZE							= TAP_TA_END - TAP_TA_BEGIN,

			TAP_CA_BEGIN						= TAP_TA_END,
				TAP_CA_SUCCESSFUL				= TAP_CA_BEGIN,
				// Additional states here ...
			TAP_CA_END,
			TAP_CA_SIZE							= TAP_CA_END - TAP_CA_BEGIN,

			TAP_BAC_BEGIN						= TAP_CA_END,
				TAP_BAC_SUCCESSFUL				= TAP_BAC_BEGIN,
				// Additional states here ...
			TAP_BAC_END,
			TAP_BAC_SIZE						= TAP_BAC_END - TAP_BAC_BEGIN,

			TAP_ICAO_BEGIN						= TAP_BAC_END,
				TAP_ICAO_SUCCESSFUL				= TAP_ICAO_BEGIN,
				// Additional states here ...
			TAP_ICAO_END,
			TAP_ICAO_SIZE						= TAP_ICAO_END - TAP_ICAO_BEGIN,

			TAP_TCOS_BEGIN						= TAP_ICAO_END,
				TAP_TCOS_SUCCESSFUL				= TAP_TCOS_BEGIN,
				// Additional states here ...
			TAP_TCOS_END,
			TAP_TCOS_SIZE						= TAP_TCOS_END - TAP_TCOS_BEGIN,

		TAP_STATE_END							= TAP_ICAO_END,
		TAP_STATE_SIZE							= TAP_STATE_END - TAP_STATE_BEGIN
	};

	//
	// AuthProtocolState
	struct AuthProtocolState
	{
		AuthProtocolState() { reset(); }
		inline void reset() { state = TAP_STATE_NOT_INITIALIZED; retry_counter = RC_UNKNOWN; }

		int	state;
		int	retry_counter;
	};

	//
	// ITokenAuthProtocol
	class ITokenAuthProtocol
		: public IRefCounted
		, public Observable<ITokenAuthProtocol, int, Blob>
	{
	protected:
		virtual ~ITokenAuthProtocol() { }

	public:
		virtual const char* GetName() const = 0;
		virtual const ITokenPIN* GetOwner() const = 0;

		virtual void Reset(const ITokenPIN* owner, AuthProtocolState& protocol_state) = 0;

		virtual ISCardSM* Execute(const ITokenPIN* owner, const Blob& owner_param,
			AuthProtocolState& protocol_state) = 0;
	};

	//
	// ITokenAuthProtocolObserver
	class ITokenAuthProtocolObserver : public Observer<ITokenAuthProtocol, int, Blob>
	{
	public:
		virtual const char* GetName() const = 0;		
	};

	typedef ITokenAuthProtocolObserver ITokenAPO;

} // namespace act

#endif // ACT_ITokenAuthProtocol_h
