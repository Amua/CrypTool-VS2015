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
#include "CrypToolApp.h"
#include "resource.h"

namespace OpenSSL {
#include "OpenSSL/md4.h"
#include "OpenSSL/md5.h"
#include "OpenSSL/ripemd.h"
#include "OpenSSL/sha.h"
}

#include "DlgShowHash.h"

OctetString::OctetString() :
	noctets(0),
	octets(0) {

}

namespace CrypTool {

	ByteString::ByteString() :
		byteData(0),
		byteLength(0) {

	}

	ByteString::ByteString(const ByteString &_byteString) :
		byteData(0),
		byteLength(0) {
		reset(_byteString.byteLength);
		memcpy(byteData, _byteString.byteData, byteLength);
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
				byteData = new unsigned char[byteLength];
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

	size_t ByteString::fromBuffer(const unsigned char *_bufferData, const size_t _bufferLength) {
		if (!_bufferData) {
			return 0;
		}
		reset();
		byteLength = _bufferLength;
		byteData = new unsigned char[_bufferLength];
		std::memset(byteData, 0, byteLength);
		std::memcpy(byteData, _bufferData, byteLength);
		return byteLength;
	}

	size_t ByteString::toBuffer(unsigned char *_bufferData, const size_t _bufferLength) const {
		if (!_bufferData) {
			return 0;
		}
		if (_bufferLength > byteLength) {
			std::memcpy(_bufferData, byteData, byteLength);
			return byteLength;
		}
		else {
			std::memcpy(_bufferData, byteData, _bufferLength);
			return _bufferLength;
		}
	}

	void ByteString::fromString(const CString &_string) {
		reset(_string.GetLength());
		byteLength = _string.GetLength();
		unsigned char *buffer = (unsigned char*)(LPCTSTR)(_string);
		std::memcpy(byteData, buffer, byteLength);
	}

	CString ByteString::toString() const {
		CString result;
		for (size_t indexByte = 0; indexByte < byteLength; indexByte++) {
			const unsigned char byte = byteData[indexByte];
			if (byte == 0) {
				break;
			}
			result.AppendChar(byte);
		}
		return result;
	}

	CString ByteString::toString(const unsigned int _base, const CString &_separator) const {
		CString result;
		if (_base != 2 && _base != 8 && _base != 10 && _base != 16) {
			return result;
		}
		for (size_t indexByte = 0; indexByte < byteLength; indexByte++) {
			char byteConverted[8];
			std::memset(byteConverted, 0, 8);
			CString byteCovertedReversed;
			unsigned char byte = byteData[indexByte];
			unsigned int n = 255;
			for (unsigned int i = 0; n > 0; i++) {
				n /= _base;
				unsigned int modulo = byte % _base;
				byte /= _base;
				byteConverted[i] = (modulo >= 10) ? modulo - 10 + 'A' : modulo + '0';
				byteCovertedReversed.AppendChar(byteConverted[i]);
			}
			result += byteCovertedReversed.MakeReverse();
			result += _separator;
		}
		return result;
	}

	void ByteString::reset(const size_t _byteLength) {
		delete byteData;
		if (_byteLength > 0) {
			byteLength = _byteLength;
			byteData = new unsigned char[byteLength];
			std::memset(byteData, 0, byteLength);
		}
		else {
			byteData = 0;
			byteLength = 0;
		}
	}

	void ByteString::truncate(const size_t _byteLength) {
		if (_byteLength >= byteLength) {
			return;
		}
		else if (_byteLength == 0) {
			reset();
		}
		else {
			byteLength = _byteLength;
			unsigned char *byteDataNew = new unsigned char[byteLength];
			std::memcpy(byteDataNew, byteData, byteLength);
			delete byteData;
			byteData = byteDataNew;
		}
	}

	ByteString &ByteString::operator=(const ByteString &_byteString) {
		reset(_byteString.byteLength);
		std::memcpy(byteData, _byteString.byteData, byteLength);
		return *this;
	}

	ByteString &ByteString::operator+=(const ByteString &_byteString) {
		const ByteString byteStringOld = *this;
		reset(byteStringOld.byteLength + _byteString.byteLength);
		std::memcpy(byteData, byteStringOld.byteData, byteStringOld.byteLength);
		std::memcpy(byteData + byteStringOld.byteLength, _byteString.byteData, byteLength);
		return *this;
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
				case HASH_ALGORITHM_TYPE_SHA256:
					hashAlgorithmName = "SHA256";
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					hashAlgorithmName = "SHA512";
					break;
				default:
					break;
				}
				return hashAlgorithmName;
			}

			unsigned int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType) {
				unsigned int hashAlgorithmBitLength = 0;
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
				case HASH_ALGORITHM_TYPE_SHA256:
					hashAlgorithmBitLength = 256;
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					hashAlgorithmBitLength = 512;
					break;
				default:
					break;
				}
				return hashAlgorithmBitLength;
			}

			unsigned int getHashAlgorithmByteLength(const HashAlgorithmType _hashAlgorithmType) {
				const unsigned int hashAlgorithmByteLength = (unsigned int)((getHashAlgorithmBitLength(_hashAlgorithmType) + 7) / 8);
				return hashAlgorithmByteLength;
			}

			HashOperation::HashOperation(const HashAlgorithmType _hashAlgorithmType) :
				hashAlgorithmType(_hashAlgorithmType),
				contextSize(0),
				fpInitialize(0),
				fpUpdate(0),
				fpFinalize(0) {
				// initialize OpenSSL context and function pointers depending on the specified hash algorithm type
				switch (hashAlgorithmType) {
				case HASH_ALGORITHM_TYPE_MD4:
					contextSize = sizeof(OpenSSL::MD4_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::MD4_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::MD4_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::MD4_Final);
					break;
				case HASH_ALGORITHM_TYPE_MD5:
					contextSize = sizeof(OpenSSL::MD5_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::MD5_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::MD5_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::MD5_Final);
					break;
				case HASH_ALGORITHM_TYPE_RIPEMD160:
					contextSize = sizeof(OpenSSL::RIPEMD160_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::RIPEMD160_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::RIPEMD160_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::RIPEMD160_Final);
					break;
				case HASH_ALGORITHM_TYPE_SHA:
					contextSize = sizeof(OpenSSL::SHA_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA_Final);
					break;
				case HASH_ALGORITHM_TYPE_SHA1:
					contextSize = sizeof(OpenSSL::SHA_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA1_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA1_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA1_Final);
					break;
				case HASH_ALGORITHM_TYPE_SHA256:
					contextSize = sizeof(OpenSSL::SHA256_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA256_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA256_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA256_Final);
					break;
				case HASH_ALGORITHM_TYPE_SHA512:
					contextSize = sizeof(OpenSSL::SHA512_CTX);
					fpInitialize = (fpInitialize_t)(OpenSSL::SHA512_Init);
					fpUpdate = (fpUpdate_t)(OpenSSL::SHA512_Update);
					fpFinalize = (fpFinalize_t)(OpenSSL::SHA512_Final);
					break;
				default:
					break;
				}
				// make sure we have a valid OpenSSL variables
				ASSERT(contextSize);
				ASSERT(fpInitialize);
				ASSERT(fpUpdate);
				ASSERT(fpFinalize);
			}

			HashOperation::~HashOperation() {
				// deinitialize variables
				contextSize = 0;
				fpInitialize = 0;
				fpUpdate = 0;
				fpFinalize = 0;
			}

			void HashOperation::executeOnByteStrings(const ByteString &_byteStringMessage, ByteString &_byteStringDigest) {
				// acquire byte length of the desired hash algorithm
				const unsigned int hashAlgorithmByteLength = getHashAlgorithmByteLength(hashAlgorithmType);
				// prepare digest byte string to hold the resulting hash value
				_byteStringDigest.reset(hashAlgorithmByteLength);
				// create the OpenSSL context
				void *context = (void*)(new unsigned char[contextSize]);
				// the actual operation
				fpInitialize(context);
				fpUpdate(context, (void*)(_byteStringMessage.getByteDataConst()), _byteStringMessage.getByteLength());
				fpFinalize((void*)(_byteStringDigest.getByteData()), context);
				// free memory
				delete context;
			}

			void HashOperation::executeOnFiles(const CString &_fileNameMessage, const CString &_fileNameDigest, const bool *_cancelled, double *_progress) {
				// acquire byte length of the desired hash algorithm
				const unsigned int hashAlgorithmByteLength = getHashAlgorithmByteLength(hashAlgorithmType);
				// this variable will store the resulting hash value
				unsigned char *digest = new unsigned char[hashAlgorithmByteLength];
				// the buffer size we're working with (the size of the chunks to be read from the source file)
				const unsigned int bufferByteLength = 4096;
				char *buffer = new char[bufferByteLength];
				// create the OpenSSL context
				void *context = (void*)(new unsigned char[contextSize]);
				// open the specified source file
				CFile fileMessage;
				if (fileMessage.Open(_fileNameMessage, CFile::modeRead)) {
					const ULONGLONG positionStart = 0;
					const ULONGLONG positionEnd = fileMessage.GetLength();
					ULONGLONG positionCurrent = positionStart;
					ULONGLONG bytesRead;
					// the actual hash operation
					fpInitialize(context);
					while (bytesRead = fileMessage.Read(buffer, bufferByteLength)) {
						fpUpdate(context, buffer, bytesRead);
						positionCurrent += bytesRead;
						if (_cancelled) {
							if (*_cancelled) {
								break;
							}
						}
						if (_progress) {
							*_progress = (double)(positionCurrent) / (double)(positionEnd);
						}
					}
					fpFinalize(digest, context);
					// write the resulting hash value to the specified target file
					CFile fileDigest;
					if (fileDigest.Open(_fileNameDigest, CFile::modeCreate | CFile::modeWrite)) {
						fileDigest.Write(digest, hashAlgorithmByteLength);
						fileDigest.Close();
					}
				}
				// free memory
				delete context;
				delete digest;
				delete buffer;
			}

		}

	}

	namespace Functions {

		void executeHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
			// create the operation controller dialog (implicitly destroyed afterwards)
			CrypTool::Internal::DialogOperationController *dialogOperationController = new CrypTool::Internal::DialogOperationController();
			// create the appropriate title for the dialog, and make it visible
			CString title;
			title.Format(IDS_PROGESS_COMPUTE_DIGEST, CrypTool::Cryptography::Hash::getHashAlgorithmName(_hashAlgorithmType));
			dialogOperationController->SetWindowText(title);
			dialogOperationController->ShowWindow(SW_SHOW);
			// start the operation in its own thread
			dialogOperationController->startHashOperation(_hashAlgorithmType, _documentFileName, _documentTitle);
		}

		bool createKeyFromPasswordPKCS5(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const ByteString &_password, const ByteString &_salt, const int _iterations, const int _keyLength, ByteString &_key) {
			// the only supported algorithms right now are MD5 and SHA1 (MD2 is deprecated)
			std::vector<CrypTool::Cryptography::Hash::HashAlgorithmType> vectorHashAlgorithmTypes;
			vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD5);
			vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA1);
			if (!CrypTool::Utilities::vectorContains<CrypTool::Cryptography::Hash::HashAlgorithmType>(vectorHashAlgorithmTypes, _hashAlgorithmType)) {
				AfxMessageBox("TODO/FIXME: specified hash algorithm not supported (PKCS5)");
				return false;
			}
			// the number of iterations must be valid [1, 100000]
			if (_iterations < 1 || _iterations > 100000) {
				AfxMessageBox("TODO/FIXME: specified number of iterations not supported (PKCS5)");
				return false;
			}
			// the key length must be valid [1, byteLengthHash]
			if (_keyLength < 1 || _keyLength > CrypTool::Cryptography::Hash::getHashAlgorithmByteLength(_hashAlgorithmType)) {
				AfxMessageBox("TODO/FIXME: specified key length is not supported (PKCS5)");
				return false;
			}
			// create concatenation of password and salt
			ByteString byteStringPasswordAndSalt;
			byteStringPasswordAndSalt += _password;
			byteStringPasswordAndSalt += _salt;
			// create byte string for temporary hash value
			ByteString byteStringHashValue;
			// execute outer hash (hash of password and salt)
			CrypTool::Cryptography::Hash::HashOperation hashOperationOuter(_hashAlgorithmType);
			hashOperationOuter.executeOnByteStrings(byteStringPasswordAndSalt, byteStringHashValue);
			// execute inner hashes (hash of hash of hash...)
			for (int iteration = 1; iteration < _iterations; iteration++) {
				ByteString byteStringHashValueNew;
				CrypTool::Cryptography::Hash::HashOperation hashOperationInner(_hashAlgorithmType);
				hashOperationInner.executeOnByteStrings(byteStringHashValue, byteStringHashValueNew);
				byteStringHashValue = byteStringHashValueNew;
			}
			// truncate calculated hash value if necessary
			byteStringHashValue.truncate(CrypTool::Cryptography::Hash::getHashAlgorithmByteLength(_hashAlgorithmType));
			// assign result variable
			_key = byteStringHashValue;
			return true;
		}

	}

	namespace Internal {

		DialogOperationController::DialogOperationController() :
			operationThread(0),
			updateTimer(0),
			ID_TIMER_EVENT_UPDATE(WM_USER + 1) {
			// create the dialog
			Create(IDD_OPERATION_CONTROLLER);
		}

		DialogOperationController::~DialogOperationController() {
			if (operationThread) {
				WaitForSingleObject(operationThread->m_hThread, INFINITE);
			}
		}

		void DialogOperationController::startHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
			// initialize operation parameters
			parameters.parametersHash.hashAlgorithmType = _hashAlgorithmType;
			parameters.parametersHash.documentFileName = _documentFileName;
			parameters.parametersHash.documentTitle = _documentTitle;
			// mark the operation as started
			parameters.started = true;
			// start the update timer
			updateTimer = SetTimer(ID_TIMER_EVENT_UPDATE, 50, NULL);
			// start the operation thread
			operationThread = AfxBeginThread(executeHashOperation, &parameters);
		}

		UINT DialogOperationController::executeHashOperation(LPVOID _parameters) {
			// acquire the operation parameters
			Parameters *parameters = (Parameters*)(_parameters);
			ASSERT(parameters);
			// create a file name and a title for the new document, 
			// and update the parameters accordingly
			parameters->parametersHash.documentFileNameNew = Utilities::createTemporaryFile();
			parameters->parametersHash.documentTitleNew.Format(IDS_STRING_HASH_VALUE_OF, CrypTool::Cryptography::Hash::getHashAlgorithmName(parameters->parametersHash.hashAlgorithmType), parameters->parametersHash.documentTitle);
			// execute the operation
			CrypTool::Cryptography::Hash::HashOperation *operation = new CrypTool::Cryptography::Hash::HashOperation(parameters->parametersHash.hashAlgorithmType);
			operation->executeOnFiles(parameters->parametersHash.documentFileName, parameters->parametersHash.documentFileNameNew, &parameters->cancelled, &parameters->progress);
			delete operation;
			// mark the operation as finished
			parameters->finished = true;
			// start post-processing: read the result value into a byte string, and display the 
			// result value in the show hash dialog; if desired by the user, display the result 
			// in a new document
			ByteString byteStringHash;
			byteStringHash.readFromFile(parameters->parametersHash.documentFileNameNew);
			CDlgShowHash dlgShowHash;
			dlgShowHash.initialize(parameters->parametersHash.documentTitleNew, byteStringHash.toString(16, " "));
			if (dlgShowHash.DoModal() == IDOK) {
				theApp.ThreadOpenDocumentFileNoMRU(parameters->parametersHash.documentFileNameNew, parameters->parametersHash.documentTitleNew);
			}
			// mark the operation as done, and end the thread
			parameters->done = true;
			AfxEndThread(0);
			return 0;
		}

		BOOL DialogOperationController::OnInitDialog() {
			// call base class implementation
			CDialog::OnInitDialog();
			// initialize controls
			controlProgress.SetRange(0, 100);
			controlText.SetWindowText("");
			return FALSE;
		}

		void DialogOperationController::OnTimer(UINT_PTR _event) {
			if (_event == ID_TIMER_EVENT_UPDATE) {
				// update the progress
				controlProgress.SetPos((int)(parameters.progress * 100));
				// update the text
				controlText.SetWindowText("");
				// if the operation is finished, hide the dialog
				if (parameters.finished) {
					ShowWindow(SW_HIDE);
				}
				// if the operation is done, kill the timer and close the dialog
				if (parameters.done) {
					KillTimer(updateTimer);
					OnClose();
				}
				return;
			}
			CDialog::OnTimer(_event);
		}

		void DialogOperationController::OnCancel() {
			// mark the operation as done
			parameters.done = true;
		}

		void DialogOperationController::OnClose() {
			// destroy the window after the dialog has been closed
			CDialog::OnClose();
			DestroyWindow();
		}

		void DialogOperationController::PostNcDestroy() {
			// this workaround is required as this dialog bas been created on the heap
			CDialog::PostNcDestroy();
			delete this;
		}

		void DialogOperationController::DoDataExchange(CDataExchange *_pDX) {
			CDialog::DoDataExchange(_pDX);
			DDX_Control(_pDX, IDC_PROGRESS_BAR, controlProgress);
			DDX_Control(_pDX, IDC_TEXT, controlText);
		}

		BEGIN_MESSAGE_MAP(DialogOperationController, CDialog)
			ON_WM_TIMER()
			ON_WM_CLOSE()
		END_MESSAGE_MAP()

	}

}