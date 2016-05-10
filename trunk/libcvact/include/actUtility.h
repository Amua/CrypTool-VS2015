//////////////////////////////////////////////////////////////////////////////////
// Name:      actUtility.h
// Product:   cv act library
// Purpose:   useful global functions
//
// Copyright: (c) 2000-2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Utility_h
#define ACT_Utility_h

#include "actBasics.h"
#include "actTypeTags.h"
#include "actException.h"
#include "actUTF8.h"

#include <typeinfo>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <stdio.h>
#include <ctype.h>

namespace act
{
#	if defined(__GNUC__) && (__GNUC__ < 4)
		typedef std::basic_string<wchar_t> wstring;
#	else
		using std::wstring;
#	endif

	namespace detail
	{
		//!
		//! \brief \c ACT_ARRAYSIZE macro.
		// ---------------------------------------------------------------------------
#		define ACT_ARRAYSIZE(array) (sizeof(act::detail::arraysize_helpler(array)))

		//!
		//! \brief arraysize_helpler<> - template used for defining ACT_ARRAYSIZE.
		//! \note  No implementation needed (!) only type for sizeof calculations.
		//! \note  GCC wants both prototypes.
		// ---------------------------------------------------------------------------
		template<typename T, size_t N> char (&arraysize_helpler(T (&array)[N]))[N];
		template<typename T, size_t N> char (&arraysize_helpler(const T (&array)[N]))[N];
	}

	class IParam;

	//
	// enums
	//

	enum displaymode
	{
		DM_AUTO		= 0,		//<! Auto - convert to hex string when nonprintable chars found
		DM_OFF		= 1,		//<! Off - Don't convert, leave nonprintable chars as-is
		DM_ON		= 2,		//<! On - Always convert to hex string, even if contents is wholly printable
	};

	//
	// Const Values
	//

	const size_t sizeof_uuid = 16;

	//
	// Prototypes
	//

	const char* get_string_param(paramid_t id, IParam* owner);

	void get_string_seq(const std::string& s, const std::string start, const std::string end, 
		std::string& result, bool case_sens);

	// Converts an unsigned hexadecimal number (independent of prefix "0x")
	// into a Blob and backwards.
	//  - for blob2hex: the user has to allocate hexnumber
	Blob& hex2blob(const char* hexnumber, Blob& b);

	inline Blob& hex2blob(const std::string& hexnumber, Blob& b)
	{
		return hex2blob(hexnumber.c_str(), b);
	}
	inline Blob hex2blob(const char* hexnumber)
	{
		Blob b;
		return hex2blob(hexnumber, b).move();
	}

	void blob2hex(const Blob& b, char* hexnumber); 
	std::string blob2hex(const Blob& b);

	template<typename ResultT>
	ResultT& blob2hex(const Blob& b, ResultT& rval, bool append = true)
	{
		typename ResultT::value_type hex[2];
		array_type<typename ResultT::value_type> hexbyte(hex);
		const typename ResultT::value_type hexval[] = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
		};

		if(false == append) rval.clear();
		rval.reserve(b.size() * 2 + rval.size());
		for(size_t i = 0; i < b.size(); ++i)
		{
			hex[0] = hexval[(b[i] >> 4) & 0x0f];
			hex[1] = hexval[(b[i] >> 0) & 0x0f];
			hexbyte.append(rval);
		}
		return rval;
	}

	// file i/o for Blob
	bool file2blob(const char* filename, Blob& blob);
	bool blob2file(const char* filename, const Blob& blob);

	// Create an ISO 9834-8 / RFC 4122 version 4 (pseudo random) UUID.
	// Output string format is "xxxxxxxx-xxxx-4xxx-vxxx-xxxxxxxxxxxx", where
	// x is random hex char 0 <= x <= f and v an element of { 8, 9, a, b}.
	Blob& uuidgen(Blob& uuid, bool network_byte_order = true);
	std::string& uuidgen(Blob& uuid, std::string& uuid_str);
	std::string& uuidgen(std::string& uuid_str);
	std::string  uuidgen();

	// Create an ISO 9834-8 / RFC 4122 version 5 (SHA-1 based) UUID from name.
	// Input is the namespace UUID in network byte order and the name (both unchecked).
	Blob& uuidgen_v5(const Blob& name_space_id, const Blob& name, Blob& uuid, bool network_byte_order = true);

	Blob& networkToLocalByteOrder(Blob& uuid);
	Blob& localToNetworkByteOrder(Blob& uuid);

	void uuid2string(const Blob& uuid, std::string& uuid_str, bool is_network_byte_order = true);
	std::string uuid2string(const Blob& uuid, bool is_network_byte_order = true);

	std::string serno2string(const Blob& serno, displaymode dm = DM_AUTO);
	std::string id2string(const Blob& id, bool is_network_byte_order = true);

	// OID to string conversion
	void EncodeOID(const std::string& oid_str, Blob& encoded_oid);
	void DecodeOID(const Blob& encoded_oid, std::string& oid_str);

	// CBCMAC with ISO padding
	void iCBCMAC(const char* cipher, const Blob& iv, const Blob& mac_key, const Blob& mac_data, Blob& mac);

	Blob& SetDESKeyParity(Blob& key);
	bool  CheckDESKeyParity(const Blob& key);

	void ASN1ToSequenceOf(Blob& asn1_data);
	Blob GetASN1SequenceOf(const Blob& asn1_data);
	Blob GetASN1EncodedLength(size_t length);
	Blob& ASN1EncodeLength(Blob& encoded, size_t length);

	// TLV parsing helpers
	size_t GetTag(ulong& tag, const Blob& data, size_t offset = 0); // returns new offset
	size_t SkipTagLength(ulong intag, const byte* tlv_data, size_t tlv_data_len);
	size_t SkipTLVElement(ulong intag, const Blob::iterator& begin, const Blob::iterator& end);
	size_t SkipTLVElement(ulong intag, const byte* tlv_data, size_t tlv_data_len, bool skip_value = true);
	int FindTlvTemplate(Blob& value, const Blob& tlv_data, ulong intag, int counts);

	// BER/DER helpers
	// Returns the size of the first block in BER/DER encoded data or zero if invalid.
	size_t GetEncodedSize(const Blob& data);

	// Key helpers
	size_t CalculateRSAKeySize(const Blob& prime_p, const Blob& prime_q);

	//
	// Implementation
	//

	//! \brief Safely calls \c GetName with parameter \c arg on \c StaticT.
	// --------------------------------------------------------------------
	template<typename ConverterT, typename StaticT, typename ParamT>
	Blob SafeGetName(ParamT* arg)
	{
		if(0 != arg)
		{
			const char* name = StaticT::GetName(arg);
			if(name != 0) return ConverterT(name).move();
		}
		return Blob();
	}

	//! \brief Safely calls \c GetName on \c instance of \c TypeT.
	// --------------------------------------------------------------------
	template<typename ConverterT, typename TypeT>
	Blob SafeGetName(TypeT* const instance)
	{
		if(0 != instance)
		{
			const char* name = instance->GetName();
			if(name != 0) return ConverterT(name).move();
		}
		return Blob();
	}

	//! \brief SafeGetName<TagReg> - Name of instance using factory \c RegistryT lookup.
	// --------------------------------------------------------------------
	template<typename TagT, typename ConverterT, typename RegistryT, typename TypeT>
	Blob SafeGetName(TypeT* const instance, const TagReg& = TagT())
	{
		void* const create_ptr = 0 != instance ? instance->GetCreatePointer() : 0;
		return SafeGetName<ConverterT, RegistryT>(create_ptr).move();
	}

	//! \brief Acessor<>
	// ---------------------------------------------------------------------------
	template<typename ArrayT, typename ReferenceT, typename ExceptionT = OutOfRangeException>
	struct Accessor
	{
		Accessor(ArrayT& array_ref_, const char* where_)
			: array_ref(array_ref_)
			, where(where_)
		{ }

		ReferenceT operator[](typename ArrayT::size_type index)
		{
			if(index < array_ref.size())
				return array_ref[index];
			throw ExceptionT("index out of range", where, ulong(index));
		}

		ArrayT& array_ref;
		const char* where;
	};

	//! \brief accessor<> - convenience helper providing automatic type deduction.
	// ---------------------------------------------------------------------------
	template<typename ArrayT>
	Accessor<ArrayT, typename ArrayT::reference> accessor(ArrayT& array, const char* where = 0)
	{
		return Accessor<ArrayT, typename ArrayT::reference>(array, where);
	}

	//! \brief accessor<const> - convenience helper providing automatic type deduction.
	// ---------------------------------------------------------------------------
	template<typename ArrayT>
	Accessor<const ArrayT, typename ArrayT::const_reference> accessor(const ArrayT& array, const char* where = 0)
	{
		return Accessor<const ArrayT, typename ArrayT::const_reference>(array, where);
	}

	//! \brief is_whitespace<>
	// ---------------------------------------------------------------------------
	template<typename TypeT>
	struct is_whitespace : is_whitespace<typename TypeT::value_type>
	{
		typedef typename TypeT::value_type argument_type;
		using is_whitespace<typename TypeT::value_type>::operator();
	};

	template<>
	struct is_whitespace<char>
	{
		typedef char argument_type;
		bool operator()(unsigned char value) const
		{
			return std::isspace(value) != 0;
		}
	};

	template<>
	struct is_whitespace<wchar_t>
	{
		typedef wchar_t argument_type;
		bool operator()(wchar_t value) const
		{
			return std::iswspace(value) != 0;
		}
	};

	//! \brief erase_right<>
	// ---------------------------------------------------------------------------
	template<typename PredicateT, typename TypeT>
	inline TypeT& erase_right(const PredicateT& predicate, TypeT& value)
	{
		value.erase(std::find_if(value.rbegin(), value.rend(), predicate).base(), value.end());
		return value;
	}

	//! \brief fill<>
	// ---------------------------------------------------------------------------
	template<typename TypeT>
	inline void fill(TypeT* begin, size_t length, byte value)
	{
		ACT_ASSERT(begin != 0);
		std::fill(reinterpret_cast<act::byte*>(begin),
				  reinterpret_cast<act::byte*>(begin) + length, value);
	}

	//! \brief value_type<T>
	// ---------------------------------------------------------------------------
	template<typename ValueT>
	struct value_type
	{
		value_type(const ValueT& refval) : val(refval) { }

		inline operator ValueT() const { return val; }

		ValueT val;
	};

	//! \brief byvalue<ValueT>
	// ---------------------------------------------------------------------------
	template<typename ValueT>
	value_type<ValueT> byvalue(const ValueT& refval)
	{
		return value_type<ValueT>(refval);
	}

	//! \brief scoped_delete<PointerT>
	// ---------------------------------------------------------------------------
	template<typename PointerT>
	struct scoped_delete<PointerT, void, TagPtr>
	{
		typedef scoped_delete<PointerT, void, TagPtr> this_type;

		explicit scoped_delete(const value_type<PointerT>& ref)
			: ptr(ref)	 { }
		explicit scoped_delete(PointerT& ref)
			: ptr(ref)   { ref = 0;    }
		 scoped_delete() { ptr = 0;    }
		~scoped_delete() { delete ptr; }

		void operator()(PointerT ptr)  { delete ptr; }

		PointerT operator->() const
		{
			if(ptr != 0) return ptr;
			throw NullPointerException();
		}

		PointerT ptr;
	};

	//! \brief checked_delete<PointerT>
	// ---------------------------------------------------------------------------
	template<typename PointerT>
	scoped_delete<PointerT, void, TagPtr> checked_delete(PointerT& ptr_ref)
	{
		return scoped_delete<PointerT, void, TagPtr>(ptr_ref);
	}

	//! \brief scoped_delete<AutoPtrT<TypeT> >
	// ---------------------------------------------------------------------------
	template
	<
		template<class> class AutoPtrT,
		class TypeT
	>
	struct scoped_delete<AutoPtrT<TypeT>, void, TagPtr>
	{
		typedef scoped_delete<AutoPtrT<TypeT>, void, TagPtr> this_type;

		explicit scoped_delete(AutoPtrT<TypeT>& ptr_ref) : ptr(ptr_ref) { }
		~scoped_delete() { AutoPtrT<TypeT>(ptr); }

		TypeT* operator->() const
		{
			TypeT* ptr_ = ptr.get();
			if(ptr_ != 0) return ptr_;
			throw NullPointerException();
		}

		AutoPtrT<TypeT> ptr;
	};

	//! \brief checked_delete<AutoPtrT<TypeT> >
	// ---------------------------------------------------------------------------
	template
	<
		template<class> class AutoPtrT,
		class TypeT
	>
	scoped_delete<AutoPtrT<TypeT>, void, TagPtr>
	checked_delete(AutoPtrT<TypeT>& ptr_ref)
	{
		return scoped_delete<AutoPtrT<TypeT>, void, TagPtr>(ptr_ref);
	}

	//! \brief scoped_delete<PointerT, DestructF>
	// ---------------------------------------------------------------------------
	template<typename PointerT, class DestructF>
	struct scoped_delete<PointerT, DestructF, TagPtr>
		 : scoped_delete<PointerT, void, TagPtr>
	{
		typedef scoped_delete<PointerT, DestructF, TagPtr> this_type;
		typedef scoped_delete<PointerT, void, TagPtr> base_type;
		typedef DestructF destruct_func;
		using base_type::operator->;

		scoped_delete(const value_type<PointerT>& ptr_ref, const DestructF& destruct_)
			: base_type(ptr_ref), destruct(destruct_)
		{ }

		scoped_delete(PointerT& ptr_ref, const DestructF& destruct_)
			: base_type(ptr_ref), destruct(destruct_)
		{ }

		~scoped_delete()
		{
			PointerT const target = base_type::ptr;
			base_type::ptr = 0;
			if(target != 0) destruct(target);
		}

		destruct_func destruct;
	};

	//! \brief  checked_delete<TypeT, DestructF>(...)
	//! \param  ptr_ref reference of PointerT pointing to instance, well be reset to 0.
	//! \param  destruct instance providing function call operator used for destruction, like std::mem_fun(&TypeT::Destroy).
	//! \return instance of specific scope_delete<>.
	// ---------------------------------------------------------------------------
	template<typename TypeT, class DestructF>
	scoped_delete<TypeT*, DestructF, TagPtr>
	checked_delete(TypeT*& ptr_ref, const DestructF& destruct)
	{
		return scoped_delete<TypeT*, DestructF, TagPtr>(ptr_ref, destruct);
	}
	template<typename TypeT, class DestructF>
	scoped_delete<TypeT*, DestructF, TagPtr>
	checked_delete(const value_type<TypeT*>& ptr_ref, const DestructF& destruct)
	{
		return scoped_delete<TypeT*, DestructF, TagPtr>(ptr_ref, destruct);
	}

	//! \brief scoped_delete<ArrayT<PointerT, AllocatorT>, DestructF>
	// ---------------------------------------------------------------------------
	template
	<
		template<class, class> class ArrayT,
		class PointerT, class AllocatorT,
		class DestructF
	>
	struct scoped_delete<ArrayT<PointerT, AllocatorT>, DestructF, TagPtrArr>
	{
		typedef scoped_delete<ArrayT<PointerT, AllocatorT>, DestructF, TagPtrArr> this_type;
		typedef ArrayT<PointerT, AllocatorT> container_type;
		typedef DestructF destruct_func;

		explicit scoped_delete(container_type& target, const destruct_func& df)
			: destruct(df)
		{	  container.swap(target);		}

		scoped_delete(container_type& target)
		{	  container.swap(target);		}

		~scoped_delete()
		{	release(container, destruct);	}

		static void release(container_type& container, destruct_func& destruct)
		{
			if(container.empty() == true)
				return;

			container_type failed;
			typedef typename container_type::iterator iterator;
			for(iterator i(container.begin()), end(container.end()); i != end; ++i)
				try					{ destruct(*i);			}
				catch(Exception&)	{ failed.push_back(*i); }

			container.swap(failed);
		}

		destruct_func  destruct;
		container_type container;
	};

	//! \brief  checked_delete<ArrayT<TypeT*, AllocatorT>, DestructF>(...)
	//! \param  container reference to iterateable array<TypeT*> containing the instances to be deleted, ownership will be taken!
	//! \param  destruct instance providing function call operator used for destruction, like std::mem_fun(&TypeT::Destroy).
	//! \return instance of scope_delete<>.
	// ---------------------------------------------------------------------------
	template
	<
		template<class,	class>	class ArrayT,
								class TypeT,
								class AllocatorT,
								class DestructF
	>
	scoped_delete< ArrayT<TypeT*, AllocatorT>, DestructF, TagPtrArr>
	checked_delete(ArrayT<TypeT*, AllocatorT>& container, const DestructF& destruct)
	{
		return scoped_delete<ArrayT<TypeT*, AllocatorT>, DestructF, TagPtrArr>(container, destruct);
	}

	//! \brief checked_delete<>
	// ---------------------------------------------------------------------------
	template
	<
		template<class,	class>	class ArrayT,
								class TypeT,
								class AllocatorT
	>
	scoped_delete< ArrayT<TypeT*, AllocatorT>, scoped_delete<TypeT*, void, TagPtr>, TagPtrArr>
	checked_delete(ArrayT<TypeT*, AllocatorT>& container)
	{
		return container;
	}

	//! \brief scoped_delete<MapT<TypeT*> >
	// ---------------------------------------------------------------------------
	template
	<
		template<class, class, class, class> class MapT,
		class KeyT, class TypeT, class PredT, class AllocatorT,
		class DestructF
	>
	struct scoped_delete<MapT<KeyT, TypeT, PredT, AllocatorT>, DestructF, TagPtrMap>
	{
		typedef scoped_delete<MapT<KeyT, TypeT, PredT, AllocatorT>, DestructF, TagPtrMap> this_type;
		typedef MapT<KeyT, TypeT, PredT, AllocatorT> container_type;
		typedef DestructF destruct_func;

		explicit scoped_delete(container_type& container_, const destruct_func& destruct_)
			: destruct(destruct_)
		{	  container.swap(container_);	}

		~scoped_delete()
		{	release(container, destruct);	}

		static void release(container_type& container, const destruct_func& destruct)
		{
			if(container.empty() == true) return;

			container_type failed;
			typedef typename container_type::const_iterator const_iterator;
			for(const_iterator i(container.begin()), end(container.end()); i != end; ++i)
				try					{ destruct(i->second);	}
				catch(Exception&)	{ failed.insert(*i);	}

			container.swap(failed);
		}

		destruct_func  destruct;
		container_type container;
	};

	//! \brief checked_delete_map(map_of_ptr_to_type, std::mem_fun(&type::destruct));
	// ---------------------------------------------------------------------------
	template
	<
		template<class, class, class, class> class MapT,
		class KeyT, class TypeT, class PredT, class AllocatorT,
		class DestructF
	>
	scoped_delete<MapT<KeyT, TypeT, PredT, AllocatorT>, DestructF, TagPtrMap>
	checked_delete_map(MapT<KeyT, TypeT, PredT, AllocatorT>& map_ref, const DestructF& destruct)
	{
		return scoped_delete<MapT<KeyT, TypeT, PredT, AllocatorT>, DestructF, TagPtrMap>(map_ref, destruct);
	}

	//! \brief scoped_delete<>
	// ---------------------------------------------------------------------------
	template<typename TypeT, class DestructF>
	struct scoped_delete<TypeT, DestructF, TagAny>
	{
		typedef scoped_delete<TypeT, DestructF, TagAny> this_type;

		explicit scoped_delete(const DestructF& destruct_)
			: destruct(destruct_)
		{ }

		~scoped_delete()
		{	if(value.empty() == false) checked_delete(value, destruct); }

		DestructF destruct;
		TypeT	  value;
	};

	//! \brief checked_cast<>(...)
	// ---------------------------------------------------------------------------
	template<class U, class E, class V, class T>
	U checked_cast(V ptr, const Location<T>& location)
	{
		ACT_MSC_WARNING_DISABLE(6287);
		if(0 != ptr && 0 != dynamic_cast<U>(ptr)) return static_cast<U>(ptr);
		ACT_MSC_WARNING_POP();
		throw E(typeid(U).name(), location);
	}
	template<class U, class V, class T>
	inline U checked_cast(V ptr, const Location<T>& location)
	{
		return checked_cast<U, BadCastException, V, T>(ptr, location);
	}

	//! \brief checked_cast<>(..., std::nothrow)
	// ---------------------------------------------------------------------------
	template<class U, class E, class V, class T>
	U checked_cast(V ptr, const Location<T>& location, const std::nothrow_t&)
	{
		ACT_MSC_WARNING_DISABLE(6287);
		if(0 != ptr && 0 != dynamic_cast<U>(ptr)) return static_cast<U>(ptr);
		ACT_MSC_WARNING_POP();
		return 0;
	}
	template<class U, class V, class T>
	inline U checked_cast(V ptr, const Location<T>& location, const std::nothrow_t& nothrow)
	{
		return checked_cast<U, BadCastException, V, T>(ptr, location, nothrow);
	}

	//! \brief checked_static_cast<>
	// ---------------------------------------------------------------------------
	template<class U, class V>
	inline U checked_static_cast(V ptr)
	{
		ACT_ASSERT(ptr != 0);
		ACT_ASSERT(dynamic_cast<U>(ptr) != 0);
		return static_cast<U>(ptr);
	}
	template<class U, class E, class V, class T>
	U checked_static_cast(V ptr, const Location<T>& location)
	{
		if(0 == ptr) throw E(typeid(U).name(), location);
		return static_cast<U>(ptr);
	}
	template<class U, class V, class T>
	inline U checked_static_cast(V ptr, const Location<T>& location)
	{
		return checked_cast<U, NullPointerException, V, T>(ptr, location);
	}

	//! \brief reverse_order<>
	// ---------------------------------------------------------------------------
	template<class T>
	void reverse_order(T& container)
	{
		typename T::size_type i;
		typename T::size_type half(container.size() / 2);
		typename T::size_type last(container.size() - 1);

		for(i = 0; i < half; ++i)
			std::swap(container[i], container[last - i]);
	}

	// ---------------------------------------------------------------------------
	inline int max_int()
	{
		return int((unsigned(1) << (8 * sizeof(int) - 1)) - 1);
	}

	// ---------------------------------------------------------------------------
	inline void OS2IP(Blob& number)
	{
		// octet string to integer presentation
		if((number.at(0) & byte(0x80)) != 0) 
			number.insert(number.begin(), 0);
	}

	// ---------------------------------------------------------------------------
	inline void I2OSP(Blob& number)
	{
		// integer to octet string presentation
		if(number.at(0) == byte(0)) 
			number.erase(number.begin());
	}

	// ---------------------------------------------------------------------------
	inline void byte2long(const byte *in, size_t input_len, uint32* out)
	{
		size_t i, output_len = input_len / 4;
		for(i = 0; i < output_len; i++)
			out[i] = in[i * 4]
				|	(in[i * 4 + 1] << 8)
				|	(in[i * 4 + 2] << 16)
				|	(in[i * 4 + 3] << 24);
	}

	// ---------------------------------------------------------------------------
	inline void long2byte(const uint32 *in, size_t input_len, byte* out)
	{
		size_t i, output_len = input_len * 4;
		for(i = 0; i < output_len; i++) 
			out[i] = byte(in[i / 4] >> (8 * (i % 4)));
	}

	// ---------------------------------------------------------------------------
	inline void sweep(void* Mem, size_t l)
	{
		std::fill_n(reinterpret_cast<byte*>(Mem), l, byte(0));
	}

	// ---------------------------------------------------------------------------
	template<class TypeT>
	inline const TypeT Min(const TypeT& a, const TypeT& b) 
	{
		return (a < b) ? a : b;
	}

	// ---------------------------------------------------------------------------
	template<class TypeT>
	inline const TypeT& Max(const TypeT& a, const TypeT& b)
	{
		return (a<b)? b : a;
	}

	// ---------------------------------------------------------------------------
	template<class T1, class T2, class T3>
	inline void xor_n(T1 a, T2 len, T3 b)
	{
		for(T2 i = 0; i < len; i++) b[i] ^= a[i];
	}

	// ---------------------------------------------------------------------------
	template<class T1, class T3> inline void Xor(T1 a, T1 a_end, T3 b)
	{
		while(a < a_end)
			*b++ ^= *a++;
	}

	// ---------------------------------------------------------------------------
	inline const char* blob2char(Blob& b)
	{
		b.push_back(byte(0));
		return reinterpret_cast<const char*>(&b[0]);
	}

	// ---------------------------------------------------------------------------
	std::string& blob2string(const Blob& value, std::string& value_str, bool append = false);

	// ---------------------------------------------------------------------------
	inline std::string blob2string(const Blob& value, bool append = false)
	{
		std::string value_tmp;
		return blob2string(value, value_tmp, append);
	}

	// ---------------------------------------------------------------------------
	inline std::string byte2hex(const byte i) 
	{
		char tmp[8];
		sprintf(tmp, "%02x", i);
		return tmp;
	}

	// ---------------------------------------------------------------------------
	inline bool isDecimal(const byte c) 
	{
		return (c >= byte('0') && c <= byte('9'));
	}

	// ---------------------------------------------------------------------------
	inline bool isDecimal(const Blob& b) 
	{
		size_t i, b_len = b.size();

		for(i = 0; i < b_len; ++i) 
			if(!isDecimal(b[i]))
				return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isHex(const byte c) 
	{
		if((c < byte('0') || c > byte('9')) 
		&& (c < byte('a') || c > byte('f')) 
		&& (c < byte('A') || c > byte('F')))
			return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isHex(const Blob& b) 
	{
		size_t i, b_len = b.size();

		for(i = 0; i < b_len; ++i) 
			if(!isHex(b[i]))
				return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isAlphanumeric(const byte c) 
	{
		if((c < byte('0') || c > byte('9')) 
		&& (c < byte('a') || c > byte('z')) 
		&& (c < byte('A') || c > byte('Z')))
			return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isAlphanumeric(const Blob& b) 
	{
		size_t i, b_len = b.size();

		for(i = 0; i < b_len; ++i) 
			if(!isAlphanumeric(b[i]))
				return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isPrintable(const Blob& b) 
	{
		size_t i, b_len = b.size();

		for(i = 0; i < b_len; ++i) 
			if(isprint(int(b[i])) == 0)
				return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isZeroBlob(const Blob& b) 
	{
		if(b.empty()) 
			throw LogicalException("bad size", "isZeroBlob");

		Blob::const_reverse_iterator iter(b.rbegin());
		for( ; iter != b.rend(); ++iter)
			if(*iter != 0)
				return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline bool isUUIDFormat(const Blob& b, bool is_network_byte_order) 
	{
		if(b.size() != sizeof_uuid)
			return false;

		// check version (high nibble of RFC 4122 time_hi_and_version field)
		byte vbyte = is_network_byte_order ? b[6] : b[7];
		if(vbyte >= 0x60) // max version is 5
			return false;

		return true;
	}

	// ---------------------------------------------------------------------------
	inline ulong blob2long(const Blob& b) 
	{
		if(b.empty()) 
			throw LogicalException("bad size", "blob2long");

		Blob tmp(b);
		while(tmp[0] == 0 && tmp.size() > sizeof(ulong))
			tmp.erase(tmp.begin());

		if(tmp.size() > sizeof(ulong)) 
			throw LogicalException("bad size", "blob2long");

		ulong n = tmp[0];
		for(unsigned i = 1; i < tmp.size(); ++i) 
		{
			n <<= 8;
			n |= tmp[i];
		}
		return n;
	}

	// ---------------------------------------------------------------------------
	inline Blob& long2blob(ulong n, Blob& value) 
	{
		value.resize(sizeof(ulong));
		for(size_t i = sizeof(ulong) - 1, j = 0; j < sizeof(ulong); --i, ++j) 
			value[j] = byte((n >> (8 * i)) & 0xff);
		return value;
	}

	// ---------------------------------------------------------------------------
	inline Blob long2blob(ulong n) 
	{
		Blob value;
		return move(long2blob(n, value));
	}

	// ---------------------------------------------------------------------------
	inline Blob size2blob(size_t size)
	{
		Blob tmp;
		tmp.reserve(8);

		if(size == 0)
		{
			tmp.resize(1);
			return move(tmp);
		}
		size_t remaining = size;
		while(remaining > 0)
		{
			tmp.insert(tmp.begin(), byte(remaining & 0xFF));
			remaining >>= 8;
		}
		return move(tmp);
	}

	// ---------------------------------------------------------------------------
	inline ushort blob2short(const Blob& b) 
	{
		if(b.size() != sizeof(ushort)) 
			throw LogicalException("bad size", "blob2short");

		ushort n = b[1];
		n += (b[0] << 8);
		return n;
	}

	//! \brief   memincr
	//! \details input \c a as big-endian byte array.
	//! \return  carry and \c ++a, incremented with carry.
	// ---------------------------------------------------------------------------
	inline byte memincr(byte* a, int len) 
	{
		int i = len-1;
		byte carry;
		do {
			carry = ++a[i] == 0 ? 1 : 0;
		} while( --i >= 0 && carry != 0);
		return carry;
	}

	//! \brief   memadd
	//! \details input \c a and \c b as big-endian byte arrays.
	//! \return  carry and a += b, added with carry.
	// ---------------------------------------------------------------------------
	inline byte memadd(byte* a, const byte* b, int len, byte carry = 0) 
	{
		int i = len - 1;
		ulong tmp;
		for(; i >= 0; --i)
		{
			tmp = a[i] + b[i] + carry;
			a[i]  = byte(tmp & 0xff);
			carry = byte(tmp >> 8);
		}
		return carry;
	}

	// ---------------------------------------------------------------------------
	inline void convert_to_upper(std::string& s)
	{
		for(std::string::iterator it = s.begin(); it != s.end() ; ++it)
			*it = toupper(*it);
	}

} //namespace act

#endif // ACT_Utility_h
