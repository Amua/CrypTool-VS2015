// ---------------------------------------------------------------------------
// Name:      actTypeTags.h
// Product:   cv act library
// Purpose:   TypeTag<> and usibility forward declarations.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  09/10/2010
// ---------------------------------------------------------------------------

#ifndef ACT_TypeTags_h
#define ACT_TypeTags_h

#include "actEnv.h"

namespace act
{
	//!
	//! \brief Int2Type<>
	template<unsigned Unsigned>
	struct Int2Type
	{
		enum { Value = Unsigned };
	};

	template<typename FirstT, typename SecondT>
	struct PairTag;

	//!
	//! \brief TypeTag<>
	template<typename TypeT>
	struct TypeTag
	{
		typedef TypeT Type;

		template<typename FirstT>
		struct PairFirst
		{
			typedef PairTag<FirstT, TypeT> Type;
		};

		template<typename SecondT>
		struct PairSecond
		{
			typedef PairTag<TypeT, SecondT> Type;
		};
	};

	typedef TypeTag<bool>	BoolTag;
	typedef TypeTag<char>	CharTag;
	typedef TypeTag<short>	ShortTag;
	typedef TypeTag<long>	LongTag;

	//!
	//! \brief PairType<>
	template<typename FirstT, typename SecondT>
	struct PairType
	{
		typedef FirstT	First;
		typedef SecondT	Second;
	};

	//!
	//! \brief PairTag<>
	template<typename FirstT, typename SecondT>
	struct PairTag
	{
		typedef TypeTag<FirstT>  First;
		typedef TypeTag<SecondT> Second;
	};

	enum BOOLOperator
	{
		BOOL_Unknown	= (1 << 0),
		BOOL_And		= (1 << 1),
		BOOL_Or			= (1 << 2),
		BOOL_Not		= (1 << 3),
		/* ... */
		BOOL_AndNot		= BOOL_Not | BOOL_And,
		BOOL_OrNot		= BOOL_Not | BOOL_Or,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(BOOLOperator);

	template
	<
		BOOLOperator	Operator,
		class			TagT,
		unsigned		Other
	>
	struct TypeCalc;

	template<class TagT, unsigned Other>
	struct TypeCalc<BOOL_And, TagT, Other> { enum { Value = TagT::Type::Value & Other }; };
	template<class TagT, unsigned Other>
	struct TypeCalc<BOOL_Or,  TagT, Other> { enum { Value = TagT::Type::Value | Other }; };

	template<class TagT, unsigned Other>
	struct TypeCalc<BOOL_AndNot, TagT, Other> { enum { Value = TypeCalc<BOOL_And, TagT, (~Other)>::Value }; };
	template<class TagT, unsigned Other>
	struct TypeCalc<BOOL_OrNot,  TagT, Other> { enum { Value = TypeCalc<BOOL_Or,  TagT, (~Other)>::Value }; };

	enum TypeId
	{
		TypeAny		= 0,
		TypeUnknown	= TypeAny,
		TypeDef,
		TypeTyp,
		/* ... */
		TypeMask	= (1 <<  8) - 1,
		TypeExcept	= (1 <<  8),
		TypeFun		= (1 <<  9),
		TypeCon		= (1 << 10),
		TypePtr		= (1 << 11),
		TypeRef		= (1 << 12),
		TypeArr		= (1 << 13),
		TypeMap		= (1 << 14),
		TypeFac		= (1 << 15),
		TypeReg		= (1 << 15),
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(TypeId);

	typedef TypeTag<Int2Type<TypeAny> >		TagAny;
	typedef TypeTag<Int2Type<TypeDef> >		TagDef;
	typedef TypeTag<Int2Type<TypeTyp> >		TagTyp;
	typedef TypeTag<Int2Type<TypeFun> >		TagFun;			//!< Indicate function
	typedef TypeTag<Int2Type<TypeFac> >		TagFac;			//!< Indicate type factory
	typedef TypeTag<Int2Type<TypeReg> >		TagReg;			//!< Indicate type registry 
	typedef TypeTag<Int2Type<TypeExcept> >	TagExcept;

	typedef TypeTag<TypeCalc<BOOL_Or, TagTyp,	 TypeRef> >	TagRef;
	typedef TypeTag<TypeCalc<BOOL_Or, TagRef,	 TypeArr> >	TagRefArr;
	typedef TypeTag<TypeCalc<BOOL_Or, TagRef,	 TypeMap> >	TagRefMap;

	typedef TypeTag<TypeCalc<BOOL_Or, TagTyp,	 TypePtr> >	TagPtr;
	typedef TypeTag<TypeCalc<BOOL_Or, TagPtr,	 TypeArr> >	TagPtrArr;
	typedef TypeTag<TypeCalc<BOOL_Or, TagPtr,	 TypeMap> >	TagPtrMap;

	typedef TypeTag<TypeCalc<BOOL_Or, TagRef,	 TypePtr> >	TagPtrRef;
	typedef TypeTag<TypeCalc<BOOL_Or, TagPtrRef, TypeArr> > TagPtrRefArr;
	typedef TypeTag<TypeCalc<BOOL_Or, TagPtrRef, TypeMap> > TagPtrRefMap;

	//
	// CloneFactory<>
	template<typename Tag, typename P1 = void, typename P2 = void, typename P3 = void>
	struct CloneFactory;

} // namespace act

#endif // ACT_TypeTags_h
