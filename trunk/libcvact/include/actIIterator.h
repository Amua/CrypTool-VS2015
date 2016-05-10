// ---------------------------------------------------------------------------
// Name:      actIIterator.h
// Product:   cv act library
// Purpose:   Iterator interface template.
//
// Copyright: (c) 2013 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  08/20/2013
// ---------------------------------------------------------------------------

#ifndef ACT_IIterator_h
#define ACT_IIterator_h

#include "actIRefCounted.h"

namespace act
{
	//!
	//! \brief IIterator
	// -----------------------------------------------------------------------
	template
	<
		class TypeT,
		class InitT = void,
		class BaseT = IRefCounted
	>
	class IIterator;

	template<class TypeT>
	class IIterator<TypeT, void, IRefCounted> : public IRefCounted
	{
	public:
		virtual void	Reset() = 0;
		virtual TypeT*	Next() = 0;
	};

	template<class TypeT, class InitT>
	class IIterator<TypeT, InitT, IRefCounted> : public IRefCounted
	{
	public:
		virtual void	Reset(InitT* = 0) = 0;
		virtual TypeT*	Next() = 0;
	};

} // namespace act

#endif // ACT_IIterator_h
