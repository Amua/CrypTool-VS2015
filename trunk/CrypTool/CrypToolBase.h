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
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <set>

namespace OpenSSL {
	// generic headers
	#include <openssl/bio.h>
	#include <openssl/pem.h>
	#include <openssl/err.h>
	#include <openssl/rand.h>
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
		// this is a convenience function to convert the byte string into a 
		// hex dump; each hex dump features lines of three columns: a 32bit 
		// address column, a hexadecimal column, and an ascii column; the 
		// parameter specifies how many bytes are displayed per row
		CString toHexDump(const size_t _bytesPerRow) const;
	public:
		// resets the byte string: deletes the allocated memory, 
		// and resets both the byte data and byte length to zero 
		// unless a new byte length is specified
		void reset(const size_t _byteLength = 0);
		// truncates the byte string to the specified size; if the specified 
		// size is larger than the actual size, the function does nothing; 
		// otherwise the function allocates new memory for the truncated 
		// contents and frees the old memory
		void truncateLeft(const size_t _byteLength);
		// truncates the byte string to the specified size; if the specified 
		// size is larger than the actual size, the function does nothing; 
		// otherwise the function allocates new memory for the truncated 
		// contents and frees the old memory
		void truncateRight(const size_t _byteLength);
		// this function is provided for convenience: it resets the byte 
		// string to the specified length and fills it with random data 
		// generated by OpenSSL
		void randomize(const size_t _byteLength);
		// this function adds zero padding to the left until the specified 
		// byte length is reached; if the byte string is as long or longer 
		// than the specified byte length, it remains untouched
		void addZeroPaddingLeft(const size_t _byteLength);
		// this function adds zero padding to the right until the specified 
		// byte length is reached; if the byte string is as long or longer 
		// than the specified byte length, it remains untouched
		void addZeroPaddingRight(const size_t _byteLength);
		// this function fills the byte string with the specified character 
		// to the left until the desired byte length is reached; if the byte 
		// string is as long or longer than the specified byte length, it 
		// remains untouched
		void fillLeft(const unsigned char _character, const size_t _byteLength);
		// this function fills the byte string with the specified character 
		// to the left until the desired byte length is reached; if the byte 
		// string is as long or longer than the specified byte length, it 
		// remains untouched
		void fillRight(const unsigned char _character, const size_t _byteLength);
	public:
		// this function is provided for convenience: it searches the byte 
		// string for the first occurence of the specified pattern; if the 
		// pattern cannot be found, the function returns false; if the 
		// pattern is found, the function returns true and sets the output 
		// parameters for start and end of the pattern accordingly
		bool findPattern(const ByteString &_pattern, size_t &_start, size_t &_end) const;
		// this function is provided for convenience: it extracts the pattern 
		// enclosed by the indices specified through start and end (where end 
		// must be larger than start of course); if the specified indices are 
		// invalid for whatever reason, the function returns false
		bool extractPattern(const size_t _start, const size_t _end, ByteString &_pattern) const;
	public:
		// this function returns true if the byte string is a null string; 
		// a byte string is a null string if all bytes in the byte string 
		// are zero, or if there are no bytes at all
		bool isNull() const;
	public:
		// this function returns a pointer to the internal data
		unsigned char *getByteData() { return byteData; }
		const unsigned char *getByteDataConst() const { return byteData; }
		// this function returns the length of the internal data
		size_t getByteLength() const { return byteLength; }
	public:
		ByteString &operator=(const ByteString &_byteString);
		ByteString &operator+=(const ByteString &_byteString);
		ByteString &operator=(const CString &_string);
		ByteString &operator+=(const CString &_string);
		ByteString &operator+=(const unsigned char _character);
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

		// these functions try to open the Windows registry and read "_variable" below "_path" into "_value";
		// upon error, false is returned and the resulting value is either empty (for strings) or zero (for 
		// numbers); the "Default" functions take an additional parameter which is returned in case of errors; 
		// for the string functions this default parameter can either be a string or a number, in the latter 
		// case this number is interpreted as a CrypTool resource identifier; if this resource identifier is 
		// invalid, the resulting  value will contain an empty string just like with the non-"Default" functions
		bool registryReadString(const CString &_path, const CString &_variable, CString &_value);
		bool registryReadStringDefault(const CString &_path, const CString &_variable, const CString &_default, CString &_value);
		bool registryReadStringDefault(const CString &_path, const CString &_variable, const unsigned int _default, CString &_value);
		bool registryReadNumber(const CString &_path, const CString &_variable, long &_value);
		bool registryReadNumber(const CString &_path, const CString &_variable, int &_value);
		bool registryReadNumberDefault(const CString &_path, const CString &_variable, const long _default, long &_value);
		bool registryReadNumberDefault(const CString &_path, const CString &_variable, const int _default, int &_value);
		// these functions try to open the Windows registry and write "_value" into "_variable" below "_path"; 
		// upon error, false is returned
		bool registryWriteString(const CString &_path, const CString &_variable, const CString &_value);
		bool registryWriteNumber(const CString &_path, const CString &_variable, const long _value);

		// this function truncates the specified byte string to the specified length; this function also 
		// removes all bytes at (and beyond) the first null byte; if the byte string is modified in any 
		// way, the user is notified; the function returns the length of the resulting byte string
		size_t truncateByteString(ByteString &_byteString, const unsigned int _truncateAtLength, const bool _truncateAtFirstNullByte);

		// this function extracts string elements from a bracketed string; for example, if we have a 
		// bracketed string like "<A><B><C>" and this function is called with an opening bracket of "<" 
		// and a closing bracket of ">", then the three elements "A", "B", and "C" are returned
		void extractElementsFromBracketedString(const CString &_input, const CString &_openingBracket, const CString &_closingBracket, std::vector<CString> &_vectorElements);

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

		// this function converts a string number from one base to another; supported base representations 
		// are base2 (binary), base8 (octal), base10 (decimal), and base16 (hexadecimal); if the specified 
		// number cannot be converted for whatever reason, the original number is returned
		CString convertStringNumberFromBaseToBase(const CString &_number, const unsigned int _baseFrom, const unsigned int _baseTo);

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
			// this function returns the hash algorithm type based on the specified name
			HashAlgorithmType getHashAlgorithmType(const CString &_hashAlgorithmName);

			// this function returns the bit length of the specified hash algorithm type
			unsigned int getHashAlgorithmBitLength(const HashAlgorithmType _hashAlgorithmType);
			// this function returns the byte length of the specified hash algorithm type
			unsigned int getHashAlgorithmByteLength(const HashAlgorithmType _hashAlgorithmType);

			// this function returns the OpenSSL message digest corresponding to 
			// the specified hash algorithm type (or null on error)
			const OpenSSL::EVP_MD *getMessageDigest(const HashAlgorithmType _hashAlgorithmType);

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
			// this function returns the symmetric algorithm type based on the specified name
			SymmetricAlgorithmType getSymmetricAlgorithmType(const CString &_symmetricAlgorithmName);

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
				ASYMMETRIC_ALGORITHM_TYPE_NULL,
				ASYMMETRIC_ALGORITHM_TYPE_RSA,
				ASYMMETRIC_ALGORITHM_TYPE_DSA,
				ASYMMETRIC_ALGORITHM_TYPE_ECC
			};

			// the supported asymmetric operation types
			enum AsymmetricOperationType {
				ASYMMETRIC_OPERATION_TYPE_NULL,
				ASYMMETRIC_OPERATION_TYPE_ENCRYPTION,
				ASYMMETRIC_OPERATION_TYPE_DECRYPTION
			};

			// this function returns the name of the specified asymmetric algorithm type
			CString getAsymmetricAlgorithmName(const AsymmetricAlgorithmType _asymmetricAlgorithmType);
			// this function returns the asymmetric algorithm type based on the specified name
			AsymmetricAlgorithmType getAsymmetricAlgorithmType(const CString &_asymmetricAlgorithmName);

			// this class provides asymmetric operations (encryption and decryption) on 
			// the supported asymmetric algorithm types for both byte strings and files 
			// (see different execute functions below); the file-based operations provide 
			// the ability to cancel the operations and track their progress when run in 
			// a separate thread; this implementation is using RSA_PKCS1_OAEP_PADDING by 
			// default unless the "_padding" parameter in the constructor is set to false, 
			// in which case RSA_NO_PADDING is used
			class AsymmetricOperationEncryptOrDecrypt {
			public:
				AsymmetricOperationEncryptOrDecrypt(const AsymmetricAlgorithmType _asymmetricAlgorithmType, const AsymmetricOperationType _asymmetricOperationType, const bool _padding = true);
				virtual ~AsymmetricOperationEncryptOrDecrypt();
			public:
				bool executeOnByteStrings(const ByteString &_byteStringInput, const long _serial, const CString &_password, ByteString &_byteStringOutput);
				bool executeOnFiles(const CString &_fileNameInput, const CString &_fileNameOutput, const long _serial, const CString &_password, const bool *_cancelled = 0, double *_progress = 0);
			private:
				const AsymmetricAlgorithmType asymmetricAlgorithmType;
				const AsymmetricOperationType asymmetricOperationType;
				const bool padding;
			};

			// the supported certificate types
			enum CertificateType {
				CERTIFICATE_TYPE_NULL,
				CERTIFICATE_TYPE_RSA,
				CERTIFICATE_TYPE_DSA,
				CERTIFICATE_TYPE_ECC
			};

			// this class represents the CrypTool-internal certificate store; it is 
			// responsible for creating and deleting certificates and acts as interface 
			// to all other CrypTool components in terms of dealing with certificates; 
			// internally it uses the "CertificateManipulator" class to inject and 
			// extract information into and from certificates (see below)
			class CertificateStore {
			protected:
				CertificateStore();
				virtual ~CertificateStore();
			public:
				static CertificateStore &instance();
			public:
				void initialize(const CString &_caPassword);
				void deinitialize();
			public:
				// this function returns the static identifier for the custom CrypTool extension
				int getCustomCrypToolExtensionIdentifier() const;
			public:
				// this function tries to create a certificate with the values specified by the user; the 
				// certificate type is one of RSA, DSA, ECC, and the the certificate parameters string contains 
				// either the desired key length (RSA and DSA) or the desired elliptic curve (ECC); all other 
				// parameters (first name, last name, remarks, password) are identical for all types
				bool createUserCertificate(const CertificateType _certificateType, const CString &_certificateParameters, const CString &_firstName, const CString &_lastName, const CString &_remarks, const CString &_password);
				// this function tries to delete the user certificate with the specified serial number; 
				// however, the correct password (protecting the private key) must be provided for the 
				// deletion to be successful
				bool deleteUserCertificate(const long _serial, const CString &_password);
			public:
				// this function returns the serial numbers of all user certificates stored in this 
				// certificate store; the arguments act as a filter in that they control which types 
				// of certificates are returned; if all arguments are false, the resulting vector 
				// is empty of course
				std::vector<long> getUserCertificateSerials(const bool _rsa, const bool _dsa, const bool _ec) const;
				// if the serial number supplied as argument doesn't match any of the available user 
				// certificates, the function returns false and all output variables remain untouched; 
				// first and foremost this function is used as a convenience interface to easily display 
				// user certificate information in list controls
				bool getUserCertificateInformation(const long _serial, CString &_firstName, CString &_lastName, CString &_remarks, CString &_type, CString &_notBefore, CString &_notAfter) const;
			public:
				// this function returns a generic public key (RSA, DSA, ECC) for the certificate 
				// corresponding to the specified serial number (no password required)
				bool getUserCertificatePublicKey(const long _serial, OpenSSL::EVP_PKEY **_key) const;
				// this function returns a generic private key (RSA, DSA, ECC) for the certificate 
				// corresponding to the specified serial number (password required for private key)
				bool getUserCertificatePrivateKey(const long _serial, const CString &_password, OpenSSL::EVP_PKEY **_key) const;
			public:
				// returns RSA public key (based on the generic function above)
				bool getUserCertificatePublicKeyRSA(const long _serial, OpenSSL::RSA **_rsa) const;
				// returns DSA public key (based on the generic function above)
				bool getUserCertificatePublicKeyDSA(const long _serial, OpenSSL::DSA **_dsa) const;
				// returns ECC public key (based on the generic function above)
				bool getUserCertificatePublicKeyECC(const long _serial, OpenSSL::EC_KEY **_ecc) const;
				// returns RSA private key (based on the generic function above)
				bool getUserCertificatePrivateKeyRSA(const long _serial, const CString &_password, OpenSSL::RSA **_rsa) const;
				// returns DSA private key (based on the generic function above)
				bool getUserCertificatePrivateKeyDSA(const long _serial, const CString &_password, OpenSSL::DSA **_dsa) const;
				// returns ECC private key (based on the generic function above)
				bool getUserCertificatePrivateKeyECC(const long _serial, const CString &_password, OpenSSL::EC_KEY **_ecc) const;
			public:
				// this function returns the public parameters of the user certificate corresponding to 
				// the specified serial number in human-readable format; the output is very similar to 
				// what you get from OpenSSL's x509 CLI command
				bool getUserCertificatePublicParameters(const long _serial, CString &_publicParameters) const;
				// this function returns the private parameters of the user certificate corresponding to 
				// the specified serial number in human-readable format; the output is very similar to 
				// what you get from OpenSSL's rsa, dsa, and ec CLI commands; since the private parameters 
				// are only to be accessed by authorized users, naturally the correct password is required
				bool getUserCertificatePrivateParameters(const long _serial, const CString &_password, CString &_privateParameters) const;
			public:
				// this function is provided for convenience
				bool getUserCertificateStringName(const long _serial, CString &_name) const;
				// this function is provided for convenience
				bool getUserCertificateStringRSAPublicKeyE(const long _serial, const unsigned int _base, CString &_e) const;
				// this function is provided for convenience
				bool getUserCertificateStringRSAPublicKeyN(const long _serial, const unsigned int _base, CString &_n) const;
				// this function is provided for convenience
				bool getUserCertificateStringRSAPrivateKeyD(const long _serial, const CString &_password, const unsigned int _base, CString &_d) const;
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
			private:
				// this map holds all user certificates (mapped to serial numbers) currently held 
				// in memory; whenever a user certificate is created or deleted, all user certificates 
				// are automatically re-loaded so that this map is always up-to-date
				std::map<long, OpenSSL::X509*> mapUserCertificates;
			private:
				// over the lifetime of the certificate store, these variables always stay the same: 
				// the path to the certificate store (where all user certificates are stored), and 
				// the file names for both the CA certificate and the CA private key
				const CString pathToCertificateStore;
				const CString fileNameCaCertificate;
				const CString fileNameCaPrivateKey;
				// these variables are always held in memory: the CA certificate and the CA private key
				OpenSSL::X509 *caCertificate;
				OpenSSL::RSA *caPrivateKey;
			};

			// this class shouldn't be used directly; it only features static methods, and it 
			// primarily acts as helper class for the "CertificateStore" class so the latter 
			// one isn't overblown with a gazillion individual methods
			class CertificateManipulator {
			public:
				// this function writes the custom CrypTool extension to the specified certificate;
				// this way the asymmetric crypto implementation adheres to CrypTool 1.4 and prior; 
				// the extension looks like this "[FIRST NAME][LAST NAME][REMARKS][TYPE]", for 
				// example "[John][Doe][Password=1234][RSA-1024]"
				static bool writeCustomCrypToolExtension(OpenSSL::X509 *_certificate, const CString &_firstName, const CString &_lastName, const CString &_remarks, const CString &_type);
				// this function reads the custom CrypTool extension from the specified certificate;
				// this way the asymmetric crypto implementation adheres to CrypTool 1.4 and prior;
				// the extension looks like this "[FIRST NAME][LAST NAME][REMARKS][TYPE]", for 
				// example "[John][Doe][Password=1234][RSA-1024]"
				static bool readCustomCrypToolExtension(OpenSSL::X509 *_certificate, CString &_firstName, CString &_lastName, CString &_remarks, CString &_type);
			};

		}

		// this namespace encapsulates functionality for digital signatures
		namespace Signature {

			// the supported signature types (combination of asymmetric algorithm and hash algorithm)
			enum SignatureType {
				SIGNATURE_TYPE_NULL,
				SIGNATURE_TYPE_RSA_MD5,
				SIGNATURE_TYPE_RSA_RIPEMD160,
				SIGNATURE_TYPE_RSA_SHA,
				SIGNATURE_TYPE_RSA_SHA1,
				SIGNATURE_TYPE_DSA_SHA,
				SIGNATURE_TYPE_DSA_SHA1,
				SIGNATURE_TYPE_ECC_RIPEMD160,
				SIGNATURE_TYPE_ECC_SHA1
			};

			// this function returns the name of the specified signature type
			CString getSignatureName(const SignatureType _signatureType);
			// this function returns the signature type based on the specified name
			SignatureType getSignatureType(const CString &_signatureName);
			// this function returns the proper signature type for the specified 
			// combination of asymmetric algorithm and hash algorithm; if the 
			// specified combination is invalid, SIGNATURE_TYPE_NULL is returned
			SignatureType getSignatureType(const Asymmetric::AsymmetricAlgorithmType _asymmetricAlgorithmType, const Hash::HashAlgorithmType _hashAlgorithmType);

			// returns the asymmetric algorithm type based on the specified 
			// signature type, or ASYMMETRIC_ALGORITHM_TYPE_NULL in case of errors
			Asymmetric::AsymmetricAlgorithmType getAsymmetricAlgorithmType(const SignatureType _signatureType);

			// returns the hash algorithm type based on the specified signature 
			// type, or HASH_ALGORITHM_TYPE_NULL in case of errors
			Hash::HashAlgorithmType getHashAlgorithmType(const SignatureType _signatureType);

			// this class provides sign operations for digital signatures; the file-based 
			// operations provide the ability to cancel the operations and track their 
			// progress when run in a separate thread
			class OperationSign {
			public:
				OperationSign(const SignatureType _signatureType);
				virtual ~OperationSign();
			public:
				bool executeOnByteStrings(const ByteString &_byteStringMessage, ByteString &_byteStringSignature, const long _serial, const CString &_password);
				bool executeOnFiles(const CString &_fileNameMessage, const CString &_fileNameSignature, const long _serial, const CString &_password, const bool *_cancelled = 0, double *_progress = 0);
			private:
				const SignatureType signatureType;
			};

			// this class provides sign operations for digital signatures; the file-based 
			// operations provide the ability to cancel the operations and track their 
			// progress when run in a separate thread
			class OperationVerify {
			public:
				OperationVerify(const SignatureType _signatureType);
				virtual ~OperationVerify();
			public:
				bool executeOnByteStrings(const ByteString &_byteStringMessage, const ByteString &_byteStringSignature, const long _serial);
				bool executeOnFiles(const CString &_fileNameMessage, const CString &_fileNameSignature, const long _serial, const bool *_cancelled = 0, double *_progress = 0);
			private:
				const SignatureType signatureType;
			};

		}

	}

	// this namespace encapsulates a variety of high-level functions
	namespace Functions {

		// TODO/FIXME: rename or remove this? the complexity behind this operation is unclear (threading, etc...)
		void executeHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
		// TODO/FIXME: rename or remove this? the complexity behind this operation is unclear (threading, etc...)
		void executeSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
		// TODO/FIXME: rename or remove this? the complexity behind this operation is unclear (threading, etc...)
		void executeAsymmetricOperationEncryptOrDecrypt(const CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType _asymmetricAlgorithmType, const CrypTool::Cryptography::Asymmetric::AsymmetricOperationType _asymmetricOperationType, const CString &_documentFileName, const CString &_documentTitle);

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
				// document-related parameters
				CString documentFileName;
				CString documentTitle;
				CString documentFileNameNew;
				CString documentTitleNew;
				// parameters specific to hash operations
				struct ParametersHash {
					CrypTool::Cryptography::Hash::HashAlgorithmType hashAlgorithmType;
					// construction/destruction
					ParametersHash() : hashAlgorithmType(CrypTool::Cryptography::Hash::HASH_ALGORITHM_TYPE_NULL) { }
					virtual ~ParametersHash() { }
				} parametersHash;
				// parameters specific to symmetric operations
				struct ParametersSymmetric {
					CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType symmetricAlgorithmType;
					CrypTool::Cryptography::Symmetric::SymmetricOperationType symmetricOperationType;
					ByteString key;
					// construction/destruction
					ParametersSymmetric() : symmetricAlgorithmType(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_NULL), key(ByteString()) { }
					virtual ~ParametersSymmetric() { }
				} parametersSymmetric;
				// parameters specific to asymmetric operations
				struct ParametersAsymmetric {
					CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType asymmetricAlgorithmType;
					CrypTool::Cryptography::Asymmetric::AsymmetricOperationType asymmetricOperationType;
					long serial;
					CString password;
					// construction/destruction
					ParametersAsymmetric() : asymmetricAlgorithmType(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_NULL), asymmetricOperationType(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_OPERATION_TYPE_NULL), serial(0), password("") { }
				} parametersAsymmetric;
				// construction/destruction
				Parameters() : operationStatus(OPERATION_STATUS_NULL), operationCancelled(false), operationProgress(0.0), documentFileName(""), documentTitle(""), documentFileNameNew(""), documentTitleNew("") { }
				virtual ~Parameters() { }
			} parameters;
		public:
			DialogOperationController();
			virtual ~DialogOperationController();
		public:
			void startHashOperation(const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
			void startSymmetricOperation(const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const CString &_documentFileName, const CString &_documentTitle);
			void startAsymmetricOperationEncryptOrDecrypt(const CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType _asymmetricAlgorithmType, const CrypTool::Cryptography::Asymmetric::AsymmetricOperationType _asymmetricOperationType, const CString &_documentFileName, const CString &_documentTitle);
		private:
			static UINT executeHashOperation(LPVOID _parameters);
			static UINT executeSymmetricOperation(LPVOID _parameters);
			static UINT executeAsymmetricOperationEncryptOrDecrypt(LPVOID _parameters);
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
			friend class CrypTool::Cryptography::Symmetric::SymmetricOperation;
			friend class CrypTool::Cryptography::Asymmetric::AsymmetricOperationEncryptOrDecrypt;
		};

	}

	namespace Utilities {

		// this function tells whether the specified file is a hybrid-encrypted file
		bool isFileHybridEncrypted(const CString &_fileName);
		// this function tries to create a hybrid-encrypted file based on the specified parameters
		bool createHybridEncryptedFile(const CString &_fileName, const long _serial, const CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType _asymmetricAlgorithmType, const CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType _symmetricAlgorithmType, const ByteString &_sessionKeyEncrypted, const ByteString &_messageEncrypted);
		// this fucntion tries to parse a hybrid-encrypted file
		bool parseHybridEncryptedFile(const CString &_fileName, long &_serial, CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType &_asymmetricAlgorithmType, CrypTool::Cryptography::Symmetric::SymmetricAlgorithmType &_symmetricAlgorithmType, ByteString &_sessionKeyEncrypted, ByteString &_messageEncrypted);

		// this function tells whether the specified file is a signature file
		bool isFileSignature(const CString &_fileName);
		// this function tries to create a signature file based on the specified parameters
		bool createSignatureFile(const CString &_fileName, const long _serial, const CrypTool::Cryptography::Hash::HashAlgorithmType _hashAlgorithmType, const CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType _asymmetricAlgorithmType, const ByteString &_message, const ByteString &_signature);
		// this function tries to parse a signature file
		bool parseSignatureFile(const CString &_fileName, long &_serial, CrypTool::Cryptography::Hash::HashAlgorithmType &_hashAlgorithmType, CrypTool::Cryptography::Asymmetric::AsymmetricAlgorithmType &_asymmetricAlgorithmType, ByteString &_message, ByteString &_signature);

	}

}

#endif