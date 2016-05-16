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

		CString getTemporaryFileName(const CString &_extension) {
			// here we try to find a folder for the temporary files; if none of 
			// the specified environment variables are valid, we stick to the 
			// folder in which CrypTool is executed
			CString temporaryFolder;
			std::vector<CString> vectorEnvironmentVariables;
			vectorEnvironmentVariables.push_back("TEMP");
			vectorEnvironmentVariables.push_back("TMP");
			// try to find a valid temporary folder using the environment variables
			for (int i = 0; i < vectorEnvironmentVariables.size(); i++) {
				temporaryFolder = getenv(vectorEnvironmentVariables[i]);
				if (temporaryFolder.GetLength() > 0) {
					break;
				}
			}
			// stick to the current folder if no temporary folder was found
			if (temporaryFolder.GetLength() == 0) {
				temporaryFolder = ".";
			}
			// now iterate through the range of valid identifiers and check 
			// whether there's a temporary file name which has not been used 
			// yet; a temporary file has not been used if it cannot be opened
			CFile file;
			CString temporaryFileName;
			const int identifierMin = 1;
			const int identifierMax = (std::numeric_limits<int>::max)();
			for (int identifier = identifierMin; identifier <= identifierMax; identifier++) {
				// create temporary file name (using the specified extension)
				temporaryFileName.Format("%s\\CrypTool-%d.%s", temporaryFolder, identifier, _extension);
				// try to open the temporary file; if it fails, that's a sign for success
				if (!file.Open(temporaryFileName, CFile::modeRead)) {
					return temporaryFileName;
				}
				file.Close();
			}
			// at this point we were not able to create a temporary file, 
			// therefore we return an empty string to indicate an error
			return CString();
		}

	}

	namespace Cryptography {

		namespace Hash {

			CString getHashAlgorithmName(const HashAlgorithmType _hashAlgorithmType) {
				CString hashAlgorithmName;
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
				int hashAlgorithmBitLength;
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

			HashOperation::HashOperation(const HashAlgorithmType _hashAlgorithmType) :
				hashAlgorithmType(_hashAlgorithmType) {

			}

			void HashOperation::startOperation(const CString &_fileNameSource, const CString &_fileNameTarget) {
				// acquire the bit length of the desired hash algorithm
				const unsigned int hashAlgorithmBitLength = getHashAlgorithmBitLength(hashAlgorithmType);
				const unsigned int hashAlgorithmByteLength = (hashAlgorithmBitLength + 7) / 8;
				// this variable will store the resulting hash value
				unsigned char *digest = new unsigned char[hashAlgorithmByteLength];
				// the buffer size we're working with (the size of the chunks to be read from the source file)
				const unsigned int bufferByteLength = 4096;
				char *buffer = new char[bufferByteLength];
				// this variable will track the progress of the operation (0.0 to 1.0)
				double progress = 0.0;
				// open the specified source file
				CFile fileSource;
				if (fileSource.Open(_fileNameSource, CFile::modeRead)) {
					const unsigned long positionStart = 0;
					const unsigned long positionEnd = fileSource.GetLength();
					unsigned long positionCurrent = positionStart;
					unsigned long bytesRead;
					// MD4
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_MD4) {
						OpenSSL::MD4_CTX context;
						OpenSSL::MD4_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::MD4_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::MD4_Final(digest, &context);
					}
					// MD5
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_MD5) {
						OpenSSL::MD5_CTX context;
						OpenSSL::MD5_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::MD5_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::MD5_Final(digest, &context);
					}
					// RIPEMD160
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_RIPEMD160) {
						OpenSSL::RIPEMD160_CTX context;
						OpenSSL::RIPEMD160_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::RIPEMD160_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::RIPEMD160_Final(digest, &context);
					}
					// SHA
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA) {
						OpenSSL::SHA_CTX context;
						OpenSSL::SHA_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA_Final(digest, &context);
					}
					// SHA1
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA1) {
						OpenSSL::SHA_CTX context;
						OpenSSL::SHA1_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA1_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA1_Final(digest, &context);
					}
					// SHA224
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA224) {
						OpenSSL::SHA256_CTX context;
						OpenSSL::SHA224_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA224_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA224_Final(digest, &context);
					}
					// SHA256
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA256) {
						OpenSSL::SHA256_CTX context;
						OpenSSL::SHA256_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA256_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA256_Final(digest, &context);
					}
					// SHA384
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA384) {
						OpenSSL::SHA512_CTX context;
						OpenSSL::SHA384_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA384_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA384_Final(digest, &context);
					}
					// SHA512
					if (hashAlgorithmType == HASH_ALGORITHM_TYPE_SHA512) {
						OpenSSL::SHA512_CTX context;
						OpenSSL::SHA512_Init(&context);
						while (bytesRead = fileSource.Read(buffer, bufferByteLength)) {
							OpenSSL::SHA512_Update(&context, buffer, bytesRead);
							positionCurrent += bytesRead;
						}
						OpenSSL::SHA512_Final(digest, &context);
					}
					// write the resulting hash value to the specified target file
					CFile fileTarget;
					if (fileTarget.Open(_fileNameTarget, CFile::modeCreate | CFile::modeWrite)) {
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

}