//////////////////////////////////////////////////////////////////////////
// Name:      actMove.h
// Product:   cv act library
// Purpose:   template<>'s to implement move semantics
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/25/2010
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Move_h
#define ACT_Move_h

#include "actTypeTags.h"

namespace act
{
	//
	// type_of<T> used to dismantle T resulting in T'
	// --------------------------------------------------------------------------------	
	template<typename T> struct type_of             { typedef T type; };
	template<typename T> struct type_of<const T>    { typedef T type; };
	template<typename T> struct type_of<T*>         { typedef T type; };
	template<typename T> struct type_of<const T*>   { typedef T type; };
	template<typename T> struct type_of<T&>         { typedef T type; };
	template<typename T> struct type_of<const T&>   { typedef T type; };

	//
	// is_const<T> 
	// --------------------------------------------------------------------------------	
	template<typename T> struct is_const			{ enum { value = 0 }; };
	template<typename T> struct is_const<const T>	{ enum { value = 1 }; };
	template<typename T> struct is_const<T*>		{ enum { value = 0 }; };
	template<typename T> struct is_const<const T*>	{ enum { value = 1 }; };
	template<typename T> struct is_const<T&>		{ enum { value = 0 }; };
	template<typename T> struct is_const<const T&>	{ enum { value = 1 }; };

	//
	// is_base_of<T> used to check if U is a base of V
	// --------------------------------------------------------------------------------	
	template<typename U, typename V>
	class is_base_of
	{
		typedef char yes[1];
		typedef char no[2];

		static yes& test(U*);
		static no& test(...);
		static V* get();

	public:
		enum { value = sizeof(test(get())) == sizeof(yes) };
	};

	//! \brief move_from<...> used to implement move semantics
	// --------------------------------------------------------------------------------	
	template<typename T, typename U = void>
	class move_from;

	//! \brief move_from<T, TagPtrRef> spcialization, holds pointer to type T 
	// --------------------------------------------------------------------------------
	template<typename T>
	class move_from<T, TagPtrRef>
	{
	public:
		typedef typename type_of<T>::type type_t;

		explicit move_from(type_t*& ptr_ref)
			: m_ptr(ptr_ref)
		{
			ptr_ref = 0;
		}

		template<typename O>
		move_from(const move_from<O, TagPtrRef>& other)
			: m_ptr(other.template source<type_t>())
		{ }

		inline type_t*				source() const	{ return m_ptr; }
		template<typename O> O*		source() const	{ return m_ptr; }
		template<typename O> O*		move(O*& other)	{ swap(other);  return other; }
		template<typename O> void	swap(O*& other)	{ O* const tmp = other; other = m_ptr; m_ptr = tmp;	}

	private:
		type_t* m_ptr;

	private:
		template<typename O, typename U>
		friend class move_from;
	};

	//! \brief move_from<T, void> default spcialization, holds reference to type T 
	// --------------------------------------------------------------------------------
	template<typename T>
	class move_from<T, void>
	{
	public:
		typedef typename type_of<T>::type type_t;

		explicit move_from(type_t& ref)
			: m_ref(ref)
		{ }

		template<typename O>
		move_from(const move_from<O, void>& other)
			: m_ref(other.template source<type_t>())
		{ }

		inline type_t& source() const				{ return m_ref; }
		template<typename O> O& source() const		{ return m_ref; }

		template<typename O> void swap(O& other)	{ m_ref.swap(other); }
		template<typename O> O& move(O& other)		{ m_ref.swap(other); return other; }

	private:
		type_t& m_ref;

	private:
		template<typename O, typename U>
		friend class move_from;
	};

	//! \brief move_from<T, U> spcialization takes ownership of 'swapped-in' source data
	// --------------------------------------------------------------------------------
	template<typename T, typename U>
	class move_from : public move_from<U, void>
	{
	public:
		typedef typename type_of<T>::type type_t;

		explicit move_from(type_t& ref)
			: move_from<U, void>(m_value)
		{
			ref.swap(m_value);
		}

		template<typename O>
		move_from(move_from<O, void> other)
			: move_from<U, void>(m_value)
		{
			other.swap(m_value);
		}

	private:
		typename move_from<U, void>::type_t m_value;
	};

	//! \brief move_empty<T> used as default move_from<...> function parameter
	// --------------------------------------------------------------------------------
	template<typename T>
	class move_empty : public move_from<T, void>
	{
	public:
		move_empty()
			: move_from<T, void>(m_empty)
		{ }

		move_empty(const move_empty&)
			: move_from<T, void>(m_empty)
		{ }

		inline move_empty& operator=(const move_empty&) { return *this; }

	private:
		T m_empty;
	};

	//! \brief move<> helper function
	// --------------------------------------------------------------------------------
	template<typename T>
	inline move_from<T, void> move(T& ref)
	{
		return move_from<T, void>(ref);
	}

	//! \brief   move_ptr<> helper function
	//! \details can be used to initialize from \c ptr, if ownership has been
	//!          transferred already.
	// --------------------------------------------------------------------------------
	template<typename T>
	inline move_from<T, TagPtrRef> move_ptr(T* ptr)
	{
		return move_from<T, TagPtrRef>(ptr);
	}

	//! \brief   move_ptr_ref<> helper function
	//! \details can be used to initialize from \c ptrref, if ownership has been
	//!          transferred already, \c ptrref will always set to null.
	// --------------------------------------------------------------------------------
	template<typename T>
	inline move_from<T, TagPtrRef> move_ptr_ref(T*& ptrref)
	{
		return move_from<T, TagPtrRef>(ptrref);
	}

	//! \brief   attach_ptr<> alias for \c move_ptr<>.
	//! \see     move_ptr<>
	// --------------------------------------------------------------------------------
	template<typename T>
	inline move_from<T, TagPtrRef> attach_ptr(T* ptr)
	{
		return move_from<T, TagPtrRef>(ptr);
	}

} // namespace act

#endif // ACT_Move_h
