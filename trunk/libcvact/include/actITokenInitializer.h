// ---------------------------------------------------------------------------
// Name:      actITokenInitializer.h
// Product:   cv act library
// Purpose:   ITokenInitializer interface declares common token profile initialization functionality.
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/20/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenInitializer_h
#define ACT_ITokenInitializer_h

#include "actBool.h"
#include "actBlob.h"
#include "actTypeTags.h"
#include "actException.h"
#include "actTokenBase.h"
#include "actITokenFile.h"
#include "actIRefCounted.h"

// TODO: MTE: *** Replace std::vector<> by simple Range<TIData>(begin, end).
#include <vector>

namespace act
{
	// Forward declarations
	// -----------------------------------------------------------------------
	class ISCardOS;
	class IProfileGenerator;
	class ISCardCmdObserver;

	class Exception;
	class SCardToken;

	struct TIData;

	// -----------------------------------------------------------------------
	extern const byte	LEN_SERIALNO;					//!< Default token serial number length.
	extern const byte	PIN_PAD_CHAR;					//!< Default PIN padding character.
	extern const byte	PIN_RETRY_COUNTER;				//!< Default PIN retry counter.
	extern const byte	PIN_ENTRY_TIMEOUT;				//!< Default PIN pad entry timeout in seconds.
	extern const byte	GP_PRIVILEGES_NOT_INITIALIZED;	//!< Default Global Platform applet privileges.

	// -----------------------------------------------------------------------
	enum NamedParam
	{	// last update:				12/10/2012
		np_begin					= 32,
		np_last						= np_begin + 32,
		np_end,
	};

	// -----------------------------------------------------------------------
	enum NamedAC
	{	// last update:				12/13/2012
		// AC
		/* Last   */ ac_begin		= np_end,
		/* Blob   */ ac_u_so		= ac_begin,	//!< AC Update for SO.
		/* Blob   */ ac_ua_so,					//!< AC Update|Append for SO.
		/* Blob   */ ac_ua_user,				//!< AC Update|Append for User.
		/* Blob   */ ac_ua_user_or_so,			//!< AC Update|Append for User or SO.

		// AC-DO
		/* Blob   */ ac_do_ro,					//!< AC-DO ReadOnly.
		/* Blob   */ ac_do_u_so,				//!< AC-DO Update for SO.
		/* Blob   */ ac_do_u_user_or_so,		//!< AC-DO Update for User or SO.

		// AC-Key
		/* Blob   */ ac_key_all_always,			//!< AC-Key Everyone all rights.

		// AC-Persoonalization
		/* Blob   */ ac_personalize,			//!< AC Update / Append only during personalization.

		// AC-??
		// NOTE: Add more access conditions ...

		/* Last   */ ac_last,
		/* End    */ ac_end,
	};

	//!
	//! \brief \a ITokenInitializer support function id's.
	// -----------------------------------------------------------------------
	enum TIFId
	{
		TIFID_ERROR			= -1,
		TIFID_BEGIN			=  0,
		TIFID_PRE_LOAD		=  TIFID_BEGIN,			//!< Before each package / applet will be loaded.
		TIFID_POST_LOAD,							//!< After successfull loading package / applet.
		TIFID_PRE_INSTALL,							//!< Before package / applet installation, \sa TIFID_PRE_LOAD.
		TIFID_PARAMETER,							//!< Provide package / applet specific load / installation parameter.
		TIFID_POST_INSTALL,							//!< After successfull package / applet installation, \sa TIFID_POST_LOAD.
		TIFID_END,
		TIFID_LENGTH		=  TIFID_END,
		/* ... */
		TIFID_CHECK_VERSION,						//!< OPTIONAL Check compatible version callback.
		TIFID_TOKEN_FACTORY,						//!< OPTIONAL Factory to create post issuance authentication token, \sa CreateSCardTokenPtr
		TIFID_DATA_PROVIDER,						//!< OPTIONAL File content provider (EF.DIR, EF.ATR, ...), used as primary source during creation.
	};

#	include "actPackOn.h"

	typedef Blob TIPin;

	struct TIPinKey
	{
		TIPinKey() : pin(key)
		{ }

		Blob&	pin;
		Blob	key;
	};

	//!
	//! \brief Token Capability Flags.
	// -----------------------------------------------------------------------
	union TCFlags
	{	struct
		{	ushort			pin_padding		: 1;	//!< Bit 0,	  \par Values [\a False | \a True], Default \a False
			ushort			pin_pce_so		: 1;	//!< Bit 1,	  \par Values [\a False | \a True], Default \a False
			ushort			pin_pce_user	: 1;	//!< Bit 2,	  \par Values [\a False | \a True], Default \a False 
			ushort			minidriver		: 1;	//!< Bit 3,   \par Values [\a False | \a True], Default \a False
			ushort			minidriver_pnp	: 1;	//!< Bit 4,   \par Values [\a False | \a True], Default \a False, \req TIData::enable::minidriver
			ushort			biometric		: 1;	//!< Bit 5,   \par Values [\a False | \a True], Default \a False
			ushort			biometric_pins	: 4;	//!< Bit 6-9, \par Values [\a False | \c 1-10], Default \a False, \req TIData::enable::biometric
			ushort			write_aodf		: 1;	//!< Bit 10,  \par Values [\a False | \a True], Default \a False
			ushort			pace			: 1;	//!< Bit 11,  \par Values [\a False | \a True], Default \a False
			ushort			eba			    : 1;	//!< Bit 12,  \par Values [\a False | \a True], Default \a False
			/*				...			*/	};
		ushort				all;
	};

	//!
	//! \brief Token Content.
	// -----------------------------------------------------------------------
	union TIContent
	{	struct
		{	ushort			required		: 1;	//!< Bit 0,	\par Values [\a False | \a True], Default \a False
			ushort			ef_atr			: 1;	//!< Bit 1,	\par Values [\a False | \a True], Default \a False
			ushort			ef_dir			: 1;	//!< Bit 2,	\par Values [\a False | \a True], Default \a False
			/*				...			*/	};
		ushort				all;
	};

	//!
	//! \brief Token install flags.
	// -----------------------------------------------------------------------
	union TIFlags
	{	struct
		{	ushort			required		: 1;	//!< Bit 0,	\par Values [\a False | \a True], Default \a True
			ushort			prerequisite	: 1;	//!< Bit 1, \par Values [\a False | \a True], Default \a False, verify existance, abort if not exist but \a TIData::package::required
			ushort			existing		: 1;	//!< Bit 2, \par Values [\a False | \a True], Default \a False, use existing package, no load, no install
			ushort			install         : 1;	//!< Bit 3, \par Values [\a False | \a True], Default \a True, install card specific package
			ushort			load            : 1;	//!< Bit 4, \par Values [\a False | \a True], Default \a False, load card specific package
			ushort			load_MoC		: 1;	//!< Bit 5, \par Values [\a False | \a True], Default \a False, load Match-on-Card package
			ushort			load_2048		: 1;	//!< Bit 6, \par Values [\a False | \a True], Default \a False, load 2048 Bit support package
			ushort			load_ecc		: 1;	//!< Bit 7, \par Values [\a False | \a True], Default \a False, load ECC support package
			ushort			pfx				: 1;	//!< Bit 8, \par Values [\a False | \a True], Default \a False, contains PFX to import
			ushort			is_virtual		: 1;	//!< Bit 9, \par Values [\a False | \a True], Default \a False, set \a True if AID is virtual. Requires more then 1 \a TIData where the root is not virtual!
			/*				...			*/	};
		ushort				all;
	};

	//!
	//! \brief Token install version range.
	// -----------------------------------------------------------------------
	union TIVersion
	{	struct
		{	ushort			minver;					//!< Lowest compatible version.
			ushort			maxver;					//!< Highest compatible version.
			/*				...			*/	};
		ulong				minmax;
	};

	//!
	//! \brief Token Install Additional Flags.
	// -----------------------------------------------------------------------
	enum TIAFlags
	{
		NoAuthentication	= 0x0000u,
		VersionInvalid		= -1,
		VersionAny			=  0,
	};

	//!
	//! \brief Token Install Security Flags.
	// -----------------------------------------------------------------------
	union TISFlags
	{	struct
		{	ushort			auth_card		: 1;	//!< Bit 0, default \a True
			ushort			auth_user		: 1;	//!< Bit 1, default \a True
			ushort			auth_so			: 1;	//!< Bit 2, default \a True
			ushort			enable_sm		: 1;	//!< Bit 3, default \a False
			/*				...			*/	};
		TIAFlags			auth;
	};

	//!
	//! \brief Token Initializer Function (TIF) - template declaration.
	// -----------------------------------------------------------------------
	template
	<
		class    ContextT,
		typename ArgInT,	//!< Argument 0 - Input
		typename ArgOutT,	//!< Argument 1 - Output (always byref)
		typename TypeTagT = TagAny
	>
	struct TIF;

	//!
	//! \brief TIF<void> specialization - base class.
	// -----------------------------------------------------------------------
	template<class ContextT, typename ArgInT, typename ArgOutT>
	struct TIF<ContextT, ArgInT, ArgOutT, void>
	{
		typedef BOOLean (*FPtr)(const ContextT&, ArgInT, ArgOutT&);

		const FPtr		function;
		const ContextT&	context;

		TIF(const ContextT& owner, FPtr fptr)
			: function(fptr)
			, context(owner)
		{ }
	};

	//!
	//! \brief TIF<TagAny> specialization - default.
	// -----------------------------------------------------------------------
	template<class ContextT, typename ArgInT, typename ArgOutT>
	struct TIF<ContextT, ArgInT, ArgOutT, TagAny>
		:  TIF<ContextT, ArgInT*, ArgOutT, void>
	{
		typedef TIF<ContextT, ArgInT*, ArgOutT, void> BaseType;
		typedef typename BaseType::FPtr FPtr;
		using	BaseType::function;
		using	BaseType::context;

		TIF(const ContextT& owner, FPtr fptr = 0)
			: BaseType(owner, fptr)
		{ }

		TIF(const ContextT& owner, size_t id)
			: BaseType(owner, owner.functions[id])
		{ }

		BOOLean operator()(ArgInT* in, ArgOutT& out) const
		{
			return	0 == function
				?	NotInitialized
				:	function(context, in, out);
		}
	};

	//!
	//! \brief TIF<TagPtr> specialization - data provider.
	// -----------------------------------------------------------------------
	template<class ContextT, typename ArgInT, typename ArgOutT>
	struct TIF<ContextT, ArgInT, ArgOutT, TagPtr>
		:  TIF<ContextT, ArgInT, ArgOutT, void>
	{
		typedef TIF<ContextT, ArgInT, ArgOutT, void> BaseType;
		typedef typename BaseType::FPtr FPtr;
		using	BaseType::function;
		using	BaseType::context;

		TIF(const ContextT& owner, FPtr fptr = 0)
			: BaseType(owner, fptr)
		{ }

		TIF(const ContextT& owner, size_t id)
			: BaseType(owner, owner.functions[id])
		{ }

		ArgOutT operator()(ArgInT in) const
		{
			ArgOutT out;
			if(0 != function) function(context, in, out);
			return out.move();
		}

		const TIF& operator()(ArgInT in, ArgOutT& out, move_from<ArgOutT> defout = move_empty<ArgOutT>()) const
		{
			if(0 == function || True != function(context, in, out))
				out = defout;
			return *this;
		}
	};

	//!
	//! \brief TIF<TagFac> specialization - token factory.
	// -----------------------------------------------------------------------
	template<class ContextT, typename TokenT, typename SCardOST>
	struct TIF<ContextT, TokenT, SCardOST, TagFac>
	{
		typedef TokenT* (*FPtr)(SCardOST*, TokenT*);

		const FPtr		function;
		const ContextT&	context;

		TIF(const ContextT& owner, FPtr fptr = 0)
			: function(fptr)
			, context(owner)
		{ }

		TokenT* operator()(SCardOST* os) const
		{
			return	0 != function
				?	function(os, 0)
				:	0;
		}
	};

	//!
	//! \brief Token Initializer Data.
	// -----------------------------------------------------------------------
	struct TIData
	{
	private:
		TIData(const TIData&) throw();
		TIData& operator=(const TIData&) throw();

	public:
		//!
		//! \brief   Access condition for oncard files or objects.
		//! \details Provide generic access conditions for one or more
		//!          files or objects.
		//!
		//! \example { { ac_u_so, create_ef,    FID_NOT_INITIALIZED },   // 1
		//!            { ac_u_so, scmd_invalid, 5555                },   // 2
		//!            { ac_u_so, create_ef,    5555                } }; // 3
		//! 
		//! 1. On matching [0-n] id, (like \a create_ef) apply given AC.
		//! 2. On matching [0-1] fid, apply given AC once or never.
		//! 3. On matching [0-1] fid AND id (like \a create_ef) apply given
		//!    AC once or never.
		// -------------------------------------------------------------------
		struct AC		{
			NamedAC		ac;						//!< Generic access condition.
			ushort		id;						//!< Related scmd_t<> id, \sa SCardCmd.
			ushort		fid;					//!< Unique oncard file id or lo-byte object-id.
		};

		typedef std::vector<AC>::iterator		ac_iterator;
		typedef std::vector<AC>::const_iterator ac_const_iterator;

		//!
		//! \brief   Data object with access condition to be created on card.
		//! \details A generic mechanism to create binary data objects.
		// -------------------------------------------------------------------
		struct DO		{
			NamedAC		ac;
			Blob		tag;
			Blob		data;
		};

		typedef std::vector<DO>::iterator		do_iterator;
		typedef std::vector<DO>::const_iterator do_const_iterator;

		//!
		//! \brief Retry counter values for SO-, User-, Card- and C/R-Pin.
		// -------------------------------------------------------------------
		struct RC		{
			byte		cr;
			byte		so;
			byte		user;
			byte		card;
		};

	public:
		TIData(const char* profile_name_ = 0)
			: profile_type(PROFILE_UNKNOWN)
			, profile_name(profile_name_)
			, profile_path(0)
			, description(0)
			, generator(0)
			, pin_pad_byte(PIN_PAD_CHAR)
			, privileges(GP_PRIVILEGES_NOT_INITIALIZED)
			, version_check(0)
			, token_factory(0)
			, data_provider(0)
			, on_error(0)
			, next(0)
		{
			for(size_t i = 0; i < TIFID_LENGTH; ++i)
				functions[i]			=  0;
			default_rc.pin.cr			=  5;
			default_rc.pin.so			=  5;
			default_rc.pin.user			=  3;
			default_rc.pin.card			= 10;
			session_rc.all				=  0;
			session_rc.pin.user			=  1;
			enable.all					=  0;
			content.all					=  0;
			flags.all					=  0;
			flags.required				=  True;
			flags.install				=  True;
			version.minmax				=  VersionAny;
			security.auth				=  NoAuthentication;
			security.auth_so			=  True;
			security.auth_user			=  True;
			security.enable_sm			=  False;
		}

		bool check(byte number, bool has_parent) const
		{
			for(const TIData* data = this;
				number > 0 && data != 0;
				data = data->next, --number)
				has_parent = has_parent
				?	data->parent_id.empty()
				:	false;
			return	number == 0 && has_parent == false;
		}

		TIData&				ref()						{ return *this; }
		const TIData&		cref() const				{ return *this; }
		TIData&				ref_next()					{ return *next; }
		const TIData&		ref_next() const			{ return *next; }
		TIData*				get_next() const			{ return  next; }
		TIData&				set_next(TIData& other)		{ other.next = next; next = &other; return other;	}
		TIData&				set_next_of(TIData& other)	{ other.set_next(*this); return other;				}

		Blob				atr_historical_bytes;
		Blob				serial_number;

		TIPin				so_pin;
		TIPin				user_pin;
		TIPin				card_pin;
		TIPinKey			challenge_response;

		Blob				pin_policy;
		Blob				pin_last_update_utc;

		Blob				passphrase;					//!< For PFX TIData objects etc.

		Blob				binary_data;
		std::vector<AC>		array_of_ac;				//!< Array of Access Conditions (AC)
		std::vector<DO>		array_of_do;				//!< Array of Data Objects (DO)

		Blob				key_slot_info;				//!< DER encoded key slot information for ISO7816OS tokens (STARCOS 3.x)

		Blob				aid;
		Blob				label;
		Blob				df_name;					//!< optional DFName.
		Blob				parent_id;					//!< optional AID of parent (server) or empty.
		Blob				domain_id;	
		Blob				package_id;
		Blob				module_id;
		ProfileType			profile_type;
		ITokenFile*			profile_path;
		const char*			profile_name;
		const char*			description;				//!< Free to use
		const char*			generator;					//!< Name of profile generator factory or 0.
		byte				privileges;
		byte				pin_pad_byte;
		struct
		{	Blob		info;
			/* ...		*/	
		}					biometric;
		union
		{	RC			pin;
			size_t		all;
		}					default_rc;
		union
		{	RC			pin;
			size_t		all;
		}					session_rc;
		TCFlags				enable;
		TIFlags				flags;
		TIVersion			version;
		TIContent			content;
		TISFlags			security;

	private:
		TIData*				next;

		typedef TIF<TIData, ISCardOS,	Exception>			FError;			//!< Error callback.
		typedef TIF<TIData, ISCardOS,	Blob>				FSupport;		//!< Support function callback.
		typedef TIF<TIData, ISCardOS,	ushort>				FCheckVersion;	//!< Version check callback.
		typedef TIF<TIData, FIDType,	Blob,     TagPtr>	FDataProvider;	//!< File content provider.
		typedef TIF<TIData, SCardToken,	ISCardOS, TagFac>	FTokenFactory;	//!< Token factory method.

		template<class, typename, typename, typename>
		friend struct TIF;

	protected:
		FError::FPtr		on_error;
		FSupport::FPtr		functions[TIFID_LENGTH];					//!< Array of support function callback.
		FCheckVersion::FPtr	version_check;
		FDataProvider::FPtr	data_provider;
		FTokenFactory::FPtr	token_factory;

	protected:
		template<TIFId id, typename TagT = TagAny>
		struct FSelector
		{
			enum  { index = id >= TIFID_BEGIN && id < TIFID_LENGTH };
			typedef FSupport FType;

			static void  set(TIData& self, TIData& other)	{ if(index) set(self, other.functions[id]);	}
			static void  set(TIData& self, FType::FPtr fun)	{ if(index) self.functions[id] = fun;		}
			static FType get(const TIData& self)			{ return FType(self, id);					}
		};

		template<typename TagT>
		struct FSelector<TIFID_CHECK_VERSION, TagT>
		{
			enum  { index = false };
			typedef FCheckVersion FType;

			static void  set(TIData& self, TIData& other)	{ set(self, other.version_check);			}
			static void  set(TIData& self, FType::FPtr fun)	{ self.version_check = fun;					}
			static FType get(const TIData& self)			{ return FType(self, self.version_check);	}
		};

		template<typename TagT>
		struct FSelector<TIFID_TOKEN_FACTORY, TagT>
		{
			enum  { index = false };
			typedef FTokenFactory FType;

			static void  set(TIData& self, TIData& other)	{ set(self, other.token_factory);			}
			static void  set(TIData& self, FType::FPtr fun)	{ self.token_factory = fun;					}
			static FType get(const TIData& self)			{ return FType(self, self.token_factory);	}
		};

		template<typename TagT>
		struct FSelector<TIFID_DATA_PROVIDER, TagT>
		{
			enum  { index = false };
			typedef FDataProvider FType;

			static void  set(TIData& self, TIData& other)	{ set(self, other.data_provider);			}
			static void  set(TIData& self, FType::FPtr fun)	{ self.data_provider = fun;					}
			static FType get(const TIData& self)			{ return FType(self, self.data_provider);	}
		};

		template<typename TagT>
		struct FSelector<TIFID_ERROR, TagT>
		{
			enum  { index = false };
			typedef FError FType;

			static void  set(TIData& self, TIData& other)	{ set(self, other.on_error);				}
			static void  set(TIData& self, FType::FPtr fun)	{ self.on_error = fun;						}
			static FType get(const TIData& self)			{ return FType(self, self.on_error);		}
		};

	public:
		template<TIFId id>
		bool valid() const
		{
			if(id == TIFID_ERROR)			return 0 != on_error;
			if(id == TIFID_CHECK_VERSION)	return 0 != version_check;
			if(id == TIFID_TOKEN_FACTORY)	return 0 != token_factory;
			if(id == TIFID_DATA_PROVIDER)	return 0 != data_provider;
			{
				ACT_MSC_WARNING_DISABLE(6201);	//!< \note Disable misleading C6201.
				return FSelector<id>::index ? 0 != functions[id] : false;
				ACT_MSC_WARNING_POP();
			}
		}

		template<TIFId id>
		void set(TIData& other)
		{
			FSelector<id>::set(*this, other);
		}

		template<TIFId id, typename RegT>
		void set(const char* name)
		{
			FSelector<id>::set(*this, RegT::GetCreatePointer(name));
			if(valid<id>() == false) throw InvalidParameterException();
		}

		template<TIFId id>
		void set(typename FSelector<id>::FType::FPtr fun)
		{
			FSelector<id>::set(*this, fun);
		}

		template<TIFId id>
		typename FSelector<id>::FType get() const
		{
			return FSelector<id>::get(*this);
		}

		template<BOOLean value>
		struct Prerequisite
		{
			bool operator()(const TIData& data) const
			{
				return value == data.flags.prerequisite;
			}
		};
	};

	//!
	//! TITokenInfo
	//! -----------------------------------------------------------------------
	struct TITokenInfo
	{
		TITokenInfo(size_t pin_len_max, size_t pin_len_min, size_t key_len_cr_)
			: serial_number_len(LEN_SERIALNO)
			, key_len_cr(key_len_cr_)
		{
			pin_len_max_admin = pin_len_max_so = pin_len_max_user = pin_len_max;
			pin_len_min_admin = pin_len_min_so = pin_len_min_user = pin_len_min;
		}

		TITokenInfo(const LengthInfo& pin_len_info, size_t key_len_cr_)
			: serial_number_len(LEN_SERIALNO)
			, key_len_cr(key_len_cr_)
		{
			pin_len_max_admin = pin_len_max_so = pin_len_max_user = pin_len_info.maxLen;
			pin_len_min_admin = pin_len_min_so = pin_len_min_user = pin_len_info.minLen;
		}

		size_t serial_number_len;

		size_t key_len_cr;

		size_t pin_len_max_admin;
		size_t pin_len_max_so;
		size_t pin_len_max_user;

		size_t pin_len_min_admin;
		size_t pin_len_min_so;
		size_t pin_len_min_user;
	};

#	include "actPackOff.h"

	//!
	//! ITokenInitializer
	//! -----------------------------------------------------------------------
	class ITokenInitializer : public IRefCounted
	{
	public:
		virtual ISCardOS* GetOS() const = 0;
		virtual const TITokenInfo& GetTokenInfo() const = 0;
		virtual const ProfileType* GetSupportedProfileList() const = 0;

		virtual bool SupportsProfile(ProfileType profile_type) const = 0;
		virtual void SetGenerator(IProfileGenerator* generator) = 0;
		virtual void SetObserver(ISCardCmdObserver* observer) = 0;

		virtual bool EraseProfile(const TIData& data, ProfileType profile_type = PROFILE_UNKNOWN) = 0;
		virtual bool ExistProfile(bool& is_pkcs15, bool& requires_adminpin) = 0;
		virtual void CreateProfile(TIData& data, ProfileType profile_type) = 0;
		virtual void FinalizeProfile(TIData& data) = 0;

		virtual void PinChangeReminder(TIData& data, bool enable) = 0;
	};

} // namespace act

#endif // ACT_ITokenInitializer_h
