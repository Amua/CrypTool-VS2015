// ---------------------------------------------------------------------------
// Name:		actITokenConfig.h
// Product:		cv act library
// Purpose:		IToken configuration.
//
// Copyright:	(c) 2008 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche
// Date:		11/07/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenConfig_h
#define ACT_ITokenConfig_h

#include "actBool.h"
#include "actBlob.h"

#include "actIParam.h"
#include "actIRefCounted.h"

#include "actTokenConfig.h"

namespace act
{
	class ISlot;
	class ISCardOS;
	class ISCardSM;
	class ISCardAccess;

	class IToken;
	class ITokenPIN;
	class ITokenAuth;
	class ITokenKey;
	class ITokenBlockCipher;
	class ITokenBlockCipherKey;
	class ITokenFileMap;
	class ITokenFileCache;
	class ITokenDFHandler;
	class IAccessCondition;

	class TokenKey;

	//
	// ITokenConfig
	class ITokenConfig
		: public IParam
		, virtual public IRefCounted
	{
	public:
		virtual ITokenConfig* Clone() const = 0;

		virtual const char* GetName() const = 0;
		virtual ITokenFileCache* GetCache() const = 0;
		virtual ITokenFileCache* GetCache(ISCardOS* os) = 0;

		using IParam::GetParam;
		using IParam::SetParam;

		virtual BOOLean GetParam(tc_serializeid_t id) const = 0;		//!< \pre \ref TC_SERIALIZE_BEGIN <= \arg \c id < \ref TC_SERIALIZE_END
		virtual void SetParam(tc_serializeid_t id, BOOLean value) = 0;	//!< \pre \ref TC_SERIALIZE_BEGIN <= \arg \c id < \ref TC_SERIALIZE_END
		virtual void IniParam() = 0;									//!< Param initialization

		virtual void Import(const Blob& bitstring) = 0;					//!< Import from BITSTRING
		virtual Blob Export() const = 0;								//!< Export to BITSTRING

		// Individual card detection
		virtual bool IsSupported(ISCardOS* os) const = 0;

		// Configures supporting (non token) instances, if fails throws an Exception
		virtual const ITokenConfig& Configure(ISCardOS* os) = 0;
		virtual const ITokenConfig& Configure(ITokenConfig* other) = 0;	//!< Configure this from other and return this reference !

		virtual const ITokenConfig& Configure(ISlot* slot) const = 0;
		virtual const ITokenConfig& Configure(ISCardSM* sm) const = 0;
		virtual const ITokenConfig& Configure(ISCardAccess* ac) const = 0;

		// Configures the token, if fails throws an Exception
		virtual const ITokenConfig& Configure(IToken* token) const = 0;
		virtual const ITokenConfig& Configure(ITokenPIN* auth_obj) const = 0;
		virtual const ITokenConfig& Configure(ITokenBlockCipher* cipher) const = 0;
		virtual const ITokenConfig& Configure(ITokenBlockCipherKey* key) const = 0;
		virtual const ITokenConfig& Configure(ITokenDFHandler* df_handler) const = 0;
		virtual const ITokenConfig& Configure(ITokenKey* key) const = 0;
		virtual const ITokenConfig&	Configure(ITokenFileCache*) const = 0;
		virtual BOOLean Configure(TokenKey* key) const = 0;

		// Factory methods - token related
		virtual ITokenAuth* CreateAuth(IToken* token) = 0;
		virtual ITokenFileMap* CreateFileMap(const IToken* token) = 0;

		// Factory methods - other
		virtual IAccessCondition* CreateAC(IToken* token) = 0;
	};

} // namespace act

#endif	// ACT_ITokenConfig_h
