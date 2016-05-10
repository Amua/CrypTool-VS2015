// ---------------------------------------------------------------------------
// Name:      actSCardOSReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create SCardOS objects.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  04/09/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardOSReg_h
#define ACT_SCardOSReg_h

#include "actBlob.h"
#include "actFactoryReg.h"

namespace act
{
#	define ACT_ISO7816OS_NAME	"ISO7816OS"

	class ISCardOS;
	class ISCardAccess;

	typedef ISCardOS* (*CreateSCardOSPtr)(ISCardAccess*);
	typedef bool      (*DetectSCardOSPtr)(const Blob&, ISCardAccess*);

	struct SCardOSMapEntry
	{
		const char*      Name;
		CreateSCardOSPtr CreatePtr;
	};

	struct SCardOSAtrMaskEntry
	{
		// const might be nice here, but it collides with the way std::vector works.
		byte_array ATR;
		byte_array Mask;
		CreateSCardOSPtr CreatePtr;
	};

	struct SCardOSFactoryEntry
	{
		DetectSCardOSPtr DetectPtr;
		CreateSCardOSPtr CreatePtr;
	};

	struct SCardOSRegInfo;

	class SCardOSReg
	{
	public:
		enum Type
		{
			DEFAULT				= 0,
			ATR					= 1,
			MODEL_ID			= 2,			//!< By default the ModelId equals the ATR-Historical Bytes
		};

		static ISCardOS* CreateSCardOS(const SCardOSRegInfo& info, ISCardAccess* ac);
		static CreateSCardOSPtr GetCreatePointer(const SCardOSRegInfo& info, ISCardAccess* ac);
		static CreateSCardOSPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateSCardOSPtr createptr);
		static void Insert(const SCardOSMapEntry* entry);
		static void Insert(const SCardOSAtrMaskEntry* entry);
		static void Insert(const SCardOSFactoryEntry* entry);
	};

	// ---------------------------------------------------------------------------
	typedef ISCardOS* (*DeriveSCardOSPtr)(ISCardOS*);
	typedef FactoryMapEntry<DeriveSCardOSPtr> SCardOSDerivationMapEntry;

	typedef FactoryReg
	<	ISCardOS, DeriveSCardOSPtr, SCardOSDerivationMapEntry
	>	SCardOSDerivationReg;

	// ---------------------------------------------------------------------------
	struct SCardOSRegInfo
	{
		const SCardOSReg::Type	m_type;
		const Blob				m_data;

		SCardOSRegInfo(SCardOSReg::Type type = SCardOSReg::DEFAULT, const Blob& data = Blob())
			: m_type(type)
			, m_data(data)
		{ }
	};

} // namespace act

#endif // ACT_SCardOSReg_h
