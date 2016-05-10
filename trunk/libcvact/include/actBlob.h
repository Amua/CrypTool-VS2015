//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlob.h
// Product:   cv act library
// Purpose:   The datatype Blob (Binary Large Object) is a universal type, which
//            can be used for any data. The class Blob almost behaves like 
//            std::vector<unsigned char> with the difference that freed memory 
//            is filled with zeros to enhance security.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Blob_h
#define ACT_Blob_h

#include "actEnv.h"
#include "actMove.h"
#include "actBasics.h"
#include "actAllocator.h"

#if !defined(UNDER_CE_30)
#	include <iostream>
#endif // UNDER_CE_30

#if !defined(NO_STL_SUPPORT)
#	include <utility>	// used for reserve_iterator
#	include <string>	// used for string
#else
	// --------------------------------------------------------------------------------
	// if there is no STL support, we define reverse_iterator here.
	// --------------------------------------------------------------------------------
	namespace std
	{	
				// ITERATOR TAGS (from <iterator>)
		struct input_iterator_tag {};
		struct output_iterator_tag {};
		struct forward_iterator_tag
			: public input_iterator_tag {};
		struct bidirectional_iterator_tag
			: public forward_iterator_tag {};
		struct random_access_iterator_tag
			: public bidirectional_iterator_tag  {};

		// TEMPLATE CLASS iterator (from <iterator>)
		template<class _C, class _Ty, class _D = ptrdiff_t>
			struct iterator {
			typedef _C iterator_category;
			typedef _Ty value_type;
			typedef _D distance_type;
			};
		template<class _Ty, class _D>
			struct _Bidit : public iterator<bidirectional_iterator_tag,
				_Ty, _D> {};
		template<class _Ty, class _D>
			struct _Ranit : public iterator<random_access_iterator_tag,
				_Ty, _D> {};
		
		// TEMPLATE CLASS iterator_traits (from <iterator>)
		template<class _It>
			struct iterator_traits {
			typedef _It::iterator_category iterator_category;
			typedef _It::value_type value_type;
			typedef _It::distance_type distance_type;
			};

		
		// TEMPLATE CLASS reverse_iterator (from <iterator>)
		template<class _RI,
			class _Ty,
			class _Rt = _Ty&,
			class _Pt = _Ty *,
			class _D = int>
			class reverse_iterator : public _Ranit<_Ty, _D> {
		public:
			typedef reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> _Myt;
			typedef _RI iter_type;
			typedef _Rt reference_type;
			typedef _Pt pointer_type;
			reverse_iterator()
				{}
			explicit reverse_iterator(_RI _X)
				: current(_X) {}
			_RI base() const
				{return(current); }
			_Rt operator*() const
				{return(*(current - 1)); }
		//	_Pt operator->() const
		//		{return(&**this); }
			_Myt& operator++()
				{--current;
				return(*this); }
			_Myt operator++(int)
				{_Myt _Tmp = *this;
				--current;
				return(_Tmp); }
			_Myt& operator--()
				{++current;
				return(*this); }
			_Myt operator--(int)
				{_Myt _Tmp = *this;
				++current;
				return(_Tmp); }
			_Myt& operator+=(_D _N)
				{current -= _N;
				return(*this); }
			_Myt operator+(_D _N) const
				{return(_Myt(current - _N)); }
			_Myt& operator-=(_D _N)
				{current += _N;
				return(*this); }
			_Myt operator-(_D _N) const
				{return(_Myt(current + _N)); }
			_Rt operator[](_D _N) const
				{return(*(*this + _N)); }
		protected:
			_RI current;
			};
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator==(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_X) == get_base(_Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator!=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X == _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) < get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(_Y < _X); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_Y < _X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X < _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			_D __cdecl operator-(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) - get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> __cdecl operator+(_D _N,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>(
				get_base(_Y) - _N)); }
	}	// namespace std
#endif	// NO_STL_SUPPORT

// --------------------------------------------------------------------------------
namespace act
{
	class FileAndLine;

	//!
	//! \brief Simple array type impl.
	// ---------------------------------------------------------------------------
	template<typename value_t>
	struct array_type
	{
		struct array
		{
			const value_t*	 value;
			size_t			 size;
		};

		typedef const array  carray;
		typedef const array* pcarray;

		struct initializer : array_type<value_t>::array
		{
			typedef typename array_type<value_t>::array base_t;
			using   base_t::value;
			using   base_t::size;

			initializer()
			{
				value = 0;
				size  = 0;
			}

			initializer(const array& other)
			{
				size  = other.size;
				value = other.value;
			}

			template<size_t len>
			initializer(const value_t(&arr)[len])
			{
				size  = len;
				value = len != 0 ? &arr[0] : 0;
			}
		};

		array_type(const initializer& arr)
			: this_array(arr)
		{ }

		array_type(const array& arr)
			: this_array(arr)
		{ }

        // array access (unsafe!)
        inline value_t operator[](size_t i) const
        {
            return this_array.value[i]; 
        }

		inline size_t size() const
		{
			return this_array.size;
		}

		inline bool empty() const
		{
			return 0 == this_array.size
				|| 0 == this_array.value;
		}

		inline bool valid(size_t i)	const
		{
			return i <  this_array.size
				&& 0 != this_array.value;
		}

		template<typename container_t>
		inline container_t& append(container_t& container) const
		{
			return container.append(this_array.value, this_array.value + this_array.size);
		}

		carray this_array;
	};

	//
	// byte_array for fixed data
	typedef array_type<act::byte>::array	byte_array;
	typedef array_type<act::byte>::carray	cbyte_array;
	typedef array_type<act::byte>::pcarray	pcbyte_array;

	//!
	//! \brief Gneralized version of empty_array
	// ---------------------------------------------------------------------------
	template<typename value_t>
	inline bool empty_array(const array_type<value_t>& arr)
	{
		return 0 == arr.this_array.size
			|| 0 == arr.this_array.value;
	}

	template<typename array_t>
	inline bool empty_array(const array_t& arr)
	{
		return 0 == arr.size
			|| 0 == arr.value;
	}

	//!
	//! \brief Gneralized version of index_at_array
	// ---------------------------------------------------------------------------
	template<typename array_t>
	inline bool index_at_array(const array_t& arr, size_t i)
	{
		return i <  arr.size
			&& 0 != arr.value;
	}

	//!
	//! \brief Gneralized version of make_array.
	// ---------------------------------------------------------------------------
	template<typename value_type>
	inline typename array_type<value_type>::array make_array(const value_type* value = 0, size_t size = 0)
	{
		typename array_type<value_type>::array a = { value, size };
		return a;
	}

#	if !defined(ACT_NO_BYTE_ARRAY_MACROS)
#		undef	_A
#		define	_A(x) x.value, x.size
#		undef	_B
#		define	_B(x) act::make_array(reinterpret_cast<const act::byte*>(x), sizeof(x) - sizeof(x[0]))
#		undef	_C
#		define	_C(x) act::make_array(reinterpret_cast<const act::byte*>(x), sizeof(x))
#		undef	_H
#		define	_H(x) { (const act::byte*) x, sizeof(x) - sizeof(x[0]) }
#	endif

#	if(ACT_MSC_VER >= ACT_CPP_VER(13, 0, 0))
	template
	<
		class _Ty,
		class _Diff,
		class _Pointer,
		class _Reference,
		class _Pointer2,
		class _Reference2
	>
	class _Ptrit : 
		public std::iterator<std::random_access_iterator_tag, _Ty, _Diff, _Pointer, _Reference>
	{	// wrap pointer as random-access iterator
	public:
		typedef _Ptrit<_Ty, _Diff, _Pointer, _Reference, _Pointer2, _Reference2> _Myt;

		_Ptrit()
		{	// construct with uninitialized wrapped pointer
		}

		_Ptrit(_Pointer _Ptr) : current(_Ptr)
		{	// construct wrapped pointer from _Ptr
		}

		_Ptrit(const _Ptrit<_Ty, _Diff, _Pointer2, _Reference2, _Pointer2, _Reference2>& _Iter)
			: current(_Iter.base())
		{	// const converter or copy constructor
		}

		inline _Pointer base() const
		{	// return wrapped pointer
			return current;
		}

		inline _Reference operator*() const
		{	// return designated value
			return *current;
		}

		_Pointer operator->() const
		{	// return pointer to class object
			return &**this;
		}

		_Myt& operator++()
		{	// preincrement
			++current;
			return *this;
		}

		_Myt operator++(int)
		{	// postincrement
			_Myt _Tmp = *this;
			++current;
			return _Tmp;
		}

		_Myt& operator--()
		{	// predecrement
			--current;
			return *this;
		}

		_Myt operator--(int)
		{	// postdecrement
			_Myt _Tmp = *this;
			--current;
			return _Tmp;
		}

		bool operator==(size_t _Right) const
		{	// test if wrapped pointer == integer (null pointer constant)
			return current == (_Pointer) _Right;
		}

		bool operator==(const _Myt& _Right) const
		{	// test for iterator equality
			return current == _Right.current;
		}

		bool operator!=(const _Myt& _Right) const
		{	// test for iterator inequality
			return !(*this == _Right);
		}

		_Myt& operator+=(_Diff _Off)
		{	// increment by integer
			current += _Off;
			return *this;
		}

		_Myt operator+(_Diff _Off) const
		{	// return this + integer
			return _Myt(current + _Off);
		}

		_Myt& operator-=(_Diff _Off)
		{	// decrement by integer
			current -= _Off;
			return *this;
		}

		_Myt operator-(_Diff _Off) const
		{	// return this - integer
			return _Myt(current - _Off);
		}

		_Reference operator[](_Diff _Off) const
		{	// subscript
			return *(*this + _Off);
		}

		bool operator<(const _Myt& _Right) const
		{	// test if this < _Right
			return current < _Right.current;
		}

		bool operator>(const _Myt& _Right) const
		{	// test if this > _Right
			return _Right < *this;
		}

		bool operator<=(const _Myt& _Right) const
		{	// test if this <= _Right
			return !(_Right < *this);
		}

		bool operator>=(const _Myt& _Right) const
		{	// test if this >= _Right
			return !(*this < _Right);
		}

		_Diff operator-(const _Myt& _Right) const
		{	// return difference of iterators
			return current - _Right.current;
		}

	protected:
		_Pointer current;	// the wrapped pointer
	};

#	endif // ACT_MSC_VER >= ACT_CPP_VER(13, 0, 0)

	//
	// Blob
	class Blob
	{
	protected:
		struct flags
		{	union
			{	ulong value;
				struct
				{
					ulong external_allocated	: 1;	// bit 0
					ulong null_terminated		: 1;	// bit 1
					ulong copy_on_write			: 1;	// bit 2
					ulong inline_buffer			: 1;	// bit 3
				};
			};
			flags()	: value(0) { }
		};

	public:
		typedef Allocator<byte, size_t>	_Alloc;
		typedef _Alloc					allocator_type;
		typedef _Alloc::size_type		size_type;
		typedef _Alloc::value_type		value_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef const value_type*		const_pointer;
		typedef const value_type&		const_reference;
		typedef ptrdiff_t				difference_type;

#		if(ACT_MSC_VER >= ACT_CPP_VER(13, 0, 0))
			typedef _Ptrit
			<	value_type, difference_type, pointer, reference, pointer, reference
			>	iterator;

			typedef _Ptrit
			<	value_type, difference_type, const_pointer, const_reference, pointer, reference
			>	const_iterator;

			inline static pointer		get_base(iterator it)		{ return it.base(); }
			inline static const_pointer get_base(const_iterator it) { return it.base(); }

#		else
			typedef byte*				iterator;
			typedef const byte*			const_iterator;

			inline static pointer		get_base(iterator it)		{ return it; }
			inline static const_pointer get_base(const_iterator it) { return it; }

#		endif

#		if(ACT_MSC_VER >= ACT_CPP_VER(12, 0, 0) \
		&& ACT_MSC_VER <  ACT_CPP_VER(13, 0, 0))
			typedef std::reverse_iterator
			<	iterator, value_type, reference, pointer, difference_type
			>	reverse_iterator;

			typedef std::reverse_iterator
			<	const_iterator, value_type, const_reference, const_pointer, difference_type
			>	const_reverse_iterator;

#		else
			typedef std::reverse_iterator<iterator>			reverse_iterator;
			typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

#		endif

		// construct/copy/destroy
		Blob();

		explicit Blob(allocator_type* allocator);
		explicit Blob(const char* str, allocator_type* allocator = dAllocator);

#		if !defined(NO_STL_SUPPORT)
			explicit Blob(std::string& str, allocator_type* allocator = dAllocator);
			explicit Blob(const std::string& str, allocator_type* allocator = dAllocator);
#		endif //	NO_STL_SUPPORT

		explicit Blob(const byte_array& ba, allocator_type* allocator = dAllocator);
		explicit Blob(size_type n, byte v = byte(0), allocator_type* allocator = dAllocator);

		template<class inputit>
		Blob(inputit f, inputit l, allocator_type* allocator = dAllocator)
			: mFirst(0), mLast(0), mEnd(0), mAllocator(allocator)
		{
			insert(begin(), f, l);			
		}

		Blob(move_from<Blob> other);
		Blob(const Blob& other);
		~Blob();

		Blob& operator=(const Blob& other);
		Blob& operator=(move_from<Blob> other);
		Blob& operator=(const byte_array& other);

		template<class inputit>
		Blob& assign(inputit f, inputit l)
		{
			erase(begin(), end());
			return insert(begin(), f, l); 
		}

		Blob& assign(const byte_array& ba);
		Blob& assign(size_type n, byte x = byte(0));

		// capacity
		bool			empty() const			{ return size() == 0;						}
		void			fill(byte x)			{ fill(begin(), end(), x);					}
		size_type		size() const			{ return mFirst == 0 ? 0 : mLast - mFirst;	}
		size_type		capacity() const		{ return mFirst == 0 ? 0 : mEnd - mFirst;	}
		size_type		max_size() const;
		void			reserve(size_type n);
		void			resize(size_type n, byte x = byte(0));

		// iterators
		iterator				begin()			{ return mFirst;							}
		const_iterator			begin() const	{ return const_iterator(mFirst);			}
		iterator				end()			{ return mLast;								}
		const_iterator			end() const		{ return const_iterator(mLast);				}
		reverse_iterator		rbegin()		{ return reverse_iterator(end());			}
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end());		}
		reverse_iterator		rend()			{ return reverse_iterator(begin());			}
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin());	}

		// element access
		reference				at(size_type p);
		const_reference			at(size_type p) const;
		inline reference		operator[](size_type p)			{ return *(begin() + p);	}
		inline const_reference	operator[](size_type p) const	{ return *(begin() + p);	}

		inline reference		front()							{ return *(begin());		}
		inline const_reference	front() const					{ return *(begin());		}
		inline reference		back()							{ return *(end() - 1);		}
		inline const_reference	back() const					{ return *(end() - 1);		}

		// modifiers
		inline void				push_back(byte x)				{ insert(end(), x);			}
		inline void				pop_back()						{ erase(end() - 1);			}

		iterator insert(iterator p, byte x = byte(0));
		Blob& insert(iterator p, size_type m, byte x);
		Blob& insert(iterator p, const byte_array& ba);

		template<class inputit>
		Blob& insert(iterator p, inputit f, inputit l)
		{
			size_type m = 0;
			distance(f, l, m);
			if(size_type(mEnd - mLast) < m) 
			{
				size_type n = size();
				n = aligned_size(n + (m < n ? n : m));
				iterator s = allocate(n, (void*) 0);
				iterator q = ucopy(mFirst, p, s);
				q = ucopy(f, l, q);
				ucopy(p, mLast, q);
				destroy(mFirst, mLast);
				deallocate(get_base(mFirst), mEnd - mFirst);
				mEnd = s + n;
				mLast = s + size() + m;
				mFirst = s; 
			}
			else
			{
				check_cow(p);
				if(size_type(mLast - p) < m)
				{
					ucopy(p, mLast, p + m);
					ucopy(f + (mLast - p), l, mLast);
					copy(f, f + (mLast - p), p);
					mLast += m; 
				}
				else if(0 < m) 
				{
					ucopy(mLast - m, mLast, mLast);
					copy_backward(p, mLast - m, mLast);
					copy(f, l, p);
					mLast += m; 
				}
			}
			return *this;
		}

		void clear();
		iterator erase(iterator p);
		iterator erase(iterator f, iterator l);

		void swap(Blob& x);
		static void swap(Blob& first, Blob& second);

		inline move_from<Blob> move() { return act::move(*this); }

		inline allocator_type* get_allocator() const { return mAllocator; }
		static _Alloc* set_default_allocator(_Alloc* allocator);

		static const Blob& get_empty();

		template<class inputit>
		inline Blob& append(inputit f, inputit l)	{ return insert(end(), f, l);				}
		inline Blob& append(size_type m, byte x)	{ return insert(end(), m, x);				}
		inline Blob& append(const byte_array& ba)	{ return insert(end(), ba);					}
		inline Blob& append(const Blob& x)			{ return insert(end(), x.begin(), x.end());	}

		// compare operators
		friend bool  operator<(const Blob& x, const Blob& y)	{ return !(x >= y);				}
		friend bool  operator>(const Blob& x, const Blob& y)	{ return !(x <= y);				}

		friend bool operator==(const Blob& x, const Blob& y)	{ return x._eq(y);				}
		friend bool operator!=(const Blob& x, const Blob& y)	{ return !x._eq(y);				}

		friend bool operator>=(const Blob& x, const Blob& y)	{ return !x._lt(y);				}
		friend bool operator<=(const Blob& x, const Blob& y)	{ return x._eq(y) || x._lt(y);	}

		// other friends
		friend const char*   cstr(const Blob&);
		friend char*         pstr(Blob&);
		friend wchar_t*     wpstr(Blob&);

	protected:
		template<typename target_t>
		static void init(target_t& target, const char* value, bool kConst = true)
		{
			if(0 == value) return;
			const_iterator f(reinterpret_cast<const_pointer>(value));
			const_iterator l(f);
			while(*l) ++l;
			target.init(f, distance(f, l), kConst);
			target.mFlags.null_terminated = true;
		}

#		if !defined(NO_STL_SUPPORT)
		template<typename target_t>
		static void init(target_t& target, const std::string& value, bool kConst = true)
		{
			if(value.empty()) return;
			const_pointer f = reinterpret_cast<const_pointer>(&value[0]);
			target.init(f, value.length(), kConst);
		}
#		endif	// NO_STL_SUPPORT

		template<typename target_t>
		static void init(target_t& target, const byte_array& ba, bool kConst = true)
		{
			if(empty_array(ba) == true) return;
			const_pointer f = reinterpret_cast<const_pointer>(ba.value);
			target.init(f, ba.size, kConst);
		}

		template<typename inputit, typename outputit>
		outputit copy(inputit f, inputit l, outputit x)
		{
			for(; f != l; ++x, ++f)
				*x = *f;
			return x; 
		}

		iterator copy_backward(const_iterator f, const_iterator l, iterator  x);

		template<typename inputit, typename outputit>
		outputit ucopy(inputit f, inputit l, outputit p)
		{
			for(; f != l; ++p, ++f)
				construct(get_base(p), *f);
			return p; 
		}

		void ufill(iterator f, size_type n, byte x);
		void fill(iterator f, const_iterator l, byte x);

		static size_type distance(const_iterator f, const_iterator l);

		template<typename inputit>
		void distance(inputit f, inputit l, size_type& n) const
		{
			for(; f != l; ++f) ++n;
		}

		bool equal(const_iterator f, const_iterator l, const_iterator x) const;
		bool lexicographical_compare(const_iterator f1, const_iterator l1, const_iterator f2, const_iterator l2) const;

		//! \brief used by compare operators
		inline bool _eq(const Blob& other) const
		{
			return size() == other.size() && equal(begin(), end(), other.begin());
		}

		//! \brief used by compare operators
		inline bool _lt(const Blob& other) const
		{
			return lexicographical_compare(begin(), end(), other.begin(), other.end());
		}

		byte* allocate(size_type n, const void* hint);
		void deallocate(pointer p, size_type n);

		void destroy(byte* p);
		void destroy(iterator f, iterator l);
		void construct(byte* p, const_reference v);

		void check_cow(iterator& p);

		void outofrange(const FileAndLine& location) const;

		static size_type aligned_size(size_type size);

	protected:
		flags						mFlags;
		iterator					mFirst, mLast, mEnd;
		allocator_type*				mAllocator;
		static allocator_type*		dAllocator;
	};

	typedef Blob::allocator_type	byte_allocator;

#	ifndef UNDER_CE_30
	std::ostream &operator<<(std::ostream& os, const Blob& blob);
#	endif // UNDER_CE_30

} // namespace act

// --------------------------------------------------------------------------------
namespace std
{
	// ---------------------------------------------------------------------------
	inline void swap(act::Blob& x, act::Blob& y) { x.swap(y); }

} // namespace std

#endif // ACT_Blob_h
