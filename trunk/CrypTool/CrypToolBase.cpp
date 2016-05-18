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

	ByteString::ByteString(const size_t _byteLength) :
		byteData(0),
		byteLength(0) {
		if (_byteLength > 0) {
			byteLength = _byteLength;
			byteData = new unsigned char[byteLength];
			std::memset(byteData, 0, byteLength);
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

	size_t ByteString::fromOctetString(OctetString *_octetString) {
		return fromBuffer((unsigned char*)(_octetString->octets), _octetString->noctets);
	}

	size_t ByteString::toOctetString(OctetString *_octetString) const {
		return toBuffer((unsigned char*)(_octetString->octets), _octetString->noctets);
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

	CString ByteString::toStringHex(const CString &_separator) const {
		CString stringHex;
		for (size_t index = 0; index < byteLength; index++) {
			unsigned char byte = byteData[index];
			char byteLo;
			char byteHi;
			if ((byte % 16) < 10) byteHi = '0' + (byte % 16);
			else byteHi = 'A' + (byte % 16) - 10;
			byte /= 16;
			if (byte < 10) byteLo = '0' + byte;
			else byteLo = 'A' + byte - 10;
			stringHex += byteLo;
			stringHex += byteHi;
			if (index < byteLength + 1) stringHex += _separator;
		}
		return stringHex;
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

			HashOperation::HashOperation(const HashAlgorithmType _hashAlgorithmType, const CString &_fileNameSource, const CString &_fileNameTarget) :
				hashAlgorithmType(_hashAlgorithmType),
				fileNameSource(_fileNameSource),
				fileNameTarget(_fileNameTarget),
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

			void HashOperation::execute(const bool *_cancelled, double *_progress) {
				// acquire the bit length of the desired hash algorithm
				const unsigned int hashAlgorithmBitLength = getHashAlgorithmBitLength(hashAlgorithmType);
				const unsigned int hashAlgorithmByteLength = (hashAlgorithmBitLength + 7) / 8;
				// this variable will store the resulting hash value
				unsigned char *digest = new unsigned char[hashAlgorithmByteLength];
				// the buffer size we're working with (the size of the chunks to be read from the source file)
				const unsigned int bufferByteLength = 4096;
				char *buffer = new char[bufferByteLength];
				// create the OpenSSL context
				void *context = (void*)(new unsigned char[contextSize]);
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
					CFile fileTarget;
					if (fileTarget.Open(fileNameTarget, CFile::modeCreate | CFile::modeWrite)) {
						fileTarget.Write(digest, hashAlgorithmByteLength);
						fileTarget.Close();
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
			CrypTool::Cryptography::Hash::HashOperation *operation = new CrypTool::Cryptography::Hash::HashOperation(parameters->parametersHash.hashAlgorithmType, parameters->parametersHash.documentFileName, parameters->parametersHash.documentFileNameNew);
			operation->execute(&parameters->cancelled, &parameters->progress);
			delete operation;
			// mark the operation as finished
			parameters->finished = true;
			// start post-processing: read the result value into a byte string, and display the 
			// result value in the show hash dialog; if desired by the user, display the result 
			// in a new document
			ByteString byteStringHash;
			byteStringHash.readFromFile(parameters->parametersHash.documentFileNameNew);
			CDlgShowHash dlgShowHash;
			dlgShowHash.initialize(parameters->parametersHash.documentTitleNew, byteStringHash.toStringHex(" "));
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