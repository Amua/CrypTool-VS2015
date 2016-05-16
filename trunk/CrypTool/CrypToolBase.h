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
#include <afxwin.h>
#include <atlstr.h>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>

// this struct encapsulates an octet string (TODO/FIXME: TEMPORARY SOLUTION FOR COMPATIBILITY WITH LEGACY CODE)
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
		// construction: if no parameter is specified, no memory is allocated
		ByteString(const size_t _byteLength = 0);
		// destruction: the allocated memory is deleted
		~ByteString();
	public:
		// read byte string from file: in case of errors, false is returned
		bool readFromFile(const CString &_fileName);
		// write byte string to file; in case of errors, false is returned
		bool writeToFile(const CString &_fileName) const;
	private:
		// resets the byte string: deletes the allocated memory, 
		// and resets both the byte data and byte length to zero
		void reset();
	private:
		// the byte data
		char *byteData;
		// the byte length
		size_t byteLength;
	};

	// this namespace encapsulates a variety of utilitiy functions
	namespace Utilities {

		// this function returns a temporary file name with the specified extension so that the resulting 
		// file name adheres to the following pattern: "CrypTool-[identifier].[extension]"; the identifier 
		// is random; if a temporary file name cannot be created, the function returns an empty string
		CString getTemporaryFileName(const CString &_extension = ".tmp");

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
				HASH_ALGORITHM_TYPE_SHA224,
				HASH_ALGORITHM_TYPE_SHA256,
				HASH_ALGORITHM_TYPE_SHA384,
				HASH_ALGORITHM_TYPE_SHA512
			};

			// this function returns the name of the specified hash algorithm type
			CString getHashAlgorithmName(const HashAlgorithmType _hashAlgorithmType);
			// this function returns the bit length of the specified hash algorithm type
			int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType);

			// this class provides hash operations on all supported hash algorithm types
			class HashOperation {
			public:
				HashOperation(const HashAlgorithmType _hashAlgorithmType);
				virtual ~HashOperation();
			public:
				void startOperation(const CString &_fileNameSource, const CString &_fileNameTarget);
			private:
				const HashAlgorithmType hashAlgorithmType;
			private:
				// OpenSSL context
				void *context;
				// type definitions for OpenSSL function pointers
				typedef void(*fpInitialize_t) (void *_context);
				typedef void(*fpUpdate_t) (void *_context, void *_message, unsigned long _length);
				typedef void(*fpFinalize_t) (void *_digest, void *_context);
				// conext and function pointers for OpenSSL hash operations
				fpInitialize_t fpInitialize;
				fpUpdate_t fpUpdate;
				fpFinalize_t fpFinalize;
			};

		}

		// the supported symmetric encryption algorithm types
		enum SymmetricEncrytionAlgorithm {
			SYMMETRIC_ENCRYPTION_ALGORITHM_TYPE_NULL
		};

		// the supported asymmetric encryption algorithm types
		enum AsymmetricEncryptionAlgorithms {
			ASYMMETRIC_ENCRYPTION_ALGORITHM_TYPE_NULL
		};

	}

}

#endif