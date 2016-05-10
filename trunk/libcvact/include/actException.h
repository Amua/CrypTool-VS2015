//////////////////////////////////////////////////////////////////////////////////
// Name:      actException.h
// Product:   cv act library
// Purpose:   exception hierarchy
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Exception_h
#define ACT_Exception_h

#include <new>
#include <exception>

#include "actMove.h"
#include "actBlob.h"
#include "actLocation.h"

namespace act
{
	class Exception;

	// ---------------------------------------------------------------------------
	enum ExceptionId
	{
		eiException												= 0,
			eiBadException										= eiException + 1,
				eiNullPointerException,
				eiOutOfRangeException,
					eiLeftOfRangeException,
					eiRightOfRangeException,

			eiBadCastException									= eiException + 10,
				eiBadNumericCast,
					eiNegativeOverflow,
					eiPositiveOverflow,

			eiRuntimeException									= eiException + 20,
				eiBadAllocException,
				eiOutOfMemoryException							= eiBadAllocException,
				eiNotSupportedException,
				eiNotImplementedException,
				eiNotInitializedException,
				eiFailedToInitializeException,
				eiAlreadyInitializedException,
				eiInvalidParameterException,
				eiInvalidSessionIdException,
				eiSynchronizationException,
				eiShutdownException,

			eiLogicalException									= eiException + 40,
				eiASN1Exception,
					eiIncompatibleVersionException,
				eiFileNotFoundException,
					eiNoSuchDLLException,
				eiNoSuchMethodException,
				eiPasswordException,
				eiArithmeticException,
				eiMessageDigestException,
				eiPaddingException,
				eiSignatureException,

				eiAlgorithmException							= eiException + 80,
					eiInvalidAlgorithmParameterException,
					eiIncompatibleAlgorithmException,
					eiNoSuchAlgorithmException,

				eiCertificateException							= eiException + 90,
					eiInvalidCertificateException,
					eiCertificateEncodingException,
					eiCertificateExpiredException,
					eiCertificateNotYetValidException,
					eiCertificateParsingException,

				eiKeyException									= eiException + 100,
					eiInvalidKeyParameterException,
					eiInvalidKeyException,
					eiKeyManagementException,

				eiEACException									= eiException + 120,
					eiEACDataException,
						eiEACMRZException,
						eiEACCVCertException,

				eiSmartcardException							= eiException + 140,
					eiCardRemovedException,
					eiCardOutOfMemoryException,
					eiCardTransactionException,
					eiPinException,
						eiPinEntryException,
						eiPinChangeException,
						eiPinModifyException					= eiPinChangeException,
						eiPinLockedException,
						eiPinExpiredException,
						eiPinLenRangeException,
						eiInvalidPinException,
						eiPinVerifyException					= eiInvalidPinException,
						eiInvalidPinFormatException,
					eiInvalidCRKeyException,
					eiInvalidCardException,
					eiInvalidAuthException,
					eiInvalidAuthObjectException,
					eiInvalidAuthConstraints,
					eiAuthProtocolException,
					eiConstraintsViolationException,
						eiAuthConstraintsViolation,
						eiTokenFileConstraintsViolation,
					eiSecureMessagingException,
						eiSMWrapException,
						eiSMUnwrapException,
						eiSMInvalidException,
				
				eiSubsystemException							= eiException + 180,
					eiNoSuchSubsystemException,
	};

#ifndef UNDER_CE_30

	// --------------------------------------------------------------------------
	namespace exception
	{
		namespace detail
		{
			template<const int index, typename ValueT = void>
			class modifier;
		}

		template<class U, bool valid = is_base_of<Exception, U>::value>
		struct convert;

		template<class U>
		struct convert<U, true>
		{
			explicit convert(const U& ref)
				: source(ref)
			{ }

			template<class V>
			V& operator()(V& dest) const
			{
				dest.code(source.code());
				dest.what(source.what());
				dest.where(source.where());
				return dest;
			}

			template<class V>
			V* operator()(V* dest) const
			{
				return 0 != dest ? &((*this)(*dest)) : 0;
			}

			const U& source;
		};

		template<class U>
		struct convert<U, false>
		{
			explicit convert(const U&)
			{ }

			template<class V>
			inline V& operator()(V& dest) const { return dest; }
		};

		template<typename T>
		struct convert<Location<T>, false>
		{
			explicit convert(const Location<T>& ref)
				: location(ref)
			{ }

			template<class V>
			inline V& operator()(V& dest) const
			{
				dest.where(location);
				return dest;
			}

			const Location<T>& location;
		};

		template<typename V, typename U>
		inline V* clone(const U& source)
		{
			return new V(*static_cast<const V*>(&source));
		}

		template<typename V, typename U, typename ParamT>
		inline V* clone(const U& source, const ParamT& param)
		{
			V* v = clone<V>(source);
			if(v != 0) *v << param;
			return v;
		}

	} // namespace exception

	//!
	//! \brief   Exception
	//! \details Base class for all exceptions thrown by cv act library
	// ---------------------------------------------------------------------------
	class Exception
	{
	public:
		typedef Exception Type;

		virtual ~Exception() { }

		explicit Exception(const char* msg = 0, const char* where = 0, ulong code = 0)
			: m_what(msg)
			, m_where(where)
			, m_code(code)
		{ }

		explicit Exception(const std::exception& other)
			: m_what(other.what())
			, m_where(0)
			, m_code(0)
		{ }

		// create modifier for Type.
		template<const int index>
		exception::detail::modifier<index, Type>
		operator<<(const exception::detail::modifier<index, void>& modifier_for)
		{
			return modifier_for(*this);
		}

		// handle exception modifier containiing derived or equal exceptions T.
		template<const int index, typename T>
		Type& operator<<(const exception::detail::modifier<index, T>& other)
		{
			return other << *this;
		}

		template<typename T>
		Type& operator<<(const T& other)
		{
			return exception::convert<T>(other)(*this);
		}

		template<typename OtherT, typename ParamT>
		inline void TypedThrow(const ParamT& param) const
		{
			throw OtherT(m_what, m_where, param);
		}

		template<typename OtherT>
		inline void TypedThrow() const
		{
			throw OtherT() << *this;
		}

		virtual Type* Clone() const;
		virtual void  Throw() const;
		virtual int	  GetId() const;

		const char*   what() const;				
		void		  what(const char* what)	{ m_what = what;	}

		const char*   where() const				{ return m_where != 0 ? m_where : ""; }
		void		  where(const char* where)	{ m_where = where;	}

		ulong		  code() const				{ return m_code;	}
		void		  code(ulong code)			{ m_code = code;	}

	protected:
		const char* m_what;
		const char* m_where;
		ulong		m_code;
	};

	//!
	//! \brief ExceptionType<>
	// ---------------------------------------------------------------------------
	template
	<
		int   exceptionId_,
		class ExceptionT,
		class BaseT,
		class OtherT = void
	>
	class ExceptionType : public BaseT, public OtherT
	{
	public:
		typedef ExceptionType
				<	exceptionId_,
					ExceptionT,
					BaseT,
					OtherT>	ThisType;
		typedef OtherT		OtherType;
		typedef BaseT		BaseType;
		typedef ExceptionT	Type;
		enum  { exceptionId = exceptionId_ };

	public:
		ExceptionType()
			: BaseType()
			, OtherT()
		{ }

		ExceptionType(const char* msg, const char* where, ulong code)
			: BaseType(msg, where, code)
			, OtherT()
		{ }

		// assign from other exceptions
		template<typename T>
		Type& operator<<(const T& other)
		{
			return exception::convert<T>(other)(*static_cast<Type*>(this));
		}

		// create modifier for Type.
		template<const int index>
		exception::detail::modifier<index, Type>
		operator<<(const exception::detail::modifier<index, void>& modifier_for)
		{
			return modifier_for(*static_cast<Type*>(this));
		}

		// handle exception modifier containiing derived or equal exceptions T.
		template<const int index, typename U, typename V>
		Type& operator<<(const exception::detail::modifier<index, U>& other)
		{
			return other << *this;
		}

		virtual void       Throw() const { throw  Type() << *this;				}
		virtual int	       GetId() const { return exceptionId;					}
		virtual ThisType*  Clone() const { return exception::clone<Type>(*static_cast<const Type*>(this)); }
	};

	template
	<
		int   exceptionId_,
		class ExceptionT,
		class BaseT
	>
	class ExceptionType<exceptionId_, ExceptionT, BaseT, void>
		: public BaseT
	{
	public:
		typedef ExceptionType
					<	exceptionId_, ExceptionT, BaseT, void
					>		ThisType;
		typedef BaseT		BaseType;
		typedef ExceptionT	Type;
		enum  { exceptionId = exceptionId_ };

	public:
		ExceptionType()
			: BaseType()
		{ }

		ExceptionType(const char* msg, const char* where, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		// assign from other exceptions
		template<typename T>
		Type& operator<<(const T& other)
		{
			return exception::convert<T>(other)(*static_cast<Type*>(this));
		}

		// create modifier for Type.
		template<const int index>
		exception::detail::modifier<index, Type>
		operator<<(const exception::detail::modifier<index, void>& modifier_for)
		{
			return modifier_for(*static_cast<Type*>(this));
		}

		// handle exception modifier containiing derived or equal exceptions T.
		template<const int index, typename T>
		Type& operator<<(const exception::detail::modifier<index, T>& other)
		{
			return other << *static_cast<Type*>(this);
		}

		template<typename OtherT>
		inline  void  TypedThrow() const { throw  OtherT() << *this;			}
		virtual void       Throw() const { throw  Type() << *this;				}
		virtual int        GetId() const { return exceptionId;					}
		virtual ThisType*  Clone() const { return exception::clone<Type>(*static_cast<const Type*>(this)); }
	};

	// ---------------------------------------------------------------------------
#	define ExceptionImpl(ExceptionT, BaseT)           ExceptionType<ei##ExceptionT, ExceptionT, BaseT>
#	define ExceptionExImpl(ExceptionT, BaseT, OtherT) ExceptionType<ei##ExceptionT, ExceptionT, BaseT, OtherT>

	//!
	//! \brief BadException
	// ---------------------------------------------------------------------------
	class BadException
		: public ExceptionImpl(BadException, Exception)
	{
	public:
		BadException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief NullPointerException
	// ---------------------------------------------------------------------------
	class NullPointerException
		: public ExceptionExImpl(NullPointerException, BadException, FileAndLine)
	{
	public:
		NullPointerException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief OutOfRangeException
	// ---------------------------------------------------------------------------
	class OutOfRangeException
		: public ExceptionExImpl(OutOfRangeException, BadException, FileAndLine)
	{
	public:
		OutOfRangeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }

		template<typename range_violation_type>
		void operator()(range_violation_type range_violation);
	};

	//!
	//! \brief LeftOfRangeException 
	// ---------------------------------------------------------------------------
	class LeftOfRangeException
		: public ExceptionImpl(LeftOfRangeException, OutOfRangeException)
	{ };

	//!
	//! \brief RightOfRangeException
	// ---------------------------------------------------------------------------
	class RightOfRangeException
		: public ExceptionImpl(RightOfRangeException, OutOfRangeException)
	{ };

	// ---------------------------------------------------------------------------
	template<typename type>
	void OutOfRangeException::operator()(type range_violation)
	{
		switch(exceptionId + range_violation)
		{
		case eiLeftOfRangeException:	TypedThrow<LeftOfRangeException>();
		case eiRightOfRangeException:	TypedThrow<RightOfRangeException>();
		default:						Throw();
		}
	}

	//!
	//! \brief BadCastException
	// ---------------------------------------------------------------------------
	class BadCastException
		: public ExceptionImpl(BadCastException, Exception)
	{
	public:
		BadCastException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief BadNumericCast
	// ---------------------------------------------------------------------------
	class BadNumericCast
		: public ExceptionImpl(BadNumericCast, BadCastException)
	{
	public:
		BadNumericCast(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }

		template<typename overflow_type>
		void operator()(overflow_type overflow);
	};

	//!
	//! \brief NegativeOverflow
	// ---------------------------------------------------------------------------
	class NegativeOverflow
		: public ExceptionImpl(NegativeOverflow, BadNumericCast)
	{ };

	//!
	//! \brief PositiveOverflow
	// ---------------------------------------------------------------------------
	class PositiveOverflow
		: public ExceptionImpl(PositiveOverflow, BadNumericCast)
	{ };

	// ---------------------------------------------------------------------------
	template<typename overflow_type>
	void BadNumericCast::operator()(overflow_type overflow)
	{
		switch(eiBadNumericCast + overflow)
		{
		case eiNegativeOverflow: TypedThrow<NegativeOverflow>();
		case eiPositiveOverflow: TypedThrow<PositiveOverflow>();
		default:				 Throw();
		}
	}

	//!
	//! \brief RuntimeException
	// ---------------------------------------------------------------------------
	class RuntimeException
		: public ExceptionImpl(RuntimeException, Exception)
	{
	public:
		RuntimeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief BadAllocException
	// ---------------------------------------------------------------------------
	class BadAllocException
		: public ExceptionImpl(BadAllocException, RuntimeException)
	{
	public:
		BadAllocException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief OutOfMemoryException
	// ---------------------------------------------------------------------------
	class OutOfMemoryException
		: public ExceptionImpl(OutOfMemoryException, RuntimeException)
	{ };

	//!
	//! \brief NotSupportedException
	// ---------------------------------------------------------------------------
	class NotSupportedException
		: public ExceptionExImpl(NotSupportedException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief NotImplementedException
	// ---------------------------------------------------------------------------
	class NotImplementedException
		: public ExceptionExImpl(NotImplementedException, RuntimeException, FileAndLine)
	{
	public:
		NotImplementedException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief NotInitializedException
	// ---------------------------------------------------------------------------
	class NotInitializedException
		: public ExceptionExImpl(NotInitializedException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief FailedToInitializeException
	// ---------------------------------------------------------------------------
	class FailedToInitializeException
		: public ExceptionExImpl(FailedToInitializeException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief AlreadyInitializedException
	// ---------------------------------------------------------------------------
	class AlreadyInitializedException
		: public ExceptionExImpl(AlreadyInitializedException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief InvalidParameterException
	// ---------------------------------------------------------------------------
	class InvalidParameterException
		: public ExceptionExImpl(InvalidParameterException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief InvalidSessionIdException
	// ---------------------------------------------------------------------------
	class InvalidSessionIdException
		: public ExceptionExImpl(InvalidSessionIdException, RuntimeException, FileAndLine)
	{ };

	//!
	//! \brief SynchronizationException
	// ---------------------------------------------------------------------------
	class SynchronizationException
		: public ExceptionExImpl(SynchronizationException, RuntimeException, FileAndLine)
	{ };


	//!
	//! \brief ShutdownException<>
	// ---------------------------------------------------------------------------
	template<class NotifyPtrT = void>
	class ShutdownException
		: public ExceptionType<eiShutdownException, ShutdownException<NotifyPtrT>, RuntimeException>
	{
	public:
		typedef ExceptionType<eiShutdownException, ShutdownException<NotifyPtrT>, RuntimeException> BaseType;
		typedef ShutdownException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		template<class OtherPtrT>
		Type& operator>>(OtherPtrT& notify)  { notify.swap(m_notify); return *this; }
		Type& operator<<(NotifyPtrT& notify) { m_notify.swap(notify); return *this; }

	protected:
		NotifyPtrT m_notify;
	};

	//!
	//! \brief ShutdownException<void>
	// ---------------------------------------------------------------------------
	template<>
	class ShutdownException<void>
		: public ExceptionType<eiShutdownException, ShutdownException<void>, RuntimeException>
	{ };


	//!
	//! \brief LogicalException
	// ---------------------------------------------------------------------------
	class LogicalException
		: public ExceptionExImpl(LogicalException, Exception, FileAndLine)
	{
	public:
		LogicalException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief ASN1Exception
	// ---------------------------------------------------------------------------
	class ASN1Exception
		: public ExceptionImpl(ASN1Exception, LogicalException)
	{
	public:
		ASN1Exception(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief IncompatibleVersionException
	// ---------------------------------------------------------------------------
	class IncompatibleVersionException
		: public ExceptionImpl(IncompatibleVersionException, ASN1Exception)
	{
	public:
		IncompatibleVersionException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief FileNotFoundException
	// ---------------------------------------------------------------------------
	class FileNotFoundException
		: public ExceptionImpl(FileNotFoundException, LogicalException)
	{
	public:
		FileNotFoundException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief NoSuchDLLException
	// ---------------------------------------------------------------------------
	class NoSuchDLLException
		: public ExceptionImpl(NoSuchDLLException, FileNotFoundException)
	{
	public:
		NoSuchDLLException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief NoSuchMethodException
	// ---------------------------------------------------------------------------
	class NoSuchMethodException
		: public ExceptionImpl(NoSuchMethodException, LogicalException)
	{
	public:
		NoSuchMethodException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PasswordException
	// ---------------------------------------------------------------------------
	class PasswordException
		: public ExceptionImpl(PasswordException, LogicalException)
	{
	public:
		PasswordException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief ArithmeticException
	// ---------------------------------------------------------------------------
	class ArithmeticException
		: public ExceptionImpl(ArithmeticException, LogicalException)
	{
	public:
		ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief MessageDigestException
	// ---------------------------------------------------------------------------
	class MessageDigestException
		: public ExceptionImpl(MessageDigestException, LogicalException)
	{
	public:
		MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PaddingException
	// ---------------------------------------------------------------------------
	class PaddingException
		: public ExceptionImpl(PaddingException, LogicalException)
	{
	public:
		PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief SignatureException
	// ---------------------------------------------------------------------------
	class SignatureException
		: public ExceptionImpl(SignatureException, LogicalException)
	{
	public:
		SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};


	//!
	//! \brief AlgorithmException
	// ---------------------------------------------------------------------------
	class AlgorithmException
		: public ExceptionImpl(AlgorithmException, LogicalException)
	{
	public:
		AlgorithmException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidAlgorithmParameterException
	// ---------------------------------------------------------------------------
	class InvalidAlgorithmParameterException
		: public ExceptionImpl(InvalidAlgorithmParameterException, AlgorithmException)
	{
	public:
		InvalidAlgorithmParameterException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief IncompatibleAlgorithmException
	// ---------------------------------------------------------------------------
	class IncompatibleAlgorithmException
		: public ExceptionImpl(IncompatibleAlgorithmException, AlgorithmException)
	{ };

	//!
	//! \brief NoSuchAlgorithmException
	// ---------------------------------------------------------------------------
	class NoSuchAlgorithmException
		: public ExceptionImpl(NoSuchAlgorithmException, AlgorithmException)
	{
	public:
		typedef NoSuchAlgorithmException Type;

		NoSuchAlgorithmException(const char* msg, const char* where, const char* algorithm = 0)
			: ThisType(msg, where)
			, m_algorithm(algorithm)
		{
			m_algorithm.push_back(0);
		}

		NoSuchAlgorithmException(const char* algorithm = 0)
			: ThisType()
			, m_algorithm(algorithm)
		{
			m_algorithm.push_back(0);
		}

		// GCC 4.2.1 whats to have it
		virtual ~NoSuchAlgorithmException()
		{ }

		virtual Type*   Clone() const { return exception::clone<Type>(*this, algorithm());		}
		virtual void    Throw() const { throw  Type(m_what, m_where, algorithm());				}

		const char* algorithm() const { return reinterpret_cast<const char*>(&m_algorithm[0]);	}

	protected:
		mutable Blob m_algorithm;
	};


	//!
	//! \brief CertificateException
	// ---------------------------------------------------------------------------
	class CertificateException
		: public ExceptionImpl(CertificateException, LogicalException)
	{
	public:
		CertificateException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidCertificateException
	// ---------------------------------------------------------------------------
	class InvalidCertificateException
		: public ExceptionImpl(InvalidCertificateException, CertificateException)
	{
	public:
		InvalidCertificateException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief CertificateEncodingException
	// ---------------------------------------------------------------------------
	class CertificateEncodingException
		: public ExceptionImpl(CertificateEncodingException, CertificateException)
	{
	public:
		CertificateEncodingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief CertificateExpiredException
	// ---------------------------------------------------------------------------
	class CertificateExpiredException
		: public ExceptionImpl(CertificateExpiredException, CertificateException)
	{
	public:
		CertificateExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief CertificateNotYetValidException
	// ---------------------------------------------------------------------------
	class CertificateNotYetValidException
		: public ExceptionImpl(CertificateNotYetValidException, CertificateException)
	{
	public:
		CertificateNotYetValidException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief CertificateParsingException
	// ---------------------------------------------------------------------------
	class CertificateParsingException
		: public ExceptionImpl(CertificateParsingException, CertificateException)
	{
	public:
		CertificateParsingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};


	//!
	//! \brief KeyException
	// ---------------------------------------------------------------------------
	class KeyException
		: public ExceptionImpl(KeyException, LogicalException)
	{
	public:
		KeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidKeyParameterException
	// ---------------------------------------------------------------------------
	class InvalidKeyParameterException
		: public ExceptionImpl(InvalidKeyParameterException, KeyException)
	{
	public:
		InvalidKeyParameterException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidKeyException
	// ---------------------------------------------------------------------------
	class InvalidKeyException
		: public ExceptionImpl(InvalidKeyException, KeyException)
	{
	public:
		InvalidKeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief KeyManagementException
	// ---------------------------------------------------------------------------
	class KeyManagementException
		: public ExceptionImpl(KeyManagementException, KeyException)
	{ };


	//!
	//! \brief EACException
	// ---------------------------------------------------------------------------
	class EACException
		: public ExceptionImpl(EACException, LogicalException)
	{
	public:
		EACException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief EACDataException
	// ---------------------------------------------------------------------------
	class EACDataException
		: public ExceptionImpl(EACDataException, EACException)
	{
	public:
		EACDataException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code)
		{ }
	};

	//!
	//! \brief EACMRZException
	// ---------------------------------------------------------------------------
	class EACMRZException
		: public ExceptionImpl(EACMRZException, EACDataException)
	{
	public:
		EACMRZException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief EACCVCertException
	// ---------------------------------------------------------------------------
	class EACCVCertException
		: public ExceptionImpl(EACCVCertException, EACDataException)
	{
	public:
		EACCVCertException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};


	//!
	//! \brief SmartcardException
	// ---------------------------------------------------------------------------
	class SmartcardException
		: public ExceptionImpl(SmartcardException, LogicalException)
	{
	public:
		SmartcardException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief CardRemovedException
	// ---------------------------------------------------------------------------
	class CardRemovedException
		: public ExceptionImpl(CardRemovedException, SmartcardException)
	{ };

	//!
	//! \brief CardOutOfMemoryException
	// ---------------------------------------------------------------------------
	class CardOutOfMemoryException
		: public ExceptionImpl(CardOutOfMemoryException, SmartcardException)
	{ };

	//!
	//! \brief CardTransactionException
	// ---------------------------------------------------------------------------
	class CardTransactionException
		: public ExceptionImpl(CardTransactionException, SmartcardException)
	{ };

	//!
	//! \brief PinException
	// ---------------------------------------------------------------------------
	class PinException
		: public ExceptionImpl(PinException, SmartcardException)
	{
	public:
		PinException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PinEntryException
	// ---------------------------------------------------------------------------
	class PinEntryException
		: public ExceptionImpl(PinEntryException, PinException)
	{ };

	//!
	//! \brief PinChangeException
	// ---------------------------------------------------------------------------
	class PinChangeException
		: public ExceptionImpl(PinChangeException, PinException)
	{ };

	//!
	//! \brief PinModifyException
	// ---------------------------------------------------------------------------
	typedef PinChangeException PinModifyException;

	//!
	//! \brief PinLockedException
	// ---------------------------------------------------------------------------
	class PinLockedException
		: public ExceptionImpl(PinLockedException, PinException)
	{
	public:
		PinLockedException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PinExpiredException
	// ---------------------------------------------------------------------------
	class PinExpiredException
		: public ExceptionImpl(PinExpiredException, PinException)
	{
	public:
		PinExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PinLenRangeException
	// ---------------------------------------------------------------------------
	class PinLenRangeException
		: public ExceptionImpl(PinLenRangeException, PinException)
	{
	public:
		PinLenRangeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidPinException
	// ---------------------------------------------------------------------------
	class InvalidPinException
		: public ExceptionImpl(InvalidPinException, PinException)
	{
	public:
		InvalidPinException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief PinVerifyException
	// ---------------------------------------------------------------------------
	typedef InvalidPinException PinVerifyException;

	//!
	//! \brief InvalidPinFormatException
	// ---------------------------------------------------------------------------
	class InvalidPinFormatException
		: public ExceptionImpl(InvalidPinFormatException, PinException)
	{
	public:
		InvalidPinFormatException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidCRKeyException
	// ---------------------------------------------------------------------------
	class InvalidCRKeyException
		: public ExceptionImpl(InvalidCRKeyException, SmartcardException)
	{
	public:
		InvalidCRKeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidCardException
	// ---------------------------------------------------------------------------
	class InvalidCardException
		: public ExceptionImpl(InvalidCardException, SmartcardException)
	{
	public:
		InvalidCardException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidAuthException
	// ---------------------------------------------------------------------------
	class InvalidAuthException
		: public ExceptionImpl(InvalidAuthException, SmartcardException)
	{
	public:
		InvalidAuthException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};

	//!
	//! \brief InvalidAuthObjectException
	// ---------------------------------------------------------------------------
	class InvalidAuthObjectException
		: public ExceptionImpl(InvalidAuthObjectException, SmartcardException)
	{ };

	//!
	//! \brief InvalidAuthConstraints
	// ---------------------------------------------------------------------------
	class InvalidAuthConstraints
		: public ExceptionImpl(InvalidAuthConstraints, SmartcardException)
	{ };

	//!
	//! \brief AuthProtocolException
	// ---------------------------------------------------------------------------
	class AuthProtocolException
		: public ExceptionImpl(AuthProtocolException, SmartcardException)
	{
	public:
		AuthProtocolException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: ThisType(msg, where, code) { }
	};


	//!
	//! \brief ConstraintsViolationException
	// ---------------------------------------------------------------------------
	class ConstraintsViolationException
		: public ExceptionImpl(ConstraintsViolationException, SmartcardException)
	{ };

	//!
	//! \brief AuthConstraintsViolation
	// ---------------------------------------------------------------------------
	class AuthConstraintsViolation
		: public ExceptionImpl(AuthConstraintsViolation, ConstraintsViolationException)
	{ };

	//!
	//! \brief TokenFileConstraintsViolation
	// ---------------------------------------------------------------------------
	class TokenFileConstraintsViolation
		: public ExceptionImpl(TokenFileConstraintsViolation, ConstraintsViolationException)
	{ };


	//!
	//! \brief SecureMessagingException
	// ---------------------------------------------------------------------------
	class SecureMessagingException
		: public ExceptionImpl(SecureMessagingException, SmartcardException)
	{ };

	//!
	//! \brief SMWrapException
	// ---------------------------------------------------------------------------
	class SMWrapException
		: public ExceptionImpl(SMWrapException, SecureMessagingException)
	{ };

	//!
	//! \brief SMUnwrapException
	// ---------------------------------------------------------------------------
	class SMUnwrapException
		: public ExceptionImpl(SMUnwrapException, SecureMessagingException)
	{ };

	//!
	//! \brief SMInvalidException
	// ---------------------------------------------------------------------------
	class SMInvalidException
		: public ExceptionImpl(SMInvalidException, SecureMessagingException)
	{ };

	//!
	//! \brief SubsystemException
	// ---------------------------------------------------------------------------
	class SubsystemException
		: public ExceptionImpl(SubsystemException, LogicalException)
	{ };

	//!
	//! \brief NoSuchSubsystemException
	// ---------------------------------------------------------------------------
	class NoSuchSubsystemException
		: public ExceptionImpl(NoSuchSubsystemException, SubsystemException)
	{ };

#	undef ExceptionExImpl
#	undef ExceptionImpl
#else

	#define throw(_x)	_exit(_x)

	int Exception(const char* msg = 0, const char* where = 0, ulong code = 0);
		int BadException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	NullPointerException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	OutOfRangeException(const char* msg = 0, const char* where = 0, ulong code = 0);
		int BadCastException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int BadNumericCast(const char* msg = 0, const char* where = 0, ulong code = 0);
		int	RuntimeException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int BadAllocException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int OutOfMemoryException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotSupportedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotImplementedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotInitializedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int FailedToInitializeException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int AlreadyInitializedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int InvalidParameterException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int InvalidSessionIdException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SynchronizationException(const char* msg = 0, const char* where = 0, ulong code = 0);
		int	LogicalException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	ASN1Exception(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	IncompatibleVersionException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	FileNotFoundException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	NoSuchDLLException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NoSuchMethodException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PasswordException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	AlgorithmException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	InvalidAlgorithmParameterException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	IncompatibleAlgorithmException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	NoSuchAlgorithmException(const char* msg = 0, const char* where = 0, const char* algorithm);
			int ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	CertificateException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateEncodingException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateNotYetValidException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateParsingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	KeyException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidKeyParameterException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	InvalidKeyException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	KeyManagementException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int EACException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int EACDataException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int EACMRZException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int EACCVCertException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SmartcardException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardRemovedException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardOutOfMemoryException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardTransactionException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int PinException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinEntryException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinModifyException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinLockedException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinLenRangeException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int InvalidPinException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int PinVerifyException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int InvalidPinFormatException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidCRKeyException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidCardException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidAuthException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidAuthObjectException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int AuthProtocolException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int ConstraintsViolationException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int AuthConstraintsViolation(const char* msg = 0, const char* where = 0, ulong code = 0);
					int TokenFileConstraintsViolation(const char* msg = 0, const char* where = 0, ulong code = 0);
				int SecureMessagingException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int SMWrapException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int SMUnwrapException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int NoSuchSubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0);

#endif	// UNDER_CE_30

} // namespace act

#endif // ACT_Exception_h
