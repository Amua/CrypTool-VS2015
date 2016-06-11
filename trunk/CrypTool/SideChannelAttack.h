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

#ifndef _SIDECHANNELATTACK_H_
#define _SIDECHANNELATTACK_H_

// internally, this struct represents a hybrid-encrypted file containing 
// the serial number of the receiver's certificate, the session key (if 
// accessible, i.e. it is not for files encrypted by other users), the 
// encrypted session key, and the cipher text
struct HybridEncryptedFile {
	// data
	long certificateSerial;
	CrypTool::ByteString sessionKey;
	CrypTool::ByteString sessionKeyEncrypted;
	CrypTool::ByteString cipherText;
	// construction
	HybridEncryptedFile() : certificateSerial(0) { }
	// operator implementation
	void operator=(const HybridEncryptedFile &_hybridEncryptedFile) {
		certificateSerial = _hybridEncryptedFile.certificateSerial;
		sessionKey = _hybridEncryptedFile.sessionKey;
		sessionKeyEncrypted = _hybridEncryptedFile.sessionKeyEncrypted;
		cipherText = _hybridEncryptedFile.cipherText;
	}
	// reset the hybrid-encrypted file
	void reset() {
		certificateSerial = 0;
		sessionKey.reset();
		sessionKeyEncrypted.reset();
		cipherText.reset();
	}
	// whether the hybrid-encrypted file is reset
	bool isReset() const {
		if (certificateSerial > 0) return false;
		if (sessionKey.getByteLength() > 0) return false;
		if (sessionKeyEncrypted.getByteLength() > 0) return false;
		if (cipherText.getByteLength() > 0) return false;
		return true;
	}
};

class SCA_Client {
public:
	SCA_Client();
	virtual ~SCA_Client();
public:
	void setHybridEncryptedFile(const HybridEncryptedFile &_hybridEncryptedFile);
	void transmitHybridEncryptedFile();
	const HybridEncryptedFile &getHybridEncryptedFile() const;
	const HybridEncryptedFile &getTransmittedHybridEncryptedFile() const;
	void resetTransmittedHybridEncryptedFile();
	const CrypTool::ByteString &getSessionKey() const { return hybridEncryptedFile.sessionKey; }
private:
	HybridEncryptedFile hybridEncryptedFile;
	HybridEncryptedFile transmittedHybridEncryptedFile;
};

class SCA_Server {
public:
	SCA_Server(const int _significantBits, const CString &_keyword);
	virtual ~SCA_Server();
public:
	void setPublicKey(const CrypTool::ByteString &_e, const CrypTool::ByteString &_n);
	void setPrivateKey(const CrypTool::ByteString &_d, const CString &_password);
	bool receiveHybridEncryptedFile(const HybridEncryptedFile &_hybridEncryptedFile);
	void resetReceivedHybridEncryptedFiles();
	void resetReceivedModifiedHybridEncryptedFiles();
	const std::vector<HybridEncryptedFile> &getReceivedHybridEncryptedFiles() const { return vectorReceivedHybridEncryptedFiles; }
	const std::vector<bool> &getResponses() const { return vectorResponses; }
	int getNumberOfPositiveResponses() const;
	const CrypTool::ByteString &getPublicKeyE() const { return e; }
	const CrypTool::ByteString &getPublicKeyN() const { return n; }
	const CrypTool::ByteString &getPrivateKeyD() const { return d; }
private:
	const int significantBits;
	const CString keyword;
private:
	CrypTool::ByteString e;
	CrypTool::ByteString n;
	CrypTool::ByteString d;
	CString password;
private:
	std::vector<HybridEncryptedFile> vectorReceivedHybridEncryptedFiles;
	std::vector<bool> vectorResponses;
};

class SCA_Attacker {
public:
	SCA_Attacker(const int _significantBits);
	virtual ~SCA_Attacker();
public:
	void setPublicKey(const CrypTool::ByteString &_e, const CrypTool::ByteString &_n);
	void setInterceptedHybridEncryptedFile(const HybridEncryptedFile &_interceptedHybridEncryptedFile);
	const HybridEncryptedFile &getInterceptedHybridEncryptedFile() const;
	const std::vector<HybridEncryptedFile> &getModifiedHybridEncryptedFiles() const { return vectorModifiedHybridEncryptedFiles; }
	const std::vector<bool> &getServerResponses() const { return vectorServerResponses; }
	const CrypTool::ByteString &getCalculatedSessionKey() const { return calculatedSessionKey; }
	void resetInterceptedHybridEncryptedFile();
	void resetAttack();
	bool isDone() const { return done; }
	HybridEncryptedFile createNextHybridEncryptedFile();
	void processServerResponse(const bool _response);
private:
	const int significantBits;
private:
	CrypTool::ByteString e;
	CrypTool::ByteString n;
private:
	HybridEncryptedFile interceptedHybridEncryptedFile;
	HybridEncryptedFile modifiedHybridEncryptedFile;
private:
	Big z;
	int b1;
	int b2;
	Big y;
	int currentStep;
private:
	bool done;
	std::vector<HybridEncryptedFile> vectorModifiedHybridEncryptedFiles;
	CrypTool::ByteString calculatedSessionKey;
	std::vector<bool> vectorServerResponses;
private:
	Big computeZ(const Big &_N, const Big &_B) const;
	int log2(const Big &_number) const;
	void convertByteStringToBig(const CrypTool::ByteString &_byteString, Big &_big) const;
	void convertBigToByteString(const Big &_big, CrypTool::ByteString &_byteString) const;
};

class SCA_Error {
public:
	SCA_Error(const long _errorCode);
	virtual ~SCA_Error();
public:
	long getErrorCode() const { return errorCode; };
private:
	const long errorCode;
};

#define E_SCA_INTERNAL_ERROR								1
#define	E_SCA_MEMORY_ALLOCATION								2
#define E_SCA_HYBENCFILE_EXTRACTION							4
#define E_SCA_ATTACK_CONDITIONS_NOT_MET						8
#define E_SCA_MIRACL_ERROR									16
#define E_SCA_WRONG_PSE_PIN									32
#define E_SCA_TIMER_NOT_AVAILABLE							64

#endif
