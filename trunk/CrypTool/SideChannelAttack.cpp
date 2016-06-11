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

#include "stdafx.h"
#include "CrypToolApp.h"
#include "CrypToolBase.h"
#include "CrypToolTools.h"

#include "SideChannelAttack.h"

SCA_Client::SCA_Client() {

}

SCA_Client::~SCA_Client() {

}

void SCA_Client::setHybridEncryptedFile(const HybridEncryptedFile &_hybridEncryptedFile) {
	hybridEncryptedFile = _hybridEncryptedFile;
}

void SCA_Client::transmitHybridEncryptedFile() {
	if (hybridEncryptedFile.isReset()) {
		throw SCA_Error(E_SCA_INTERNAL_ERROR);
	}
	transmittedHybridEncryptedFile = hybridEncryptedFile;
}

const HybridEncryptedFile &SCA_Client::getHybridEncryptedFile() const {
	return hybridEncryptedFile;
}

const HybridEncryptedFile &SCA_Client::getTransmittedHybridEncryptedFile() const {
	return transmittedHybridEncryptedFile;
}

void SCA_Client::resetTransmittedHybridEncryptedFile() {
	transmittedHybridEncryptedFile.reset();
}

SCA_Server::SCA_Server(const int _significantBits, const CString &_keyword) :
	significantBits(_significantBits),
	keyword(_keyword) {

}

SCA_Server::~SCA_Server() {

}

void SCA_Server::setPublicKey(const CrypTool::ByteString &_e, const CrypTool::ByteString &_n) {
	e = _e;
	n = _n;
}

void SCA_Server::setPrivateKey(const CrypTool::ByteString &_d, const CString &_password) {
	d = _d;
	password = _password;
}

bool SCA_Server::receiveHybridEncryptedFile(const HybridEncryptedFile &_hybridEncryptedFile) {
	// create a copy of the specified hybrid-encrypted file
	HybridEncryptedFile hybridEncryptedFile = _hybridEncryptedFile;
	// this variable will hold the plain text
	CrypTool::ByteString byteStringPlainText;
	// this variable will hold the keyword based on which the server 
	// decides whether a decryption was successful or not
	CrypTool::ByteString byteStringKeyword;
	byteStringKeyword = keyword;
	// here we try to decrypt the encrypted session key, and then we 
	// update the newly created hybrid-encrypted file accordingly 
	// (NO PADDING!)
	SHOW_HOUR_GLASS
	const bool padding = false;
	CrypTool::Cryptography::Asymmetric::AsymmetricOperationEncryptOrDecrypt operationAsymmetric(CrypTool::Cryptography::Asymmetric::ASYMMETRIC_ALGORITHM_TYPE_RSA, CrypTool::Cryptography::Asymmetric::ASYMMETRIC_OPERATION_TYPE_DECRYPTION, padding);
	const bool resultAsymmetric = operationAsymmetric.executeOnByteStrings(hybridEncryptedFile.sessionKeyEncrypted, hybridEncryptedFile.certificateSerial, password, hybridEncryptedFile.sessionKey);
	// // truncate session key to appropriate size (depends on the padding option)
	if (padding) hybridEncryptedFile.sessionKey.truncateRight(significantBits / 8);
	else hybridEncryptedFile.sessionKey.truncateLeft(significantBits / 8);
	// here we try to decrypt the cipher text using the decrypted 
	// session key, the result is stored in a temporary variable
	CrypTool::Cryptography::Symmetric::SymmetricOperation operationSymmetric(CrypTool::Cryptography::Symmetric::SYMMETRIC_ALGORITHM_TYPE_AES, CrypTool::Cryptography::Symmetric::SYMMETRIC_OPERATION_TYPE_DECRYPTION);
	const bool resultSymmetric = operationSymmetric.executeOnByteStrings(hybridEncryptedFile.cipherText, hybridEncryptedFile.sessionKey, byteStringPlainText);
	HIDE_HOUR_GLASS
	// this is our result variable
	bool result = false;
	// if either the asymmetric or the symmetric decryption failed, 
	// we don't need to analyze the decrypted message because the 
	// server could not have understood the message
	if (resultAsymmetric && resultSymmetric) {
		// determine whether the decryption was successful
		size_t start;
		size_t end;
		result = byteStringPlainText.findPattern(byteStringKeyword, start, end);
	}
	// store both the adapted hybrid-encrypted file and the decryption result
	vectorReceivedHybridEncryptedFiles.push_back(hybridEncryptedFile);
	vectorResponses.push_back(result);
	return result;
}

void SCA_Server::resetReceivedHybridEncryptedFiles() {
	vectorReceivedHybridEncryptedFiles.clear();
	vectorResponses.clear();
}

void SCA_Server::resetReceivedModifiedHybridEncryptedFiles() {
	// remove all but the very first hybrid encrypted file (the original one)
	while (vectorReceivedHybridEncryptedFiles.size() > 1)
		vectorReceivedHybridEncryptedFiles.pop_back();
	// do the same for the responses (keep the one referring to the original)
	while (vectorResponses.size() > 1)
		vectorResponses.pop_back();
}

int SCA_Server::getNumberOfPositiveResponses() const {
	int numberOfPositiveResponses = 0;
	for (size_t index = 0; index < vectorResponses.size(); index++) {
		if (vectorResponses.at(index)) {
			numberOfPositiveResponses++;
		}
	}
	return numberOfPositiveResponses;
}

SCA_Attacker::SCA_Attacker(const int _significantBits) :
	significantBits(_significantBits),
	z("0"),
	b1(0),
	b2(0),
	y("0"),
	currentStep(1),
	done(false) {

}

SCA_Attacker::~SCA_Attacker() {

}

void SCA_Attacker::setPublicKey(const CrypTool::ByteString &_e, const CrypTool::ByteString &_n) {
	e = _e;
	n = _n;
}

void SCA_Attacker::setInterceptedHybridEncryptedFile(const HybridEncryptedFile &_interceptedHybridEncryptedFile) {
	interceptedHybridEncryptedFile = _interceptedHybridEncryptedFile;
}

const HybridEncryptedFile &SCA_Attacker::getInterceptedHybridEncryptedFile() const {
	return interceptedHybridEncryptedFile;
}

void SCA_Attacker::resetInterceptedHybridEncryptedFile() {
	interceptedHybridEncryptedFile.reset();
}

void SCA_Attacker::resetAttack() {
	// reset algorithm variables
	z = "0";
	b1 = significantBits;
	b2 = 0;
	y = "0";
	currentStep = 1;
	// reset status variables
	done = false;
	vectorModifiedHybridEncryptedFiles.clear();
	calculatedSessionKey.reset();
}

HybridEncryptedFile SCA_Attacker::createNextHybridEncryptedFile() {
	// the result variable
	HybridEncryptedFile nextHybridEncryptedFile;
	if (vectorModifiedHybridEncryptedFiles.empty()) {
		nextHybridEncryptedFile = interceptedHybridEncryptedFile;
	}
	else {
		nextHybridEncryptedFile = vectorModifiedHybridEncryptedFiles.back();
	}
	// *** STEP 1 ***
	if (currentStep == 1) {
		// calculate z based on B and N
		Big base = "2";
		int exp = b1;
		Big B = pow(base, exp);
		Big N = (char*)(LPCTSTR)(n.toString());
		// assign z
		z = computeZ(N, B);
		// copy b to b'
		b2 = b1;
		// next step
		currentStep++;
	}
	// *** STEP 2 ***
	if (currentStep == 2) {
		// cNew = cOld * (2z + 1)^e % N
		Big oldChallenge = "0";
		convertByteStringToBig(nextHybridEncryptedFile.sessionKeyEncrypted, oldChallenge);
		Big publicKey = (char*)(LPCTSTR)(e.toString());
		Big modulus = (char*)(LPCTSTR)(n.toString());
		Big newChallenge;
		newChallenge = (2 * z) + 1;
		newChallenge = pow(newChallenge, publicKey, modulus);
		newChallenge = (oldChallenge * newChallenge) % modulus;
		convertBigToByteString(newChallenge, nextHybridEncryptedFile.sessionKeyEncrypted);
		vectorModifiedHybridEncryptedFiles.push_back(nextHybridEncryptedFile);
		return nextHybridEncryptedFile;
	}
	// *** STEP 3 ***
	if (currentStep == 3) {
		y = z / 2;
		currentStep++;
	}
	// *** STEP 4 ***
	if (currentStep == 4) {
		// b' + 1 times...
		while (b2 >= 0) {
			// cNew = cOld * (z+y+1)^e % N
			Big oldChallenge = "0";
			convertByteStringToBig(interceptedHybridEncryptedFile.sessionKeyEncrypted, oldChallenge);
			Big publicKey = (char*)(LPCTSTR)(e.toString());
			Big modulus = (char*)(LPCTSTR)(n.toString());
			Big newChallenge;
			newChallenge = (z + y + 1);
			newChallenge = pow(newChallenge, publicKey, modulus);
			newChallenge = (oldChallenge * newChallenge) % modulus;
			convertBigToByteString(newChallenge, nextHybridEncryptedFile.sessionKeyEncrypted);
			vectorModifiedHybridEncryptedFiles.push_back(nextHybridEncryptedFile);
			b2 -= 1;
			return nextHybridEncryptedFile;
		}
		currentStep++;
	}
	// *** STEP 5 ***
	if (currentStep == 5) {
		// final calculation
		Big modulus = (char*)(LPCTSTR)(n.toString());
		Big Z = z;
		Big finalChallenge = (modulus / (Z + 1));
		Big bitMask;
		// entsprechende Bitmaske erstellen
		bitMask = "2";
		bitMask = pow(bitMask, significantBits);
		// nur die least significant bits (LSB) betrachten
		finalChallenge = finalChallenge % bitMask;
		convertBigToByteString(finalChallenge, calculatedSessionKey);
		done = true;
	}
	// return the result variable
	return nextHybridEncryptedFile;
}

void SCA_Attacker::processServerResponse(const bool _response) {
	// store server response
	vectorServerResponses.push_back(_response);
	// continue with the algorithm
	if (currentStep == 2) {
		if (_response) {
			z *= 2;
			if (b2 == 0) {
				currentStep = 3;
			}
			else {
				b2 -= 1;
			}
			return;
		}
		currentStep++;
	}
	if (currentStep == 4) {
		if (_response) {
			z += y;
		}
		y /= 2;
	}
}

Big SCA_Attacker::computeZ(const Big &_N, const Big &_B) const {
	// calculate big length of RSA modul _N
	CString stringN;
	BigToCString(_N, stringN, 10);
	const double bitLengthModul = ceil(BitLength(stringN, 10));
	// calculate bit length of known boundaries (2^b = _B)
	const int b = log2(_B);
	// if the condition L(N) > 3b+c is not met, throw an exception
	if (!(bitLengthModul > (float)(3 * b + 3))) {
		throw SCA_Error(E_SCA_ATTACK_CONDITIONS_NOT_MET);
	}
	// calculate _N/_B which is required for Z
	Big fraction = (_N / _B);
	Big Z = "0";
	Big two = "2";
	for (int i = (int)bitLengthModul; i>0; i--) {
		if (pow(two, i) < fraction) {
			Z = pow(two, i);
			break;
		}
	}

	return Z;
}

int SCA_Attacker::log2(const Big &_number) const {
	Big number = _number;
	int i = 0;
	while (number != "0") {
		number /= 2;
		if (number == "0") {
			break;
		}
		i++;
	}
	return i;
}

void SCA_Attacker::convertByteStringToBig(const CrypTool::ByteString &_byteString, Big &_big) const {
	_big = "0";
	for (size_t index = 0; index < _byteString.getByteLength(); index++) {
		_big = _big * 256 + _byteString.getByteDataConst()[index];
	}
}

void SCA_Attacker::convertBigToByteString(const Big &_big, CrypTool::ByteString &_byteString) const {
	_byteString.reset();
	Big big = _big;
	Big temp = "0";
	while (big > 0) {
		temp = big % 256;
		big /= 256;
		CString stringNumber;
		BigToCString(temp, stringNumber, 10);
		const long number = atol(stringNumber);
		unsigned char character = (unsigned char)(number);
		_byteString += character;
	}
}

SCA_Error::SCA_Error(const long _errorCode) :
	errorCode(_errorCode) {

}

SCA_Error::~SCA_Error() {

}
