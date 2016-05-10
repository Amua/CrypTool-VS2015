// ---------------------------------------------------------------------------
// Name:      actSmartPointer.h
// Product:   cv act library
// Purpose:   Generic SmartPointer templates and types.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  1/18/2006
// ---------------------------------------------------------------------------

#ifndef ACT_SmartPointer_h
#define ACT_SmartPointer_h

#include "actEnv.h"
#include "actMove.h"
#include "actDebug.h"
#include "actBasics.h"
#include "actTypeTags.h"
#include "actException.h"

#include "actReference.h"
#include "actRefMethods.h"

#include <algorithm>

namespace act 
{
	//
	// RefCounterBase<>,
	// Reference counting base impl.
	template
	<
		typename   TypeT,
		const long RefCount,
		typename   RefCountT = volatile long
	>
	class RefCounterBase : public TypeT
	{
	public:
		RefCounterBase() : m_refcount(RefCount)
		{ }

	protected:
		~RefCounterBase()
		{
			ACT_ASSERT(0 == m_refcount);
		}

		virtual void destruct()
		{
			::delete this;
		}

	private:
		friend const RefCountT& getRefCount(RefCounterBase<TypeT, RefCount, RefCountT>* pT)
		{
			if(pT == 0) throw NullPointerException();
			return pT->m_refcount;
		}

	protected:
		RefCountT m_refcount;
	};

	//
	// TypedRefCounterImpl<>
	// Overwrites the destruct method. 
	// Performs an up cast to TypeT before delete gets called.
	template
	<
		typename ConcreteT,
		class	 RefCounterImplT /* f.e. AtomicRefCounter<TypeT, RefValue> */
	>
	class TypedRefCounterImpl : public RefCounterImplT
	{
	protected:
		virtual void destruct()
		{
			ConcreteT* pT = static_cast<ConcreteT*>(this);
			delete pT;
		}
	};

	//
	// act::refmethods
	// Holds addRef and release methods for different reference counted types.
	// NOTE: See SecureToken/ReferenceCounter.h for a sample extension !
	namespace refmethods
	{
		inline void addRef(Reference& pT)  { pT.add(); }
		inline void release(Reference& pT) { if(pT.remove() == 0) delete &pT; }

	} // namespace refmethods


	//
	// SmartPointer reference behavior templates.
	//
	// SPNoRefBehaviorImpl<> : Does simply nothing.
	// SPRefBehaviorImpl<>	 : redirects addRef / release to corresponding refmethods:: methods.
	//

	//
	// SPNoRefBehaviorImpl<>
	template<typename TypeT>
	class SPNoRefBehaviorImpl
	{
	protected:
		typedef /*typename*/ TypeT Type;

	protected:
		TypeT* addRef(TypeT* pT) { return pT; }
		void   release(TypeT*)	 { }
	};

	//
	// SPRefBehaviorImpl<>
	template<typename TypeT>
	class SPRefBehaviorImpl
	{
	protected:
		typedef /*typename*/ TypeT Type;

	protected:
		TypeT* addRef(TypeT* pT)
		{
			if(pT != 0) refmethods::addRef(*pT);
			return pT;
		}

		void release(TypeT* pT)
		{
			if(pT != 0) refmethods::release(*pT);
		}
	};


	//
	// SmartPointer storage templates.
	//
	// SPStorageImpl<>		: The default storage type, holds a pointer of TypeT.
	// SPSmartStorageImpl<>	: This storage calls release on destruction, derived from SPStorageImpl<>
	//
	// NOTE: Every storage impl. needs to declare these 2 friend accessor methods:
	// {
	//	   friend Type*& getPointerRef(StorageType& storage)
	//     friend Type*  getPointer(const StorageType& storage)
	// }

	//
	// SPStorageImpl<>
	// The default (non array) SmartPointer-Storage.
	template
	<
		class RefBehaviorT	/* for example: SPRefBehaviorImpl<TypeT>	*/
	>
	class SPStorageImpl : public RefBehaviorT
	{
	protected:
		typedef typename		RefBehaviorT::Type			Type;
		typedef /*typename*/	RefBehaviorT				RefBehavior;
		typedef /*typename*/	SPStorageImpl<RefBehaviorT>	StorageType;

	// TODO: Change to private!
	protected:
		Type* m_pT;

	protected:
		SPStorageImpl(Type* pT = 0) : m_pT(pT)
		{ }

	public:
		Type* attach(Type* pT)
		{
			RefBehavior::release(m_pT);
			m_pT = pT;
			return pT;
		}

		Type* detach()
		{
			Type* pT = m_pT;
			m_pT = 0;
			return pT;
		}

		void swap(Type*& other)
		{
			std::swap(m_pT, other);
		}

		template<typename OtherRefBehaviorT>
		void swap(SPStorageImpl<OtherRefBehaviorT>& other)
		{
			std::swap(m_pT, getPointerRef(other));
		}

		//
		// friend storage accessor methods.
		friend Type* getPointer(const StorageType& storage)
		{
			return storage.m_pT;
		}

		friend Type*& getPointerRef(StorageType& storage)
		{
			return storage.m_pT;
		}
	};

	//
	// SPSmartStorageImpl<>
	// Calls release on destruction.
	template<class RefBehaviorT>
	class SPSmartStorageImpl : public SPStorageImpl<RefBehaviorT>
	{
	protected:
		typedef typename		RefBehaviorT::Type					Type;
		typedef /*typename*/	SPSmartStorageImpl<RefBehaviorT>	StorageType;
		typedef /*typename*/	RefBehaviorT						RefBehavior;

	protected:
		SPSmartStorageImpl(Type* pT = 0) : SPStorageImpl<RefBehaviorT>(pT)
		{ }

	public:
		~SPSmartStorageImpl()
		{
			RefBehavior::release(SPStorageImpl<RefBehaviorT>::detach());
		}
	};

	//
	// SmartPointer storage behavior templates.
	//
	// SPCompareableImpl<>	: Makes the storage comparable using != and ==.
	//

	//
	// SPCompareableImpl
	template<class StorageT>
	class SPCompareableImpl : public StorageT
	{
	protected:
		typedef typename	StorageT::Type				Type;
		typedef typename	StorageT::RefBehavior		RefBehavior;
		typedef				SPCompareableImpl<StorageT>	StorageType;

	protected:
		SPCompareableImpl(Type* pT = 0) : StorageT(pT)
		{ }

	public:
		bool operator==(const Type* p_other) const
		{
			return StorageT::m_pT == p_other;
		}

		template<typename RefBehaviorT>
		bool operator==(const SPStorageImpl<RefBehaviorT>& other) const
		{
			return StorageT::m_pT == getPointer(other);
		}

		bool operator!=(const Type* p_other) const
		{
			return StorageT::m_pT != p_other;
		}

		template<typename RefBehaviorT>
		bool operator!=(const SPStorageImpl<RefBehaviorT>& other) const
		{
			return StorageT::m_pT != getPointer(other);
		}
	};

	//
	// SmartPointer accessor policy templates.
	// NOTE: Accessor policies should only use SPNoRefBehaviorImpl<> !
	//
	// SPPolBaseImpl<>		  : Baseclass of all policy types, derived from SPStorageImpl<>.
	// SPPolAssertIfNull<>	  : Uses ACT_ASSERT on construction for pointer of TypeT in DEBUG build.
	// SPPolExceptionIfNull<> : Throws act::NullPointerException on construction for pointer of TypeT.
	//

	//
	// SPPolBaseImpl<>
	// Baseclass of a SmartPointer-Policy.
	template<typename TypeT>
	class SPPolBaseImpl : public SPStorageImpl<SPNoRefBehaviorImpl<TypeT> >
	{
	private:
		// SPPolBaseImpl(const SPPolBaseImpl&);
		SPPolBaseImpl& operator=(const SPPolBaseImpl&);

	protected:
		typedef TypeT Type;

	public:
		explicit SPPolBaseImpl(TypeT* pT) 
			: SPStorageImpl<SPNoRefBehaviorImpl<TypeT> >(pT)
		{
			ACT_ASSERT(pT != 0);
		}

		SPPolBaseImpl(const SPPolBaseImpl& other)
			: SPStorageImpl<SPNoRefBehaviorImpl<TypeT> >(getPointer(other))
		{
			ACT_ASSERT(getPointer(*this) != 0);
		}

		operator		TypeT*()     const	{ return  getPointer(*this); }
		operator		TypeT&()     const	{ return *getPointer(*this); }
		TypeT*			operator->() const	{ return  getPointer(*this); }
		const TypeT&	operator*()  const	{ return *getPointer(*this); }
		TypeT&			operator*()			{ return *getPointer(*this); }
		operator		const TypeT&()		{ return *getPointer(*this); }
	};

	//
	// SPPolAssertIfNull<>
	template<typename TypeT>
	struct SPPolAssertIfNull
	{
		template<typename OtherT>
		struct Rebind
		{
			typedef SPPolBaseImpl<OtherT> AccessorType;
		};

		typedef SPPolBaseImpl<TypeT> AccessorType;
	};

	//
	// SPPolExceptionIfNull<>
	template<typename TypeT>
	struct SPPolExceptionIfNull
	{
		template<typename TypeU>
		class AccessorImpl : public SPPolBaseImpl<TypeU>
		{
		public:
			explicit AccessorImpl(TypeU* pT) : SPPolBaseImpl<TypeU>(pT)
			{
				if(pT == 0) throw NullPointerException();
			}

			AccessorImpl(TypeU* pT, const Location<>& location) : SPPolBaseImpl<TypeU>(pT)
			{
				if(pT == 0) throw NullPointerException() << location;
			}
		};

		template<typename OtherT>
		struct Rebind
		{
			typedef AccessorImpl<OtherT> AccessorType;
		};

		typedef AccessorImpl<TypeT> AccessorType;
	};


	//
	// SmartPointer templates.
	//
	// PointerRef<>	: Use to enable automatic attach / detach between SmartPtr<>.
	// SmartPtr<>	: The default reference counting SmartPointer impl.
	//

	//
	// PointerRef<> impl. 
	// NOTE: Supports no copy-assignment/-construction by design !
	template
	<
		typename TypeT,
		class	 StorageT = SPCompareableImpl<SPSmartStorageImpl<SPRefBehaviorImpl<TypeT> > >
	>
	class PointerRef : public StorageT
	{
	protected:
		typedef /*typename*/	TypeT					Type;
		typedef typename		StorageT::RefBehavior	RefBehavior;
		typedef typename		StorageT::StorageType	StorageType;

	private:
		PointerRef(const PointerRef&);
		PointerRef& operator=(const PointerRef&);

	public:
		PointerRef(TypeT* pT)
			: StorageT(RefBehavior::addRef(pT))
		{ }

		PointerRef(StorageType& other)
			: StorageT(other.detach())
		{ }
	};

	//
	// SmartPtr<> impl. 
	template
	<
		typename TypeT, 
		class	 PolicyT  = SPPolExceptionIfNull<TypeT>, /* SPPolAssertIfNull<TypeT> */
		class	 StorageT = SPCompareableImpl<SPSmartStorageImpl<SPRefBehaviorImpl<TypeT> > >
	>
	class SmartPtr : public StorageT
	{
	private:
		typedef /*typename*/	StorageT					Storage;

	protected:
		typedef /*typename*/	TypeT						Type;
		typedef typename		StorageT::RefBehavior		RefBehavior;
		typedef typename		StorageT::StorageType		StorageType;
		typedef typename		PolicyT::AccessorType		AccessorType;

	public:
		SmartPtr()
		{ }

		SmartPtr(TypeT* pT)
			: Storage(RefBehavior::addRef(pT))
		{ }

		SmartPtr(move_from<TypeT, TagPtrRef> other)
			: Storage(other.source())
		{ }

		// construct by consuming pointer from PointerRef<>
		SmartPtr(PointerRef<TypeT, StorageT>& other)
			: Storage(other.detach())
		{ }

		template<class OtherPolicyT, class OtherStorageT>
		SmartPtr(move_from<SmartPtr<TypeT, OtherPolicyT, OtherStorageT> > other)
			: Storage(other.source().detach())
		{ }

		// construct by accessing pointer from other, compatible SmartPtr<>
		template<typename OtherT, class OtherPolicyT, class OtherStorageT>
		SmartPtr(const SmartPtr<OtherT, OtherPolicyT, OtherStorageT>& other) 
			: Storage(RefBehavior::addRef(getPointer(other)))
		{ }

		// copyctor by accessing pointer from other SmartPtr<>
		SmartPtr(const SmartPtr<TypeT, PolicyT, StorageT>& other) 
			: Storage(RefBehavior::addRef(getPointer(other)))
		{ }


		// assign a raw pointer of TypeT.
		SmartPtr& operator=(TypeT* pT)
		{
			StorageType::attach(RefBehavior::addRef(pT));
			return *this;
		}

		// assign by assuming pointer from PointerRef<>
		SmartPtr& operator=(PointerRef<TypeT, StorageT>& other)
		{
			StorageType::attach(other.detach());
			return *this;
		}

		// assign by accessing pointer from other, compatible SmartPtr<>
		template<typename OtherT, class OtherPolicyT, class OtherStorageT>
		SmartPtr& operator=(const SmartPtr<OtherT, OtherPolicyT, OtherStorageT>& other)
		{
			StorageType::attach(RefBehavior::addRef(getPointer(other)));
			return *this;
		}

		ACT_EMPTY_TEMPLATE
		SmartPtr& operator=(const SmartPtr<TypeT, PolicyT, StorageT>& other)
		{
			StorageType::attach(RefBehavior::addRef(getPointer(other)));
			return *this;
		}

		//
		// accessor methods.
		AccessorType	operator*() const	{ return AccessorType(StorageT::m_pT);		}
		AccessorType	operator->() const	{ return AccessorType(StorageT::m_pT);		}

		TypeT* get() const					{ return getPointer(*this);					}
		move_from<TypeT, TagPtrRef> move()	{ return act::move_ptr_ref(StorageT::m_pT);	}

		//
		// as<> - dynamicly cast to OtherT and get rebound accessor
		template<typename OtherT>
		typename PolicyT::template Rebind<OtherT>::AccessorType as() const
		{
			OtherT* other = dynamic_cast<OtherT*>(StorageT::m_pT);
			return typename PolicyT::template Rebind<OtherT>::AccessorType(other);
		}

		//
		// friend methods.
		friend PointerRef<TypeT, StorageT> swap(StorageType& storage)
		{
			return storage;
		}
	};

	//
	// RefPtr<>
	// ---------------------------------------------------------------------------
	template
	<
		typename TypeT,
		typename BaseT
	>
	class RefPtr : public BaseT
	{
	private:
		RefPtr(const RefPtr&);
		RefPtr& operator=(const RefPtr&);

	public:
		RefPtr(TypeT* pT) : m_pT(pT)	{ ACT_ASSERT(pT != 0);	}
		~RefPtr()						{ delete m_pT;			}

		const TypeT* operator&() const	{ return m_pT;			}

		TypeT& operator*() const
		{
			if(m_pT != 0) return *m_pT;
			throw NullPointerException() << ACT_DEBUG_SOURCE();
		}

		TypeT* operator->() const
		{
			if(m_pT != 0) return m_pT;
			throw NullPointerException() << ACT_DEBUG_SOURCE();
		}

	private:
		TypeT* m_pT;
	};

	//!
	//! \brief Type specific 0-pointer.
	// ---------------------------------------------------------------------------
	template<class TypeT>
	inline TypeT* null_ptr() { return 0; }

	//!
	//! \brief make_ptr<>
	// ---------------------------------------------------------------------------
	template<typename TypeT>
	inline SmartPtr<TypeT> make_ptr(TypeT* pointer)
	{
		return SmartPtr<TypeT>(pointer).move();
	}

	//!
	//! \brief check_ptr<>
	// ---------------------------------------------------------------------------
	template<class TypeT>
	inline typename SPPolExceptionIfNull<TypeT>::AccessorType check_ptr(TypeT* const ptr)
	{
		ACT_ASSERT(ptr != 0);
		return typename SPPolExceptionIfNull<TypeT>::AccessorType(ptr);
	}

	//!
	//! \brief cast_ptr<>
	// ---------------------------------------------------------------------------
	template<class DestT, class TypeT>
	inline typename SPPolExceptionIfNull<DestT>::AccessorType cast_ptr(TypeT* ptr)
	{
		ACT_ASSERT(dynamic_cast<DestT*>(ptr) != 0);
		return typename SPPolExceptionIfNull<DestT>::AccessorType(dynamic_cast<DestT*>(ptr));
	}

	//!
	//! \brief scoped_delete<SmartPtrT>
	// ---------------------------------------------------------------------------
	template<class TypeT, class PolicyT, class StorageT>
	struct scoped_delete<SmartPtr<TypeT, PolicyT, StorageT>, void, TypeTag<TypeT> >
	{
		SmartPtr<TypeT, PolicyT, StorageT> ptr;

		explicit scoped_delete(SmartPtr<TypeT, PolicyT, StorageT>& ptr_ref) { ptr.swap(ptr_ref); }
		explicit scoped_delete(TypeT* p) { ptr.attach(p); }
		~scoped_delete() { ptr = 0; }

		TypeT* operator->() const { return (*ptr).operator->(); }
	};

	//!
	//! \brief checked_delete
	// ---------------------------------------------------------------------------
	template<class TypeT, class PolicyT, class StorageT>
	scoped_delete< SmartPtr<TypeT, PolicyT, StorageT>, void, TypeTag<TypeT> >
	checked_delete(SmartPtr<TypeT, PolicyT, StorageT>& ptr_ref)
	{
		return scoped_delete<SmartPtr<TypeT, PolicyT, StorageT>, void, TypeTag<TypeT> >(ptr_ref);
	}

} // namespace act

#endif	// ACT_SmartPointer_h
