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

#include "CrypToolBase.h"
#include "resource.h"

namespace OpenSSL {
#include "OpenSSL/md4.h"
#include "OpenSSL/md5.h"
#include "OpenSSL/ripemd.h"
#include "OpenSSL/sha.h"
}

OctetString::OctetString() :
	noctets(0),
	octets(0) {

}

namespace CrypTool {

	ByteString::ByteString(const size_t _byteLength) :
		byteData(0),
		byteLength(0) {
		if (_byteLength > 0) {
			byteData = new char[byteLength];
			std::memset(byteData, 0, byteLength);
			byteLength = _byteLength;
		}
	}

	ByteString::~ByteString() {
		reset();
	}

	bool ByteString::readFromFile(const CString &_fileName) {
		CFile infile;
		if (infile.Open(_fileName, CFile::modeRead)) {
			reset();
			const uint64_t infileLength = infile.GetLength();
			if (infileLength <= (std::numeric_limits<size_t>::max)()) {
				byteLength = (size_t)(infileLength);
				byteData = new char[byteLength];
				std::memset(byteData, 0, byteLength);
				if (infile.Read(byteData, byteLength) == byteLength) {
					infile.Close();
					return true;
				}
			}
			infile.Close();
			reset();
		}
		return false;
	}

	bool ByteString::writeToFile(const CString &_fileName) const {
		CFile outfile;
		if (outfile.Open(_fileName, CFile::modeCreate | CFile::modeWrite)) {
			outfile.Write(byteData, byteLength);
			outfile.Close();
		}
		return false;
	}

	void ByteString::reset() {
		delete byteData;
		byteData = 0;
		byteLength = 0;
	}

	namespace Utilities {

		CString createTemporaryFile(const CString &_extension) {
			// here we try to find a folder for the temporary files; if none of 
			// the specified environment variables are valid, we stick to the 
			// folder in which CrypTool is executed
			CString temporaryFolder;
			std::vector<CString> vectorEnvironmentVariables;
			vectorEnvironmentVariables.push_back("TEMP");
			vectorEnvironmentVariables.push_back("TMP");
			// try to find a valid temporary folder using the environment variables
			for (unsigned int i = 0; i < vectorEnvironmentVariables.size(); i++) {
				char *environmentVariable = 0;
				size_t environmentVariableSize = 0;
				ASSERT(_dupenv_s(&environmentVariable, &environmentVariableSize, vectorEnvironmentVariables[i]) == 0);
				temporaryFolder = environmentVariable;
				delete environmentVariable;
				if (temporaryFolder.GetLength() > 0) {
					break;
				}
			}
			// stick to the current folder if no temporary folder was found
			if (temporaryFolder.GetLength() == 0) {
				temporaryFolder = ".";
			}
			// provide thread-safety
			static CMutex mutex;
			mutex.Lock();
			// now iterate through the range of valid identifiers and check 
			// whether there's a file name for which a temporary file has not 
			// been created yet
			CFile file;
			CString temporaryFileName;
			const int identifierMin = 1;
			const int identifierMax = (std::numeric_limits<int>::max)();
			for (int identifier = identifierMin; identifier <= identifierMax; identifier++) {
				// create temporary file name (using the specified extension)
				temporaryFileName.Format("%s\\CrypTool-%d.%s", temporaryFolder, identifier, _extension);
				// try to open the temporary file for reading
				if (file.Open(temporaryFileName, CFile::modeRead)) {
					file.Close();
				}
				else {
					// try to open the temporary file for writing
					if (file.Open(temporaryFileName, CFile::modeWrite | CFile::modeCreate)) {
						file.Close();
						break;
					}
				}
			}
			mutex.Unlock();
			// make sure the temporary file name is valid before returning
			ASSERT(!temporaryFileName.IsEmpty());
			return temporaryFileName;
		}

	}

	namespace Cryptography {

		namespace Hash {

			CString getHashAlgorithmName(const HashAlgorithmType _hashAlgorithmType) {
				CString hashAlgorithmName = "";
				switch (_hashAlgorithmType) {
				case HASH_ALGORITHM_TYPE_MD4:
					hashAlgorithmName = "MD4";
					break;
				case HASH_ALGORITHM_TYPE_MD5:
					hashAlgorithmName = "MD5";
					break;
				case HASH_ALGORITHM_TYPE_RIPEMD160:
					hashAlgorithmName = "RIPEMD160";
					break;
				case HASH_ALGORITHM_TYPE_SHA:
					hashAlgorithmName = "SHA";
					break;
				case HASH_ALGORITHM_TYPE_SHA1:
					hashAlgorithmName = "SHA1";
					break;
				case HASH_ALGORITHM_TYPE_SHA224:
					hashAlgorithmName = "SHA224";
					break;
				case HASH_ALGORITHM_TYPE_SHA256:
					hashAlgorithmName = "SHA256";
					break;
				case HASH_ALGORITHM_TYPE_SHA384:
					hashAlgorithmName = "SHA384";
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					hashAlgorithmName = "SHA512";
					break;
				default:
					break;
				}
				return hashAlgorithmName;
			}

			int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType) {
				int hashAlgorithmBitLength = 0;
				switch (_hashAlgorithmType) {
				case HASH_ALGORITHM_TYPE_MD4:
					hashAlgorithmBitLength = 128;
					break;
				case HASH_ALGORITHM_TYPE_MD5:
					hashAlgorithmBitLength = 128;
					break;
				case HASH_ALGORITHM_TYPE_RIPEMD160:
					hashAlgorithmBitLength = 160;
					break;
				case HASH_ALGORITHM_TYPE_SHA:
					hashAlgorithmBitLength = 160;
					break;
				case HASH_ALGORITHM_TYPE_SHA1:
					hashAlgorithmBitLength = 160;
					break;
				case HASH_ALGORITHM_TYPE_SHA224:
					hashAlgorithmBitLength = 224;
					break;
				case HASH_ALGORITHM_TYPE_SHA256:
					hashAlgorithmBitLength = 256;
					break;
				case HASH_ALGORITHM_TYPE_SHA384:
					hashAlgorithmBitLength = 384;
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					hashAlgorithmBitLength = 512;
					break;
				default:
					break;
				}
				return hashAlgorithmBitLength;
			}

			HashOperation::HashOperation(const HashAlgorithmType _hashAlgorithmType, const CString &_fileNameSource, const CString &_fileNameTarget) :
				hashAlgorithmType(_hashAlgorithmType),
				fileNameSource(_fileNameSource),
				fileNameTarget(_fileNameTarget),
				context(0),
				fpInitialize(0),
				fpUpdate(0),
				fpFinalize(0) {
				// initialize OpenSSL context and function pointers depending on the specified hash algorithm type
				switch (hashAlgorithmType) {
				case HASH_ALGORITHM_TYPE_MD4:
					context = new unsigned char[sizeof(OpenSSL::MD4_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::MD4_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::MD4_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::MD4_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_MD5:
					context = new unsigned char[sizeof(OpenSSL::MD5_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::MD5_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::MD5_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::MD5_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_RIPEMD160:
					context = new unsigned char[sizeof(OpenSSL::RIPEMD160_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::RIPEMD160_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::RIPEMD160_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::RIPEMD160_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA:
					context = new unsigned char[sizeof(OpenSSL::SHA_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA1:
					context = new unsigned char[sizeof(OpenSSL::SHA_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA1_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA1_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA1_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA224:
					context = new unsigned char[sizeof(OpenSSL::SHA256_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA224_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA224_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA224_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA256:
					context = new unsigned char[sizeof(OpenSSL::SHA256_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA256_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA256_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA256_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA384:
					context = new unsigned char[sizeof(OpenSSL::SHA512_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA384_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA384_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA384_Final);
					delete context;
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					context = new unsigned char[sizeof(OpenSSL::SHA512_CTX)];
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA512_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA512_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA512_Final);
					delete context;
					break;
				default:
					break;
				}
				// make sure we have a valid OpenSSL function pointers for the specified hash function
				ASSERT(fpInitialize);
				ASSERT(fpUpdate);
				ASSERT(fpFinalize);
			}

			HashOperation::~HashOperation() {
				// deinitialize variables
				context = 0;
				fpInitialize = 0;
				fpUpdate = 0;
				fpFinalize = 0;
			}

			void HashOperation::execute(double *_progress) {
				// acquire the bit length of the desired hash algorithm
				const unsigned int hashAlgorithmBitLength = getHashAlgorithmBitLength(hashAlgorithmType);
				const unsigned int hashAlgorithmByteLength = (hashAlgorithmBitLength + 7) / 8;
				// this variable will store the resulting hash value
				unsigned char *digest = new unsigned char[hashAlgorithmByteLength];
				// the buffer size we're working with (the size of the chunks to be read from the source file)
				const unsigned int bufferByteLength = 4096;
				char *buffer = new char[bufferByteLength];
				// open the specified source file
				CFile fileSource;
				if (fileSource.Open(fileNameSource, CFile::modeRead)) {
					const ULONGLONG positionStart = 0;
					const ULONGLONG positionEnd = fileSource.GetLength();
					ULONGLONG positionCurrent = positionStart;
					ULONGLONG bytesRead;
					// the actual hash operation
					fpInitialize(context);
					while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
						fpUpdate(context, buffer, bytesRead);
						positionCurrent += bytesRead;
						if (_progress) {
							*_progress = (double)(positionCurrent) / (double)(positionEnd);
						}
					}
					fpFinalize(digest, context);
					// write the resulting hash value to the specified target file
					CFile fileTarget;
					if (fileTarget.Open(fileNameTarget, CFile::modeCreate | CFile::modeWrite)) {
						fileTarget.Write(digest, hashAlgorithmByteLength);
						fileTarget.Close();
					}
				}
				// free the memory for the resulting hash value
				delete digest;
				// free the memory for the buffer
				delete buffer;
			}

		}

	}

	DialogOperationController::DialogOperationController() :
		operationParameters(0),
		operationThread(0),
		operationProgress(0.0) {
		// create the dialog
		Create(IDD_SHOW_PROGRESS);
	}

	DialogOperationController::~DialogOperationController() {
		// clean up memory
		delete operationParameters;
	}

	void DialogOperationController::startHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
		// initialize operation parameters
		operationParameters = new OperationParametersHash(_hashAlgorithmType, _documentFileName, _documentTitle);
		// execute operation thread
		operationThread = AfxBeginThread(execute, this);
	}

	UINT DialogOperationController::execute(LPVOID _operationController) {
		// acquire the operation controller, the operation parameters, and the operation type
		DialogOperationController *controller = (DialogOperationController*)(_operationController);
		ASSERT(controller);
		OperationParameters *parameters = controller->operationParameters;
		ASSERT(parameters);
		const OperationType type = parameters->operationType;
		// execute the desired operation
		if (type == OPERATION_TYPE_HASH) {
			OperationParametersHash *parametersHash = (OperationParametersHash*)(parameters);
			ASSERT(parametersHash);
			// create a title for the dialog, and then make the dialog visible
			CString title;
			title.Format(IDS_PROGESS_COMPUTE_DIGEST, CrypTool::Cryptography::Hash::getHashAlgorithmName(parametersHash->hashAlgorithmType));
			controller->SetWindowText(title);
			controller->ShowWindow(SW_SHOW);
			// execute the operation
			CrypTool::Cryptography::Hash::HashOperation operation(parametersHash->hashAlgorithmType, parametersHash->documentFileName, Utilities::createTemporaryFile());
			operation.execute(&controller->operationProgress);
		}
		else if (type == OPERATION_TYPE_SYMMETRIC_ENCRYPTION) {
			// TODO/FIXME
		}
		else if (type == OPERATION_TYPE_ASYMMETRIC_ENCRYPTION) {
			// TODO/FIXME
		}
		else {
			controller->SendMessage(WM_CLOSE);
			AfxEndThread(-1);
			return -1;
		}
		controller->SendMessage(WM_CLOSE);
		AfxEndThread(0);
		return 0;
	}

	void DialogOperationController::OnClose() {
		CDialog::OnClose();
		DestroyWindow();
	}

	void DialogOperationController::PostNcDestroy() {
		CDialog::PostNcDestroy();
		delete this;
	}

	BEGIN_MESSAGE_MAP(DialogOperationController, CDialog)
		ON_WM_CLOSE()
	END_MESSAGE_MAP()

}