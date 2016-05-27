/**************************************************************************

Copyright [2009] [CrypTool Team]

This file is part of CrypTool.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

**************************************************************************/

#ifndef _CRYPTOOLBASE_H_
#define _CRYPTOOLBASE_H_

#include <afx.h>
#include <afxmt.h>
#include <afxwin.h>
#include <afxcmn.h>
#include <stdafx.h>
#include <atlstr.h>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>
#include <map>
#include <set>

namespace OpenSSL {
	// generic headers
	#include <openssl/bio.h>
	#include <openssl/pem.h>
	#include <openssl/err.h>
	// hash algorithms
	#include "OpenSSL/md4.h"
	#include "OpenSSL/md5.h"
	#include "OpenSSL/ripemd.h"
	#include "OpenSSL/sha.h"
	// symmetric cryptography
	#include "OpenSSL/evp.h"
	// asymmetric cryptography
	#include <openssl/x509v3.h>
}

// this struct encapsulates an octet string for compatibility with legacy code
struct OctetString {
	// construction
	OctetString();
	// the number of octets stored in this octet string (default: zero)
	uint32_t noctets;
	// the actual data (default: zero)
	char *octets;
};

// this namespace encapsulates high-level CrypTool functionality
namespace CrypTool {

	// this class encapsulates byte strings for various cryptographic operations; 
	// it provides an interface for reading/writing bytes from/to files, and it 
	// makes sure the allocated memory is deleted upon destruction
	class ByteString {
	public:
		// construction
		ByteString();
		ByteString(const ByteString &_byteString);
		ByteString(const size_t _byteLength);
		ByteString(const unsigned char *_byteData, const size_t _byteLength);
		// destruction
		~ByteString();
	public:
		// read byte string from file: in case of errors, false is returned
		bool readFromFile(const CString &_fileName);
		// write byte string to file; in case of errors, false is returned
		bool writeToFile(const CString &_fileName) const;
	public:
		// read data from the specified buffer; this function is "dumb" in that the 
		// caller needs to make sure the memory of the specified buffer is valid; 
		// zero pointers make this function return zero without doing anything else; 
		// otherwise this function returns the number of bytes copied to the internal 
		// buffer (it allocates new memory internally)
		size_t fromBuffer(const unsigned char *_bufferData, const size_t _bufferLength);
		// write data to the specified buffer; this function is "dumb" in that the 
		// caller needs to make sure the memory of the specified buffer is valid; 
		// zero pointers make this function return zero without doing anything else; 
		// otherwise this function returns the number of bytes copied to the specified 
		// buffer
		size_t toBuffer(unsigned char *_bufferData, const size_t _bufferLength) const;
	public:
		// this is a convenience function to convert CString objects to byte strings
		void fromString(const CString &_string);
		// this is a convenience function to convert byte strings to CString objects; 
		// note that the result is truncated where the first null byte is spotted
		CString toString() const;
		// this is a convenience function to convert byte strings to either binary, 
		// octal, decimal, or hexadecimal representations; if an invalid base is 
		// specified, the function returns an empty string
		CString toString(const unsigned int _base, const CString &_separator = "") const;
	public:
		// resets the byte string: deletes the allocated memory, 
		// and resets both the byte data and byte length to zero 
		// unless a new byte length is specified
		void reset(const size_t _byteLength = 0);
		// truncates the byte string to the specified size; if the specified 
		// size is larger than the actual size, the function does nothing; 
		// otherwise the function allocates new memory for the truncated 
		// contents and frees the old memory
		void truncate(const size_t _byteLength);
	public:
		// this function returns a pointer to the internal data
		unsigned char *getByteData() { return byteData; }
		const unsigned char *getByteDataConst() const { return byteData; }
		// this function returns the length of the internal data
		size_t getByteLength() const { return byteLength; }
	public:
		// operator implementation
		ByteString &operator=(const ByteString &_byteString);
		// operator implementation
		ByteString &operator+=(const ByteString &_byteString);
	private:
		// the byte data
		unsigned char *byteData;
		// the byte length
		size_t byteLength;
	};

	// this function returns the path in which CrypTool is executed
	CString getCrypToolPath();

	// this namespace encapsulates a variety of utilitiy functions
	namespace Utilities {

		// this function creates a temporary file with the specified extension so that the resulting file 
		// name adheres to the following pattern: "CrypTool-[identifier].[extension]", the identifiers are 
		// generated sequentially; if the function cannot create a temporary file in one of the system temp 
		// folders, it uses the CrypTool directory; if a temporary file name cannot be created, the function 
		// asserts; the function is thread-safe
		CString createTemporaryFile(const CString &_extension = ".tmp");

		// this function truncates the specified byte string to the specified length; this function also 
		// removes all bytes at (and beyond) the first null byte; if the byte string is modified in any 
		// way, the user is notified; the function returns the length of the resulting byte string
		size_t truncateByteString(ByteString &_byteString, const unsigned int _truncateAtLength, const bool _truncateAtFirstNullByte);

		// this template function is provided for convenience, it returns true if the specified vector 
		// contains the specified element
		template<class T>
		bool vectorContains(const std::vector<T> &_vector, const T &_element) {
			for (size_t index = 0; index < _vector.size(); index++) {
				if (_vector[index] == _element) {
					return true;
				}
			}
			return false;
		}

	}

	// this namespace encapsulates cryptographic functionality
	namespace Cryptography {

		// this namespace encapsulates hash functionality
		namespace Hash {

			// the supported hash algorithm types
			enum HashAlgorithmType {
				HASH_ALGORITHM_TYPE_NULL,
				HASH_ALGORITHM_TYPE_MD4,
				HASH_ALGORITHM_TYPE_MD5,
				HASH_ALGORITHM_TYPE_RIPEMD160,
				HASH_ALGORITHM_TYPE_SHA,
				HASH_ALGORITHM_TYPE_SHA1,
				HASH_ALGORITHM_TYPE_SHA256,
				HASH_ALGORITHM_TYPE_SHA512
			};

			// this function returns the name of the specified hash algorithm type
			CString getHashAlgorithmName(const HashAlgorithmType _hashAlgorithmType);
			// this function returns the bit length of the specified hash algorithm type
			unsigned int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType);
			// this function returns the byte length of the specified hash algorithm type
			unsigned int getHashAlgorithmByteLength(const HashAlgorithmType _hashAlgorithmType);

			// this class provides hash operations on all supported hash algorithm types 
			// for both byte strings and files (see different execute functions below); 
			// the file-based operation provides the ability to cancel the operation 
			// and track its progress when run in a separate thread
			class HashOperation {
			public:
				HashOperation(const HashAlgorithmType _hashAlgorithmType);
				virtual ~HashOperation();
			public:
				bool executeOnByteStrings(const ByteString &_byteStringInput, ByteString &_byteStringOutput);
				bool executeOnFiles(const CString &_fileNameInput, const CString &_fileNameOutput, const bool *_cancelled = 0, double *_progress = 0);
			private:
				const HashAlgorithmType hashAlgorithmType;
			private:
				// type definitions for OpenSSL function pointers
				typedef int(*fpInitialize_t) (void *_context);
				typedef int(*fpUpdate_t) (void *_context, void *_input, ULONGLONG _inputLength);
				typedef int(*fpFinalize_t) (void *_digest, void *_context);
				// context size and function pointers for OpenSSL
				size_t contextSize;
				fpInitialize_t fpInitialize;
				fpUpdate_t fpUpdate;
				fpFinalize_t fpFinalize;
			};

		}

		// this namespace encapsulates symmetric encryption and decryption functionality
		namespace Symmetric {

			// the supported symmetric algorithm types
			enum SymmetricAlgorithmType {
				SYMMETRIC_ALGORITHM_TYPE_NULL,
				SYMMETRIC_ALGORITHM_TYPE_IDEA,
				SYMMETRIC_ALGORITHM_TYPE_RC2,
				SYMMETRIC_ALGORITHM_TYPE_RC4,
				SYMMETRIC_ALGORITHM_TYPE_DES_ECB,
				SYMMETRIC_ALGORITHM_TYPE_DES_CBC,
				SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_ECB,
				SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_CBC,
				SYMMETRIC_ALGORITHM_TYPE_AES,
				SYMMETRIC_ALGORITHM_TYPE_MARS,
				SYMMETRIC_ALGORITHM_TYPE_RC6,
				SYMMETRIC_ALGORITHM_TYPE_SERPENT,
				SYMMETRIC_ALGORITHM_TYPE_TWOFISH,
				SYMMETRIC_ALGORITHM_TYPE_DESX,
				SYMMETRIC_ALGORITHM_TYPE_DESL,
				SYMMETRIC_ALGORITHM_TYPE_DESXL
			};

			// the supported symmetric operation types
			enum SymmetricOperationType {
				SYMMETRIC_OPERATION_TYPE_NULL,
				SYMMETRIC_OPERATION_TYPE_ENCRYPTION,
				SYMMETRIC_OPERATION_TYPE_DECRYPTION
			};

			// this function returns the name of the specified symmetric algorithm type
			CString getSymmetricAlgorithmName(const SymmetricAlgorithmType _symmetricAlgorithmType);

			// this class provides symmetric operations (encryption and decryption) on 
			// all supported symmetric algorithm types for both byte strings and files 
			// (see different execute functions below); the file-based operations provide 
			// the ability to cancel the operations and track their progress when run in 
			// a separate thread
			class SymmetricOperation {
			public:
				SymmetricOperation(const SymmetricAlgorithmType _symmetricAlgorithmType, const SymmetricOperationType _symmetricOperationType);
				virtual ~SymmetricOperation();
			public:
				bool executeOnByteStrings(const ByteString &_byteStringInput, const ByteString &_byteStringKey, ByteString &_byteStringOutput);
				bool executeOnFiles(const CString &_fileNameInput, const CString &_fileNameOutput, const ByteString &_byteStringKey, const bool *_cancelled = 0, double *_progress = 0);
			private:
				const SymmetricAlgorithmType symmetricAlgorithmType;
				const SymmetricOperationType symmetricOperationType;
			private:
				const OpenSSL::EVP_CIPHER *getOpenSSLCipher(const SymmetricAlgorithmType _symmetricAlgorithmType, const size_t _keyLength) const;
			private:
				// type definitions for OpenSSL function pointers
				typedef int(*fpInitialize_t) (void *_context, const void *_cipher, const void *_key, const void *_iv);
				typedef int(*fpUpdate_t) (void *_context, void *_output, int *_outputLength, const void *_input, int _inputLength);
				typedef int(*fpFinalize_t) (void *_context, void *_output, int *_outputLength);
				// context and function pointers for OpenSSL
				OpenSSL::EVP_CIPHER_CTX *context;
				fpInitialize_t fpInitialize;
				fpUpdate_t fpUpdate;
				fpFinalize_t fpFinalize;
			};

		}

		// this namespace encapsulates asymmetric encryption and decryption functionality
		namespace Asymmetric {

			// the supported asymmetric algorithm types
			enum AsymmetricAlgorithmType {
				ASYMMETRIC_ALGORITHM_TYPE_NULL
			};

			// the supported asymmetric operation types
			enum AsymmetricOperationType {
				ASYMMETRIC_OPERATION_TYPE_NULL,
				ASYMMETRIC_OPERATION_TYPE_ENCRYPTION,
				ASYMMETRIC_OPERATION_TYPE_DECRYPTION
			};

			//
			// TODO/FIXME: implement "AsymmetricOperation" class? (see symmetric counterpart above)
			//

			// the supported certificate types
			enum CertificateType {
				CERTIFICATE_TYPE_NULL,
				CERTIFICATE_TYPE_RSA,
				CERTIFICATE_TYPE_DSA,
				CERTIFICATE_TYPE_EC
			};

			// TODO/FIXME
			class CertificateStore {
			protected:
				CertificateStore();
				virtual ~CertificateStore();
			public:
				static CertificateStore &instance();
			public:
				void initialize(const CString &_caPassword);
				void deinitialize();
			private:
				const CString pathToCertificateStore;
				const CString fileNameCaCertificate;
				const CString fileNameCaPrivateKey;
			private:
				OpenSSL::X509 *caCertificate;
				OpenSSL::RSA *caPrivateKey;
			private:
				// this map holds all user certificates (mapped to serial numbers) currently held 
				// in memory; whenever a user certificate is created or deleted, all user certificates 
				// are automatically re-loaded so that this map is always up-to-date
				std::map<long, OpenSSL::X509*> mapUserCertificates;
			public:
				// this function tries to create a certificate with the values specified by the user; the 
				// certificate type is one of RSA, DSA, EC, and the the certificate parameters string contains 
				// either the desired key length (RSA and DSA) or the desired elliptic curve (EC); all other 
				// parameters (first name, last name, remarks, password) are identical for all types
				bool createUserCertificate(const CertificateType _certificateType, const CString &_certificateParameters, const CString &_firstName, const CString &_lastName, const CString &_remarks, const CString &_password);
				// this function tries to delete the user certificate with the specified serial number; 
				// however, the correct password (protecting the private key) must be provided for the 
				// deletion to be successful
				bool deleteUserCertificate(const long _serial, const CString &_password);
			private:
				// this function generates file names for the user certificate and the user private key 
				// based on the serial number of the certificate (which is unique due to the implementation)
				void generateFileNamesForUserCertificateAndUserPrivateKey(const long _serial, CString &_fileNameUserCertificate, CString &_fileNameUserPrivateKey) const;
			private:
				// this function is called whenever the certificate store content changes, in other words: 
				// whenever a user certificate is created or deleted; it makes sure all user certificates 
				// are always held in memory to provide quick access without expensive file operations
				void loadUserCertificates();
				// this function is called to unload all user certificates from memory
				void unloadUserCertificates();
			public:
				// the following function is provided for convenience: it returns the serial numbers of 
				// all user certificates stored in this certificate store; the arguments control which
				// types of certificates are returned; if all arguments are false, the resulting vector 
				// is empty of course
				std::vector<long> getUserCertificateSerials(const bool _rsa, const bool _dsa, const bool _ec) const;
				// the following function is provided for convenience: if the serial number supplied as 
				// argument doesn't match any of the available user certificates, the function returns 
				// false and all output variables remain untouched; first and foremost this function is 
				// used as an interface to easily display user certificate information to the user
				bool getUserCertificateInformation(const long _serial, CString &_firstName, CString &_lastName, CString &_remarks, CString &_type, CString &_validFrom, CString &_validTo) const;
			};

		}

	}

	// this namespace encapsulates a variety of high-level functions
	namespace Functions {

		// TODO/FIXME: rename or remove this? the complexity behind this operation is unclear (threading, etc...)
		void executeHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
		// TODO/FIXME: rename or remove this? the complexity behind this operation is unclear (threading, etc...)
		void executeSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);

		// this function creates a password-derived key based on the PKCS#5 standard
		bool createKeyFromPasswordPKCS5(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const ByteString &_password, const ByteString &_salt, const int _iterations, const int _keyLength, ByteString &_key);

	}

	// this namespace encapsulates internal functionality
	namespace Internal {

		class DialogOperationController : public CDialog {
		private:
			enum OperationStatus {
				OPERATION_STATUS_NULL,
				OPERATION_STATUS_STARTED,
				OPERATION_STATUS_FINISHED,
				OPERATION_STATUS_DONE
			};
			// this struct is passed to the individual execution threads to 
			// communicate with the main thread (where this dialog lives in)
			struct Parameters {
				// the status of the operation
				OperationStatus operationStatus;
				// whether the operation was cancelled
				bool operationCancelled;
				// the progress of the operation
				double operationProgress;
				// parameters specific to hash operations
				struct ParametersHash {
					CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType;
					CString documentFileName;
					CString documentTitle;
					CString documentFileNameNew;
					CString documentTitleNew;
					// construction/destruction
					ParametersHash() : hashAlgorithmType(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL), documentFileName(""), documentTitle(""), documentFileNameNew(""), documentTitleNew("") { }
					virtual ~ParametersHash() { }
				} parametersHash;
				// parameters specific to symmetric operations
				struct ParametersSymmetric {
					CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
					CrypTool::Cryptography::Symmetric::SymmetricOperationType symmetricOperationType;
					CString documentFileName;
					CString documentTitle;
					CString documentFileNameNew;
					CString documentTitleNew;
					ByteString key;
					// construction/destruction
					ParametersSymmetric() : symmetricAlgorithmType(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_NULL), documentFileName(""), documentTitle(""), documentFileNameNew(""), documentTitleNew(""), key(ByteString()) { }
					virtual ~ParametersSymmetric() { }
				} parametersSymmetric;
				// construction/destruction
				Parameters() : operationStatus(OPERATION_STATUS_NULL), operationCancelled(false), operationProgress(0.0) { }
				virtual ~Parameters() { }
			} parameters;
		public:
			DialogOperationController();
			virtual ~DialogOperationController();
		public:
			void startHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
			void startSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
		private:
			static UINT executeHashOperation(LPVOID _parameters);
			static UINT executeSymmetricOperation(LPVOID _parameters);
		private:
			// this thread is used for executing the actual operation
			CWinThread *operationThread;
		private:
			// the identifier of the update timer
			UINT_PTR updateTimer;
			// the identifier for the update timer event
			const UINT ID_TIMER_EVENT_UPDATE;
		private:
			virtual BOOL OnInitDialog();
			virtual void OnTimer(UINT_PTR _event);
			virtual void OnCancel();
			virtual void OnClose();
		private:
			void PostNcDestroy();
		private:
			virtual void DoDataExchange(CDataExchange *_pDX);
		private:
			CProgressCtrl controlProgress;
			CStatic controlText;
		private:
			DECLARE_MESSAGE_MAP()
		private:
			friend class CrypTool::Cryptography::Hash::HashOperation;
		};

	}

}

#endif