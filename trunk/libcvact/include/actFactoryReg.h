// ---------------------------------------------------------------------------
// Name:      actFactoryReg.h
// Product:   cv act library
// Purpose:   Templates for simple factory-registry implementation.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_FactoryReg_h
#define ACT_FactoryReg_h
#pragma once

#include <actEnv.h>
#include <actLocation.h>

#include <map>
#include <cstring>

namespace act
{
	// ---------------------------------------------------------------------------
	// Actually defined in actUtility.cpp
	extern const char* Default;

	//!
	//! FactoryMapEntry<>
	// ---------------------------------------------------------------------------
	template<typename CreateF>
	struct FactoryMapEntry
	{
		typedef char	KeyType;
		typedef CreateF CreateFun;

		struct KeyLessPredicate
			: public std::binary_function<const KeyType*, const KeyType*, bool> 
		{
			bool operator()(const KeyType* left, const KeyType* right) const
			{
				if(left == 0) return false;
				if(right == 0) return true;
				return strcmp(left, right) < 0;
			}
		};

		typedef std::map
		<	const KeyType*, CreateF, KeyLessPredicate
		>	MapType;

		static const KeyType* const	empty;

		const KeyType*	keyvalue;
		CreateF			createptr;
	};

	template<typename CreateF>
	const typename FactoryMapEntry<CreateF>::KeyType* const
				   FactoryMapEntry<CreateF>::empty = "";

	//!
	//! \brief Get instance of concrete creator for keyvalue, bound on factory.
	// ---------------------------------------------------------------------------
	template<class FactoryT, class InvalidT>
	typename FactoryT::template Creator<InvalidT>::Type
	Bind(const typename FactoryT::KeyType* keyvalue)
	{
		return typename FactoryT::template Creator<InvalidT>::Type(keyvalue);
	}

	//!
	//! \brief ConcreteCreator<> simple concrete creator functor.
	// ---------------------------------------------------------------------------
	template<typename FactoryRegT, typename InvalidT>
	struct ConcreteCreator;

	template
	<
		template<class, class, class, class> class FactoryRegT,
		class ResultT, class CreateF, class MapEntryT, class MapT,
		typename InvalidT
	>
	struct ConcreteCreator<FactoryRegT<ResultT, CreateF, MapEntryT, MapT>, InvalidT>
		: MapEntryT
	{
		typedef FactoryRegT<ResultT, CreateF, MapEntryT, MapT> FactoryRegType;
		typedef typename MapEntryT::KeyType KeyType;

		ConcreteCreator(const KeyType* keyvalue)
		{
					MapEntryT::createptr = 0;
			if(0 == keyvalue)  keyvalue  = MapEntryT::empty;
					MapEntryT::keyvalue  = keyvalue;
			if(0 == FactoryRegType::GetEntry(*this).createptr)
					InvalidT::Throw(MapEntryT::keyvalue);
		}

		template<typename Arg0, typename T>
		ResultT* operator()(Arg0 arg0, const Location<T>& location)
		{
			CreateF createptr = MapEntryT::createptr;
			if(0 != createptr) return (*createptr)(arg0);
			InvalidT::Throw(location, MapEntryT::keyvalue);
			return 0;
		}
	};

	//!
	//! \brief FactoryReg<> implements a "global type-specific factory".
	// ---------------------------------------------------------------------------
	template
	<
		class ResultT,
		class CreateF,
		class MapEntryT,
		class MapT = typename MapEntryT::MapType
	>
	class FactoryReg
	{
	public:
		typedef typename MapEntryT::KeyType	KeyType;

		template<typename InvalidT>
		struct Creator
		{
			typedef ConcreteCreator
				<	FactoryReg<ResultT, CreateF, MapEntryT, MapT>,
					InvalidT
				>	Type;
		};

		static MapEntryT& Default(MapEntryT& entry)
		{
			entry.keyvalue = act::Default;
			return entry;
		}

		//!
		//! \brief Lookup factory method for \param keyvalue and execute it!
		//! \note  The given \param keyvalue will NOT be used as call parameter
		//!    (!) maybe temporary.
		// -----------------------------------------------------------------------
		static ResultT* Create(const KeyType* keyvalue)
		{
			if(keyvalue == 0) keyvalue = MapEntryT::empty;
			typename MapT::const_iterator result(g_map.find(keyvalue));
			if(result == g_map.end()) result = g_map.find(act::Default);
			return result != g_map.end() ? result->second(result->first) : 0;
		}

		//!
		//! \brief Lookup factory method for \param keyvalue and execute it
		//!        with additional \tparam ParamT.
		//! \note  The given \param keyvalue will NOT be used as call parameter
		//!    (!) maybe temporary.
		// -----------------------------------------------------------------------
		template<typename ParamT>
		static ResultT* Create(const KeyType* keyvalue, ParamT param)
		{
			if(keyvalue == 0) keyvalue = MapEntryT::empty;
			typename MapT::const_iterator result(g_map.find(keyvalue));
			if(result == g_map.end()) result = g_map.find(act::Default);
			return result != g_map.end() ? result->second(result->first, param) : 0;
		}

		template<typename ParamT>
		static ResultT* Create(ParamT param) { return Create<ParamT>(0, param); }
		static ResultT* Create()             { return Create(0);				}

		// -----------------------------------------------------------------------
		static const KeyType* GetName(const void* createptr)
		{
			if(createptr == 0) return 0;
			for(typename MapT::const_iterator i(g_map.begin()),
				end(g_map.end()); i != end; ++i)
				if(i->second == createptr)
					return i->first;

			return 0;
		}

		// -----------------------------------------------------------------------
		static const MapEntryT& GetEntry(MapEntryT& entry)
		{
			if(g_map.empty() == false)
				if(0 == entry.keyvalue)
					entry.createptr = g_map.begin()->second;
				else
				{
					typename MapT::const_iterator result(g_map.find(entry.keyvalue));
					if(result != g_map.end()) entry.createptr = result->second;
				}

			return entry;
		}

		// -----------------------------------------------------------------------
		static CreateF GetCreatePointer(const KeyType* keyvalue)
		{
			MapEntryT entry = { keyvalue, 0 };
			return	GetEntry(entry).createptr == 0
				?	GetEntry(Default(entry)).createptr
				:	entry.createptr;
		}

		// -----------------------------------------------------------------------
		static const KeyType* GetNextName(const KeyType* keyvalue)
		{
			if(keyvalue == 0) 
				return g_map.empty() == true ? 0 : g_map.begin()->first;

			typename MapT::const_iterator result(g_map.find(keyvalue));
			return result == g_map.end() || ++result == g_map.end() ? 0 : result->first;
		}

		// -----------------------------------------------------------------------
		static bool Insert(const KeyType* keyvalue, CreateF createptr, bool replace = false)
		{
			typename MapT::value_type value(keyvalue, createptr);
			std::pair<typename MapT::iterator, bool> result(g_map.insert(value));

			if(result.second == false)
				if(replace == true)
				{
					g_map.erase(result.first);
					result = g_map.insert(value);
				}

			return result.second;
		}

		// -----------------------------------------------------------------------
		static bool Insert(const MapEntryT* entry, bool replace = false)
		{
			bool succeeded = true;
			while(entry->keyvalue != 0)
			{
				succeeded &= Insert(entry->keyvalue, entry->createptr, replace);
				++entry;
			}

			return succeeded;
		}

	protected:
		static MapT g_map;
	};

	template<class ResultT, class CreateF, class MapEntryT, class MapT>
	MapT FactoryReg<ResultT, CreateF, MapEntryT, MapT>::g_map;

	//!
	//! \brief FactoryRegistry<> provides the default (simplified) \ref FactoryReg<>.
	// ---------------------------------------------------------------------------
	template
	<
		class ResultT,
		class CreateF, // ResultT*(*)(const char*),
		class EntryT = FactoryMapEntry<CreateF>
	>
	class FactoryRegistry : public FactoryReg<ResultT, CreateF, EntryT>
	{
	public:
		typedef CreateF	CreateFun;
		typedef EntryT	Entry;
	};

}		// namespace act
#endif	// ACT_FactoryReg_h
