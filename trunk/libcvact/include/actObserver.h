// ---------------------------------------------------------------------------
// Name:      actObserver.h
// Product:   cv act library
// Purpose:   A simple Observer-Pattern impl. used token related objects.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/31/2008
// ---------------------------------------------------------------------------

#ifndef ACT_Observer_h
#define ACT_Observer_h

#include "actIRefCounted.h"

#include "actBlob.h"
#include "actSmartPointer.h"

#include <list>

namespace act
{
	//
	// Observer<>
	template
	<
		class OwnerT,
		class ValueT,
		class InfoT = typename ValueT::InfoType
	>
	class Observer : virtual public IRefCounted
	{
	public:
		typedef OwnerT	Owner;
		typedef ValueT	Value;
		typedef InfoT	Info;

	public:
		virtual void Update(const Owner* owner, const Value& value, Info& info) = 0;
		virtual void Update(const Owner* owner, const Value& value, const Info& info) = 0;
	};

	//
	// Observable<>
	template
	<
		class OwnerT,
		class ValueT,
		class InfoT = typename ValueT::InfoType
	>
	class Observable
	{
	public:
		typedef Observer<OwnerT, ValueT, InfoT> ObserverT;

	protected:
		template<class ValueT_, class InfoT_>
		class func : public std::binary_function<SmartPtr<ObserverT>, bool, void>
		{
		public:
			func(const Observable* owner, ValueT_& value, InfoT_& info)
				: m_owner(static_cast<const OwnerT*>(owner))
				, m_value(value)
				, m_info(info)
			{ }

			void operator()(const SmartPtr<ObserverT>& observer, bool) const
			{
				ACT_ASSERT(observer != 0);
				if(observer != 0) observer->Update(m_owner, m_value, m_info);
			}

		protected:
			ValueT_&		m_value;
			InfoT_&			m_info;
			const OwnerT*	m_owner;
		};

	protected:
		virtual ~Observable()
		{
			m_observers.clear(); 
		}

		virtual void Notify(const ValueT& value, InfoT& info) const
		{
			if(m_observers.empty() == false)
				std::for_each(m_observers.begin(), m_observers.end(),
					std::bind2nd(func<const ValueT, InfoT>(this, value, info), false));
		}

		virtual void Notify(const ValueT& value, const InfoT& info) const
		{
			if(m_observers.empty() == false)
				std::for_each(m_observers.begin(), m_observers.end(),
					std::bind2nd(func<const ValueT, const InfoT>(this, value, info), false));
		}

		virtual bool Register(ObserverT* observer)
		{
			if(isRegistered(observer))
				return false;

			m_observers.push_back(observer);
			return true;
		}

		virtual bool UnRegister(ObserverT* observer)
		{
			if(isRegistered(observer) == false)
				return false;
			
			m_observers.remove(observer);
			return true;
		}

		bool isRegistered(ObserverT* observer) const
		{
			return std::find(m_observers.begin(), m_observers.end(), observer) != m_observers.end();
		}

	private:
		std::list<SmartPtr<ObserverT> > m_observers;

	private:
		template<class OwnerT_, class ValueT_, class InfoT_, class ObserverT_>
		friend class ObserverIterator;

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend bool Register(Observable<OwnerT_, ValueT_, InfoT_>*, Observer<OwnerT_, ValueT_, InfoT_>*);

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend bool UnRegister(Observable<OwnerT_, ValueT_, InfoT_>*, Observer<OwnerT_, ValueT_, InfoT_>*);

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend void Notify(const Observable<OwnerT_, ValueT_, InfoT_>*, const ValueT_&, InfoT_&);

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend void Notify(const Observable<OwnerT_, ValueT_, InfoT_>*, const ValueT_&, const InfoT_&);

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend bool HasObserver(const Observable<OwnerT_, ValueT_, InfoT_>*);

		template<class ValueT_, class InfoT_, class OwnerT_>
		friend bool IsRegistered(const Observable<OwnerT_, ValueT_, InfoT_>*, Observer<OwnerT_, ValueT_, InfoT_>*);
	};

	//
	// SyncronizedObservable<>
	template
	<
		class OwnerT,
		class ValueT,
		class InfoT,
		class LockT	/* GuardT<SyncObject> */
	>
	class SyncronizedObservable : public Observable<OwnerT, ValueT, InfoT>
	{
	protected:
		typedef Observable<OwnerT, ValueT, InfoT>	BaseT;
		typedef typename BaseT::ObserverT			ObserverT;

	protected:
		virtual typename LockT::SyncObject& GetSyncObjRef() const = 0;

		// Observable<> methods
		virtual void Notify(const ValueT& value, InfoT& info) const
		{
			LockT lock(GetSyncObjRef());
			BaseT::Notify(value, info);
		}

		virtual void Notify(const ValueT& value, const InfoT& info) const
		{
			LockT lock(GetSyncObjRef());
			BaseT::Notify(value, info);
		}

		virtual bool Register(ObserverT* observer)
		{
			LockT lock(GetSyncObjRef());
			return BaseT::Register(observer);
		}

		virtual bool UnRegister(ObserverT* observer)
		{
			LockT lock(GetSyncObjRef());
			return BaseT::UnRegister(observer);
		}
	};

	//
	// IsRegistered<>
	template<class ValueT, class InfoT, class OwnerT>
	bool IsRegistered(const Observable<OwnerT, ValueT, InfoT>* subject, Observer<OwnerT, ValueT, InfoT>* observer)
	{
		return subject != 0 ? subject->isRegistered(observer) : false;
	}

	//
	// Register<>
	template<class ValueT, class InfoT, class OwnerT>
	bool Register(Observable<OwnerT, ValueT, InfoT>* subject, Observer<OwnerT, ValueT, InfoT>* observer)
	{
		return subject != 0 ? subject->Register(observer) : false;
	}

	template<class OwnerT>
	struct RegisterFun
	{
		OwnerT* m_owner;

		RegisterFun(OwnerT* owner)
			: m_owner(owner)
		{ }

		template<class ValueT, class InfoT>
		inline void operator()(Observer<OwnerT, ValueT, InfoT>* observer) const
		{
			if(0 == observer)
				return;

			Observable<OwnerT, ValueT, InfoT>* subject = 
				static_cast<Observable<OwnerT, ValueT, InfoT>*>(m_owner);

			act::Register<ValueT>(subject, observer);
			ACT_ASSERT(act::IsRegistered<ValueT>(subject, observer));
		}
	};

	template<class OwnerT>
	inline RegisterFun<OwnerT> Register(OwnerT* subject)
	{
		return subject;
	}

	//
	// UnRegister<>
	template<class ValueT, class InfoT, class OwnerT>
	bool UnRegister(Observable<OwnerT, ValueT, InfoT>* subject, Observer<OwnerT, ValueT, InfoT>* observer)
	{
		return subject != 0 ? subject->UnRegister(observer) : false;
	}

	//
	// Notify<>
	template<class ValueT, class InfoT, class OwnerT>
	void Notify(const Observable<OwnerT, ValueT, InfoT>* subject, const ValueT& value, InfoT& info)
	{
		if(subject != 0) subject->Notify(value, info);
	}

	template<class ValueT, class InfoT, class OwnerT>
	void Notify(const Observable<OwnerT, ValueT, InfoT>* subject, const ValueT& value, const InfoT& info)
	{
		if(subject != 0) subject->Notify(value, info);
	}

	//
	// HasObserver<>
	template<class ValueT, class InfoT, class OwnerT>
	bool HasObserver(const Observable<OwnerT, ValueT, InfoT>* subject)
	{
		return subject != 0 ? subject->m_observers.empty() == false : false;
	}

	//
	// ObserverIterator<>
	template
	<
		class OwnerT,
		class ValueT,
		class InfoT,
		class ObserverT_ = typename Observable<OwnerT, ValueT, InfoT>::ObserverT
	>
	class ObserverIterator
	{
	public:
		typedef ObserverT_														ObserverT;
		typedef Observable<OwnerT, ValueT, InfoT>								ObservableT;
		typedef SmartPtr<typename Observable<OwnerT, ValueT, InfoT>::ObserverT>	ObserverPtrT;

	private:
		ObserverIterator(const ObserverIterator&) throw();
		ObserverIterator& operator=(const ObserverIterator&) throw();

	public:
		ObserverIterator()
		{ }

		ObserverIterator(ObservableT* subject)
			: m_subject(static_cast<OwnerT*>(subject))
		{
			if(subject != 0) Reset();
		}

		ObserverIterator(move_from<ObserverIterator> other)
			: m_current(other.source.m_current)
		{
			m_subject.swap(other.source.m_subject);
		}

		void swap(ObserverIterator& other)
		{
			m_subject.swap(other.m_subject);
			std::swap(m_current, other.m_current);
		}

		void Reset()
		{
			ObservableT* subject = getPointer(m_subject);
			if(subject != 0) m_current = subject->m_observers.begin();
		}

		ObserverT* Next()
		{
			ObserverT* observer = 0;
			ObservableT* subject = getPointer(m_subject);
			if(subject != 0 && subject->m_observers.end() != m_current)
			{
				observer = static_cast<ObserverT*>(getPointer(static_cast<ObserverPtrT&>(*m_current)));
				++m_current;
			}
			return observer;
		}

	private:
		SmartPtr<OwnerT> m_subject;
		typename std::list<ObserverPtrT>::iterator m_current;
	};

	//
	// GetIterator<>
	template<class OwnerT, class ValueT, class InfoT>
	ObserverIterator<OwnerT, ValueT, InfoT> GetIterator(Observable<OwnerT, ValueT, InfoT>* subject)
	{
		ACT_ASSERT(0 != subject);
		ObserverIterator<OwnerT, ValueT, InfoT> iterator(subject);
		return move(iterator);
	}

	//
	// ObserverTraits<>
	template<class ObserverT>
	class ObserverTraits
	{
	public:
		typedef typename ObserverT::Owner						Owner;
		typedef typename ObserverT::Value						Value;
		typedef typename ObserverT::Info						Info;
		typedef ObserverIterator<Owner, Value, Info, ObserverT>	ObserverIteratorT;
		typedef typename ObserverIteratorT::ObservableT			ObservableT;

		struct Observable
		{
			Observable(ObservableT* subject) : _iterator(subject) { }
			ObserverIteratorT* operator->() { return &_iterator; }
			ObserverIteratorT _iterator;
		};
	};

	//
	// UnRegisterAll
	template<class ValueT, class InfoT, class OwnerT>
	void UnRegisterAll(Observable<OwnerT, ValueT, InfoT>* subject)
	{
		ObserverIterator<OwnerT, ValueT, InfoT> iterator;
		act::GetIterator(subject).swap(iterator);

		Observer<OwnerT, ValueT, InfoT>* observer;
		while((observer = iterator.Next()) != 0)
			act::UnRegister(subject, observer);
	}

} // namespace act

#endif // ACT_Observer_h
