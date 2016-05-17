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
#include <atlstr.h>
#include <cstdint>
#include <cstring>
#include <limits>
#include <vector>
#include <set>

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

		// this function creates a temporary file with the specified extension so that the resulting file 
		// name adheres to the following pattern: "CrypTool-[identifier].[extension]", the identifiers are 
		// generated sequentially; if the function cannot create a temporary file in one of the system temp 
		// folders, it uses the CrypTool directory; if a temporary file name cannot be created, the function 
		// asserts; the function is thread-safe
		CString createTemporaryFile(const CString &_extension = ".tmp");

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
			int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType);

			// this class provides hash operations on all supported hash algorithm types
			class HashOperation {
			public:
				HashOperation(const HashAlgorithmType _hashAlgorithmType, const CString &_fileNameSource, const CString &_fileNameTarget);
				virtual ~HashOperation();
			public:
				void execute(const bool *_cancelled = 0, double *_progress = 0);
			private:
				const HashAlgorithmType hashAlgorithmType;
				const CString fileNameSource;
				const CString fileNameTarget;
			private:
				// OpenSSL context
				void *context;
				// type definitions for OpenSSL function pointers
				typedef void(*fpInitialize_t) (void *_context);
				typedef void(*fpUpdate_t) (void *_context, void *_message, ULONGLONG _length);
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

	// this namespace encapsulates a variety of high-level functions
	namespace Functions {

		void executeHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);

	}

	// this namespace encapsulates internal functionality
	namespace Internal {

		class DialogOperationController : public CDialog {
		private:
			// this struct is passed to the individual execution threads to 
			// communicate with the main thread (where this dialog lives in)
			struct Parameters {
				// whether the operation has been started
				bool started;
				// whether the operation has been finished
				bool finished;
				// whether the operation has been cancelled
				bool cancelled;
				// the progress of the operation (0.0 to 1.0)
				double progress;
				// parameters specific to hash operations
				struct ParametersHash {
					CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType;
					CString documentFileName;
					CString documentTitle;
					// construction
					ParametersHash() : hashAlgorithmType(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL), documentFileName(""), documentTitle("") { }
				} parametersHash;
				// construction
				Parameters() : started(false), finished(false), cancelled(false), progress(0.0) { }
			} parameters;
		public:
			DialogOperationController();
			virtual ~DialogOperationController();
		public:
			void startHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
			// TODO/FIXME: insert functions for other operations here
		private:
			static UINT executeHashOperation(LPVOID _parameters);
			// TODO/FIXME: insert functions for other operations here
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