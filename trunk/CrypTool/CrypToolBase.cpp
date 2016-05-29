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
#include "Cryptography.h"
#include "resource.h"

#include "DlgShowHash.h"
#include "DlgKeyHexFixedLen.h"

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
		std::memcpy(byteData, _byteString.byteData, byteLength);
	}

	ByteString::ByteString(const size_t _byteLength) :
		byteData(0),
		byteLength(0) {
		reset(_byteLength);
	}

	ByteString::ByteString(const unsigned char *_byteData, const size_t _byteLength) :
		byteData(0),
		byteLength(0) {
		fromBuffer(_byteData, _byteLength);
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
		std::memcpy(byteData + byteStringOld.byteLength, _byteString.byteData, _byteString.byteLength);
		return *this;
	}

	CString getCrypToolPath() {
		// acquire the module file name, which is the full path to the CrypTool 
		// executable including "\\CrypTool.exe"
		char buffer[_MAX_PATH];
		GetModuleFileName(AfxGetApp()->m_hInstance, buffer, _MAX_PATH);
		CString path = buffer;
		// here we remove the trailing "\\CrypTool.exe" part
		const int indexTrailingSlashes = path.ReverseFind('\\');
		if (indexTrailingSlashes > 0) {
			path = path.Left(indexTrailingSlashes);
		}
		return path;
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

		size_t truncateByteString(ByteString &_byteString, const unsigned int _truncateAtLength, const bool _truncateAtFirstNullByte) {
			// if the byte string contains null bytes, notify user and truncate it
			if (_truncateAtFirstNullByte) {
				for (size_t index = 0; index < _byteString.getByteLength(); index++) {
					const unsigned char currentByte = _byteString.getByteData()[index];
					if (currentByte == 0) {
						CString message;
						message.Format("CRYPTOOL_BASE: null bytes not allowed, string is truncated");
						AfxMessageBox(message, MB_ICONEXCLAMATION);
						_byteString.truncate(index);
						break;
					}
				}
			}
			// if the byte string exceeds the specified length, notify user and truncate it
			if (_byteString.getByteLength() > _truncateAtLength) {
				CString message;
				message.Format("CRYPTOOL_BASE: string length exceeded, string is truncated to %d bytes", _truncateAtLength);
				AfxMessageBox(message, MB_ICONEXCLAMATION);
				// truncate the byte string
				_byteString.truncate(_truncateAtLength);
			}
			// return the length of the resulting byte string
			return _byteString.getByteLength();
		}

		void extractElementsFromBracketedString(const CString &_input, const CString &_openingBracket, const CString &_closingBracket, std::vector<CString> &_vectorElements) {
			// we need a copy of the original string we can manipulate
			CString input = _input;
			// now go through the string and extract the elements
			while (true) {
				const int indexOpeningBracket = input.Find(_openingBracket);
				const int indexClosingBracket = input.Find(_closingBracket);
				if (indexOpeningBracket == -1) break;
				if (indexClosingBracket == -1) break;
				if (indexOpeningBracket >= indexClosingBracket) break;
				CString element = input;
				// delete portion after the closing bracket (including the closing bracket)
				element = element.Left(indexClosingBracket);
				// delete portion before the opening bracket (including the opening bracket)
				element = element.Right(element.GetLength() - indexOpeningBracket - _openingBracket.GetLength());
				// update the output variable
				_vectorElements.push_back(element);
				// don't forget to truncate the input string
				input = input.Right(input.GetLength() - indexClosingBracket - _closingBracket.GetLength());
			}
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
				// initialize context size and OpenSSL function pointers depending on the specified hash algorithm type
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
				// make sure we have valid OpenSSL variables
				ASSERT(contextSize);
				ASSERT(fpInitialize);
				ASSERT(fpUpdate);
				ASSERT(fpFinalize);
			}

			HashOperation::~HashOperation() {
				// deinitialize OpenSSL variables
				contextSize = 0;
				fpInitialize = 0;
				fpUpdate = 0;
				fpFinalize = 0;
			}

			bool HashOperation::executeOnByteStrings(const ByteString &_byteStringInput, ByteString &_byteStringOutput) {
				// acquire byte length of the desired hash algorithm
				const unsigned int hashAlgorithmByteLength = getHashAlgorithmByteLength(hashAlgorithmType);
				// prepare output byte string to hold the resulting hash value
				_byteStringOutput.reset(hashAlgorithmByteLength);
				// create the OpenSSL context
				void *context = (void*)(new unsigned char[contextSize]);
				// the actual operation
				ASSERT(fpInitialize(context));
				ASSERT(fpUpdate(context, (void*)(_byteStringInput.getByteDataConst()), _byteStringInput.getByteLength()));
				ASSERT(fpFinalize((void*)(_byteStringOutput.getByteData()), context));
				// free memory
				delete context;
				// return without errors
				return true;
			}

			bool HashOperation::executeOnFiles(const CString &_fileNameInput, const CString &_fileNameOutput, const bool *_cancelled, double *_progress) {
				// try to open files
				CFile fileInput;
				CFile fileOutput;
				// try to open the input file for reading
				if (!fileInput.Open(_fileNameInput, CFile::modeRead)) {
					return false;
				}
				// try to open the output file for writing
				if (!fileOutput.Open(_fileNameOutput, CFile::modeCreate | CFile::modeWrite)) {
					return false;
				}
				// acquire byte length of the desired hash algorithm
				const unsigned int hashAlgorithmByteLength = getHashAlgorithmByteLength(hashAlgorithmType);
				// this variable will store the resulting hash value
				unsigned char *output = new unsigned char[hashAlgorithmByteLength];
				// the buffer size we're working with (the size of the chunks to be read from the input file)
				const unsigned int bufferByteLength = 4096;
				char *buffer = new char[bufferByteLength];
				// create the OpenSSL context
				void *context = (void*)(new unsigned char[contextSize]);
				// initialize some internal variables
				const ULONGLONG positionStart = 0;
				const ULONGLONG positionEnd = fileInput.GetLength();
				ULONGLONG positionCurrent = positionStart;
				ULONGLONG bytesRead;
				// the actual hash operation
				ASSERT(fpInitialize(context));
				while (bytesRead = fileInput.Read(buffer, bufferByteLength)) {
					ASSERT(fpUpdate(context, buffer, bytesRead));
					positionCurrent += bytesRead;
					if (_cancelled) {
						if (*_cancelled) {
							// free memory
							delete context;
							delete output;
							delete buffer;
							return false;
						}
					}
					if (_progress) {
						*_progress = (double)(positionCurrent) / (double)(positionEnd);
					}
				}
				ASSERT(fpFinalize(output, context));
				// write the resulting hash value to the output file
				fileOutput.Write(output, hashAlgorithmByteLength);
				// free memory
				delete context;
				delete output;
				delete buffer;
				return true;
			}

		}

		namespace Symmetric {

			CString getSymmetricAlgorithmName(const SymmetricAlgorithmType _symmetricAlgorithmType) {
				CString symmetricAlgorithmName = "";
				switch (_symmetricAlgorithmType) {
				case SYMMETRIC_ALGORITHM_TYPE_IDEA:
					symmetricAlgorithmName = "IDEA";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_RC2:
					symmetricAlgorithmName = "RC2";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_RC4:
					symmetricAlgorithmName = "RC4";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DES_ECB:
					symmetricAlgorithmName = "DES (ECB)";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DES_CBC:
					symmetricAlgorithmName = "DES (CBC)";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_ECB:
					symmetricAlgorithmName = "Triple-DES (ECB)";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_CBC:
					symmetricAlgorithmName = "Triple-DES (CBC)";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_AES:
					symmetricAlgorithmName = "AES";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_MARS:
					symmetricAlgorithmName = "MARS";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_RC6:
					symmetricAlgorithmName = "RC6";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_SERPENT:
					symmetricAlgorithmName = "Serpent";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_TWOFISH:
					symmetricAlgorithmName = "Twofish";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESX:
					symmetricAlgorithmName = "DESX";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESL:
					symmetricAlgorithmName = "DESL";
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESXL:
					symmetricAlgorithmName = "DESXL";
					break;
				default:
					break;
				}
				return symmetricAlgorithmName;
			}

			SymmetricOperation::SymmetricOperation(const SymmetricAlgorithmType _symmetricAlgorithmType, const SymmetricOperationType _symmetricOperationType) :
				symmetricAlgorithmType(_symmetricAlgorithmType),
				symmetricOperationType(_symmetricOperationType),
				context(0),
				fpInitialize(0),
				fpUpdate(0),
				fpFinalize(0) {
				// initialize OpenSSL function pointers depending on the specified symmetric operation type
				switch (symmetricOperationType) {
				case SYMMETRIC_OPERATION_TYPE_ENCRYPTION:
					context = OpenSSL::EVP_CIPHER_CTX_new();
					fpInitialize = (fpInitialize_t)(OpenSSL::EVP_EncryptInit);
					fpUpdate = (fpUpdate_t)(OpenSSL::EVP_EncryptUpdate);
					fpFinalize = (fpFinalize_t)(OpenSSL::EVP_EncryptFinal);
					break;
				case SYMMETRIC_OPERATION_TYPE_DECRYPTION:
					context = OpenSSL::EVP_CIPHER_CTX_new();
					fpInitialize = (fpInitialize_t)(OpenSSL::EVP_DecryptInit);
					fpUpdate = (fpUpdate_t)(OpenSSL::EVP_DecryptUpdate);
					fpFinalize = (fpFinalize_t)(OpenSSL::EVP_DecryptFinal);
					break;
				default:
					break;
				}
				// make sure we have valid OpenSSL variables
				ASSERT(context);
				ASSERT(fpInitialize);
				ASSERT(fpUpdate);
				ASSERT(fpFinalize);
			}

			SymmetricOperation::~SymmetricOperation() {
				// deinitialize OpenSSL variables
				OpenSSL::EVP_CIPHER_CTX_free(context);
				context = 0;
				fpInitialize = 0;
				fpUpdate = 0;
				fpFinalize = 0;
			}

			bool SymmetricOperation::executeOnByteStrings(const ByteString &_byteStringInput, const ByteString &_byteStringKey, ByteString &_byteStringOutput) {
				using namespace OpenSSL;
				// make sure we have a valid cipher
				const EVP_CIPHER *cipher = getOpenSSLCipher(symmetricAlgorithmType, _byteStringKey.getByteLength());
				if (!cipher) return false;
				// acquire iv length, key length, block size
				const int cipherIvLength = EVP_CIPHER_iv_length(cipher);
				const int cipherKeyLength = EVP_CIPHER_key_length(cipher);
				const int cipherBlockSize = EVP_CIPHER_block_size(cipher);
				// create variables for iv, key (all zero bytes)
				unsigned char *iv = new unsigned char[cipherIvLength];
				std::memset(iv, 0, cipherIvLength);
				unsigned char *key = new unsigned char[cipherKeyLength];
				std::memset(key, 0, cipherKeyLength);
				// create variables for input, output, final (all zero bytes)
				unsigned char *input = new unsigned char[_byteStringInput.getByteLength()];
				std::memset(input, 0, _byteStringInput.getByteLength());
				unsigned char *output = new unsigned char[_byteStringInput.getByteLength() + cipherBlockSize];
				std::memset(output, 0, _byteStringInput.getByteLength() + cipherBlockSize);
				unsigned char *final = new unsigned char[cipherBlockSize];
				std::memset(final, 0, cipherBlockSize);
				// initialize variables for input length, output length, final length (all zero)
				int inputLength = _byteStringInput.getByteLength();
				int outputLength = 0;
				int finalLength = 0;
				// temporary byte strings for concatenating
				ByteString byteStringUpdate;
				ByteString byteStringFinalize;
				// initialize iv, key, input
				std::memset(iv, 0, cipherIvLength);
				std::memcpy(key, _byteStringKey.getByteDataConst(), _byteStringKey.getByteLength());
				std::memcpy(input, _byteStringInput.getByteDataConst(), _byteStringInput.getByteLength());
				// encryption/decryption (initialize, update, finalize)
				ASSERT(fpInitialize(context, cipher, key, iv));
				ASSERT(fpUpdate(context, output, &outputLength, input, inputLength));
				byteStringUpdate.fromBuffer(output, outputLength);
				ASSERT(fpFinalize(context, final, &finalLength));
				byteStringFinalize.fromBuffer(final, finalLength);
				// set output byte string
				_byteStringOutput += byteStringUpdate;
				_byteStringOutput += byteStringFinalize;
				// free memory
				delete iv;
				delete key;
				delete input;
				delete output;
				delete final;
				return true;
			}

			bool SymmetricOperation::executeOnFiles(const CString &_fileNameInput, const CString &_fileNameOutput, const ByteString &_byteStringKey, const bool *_cancelled, double *_progress) {
				using namespace OpenSSL;
				// make sure we have a valid cipher
				const EVP_CIPHER *cipher = getOpenSSLCipher(symmetricAlgorithmType, _byteStringKey.getByteLength());
				if (!cipher) return false;
				// try to open files
				CFile fileInput;
				CFile fileOutput;
				// try to open the input file for reading
				if (!fileInput.Open(_fileNameInput, CFile::modeRead)) {
					return false;
				}
				// try to open the output file for writing
				if (!fileOutput.Open(_fileNameOutput, CFile::modeCreate | CFile::modeWrite)) {
					return false;
				}
				// the buffer size we're working with (the size of the chunks to be read from the input file)
				const unsigned int bufferByteLength = 4096;
				// acquire iv length, key length, block size
				const int cipherIvLength = EVP_CIPHER_iv_length(cipher);
				const int cipherKeyLength = EVP_CIPHER_key_length(cipher);
				const int cipherBlockSize = EVP_CIPHER_block_size(cipher);
				// create variables for iv, key (all zero bytes)
				unsigned char *iv = new unsigned char[cipherIvLength];
				std::memset(iv, 0, cipherIvLength);
				unsigned char *key = new unsigned char[cipherKeyLength];
				std::memset(key, 0, cipherKeyLength);
				// create variables for input, output, final (all zero bytes)
				unsigned char *input = new unsigned char[bufferByteLength];
				std::memset(input, 0, bufferByteLength);
				unsigned char *output = new unsigned char[bufferByteLength + cipherBlockSize];
				std::memset(output, 0, bufferByteLength + cipherBlockSize);
				unsigned char *final = new unsigned char[cipherBlockSize];
				std::memset(final, 0, cipherBlockSize);
				// initialize variables for input length, output length, final length (all zero)
				int inputLength = bufferByteLength;
				int outputLength = 0;
				int finalLength = 0;
				// initialize iv, key, input
				std::memset(iv, 0, cipherIvLength);
				std::memcpy(key, _byteStringKey.getByteDataConst(), _byteStringKey.getByteLength());
				// encryption/decryption (initialize);
				ASSERT(fpInitialize(context, cipher, key, iv));
				// initialize some internal variables
				const ULONGLONG positionStart = 0;
				const ULONGLONG positionEnd = fileInput.GetLength();
				ULONGLONG positionCurrent = positionStart;
				ULONGLONG bytesRead;
				while (bytesRead = fileInput.Read(input, bufferByteLength)) {
					ASSERT(fpUpdate(context, output, &outputLength, input, (int)(bytesRead)));
					fileOutput.Write(output, outputLength);
					positionCurrent += bytesRead;
					if (_cancelled) {
						if (*_cancelled) {
							// free memory
							delete iv;
							delete key;
							delete input;
							delete output;
							delete final;
							return false;
						}
					}
					if (_progress) {
						*_progress = (double)(positionCurrent) / (double)(positionEnd);
					}
				}
				// ecryption/decryption (finalize)
				ASSERT(fpFinalize(context, final, &finalLength));
				fileOutput.Write(final, finalLength);
				// free memory
				delete iv;
				delete key;
				delete input;
				delete output;
				delete final;
				return true;
			}

			const OpenSSL::EVP_CIPHER *SymmetricOperation::getOpenSSLCipher(const SymmetricAlgorithmType _symmetricAlgorithmType, const size_t _keyLength) const {
				switch (_symmetricAlgorithmType) {
				case SYMMETRIC_ALGORITHM_TYPE_IDEA:
					return OpenSSL::EVP_idea_ecb();
				case SYMMETRIC_ALGORITHM_TYPE_RC2:
					return OpenSSL::EVP_rc2_cbc();
				case SYMMETRIC_ALGORITHM_TYPE_RC4:
					return OpenSSL::EVP_rc4();
				case SYMMETRIC_ALGORITHM_TYPE_DES_ECB:
					return OpenSSL::EVP_des_ecb();
				case SYMMETRIC_ALGORITHM_TYPE_DES_CBC:
					return OpenSSL::EVP_des_cbc();
				case SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_ECB:
					return OpenSSL::EVP_des_ede3_ecb();
				case SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_CBC:
					return OpenSSL::EVP_des_ede3_cbc();
				case SYMMETRIC_ALGORITHM_TYPE_AES:
					if (_keyLength == 16) return OpenSSL::EVP_aes_128_cbc();
					if (_keyLength == 24) return OpenSSL::EVP_aes_192_cbc();
					if (_keyLength == 32) return OpenSSL::EVP_aes_256_cbc();
					break;
				case SYMMETRIC_ALGORITHM_TYPE_MARS:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_RC6:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_SERPENT:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_TWOFISH:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESX:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESL:
					break;
				case SYMMETRIC_ALGORITHM_TYPE_DESXL:
					break;
				default:
					break;
				}
				AfxMessageBox("CRYPTOOL_BASE: SymmetricOperation::getCipher -> OpenSSL cipher invalid");
				return 0;
			}

		}

		namespace Asymmetric {

			CertificateStore::CertificateStore() :
				pathToCertificateStore(getCrypToolPath() + "\\certificates"),
				fileNameCaCertificate(getCrypToolPath() + "\\certificates\\ca\\CrypToolCA.crt"),
				fileNameCaPrivateKey(getCrypToolPath() + "\\certificates\\ca\\CrypToolCA.key"),
				caCertificate(0),
				caPrivateKey(0) {
				
			}

			CertificateStore::~CertificateStore() {
				
			}

			CertificateStore &CertificateStore::instance() {
				static CertificateStore certificateStore;
				return certificateStore;
			}

			void CertificateStore::initialize(const CString &_caPassword) {
				using namespace OpenSSL;
				// before doing anything else, we need to propertly initialize 
				// all available OpenSSL algorithms, otherwise the initialization 
				// of the CrypTool certificate store will fail
				OpenSSL_add_all_algorithms();
				// try to read the CA's certificate and private key
				BIO *bioCertificate = BIO_new(BIO_s_file());
				BIO *bioPrivateKey = BIO_new(BIO_s_file());
				if (BIO_read_filename(bioCertificate, (LPCTSTR)(fileNameCaCertificate)) && BIO_read_filename(bioPrivateKey, (LPCTSTR)(fileNameCaPrivateKey))) {
					caCertificate = PEM_read_bio_X509(bioCertificate, 0, 0, 0);
					caPrivateKey = PEM_read_bio_RSAPrivateKey(bioPrivateKey, 0, 0, (void*)(LPCTSTR)(_caPassword));
				}
				BIO_free(bioCertificate);
				BIO_free(bioPrivateKey);
				// if the CA's certificate and private key are still null, something went wrong
				if (!caCertificate || !caPrivateKey) {
					AfxMessageBox("CRYPTOOL_BASE: cannot initialize CrypTool certificate store");
				}
				// load all user certificates after certificate store initialization
				else {
					loadUserCertificates();
				}
			}

			void CertificateStore::deinitialize() {
				using namespace OpenSSL;
				// free previously allocated memory
				X509_free(caCertificate);
				RSA_free(caPrivateKey);
				// unload all user certificates
				unloadUserCertificates();
			}

			int CertificateStore::getCustomCrypToolExtensionIdentifier() const {
				using namespace OpenSSL;
				// ATTENTION: not sure whether this identifier interferes with anything else, 
				// but at least the implementation is working; don't touch the following lines 
				// unless you're absolutely positive you know what you're doing
				const int customCrypToolExtensionIdentifier = OBJ_create("1.2.3.4.5", "CCTX", "Custom CrypTool Extension");
				return customCrypToolExtensionIdentifier;
			}

			bool CertificateStore::createUserCertificate(const CertificateType _certificateType, const CString &_certificateParameters, const CString &_firstName, const CString &_lastName, const CString &_remarks, const CString &_password) {
				using namespace OpenSSL;
				// both the CA certificate and the CA private key need to be valid
				if (!caCertificate || !caPrivateKey) {
					return false;
				}
				// extract signing key from CA private key
				EVP_PKEY *signingKey = EVP_PKEY_new();
				EVP_PKEY_set1_RSA(signingKey, caPrivateKey);
				// allocate memory
				X509 *certificate = X509_new();
				EVP_PKEY *pkey = EVP_PKEY_new();
				// create the certificate serial number: for convenience, we simply use the number 
				// of seconds passed since the unix epoch (1970/01/01), and we insert a one second 
				// delay at the end of this function to prevent duplicate serial numbers
				const long serial = (long)(time(0));
				// set certificate version and serial number
				X509_set_version(certificate, 2);
				ASN1_INTEGER_set(X509_get_serialNumber(certificate), serial);
				// set certificate validity (one year from now)
				const long timeNotBefore = 0;
				const long timeNotAfter = 60 * 60 * 24 * 365;
				X509_gmtime_adj(X509_get_notBefore(certificate), timeNotBefore);
				X509_gmtime_adj(X509_get_notAfter(certificate), timeNotAfter);
				// set certificate type (i.e. "RSA-512", "DSA-1024", or "ECC-prime192v1")
				CString certificateType;
				if (_certificateType == CERTIFICATE_TYPE_RSA) certificateType = "RSA-" + _certificateParameters;
				if (_certificateType == CERTIFICATE_TYPE_DSA) certificateType = "DSA-" + _certificateParameters;
				if (_certificateType == CERTIFICATE_TYPE_ECC) certificateType = "ECC-" + _certificateParameters;
				// set certificate issuer name
				X509_set_issuer_name(certificate, X509_get_subject_name(caCertificate));
				// set certificate data (C, L, O, CN)
				const CString certificateDataC = "DE";
				const CString certificateDataL = "Frankfurt";
				const CString certificateDataO = "CrypTool Team";
				CString certificateDataCN; certificateDataCN.Format("User Certificate #%d", serial);
				// assign certificate data (C, L, O, CN)
				X509_NAME_add_entry_by_txt(X509_get_subject_name(certificate), "C", MBSTRING_ASC, (const unsigned char*)(LPCTSTR)(certificateDataC), -1, -1, 0);
				X509_NAME_add_entry_by_txt(X509_get_subject_name(certificate), "L", MBSTRING_ASC, (const unsigned char*)(LPCTSTR)(certificateDataL), -1, -1, 0);
				X509_NAME_add_entry_by_txt(X509_get_subject_name(certificate), "O", MBSTRING_ASC, (const unsigned char*)(LPCTSTR)(certificateDataO), -1, -1, 0);
				X509_NAME_add_entry_by_txt(X509_get_subject_name(certificate), "CN", MBSTRING_ASC, (const unsigned char*)(LPCTSTR)(certificateDataCN), -1, -1, 0);
				// add custom CrypTool extension
				if (!CertificateManipulator::writeCustomCrypToolExtension(certificate, _firstName, _lastName, _remarks, certificateType)) {
					return false;
				}
				// generate file names for the certificate and the private key
				CString fileNameUserCertificate;
				CString fileNameUserPrivateKey;
				generateFileNamesForUserCertificateAndUserPrivateKey(serial, fileNameUserCertificate, fileNameUserPrivateKey);
				// the internal result variable
				bool result = false;
				// RSA-based certificate
				if (_certificateType == CERTIFICATE_TYPE_RSA) {
					// determine the specified key length
					const int keyLength = atoi(_certificateParameters);
					// allocate memory
					RSA *rsa = RSA_new();
					BIGNUM *exponent = BN_new();
					// generate RSA key
					if (BN_set_word(exponent, RSA_F4)) {
						if (RSA_generate_key_ex(rsa, keyLength, exponent, 0)) {
							// set RSA private key
							EVP_PKEY_set1_RSA(pkey, rsa);
							// set RSA public key
							X509_set_pubkey(certificate, pkey);
							// sign certificate with the private key of the CrypTool CA
							X509_sign(certificate, signingKey, EVP_sha1());
							// write user's certificate and private key
							BIO *bioCertificate = BIO_new(BIO_s_file());
							BIO *bioPrivateKey = BIO_new(BIO_s_file());
							if (BIO_write_filename(bioCertificate, (void*)(LPCTSTR)(fileNameUserCertificate)) && BIO_write_filename(bioPrivateKey, (void*)(LPCTSTR)(fileNameUserPrivateKey))) {
								if (PEM_write_bio_X509(bioCertificate, certificate) && PEM_write_bio_RSAPrivateKey(bioPrivateKey, rsa, EVP_aes_256_cbc(), 0, 0, 0, (void*)(LPCTSTR)(_password))) {
									result = true;
								}
							}
							BIO_free(bioCertificate);
							BIO_free(bioPrivateKey);
						}
					}
					// free memory
					RSA_free(rsa);
					BN_free(exponent);
				}
				// DSA-based certificate
				if (_certificateType == CERTIFICATE_TYPE_DSA) {
					// determine the specified key length
					const int keyLength = atoi(_certificateParameters);
					// allocate memory
					DSA *dsa = DSA_new();
					// generate DSA parameters
					if (DSA_generate_parameters_ex(dsa, keyLength, NULL, 0, NULL, NULL, NULL)) {
						// generate DSA key
						if (DSA_generate_key(dsa)) {
							// set DSA private key
							EVP_PKEY_set1_DSA(pkey, dsa);
							// set DSA public key
							X509_set_pubkey(certificate, pkey);
							// sign certificate with the private key of the CrypTool CA
							X509_sign(certificate, signingKey, EVP_sha1());
							// write user's certificate and private key
							BIO *bioCertificate = BIO_new(BIO_s_file());
							BIO *bioPrivateKey = BIO_new(BIO_s_file());
							if (BIO_write_filename(bioCertificate, (void*)(LPCTSTR)(fileNameUserCertificate)) && BIO_write_filename(bioPrivateKey, (void*)(LPCTSTR)(fileNameUserPrivateKey))) {
								if (PEM_write_bio_X509(bioCertificate, certificate) && PEM_write_bio_DSAPrivateKey(bioPrivateKey, dsa, EVP_aes_256_cbc(), 0, 0, 0, (void*)(LPCTSTR)(_password))) {
									result = true;
								}
							}
							BIO_free(bioCertificate);
							BIO_free(bioPrivateKey);
						}
					}
					// free memory
					DSA_free(dsa);
				}
				// ECC-based certificate
				if (_certificateType == CERTIFICATE_TYPE_ECC) {
					// determine the specified curve name
					const CString curveName = _certificateParameters;
					// generate EC key
					EC_KEY *ec = EC_KEY_new_by_curve_name(OBJ_txt2nid(curveName));
					if (ec) {
						if (EC_KEY_generate_key(ec)) {
							// set EC private key
							EVP_PKEY_set1_EC_KEY(pkey, ec);
							// set EC public key
							X509_set_pubkey(certificate, pkey);
							// sign certificate with the private key of the CrypTool CA
							X509_sign(certificate, signingKey, EVP_sha1());
							// write user's certificate and private key
							BIO *bioCertificate = BIO_new(BIO_s_file());
							BIO *bioPrivateKey = BIO_new(BIO_s_file());
							if (BIO_write_filename(bioCertificate, (void*)(LPCTSTR)(fileNameUserCertificate)) && BIO_write_filename(bioPrivateKey, (void*)(LPCTSTR)(fileNameUserPrivateKey))) {
								if (PEM_write_bio_X509(bioCertificate, certificate) && PEM_write_bio_ECPrivateKey(bioPrivateKey, ec, EVP_aes_256_cbc(), 0, 0, 0, (void*)(LPCTSTR)(_password))) {
									result = true;
								}
							}
							BIO_free(bioCertificate);
							BIO_free(bioPrivateKey);
						}
					}
					// free memory
					EC_KEY_free(ec);
				}
				// free memory
				EVP_PKEY_free(signingKey);
				X509_free(certificate);
				EVP_PKEY_free(pkey);
				// dump an error message before returning false
				if (!result) {
					AfxMessageBox("CRYPTOOL_BASE: user certificate creation failed");
					return false;
				}
				// we add this delay so we don't get duplicate certificate serial numbers
				Sleep(1000);
				// re-load all user certificates after a certificate was created
				loadUserCertificates();
				// if we reach this point, everything went well
				return true;
			}

			bool CertificateStore::deleteUserCertificate(const long _serial, const CString &_password) {
				// the first thing we need to do is check whether there is a certificate with the 
				// specified serial at all; if not, dump a warning message and return false
				if (mapUserCertificates.find(_serial) == mapUserCertificates.end()) {
					AfxMessageBox("CRYPTOOL_BASE: no certificate with the specified serial exists");
					return false;
				}
				// generate file names for the certificate and the private key
				CString fileNameUserCertificate;
				CString fileNameUserPrivateKey;
				generateFileNamesForUserCertificateAndUserPrivateKey(_serial, fileNameUserCertificate, fileNameUserPrivateKey);
				// here we check whether the generated file names actually point to valid files; 
				// if not, we also dump and warning message and return false
				CFileFind finderUserCertificate;
				CFileFind finderUserPrivateKey;
				if (!finderUserCertificate.FindFile(fileNameUserCertificate) || !finderUserPrivateKey.FindFile(fileNameCaPrivateKey)) {
					AfxMessageBox("CRYPTOOL_BASE: no certificate with the specified serial exists");
					return false;
				}
				// this flag will determine whether we delete the certificate
				bool authorized = false;
				// now we try to access the private key with the specified password
				using namespace OpenSSL;
				EVP_PKEY *pkey = EVP_PKEY_new();
				BIO *bioUserUserPrivateKey = BIO_new(BIO_s_file());
				if (BIO_read_filename(bioUserUserPrivateKey, (void*)(LPCTSTR)(fileNameUserPrivateKey))) {
					authorized = (PEM_read_bio_PrivateKey(bioUserUserPrivateKey, &pkey, 0, (void*)(LPCTSTR)(_password)) != 0);
				}
				BIO_free(bioUserUserPrivateKey);
				EVP_PKEY_free(pkey);
				// if the user is not authorized (as in: password is wrong), 
				// dump a warning message and return false
				if (!authorized) {
					AfxMessageBox("CRYPTOOL_BASE: wrong password, not authorized to access private key");
					return false;
				}
				// at this point we can safely assume the user is authorized, 
				// so we delete both the certificate and the private key; we 
				// don't do any error checking here on purpose, because if 
				// the file had been removed in the meantime manually, the 
				// result would be the same
				DeleteFile(fileNameUserCertificate);
				DeleteFile(fileNameUserPrivateKey);
				// re-load all user certificates after a certificate was deleted
				loadUserCertificates();
				// if we reach this point, everything went well
				return true;
			}

			std::vector<long> CertificateStore::getUserCertificateSerials(const bool _rsa, const bool _dsa, const bool _ec) const {
				using namespace OpenSSL;
				std::vector<long> vectorUserCertificateSerials;
				for (std::map<long, X509*>::const_iterator iter = mapUserCertificates.begin(); iter != mapUserCertificates.end(); iter++) {
					const long userCertificateSerial = iter->first;
					X509 *userCertificate = iter->second;
					if (userCertificate) {
						EVP_PKEY *pkey = X509_get_pubkey(userCertificate);
						const int keyType = EVP_PKEY_type(pkey->type);
						if ((keyType == EVP_PKEY_RSA && _rsa) || (keyType == EVP_PKEY_DSA && _dsa) || (keyType == EVP_PKEY_EC && _ec)) {
							vectorUserCertificateSerials.push_back(userCertificateSerial);
						}
						EVP_PKEY_free(pkey);
					}
				}
				return vectorUserCertificateSerials;
			}

			bool CertificateStore::getUserCertificateInformation(const long _serial, CString &_firstName, CString &_lastName, CString &_remarks, CString &_type, CString &_notBefore, CString &_notAfter) const {
				using namespace OpenSSL;
				// make sure there is a user certificate which corresponds to the provided serial number, 
				// otherwise return false right away and leave the output variables untouched
				const std::map<long, X509*>::const_iterator iter = mapUserCertificates.find(_serial);
				if (iter == mapUserCertificates.end()) {
					return false;
				}
				// acquire the X509 structure of the specified user certificate
				X509 *userCertificate = iter->second;
				if (!userCertificate) {
					return false;
				}
				// try to read custom CrypTool extension from the certificate
				if (!CertificateManipulator::readCustomCrypToolExtension(userCertificate, _firstName, _lastName, _remarks, _type)) {
					return false;
				}
				// manually assign not before and not after dates
				char bufferNotBefore[1024];
				char bufferNotAfter[1024];
				BIO *bioNotBefore = BIO_new(BIO_s_mem());
				BIO *bioNotAfter = BIO_new(BIO_s_mem());
				ASN1_TIME_print(bioNotBefore, X509_get_notBefore(userCertificate));
				ASN1_TIME_print(bioNotAfter, X509_get_notAfter(userCertificate));
				BIO_gets(bioNotBefore, bufferNotBefore, 100);
				BIO_gets(bioNotAfter, bufferNotAfter, 100);
				BIO_free(bioNotBefore);
				BIO_free(bioNotAfter);
				_notBefore = bufferNotBefore;
				_notAfter = bufferNotAfter;
				// obviously everything went well
				return true;
			}

			bool CertificateStore::getUserCertificatePublicParameters(const long _serial, CString &_publicParameters) const {
				using namespace OpenSSL;

				// TODO/FIXME
				_publicParameters = "TODO/FIXME: public parameters";
				return true;
				// TODO/FIXME

				return false;
			}

			bool CertificateStore::getUserCertificatePrivateParameters(const long _serial, const CString &_password, CString &_privateParameters) const {
				using namespace OpenSSL;

				// TODO/FIXME
				_privateParameters = "TODO/FIXME: private parameters";
				return true;
				// TODO/FIXME

				return false;
			}

			void CertificateStore::generateFileNamesForUserCertificateAndUserPrivateKey(const long _serial, CString &_fileNameUserCertificate, CString &_fileNameUserPrivateKey) const {
				CString fileNameBase;
				fileNameBase.Format(pathToCertificateStore + "\\" + "%d", _serial);
				_fileNameUserCertificate = fileNameBase + ".crt";
				_fileNameUserPrivateKey = fileNameBase + ".key";
			}

			void CertificateStore::loadUserCertificates() {
				using namespace OpenSSL;
				// first unload all user certificates
				unloadUserCertificates();
				// initialize some variables used for file searching
				std::vector<CString> vectorFileNamesUserCertificates;
				const CString patternUserCertificates = pathToCertificateStore + "\\*.crt";
				CFileFind finderUserCertificates;
				// find user certificate files
				BOOL foundUserCertificate = finderUserCertificates.FindFile(patternUserCertificates);
				while(foundUserCertificate) {
					foundUserCertificate = finderUserCertificates.FindNextFile();
					if (finderUserCertificates.IsDots()) continue;
					if (finderUserCertificates.IsDirectory()) continue;
					vectorFileNamesUserCertificates.push_back(finderUserCertificates.GetFilePath());
				}
				// try to acquire user certificates
				for (size_t indexUserCertificate = 0; indexUserCertificate < vectorFileNamesUserCertificates.size(); indexUserCertificate++) {
					BIO *bioUserCertificate = BIO_new(BIO_s_file());
					if (BIO_read_filename(bioUserCertificate, (LPCTSTR)(vectorFileNamesUserCertificates[indexUserCertificate]))) {
						X509 *userCertificate = X509_new();
						userCertificate = PEM_read_bio_X509(bioUserCertificate, 0, 0, 0);
						ASN1_INTEGER *asn1SerialNumber = X509_get_serialNumber(userCertificate);
						if (asn1SerialNumber && asn1SerialNumber->length <= (int)(sizeof(long))) {
							const long serialNumber = ASN1_INTEGER_get(asn1SerialNumber);
							mapUserCertificates[serialNumber] = userCertificate;
						}
					}
					BIO_free(bioUserCertificate);
				}
			}

			void CertificateStore::unloadUserCertificates() {
				using namespace OpenSSL;
				for (std::map<long, X509*>::iterator iter = mapUserCertificates.begin(); iter != mapUserCertificates.end(); iter++) {
					X509 *userCertificate = iter->second;
					X509_free(userCertificate);
				}
				mapUserCertificates.clear();
			}

			bool CertificateManipulator::writeCustomCrypToolExtension(OpenSSL::X509 *_certificate, const CString &_firstName, const CString &_lastName, const CString &_remarks, const CString &_type) {
				using namespace OpenSSL;
				// if we don't have a valid certificate, return false right away
				if (!_certificate) {
					return false;
				}
				// acquire extension identifier
				const int extensionIdentifier = CertificateStore::instance().getCustomCrypToolExtensionIdentifier();
				// at this point we create a string in the following format, without the quotes:  
				// "[FIRST NAME][LAST NAME][REMARKS][TYPE]"
				const CString extensionString = "[" + _firstName + "][" + _lastName + "][" + _remarks + "][" + _type + "]";
				ASN1_OCTET_STRING *asn1String = ASN1_OCTET_STRING_new();
				if (!ASN1_OCTET_STRING_set(asn1String, (const unsigned char*)(LPCTSTR)(extensionString), extensionString.GetLength())) {
					return false;
				}
				X509_EXTENSION *extension = X509_EXTENSION_create_by_NID(0, extensionIdentifier, 0, asn1String);
				if (!extension) {
					return false;
				}
				ASN1_OCTET_STRING_free(asn1String);
				if (!X509_add_ext(_certificate, extension, -1)) {
					return false;
				}
				X509_EXTENSION_free(extension);
				// seems like everything went fine
				return true;
			}

			bool CertificateManipulator::readCustomCrypToolExtension(OpenSSL::X509 *_certificate, CString &_firstName, CString &_lastName, CString &_remarks, CString &_type) {
				using namespace OpenSSL;
				// if we don't have a valid certificate, return false right away
				if (!_certificate) {
					return false;
				}
				// acquire extension identifier
				const int extensionIdentifier = CertificateStore::instance().getCustomCrypToolExtensionIdentifier();
				// extract the extension data
				const int index = X509_get_ext_by_NID(_certificate, extensionIdentifier, -1);
				X509_EXTENSION *extension = X509_get_ext(_certificate, index);
				if (!extension) {
					return false;
				}
				ASN1_OCTET_STRING *asn1String = X509_EXTENSION_get_data(extension);
				if (!asn1String) {
					return false;
				}
				const unsigned char *asn1StringData = asn1String->data;
				long xlen;
				int tag;
				int xclass;
				if (!ASN1_get_object(&asn1StringData, &xlen, &tag, &xclass, asn1String->length)) {
					return false;
				}
				// at this point we expect a string in the following format, without the quotes:  
				// "[FIRST NAME][LAST NAME][REMARKS][TYPE]"; if any of the elements is missing, 
				// we return false without changing the output variables
				const CString extensionString = asn1String->data;
				std::vector<CString> vectorElements;
				Utilities::extractElementsFromBracketedString(extensionString, "[", "]", vectorElements);
				if (vectorElements.size() != 4) {
					return false;
				}
				// seems like everything went fine-- assign the output variables, and then return
				_firstName = vectorElements.at(0);
				_lastName = vectorElements.at(1);
				_remarks = vectorElements.at(2);
				_type = vectorElements.at(3);
				return true;
			}

			bool encryptByteStringRSA(const long _serial, const ByteString &_byteStringInput, ByteString &_byteStringOutput) {
				// xxxxx
				return false;
			}
			
			bool decryptByteStringRSA(const long _serial, const CString &_password, const ByteString &_byteStringInput, ByteString &_byteStringOutput) {
				// xxxxx
				return false;
			}

		}

	}

	namespace Functions {

		void executeHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
			// create the operation controller dialog (implicitly destroyed after the operation)
			CrypTool::Internal::DialogOperationController *dialogOperationController = new CrypTool::Internal::DialogOperationController();
			// create the appropriate title for the dialog, and make it visible
			CString dialogOperationControllerTitle;
			dialogOperationControllerTitle.Format("CRYPTOOL_BASE: hash operation (%s)", CrypTool::Cryptography::Hash::getHashAlgorithmName(_hashAlgorithmType));
			dialogOperationController->SetWindowText(dialogOperationControllerTitle);
			// start the operation in its own thread
			dialogOperationController->startHashOperation(_hashAlgorithmType, _documentFileName, _documentTitle);
		}

		void executeSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
			// create the operation controller dialog (implicitly destroyed after the operation)
			CrypTool::Internal::DialogOperationController *dialogOperationController = new CrypTool::Internal::DialogOperationController();
			// create the appropriate title for the dialog, and make it visible
			CString dialogOperationControllerTitle;
			dialogOperationControllerTitle.Format("CRYPTOOL_BASE: symmetric operation (%s)", CrypTool::Cryptography::Symmetric::getSymmetricAlgorithmName(_symmetricAlgorithmType));
			dialogOperationController->SetWindowText(dialogOperationControllerTitle);
			// start the operation in its own thread
			dialogOperationController->startSymmetricOperation(_symmetricAlgorithmType, _documentFileName, _documentTitle);
		}

		void executeRSAEncryption(const CString &_documentFileName, const CString &_documentTitle) {
			// xxxxx
		}
		
		void executeRSADecryption(const CString &_documentFileName, const CString &_documentTitle) {
			// xxxxx
		}

		bool createKeyFromPasswordPKCS5(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const ByteString &_password, const ByteString &_salt, const int _iterations, const int _keyLength, ByteString &_key) {
			// the only supported algorithms right now are MD5 and SHA1 (MD2 is deprecated)
			std::vector<CrypTool::Cryptography::Hash::HashAlgorithmType> vectorHashAlgorithmTypes;
			vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_MD5);
			vectorHashAlgorithmTypes.push_back(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_SHA1);
			if (!CrypTool::Utilities::vectorContains<CrypTool::Cryptography::Hash::HashAlgorithmType>(vectorHashAlgorithmTypes, _hashAlgorithmType)) {
				AfxMessageBox("CRYPTOOL_BASE: specified hash algorithm not supported (PKCS5)");
				return false;
			}
			// the number of iterations must be valid [1, 100000]
			if (_iterations < 1 || _iterations > 100000) {
				AfxMessageBox("CRYPTOOL_BASE: specified number of iterations not supported (PKCS5)");
				return false;
			}
			// the key length must be valid [1, byteLengthHash]
			if (_keyLength < 1 || _keyLength > (int)(CrypTool::Cryptography::Hash::getHashAlgorithmByteLength(_hashAlgorithmType))) {
				AfxMessageBox("CRYPTOOL_BASE: specified key length is not supported (PKCS5)");
				return false;
			}
			// create concatenation of password and salt
			ByteString byteStringPasswordAndSalt;
			byteStringPasswordAndSalt += _password;
			byteStringPasswordAndSalt += _salt;
			// create byte strings for temporary hash values
			ByteString byteStringHashValue;
			ByteString byteStringHashValueTemp;
			// create objects for inner and outer hash operations
			CrypTool::Cryptography::Hash::HashOperation hashOperationOuter(_hashAlgorithmType);
			CrypTool::Cryptography::Hash::HashOperation hashOperationInner(_hashAlgorithmType);
			// execute outer hash (hash of password and salt)
			hashOperationOuter.executeOnByteStrings(byteStringPasswordAndSalt, byteStringHashValue);
			// execute inner hashes (hash of hash of hash...)
			for (int iteration = 1; iteration < _iterations; iteration++) {
				hashOperationInner.executeOnByteStrings(byteStringHashValue, byteStringHashValueTemp);
				byteStringHashValue = byteStringHashValueTemp;
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
			parameters.operationStatus = OPERATION_STATUS_STARTED;
			// start the update timer
			updateTimer = SetTimer(ID_TIMER_EVENT_UPDATE, 50, NULL);
			// start the operation thread
			operationThread = AfxBeginThread(executeHashOperation, &parameters);
		}

		void DialogOperationController::startSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle) {
			// ask user for operation parameters (key and encryption/decryption)
			CString dlgKeyHexFixedLenTitle;
			dlgKeyHexFixedLenTitle.Format(IDS_STRING_KEYINPUT_SYMMETRIC, CrypTool::Cryptography::Symmetric::getSymmetricAlgorithmName(_symmetricAlgorithmType));
			CDlgKeyHexFixedLen dlgKeyHexFixedLen;
			switch (_symmetricAlgorithmType) {
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_IDEA:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 128, 128, 128);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_RC2:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_RC4:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 8, 128, 8);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_DES_ECB:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_DES_CBC:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 64, 64, 64, CRYPT_PARITY_DES);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_ECB:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_TRIPLE_DES_CBC:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 128, 128, 128, CRYPT_PARITY_DESX);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_MARS:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_RC6:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_SERPENT:
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_TWOFISH:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 128, 256, 64);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_DESX:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 192, 192, 192, CRYPT_PARITY_DESX);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_DESL:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 64, 64, 64, CRYPT_PARITY_DES);
				break;
			case CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_DESXL:
				dlgKeyHexFixedLen.Init(dlgKeyHexFixedLenTitle, 192, 192, 192, CRYPT_PARITY_DESX);
				break;
			default:
				AfxMessageBox("CRYPTOOL_BASE: unsupported symmetric algorithm");
				return;
			}
			// don't do anything else if dialog is cancelled by the user
			if (dlgKeyHexFixedLen.DoModal() != IDOK) {
				return;
			}
			// extract operation key and operation type from key dialog
			const CrypTool::Cryptography::Symmetric::SymmetricOperationType operationType = dlgKeyHexFixedLen.ModeIsDecrypt() ? CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_DECRYPTION : CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_ENCRYPTION;
			const ByteString operationKey = ByteString((const unsigned char*)(dlgKeyHexFixedLen.GetKeyBytes()), (const size_t)(dlgKeyHexFixedLen.GetKeyByteLength()));
			// initialize operation parameters
			parameters.parametersSymmetric.symmetricAlgorithmType = _symmetricAlgorithmType;
			parameters.parametersSymmetric.symmetricOperationType = operationType;
			parameters.parametersSymmetric.documentFileName = _documentFileName;
			parameters.parametersSymmetric.documentTitle = _documentTitle;
			parameters.parametersSymmetric.key = operationKey;
			// mark the operation as started
			parameters.operationStatus = OPERATION_STATUS_STARTED;
			// start the update timer
			updateTimer = SetTimer(ID_TIMER_EVENT_UPDATE, 50, NULL);
			// start the operation thread
			operationThread = AfxBeginThread(executeSymmetricOperation, &parameters);
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
			const bool result = operation->executeOnFiles(parameters->parametersHash.documentFileName, parameters->parametersHash.documentFileNameNew, &parameters->operationCancelled, &parameters->operationProgress);
			delete operation;
			// mark the operation as finished
			parameters->operationStatus = OPERATION_STATUS_FINISHED;
			// start post-processing only if operation was successful
			if (result) {
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
			}
			// mark the operation as done, and end the thread
			parameters->operationStatus = OPERATION_STATUS_DONE;
			AfxEndThread(0);
			return 0;
		}

		UINT DialogOperationController::executeSymmetricOperation(LPVOID _parameters) {
			// acquire the operation parameters
			Parameters *parameters = (Parameters*)(_parameters);
			ASSERT(parameters);
			// create a file name and a title for the new document, 
			// and update the parameters accordingly
			parameters->parametersSymmetric.documentFileNameNew = Utilities::createTemporaryFile();
			parameters->parametersSymmetric.documentTitleNew.Format(parameters->parametersSymmetric.symmetricOperationType == CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_DECRYPTION ? IDS_STRING_DECRYPTION_OF_USING_KEY : IDS_STRING_ENCRYPTION_OF_USING_KEY, CrypTool::Cryptography::Symmetric::getSymmetricAlgorithmName(parameters->parametersSymmetric.symmetricAlgorithmType), parameters->parametersSymmetric.documentTitle, parameters->parametersSymmetric.key.toString(16, " "));
			// execute the operation
			CrypTool::Cryptography::Symmetric::SymmetricOperation *operation = new CrypTool::Cryptography::Symmetric::SymmetricOperation(parameters->parametersSymmetric.symmetricAlgorithmType, parameters->parametersSymmetric.symmetricOperationType);
			const bool result = operation->executeOnFiles(parameters->parametersSymmetric.documentFileName, parameters->parametersSymmetric.documentFileNameNew, parameters->parametersSymmetric.key, &parameters->operationCancelled, &parameters->operationProgress);
			delete operation;
			// mark the operation as finished
			parameters->operationStatus = OPERATION_STATUS_FINISHED;
			// start post-processing only if operation was successful
			if (result) {
				// start post-processing: display the result in a new document
				theApp.ThreadOpenDocumentFileNoMRU(parameters->parametersSymmetric.documentFileNameNew, parameters->parametersSymmetric.documentTitleNew);
			}
			// mark the operation as done, and end the thread
			parameters->operationStatus = OPERATION_STATUS_DONE;
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
				controlProgress.SetPos((int)(parameters.operationProgress * 100));
				// update the text
				controlText.SetWindowText("");
				// do some magic depending on the operation status
				switch (parameters.operationStatus) {
				case OPERATION_STATUS_STARTED:
					// if the operation has started, show the dialog
					ShowWindow(SW_SHOW);
					break;
				case OPERATION_STATUS_FINISHED:
					// if the operation has finished, hide the dialog
					ShowWindow(SW_HIDE);
					break;
				case OPERATION_STATUS_DONE:
					// if the operation is done, kill the timer and close the dialog
					KillTimer(updateTimer);
					OnClose();
					break;
				default:
					break;
				}
				return;
			}
			CDialog::OnTimer(_event);
		}

		void DialogOperationController::OnCancel() {
			// mark the operation as cancelled
			parameters.operationCancelled = true;
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