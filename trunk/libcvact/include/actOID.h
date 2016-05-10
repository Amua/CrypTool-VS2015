//////////////////////////////////////////////////////////////////////////////////
// Name:      actOID.h
// Product:   cv act library
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_OID_H
#define ACT_OID_H

#include "actEnv.h"
#include "actBlob.h"

#if defined(ACT_MSC)
#	pragma warning(push)
#	pragma warning(disable : 4305) // Verkuerzung von 'static const int' in 'static const unsigned char'
#	pragma warning(disable : 4309) // Verkuerzung eines konstanten Wertes
#endif

#define CV_OID_DEF(x)				(act::Blob((x), (x) + sizeof((x))))

//! \brief   1.2.840.10045.4.1
//! \details ECDSA cvECDSA
static const act::byte cvOID_cvECDSA[] = {0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x01};
//! \brief   1.2.840.113549.1.9.1
//! \details Alternate Name cvAlternateName
static const act::byte cvOID_cvAlternateName[] = {0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x09, 0x01};

//! \brief   0.2.262.1.10
//! \details Deutsche Telekom Telesec 
static const act::byte cvOID_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A};
//! \brief   0.2.262.1.10.0
//! \details Telesec extension 
static const act::byte cvOID_extension[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x00};
//! \brief   0.2.262.1.10.1
//! \details Telesec mechanism 
static const act::byte cvOID_mechanism[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01};
//! \brief   0.2.262.1.10.1.0
//! \details Telesec mechanism authentication 
static const act::byte cvOID_authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00};
//! \brief   0.2.262.1.10.1.0.1
//! \details Telesec authentication passwordAuthentication 
static const act::byte cvOID_passwordAuthentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x01};
//! \brief   0.2.262.1.10.1.0.2
//! \details Telesec authentication protectedPasswordAuthentication 
static const act::byte cvOID_protectedPasswordAuthentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x02};
//! \brief   0.2.262.1.10.1.0.3
//! \details Telesec authentication oneWayX509Authentication 
static const act::byte cvOID_oneWayX509Authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x03};
//! \brief   0.2.262.1.10.1.0.4
//! \details Telesec authentication twoWayX509Authentication 
static const act::byte cvOID_twoWayX509Authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x04};
//! \brief   0.2.262.1.10.1.0.5
//! \details Telesec authentication threeWayX509Authentication 
static const act::byte cvOID_threeWayX509Authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x05};
//! \brief   0.2.262.1.10.1.0.6
//! \details Telesec authentication oneWayISO9798Authentication 
static const act::byte cvOID_oneWayISO9798Authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x06};
//! \brief   0.2.262.1.10.1.0.7
//! \details Telesec authentication twoWayISO9798Authentication 
static const act::byte cvOID_twoWayISO9798Authentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x07};
//! \brief   0.2.262.1.10.1.0.8
//! \details Telesec authentication telekomAuthentication 
static const act::byte cvOID_telekomAuthentication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x00, 0x08};
//! \brief   0.2.262.1.10.1.1
//! \details Telesec mechanism signature 
static const act::byte cvOID_signature[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01};
//! \brief   0.2.262.1.10.1.1.1
//! \details Telesec mechanism md4WithRSAAndISO9697 
static const act::byte cvOID_md4WithRSAAndISO9697[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x01};
//! \brief   0.2.262.1.10.1.1.2
//! \details Telesec mechanism md4WithRSAAndTelesecSignatureStandard 
static const act::byte cvOID_md4WithRSAAndTelesecSignatureStandard[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x02};
//! \brief   0.2.262.1.10.1.1.3
//! \details Telesec mechanism md5WithRSAAndISO9697 
static const act::byte cvOID_md5WithRSAAndISO9697[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x03};
//! \brief   0.2.262.1.10.1.1.4
//! \details Telesec mechanism md5WithRSAAndTelesecSignatureStandard 
static const act::byte cvOID_md5WithRSAAndTelesecSignatureStandard[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x04};
//! \brief   0.2.262.1.10.1.1.5
//! \details Telesec mechanism ripemd160WithRSAAndTelekomSignatureStandard 
static const act::byte cvOID_ripemd160WithRSAAndTelekomSignatureStandard[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x05};
//! \brief   0.2.262.1.10.1.1.9
//! \details Telesec signature hbciRsaSignature 
static const act::byte cvOID_hbciRsaSignature[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x01, 0x09};
//! \brief   0.2.262.1.10.1.2
//! \details Telesec mechanism encryption 
static const act::byte cvOID_encryption[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02};
//! \brief   0.2.262.1.10.1.2.0
//! \details Telesec encryption none 
static const act::byte cvOID_none[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x00};
//! \brief   0.2.262.1.10.1.2.1
//! \details Telesec encryption rsaTelesec 
static const act::byte cvOID_rsaTelesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x01};
//! \brief   0.2.262.1.10.1.2.2
//! \details Telesec encryption des 
static const act::byte cvOID_des[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02};
//! \brief   0.2.262.1.10.1.2.2.1
//! \details Telesec encryption desECB 
static const act::byte cvOID_desECB[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x01};
//! \brief   0.2.262.1.10.1.2.2.2
//! \details Telesec encryption desCBC 
static const act::byte cvOID_desCBC[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x02};
//! \brief   0.2.262.1.10.1.2.2.3
//! \details Telesec encryption desOFB 
static const act::byte cvOID_desOFB[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x03};
//! \brief   0.2.262.1.10.1.2.2.4
//! \details Telesec encryption desCFB8 
static const act::byte cvOID_desCFB8[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x04};
//! \brief   0.2.262.1.10.1.2.2.5
//! \details Telesec encryption desCFB64 
static const act::byte cvOID_desCFB64[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x02, 0x05};
//! \brief   0.2.262.1.10.1.2.3
//! \details Telesec encryption des3 
static const act::byte cvOID_des3[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03};
//! \brief   0.2.262.1.10.1.2.3.1
//! \details Telesec encryption des3ECB 
static const act::byte cvOID_des3ECB[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x01};
//! \brief   0.2.262.1.10.1.2.3.2
//! \details Telesec encryption des3CBC 
static const act::byte cvOID_des3CBC[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x02};
//! \brief   0.2.262.1.10.1.2.3.3
//! \details Telesec encryption des3OFB 
static const act::byte cvOID_des3OFB[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x03};
//! \brief   0.2.262.1.10.1.2.3.4
//! \details Telesec encryption des3CFB8 
static const act::byte cvOID_des3CFB8[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x04};
//! \brief   0.2.262.1.10.1.2.3.5
//! \details Telesec encryption des3CFB64 
static const act::byte cvOID_des3CFB64[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x03, 0x05};
//! \brief   0.2.262.1.10.1.2.4
//! \details Telesec encryption magenta 
static const act::byte cvOID_magenta[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x04};
//! \brief   0.2.262.1.10.1.2.5
//! \details Telesec encryption idea 
static const act::byte cvOID_idea[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05};
//! \brief   0.2.262.1.10.1.2.5.1
//! \details Telesec encryption ideaECB 
static const act::byte cvOID_ideaECB_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x01};
//! \brief   0.2.262.1.10.1.2.5.2
//! \details Telesec encryption ideaCBC 
static const act::byte cvOID_ideaCBC_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x02};
//! \brief   0.2.262.1.10.1.2.5.3
//! \details Telesec encryption ideaOFB 
static const act::byte cvOID_ideaOFB_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x03};
//! \brief   0.2.262.1.10.1.2.5.4
//! \details Telesec encryption ideaCFB8 
static const act::byte cvOID_ideaCFB8_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x04};
//! \brief   0.2.262.1.10.1.2.5.5
//! \details Telesec encryption ideaCFB64 
static const act::byte cvOID_ideaCFB64_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x02, 0x05, 0x05};
//! \brief   0.2.262.1.10.1.3
//! \details Telesec mechanism oneWayFunction 
static const act::byte cvOID_oneWayFunction[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03};
//! \brief   0.2.262.1.10.1.3.1
//! \details Telesec one-way function md4 
static const act::byte cvOID_md4_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x01};
//! \brief   0.2.262.1.10.1.3.2
//! \details Telesec one-way function md5 
static const act::byte cvOID_md5_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x02};
//! \brief   0.2.262.1.10.1.3.3
//! \details Telesec one-way function sqModNX509 
static const act::byte cvOID_sqModNX509[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x03};
//! \brief   0.2.262.1.10.1.3.4
//! \details Telesec one-way function sqModNISO 
static const act::byte cvOID_sqModNISO[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x04};
//! \brief   0.2.262.1.10.1.3.5
//! \details Telesec one-way function ripemd128 
static const act::byte cvOID_ripemd128[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x05};
//! \brief   0.2.262.1.10.1.3.6
//! \details Telesec one-way function hashUsingBlockCipher 
static const act::byte cvOID_hashUsingBlockCipher[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x06};
//! \brief   0.2.262.1.10.1.3.7
//! \details Telesec one-way function                     mac 
static const act::byte cvOID_mac[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x07};
//! \brief   0.2.262.1.10.1.3.8
//! \details Telesec one-way function ripemd160 
static const act::byte cvOID_ripemd160[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x08};
//! \brief   0.2.262.1.10.1.4
//! \details Telesec mechanism fecFunction 
static const act::byte cvOID_fecFunction[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x04};
//! \brief   0.2.262.1.10.1.4.1
//! \details Telesec mechanism reedSolomon 
static const act::byte cvOID_reedSolomon[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x04, 0x01};
//! \brief   0.2.262.1.10.2
//! \details Telesec module 
static const act::byte cvOID_module_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02};
//! \brief   0.2.262.1.10.2.0
//! \details Telesec module algorithms 
static const act::byte cvOID_algorithms[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x00};
//! \brief   0.2.262.1.10.2.1
//! \details Telesec module attributeTypes 
static const act::byte cvOID_attributeTypes[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x01};
//! \brief   0.2.262.1.10.2.2
//! \details Telesec module certificateTypes 
static const act::byte cvOID_certificateTypes[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x02};
//! \brief   0.2.262.1.10.2.3)..				Telesec module messageTypes 
static const act::byte cvOID_messageTypes[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x03};
//! \brief   0.2.262.1.10.2.4
//! \details Telesec module plProtocol 
static const act::byte cvOID_plProtocol[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x04};
//! \brief   0.2.262.1.10.2.5
//! \details Telesec module smeAndComponentsOfSme 
static const act::byte cvOID_smeAndComponentsOfSme[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x05};
//! \brief   0.2.262.1.10.2.6
//! \details Telesec module fec 
static const act::byte cvOID_fec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x06};
//! \brief   0.2.262.1.10.2.7
//! \details Telesec module usefulDefinitions 
static const act::byte cvOID_usefulDefinitions[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x07};
//! \brief   0.2.262.1.10.2.8
//! \details Telesec module stefiles 
static const act::byte cvOID_stefiles[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x08};
//! \brief   0.2.262.1.10.2.9
//! \details Telesec module sadmib 
static const act::byte cvOID_sadmib[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x09};
//! \brief   0.2.262.1.10.2.10
//! \details Telesec module electronicOrder 
static const act::byte cvOID_electronicOrder[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0A};
//! \brief   0.2.262.1.10.2.11
//! \details Telesec module telesecTtpAsymmetricApplication 
static const act::byte cvOID_telesecTtpAsymmetricApplication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0B};
//! \brief   0.2.262.1.10.2.12).....			Telesec module telesecTtpBasisApplication 
static const act::byte cvOID_telesecTtpBasisApplication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0C};
//! \brief   0.2.262.1.10.2.13).......		Telesec module telesecTtpMessages 
static const act::byte cvOID_telesecTtpMessages[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0D};
//! \brief   0.2.262.1.10.2.14).......		Telesec module telesecTtpTimeStampApplication 
static const act::byte cvOID_telesecTtpTimeStampApplication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x02, 0x0E};
//! \brief   0.2.262.1.10.3
//! \details Telesec objectClass 
static const act::byte cvOID_objectClass_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03};
//! \brief   0.2.262.1.10.3.0
//! \details Telesec object class telesecOtherName 
static const act::byte cvOID_telesecOtherName_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x00};
//! \brief   0.2.262.1.10.3.1
//! \details Telesec object class directory 
static const act::byte cvOID_directory_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x01};
//! \brief   0.2.262.1.10.3.2
//! \details Telesec object class directoryType 
static const act::byte cvOID_directoryType_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x02};
//! \brief   0.2.262.1.10.3.3
//! \details Telesec object class directroyGroup 
static const act::byte cvOID_directroyGroup_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x03};
//! \brief   0.2.262.1.10.3.4
//! \details Telesec object class directoryUser 
static const act::byte cvOID_directoryUser_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x04};
//! \brief   0.2.262.1.10.3.5
//! \details Telesec object class symmetricKeyEntry 
static const act::byte cvOID_symmetricKeyEntry[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x03, 0x05};
//! \brief   0.2.262.1.10.4
//! \details Telesec package 
static const act::byte cvOID_package[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x04};
//! \brief   0.2.262.1.10.5
//! \details Telesec parameter 
static const act::byte cvOID_parameter[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x05};
//! \brief   0.2.262.1.10.6
//! \details Telesec nameBinding 
static const act::byte cvOID_nameBinding[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x06};
//! \brief   0.2.262.1.10.7
//! \details Telesec attribute 
static const act::byte cvOID_attribute_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07};
//! \brief   0.2.262.1.10.7.0
//! \details Telesec attribute applicationGroupIdentifier 
static const act::byte cvOID_applicationGroupIdentifier[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x00};
//! \brief   0.2.262.1.10.7.1
//! \details Telesec attribute certificateType 
static const act::byte cvOID_certificateType[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x01};
//! \brief   0.2.262.1.10.7.2
//! \details Telesec attribute telesecCertificate 
static const act::byte cvOID_Certificate_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x02};
//! \brief   0.2.262.1.10.7.3
//! \details Telesec attribute certificateNumber 
static const act::byte cvOID_certificateNumber[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x03};
//! \brief   0.2.262.1.10.7.4
//! \details Telesec attribute certificateRevocationList 
static const act::byte cvOID_certificateRevocationList_Telesec[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x04};
//! \brief   0.2.262.1.10.7.5
//! \details Telesec attribute creationDate 
static const act::byte cvOID_creationDate[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x05};
//! \brief   0.2.262.1.10.7.6)....			Telesec attribute issuer 
static const act::byte cvOID_issuer[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x06};
//! \brief   0.2.262.1.10.7.7
//! \details Telesec attribute namingAuthority 
static const act::byte cvOID_namingAuthority[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x07};
//! \brief   0.2.262.1.10.7.8
//! \details Telesec attribute publicKeyDirectory 
static const act::byte cvOID_publicKeyDirectory[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x08};
//! \brief   0.2.262.1.10.7.9)..				Telesec attribute securityDomain 
static const act::byte cvOID_securityDomain[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x09};
//! \brief   0.2.262.1.10.7.10).....			Telesec attribute subject 
static const act::byte cvOID_subject[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0A};
//! \brief   0.2.262.1.10.7.11
//! \details Telesec attribute timeOfRevocation 
static const act::byte cvOID_timeOfRevocation[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0B};
//! \brief   0.2.262.1.10.7.12
//! \details Telesec attribute userGroupReference 
static const act::byte cvOID_userGroupReference[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0C};
//! \brief   0.2.262.1.10.7.13
//! \details Telesec attribute validity 
static const act::byte cvOID_validity[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0D};
//! \brief   0.2.262.1.10.7.14
//! \details Telesec attribute zert93 
static const act::byte cvOID_zert93[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0E};
//! \brief   0.2.262.1.10.7.15
//! \details Telesec attribute securityMessEnv 
static const act::byte cvOID_securityMessEnv[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x0F};
//! \brief   0.2.262.1.10.7.16
//! \details Telesec attribute anonymizedPublicKeyDirectory 
static const act::byte cvOID_anonymizedPublicKeyDirectory[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x10};
//! \brief   0.2.262.1.10.7.17
//! \details Telesec attribute telesecGivenName 
static const act::byte cvOID_telesecGivenName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x11};
//! \brief   0.2.262.1.10.7.18).				Telesec attribute nameAdditions 
static const act::byte cvOID_nameAdditions[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x12};
//! \brief   0.2.262.1.10.7.19
//! \details Telesec attribute telesecPostalCode 
static const act::byte cvOID_telesecPostalCode[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x13};
//! \brief   0.2.262.1.10.7.20
//! \details Telesec attribute nameDistinguisher 
static const act::byte cvOID_nameDistinguisher[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x14};
//! \brief   0.2.262.1.10.7.21
//! \details Telesec attribute telesecCertificateList 
static const act::byte cvOID_telesecCertificateList[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x15};
//! \brief   0.2.262.1.10.7.22
//! \details Telesec attribute teletrustCertificateList 
static const act::byte cvOID_teletrustCertificateList[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x16};
//! \brief   0.2.262.1.10.7.23)...			Telesec attribute x509CertificateList 
static const act::byte cvOID_x509CertificateList[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x17};
//! \brief   0.2.262.1.10.7.24
//! \details Telesec attribute                          timeOfIssue 
static const act::byte cvOID_timeOfIssue[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x18};
//! \brief   0.2.262.1.10.7.25
//! \details Telesec attribute physicalCardNumber 
static const act::byte cvOID_physicalCardNumber[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x19};
//! \brief   0.2.262.1.10.7.26)........		Telesec attribute fileType 
static const act::byte cvOID_fileType[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1A};
//! \brief   0.2.262.1.10.7.27
//! \details Telesec attribute ctlFileIsArchive 
static const act::byte cvOID_ctlFileIsArchive[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1B};
//! \brief   0.2.262.1.10.7.28)........		Telesec attribute emailAddress 
static const act::byte cvOID_emailAddress[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1C};
//! \brief   0.2.262.1.10.7.29)........		Telesec attribute certificateTemplateList 
static const act::byte cvOID_certificateTemplateList[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1D};
//! \brief   0.2.262.1.10.7.30)........		Telesec attribute directoryName 
static const act::byte cvOID_directoryName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1E};
//! \brief   0.2.262.1.10.7.31)........		Telesec attribute directoryTypeName 
static const act::byte cvOID_directoryTypeName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x1F};
//! \brief   0.2.262.1.10.7.32
//! \details Telesec attribute directoryGroupName 
static const act::byte cvOID_directoryGroupName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x20};
//! \brief   0.2.262.1.10.7.33
//! \details Telesec attribute directoryUserName 
static const act::byte cvOID_directoryUserName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x21};
//! \brief   0.2.262.1.10.7.34
//! \details Telesec attribute revocationFlag 
static const act::byte cvOID_revocationFlag[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x22};
//! \brief   0.2.262.1.10.7.35
//! \details Telesec attribute symmetricKeyEntryName 
static const act::byte cvOID_symmetricKeyEntryName[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x23};
//! \brief   0.2.262.1.10.7.36
//! \details Telesec attribute glNumber 
static const act::byte cvOID_glNumber[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x24};
//! \brief   0.2.262.1.10.7.37
//! \details Telesec attribute goNumber 
static const act::byte cvOID_goNumber[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x25};
//! \brief   0.2.262.1.10.7.38
//! \details Telesec attribute gKeyData 
static const act::byte cvOID_gKeyData[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x26};
//! \brief   0.2.262.1.10.7.39
//! \details Telesec attribute zKeyData 
static const act::byte cvOID_zKeyData[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x27};
//! \brief   0.2.262.1.10.7.40
//! \details Telesec attribute ktKeyData 
static const act::byte cvOID_ktKeyData[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x28};
//! \brief   0.2.262.1.10.7.41
//! \details Telesec attribute ktKeyNumber 
static const act::byte cvOID_ktKeyNumber[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x2A};
//! \brief   0.2.262.1.10.7.51
//! \details Telesec attribute timeOfRevocationGen 
static const act::byte cvOID_timeOfRevocationGen[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x33};
//! \brief   0.2.262.1.10.7.52)....			Telesec attribute liabilityText 
static const act::byte cvOID_liabilityText[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x07, 0x34};
//! \brief   0.2.262.1.10.8
//! \details Telesec attributeGroup 
static const act::byte cvOID_attributeGroup[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x08};
//! \brief   0.2.262.1.10.9
//! \details Telesec action 
static const act::byte cvOID_action[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x09};
//! \brief   0.2.262.1.10.10
//! \details Telesec notification 
static const act::byte cvOID_notification[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0A};
//! \brief   0.2.262.1.10.11
//! \details Telesec snmp-mibs 
static const act::byte cvOID_snmp_mibs[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0B};
//! \brief   0.2.262.1.10.11.1
//! \details Telesec SNMP MIBs securityApplication 
static const act::byte cvOID_securityApplication[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0B, 0x01};
//! \brief   0.2.262.1.10.12
//! \details Telesec certAndCrlExtensionDefinitions 
static const act::byte cvOID_certAndCrlExtensionDefinitions[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C};
//! \brief   0.2.262.1.10.12.0
//! \details Telesec cert/CRL extension certExtensionLiabilityLimitationExt 
static const act::byte cvOID_certExtensionLiabilityLimitationExt[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x00};
//! \brief   0.2.262.1.10.12.1
//! \details Telesec cert/CRL extension telesecCertIdExt 
static const act::byte cvOID_telesecCertIdExt[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x01};
//! \brief   0.2.262.1.10.12.2
//! \details Telesec cert/CRL extension telesecPolicyIdentifier 
static const act::byte cvOID_telesecPolicyIdentifier[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x02};
//! \brief   0.2.262.1.10.12.3
//! \details Telesec cert/CRL extension telesecPolicyQualifierID 
static const act::byte cvOID_telesecPolicyQualifierID[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x03};
//! \brief   0.2.262.1.10.12.4
//! \details Telesec cert/CRL extension telesecCRLFilteredExt 
static const act::byte cvOID_telesecCRLFilteredExt[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x04};
//! \brief   0.2.262.1.10.12.5
//! \details Telesec cert/CRL extension telesecCRLFilterExt 
static const act::byte cvOID_telesecCRLFilterExt[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x05};
//! \brief   0.2.262.1.10.12.6
//! \details Telesec cert/CRL extension telesecNamingAuthorityExt 
static const act::byte cvOID_telesecNamingAuthorityExt[] = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x0C, 0x06};
//! \brief   0.9.2342.19200300.1.3
//! \details Some oddball X.500 attribute collection rfc822Mailbox 
static const act::byte cvOID_rfc822Mailbox[] = { 0x09, 0x92, 0x26, 0x89, 0x93, 0xF2, 0x2C, 0x01, 0x03};
//! \brief   0.9.2342.19200300.100.1.25
//! \details Men are from Mars, this OID is from Pluto domainComponent 
static const act::byte cvOID_domainComponent[] = { 0x09, 0x92, 0x26, 0x89, 0x93, 0xF2, 0x2C, 0x64, 0x01, 0x019};
//! \brief   1.2.36.75878867.1.100.1.1
//! \details Certificates Australia CA Certificates Australia policyIdentifier 
static const act::byte cvOID_Certificates_Australia_policyIdentifier[] = { 0x2A, 0x24, 0xA4, 0x97, 0xA3, 0x53, 0x01, 0x64, 0x01, 0x01};
//! \brief   1.2.36.68980861.1.1.2
//! \details Signet CA Signet personal 
static const act::byte cvOID_Signet_personal[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x02};
//! \brief   1.2.36.68980861.1.1.3
//! \details Signet CA Signet business 
static const act::byte cvOID_Signet_business[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x03};
//! \brief   1.2.36.68980861.1.1.4
//! \details Signet CA Signet legal 
static const act::byte cvOID_Signet_legal[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x04};
//! \brief   1.2.36.68980861.1.1.10
//! \details Signet CA Signet pilot 
static const act::byte cvOID_Signet_pilot[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x0A};
//! \brief   1.2.36.68980861.1.1.11
//! \details Signet CA Signet intraNet 
static const act::byte cvOID_Signet_intraNet[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x0B};
//! \brief   1.2.36.68980861.1.1.20
//! \details Signet CA Signet securityPolicy 
static const act::byte cvOID_Signet_securityPolicy[] = { 0x2A, 0x24, 0xA0, 0xF2, 0xA0, 0x7D, 0x01, 0x01, 0x14};
//! \brief   1.2.392.200011.61.1.1.1
//! \details Mitsubishi security algorithm symmetric-encryption-algorithm 
static const act::byte cvOID_symmetric_encryption_algorithm[] = { 0x2A, 0x83, 0x08, 0x8C, 0x1A, 0x4B, 0x3D, 0x01, 0x01, 0x01};
//! \brief   1.2.392.200011.61.1.1.1.1
//! \details Mitsubishi security algorithm misty1-cbc 
static const act::byte cvOID_misty1_cbc[] = { 0x2A, 0x83, 0x08, 0x8C, 0x9A, 0x4B, 0x3D, 0x01, 0x01, 0x01, 0x01};
//! \brief   1.2.752.34.1
//! \details SEIS Project seis-cp 
static const act::byte cvOID_seis_cp[] = { 0x2A, 0x85, 0x70, 0x22, 0x01};
//! \brief   1.2.752.34.1.1
//! \details SEIS Project certificate policies SEIS high-assurnace certificatePolicy 
static const act::byte cvOID_SEIS_high_assurnace_certificatePolicy[] = { 0x2A, 0x85, 0x70, 0x22, 0x01, 0x01};
//! \brief   1.2.752.34.1.2
//! \details SEIS Project certificate policies SEIS GAK certificatePolicy 
static const act::byte cvOID_SEIS_GAK_certificatePolicy[] = { 0x2A, 0x85, 0x70, 0x22, 0x01, 0x02};
//! \brief   1.2.752.34.2
//! \details SEIS Project SEIS pe 
static const act::byte cvOID_SEIS_pe[] = { 0x2A, 0x85, 0x70, 0x22, 0x02};
//! \brief   1.2.752.34.3
//! \details SEIS Project SEIS at 
static const act::byte cvOID_SEIS_at[] = { 0x2A, 0x85, 0x70, 0x22, 0x03};
//! \brief   1.2.752.34.3.1
//! \details SEIS Project attribute SEIS at-personalIdentifier 
static const act::byte cvOID_SEIS_at_personalIdentifier[] = { 0x2A, 0x85, 0x70, 0x22, 0x03, 0x01};
//! \brief   1.2.840.10040.1
//! \details ANSI X9.57 module 
static const act::byte cvOID_module[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x01};
//! \brief   1.2.840.10040.1.1
//! \details ANSI X9.57 module x9f1-cert-mgmt 
static const act::byte cvOID_x9f1_cert_mgmt[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x01, 0x01};
//! \brief   1.2.840.10040.2
//! \details ANSI X9.57 holdinstruction 
static const act::byte cvOID_holdinstruction[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02};
//! \brief   1.2.840.10040.2.1
//! \details ANSI X9.57 hold instruction holdinstruction-none 
static const act::byte cvOID_holdinstruction_none[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x01};
//! \brief   1.2.840.10040.2.2
//! \details ANSI X9.57 hold instruction callissuer 
static const act::byte cvOID_callissuer[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x02};
//! \brief   1.2.840.10040.2.3
//! \details ANSI X9.57 hold instruction reject 
static const act::byte cvOID_reject[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x03};
//! \brief   1.2.840.10040.2.4
//! \details ANSI X9.57 hold instruction pickupToken 
static const act::byte cvOID_pickupToken[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x02, 0x04};
//! \brief   1.2.840.10040.3
//! \details ANSI X9.57 attribute 
static const act::byte cvOID_attribute[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03};
//! \brief   1.2.840.10040.3.1
//! \details ANSI X9.57 attribute countersignature 
static const act::byte cvOID_countersignature[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03, 0x01};
//! \brief   1.2.840.10040.3.2
//! \details ANSI X9.57 attribute attribute-cert 
static const act::byte cvOID_attribute_cert[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x03, 0x02};
//! \brief   1.2.840.10040.4
//! \details ANSI X9.57 algorithm 
static const act::byte cvOID_algorithm[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04};
//! \brief   1.2.840.10040.4.1
//! \details ANSI X9.57 algorithm dsa 
static const act::byte cvOID_dsa[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x01};
//! \brief   1.2.840.10040.4.2
//! \details ANSI X9.57 algorithm dsa-match 
static const act::byte cvOID_dsa_match[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x02};
//! \brief   1.2.840.10040.4.3
//! \details ANSI X9.57 algorithm dsaWithSha1 
static const act::byte cvOID_dsaWithSha1[] = { 0x2A, 0x86, 0x48, 0xCE, 0x38, 0x04, 0x03};
//! \brief   1.2.840.10045.1
//! \details ANSI X9.62.  This OID is also assigned as ecdsa-with-SHA1 fieldType 
static const act::byte cvOID_fieldType[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01};
//! \brief   1.2.840.10045.1.1
//! \details ANSI X9.62 field type prime-field 
static const act::byte cvOID_prime_field[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x01};
//! \brief   1.2.840.10045.1.2
//! \details ANSI X9.62 field type characteristic-two-field 
static const act::byte cvOID_characteristic_two_field[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02};
//! \brief   1.2.840.10045.1.2.3
//! \details ANSI X9.62 field type characteristic-two-basis 
static const act::byte cvOID_characteristic_two_basis[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03};
//! \brief   1.2.840.10045.1.2.3.1
//! \details ANSI X9.62 field basis onBasis 
static const act::byte cvOID_onBasis[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x01};
//! \brief   1.2.840.10045.1.2.3.2
//! \details ANSI X9.62 field basis tpBasis 
static const act::byte cvOID_tpBasis[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x02};
//! \brief   1.2.840.10045.1.2.3.3
//! \details ANSI X9.62 field basis ppBasis 
static const act::byte cvOID_ppBasis[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x01, 0x02, 0x03, 0x03};
//! \brief   1.2.840.10045.2
//! \details ANSI X9.62 publicKeyType 
static const act::byte cvOID_publicKeyType[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02};
//! \brief   1.2.840.10045.2.1
//! \details ANSI X9.62 public key type ecPublicKey 
static const act::byte cvOID_ecPublicKey[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01};
//! \brief   1.2.840.10046.1
//! \details ANSI X9.42 fieldType 
static const act::byte cvOID_fieldType42[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x01};
//! \brief   1.2.840.10046.1.1
//! \details ANSI X9.42 field type gf-prime 
static const act::byte cvOID_gf_prime[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x01, 0x01};
//! \brief   1.2.840.10046.2
//! \details ANSI X9.42 numberType 
static const act::byte cvOID_numberType[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x02};
//! \brief   1.2.840.10046.2.1
//! \details ANSI X9.42 number type dhPublicKey 
static const act::byte cvOID_dhPublicKey[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x02, 0x01};
//! \brief   1.2.840.10046.3
//! \details ANSI X9.42 scheme 
static const act::byte cvOID_scheme[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03};
//! \brief   1.2.840.10046.3.1
//! \details ANSI X9.42 scheme dhStatic 
static const act::byte cvOID_dhStatic[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x01};
//! \brief   1.2.840.10046.3.2
//! \details ANSI X9.42 scheme dhEphem 
static const act::byte cvOID_dhEphem[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x02};
//! \brief   1.2.840.10046.3.3
//! \details ANSI X9.42 scheme dhHybrid1 
static const act::byte cvOID_dhHybrid1[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x03};
//! \brief   1.2.840.10046.3.4
//! \details ANSI X9.42 scheme dhHybrid2 
static const act::byte cvOID_dhHybrid2[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x04};
//! \brief   1.2.840.10046.3.5
//! \details ANSI X9.42 scheme mqv2 
static const act::byte cvOID_mqv2[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x05};
//! \brief   1.2.840.10046.3.6
//! \details ANSI X9.42 scheme mqv1 
static const act::byte cvOID_mqv1[] = { 0x2A, 0x86, 0x48, 0xCE, 0x3E, 0x03, 0x06};
//! \brief   1.2.840.113533.7.65.0
//! \details Nortel Secure Networks ce (1 2 840 113533 7 65) entrustVersInfo 
static const act::byte cvOID_entrustVersInfo[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x41, 0x00};
//! \brief   1.2.840.113533.7.66.3
//! \details Nortel Secure Networks alg (1 2 840 113533 7 66) cast3CBC 
static const act::byte cvOID_cast3CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x03};
//! \brief   1.2.840.113533.7.66.10
//! \details Nortel Secure Networks alg (1 2 840 113533 7 66) cast5CBC 
static const act::byte cvOID_cast5CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0A};
//! \brief   1.2.840.113533.7.66.11
//! \details Nortel Secure Networks alg (1 2 840 113533 7 66) cast5MAC 
static const act::byte cvOID_cast5MAC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0B};
//! \brief   1.2.840.113533.7.66.12
//! \details Nortel Secure Networks alg (1 2 840 113533 7 66) pbeWithMD5AndCAST5-CBC 
static const act::byte cvOID_pbeWithMD5AndCAST5_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0C};
//! \brief   1.2.840.113533.7.66.13
//! \details Nortel Secure Networks alg (1 2 840 113533 7 66) passwordBasedMac 
static const act::byte cvOID_passwordBasedMac[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x42, 0x0D};
//! \brief   1.2.840.113
static const act::byte cvOID_entrustUser[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x43, 0x0C};
//! \brief   1.2.840.113533.7.68.0
//! \details Nortel Secure Networks at (1 2 840 113533 7 68) entrustCAInfo 
static const act::byte cvOID_entrustCAInfo[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x44, 0x00};
//! \brief   1.2.840.113533.7.68.10
//! \details Nortel Secure Networks at (1 2 840 113533 7 68) attributeCertificate 
static const act::byte cvOID_attributeCertificate[] = { 0x2A, 0x86, 0x48, 0x86, 0xF6, 0x7D, 0x07, 0x44, 0x0A};
//! \brief   1.2.840.113549.1.1.1
//! \details PKCS #1 rsaEncryption 
static const act::byte cvOID_rsaEncryption[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01};
//! \brief   1.2.840.113549.1.1.2
//! \details PKCS #1 md2withRSAEncryption 
static const act::byte cvOID_md2withRSAEncryption[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x02};
//! \brief   1.2.840.113549.1.1.3
//! \details PKCS #1 md4withRSAEncryption 
static const act::byte cvOID_md4withRSAEncryption[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x03};
//! \brief   1.2.840.113549.1.1.4
//! \details PKCS #1 md5withRSAEncryption 
static const act::byte cvOID_md5withRSAEncryption[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x04};
//! \brief   1.2.840.113549.1.1.5
//! \details PKCS #1 sha1withRSAEncryption 
static const act::byte cvOID_sha1withRSAEncryption[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x05};
//! \brief   1.2.840.113549.1.1.6
//! \details PKCS #1.  This OID may also be assigned as ripemd160WithRSAEncryption rsaOAEPEncryptionSET 
static const act::byte cvOID_rsaOAEPEncryptionSET[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x06};
//! \brief   1.2.840.113549.1.1.7
//! \details PKCS #1 id-RSAES-OAEP 
static const act::byte cvOID_rsaES_OAEP[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x07};
//! \brief   1.2.840.113549.1.1.8
//! \details PKCS #1. id-mgf1 (0x2A864886F70D010108)
static const act::byte cvOID_mgf1[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x08};
//! \brief   1.2.840.113549.1.1.9
//! \details PKCS #1. id-pSpecified (0x2A864886F70D010109)
static const act::byte cvOID_pSpecified[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x09};
//! \brief   1.2.840.113549.1.1.10
//! \details PKCS #1. id-RSASSA-PSS (0x2A864886F70D01010A)
static const act::byte cvOID_rsaSSA_PSS[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x0A};
//! \brief   1.2.840.113549.1.2
//! \details Obsolete BSAFE OID bsafeRsaEncr 
static const act::byte cvOID_bsafeRsaEncr[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01};
//! \brief   1.2.840.113549.1.3.1
//! \details PKCS #3 dhKeyAgreement 
static const act::byte cvOID_dhKeyAgreement[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x03, 0x01};
//! \brief   1.2.840.113549.1.5.1
//! \details PKCS #5 pbeWithMD2AndDES-CBC 
static const act::byte cvOID_pbeWithMD2AndDES_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x01};
//! \brief   1.2.840.113549.1.5.3
//! \details PKCS #5 pbeWithMD5AndDES-CBC 
static const act::byte cvOID_pbeWithMD5AndDES_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x03};
//! \brief   1.2.840.113549.1.5.4
//! \details PKCS #5 pbeWithMD2AndRC2-CBC 
static const act::byte cvOID_pbeWithMD2AndRC2_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x04};
//! \brief   1.2.840.113549.1.5.6
//! \details PKCS #5 pbeWithMD5AndRC2-CBC 
static const act::byte cvOID_pbeWithMD5AndRC2_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x06};
//! \brief   1.2.840.113549.1.5.9
//! \details PKCS #5, used in BSAFE only pbeWithMD5AndXOR 
static const act::byte cvOID_pbeWithMD5AndXOR[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x09};
//! \brief   1.2.840.113549.1.5.10
//! \details PKCS #5 pbeWithSHAAndDES-CBC 
static const act::byte cvOID_pbeWithSHAAndDES_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0A};
//! \brief   1.2.840.113549.1.5.12
//! \details PKCS #5 v2.0 id-PBKDF2 
static const act::byte cvOID_id_PBKDF2[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0C};
//! \brief   1.2.840.113549.1.5.13
//! \details PKCS #5 v2.0 id-PBES2 
static const act::byte cvOID_id_PBES2[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0D};
//! \brief   1.2.840.113549.1.5.14
//! \details PKCS #5 v2.0 id-PBMAC1 
static const act::byte cvOID_id_PBMAC1[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x05, 0x0E};
//! \brief   1.2.840.113549.1.7.1
//! \details PKCS #7 data 
static const act::byte cvOID_data[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x01};
//! \brief   1.2.840.113549.1.7.2
//! \details PKCS #7 signedData 
static const act::byte cvOID_signedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x02};
//! \brief   1.2.840.113549.1.7.3
//! \details PKCS #7 envelopedData 
static const act::byte cvOID_envelopedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x03};
//! \brief   1.2.840.113549.1.7.4
//! \details PKCS #7 signedAndEnvelopedData 
static const act::byte cvOID_signedAndEnvelopedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x04};
//! \brief   1.2.840.113549.1.7.5
//! \details PKCS #7 digestedData 
static const act::byte cvOID_digestedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x05};
//! \brief   1.2.840.113549.1.7.6
//! \details PKCS #7 encryptedData 
static const act::byte cvOID_encryptedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x06};
//! \brief   1.2.840.113549.1.7.7
//! \details PKCS #7 experimental dataWithAttributes 
static const act::byte cvOID_dataWithAttributes[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x07};
//! \brief   1.2.840.113549.1.7.8
//! \details PKCS #7 experimental encryptedPrivateKeyInfo 
static const act::byte cvOID_encryptedPrivateKeyInfo[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x07, 0x08};
//! \brief   1.2.840.113549.1.9.1
//! \details PKCS #9 (1 2 840 113549 1 9).  Deprecated, use an altName extension instead emailAddress 
static const act::byte cvOID_emailAddress_PKCS9[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x01};
//! \brief   1.2.840.113549.1.9.2
//! \details PKCS #9 (1 2 840 113549 1 9) unstructuredName 
static const act::byte cvOID_unstructuredName[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x02};
//! \brief   1.2.840.113549.1.9.3
//! \details PKCS #9 (1 2 840 113549 1 9) contentType 
static const act::byte cvOID_contentType[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x03};
//! \brief   1.2.840.113549.1.9.4
//! \details PKCS #9 (1 2 840 113549 1 9) messageDigest 
static const act::byte cvOID_messageDigest[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x04};
//! \brief   1.2.840.113549.1.9.5
//! \details PKCS #9 (1 2 840 113549 1 9) signingTime 
static const act::byte cvOID_signingTime[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x05};
//! \brief   1.2.840.113549.1.9.6
//! \details PKCS #9 (1 2 840 113549 1 9) countersignature 
static const act::byte cvOID_countersignature_PKCS9[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x06};
//! \brief   1.2.840.113549.1.9.7
//! \details PKCS #9 (1 2 840 113549 1 9) challengePassword 
static const act::byte cvOID_challengePassword[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x07};
//! \brief   1.2.840.113549.1.9.8
//! \details PKCS #9 (1 2 840 113549 1 9) unstructuredAddress 
static const act::byte cvOID_unstructuredAddress[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x08};
//! \brief   1.2.840.113549.1.9.9
//! \details PKCS #9 (1 2 840 113549 1 9) extendedCertificateAttributes 
static const act::byte cvOID_extendedCertificateAttributes[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x09};
//! \brief   1.2.840.113549.1.9.10
//! \details PKCS #9 (1 2 840 113549 1 9) experimental issuerAndSerialNumber 
static const act::byte cvOID_issuerAndSerialNumber[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0A};
//! \brief   1.2.840.113549.1.9.11
//! \details PKCS #9 (1 2 840 113549 1 9) experimental passwordCheck 
static const act::byte cvOID_passwordCheck[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0B};
//! \brief   1.2.840.113549.1.9.12
//! \details PKCS #9 (1 2 840 113549 1 9) experimental publicKey 
static const act::byte cvOID_publicKey[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0C};
//! \brief   1.2.840.113549.1.9.13
//! \details PKCS #9 (1 2 840 113549 1 9) experimental signingDescription 
static const act::byte cvOID_signingDescription[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0D};
//! \brief   1.2.840.113549.1.9.14
//! \details PKCS #9 (1 2 840 113549 1 9) experimental extensionReq 
static const act::byte cvOID_extensionReq[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0E};
//! \brief   1.2.840.113549.1.9.15
//! \details PKCS #9 (1 2 840 113549 1 9).  This OID was formerly assigned as symmetricCapabilities, then reassigned as SMIMECapabilities, then renamed to the current name sMIMECapabilities 
static const act::byte cvOID_sMIMECapabilities[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F};
//! \brief   1.2.840.113549.1.9.15.1
//! \details sMIMECapabilities (1 2 840 113549 1 9 15) preferSignedData 
static const act::byte cvOID_preferSignedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x01};
//! \brief   1.2.840.113549.1.9.15.2
//! \details sMIMECapabilities (1 2 840 113549 1 9 15) canNotDecryptAny 
static const act::byte cvOID_canNotDecryptAny[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x02};
//! \brief   1.2.840.113549.1.9.15.3
//! \details sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 1) instead receiptRequest 
static const act::byte cvOID_receiptRequest[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x03};
//! \brief   1.2.840.113549.1.9.15.4
//! \details sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 1 1) instead receipt 
static const act::byte cvOID_receipt[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x04};
//! \brief   1.2.840.113549.1.9.15.5
//! \details sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 4) instead contentHints 
static const act::byte cvOID_contentHints[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x05};
//! \brief   1.2.840.113549.1.9.15.6
//! \details sMIMECapabilities (1 2 840 113549 1 9 15).  Deprecated, use (1 2 840 113549 1 9 16 2 3) instead mlExpansionHistory 
static const act::byte cvOID_mlExpansionHistory[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x0F, 0x06};
//! \brief   1.2.840.113549.1.9.16
//! \details PKCS #9 (1 2 840 113549 1 9) id-sMIME 
static const act::byte cvOID_id_sMIME[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10};
//! \brief   1.2.840.113549.1.9.16.0
//! \details id-sMIME (1 2 840 113549 1 9 16) id-mod 
static const act::byte cvOID_id_mod[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00};
//! \brief   1.2.840.113549.1.9.16.0.1
//! \details S/MIME Modules (1 2 840 113549 1 9 16 0) id-mod-cms 
static const act::byte cvOID_id_mod_cms[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00, 0x01};
//! \brief   1.2.840.113549.1.9.16.0.2
//! \details S/MIME Modules (1 2 840 113549 1 9 16 0) id-mod-ess 
static const act::byte cvOID_id_mod_ess[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x00, 0x02};
//! \brief   1.2.840.113549.1.9.16.1
//! \details id-sMIME (1 2 840 113549 1 9 16) id-ct 
static const act::byte cvOID_id_ct[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01};
//! \brief   1.2.840.113549.1.9.16.1.1
//! \details S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-receipt 
static const act::byte cvOID_id_ct_receipt[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x01};
//! \brief   1.2.840.113549.1.9.16.1.2
//! \details S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-authData 
static const act::byte cvOID_id_ct_authData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x02};
//! \brief   1.2.840.113549.1.9.16.1.3
//! \details S/MIME Content Types (1 2 840 113549 1 9 16 1) id-ct-compressedData 
static const act::byte cvOID_id_ct_compressedData[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x01, 0x03};
//! \brief   1.2.840.113549.1.9.16.2
//! \details id-sMIME (1 2 840 113549 1 9 16) id-aa 
static const act::byte cvOID_id_aa[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02};
//! \brief   1.2.840.113549.1.9.16.2.1
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-receiptRequest 
static const act::byte cvOID_id_aa_receiptRequest[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x01};
//! \brief   1.2.840.113549.1.9.16.2.2
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-securityLabel 
static const act::byte cvOID_id_aa_securityLabel[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x02};
//! \brief   1.2.840.113549.1.9.16.2.3
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-mlExpandHistory 
static const act::byte cvOID_id_aa_mlExpandHistory[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x03};
//! \brief   1.2.840.113549.1.9.16.2.4
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentHint 
static const act::byte cvOID_id_aa_contentHint[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x04};
//! \brief   1.2.840.113549.1.9.16.2.5
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-msgSigDigest 
static const act::byte cvOID_id_aa_msgSigDigest[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x05};
//! \brief   1.2.840.113549.1.9.16.2.7
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentIdentifier 
static const act::byte cvOID_id_aa_contentIdentifier[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x07};
//! \brief   1.2.840.113549.1.9.16.2.8
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-macValue 
static const act::byte cvOID_id_aa_macValue[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x08};
//! \brief   1.2.840.113549.1.9.16.2.9
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-equivalentLabels 
static const act::byte cvOID_id_aa_equivalentLabels[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x09};
//! \brief   1.2.840.113549.1.9.16.2.10
//! \details S/MIME Authenticated Attributes (1 2 840 113549 1 9 16 2) id-aa-contentReference 
static const act::byte cvOID_id_aa_contentReference[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x02, 0x0A};
//! \brief   1.2.840.113549.1.9.16.3.5
//! \details S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-ESDH 
static const act::byte cvOID_id_alg_ESDH[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x05};
//! \brief   1.2.840.113549.1.9.16.3.6
//! \details S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-CMS3DESwrap 
static const act::byte cvOID_id_alg_CMS3DESwrap[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x06};
//! \brief   1.2.840.113549.1.9.16.3.7
//! \details S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-CMSRC2wrap 
static const act::byte cvOID_id_alg_CMSRC2wrap[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x07};
//! \brief   1.2.840.113549.1.9.16.3.8
//! \details S/MIME Algorithms (1 2 840 113549 1 9 16 3) id-alg-zlib 
static const act::byte cvOID_id_alg_zlib[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x10, 0x03, 0x08};
//! \brief   1.2.840.113549.1.9.20
//! \details PKCS #9 (1 2 840 113549 1 9) friendlyName (for PKCS #12) 
static const act::byte cvOID_friendlyName[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x14};
//! \brief   1.2.840.113549.1.9.21
//! \details PKCS #9 (1 2 840 113549 1 9) localKeyID (for PKCS #12) 
static const act::byte cvOID_localKeyID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x15};
//! \brief   1.2.840.113549.1.9.22
//! \details PKCS #9 (1 2 840 113549 1 9) certTypes (for PKCS #12) 
static const act::byte cvOID_certTypes[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16};
//! \brief   1.2.840.113549.1.9.22.1
//! \details PKCS #9 (1 2 840 113549 1 9) x509Certificate (for PKCS #12) 
static const act::byte cvOID_x509Certificate[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16, 0x01};
//! \brief   1.2.840.113549.1.9.22.2
//! \details PKCS #9 (1 2 840 113549 1 9) sdsiCertificate (for PKCS #12) 
static const act::byte cvOID_sdsiCertificate[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x16, 0x02};
//! \brief   1.2.840.113549.1.9.23
//! \details PKCS #9 (1 2 840 113549 1 9) crlTypes (for PKCS #12) 
static const act::byte cvOID_crlTypes[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x17};
//! \brief   1.2.840.113549.1.9.23.1
//! \details PKCS #9 (1 2 840 113549 1 9) x509Crl (for PKCS #12) 
static const act::byte cvOID_x509Crl[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x09, 0x17, 0x01};
//! \brief   1.2.840.113549.1.12.1
//! \details This OID was formerly assigned as PKCS #12 modeID pkcs-12-PbeIds 
static const act::byte cvOID_pkcs_12_PbeIds[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01};
//! \brief   1.2.840.113549.1.12.1.1
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 1). This OID was formerly assigned as pkcs-12-OfflineTransportMode pbeWithSHAAnd128BitRC4 
static const act::byte cvOID_pbeWithSHAAnd128BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x01};
//! \brief   1.2.840.113549.1.12.1.2
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 2). This OID was formerly assigned as pkcs-12-OnlineTransportMode pbeWithSHAAnd40BitRC4 
static const act::byte cvOID_pbeWithSHAAnd40BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x02};
//! \brief   1.2.840.113549.1.12.1.3
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd3-KeyTripleDES-CBC 
static const act::byte cvOID_pbeWithSHAAnd3_KeyTripleDES_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x03};
//! \brief   1.2.840.113549.1.12.1.4
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd2-KeyTripleDES-CBC 
static const act::byte cvOID_pbeWithSHAAnd2_KeyTripleDES_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x04};
//! \brief   1.2.840.113549.1.12.1.5
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd128BitRC2-CBC 
static const act::byte cvOID_pbeWithSHAAnd128BitRC2_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x05};
//! \brief   1.2.840.113549.1.12.1.6
//! \details PKCS #12 PbeIds (1 2 840 113549 1 12 3) pbeWithSHAAnd40BitRC2-CBC 
static const act::byte cvOID_pbeWithSHAAnd40BitRC2_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x01, 0x06};
//! \brief   1.2.840.113549.1.12.2
//! \details Deprecated pkcs-12-ESPVKID 
static const act::byte cvOID_pkcs_12_ESPVKID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x02};
//! \brief   1.2.840.113549.1.12.2.1
//! \details PKCS #12 ESPVKID (1 2 840 113549 1 12 2). Deprecated, use (1 2 840 113549 1 12 3 5) instead pkcs-12-PKCS8KeyShrouding 
static const act::byte cvOID_pkcs_12_PKCS8KeyShrouding[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x02, 0x01};
//! \brief   1.2.840.113549.1.12.3.1
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-keyBagId 
static const act::byte cvOID_pkcs_12_keyBagId[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x01};
//! \brief   1.2.840.113549.1.12.3.2
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-certAndCRLBagId 
static const act::byte cvOID_pkcs_12_certAndCRLBagId[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x02};
//! \brief   1.2.840.113549.1.12.3.3
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-secretBagId 
static const act::byte cvOID_pkcs_12_secretBagId[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x03};
//! \brief   1.2.840.113549.1.12.3.4
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-safeContentsId 
static const act::byte cvOID_pkcs_12_safeContentsId[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x04};
//! \brief   1.2.840.113549.1.12.3.5
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 3) pkcs-12-pkcs-8ShroudedKeyBagId 
static const act::byte cvOID_pkcs_12_pkcs_8ShroudedKeyBagId[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x03, 0x05};
//! \brief   1.2.840.113549.1.12.4
//! \details Deprecated pkcs-12-CertBagID 
static const act::byte cvOID_pkcs_12_CertBagID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04};
//! \brief   1.2.840.113549.1.12.4.1
//! \details PKCS #12 CertBagID (1 2 840 113549 1 12 4).  This OID was formerly assigned as pkcs-12-X509CertCRLBag pkcs-12-X509CertCRLBagID 
static const act::byte cvOID_pkcs_12_X509CertCRLBagID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04, 0x01};
//! \brief   1.2.840.113549.1.12.4.2
//! \details PKCS #12 CertBagID (1 2 840 113549 1 12 4).  This OID was formerly assigned as pkcs-12-SDSICertBag pkcs-12-SDSICertBagID 
static const act::byte cvOID_pkcs_12_SDSICertBagID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x04, 0x02};
//! \brief   1.2.840.113549.1.12.5.1
//! \details PKCS #12 OID (1 2 840 113549 1 12 5).  Deprecated, use the partially compatible (1 2 840 113549 1 12 1) OIDs instead pkcs-12-PBEID 
static const act::byte cvOID_pkcs_12_PBEID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01};
//! \brief   1.2.840.113549.1.12.5.1.1
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 1) instead pkcs-12-PBEWithSha1And128BitRC4 
static const act::byte cvOID_pkcs_12_PBEWithSha1And128BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x01};
//! \brief   1.2.840.113549.1.12.5.1.2
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 2) instead pkcs-12-PBEWithSha1And40BitRC4 
static const act::byte cvOID_pkcs_12_PBEWithSha1And40BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x02};
//! \brief   1.2.840.113549.1.12.5.1.3
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 3) or (1 2 840 113549 1 12 1 4) instead pkcs-12-PBEWithSha1AndTripleDESCBC 
static const act::byte cvOID_pkcs_12_PBEWithSha1AndTripleDESCBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x03};
//! \brief   1.2.840.113549.1.12.5.1.4
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 5) instead pkcs-12-PBEWithSha1And128BitRC2CBC 
static const act::byte cvOID_pkcs_12_PBEWithSha1And128BitRC2CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x04};
//! \brief   1.2.840.113549.1.12.5.1.5
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use (1 2 840 113549 1 12 1 6) instead pkcs-12-PBEWithSha1And40BitRC2CBC 
static const act::byte cvOID_pkcs_12_PBEWithSha1And40BitRC2CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x05};
//! \brief   1.2.840.113549.1.12.5.1.6
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 1) or (1 2 840 113549 1 12 1 2) instead pkcs-12-PBEWithSha1AndRC4 
static const act::byte cvOID_pkcs_12_PBEWithSha1AndRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x06};
//! \brief   1.2.840.113549.1.12.5.1.7
//! \details PKCS #12 OID PBEID (1 2 840 113549 1 12 5 1).  Deprecated, use the incompatible but similar (1 2 840 113549 1 12 1 5) or (1 2 840 113549 1 12 1 6) instead pkcs-12-PBEWithSha1AndRC2CBC 
static const act::byte cvOID_pkcs_12_PBEWithSha1AndRC2CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x01, 0x07};
//! \brief   1.2.840.113549.1.12.5.2.1
//! \details PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWith128BitRC4 
static const act::byte cvOID_pkcs_12_RSAEncryptionWith128BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x01};
//! \brief   1.2.840.113549.1.12.5.2.2
//! \details PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWith40BitRC4 
static const act::byte cvOID_pkcs_12_RSAEncryptionWith40BitRC4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x02};
//! \brief   1.2.840.113549.1.12.5.2.3
//! \details PKCS #12 OID EnvelopingID (1 2 840 113549 1 12 5 2).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSAEncryptionWithTripleDES 
static const act::byte cvOID_pkcs_12_RSAEncryptionWithTripleDES[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x02, 0x03};
//! \brief   1.2.840.113549.1.12.5.3.1
//! \details PKCS #12 OID SignatureID (1 2 840 113549 1 12 5 3).  Deprecated, use the conventional PKCS #1 OIDs instead pkcs-12-RSASignatureWithSHA1Digest 
static const act::byte cvOID_pkcs_12_RSASignatureWithSHA1Digest[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x05, 0x03, 0x01};
//! \brief   1.2.840.113549.1.12.10.1.1
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-keyBag 
static const act::byte cvOID_pkcs_12_keyBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x01};
//! \brief   1.2.840.113549.1.12.10.1.2
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-pkcs-8ShroudedKeyBag 
static const act::byte cvOID_pkcs_12_pkcs_8ShroudedKeyBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x02};
//! \brief   1.2.840.113549.1.12.10.1.3
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-certBag 
static const act::byte cvOID_pkcs_12_certBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x03};
//! \brief   1.2.840.113549.1.12.10.1.4
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-crlBag 
static const act::byte cvOID_pkcs_12_crlBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x04};
//! \brief   1.2.840.113549.1.12.10.1.5
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-secretBag 
static const act::byte cvOID_pkcs_12_secretBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x05};
//! \brief   1.2.840.113549.1.12.10.1.6
//! \details PKCS #12 BagIds (1 2 840 113549 1 12 10 1) pkcs-12-safeContentsBag 
static const act::byte cvOID_pkcs_12_safeContentsBag[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x0C, 0x0A, 0x01, 0x06};
//! \brief   1.2.840.113549.2.2
//! \details RSADSI digestAlgorithm (1 2 840 113549 2) md2 
static const act::byte cvOID_md2[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x02};
//! \brief   1.2.840.113549.2.4
//! \details RSADSI digestAlgorithm (1 2 840 113549 2) md4 
static const act::byte cvOID_md4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x04};
//! \brief   1.2.840.113549.2.5
//! \details RSADSI digestAlgorithm (1 2 840 113549 2) md5 
static const act::byte cvOID_md5[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x05};
//! \brief   1.2.840.113549.3.2
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc2CBC 
static const act::byte cvOID_rc2CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x02};
//! \brief   1.2.840.113549.3.3
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc2ECB 
static const act::byte cvOID_rc2ECB[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x03};
//! \brief   1.2.840.113549.3.4
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc4 
static const act::byte cvOID_rc4[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x04};
//! \brief   1.2.840.113549.3.5
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc4WithMAC 
static const act::byte cvOID_rc4WithMAC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x05};
//! \brief   1.2.840.113549.3.6
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) desx-CBC 
static const act::byte cvOID_desx_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x06};
//! \brief   1.2.840.113549.3.7
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) des-EDE3-CBC 
static const act::byte cvOID_des_EDE3_CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x07};
//! \brief   1.2.840.113549.3.8
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc5CBC 
static const act::byte cvOID_rc5CBC[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x08};
//! \brief   1.2.840.113549.3.9
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3) rc5-CBCPad 
static const act::byte cvOID_rc5_CBCPad[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x09};
//! \brief   1.2.840.113549.3.10
//! \details RSADSI encryptionAlgorithm (1 2 840 113549 3).  Formerly called CDMFCBCPad desCDMF 
static const act::byte cvOID_desCDMF[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x03, 0x0A};
//! \brief   1.3.6.1.4.1.188.7.1.1
//! \details Ascom Systech ascom 
static const act::byte cvOID_ascom[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.188.7.1.1.1
//! \details Ascom Systech ideaECB 
static const act::byte cvOID_ideaECB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.188.7.1.1.2
//! \details Ascom Systech ideaCBC 
static const act::byte cvOID_ideaCBC[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x02};
//! \brief   1.3.6.1.4.1.188.7.1.1.3
//! \details Ascom Systech ideaCFB 
static const act::byte cvOID_ideaCFB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x03};
//! \brief   1.3.6.1.4.1.188.7.1.1.4
//! \details Ascom Systech ideaOFB 
static const act::byte cvOID_ideaOFB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x81, 0x3C, 0x07, 0x01, 0x01, 0x04};
//! \brief   1.2.840.113556.4.3
//! \details Microsoft microsoftExcel 
static const act::byte cvOID_microsoftExcel[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x03};
//! \brief   1.2.840.113556.4.4
//! \details Microsoft titledWithOID 
static const act::byte cvOID_titledWithOID[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x04};
//! \brief   1.2.840.113556.4.5
//! \details Microsoft microsoftPowerPoint 
static const act::byte cvOID_microsoftPowerPoint[] = { 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x14, 0x04, 0x05};
//! \brief   1.3.6.1.4.1.311.2.1.4
//! \details Microsoft code signing spcIndirectDataContext 
static const act::byte cvOID_spcIndirectDataContext[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x04};
//! \brief   1.3.6.1.4.1.311.2.1.10
//! \details Microsoft code signing.  Also known as policyLink spcAgencyInfo 
static const act::byte cvOID_spcAgencyInfo[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0A};
//! \brief   1.3.6.1.4.1.311.2.1.11
//! \details Microsoft code signing spcStatementType 
static const act::byte cvOID_spcStatementType[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0B};
//! \brief   1.3.6.1.4.1.311.2.1.12
//! \details Microsoft code signing spcSpOpusInfo 
static const act::byte cvOID_spcSpOpusInfo[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0C};
//! \brief   1.3.6.1.4.1.311.2.1.14
//! \details Microsoft certReqExtensions 
static const act::byte cvOID_certReqExtensions[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0E};
//! \brief   1.3.6.1.4.1.311.2.1.15
//! \details Microsoft code signing spcPelmageData 
static const act::byte cvOID_spcPelmageData[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x0F};
//! \brief   1.3.6.1.4.1.311.2.1.20
//! \details Microsoft code signing.  Also known as "glue extension" spcLink (type 1) 
static const act::byte cvOID_spcLink_1[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x14};
//! \brief   1.3.6.1.4.1.311.2.1.21
//! \details Microsoft individualCodeSigning 
static const act::byte cvOID_individualCodeSigning[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x15};
//! \brief   1.3.6.1.4.1.311.2.1.22
//! \details Microsoft commercialCodeSigning 
static const act::byte cvOID_commercialCodeSigning[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x16};
//! \brief   1.3.6.1.4.1.311.2.1.25
//! \details Microsoft code signing.  Also known as "glue extension" spcLink (type 2) 
static const act::byte cvOID_spcLink_2[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x19};
//! \brief   1.3.6.1.4.1.311.2.1.26
//! \details Microsoft code signing spcMinimalCriteriaInfo 
static const act::byte cvOID_spcMinimalCriteriaInfo[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1A};
//! \brief   1.3.6.1.4.1.311.2.1.27
//! \details Microsoft code signing spcFinancialCriteriaInfo 
static const act::byte cvOID_spcFinancialCriteriaInfo[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1B};
//! \brief   1.3.6.1.4.1.311.2.1.28
//! \details Microsoft code signing.  Also known as "glue extension" spcLink (type 3) 
static const act::byte cvOID_spcLink_3[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x02, 0x01, 0x1C};
//! \brief   1.3.6.1.4.1.311.3.2.1
//! \details Microsoft code signing timestampCountersignature 
static const act::byte cvOID_timestampCountersignature[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x03, 0x02, 0x01};
//! \brief   1.3.6.1.4.1.311.10.1
//! \details Microsoft PKCS #7 contentType certTrustList 
static const act::byte cvOID_certTrustList[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x01};
//! \brief   1.3.6.1.4.1.311.10.2
//! \details Microsoft nextUpdateLocation 
static const act::byte cvOID_nextUpdateLocation[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x02};
//! \brief   1.3.6.1.4.1.311.10.3.1
//! \details Microsoft enhanced key usage certTrustListSigning 
static const act::byte cvOID_certTrustListSigning[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x01};
//! \brief   1.3.6.1.4.1.311.10.3.2
//! \details Microsoft enhanced key usage timeStampSigning 
static const act::byte cvOID_timeStampSigning[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x02};
//! \brief   1.3.6.1.4.1.311.10.3.3
//! \details Microsoft enhanced key usage serverGatedCrypto 
static const act::byte cvOID_serverGatedCrypto[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x03};
//! \brief   1.3.6.1.4.1.311.10.3.4
//! \details Microsoft enhanced key usage encryptedFileSystem 
static const act::byte cvOID_encryptedFileSystem[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x03, 0x04};
//! \brief   1.3.6.1.4.1.311.10.4.1
//! \details Microsoft attribute yesnoTrustAttr 
static const act::byte cvOID_yesnoTrustAttr[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0A, 0x04, 0x01};
//! \brief   1.3.6.1.4.1.311.16.4
//! \details Microsoft S/MIME cert attribute microsoftEncryptionCert 
static const act::byte cvOID_microsoftEncryptionCert[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x10, 0x04};
//! \brief   1.3.6.1.4.1.311.20.2.2
//! \details Microsoft enhanced key usage smartcardLogon
static const act::byte cvOID_smartcardLogon[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x14, 0x02, 0x02};
//! \brief   1.3.6.1.4.1.311.21.1
//! \details Microsoft attribute cAKeyCertIndexPair 
static const act::byte cvOID_cAKeyCertIndexPair[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x15, 0x01};
//! \brief   1.3.6.1.4.1.311.13.2.2
//! \details Microsoft attribute Unknown MS CryptoAPI-related extension 
static const act::byte cvOID_Unknown_MS_CryptoAPI_related_extension[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x0D, 0x02, 0x02};
//! \brief   1.3.6.1.4.1.311.16.4
//! \details Microsoft attribute microsoftRecipientInfo 
static const act::byte cvOID_microsoftRecipientInfo[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x82, 0x37, 0x10, 0x04};
//! \brief   1.3.6.1.4.1.2428.10.1.1
//! \details UNINETT PCA UNINETT policyIdentifier 
static const act::byte cvOID_UNINETT_policyIdentifier[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x92, 0x7C, 0x0A, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.2712.10
//! \details ICE-TEL CA ICE-TEL policyIdentifier 
static const act::byte cvOID_ICE_TEL_policyIdentifier[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x95, 0x18, 0x0A};
//! \brief   1.3.6.1.4.1.2786.1.1.1
//! \details ICE-TEL CA policy ICE-TEL Italian policyIdentifier 
static const act::byte cvOID_ICE_TEL_Italian_policyIdentifier[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x95, 0x62, 0x01, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.3029.1.1
//! \details cryptlib encryption algorithm blowfishECB 
static const act::byte cvOID_blowfishECB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.3029.1.2
//! \details cryptlib encr
static const act::byte cvOID_blowfishCBC[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x02};
//! \brief   1.3.6.1.4.1.3029.1.3
//! \details cryptlib encryption algorithm blowfishCFB 
static const act::byte cvOID_blowfishCFB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x03};
//! \brief   1.3.6.1.4.1.3029.1.4
//! \details cryptlib encryption algorithm blowfishOFB 
static const act::byte cvOID_blowfishOFB[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x04};
//! \brief   1.3.6.1.4.1.3029.3.1
//! \details cryptlib public-key algorithm elgamal 
static const act::byte cvOID_elgamal[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01};
//! \brief   1.3.6.1.4.1.3029.3.1.1
//! \details cryptlib public-key algorithm elgamalWithSHA-1 
static const act::byte cvOID_elgamalWithSHA_1[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01, 0x01};
//! \brief   1.3.6.1.4.1.3029.3.1.2
//! \details cryptlib public-key algorithm elgamalWithRIPEMD-160 
static const act::byte cvOID_elgamalWithRIPEMD_160[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x03, 0x01, 0x02};
//! \brief   1.3.6.1.4.1.3029.32.1
//! \details cryptlib cryptlibPrivateKey 
static const act::byte cvOID_cryptlibPrivateKey[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x20, 0x01};
//! \brief   1.3.6.1.4.1.3029.42.11172.1
//! \details cryptlib special MPEG-of-cat OID mpeg-1 
static const act::byte cvOID_mpeg_1[] = { 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x2A, 0xD7, 0x24, 0x01};
//! \brief   1.3.6.1.5.5.7.1
//! \details PKIX privateExtension 
static const act::byte cvOID_privateExtension[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01};
//! \brief   1.3.6.1.5.5.7.1.1
//! \details PKIX private extension authorityInfoAccess 
static const act::byte cvOID_authorityInfoAccess[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x01};

// AME
//! \brief   1.3.6.1.5.5.7.1.11
//! \details PKIX private extension subjectInfoAccess
static const unsigned				char cvOID_subjectInfoAccess[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x01, 0x0a};

//! \brief   1.3.6.1.5.5.7.2
//! \details PKIX policyQualifierIds 
static const unsigned				char cvOID_policyQualifierIds[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02};
//! \brief   1.3.6.1.5.5.7.2.1
//! \details PKIX policy qualifier cps 
static const act::byte cvOID_cps[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x01};
//! \brief   1.3.6.1.5.5.7.2.2
//! \details PKIX policy qualifier unotice 
static const act::byte cvOID_unotice[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x02, 0x02};
//! \brief   1.3.6.1.5.5.7.3
//! \details PKIX keyPurpose 
static const act::byte cvOID_keyPurpose[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03};
//! \brief   1.3.6.1.5.5.7.3.1
//! \details PKIX key purpose serverAuth 
static const act::byte cvOID_serverAuth[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x01};
//! \brief   1.3.6.1.5.5.7.3.2
//! \details PKIX key purpose clientAuth 
static const act::byte cvOID_clientAuth[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x02};
//! \brief   1.3.6.1.5.5.7.3.3
//! \details PKIX key purpose codeSigning 
static const act::byte cvOID_codeSigning[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x03};
//! \brief   1.3.6.1.5.5.7.3.4
//! \details PKIX key purpose emailProtection 
static const act::byte cvOID_emailProtection[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x04};
//! \brief   1.3.6.1.5.5.7.3.5
//! \details PKIX key purpose ipsecEndSystem 
static const act::byte cvOID_ipsecEndSystem[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x05};
//! \brief   1.3.6.1.5.5.7.3.6
//! \details PKIX key purpose ipsecTunnel 
static const act::byte cvOID_ipsecTunnel[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x06};
//! \brief   1.3.6.1.5.5.7.3.7
//! \details PKIX key purpose ipsecUser 
static const act::byte cvOID_ipsecUser[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x07};
//! \brief   1.3.6.1.5.5.7.3.8
//! \details PKIX key purpose timeStamping 
static const act::byte cvOID_timeStamping[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x08};
// AME
//! \brief   1.3.6.1.5.5.7.3.9
//! \details PKIX key purpose OCSPSigning 
static const act::byte cvOID_OCSPSigning[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x03, 0x09};
//! \brief   1.3.6.1.5.5.7.4
//! \details PKIX cmpInformationTypes 
static const act::byte cvOID_cmpInformationTypes[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04};
//! \brief   1.3.6.1.5.5.7.4.1
//! \details PKIX CMP information caProtEncCert 
static const act::byte cvOID_caProtEncCert[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x01};
//! \brief   1.3.6.1.5.5.7.4.2
//! \details PKIX CMP information signKeyPairTypes 
static const act::byte cvOID_signKeyPairTypes[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x02};
//! \brief   1.3.6.1.5.5.7.4.3
//! \details PKIX CMP information encKeyPairTypes 
static const act::byte cvOID_encKeyPairTypes[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x03};
//! \brief   1.3.6.1.5.5.7.4.4
//! \details PKIX CMP information preferredSymmAlg 
static const act::byte cvOID_preferredSymmAlg[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x04};
//! \brief   1.3.6.1.5.5.7.4.5
//! \details PKIX CMP information caKeyUpdateInfo 
static const act::byte cvOID_caKeyUpdateInfo[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x05};
//! \brief   1.3.6.1.5.5.7.4.6
//! \details PKIX CMP information currentCRL 
static const act::byte cvOID_currentCRL[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x04, 0x06};
//! \brief   1.3.6.1.5.5.7.6.3
//! \details PKIX algorithm dh-sig-hmac-sha1 
static const act::byte cvOID_dh_sig_hmac_sha1[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x06, 0x03};
//! \brief   1.3.6.1.5.5.7.6.4
//! \details PKIX algorithm dh-pop 
static const act::byte cvOID_dh_pop[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x06, 0x04};
//! \brief   1.3.6.1.5.5.7.48.1
//! \details PKIX authority info access descriptor ocsp 
static const act::byte cvOID_ocsp[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x01};
//! \brief   1.3.6.1.5.5.7.48.2
//! \details PKIX authority info access descriptor caIssuers 
static const act::byte cvOID_caIssuers[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x02};

// AME
//! \brief   1.3.6.1.5.5.7.48.3
//! \details PKIX subject info access descriptor timeStamping
static const unsigned				char cvOID_info_timeStamping[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x03};
//! \brief   1.3.6.1.5.5.7.48.5
//! \details PKIX subject info access descriptor caRepository
static const unsigned				char cvOID_caRepository[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x07, 0x30, 0x05};

//! \brief   1.3.6.1.5.5.8.1.1
//! \details ISAKMP HMAC algorithm HMAC-MD5 
static const act::byte cvOID_HMAC_MD5[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x01};
//! \brief   1.3.6.1.5.5.8.1.2
//! \details ISAKMP HMAC algorithm HMAC-SHA 
static const act::byte cvOID_HMAC_SHA[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x02};
//! \brief   1.3.6.1.5.5.8.1.3
//! \details ISAKMP HMAC algorithm HMAC-Tiger 
static const act::byte cvOID_HMAC_Tiger[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x01, 0x03};
//! \brief   1.3.6.1.5.5.8.2.2
//! \details ipsec_kp_ike_intermediate
static const act::byte cvOID_iKEIntermediate[] = { 0x2B, 0x06, 0x01, 0x05, 0x05, 0x08, 0x02, 0x02};

//! \brief   1.3.12.2.1011.7.1
//! \details DASS algorithm decEncryptionAlgorithm 
static const act::byte cvOID_decEncryptionAlgorithm[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x01};
//! \brief   1.3.12.2.1011.7.1.2
//! \details DASS encryption algorithm decDEA 
static const act::byte cvOID_decDEA[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x01, 0x02};
//! \brief   1.3.12.2.1011.7.2
//! \details DASS algorithm decHashAlgorithm 
static const act::byte cvOID_decHashAlgorithm[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02};
//! \brief   1.3.12.2.1011.7.2.1
//! \details DASS hash algorithm decMD2 
static const act::byte cvOID_decMD2[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02, 0x01};
//! \brief   1.3.12.2.1011.7.2.2
//! \details DASS hash algorithm decMD4 
static const act::byte cvOID_decMD4[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x02, 0x02};
//! \brief   1.3.12.2.1011.7.3
//! \details DASS algorithm decSignatureAlgorithm 
static const act::byte cvOID_decSignatureAlgorithm[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03};
//! \brief   1.3.12.2.1011.7.3.1
//! \details DASS signature algorithm decMD2withRSA 
static const act::byte cvOID_decMD2withRSA[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x01};
//! \brief   1.3.12.2.1011.7.3.2
//! \details DASS signature algorithm decMD4withRSA 
static const act::byte cvOID_decMD4withRSA[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x02};
//! \brief   1.3.12.2.1011.7.3.3
//! \details DASS signature algorithm decDEAMAC 
static const act::byte cvOID_decDEAMAC[] = { 0x2B, 0x0C, 0x02, 0x87, 0x73, 0x07, 0x03, 0x03};
//! \brief   1.3.14.2.26.5
//! \details Unsure about this OID sha 
static const act::byte cvOID_sha[] = { 0x2B, 0x0E, 0x02, 0x1A, 0x05};
//! \brief   1.3.14.3.2.1.1
//! \details X.509. Unsure about this OID rsa 
static const act::byte cvOID_rsa[] = { 0x2B, 0x0E, 0x03, 0x02, 0x01, 0x01};
//! \brief   1.3.14.3.2.2
//! \details Oddball OIW OID md4WitRSA 
static const act::byte cvOID_md4WitRSA[] = { 0x2B, 0x0E, 0x03, 0x02, 0x02};
//! \brief   1.3.14.3.2.3
//! \details Oddball OIW OID md5WithRSA 
static const act::byte cvOID_md5WithRSA[] = { 0x2B, 0x0E, 0x03, 0x02, 0x03};
//! \brief   1.3.14.3.2.4
//! \details Oddball OIW OID md4WithRSAEncryption 
static const act::byte cvOID_md4WithRSAEncryption[] = { 0x2B, 0x0E, 0x03, 0x02, 0x04};
//! \brief   1.3.14.3.2.2.1
//! \details X.509. Deprecated sqmod-N 
static const act::byte cvOID_sqmod_N[] = { 0x2B, 0x0E, 0x03, 0x02, 0x02, 0x01};
//! \brief   1.3.14.3.2.3.1
//! \details X.509. Deprecated sqmod-NwithRSA 
static const act::byte cvOID_sqmod_NwithRSA[] = { 0x2B, 0x0E, 0x03, 0x02, 0x03, 0x01};
//! \brief   1.3.14.3.2.11
//! \details ISO 9796-2, also X9.31 Part 1 rsaSignature 
static const act::byte cvOID_rsaSignature[] = { 0x2B, 0x0E, 0x03, 0x02, 0x0B};
////! \brief   1.3.14.3.2.12
////! \details OIW?, supposedly from an incomplete version of SDN.701 (doesn't match final SDN.701) dsa 
//static const unsigned 			char cvOID_dsa[] = { 0x2B, 0x0E, 0x03, 0x02, 0x0C};
//! \brief   1.3.14.3.2.14
//! \details Oddball OIW OID using 9796-2 padding rules mdc2WithRSASignature 
static const act::byte cvOID_mdc2WithRSASignature[] = { 0x2B, 0x0E, 0x03, 0x02, 0x0E};
//! \brief   1.3.14.3.2.15
//! \details Oddball OIW OID using 9796-2 padding rules shaWithRSASignature 
static const act::byte cvOID_shaWithRSASignature[] = { 0x2B, 0x0E, 0x03, 0x02, 0x0F};
//! \brief   1.3.14.3.2.16
//! \details Oddball OIW OID.  Deprecated, use a plain DH OID instead dhWithCommonModulus 
static const act::byte cvOID_dhWithCommonModulus[] = { 0x2B, 0x0E, 0x03, 0x02, 0x10};
//! \brief   1.3.14.3.2.17
//! \details Oddball OIW OID.  Mode is ECB desEDE 
static const act::byte cvOID_desEDE[] = { 0x2B, 0x0E, 0x03, 0x02, 0x11};
////! \brief   1.3.14.3.2.18
////! \details Oddball OIW OID sha 
//static const unsigned 			char cvOID_sha[] = { 0x2B, 0x0E, 0x03, 0x02, 0x12};
//! \brief   1.3.14.3.2.19
//! \details Oddball OIW OID, DES-based hash, planned for X9.31 Part 2 mdc-2 
static const act::byte cvOID_mdc_2[] = { 0x2B, 0x0E, 0x03, 0x02, 0x13};
//! \brief   1.3.14.3.2.20
//! \details Oddball OIW OID.  Deprecated, use a plain DSA OID instead dsaCommon 
static const act::byte cvOID_dsaCommon[] = { 0x2B, 0x0E, 0x03, 0x02, 0x14};
//! \brief   1.3.14.3.2.21
//! \details Oddball OIW OID.  Deprecated, use a plain dsaWithSHA OID instead dsaCommonWithSHA 
static const act::byte cvOID_dsaCommonWithSHA[] = { 0x2B, 0x0E, 0x03, 0x02, 0x15};
//! \brief   1.3.14.3.2.22
//! \details Oddball OIW OID rsaKeyTransport 
static const act::byte cvOID_rsaKeyTransport[] = { 0x2B, 0x0E, 0x03, 0x02, 0x16};
//! \brief   1.3.14.3.2.23
//! \details Oddball OIW OID keyed-hash-seal 
static const act::byte cvOID_keyed_hash_seal[] = { 0x2B, 0x0E, 0x03, 0x02, 0x17};
//! \brief   1.3.14.3.2.24
//! \details Oddball OIW OID using 9796-2 padding rules md2WithRSASignature 
static const act::byte cvOID_md2WithRSASignature[] = { 0x2B, 0x0E, 0x03, 0x02, 0x18};
//! \brief   1.3.14.3.2.25
//! \details Oddball OIW OID using 9796-2 padding rules md5WithRSASignature 
static const act::byte cvOID_md5WithRSASignature[] = { 0x2B, 0x0E, 0x03, 0x02, 0x19};
//! \brief   1.3.14.3.2.26
//! \details OIW sha1 
static const act::byte cvOID_sha1[] = { 0x2B, 0x0E, 0x03, 0x02, 0x1A};
//! \brief   1.3.14.3.2.27
//! \details OIW. This OID may also be assigned as ripemd-160 dsaWithSHA1 
static const act::byte cvOID_dsaWithSHA1[] = { 0x2B, 0x0E, 0x03, 0x02, 0x1B};
//! \brief   1.3.14.3.2.28
//! \details OIW dsaWithCommonSHA1 
static const act::byte cvOID_dsaWithCommonSHA1[] = { 0x2B, 0x0E, 0x03, 0x02, 0x1C};
//! \brief   1.3.14.3.2.29
//! \details Oddball OIW OID sha-1WithRSAEncryption 
static const act::byte cvOID_sha_1WithRSAEncryption[] = { 0x2B, 0x0E, 0x03, 0x02, 0x1D};
//! \brief   1.3.14.3.3.1
//! \details Oddball OIW OID simple-strong-auth-mechanism 
static const act::byte cvOID_simple_strong_auth_mechanism[] = { 0x2B, 0x0E, 0x03, 0x03, 0x01};
//! \brief   1.3.14.7.2.1.1
//! \details Unsure about this OID ElGamal 
static const act::byte cvOID_ElGamal[] = { 0x2B, 0x0E, 0x07, 0x02, 0x01, 0x01};
//! \brief   1.3.14.7.2.3.1
//! \details Unsure about this OID md2WithRSA 
static const act::byte cvOID_md2WithRSA[] = { 0x2B, 0x0E, 0x07, 0x02, 0x03, 0x01};
//! \brief   1.3.14.7.2.3.2
//! \details Unsure about this OID md2WithElGamal 
static const act::byte cvOID_md2WithElGamal[] = { 0x2B, 0x0E, 0x07, 0x02, 0x03, 0x02};
//! \brief   1.3.36.1
//! \details Teletrust document document 
static const act::byte cvOID_document[] = { 0x2B, 0x24, 0x01};
//! \brief   1.3.36.1.1
//! \details Teletrust document finalVersion 
static const act::byte cvOID_finalVersion[] = { 0x2B, 0x24, 0x01, 0x01};
//! \brief   1.3.36.1.2
//! \details Teletrust document draft 
static const act::byte cvOID_draft[] = { 0x2B, 0x24, 0x01, 0x02};
//! \brief   1.3.36.2
//! \details Teletrust sio sio 
static const act::byte cvOID_sio[] = { 0x2B, 0x24, 0x02};
//! \brief   1.3.36.2.1
//! \details Teletrust sio sedu 
static const act::byte cvOID_sedu[] = { 0x2B, 0x24, 0x02, 0x01};
//! \brief   1.3.36.3
//! \details Teletrust algorithm algorithm 
static const act::byte cvOID_algorithm_Teletrust[] = { 0x2B, 0x24, 0x03};
//! \brief   1.3.36.3.1
//! \details Teletrust algorithm encryptionAlgorithm 
static const act::byte cvOID_encryptionAlgorithm_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01};
//! \brief   1.3.36.3.1.1
//! \details Teletrust encryption algorithm des 
static const act::byte cvOID_des_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x01};
//! \brief   1.3.36.3.1.1.1
//! \details Teletrust encryption algorithm desECB_pad 
static const act::byte cvOID_desECB_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x01, 0x01};
//! \brief   1.3.36.3.1.1.1.1
//! \details Teletrust encryption algorithm desECB_ISOpad 
static const act::byte cvOID_desECB_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x01, 0x01, 0x01};
//! \brief   1.3.36.3.1.1.2.1
//! \details Teletrust encryption algorithm desCBC_pad 
static const act::byte cvOID_desCBC_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x01, 0x02, 0x01};
//! \brief   1.3.36.3.1.1.2.1.1
//! \details Teletrust encryption algorithm desCBC_ISOpad 
static const act::byte cvOID_desCBC_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x01, 0x02, 0x01, 0x01};
//! \brief   1.3.36.3.1.3
//! \details Teletrust encryption algorithm des_3 
static const act::byte cvOID_des_3[] = { 0x2B, 0x24, 0x03, 0x01, 0x03};
//! \brief   1.3.36.3.1.3.1.1
//! \details Teletrust encryption algorithm.  EDE triple DES des_3ECB_pad 
static const act::byte cvOID_des_3ECB_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x03, 0x01, 0x01};
//! \brief   1.3.36.3.1.3.1.1.1
//! \details Teletrust encryption algorithm.  EDE triple DES des_3ECB_ISOpad 
static const act::byte cvOID_des_3ECB_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x03, 0x01, 0x01, 0x01};
//! \brief   1.3.36.3.1.3.2.1
//! \details Teletrust encryption algorithm.  EDE triple DES des_3CBC_pad 
static const act::byte cvOID_des_3CBC_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x03, 0x02, 0x01};
//! \brief   1.3.36.3.1.3.2.1.1
//! \details Teletrust encryption algorithm.  EDE triple DES des_3CBC_ISOpad 
static const act::byte cvOID_des_3CBC_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x03, 0x02, 0x01, 0x01};
//! \brief   1.3.36.3.1.2
//! \details Teletrust encryption algorithm idea 
static const act::byte cvOID_idea_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x02};
//! \brief   1.3.36.3.1.2.1
//! \details Teletrust encryption algorithm ideaECB 
static const act::byte cvOID_ideaECB_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x01};
//! \brief   1.3.36.3.1.2.1.1
//! \details Teletrust encryption algorithm ideaECB_pad 
static const act::byte cvOID_ideaECB_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x01, 0x01};
//! \brief   1.3.36.3.1.2.1.1.1
//! \details Teletrust encryption algorithm ideaECB_ISOpad 
static const act::byte cvOID_ideaECB_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x01, 0x01, 0x01};
//! \brief   1.3.36.3.1.2.2
//! \details Teletrust encryption algorithm ideaCBC 
static const act::byte cvOID_ideaCBC_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x02};
//! \brief   1.3.36.3.1.2.2.1
//! \details /Teletrust encryption algorithm ideaCBC_pad 
static const act::byte cvOID_ideaCBC_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x02, 0x01};
//! \brief   1.3.36.3.1.2.2.1.1
//! \details Teletrust encryption algorithm ideaCBC_ISOpad 
static const act::byte cvOID_ideaCBC_ISOpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x02, 0x01, 0x01};
//! \brief   1.3.36.3.1.2.3
//! \details Teletrust encryption algorithm ideaOFB 
static const act::byte cvOID_ideaOFB_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x03};
//! \brief   1.3.36.3.1.2.4
//! \details Teletrust encryption algorithm ideaCFB 
static const act::byte cvOID_ideaCFB_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x02, 0x04};
//! \brief   1.3.36.3.1.4
//! \details Teletrust encryption algorithm rsaEncryption 
static const act::byte cvOID_rsaEncryption_Teletrust[] = { 0x2B, 0x24, 0x03, 0x01, 0x04};
//! \brief   1.3.36.3.1.4.512.17
//! \details Teletrust encryption algorithm rsaEncryptionWithlmod512expe17 
static const act::byte cvOID_rsaEncryptionWithlmod512expe17[] = { 0x2B, 0x24, 0x03, 0x01, 0x04, 0x84, 0x00, 0x11};
//! \brief   1.3.36.3.1.5
//! \details Teletrust encryption algorithm bsi-1 
static const act::byte cvOID_bsi_1[] = { 0x2B, 0x24, 0x03, 0x01, 0x05};
//! \brief   1.3.36.3.1.5.1
//! \details Teletrust encryption algorithm bsi_1ECB_pad 
static const act::byte cvOID_bsi_1ECB_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x05, 0x01};
//! \brief   1.3.36.3.1.5.2
//! \details Teletrust encryption algorithm bsi_1CBC_pad 
static const act::byte cvOID_bsi_1CBC_pad[] = { 0x2B, 0x24, 0x03, 0x01, 0x05, 0x02};
//! \brief   1.3.36.3.1.5.2.1
//! \details Teletrust encryption algorithm bsi_1CBC_PEMpad 
static const act::byte cvOID_bsi_1CBC_PEMpad[] = { 0x2B, 0x24, 0x03, 0x01, 0x05, 0x02, 0x01};
//! \brief   1.3.36.3.2
//! \details Teletrust algorithm hashAlgorithm 
static const act::byte cvOID_hashAlgorithm[] = { 0x2B, 0x24, 0x03, 0x02};
//! \brief   1.3.36.3.2.1
//! \details Teletrust hash algorithm ripemd160 
static const act::byte cvOID_ripemd160_Teletrust[] = { 0x2B, 0x24, 0x03, 0x02, 0x01};
//! \brief   1.3.36.3.2.2
//! \details Teletrust hash algorithm ripemd128 
static const act::byte cvOID_ripemd128_Teletrust[] = { 0x2B, 0x24, 0x03, 0x02, 0x02};
//! \brief   1.3.36.3.2.3
//! \details Teletrust hash algorithm ripemd256 
static const act::byte cvOID_ripemd256[] = { 0x2B, 0x24, 0x03, 0x02, 0x03};
//! \brief   1.3.36.3.2.4
//! \details Teletrust hash algorithm mdc2singleLength 
static const act::byte cvOID_mdc2singleLength[] = { 0x2B, 0x24, 0x03, 0x02, 0x04};
//! \brief   1.3.36.3.2.5
//! \details Teletrust hash algorithm mdc2doubleLength 
static const act::byte cvOID_mdc2doubleLength[] = { 0x2B, 0x24, 0x03, 0x02, 0x05};
//! \brief   1.3.36.3.3
//! \details Teletrust algorithm signatureAlgorithm 
static const act::byte cvOID_signatureAlgorithm[] = { 0x2B, 0x24, 0x03, 0x03};
//! \brief   1.3.36.3.3.1
//! \details Teletrust signature algorithm rsaSignature 
static const act::byte cvOID_rsaSignature_Teletrust[] = { 0x2B, 0x24, 0x03, 0x03, 0x01};
//! \brief   1.3.36.3.3.1.1
//! \details Teletrust signature algorithm rsaSignatureWithsha1 
static const act::byte cvOID_rsaSignatureWithsha1[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01};
//! \brief   1.3.36.3.3.1.1.512.2
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l512_l2 
static const act::byte cvOID_rsaSignatureWithsha1_l512_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.1.640.2
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l640_l2 
static const act::byte cvOID_rsaSignatureWithsha1_l640_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.1.768.2
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l768_l2 
static const act::byte cvOID_rsaSignatureWithsha1_l768_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.1.892.2
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l896_l2 
static const act::byte cvOID_rsaSignatureWithsha1_l896_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.1.1024.2
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l1024_l2 
static const act::byte cvOID_rsaSignatureWithsha1_l1024_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.1.512.3
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l512_l3 
static const act::byte cvOID_rsaSignatureWithsha1_l512_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.1.640.3
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l640_l3 
static const act::byte cvOID_rsaSignatureWithsha1_l640_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.1.768.3
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l768_l3 
static const act::byte cvOID_rsaSignatureWithsha1_l768_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.1.896.3
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l896_l3 
static const act::byte cvOID_rsaSignatureWithsha1_l896_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.1.1024.3
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l1024_l3 
static const act::byte cvOID_rsaSignatureWithsha1_l1024_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.1.512.5
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l512_l5 
static const act::byte cvOID_rsaSignatureWithsha1_l512_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.1.640.5
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l640_l5 
static const act::byte cvOID_rsaSignatureWithsha1_l640_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.1.768.5
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l768_l5 
static const act::byte cvOID_rsaSignatureWithsha1_l768_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.1.896.5
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l896_l5 
static const act::byte cvOID_rsaSignatureWithsha1_l896_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.1.1024.5
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l1024_l5 
static const act::byte cvOID_rsaSignatureWithsha1_l1024_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.1.512.9
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l512_l9 
static const act::byte cvOID_rsaSignatureWithsha1_l512_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.1.640.9
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l640_l9 
static const act::byte cvOID_rsaSignatureWithsha1_l640_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.1.768.9
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l768_l9 
static const act::byte cvOID_rsaSignatureWithsha1_l768_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.1.896.9
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l896_l9 
static const act::byte cvOID_rsaSignatureWithsha1_l896_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.1.1024.9
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l1024_l9 
static const act::byte cvOID_rsaSignatureWithsha1_l1024_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.1.512.11
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l512_l11 
static const act::byte cvOID_rsaSignatureWithsha1_l512_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x84, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.1.640.11
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l640_l11 
static const act::byte cvOID_rsaSignatureWithsha1_l640_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x85, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.1.768.11
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l768_l11 
static const act::byte cvOID_rsaSignatureWithsha1_l768_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x86, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.1.896.11
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l896_l11 
static const act::byte cvOID_rsaSignatureWithsha1_l896_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x87, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.1.1024.11
//! \details Teletrust signature algorithm rsaSignatureWithsha1_l1024_l11 
static const act::byte cvOID_rsaSignatureWithsha1_l1024_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x01, 0x88, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160 
static const act::byte cvOID_rsaSignatureWithripemd160[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02};
//! \brief   1.3.36.3.3.1.2.512.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l512_l2 
static const act::byte cvOID_rsaSignatureWithripemd160_l512_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.2.640.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l640_l2 
static const act::byte cvOID_rsaSignatureWithripemd160_l640_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.2.768.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l768_l2 
static const act::byte cvOID_rsaSignatureWithripemd160_l768_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.2.892.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l896_l2 
static const act::byte cvOID_rsaSignatureWithripemd160_l896_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.2.1024.2
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l2 
static const act::byte cvOID_rsaSignatureWithripemd160_l1024_l2[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x02};
//! \brief   1.3.36.3.3.1.2.512.3
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l512_l3 
static const act::byte cvOID_rsaSignatureWithripemd160_l512_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.2.640.3
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l640_l3 
static const act::byte cvOID_rsaSignatureWithripemd160_l640_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.2.768.3
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l768_l3 
static const act::byte cvOID_rsaSignatureWithripemd160_l768_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.2.896.3
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l896_l3 
static const act::byte cvOID_rsaSignatureWithripemd160_l896_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.2.1024.3
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l3 
static const act::byte cvOID_rsaSignatureWithripemd160_l1024_l3[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x03};
//! \brief   1.3.36.3.3.1.2.512.5
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l512_l5 
static const act::byte cvOID_rsaSignatureWithripemd160_l512_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.2.640.5
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l640_l5 
static const act::byte cvOID_rsaSignatureWithripemd160_l640_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.2.768.5
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l768_l5 
static const act::byte cvOID_rsaSignatureWithripemd160_l768_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.2.896.5
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l896_l5 
static const act::byte cvOID_rsaSignatureWithripemd160_l896_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.2.1024.5
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l5 
static const act::byte cvOID_rsaSignatureWithripemd160_l1024_l5[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x05};
//! \brief   1.3.36.3.3.1.2.512.9
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l512_l9 
static const act::byte cvOID_rsaSignatureWithripemd160_l512_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.2.640.9
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l640_l9 
static const act::byte cvOID_rsaSignatureWithripemd160_l640_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.2.768.9
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l768_l9 
static const act::byte cvOID_rsaSignatureWithripemd160_l768_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.2.896.9
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l896_l9 
static const act::byte cvOID_rsaSignatureWithripemd160_l896_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.2.1024.9
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l9 
static const act::byte cvOID_rsaSignatureWithripemd160_l1024_l9[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x09};
//! \brief   1.3.36.3.3.1.2.512.11
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l512_l11 
static const act::byte cvOID_rsaSignatureWithripemd160_l512_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x84, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.2.640.11
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l640_l11 
static const act::byte cvOID_rsaSignatureWithripemd160_l640_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x85, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.2.768.11
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l768_l11 
static const act::byte cvOID_rsaSignatureWithripemd160_l768_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x86, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.2.896.11
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l896_l11 
static const act::byte cvOID_rsaSignatureWithripemd160_l896_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x87, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.2.1024.11
//! \details Teletrust signature algorithm rsaSignatureWithripemd160_l1024_l11 
static const act::byte cvOID_rsaSignatureWithripemd160_l1024_l11[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x02, 0x88, 0x00, 0x11};
//! \brief   1.3.36.3.3.1.3
//! \details Teletrust signature algorithm rsaSignatureWithrimpemd128 
static const act::byte cvOID_rsaSignatureWithrimpemd128[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x03};
//! \brief   1.3.36.3.3.1.4
//! \details Teletrust signature algorithm rsaSignatureWithrimpemd256 
static const act::byte cvOID_rsaSignatureWithrimpemd256[] = { 0x2B, 0x24, 0x03, 0x03, 0x01, 0x04};
//! \brief   1.3.36.3.3.2
//! \details Teletrust signature algorithm ecsieSign 
static const act::byte cvOID_ecsieSign[] = { 0x2B, 0x24, 0x03, 0x03, 0x02};
//! \brief   1.3.36.3.3.2.1
//! \details Teletrust signature algorithm ecsieSignWithsha1 
static const act::byte cvOID_ecsieSignWithsha1[] = { 0x2B, 0x24, 0x03, 0x03, 0x02, 0x01};
//! \brief   1.3.36.3.3.2.2
//! \details Teletrust signature algorithm ecsieSignWithripemd160 
static const act::byte cvOID_ecsieSignWithripemd160[] = { 0x2B, 0x24, 0x03, 0x03, 0x02, 0x02};
//! \brief   1.3.36.3.3.2.3
//! \details Teletrust signature algorithm ecsieSignWithmd2 
static const act::byte cvOID_ecsieSignWithmd2[] = { 0x2B, 0x24, 0x03, 0x03, 0x02, 0x03};
//! \brief   1.3.36.3.3.2.4
//! \details Teletrust signature algorithm ecsieSignWithmd5 
static const act::byte cvOID_ecsieSignWithmd5[] = { 0x2B, 0x24, 0x03, 0x03, 0x02, 0x04};
//! \brief   1.3.36.3.4
//! \details Teletrust algorithm signatureScheme 
static const act::byte cvOID_signatureScheme[] = { 0x2B, 0x24, 0x03, 0x04};
//! \brief   1.3.36.3.4.1
//! \details Teletrust signature scheme sigS_ISO9796-1 
static const act::byte cvOID_sigS_ISO9796_1[] = { 0x2B, 0x24, 0x03, 0x04, 0x01};
//! \brief   1.3.36.3.4.2
//! \details Teletrust signature scheme sigS_ISO9796-2 
static const act::byte cvOID_sigS_ISO9796_2[] = { 0x2B, 0x24, 0x03, 0x04, 0x02};
//! \brief   1.3.36.3.4.2.1
//! \details Teletrust signature scheme.  Unsure what this is supposed to be sigS_ISO9796-2Withred 
static const act::byte cvOID_sigS_ISO9796_2Withred[] = { 0x2B, 0x24, 0x03, 0x04, 0x02, 0x01};
//! \brief   1.3.36.3.4.2.2
//! \details Teletrust signature scheme.  Unsure what this is supposed to be sigS_ISO9796-2Withrsa 
static const act::byte cvOID_sigS_ISO9796_2Withrsa[] = { 0x2B, 0x24, 0x03, 0x04, 0x02, 0x02};
//! \brief   1.3.36.3.4.2.3
//! \details Teletrust signature scheme.  9796-2 with random number in padding field sigS_ISO9796-2Withrnd 
static const act::byte cvOID_sigS_ISO9796_2Withrnd[] = { 0x2B, 0x24, 0x03, 0x04, 0x02, 0x03};
//! \brief   1.3.36.4
//! \details Teletrust attribute attribute 
static const act::byte cvOID_attribute_Teletrust[] = { 0x2B, 0x24, 0x04};
//! \brief   1.3.36.5
//! \details Teletrust policy policy 
static const act::byte cvOID_policy[] = { 0x2B, 0x24, 0x05};
//! \brief   1.3.36.6
//! \details Teletrust API api 
static const act::byte cvOID_api[] = { 0x2B, 0x24, 0x06};
//! \brief   1.3.36.6.1
//! \details Teletrust API manufacturer-specific_api 
static const act::byte cvOID_manufacturer_specific_api[] = { 0x2B, 0x24, 0x06, 0x01};
//! \brief   1.3.36.6.1.1
//! \details Teletrust API utimaco-api 
static const act::byte cvOID_utimaco_api[] = { 0x2B, 0x24, 0x06, 0x01, 0x01};
//! \brief   1.3.36.6.2
//! \details Teletrust API functionality-specific_api 
static const act::byte cvOID_functionality_specific_api[] = { 0x2B, 0x24, 0x06, 0x02};
//! \brief   1.3.36.7
//! \details Teletrust key management keymgmnt 
static const act::byte cvOID_keymgmnt[] = { 0x2B, 0x24, 0x07};
//! \brief   1.3.36.7.1
//! \details Teletrust key management keyagree 
static const act::byte cvOID_keyagree[] = { 0x2B, 0x24, 0x07, 0x01};
//! \brief   1.3.36.7.1.1
//! \details Teletrust key management bsiPKE 
static const act::byte cvOID_bsiPKE[] = { 0x2B, 0x24, 0x07, 0x01, 0x01};
//! \brief   1.3.36.7.2
//! \details Teletrust key management keytrans 
static const act::byte cvOID_keytrans[] = { 0x2B, 0x24, 0x07, 0x02};
//! \brief   1.3.36.7.2.1
//! \details Teletrust key management.  9796-2 with key stored in hash field encISO9796-2Withrsa 
static const act::byte cvOID_encISO9796_2Withrsa[] = { 0x2B, 0x24, 0x07, 0x02, 0x01};
//! \brief   1.3.36.8.1.1
//! \details Teletrust policy sigiSigConform 
static const act::byte cvOID_sigiSigConform[] = { 0x2B, 0x24, 0x08, 0x01, 0x01};
//! \brief   1.3.36.8.2.1
//! \details Teletrust extended key usage directoryService 
static const act::byte cvOID_directoryService[] = { 0x2B, 0x24, 0x08, 0x02, 0x01};
//! \brief   1.3.36.8.3.1
//! \details Teletrust attribute dateOfCertGen 
static const act::byte cvOID_dateOfCertGen[] = { 0x2B, 0x24, 0x08, 0x03, 0x01};
//! \brief   1.3.36.8.3.2
//! \details Teletrust attribute procuration 
static const act::byte cvOID_procuration[] = { 0x2B, 0x24, 0x08, 0x03, 0x02};
//! \brief   1.3.36.8.3.3
//! \details Teletrust attribute admission 
static const act::byte cvOID_admission[] = { 0x2B, 0x24, 0x08, 0x03, 0x03};
//! \brief   1.3.36.8.3.4
//! \details Teletrust attribute monetaryLimit 
static const act::byte cvOID_monetaryLimit[] = { 0x2B, 0x24, 0x08, 0x03, 0x04};
//! \brief   1.3.36.8.3.5
//! \details Teletrust attribute declarationOfMajority 
static const act::byte cvOID_declarationOfMajority[] = { 0x2B, 0x24, 0x08, 0x03, 0x05};
//! \brief   1.3.36.8.3.6
//! \details Teletrust attribute integratedCircuitCardSerialNumber 
static const act::byte cvOID_integratedCircuitCardSerialNumber[] = { 0x2B, 0x24, 0x08, 0x03, 0x06};
//! \brief   1.3.36.8.3.7
//! \details Teletrust attribute pKReference 
static const act::byte cvOID_pKReference[] = { 0x2B, 0x24, 0x08, 0x03, 0x07};
//! \brief   1.3.36.8.3.8
//! \details Teletrust attribute restriction 
static const act::byte cvOID_restriction_1[] = { 0x2B, 0x24, 0x08, 0x03, 0x08};
//! \brief   1.3.36.8.3.9
//! \details Teletrust attribute retrieveIfAllowed 
static const act::byte cvOID_retrieveIfAllowed[] = { 0x2B, 0x24, 0x08, 0x03, 0x09};
//! \brief   1.3.36.8.3.10
//! \details Teletrust attribute requestedCertificate 
static const act::byte cvOID_requestedCertificate[] = { 0x2B, 0x24, 0x08, 0x03, 0x0A};
//! \brief   1.3.36.8.3.11
//! \details Teletrust attribute namingAuthorities 
static const act::byte cvOID_namingAuthorities[] = { 0x2B, 0x24, 0x08, 0x03, 0x0B};
//! \brief   1.3.36.8.3.12
//! \details Teletrust attribute certInDirSince 
static const act::byte cvOID_certInDirSince[] = { 0x2B, 0x24, 0x08, 0x03, 0x0C};
//! \brief   1.3.36.8.3.13
//! \details Teletrust attribute certHash 
static const act::byte cvOID_certHash[] = { 0x2B, 0x24, 0x08, 0x03, 0x0D};
//! \brief   1.3.36.8.4.1
//! \details Teletrust OtherName attribute personalData 
static const act::byte cvOID_personalData[] = { 0x2B, 0x24, 0x08, 0x04, 0x01};
//! \brief   1.3.36.8.4.8
//! \details Teletrust attribute certificate attribute restriction 
static const act::byte cvOID_restriction_2[] = { 0x2B, 0x24, 0x08, 0x04, 0x08};
//! \brief   1.3.36.8.5.1.1.1
//! \details Teletrust signature algorithm rsaIndicateSHA1 
static const act::byte cvOID_rsaIndicateSHA1[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x01};
//! \brief   1.3.36.8.5.1.1.2
//! \details Teletrust signature algorithm rsaIndicateRIPEMD160 
static const act::byte cvOID_rsaIndicateRIPEMD160[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x02};
//! \brief   1.3.36.8.5.1.1.3
//! \details Teletrust signature algorithm rsaWithSHA1 
static const act::byte cvOID_rsaWithSHA1[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x03};
//! \brief   1.3.36.8.5.1.1.4
//! \details Teletrust signature algorithm rsaWithRIPEMD160 
static const act::byte cvOID_rsaWithRIPEMD160[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x01, 0x04};
//! \brief   1.3.36.8.5.1.2.1
//! \details Teletrust signature algorithm dsaExtended 
static const act::byte cvOID_dsaExtended[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x02, 0x01};
//! \brief   1.3.36.8.5.1.2.2
//! \details Teletrust signature algorithm dsaWithRIPEMD160 
static const act::byte cvOID_dsaWithRIPEMD160[] = { 0x2B, 0x24, 0x08, 0x05, 0x01, 0x02, 0x02};
//! \brief   1.3.36.8.6.1
//! \details Teletrust signature attributes cert 
static const act::byte cvOID_cert[] = { 0x2B, 0x24, 0x08, 0x06, 0x01};
//! \brief   1.3.36.8.6.2
//! \details Teletrust signature attributes certRef 
static const act::byte cvOID_certRef[] = { 0x2B, 0x24, 0x08, 0x06, 0x02};
//! \brief   1.3.36.8.6.3
//! \details Teletrust signature attributes attrCert 
static const act::byte cvOID_attrCert[] = { 0x2B, 0x24, 0x08, 0x06, 0x03};
//! \brief   1.3.36.8.6.4
//! \details Teletrust signature attributes attrRef 
static const act::byte cvOID_attrRef[] = { 0x2B, 0x24, 0x08, 0x06, 0x04};
//! \brief   1.3.36.8.6.5
//! \details Teletrust signature attributes fileName 
static const act::byte cvOID_fileName[] = { 0x2B, 0x24, 0x08, 0x06, 0x05};
//! \brief   1.3.36.8.6.6
//! \details Teletrust signature attributes storageTime 
static const act::byte cvOID_storageTime[] = { 0x2B, 0x24, 0x08, 0x06, 0x06};
//! \brief   1.3.36.8.6.7
//! \details Teletrust signature attributes fileSize 
static const act::byte cvOID_fileSize[] = { 0x2B, 0x24, 0x08, 0x06, 0x07};
//! \brief   1.3.36.8.6.8
//! \details Teletrust signature attributes location 
static const act::byte cvOID_location[] = { 0x2B, 0x24, 0x08, 0x06, 0x08};
//! \brief   1.3.36.8.6.9
//! \details Teletrust signature attributes sigNumber 
static const act::byte cvOID_sigNumber[] = { 0x2B, 0x24, 0x08, 0x06, 0x09};
//! \brief   1.3.36.8.6.10
//! \details Teletrust signature attributes autoGen 
static const act::byte cvOID_autoGen[] = { 0x2B, 0x24, 0x08, 0x06, 0x0A};
//! \brief   1.3.36.8.7.1.1
//! \details Teletrust presentation types ptAdobeILL 
static const act::byte cvOID_ptAdobeILL[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x01};
//! \brief   1.3.36.8.7.1.2
//! \details Teletrust presentation types ptAmiPro 
static const act::byte cvOID_ptAmiPro[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x02};
//! \brief   1.3.36.8.7.1.3
//! \details Teletrust presentation types ptAutoCAD 
static const act::byte cvOID_ptAutoCAD[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x03};
//! \brief   1.3.36.8.7.1.4
//! \details Teletrust presentation types ptBinary 
static const act::byte cvOID_ptBinary[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x04};
//! \brief   1.3.36.8.7.1.5
//! \details Teletrust presentation types ptBMP 
static const act::byte cvOID_ptBMP[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x05};
//! \brief   1.3.36.8.7.1.6
//! \details Teletrust presentation types ptCGM 
static const act::byte cvOID_ptCGM[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x06};
//! \brief   1.3.36.8.7.1.7
//! \details Teletrust presentation types ptCorelCRT 
static const act::byte cvOID_ptCorelCRT[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x07};
//! \brief   1.3.36.8.7.1.8
//! \details Teletrust presentation types ptCorelDRW 
static const act::byte cvOID_ptCorelDRW[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x08};
//! \brief   1.3.36.8.7.1.9
//! \details Teletrust presentation types ptCorelEXC 
static const act::byte cvOID_ptCorelEXC[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x09};
//! \brief   1.3.36.8.7.1.10
//! \details Teletrust presentation types ptCorelPHT 
static const act::byte cvOID_ptCorelPHT[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0A};
//! \brief   1.3.36.8.7.1.11
//! \details Teletrust presentation types ptDraw 
static const act::byte cvOID_ptDraw[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0B};
//! \brief   1.3.36.8.7.1.12
//! \details Teletrust presentation types ptDVI 
static const act::byte cvOID_ptDVI[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0C};
//! \brief   1.3.36.8.7.1.13
//! \details Teletrust presentation types ptEPS 
static const act::byte cvOID_ptEPS[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0D};
//! \brief   1.3.36.8.7.1.14
//! \details Teletrust presentation types ptExcel 
static const act::byte cvOID_ptExcel[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0E};
//! \brief   1.3.36.8.7.1.15
//! \details Teletrust presentation types ptGEM 
static const act::byte cvOID_ptGEM[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x0F};
//! \brief   1.3.36.8.7.1.16
//! \details Teletrust presentation types ptGIF 
static const act::byte cvOID_ptGIF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x10};
//! \brief   1.3.36.8.7.1.17
//! \details Teletrust presentation types ptHPGL 
static const act::byte cvOID_ptHPGL[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x11};
//! \brief   1.3.36.8.7.1.18
//! \details Teletrust presentation types ptJPEG 
static const act::byte cvOID_ptJPEG[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x12};
//! \brief   1.3.36.8.7.1.19
//! \details Teletrust presentation types ptKodak 
static const act::byte cvOID_ptKodak[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x13};
//! \brief   1.3.36.8.7.1.20
//! \details Teletrust presentation types ptLaTeX 
static const act::byte cvOID_ptLaTeX[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x14};
//! \brief   1.3.36.8.7.1.21
//! \details Teletrust presentation types ptLotus 
static const act::byte cvOID_ptLotus[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x15};
//! \brief   1.3.36.8.7.1.22
//! \details Teletrust presentation types ptLotusPIC 
static const act::byte cvOID_ptLotusPIC[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x16};
//! \brief   1.3.36.8.7.1.23
//! \details Teletrust presentation types ptMacPICT 
static const act::byte cvOID_ptMacPICT[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x17};
//! \brief   1.3.36.8.7.1.24
//! \details Teletrust presentation types ptMacWord 
static const act::byte cvOID_ptMacWord[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x18};
//! \brief   1.3.36.8.7.1.25
//! \details Teletrust presentation types ptMSWfD 
static const act::byte cvOID_ptMSWfD[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x19};
//! \brief   1.3.36.8.7.1.26
//! \details Teletrust presentation types ptMSWord 
static const act::byte cvOID_ptMSWord[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1A};
//! \brief   1.3.36.8.7.1.27
//! \details Teletrust presentation types ptMSWord2 
static const act::byte cvOID_ptMSWord2[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1B};
//! \brief   1.3.36.8.7.1.28
//! \details Teletrust presentation types ptMSWord6 
static const act::byte cvOID_ptMSWord6[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1C};
//! \brief   1.3.36.8.7.1.29
//! \details Teletrust presentation types ptMSWord8 
static const act::byte cvOID_ptMSWord8[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1D};
//! \brief   1.3.36.8.7.1.30
//! \details Teletrust presentation types ptPDF 
static const act::byte cvOID_ptPDF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1E};
//! \brief   1.3.36.8.7.1.31
//! \details Teletrust presentation types ptPIF 
static const act::byte cvOID_ptPIF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x1F};
//! \brief   1.3.36.8.7.1.32
//! \details Teletrust presentation types ptPostscript 
static const act::byte cvOID_ptPostscript[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x20};
//! \brief   1.3.36.8.7.1.33
//! \details Teletrust presentation types ptRTF 
static const act::byte cvOID_ptRTF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x21};
//! \brief   1.3.36.8.7.1.34
//! \details Teletrust presentation types ptSCITEX 
static const act::byte cvOID_ptSCITEX[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x22};
//! \brief   1.3.36.8.7.1.35
//! \details Teletrust presentation types ptTAR 
static const act::byte cvOID_ptTAR[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x23};
//! \brief   1.3.36.8.7.1.36
//! \details Teletrust presentation types ptTarga 
static const act::byte cvOID_ptTarga[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x24};
//! \brief   1.3.36.8.7.1.37
//! \details Teletrust presentation types ptTeX 
static const act::byte cvOID_ptTeX[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x25};
//! \brief   1.3.36.8.7.1.38
//! \details Teletrust presentation types ptText 
static const act::byte cvOID_ptText[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x26};
//! \brief   1.3.36.8.7.1.39
//! \details Teletrust presentation types ptTIFF 
static const act::byte cvOID_ptTIFF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x27};
//! \brief   1.3.36.8.7.1.40
//! \details Teletrust presentation types ptTIFF-FC 
static const act::byte cvOID_ptTIFF_FC[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x28};
//! \brief   1.3.36.8.7.1.41
//! \details Teletrust presentation types ptUID 
static const act::byte cvOID_ptUID[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x29};
//! \brief   1.3.36.8.7.1.42
//! \details Teletrust presentation types ptUUEncode 
static const act::byte cvOID_ptUUEncode[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x2A};
//! \brief   1.3.36.8.7.1.43
//! \details Teletrust presentation types ptWMF 
static const act::byte cvOID_ptWMF[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x2B};
//! \brief   1.3.36.8.7.1.44
//! \details Teletrust presentation types ptWordPerfect 
static const act::byte cvOID_ptWordPerfect[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x2C};
//! \brief   1.3.36.8.7.1.45
//! \details Teletrust presentation types ptWPGrph 
static const act::byte cvOID_ptWPGrph[] = { 0x2B, 0x24, 0x08, 0x07, 0x01, 0x2D};
//! \brief   1.3.101.1.4
//! \details Thawte thawte-ce 
static const act::byte cvOID_thawte_ce[] = { 0x2B, 0x65, 0x01, 0x04};
//! \brief   1.3.101.1.4.1
//! \details Thawte certificate extension strongExtranet 
static const act::byte cvOID_strongExtranet[] = { 0x2B, 0x65, 0x01, 0x04, 0x01};
//! \brief   2.5.4.0
//! \details X.520 id-at (2 5 4) objectClass 
static const act::byte cvOID_objectClass[] = { 0x55, 0x04, 0x00};
//! \brief   2.5.4.1
//! \details X.520 id-at (2 5 4) aliasedEntryName 
static const act::byte cvOID_aliasedEntryName[] = { 0x55, 0x04, 0x01};
//! \brief   2.5.4.2
//! \details X.520 id-at (2 5 4) knowledgeInformation 
static const act::byte cvOID_knowledgeInformation[] = { 0x55, 0x04, 0x02};
//! \brief   2.5.4.3
//! \details X.520 id-at (2 5 4) commonName 
static const act::byte cvOID_commonName[] = { 0x55, 0x04, 0x03};
//! \brief   2.5.4.4
//! \details X.520 id-at (2 5 4) surname 
static const act::byte cvOID_surname[] = { 0x55, 0x04, 0x04};
//! \brief   2.5.4.5
//! \details X.520 id-at (2 5 4) serialNumber 
static const act::byte cvOID_serialNumber[] = { 0x55, 0x04, 0x05};
//! \brief   2.5.4.6
//! \details X.520 id-at (2 5 4) countryName 
static const act::byte cvOID_countryName[] = { 0x55, 0x04, 0x06};
//! \brief   2.5.4.7
//! \details X.520 id-at (2 5 4) localityName 
static const act::byte cvOID_localityName[] = { 0x55, 0x04, 0x07};
//! \brief   2.5.4.7.1
//! \details X.520 id-at (2 5 4) collectiveLocalityName 
static const act::byte cvOID_collectiveLocalityName[] = { 0x55, 0x04, 0x07, 0x01};
//! \brief   2.5.4.8
//! \details X.520 id-at (2 5 4) stateOrProvinceName 
static const act::byte cvOID_stateOrProvinceName[] = { 0x55, 0x04, 0x08};
//! \brief   2.5.4.8.1
//! \details X.520 id-at (2 5 4) collectiveStateOrProvinceName 
static const act::byte cvOID_collectiveStateOrProvinceName[] = { 0x55, 0x04, 0x08, 0x01};
//! \brief   2.5.4.9
//! \details X.520 id-at (2 5 4) streetAddress 
static const act::byte cvOID_streetAddress[] = { 0x55, 0x04, 0x09};
//! \brief   2.5.4.9.1
//! \details X.520 id-at (2 5 4) collectiveStreetAddress 
static const act::byte cvOID_collectiveStreetAddress[] = { 0x55, 0x04, 0x09, 0x01};
//! \brief   2.5.4.10
//! \details X.520 id-at (2 5 4) organizationName 
static const act::byte cvOID_organizationName[] = { 0x55, 0x04, 0x0A};
//! \brief   2.5.4.10.1
//! \details X.520 id-at (2 5 4) collectiveOrganizationName 
static const act::byte cvOID_collectiveOrganizationName[] = { 0x55, 0x04, 0x0A, 0x01};
//! \brief   2.5.4.11
//! \details X.520 id-at (2 5 4) organizationalUnitName 
static const act::byte cvOID_organizationalUnitName[] = { 0x55, 0x04, 0x0B};
//! \brief   2.5.4.11.1
//! \details X.520 id-at (2 5 4) collectiveOrganizationalUnitName 
static const act::byte cvOID_collectiveOrganizationalUnitName[] = { 0x55, 0x04, 0x0B, 0x01};
//! \brief   2.5.4.12
//! \details X.520 id-at (2 5 4) title 
static const act::byte cvOID_title[] = { 0x55, 0x04, 0x0C};
//! \brief   2.5.4.13
//! \details X.520 id-at (2 5 4) description 
static const act::byte cvOID_description[] = { 0x55, 0x04, 0x0D};
//! \brief   2.5.4.14
//! \details X.520 id-at (2 5 4) searchGuide 
static const act::byte cvOID_searchGuide[] = { 0x55, 0x04, 0x0E};
//! \brief   2.5.4.15
//! \details X.520 id-at (2 5 4) businessCategory 
static const act::byte cvOID_businessCategory[] = { 0x55, 0x04, 0x0F};
//! \brief   2.5.4.16
//! \details X.520 id-at (2 5 4) postalAddress 
static const act::byte cvOID_postalAddress[] = { 0x55, 0x04, 0x10};
//! \brief   2.5.4.16.1
//! \details X.520 id-at (2 5 4) collectivePostalAddress 
static const act::byte cvOID_collectivePostalAddress[] = { 0x55, 0x04, 0x10, 0x01};
//! \brief   2.5.4.17
//! \details X.520 id-at (2 5 4) postalCode 
static const act::byte cvOID_postalCode[] = { 0x55, 0x04, 0x11};
//! \brief   2.5.4.17.1
//! \details X.520 id-at (2 5 4) collectivePostalCode 
static const act::byte cvOID_collectivePostalCode[] = { 0x55, 0x04, 0x11, 0x01};
//! \brief   2.5.4.18
//! \details X.520 id-at (2 5 4) postOfficeBox 
static const act::byte cvOID_postOfficeBox[] = { 0x55, 0x04, 0x12};
//! \brief   2.5.4.18.1
//! \details X.520 id-at (2 5 4) collectivePostOfficeBox 
static const act::byte cvOID_collectivePostOfficeBox[] = { 0x55, 0x04, 0x12, 0x01};
//! \brief   2.5.4.19
//! \details X.520 id-at (2 5 4) physicalDeliveryOfficeName 
static const act::byte cvOID_physicalDeliveryOfficeName[] = { 0x55, 0x04, 0x13};
//! \brief   2.5.4.19.1
//! \details X.520 id-at (2 5 4) collectivePhysicalDeliveryOfficeName 
static const act::byte cvOID_collectivePhysicalDeliveryOfficeName[] = { 0x55, 0x04, 0x13, 0x01};
//! \brief   2.5.4.20
//! \details X.520 id-at (2 5 4) telephoneNumber 
static const act::byte cvOID_telephoneNumber[] = { 0x55, 0x04, 0x14};
//! \brief   2.5.4.20.1
//! \details X.520 id-at (2 5 4) collectiveTelephoneNumber 
static const act::byte cvOID_collectiveTelephoneNumber[] = { 0x55, 0x04, 0x14, 0x01};
//! \brief   2.5.4.21
//! \details X.520 id-at (2 5 4) telexNumber 
static const act::byte cvOID_telexNumber[] = { 0x55, 0x04, 0x15};
//! \brief   2.5.4.21.1
//! \details X.520 id-at (2 5 4) collectiveTelexNumber 
static const act::byte cvOID_collectiveTelexNumber[] = { 0x55, 0x04, 0x15, 0x01};
//! \brief   2.5.4.22
//! \details X.520 id-at (2 5 4) teletexTerminalIdentifier 
static const act::byte cvOID_teletexTerminalIdentifier[] = { 0x55, 0x04, 0x16};
//! \brief   2.5.4.22.1
//! \details X.520 id-at (2 5 4) collectiveTeletexTerminalIdentifier 
static const act::byte cvOID_collectiveTeletexTerminalIdentifier[] = { 0x55, 0x04, 0x16, 0x01};
//! \brief   2.5.4.23
//! \details X.520 id-at (2 5 4) facsimileTelephoneNumber 
static const act::byte cvOID_facsimileTelephoneNumber[] = { 0x55, 0x04, 0x17};
//! \brief   2.5.4.23.1
//! \details X.520 id-at (2 5 4) collectiveFacsimileTelephoneNumber 
static const act::byte cvOID_collectiveFacsimileTelephoneNumber[] = { 0x55, 0x04, 0x17, 0x01};
//! \brief   2.5.4.24
//! \details X.520 id-at (2 5 4) x121Address 
static const act::byte cvOID_x121Address[] = { 0x55, 0x04, 0x18};
//! \brief   2.5.4.25
//! \details X.520 id-at (2 5 4) internationalISDNNumber 
static const act::byte cvOID_internationalISDNNumber[] = { 0x55, 0x04, 0x19};
//! \brief   2.5.4.25.1
//! \details X.520 id-at (2 5 4) collectiveInternationalISDNNumber 
static const act::byte cvOID_collectiveInternationalISDNNumber[] = { 0x55, 0x04, 0x19, 0x01};
//! \brief   2.5.4.26
//! \details X.520 id-at (2 5 4) registeredAddress 
static const act::byte cvOID_registeredAddress[] = { 0x55, 0x04, 0x1A};
//! \brief   2.5.4.27
//! \details X.520 id-at (2 5 4) destinationIndicator 
static const act::byte cvOID_destinationIndicator[] = { 0x55, 0x04, 0x1B};
//! \brief   2.5.4.28
//! \details X.520 id-at (2 5 4) preferredDeliveryMehtod 
static const act::byte cvOID_preferredDeliveryMehtod[] = { 0x55, 0x04, 0x1C};
//! \brief   2.5.4.29
//! \details X.520 id-at (2 5 4) presentationAddress 
static const act::byte cvOID_presentationAddress[] = { 0x55, 0x04, 0x1D};
//! \brief   2.5.4.30
//! \details X.520 id-at (2 5 4) supportedApplicationContext 
static const act::byte cvOID_supportedApplicationContext[] = { 0x55, 0x04, 0x1E};
//! \brief   2.5.4.31
//! \details X.520 id-at (2 5 4) member 
static const act::byte cvOID_member[] = { 0x55, 0x04, 0x1F};
//! \brief   2.5.4.32
//! \details X.520 id-at (2 5 4) owner 
static const act::byte cvOID_owner[] = { 0x55, 0x04, 0x20};
//! \brief   2.5.4.33
//! \details X.520 id-at (2 5 4) roleOccupant 
static const act::byte cvOID_roleOccupant[] = { 0x55, 0x04, 0x21};
//! \brief   2.5.4.34
//! \details X.520 id-at (2 5 4) seeAlso 
static const act::byte cvOID_seeAlso[] = { 0x55, 0x04, 0x22};
//! \brief   2.5.4.35
//! \details X.520 id-at (2 5 4) userPassword 
static const act::byte cvOID_userPassword[] = { 0x55, 0x04, 0x23};
//! \brief   2.5.4.36
//! \details X.520 id-at (2 5 4) userCertificate 
static const act::byte cvOID_userCertificate[] = { 0x55, 0x04, 0x24};
//! \brief   2.5.4.37
//! \details X.520 id-at (2 5 4) caCertificate 
static const act::byte cvOID_caCertificate[] = { 0x55, 0x04, 0x25};
//! \brief   2.5.4.38
//! \details X.520 id-at (2 5 4) authorityRevocationList 
static const act::byte cvOID_authorityRevocationList[] = { 0x55, 0x04, 0x26};
//! \brief   2.5.4.39
//! \details X.520 id-at (2 5 4) certificateRevocationList 
static const act::byte cvOID_certificateRevocationList[] = { 0x55, 0x04, 0x27};
//! \brief   2.5.4.40
//! \details X.520 id-at (2 5 4) crossCertificatePair 
static const act::byte cvOID_crossCertificatePair_2[] = { 0x55, 0x04, 0x28};
//! \brief   2.5.4.41
//! \details X.520 id-at (2 5 4) name 
static const act::byte cvOID_name[] = { 0x55, 0x04, 0x29};
//! \brief   2.5.4.42
//! \details X.520 id-at (2 5 4) givenName 
static const act::byte cvOID_givenName[] = { 0x55, 0x04, 0x2A};
//! \brief   2.5.4.43
//! \details X.520 id-at (2 5 4) initials 
static const act::byte cvOID_initials[] = { 0x55, 0x04, 0x2B};
//! \brief   2.5.4.44
//! \details X.520 id-at (2 5 4) generationQualifier 
static const act::byte cvOID_generationQualifier[] = { 0x55, 0x04, 0x2C};
//! \brief   2.5.4.45
//! \details X.520 id-at (2 5 4) uniqueIdentifier 
static const act::byte cvOID_uniqueIdentifier[] = { 0x55, 0x04, 0x2D};
//! \brief   2.5.4.46
//! \details X.520 id-at (2 5 4) dnQualifier 
static const act::byte cvOID_dnQualifier[] = { 0x55, 0x04, 0x2E};
//! \brief   2.5.4.47
//! \details X.520 id-at (2 5 4) enhancedSearchGuide 
static const act::byte cvOID_enhancedSearchGuide[] = { 0x55, 0x04, 0x2F};
//! \brief   2.5.4.48
//! \details X.520 id-at (2 5 4) protocolInformation 
static const act::byte cvOID_protocolInformation[] = { 0x55, 0x04, 0x30};
//! \brief   2.5.4.49
//! \details X.520 id-at (2 5 4) distinguishedName 
static const act::byte cvOID_distinguishedName[] = { 0x55, 0x04, 0x31};
//! \brief   2.5.4.50
//! \details X.520 id-at (2 5 4) uniqueMember 
static const act::byte cvOID_uniqueMember[] = { 0x55, 0x04, 0x32};
//! \brief   2.5.4.51
//! \details X.520 id-at (2 5 4) houseIdentifier 
static const act::byte cvOID_houseIdentifier[] = { 0x55, 0x04, 0x33};
//! \brief   2.5.4.52
//! \details X.520 id-at (2 5 4) supportedAlgorithms 
static const act::byte cvOID_supportedAlgorithms[] = { 0x55, 0x04, 0x34};
//! \brief   2.5.4.53
//! \details X.520 id-at (2 5 4) deltaRevocationList 
static const act::byte cvOID_deltaRevocationList[] = { 0x55, 0x04, 0x35};
//! \brief   2.5.4.55
//! \details X.520 id-at (2 5 4) clearance 
static const act::byte cvOID_clearance[] = { 0x55, 0x04, 0x36};
//! \brief   2.5.4.58
//! \details X.520 id-at (2 5 4) crossCertificatePair 
static const act::byte cvOID_crossCertificatePair_1[] = { 0x55, 0x04, 0x3A};
//! \brief   2.5.4.65
//! \details Naming attributes of type X520Pseudonym
static const act::byte cvOID_pseudonym[] =    { 0x55, 0x04, 0x41};
//! \brief   2.5.8.1.1
//! \details X.500 algorithms.  Ambiguous, since no padding rules specified rsa 
static const act::byte cvOID_rsa_X500[] = { 0x55, 0x08, 0x01, 0x01};
//! \brief   2.5.29.1
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 35) instead authorityKeyIdentifier 
static const act::byte cvOID_authorityKeyIdentifier_old[] = { 0x55, 0x1D, 0x01};
//! \brief   2.5.29.2
//! \details X.520 id-ce (2 5 29).  Obsolete, use keyUsage/extKeyUsage instead keyAttributes 
static const act::byte cvOID_keyAttributes[] = { 0x55, 0x1D, 0x02};
//! \brief   2.5.29.3
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 32) instead certificatePolicies 
static const act::byte cvOID_certificatePolicies_old[] = { 0x55, 0x1D, 0x03};
//! \brief   2.5.29.4
//! \details X.520 id-ce (2 5 29).  Obsolete, use keyUsage/extKeyUsage instead keyUsageRestriction 
static const act::byte cvOID_keyUsageRestriction[] = { 0x55, 0x1D, 0x04};
//! \brief   2.5.29.5
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 33) instead policyMapping 
static const act::byte cvOID_policyMapping[] = { 0x55, 0x1D, 0x05};
//! \brief   2.5.29.6
//! \details X.520 id-ce (2 5 29).  Obsolete, use namestatic constraints instead subtreesstatic constraint 
static const act::byte cvOID_subtreesconstraint[] = { 0x55, 0x1D, 0x06};
//! \brief   2.5.29.7
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 17) instead subjectAltName 
static const act::byte cvOID_subjectAltName_old[] = { 0x55, 0x1D, 0x07};
//! \brief   2.5.29.8
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 18) instead issuerAltName 
static const act::byte cvOID_issuerAltName_old[] = { 0x55, 0x1D, 0x08};
//! \brief   2.5.29.9
//! \details X.520 id-ce (2 5 29) subjectDirectoryAttributes 
static const act::byte cvOID_subjectDirectoryAttributes[] = { 0x55, 0x1D, 0x09};
//! \brief   2.5.29.10
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 19) instead basicstatic constraints 
static const act::byte cvOID_basicconstraints_old[] = { 0x55, 0x1D, 0x0A};
//! \brief   2.5.29.11
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 30) instead namestatic constraints 
static const act::byte cvOID_nameconstraints_old[] = { 0x55, 0x1D, 0x0B};
//! \brief   2.5.29.12
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 36) instead policystatic constraints 
static const act::byte cvOID_policyconstraints_old_1[] = { 0x55, 0x1D, 0x0C};
//! \brief   2.5.29.13
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 19) instead basicstatic constraints 
static const act::byte cvOID_basicconstraints_2[] = { 0x55, 0x1D, 0x0D};
//! \brief   2.5.29.14
//! \details X.520 id-ce (2 5 29) subjectKeyIdentifier 
static const act::byte cvOID_subjectKeyIdentifier[] = { 0x55, 0x1D, 0x0E};
//! \brief   2.5.29.15
//! \details X.520 id-ce (2 5 29) keyUsage 
static const act::byte cvOID_keyUsage[] = { 0x55, 0x1D, 0x0F};
//! \brief   2.5.29.16
//! \details X.520 id-ce (2 5 29) privateKeyUsagePeriod 
static const act::byte cvOID_privateKeyUsagePeriod[] = { 0x55, 0x1D, 0x10};
//! \brief   2.5.29.17
//! \details X.520 id-ce (2 5 29) subjectAltName 
static const act::byte cvOID_subjectAltName[] = { 0x55, 0x1D, 0x11};
//! \brief   2.5.29.18
//! \details X.520 id-ce (2 5 29) issuerAltName 
static const act::byte cvOID_issuerAltName[] = { 0x55, 0x1D, 0x12};
//! \brief   2.5.29.19
//! \details X.520 id-ce (2 5 29) basicstatic constraints 
static const act::byte cvOID_basicconstraints[] = { 0x55, 0x1D, 0x13};
//! \brief   2.5.29.20
//! \details X.520 id-ce (2 5 29) cRLNumber 
static const act::byte cvOID_cRLNumber[] = { 0x55, 0x1D, 0x14};
//! \brief   2.5.29.21
//! \details X.520 id-ce (2 5 29) cRLReason 
static const act::byte cvOID_cRLReason[] = { 0x55, 0x1D, 0x15};
//! \brief   2.5.29.22
//! \details X.520 id-ce (2 5 29).  Deprecated, alternative OID uncertain expirationDate 
static const act::byte cvOID_expirationDate[] = { 0x55, 0x1D, 0x16};
//! \brief   2.5.29.23
//! \details X.520 id-ce (2 5 29) instructionCode 
static const act::byte cvOID_instructionCode[] = { 0x55, 0x1D, 0x17};
//! \brief   2.5.29.24
//! \details X.520 id-ce (2 5 29) invalidityDate 
static const act::byte cvOID_invalidityDate[] = { 0x55, 0x1D, 0x18};
//! \brief   2.5.29.25
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 31) instead cRLDistributionPoints 
static const act::byte cvOID_cRLDistributionPoints_old[] = { 0x55, 0x1D, 0x19};
//! \brief   2.5.29.26
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 28) instead issuingDistributionPoint 
static const act::byte cvOID_issuingDistributionPoint_old[] = { 0x55, 0x1D, 0x1A};
//! \brief   2.5.29.27
//! \details X.520 id-ce (2 5 29) deltaCRLIndicator 
static const act::byte cvOID_deltaCRLIndicator[] = { 0x55, 0x1D, 0x1B};
//! \brief   2.5.29.28
//! \details X.520 id-ce (2 5 29) issuingDistributionPoint 
static const act::byte cvOID_issuingDistributionPoint[] = { 0x55, 0x1D, 0x1C};
//! \brief   2.5.29.29
//! \details X.520 id-ce (2 5 29) certificateIssuer 
static const act::byte cvOID_certificateIssuer[] = { 0x55, 0x1D, 0x1D};
//! \brief   2.5.29.30
//! \details X.520 id-ce (2 5 29) namestatic constraints 
static const act::byte cvOID_nameconstraints[] = { 0x55, 0x1D, 0x1E};
//! \brief   2.5.29.31
//! \details X.520 id-ce (2 5 29) cRLDistributionPoints 
static const act::byte cvOID_cRLDistributionPoints[] = { 0x55, 0x1D, 0x1F};
//! \brief   2.5.29.32
//! \details X.520 id-ce (2 5 29) certificatePolicies 
static const act::byte cvOID_certificatePolicies[] = { 0x55, 0x1D, 0x20};
//! \brief   2.5.29.32.0
//! \details X.520 id-ce (2 5 29.0) anyPolicies 
static const act::byte cvOID_anyPolicies[] = { 0x55, 0x1D, 0x20, 0x00};
//! \brief   2.5.29.33
//! \details X.520 id-ce (2 5 29) policyMappings 
static const act::byte cvOID_policyMappings[] = { 0x55, 0x1D, 0x21};
//! \brief   2.5.29.34
//! \details X.520 id-ce (2 5 29).  Deprecated, use (2 5 29 36) instead policystatic constraints 
static const act::byte cvOID_policyconstraints_old_2[] = { 0x55, 0x1D, 0x22};
//! \brief   2.5.29.35
//! \details X.520 id-ce (2 5 29) authorityKeyIdentifier 
static const act::byte cvOID_authorityKeyIdentifier[] = { 0x55, 0x1D, 0x23};
//! \brief   2.5.29.36
//! \details X.520 id-ce (2 5 29) policystatic constraints 
static const act::byte cvOID_policyconstraints[] = { 0x55, 0x1D, 0x24};
//! \brief   2.5.29.37
//! \details X.520 id-ce (2 5 29) extKeyUsage 
static const act::byte cvOID_extKeyUsage[] = { 0x55, 0x1D, 0x25};
//! \brief   2.5.29.37.0
//! \details anyExtendedKeyUsage id-ce-extKeyUsage 0
static const act::byte cvOID_anyExtendedKeyUsage[] = { 0x55, 0x1D, 0x25, 0x00};

// AME
//! \brief   2.5.29.46
//! \details X.520 id-ce (2 5 29) id-ce-freshestCRL 
static const act::byte cvOID_freshestCRL[] = { 0x55, 0x1D, 0x2E};
//! \brief   2.5.29.54
//! \details X.520 id-ce (2 5 29) inhibitAnyPolicy 
static const act::byte cvOID_inhibitAnyPolicy[] = { 0x55, 0x1D, 0x36};

//! \brief   2.16.840.1.101.2.1.1.1
//! \details SDN.700 INFOSEC algorithms sdnsSignatureAlgorithm 
static const act::byte cvOID_sdnsSignatureAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x01};
//! \brief   2.16.840.1.101.2.1.1.2
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicSignatureAlgorithm, this OID is better known as dsaWithSHA-1. fortezzaSignatureAlgorithm 
static const act::byte cvOID_fortezzaSignatureAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x02};
//! \brief   2.16.840.1.101.2.1.1.3
//! \details SDN.700 INFOSEC algorithms sdnsConfidentialityAlgorithm 
static const act::byte cvOID_sdnsConfidentialityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x03};
//! \brief   2.16.840.1.101.2.1.1.4
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicConfidentialityAlgorithm fortezzaConfidentialityAlgorithm 
static const act::byte cvOID_fortezzaConfidentialityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x04};
//! \brief   2.16.840.1.101.2.1.1.5
//! \details SDN.700 INFOSEC algorithms sdnsIntegrityAlgorithm 
static const act::byte cvOID_sdnsIntegrityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x05};
//! \brief   2.16.840.1.101.2.1.1.6
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicIntegrityAlgorithm fortezzaIntegrityAlgorithm 
static const act::byte cvOID_fortezzaIntegrityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x06};
//! \brief   2.16.840.1.101.2.1.1.7
//! \details SDN.700 INFOSEC algorithms sdnsTokenProtectionAlgorithm 
static const act::byte cvOID_sdnsTokenProtectionAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x07};
//! \brief   2.16.840.1.101.2.1.1.8
//! \details SDN.700 INFOSEC algorithms.  Formerly know as mosaicTokenProtectionAlgorithm fortezzaTokenProtectionAlgorithm 
static const act::byte cvOID_fortezzaTokenProtectionAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x08};
//! \brief   2.16.840.1.101.2.1.1.9
//! \details SDN.700 INFOSEC algorithms sdnsKeyManagementAlgorithm 
static const act::byte cvOID_sdnsKeyManagementAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x09};
//! \brief   2.16.840.1.101.2.1.1.10
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicKeyManagementAlgorithm fortezzaKeyManagementAlgorithm 
static const act::byte cvOID_fortezzaKeyManagementAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0A};
//! \brief   2.16.840.1.101.2.1.1.11
//! \details SDN.700 INFOSEC algorithms sdnsKMandSigAlgorithm 
static const act::byte cvOID_sdnsKMandSigAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0B};
//! \brief   2.16.840.1.101.2.1.1.12
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicKMandSigAlgorithm fortezzaKMandSigAlgorithm 
static const act::byte cvOID_fortezzaKMandSigAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0C};
//! \brief   2.16.840.1.101.2.1.1.13
//! \details SDN.700 INFOSEC algorithms suiteASignatureAlgorithm 
static const act::byte cvOID_suiteASignatureAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0D};
//! \brief   2.16.840.1.101.2.1.1.14
//! \details SDN.700 INFOSEC algorithms suiteAConfidentialityAlgorithm 
static const act::byte cvOID_suiteAConfidentialityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0E};
//! \brief   2.16.840.1.101.2.1.1.15
//! \details SDN.700 INFOSEC algorithms suiteAIntegrityAlgorithm 
static const act::byte cvOID_suiteAIntegrityAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x0F};
//! \brief   2.16.840.1.101.2.1.1.16
//! \details SDN.700 INFOSEC algorithms suiteATokenProtectionAlgorithm 
static const act::byte cvOID_suiteATokenProtectionAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x10};
//! \brief   2.16.840.1.101.2.1.1.17
//! \details SDN.700 INFOSEC algorithms suiteAKeyManagementAlgorithm 
static const act::byte cvOID_suiteAKeyManagementAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x11};
//! \brief   2.16.840.1.101.2.1.1.18
//! \details SDN.700 INFOSEC algorithms suiteAKMandSigAlgorithm 
static const act::byte cvOID_suiteAKMandSigAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x12};
//! \brief   2.16.840.1.101.2.1.1.19
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicUpdatedSigAlgorithm fortezzaUpdatedSigAlgorithm 
static const act::byte cvOID_fortezzaUpdatedSigAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x13};
//! \brief   2.16.840.1.101.2.1.1.20
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicKMandUpdSigAlgorithms fortezzaKMandUpdSigAlgorithms 
static const act::byte cvOID_fortezzaKMandUpdSigAlgorithms[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x14};
//! \brief   2.16.840.1.101.2.1.1.21
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicUpdatedIntegAlgorithm fortezzaUpdatedIntegAlgorithm 
static const act::byte cvOID_fortezzaUpdatedIntegAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x15};
//! \brief   2.16.840.1.101.2.1.1.22
//! \details SDN.700 INFOSEC algorithms.  Formerly known as mosaicKeyEncryptionAlgorithm keyExchangeAlgorithm 
static const act::byte cvOID_keyExchangeAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x16};
//! \brief   2.16.840.1.101.2.1.1.23
//! \details SDN.700 INFOSEC algorithms fortezzaWrap80Algorithm 
static const act::byte cvOID_fortezzaWrap80Algorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x17};
//! \brief   2.16.840.1.101.2.1.1.24
//! \details SDN.700 INFOSEC algorithms kEAKeyEncryptionAlgorithm 
static const act::byte cvOID_kEAKeyEncryptionAlgorithm[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x01, 0x18};
//! \brief   2.16.840.1.101.2.1.2.1
//! \details SDN.700 INFOSEC format rfc822MessageFormat 
static const act::byte cvOID_rfc822MessageFormat[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x01};
//! \brief   2.16.840.1.101.2.1.2.2
//! \details SDN.700 INFOSEC format emptyContent 
static const act::byte cvOID_emptyContent[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x02};
//! \brief   2.16.840.1.101.2.1.2.3
//! \details SDN.700 INFOSEC format cspContentType 
static const act::byte cvOID_cspContentType[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x03};
//! \brief   2.16.840.1.101.2.1.2.42
//! \details SDN.700 INFOSEC format mspRev3ContentType 
static const act::byte cvOID_mspRev3ContentType[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x2A};
//! \brief   2.16.840.1.101.2.1.2.48
//! \details SDN.700 INFOSEC format mspContentType 
static const act::byte cvOID_mspContentType[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x30};
//! \brief   2.16.840.1.101.2.1.2.49
//! \details SDN.700 INFOSEC format mspRekeyAgentProtocol 
static const act::byte cvOID_mspRekeyAgentProtocol[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x31};
//! \brief   2.16.840.1.101.2.1.2.50
//! \details SDN.700 INFOSEC format mspMMP 
static const act::byte cvOID_mspMMP[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x32};
//! \brief   2.16.840.1.101.2.1.2.66
//! \details SDN.700 INFOSEC format mspRev3-1ContentType 
static const act::byte cvOID_mspRev3_1ContentType[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x42};
//! \brief   2.16.840.1.101.2.1.2.72
//! \details SDN.700 INFOSEC format forwardedMSPMessageBodyPart 
static const act::byte cvOID_forwardedMSPMessageBodyPart[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x48};
//! \brief   2.16.840.1.101.2.1.2.73
//! \details SDN.700 INFOSEC format mspForwardedMessageParameters 
static const act::byte cvOID_mspForwardedMessageParameters[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x49};
//! \brief   2.16.840.1.101.2.1.2.74
//! \details SDN.700 INFOSEC format forwardedCSPMsgBodyPart 
static const act::byte cvOID_forwardedCSPMsgBodyPart[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x50};
//! \brief   2.16.840.1.101.2.1.2.75
//! \details SDN.700 INFOSEC format cspForwardedMessageParameters 
static const act::byte cvOID_cspForwardedMessageParameters[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x51};
//! \brief   2.16.840.1.101.2.1.2.76
//! \details SDN.700 INFOSEC format mspMMP2 
static const act::byte cvOID_mspMMP2[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x02, 0x52};
//! \brief   2.16.840.1.101.2.1.3.1
//! \details SDN.700 INFOSEC policy sdnsSecurityPolicy 
static const act::byte cvOID_sdnsSecurityPolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x01};
//! \brief   2.16.840.1.101.2.1.3.2
//! \details SDN.700 INFOSEC policy sdnsPRBAC 
static const act::byte cvOID_sdnsPRBAC[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x02};
//! \brief   2.16.840.1.101.2.1.3.3
//! \details SDN.700 INFOSEC policy mosaicPRBAC 
static const act::byte cvOID_mosaicPRBAC[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x03};
//! \brief   2.16.840.1.101.2.1.3.10
//! \details SDN.700 INFOSEC policy siSecurityPolicy 
static const act::byte cvOID_siSecurityPolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A};
//! \brief   2.16.840.1.101.2.1.3.10.0
//! \details SDN.700 INFOSEC policy (obsolete) siNASP 
static const act::byte cvOID_siNASP[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x00};
//! \brief   2.16.840.1.101.2.1.3.10.1
//! \details SDN.700 INFOSEC policy (obsolete) siELCO 
static const act::byte cvOID_siELCO[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x01};
//! \brief   2.16.840.1.101.2.1.3.10.2
//! \details SDN.700 INFOSEC policy (obsolete) siTK 
static const act::byte cvOID_siTK[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x02};
//! \brief   2.16.840.1.101.2.1.3.10.3
//! \details SDN.700 INFOSEC policy (obsolete) siDSAP 
static const act::byte cvOID_siDSAP[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x03};
//! \brief   2.16.840.1.101.2.1.3.10.4
//! \details SDN.700 INFOSEC policy (obsolete) siSSSS 
static const act::byte cvOID_siSSSS[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x04};
//! \brief   2.16.840.1.101.2.1.3.10.5
//! \details SDN.700 INFOSEC policy (obsolete) siDNASP 
static const act::byte cvOID_siDNASP[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x05};
//! \brief   2.16.840.1.101.2.1.3.10.6
//! \details SDN.700 INFOSEC policy (obsolete) siBYEMAN 
static const act::byte cvOID_siBYEMAN[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x06};
//! \brief   2.16.840.1.101.2.1.3.10.7
//! \details SDN.700 INFOSEC policy (obsolete) siREL-US 
static const act::byte cvOID_siREL_US[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x07};
//! \brief   2.16.840.1.101.2.1.3.10.8
//! \details SDN.700 INFOSEC policy (obsolete) siREL-AUS 
static const act::byte cvOID_siREL_AUS[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x08};
//! \brief   2.16.840.1.101.2.1.3.10.9
//! \details SDN.700 INFOSEC policy (obsolete) siREL-CAN 
static const act::byte cvOID_siREL_CAN[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x09};
//! \brief   2.16.840.1.101.2.1.3.10.10
//! \details SDN.700 INFOSEC policy (obsolete) siREL_UK 
static const act::byte cvOID_siREL_UK[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0A};
//! \brief   2.16.840.1.101.2.1.3.10.11
//! \details SDN.700 INFOSEC policy (obsolete) siREL-NZ 
static const act::byte cvOID_siREL_NZ[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0B};
//! \brief   2.16.840.1.101.2.1.3.10.12
//! \details SDN.700 INFOSEC policy (obsolete) siGeneric 
static const act::byte cvOID_siGeneric[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0A, 0x0C};
//! \brief   2.16.840.1.101.2.1.3.11
//! \details SDN.700 INFOSEC policy genser 
static const act::byte cvOID_genser[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B};
//! \brief   2.16.840.1.101.2.1.3.11.0
//! \details SDN.700 INFOSEC policy (obsolete) genserNations 
static const act::byte cvOID_genserNations[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x00};
//! \brief   2.16.840.1.101.2.1.3.11.1
//! \details SDN.700 INFOSEC policy (obsolete) genserComsec 
static const act::byte cvOID_genserComsec[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x01};
//! \brief   2.16.840.1.101.2.1.3.11.2
//! \details SDN.700 INFOSEC policy (obsolete) genserAcquisition 
static const act::byte cvOID_genserAcquisition[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x02};
//! \brief   2.16.840.1.101.2.1.3.11.3
//! \details SDN.700 INFOSEC policy genserSecurityCategories 
static const act::byte cvOID_genserSecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x03};
//! \brief   2.16.840.1.101.2.1.3.11.3.0
//! \details SDN.700 INFOSEC GENSER policy genserTagSetName 
static const act::byte cvOID_genserTagSetName[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0B, 0x03, 0x00};
//! \brief   2.16.840.1.101.2.1.3.12
//! \details SDN.700 INFOSEC policy defaultSecurityPolicy 
static const act::byte cvOID_defaultSecurityPolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0C};
//! \brief   2.16.840.1.101.2.1.3.13
//! \details SDN.700 INFOSEC policy capcoMarkings 
static const act::byte cvOID_capcoMarkings[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D};
//! \brief   2.16.840.1.101.2.1.3.13.0
//! \details SDN.700 INFOSEC policy CAPCO markings capcoSecurityCategories 
static const act::byte cvOID_capcoSecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00};
//! \brief   2.16.840.1.101.2.1.3.13.0.1
//! \details SDN.700 INFOSEC policy CAPCO markings capcoTagSetName1 
static const act::byte cvOID_capcoTagSetName1[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x01};
//! \brief   2.16.840.1.101.2.1.3.13.0.2
//! \details SDN.700 INFOSEC policy CAPCO markings capcoTagSetName2 
static const act::byte cvOID_capcoTagSetName2[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x02};
//! \brief   2.16.840.1.101.2.1.3.13.0.3
//! \details SDN.700 INFOSEC policy CAPCO markings capcoTagSetName3 
static const act::byte cvOID_capcoTagSetName3[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x03};
//! \brief   2.16.840.1.101.2.1.3.13.0.4
//! \details SDN.700 INFOSEC policy CAPCO markings capcoTagSetName4 
static const act::byte cvOID_capcoTagSetName4[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x03, 0x0D, 0x00, 0x04};
//! \brief   2.16.840.1.101.2.1.5.1
//! \details SDN.700 INFOSEC attributes (superseded) sdnsKeyManagementCertificate 
static const act::byte cvOID_sdnsKeyManagementCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x01};
//! \brief   2.16.840.1.101.2.1.5.2
//! \details SDN.700 INFOSEC attributes (superseded) sdnsUserSignatureCertificate 
static const act::byte cvOID_sdnsUserSignatureCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x02};
//! \brief   2.16.840.1.101.2.1.5.3
//! \details SDN.700 INFOSEC attributes (superseded) sdnsKMandSigCertificate 
static const act::byte cvOID_sdnsKMandSigCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x03};
//! \brief   2.16.840.1.101.2.1.5.4
//! \details SDN.700 INFOSEC attributes (superseded) fortezzaKeyManagementCertificate 
static const act::byte cvOID_fortezzaKeyManagementCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x04};
//! \brief   2.16.840.1.101.2.1.5.5
//! \details SDN.700 INFOSEC attributes (superseded) fortezzaKMandSigCertificate 
static const act::byte cvOID_fortezzaKMandSigCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x05};
//! \brief   2.16.840.1.101.2.1.5.6
//! \details SDN.700 INFOSEC attributes (superseded) fortezzaUserSignatureCertificate 
static const act::byte cvOID_fortezzaUserSignatureCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x06};
//! \brief   2.16.840.1.101.2.1.5.7
//! \details SDN.700 INFOSEC attributes (superseded) fortezzaCASignatureCertificate 
static const act::byte cvOID_fortezzaCASignatureCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x07};
//! \brief   2.16.840.1.101.2.1.5.8
//! \details SDN.700 INFOSEC attributes (superseded) sdnsCASignatureCertificate 
static const act::byte cvOID_sdnsCASignatureCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x08};
//! \brief   2.16.840.1.101.2.1.5.10
//! \details SDN.700 INFOSEC attributes (superseded) auxiliaryVector 
static const act::byte cvOID_auxiliaryVector[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0A};
//! \brief   2.16.840.1.101.2.1.5.11
//! \details SDN.700 INFOSEC attributes mlReceiptPolicy 
static const act::byte cvOID_mlReceiptPolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0B};
//! \brief   2.16.840.1.101.2.1.5.12
//! \details SDN.700 INFOSEC attributes mlMembership 
static const act::byte cvOID_mlMembership[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0C};
//! \brief   2.16.840.1.101.2.1.5.13
//! \details SDN.700 INFOSEC attributes mlAdministrators 
static const act::byte cvOID_mlAdministrators[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0D};
//! \brief   2.16.840.1.101.2.1.5.14
//! \details SDN.700 INFOSEC attributes alid 
static const act::byte cvOID_alid[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x0E};
//! \brief   2.16.840.1.101.2.1.5.20
//! \details SDN.700 INFOSEC attributes janUKMs 
static const act::byte cvOID_janUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x14};
//! \brief   2.16.840.1.101.2.1.5.21
//! \details SDN.700 INFOSEC attributes febUKMs 
static const act::byte cvOID_febUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x15};
//! \brief   2.16.840.1.101.2.1.5.22
//! \details SDN.700 INFOSEC attributes marUKMs 
static const act::byte cvOID_marUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x16};
//! \brief   2.16.840.1.101.2.1.5.23
//! \details SDN.700 INFOSEC attributes aprUKMs 
static const act::byte cvOID_aprUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x17};
//! \brief   2.16.840.1.101.2.1.5.24
//! \details SDN.700 INFOSEC attributes mayUKMs 
static const act::byte cvOID_mayUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x18};
//! \brief   2.16.840.1.101.2.1.5.25
//! \details SDN.700 INFOSEC attributes junUKMs 
static const act::byte cvOID_junUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x19};
//! \brief   2.16.840.1.101.2.1.5.26
//! \details SDN.700 INFOSEC attributes julUKMs 
static const act::byte cvOID_julUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1A};
//! \brief   2.16.840.1.101.2.1.5.27
//! \details SDN.700 INFOSEC attributes augUKMs 
static const act::byte cvOID_augUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1B};
//! \brief   2.16.840.1.101.2.1.5.28
//! \details SDN.700 INFOSEC attributes sepUKMs 
static const act::byte cvOID_sepUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1C};
//! \brief   2.16.840.1.101.2.1.5.29
//! \details SDN.700 INFOSEC attributes octUKMs 
static const act::byte cvOID_octUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1D};
//! \brief   2.16.840.1.101.2.1.5.30
//! \details SDN.700 INFOSEC attributes novUKMs 
static const act::byte cvOID_novUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1E};
//! \brief   2.16.840.1.101.2.1.5.21
//! \details SDN.700 INFOSEC attributes decUKMs 
static const act::byte cvOID_decUKMs[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x1F};
//! \brief   2.16.840.1.101.2.1.5.40
//! \details SDN.700 INFOSEC attributes metaSDNSckl 
static const act::byte cvOID_metaSDNSckl[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x28};
//! \brief   2.16.840.1.101.2.1.5.41
//! \details SDN.700 INFOSEC attributes sdnsCKL 
static const act::byte cvOID_sdnsCKL[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x29};
//! \brief   2.16.840.1.101.2.1.5.42
//! \details SDN.700 INFOSEC attributes metaSDNSsignatureCKL 
static const act::byte cvOID_metaSDNSsignatureCKL[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2A};
//! \brief   2.16.840.1.101.2.1.5.43
//! \details SDN.700 INFOSEC attributes sdnsSignatureCKL 
static const act::byte cvOID_sdnsSignatureCKL[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2B};
//! \brief   2.16.840.1.101.2.1.5.44
//! \details SDN.700 INFOSEC attributes sdnsCertificateRevocationList 
static const act::byte cvOID_sdnsCertificateRevocationList[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2C};
//! \brief   2.16.840.1.101.2.1.5.45
//! \details SDN.700 INFOSEC attributes (superseded) fortezzaCertificateRevocationList 
static const act::byte cvOID_fortezzaCertificateRevocationList[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2D};
//! \brief   2.16.840.1.101.2.1.5.46
//! \details SDN.700 INFOSEC attributes fortezzaCKL 
static const act::byte cvOID_fortezzaCKL[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2E};
//! \brief   2.16.840.1.101.2.1.5.47
//! \details SDN.700 INFOSEC attributes alExemptedAddressProcessor 
static const act::byte cvOID_alExemptedAddressProcessor[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x2F};
//! \brief   2.16.840.1.101.2.1.5.48
//! \details SDN.700 INFOSEC attributes (obsolete) guard 
static const act::byte cvOID_guard[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x30};
//! \brief   2.16.840.1.101.2.1.5.49
//! \details SDN.700 INFOSEC attributes (obsolete) algorithmsSupported 
static const act::byte cvOID_algorithmsSupported[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x31};
//! \brief   2.16.840.1.101.2.1.5.50
//! \details SDN.700 INFOSEC attributes (obsolete) suiteAKeyManagementCertificate 
static const act::byte cvOID_suiteAKeyManagementCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x32};
//! \brief   2.16.840.1.101.2.1.5.51
//! \details SDN.700 INFOSEC attributes (obsolete) suiteAKMandSigCertificate 
static const act::byte cvOID_suiteAKMandSigCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x33};
//! \brief   2.16.840.1.101.2.1.5.52
//! \details SDN.700 INFOSEC attributes (obsolete) suiteAUserSignatureCertificate 
static const act::byte cvOID_suiteAUserSignatureCertificate[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x34};
//! \brief   2.16.840.1.101.2.1.5.53
//! \details SDN.700 INFOSEC attributes prbacInfo 
static const act::byte cvOID_prbacInfo[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x35};
//! \brief   2.16.840.1.101.2.1.5.54
//! \details SDN.700 INFOSEC attributes prbacCAstatic constraints 
static const act::byte cvOID_prbacCAconstraints[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x36};
//! \brief   2.16.840.1.101.2.1.5.55
//! \details SDN.700 INFOSEC attributes sigOrKMPrivileges 
static const act::byte cvOID_sigOrKMPrivileges[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x37};
//! \brief   2.16.840.1.101.2.1.5.56
//! \details SDN.700 INFOSEC attributes commPrivileges 
static const act::byte cvOID_commPrivileges[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x38};
//! \brief   2.16.840.1.101.2.1.5.57
//! \details SDN.700 INFOSEC attributes labeledAttribute 
static const act::byte cvOID_labeledAttribute[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x39};
//! \brief   2.16.840.1.101.2.1.5.58
//! \details SDN.700 INFOSEC attributes (obsolete) policyInformationFile 
static const act::byte cvOID_policyInformationFile[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3A};
//! \brief   2.16.840.1.101.2.1.5.59
//! \details SDN.700 INFOSEC attributes secPolicyInformationFile 
static const act::byte cvOID_secPolicyInformationFile[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3B};
//! \brief   2.16.840.1.101.2.1.5.60
//! \details SDN.700 INFOSEC attributes cAClearancestatic constraint 
static const act::byte cvOID_cAClearanceconstraint[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x05, 0x3C};
//! \brief   2.16.840.1.101.2.1.7.1
//! \details SDN.700 INFOSEC extensions cspExtns 
static const act::byte cvOID_cspExtns[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x07, 0x01};
//! \brief   2.16.840.1.101.2.1.7.1.0
//! \details SDN.700 INFOSEC extensions cspCsExtn 
static const act::byte cvOID_cspCsExtn[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x07, 0x01, 0x00};
//! \brief   2.16.840.1.101.2.1.8.1
//! \details SDN.700 INFOSEC security category mISSISecurityCategories 
static const act::byte cvOID_mISSISecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x08, 0x01};
//! \brief   2.16.840.1.101.2.1.8.2
//! \details SDN.700 INFOSEC security category standardSecurityLabelPrivileges 
static const act::byte cvOID_standardSecurityLabelPrivileges[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x08, 0x02};
//! \brief   2.16.840.1.101.2.1.10.1
//! \details SDN.700 INFOSEC privileges sigPrivileges 
static const act::byte cvOID_sigPrivileges[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x01};
//! \brief   2.16.840.1.101.2.1.10.2
//! \details SDN.700 INFOSEC privileges kmPrivileges 
static const act::byte cvOID_kmPrivileges[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x02};
//! \brief   2.16.840.1.101.2.1.10.3
//! \details SDN.700 INFOSEC privileges namedTagSetPrivilege 
static const act::byte cvOID_namedTagSetPrivilege[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0A, 0x03};
//! \brief   2.16.840.1.101.2.1.11.1
//! \details SDN.700 INFOSEC certificate policy ukDemo 
static const act::byte cvOID_ukDemo[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x01};
//! \brief   2.16.840.1.101.2.1.11.2
//! \details SDN.700 INFOSEC certificate policy usDODClass2 
static const act::byte cvOID_usDODClass2[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x02};
//! \brief   2.16.840.1.101.2.1.11.3
//! \details SDN.700 INFOSEC certificate policy usMediumPilot 
static const act::byte cvOID_usMediumPilot[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x03};
//! \brief   2.16.840.1.101.2.1.11.4
//! \details SDN.700 INFOSEC certificate policy usDODClass4 
static const act::byte cvOID_usDODClass4[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x04};
//! \brief   2.16.840.1.101.2.1.11.5
//! \details SDN.700 INFOSEC certificate policy usDODClass3 
static const act::byte cvOID_usDODClass3[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x05};
//! \brief   2.16.840.1.101.2.1.11.6
//! \details SDN.700 INFOSEC certificate policy usDODClass5 
static const act::byte cvOID_usDODClass5[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0B, 0x06};
//! \brief   2.16.840.1.101.2.1.12.0
//! \details SDN.700 INFOSEC test objects testSecurityPolicy 
static const act::byte cvOID_testSecurityPolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.1
//! \details SDN.700 INFOSEC test objects tsp1 
static const act::byte cvOID_tsp1[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01};
//! \brief   2.16.840.1.101.2.1.12.0.1.0
//! \details SDN.700 INFOSEC test objects tsp1SecurityCategories 
static const act::byte cvOID_tsp1SecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.1.0.0
//! \details SDN.700 INFOSEC test objects tsp1TagSetZero 
static const act::byte cvOID_tsp1TagSetZero[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.1.0.1
//! \details SDN.700 INFOSEC test objects tsp1TagSetOne 
static const act::byte cvOID_tsp1TagSetOne[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x01};
//! \brief   2.16.840.1.101.2.1.12.0.1.0.2
//! \details SDN.700 INFOSEC test objects tsp1TagSetTwo 
static const act::byte cvOID_tsp1TagSetTwo[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x01, 0x00, 0x02};
//! \brief   2.16.840.1.101.2.1.12.0.2
//! \details SDN.700 INFOSEC test objects tsp2 
static const act::byte cvOID_tsp2[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02};
//! \brief   2.16.840.1.101.2.1.12.0.2.0
//! \details SDN.700 INFOSEC test objects tsp2SecurityCategories 
static const act::byte cvOID_tsp2SecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.2.0.0
//! \details SDN.700 INFOSEC test objects tsp2TagSetZero 
static const act::byte cvOID_tsp2TagSetZero[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.2.0.1
//! \details SDN.700 INFOSEC test objects tsp2TagSetOne 
static const act::byte cvOID_tsp2TagSetOne[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x01};
//! \brief   2.16.840.1.101.2.1.12.0.2.0.2
//! \details SDN.700 INFOSEC test objects tsp2TagSetTwo 
static const act::byte cvOID_tsp2TagSetTwo[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x02, 0x00, 0x02};
//! \brief   2.16.840.1.101.2.1.12.0.3
//! \details SDN.700 INFOSEC test objects kafka 
static const act::byte cvOID_kafka[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03};
//! \brief   2.16.840.1.101.2.1.12.0.3.0
//! \details SDN.700 INFOSEC test objects kafkaSecurityCategories 
static const act::byte cvOID_kafkaSecurityCategories[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00};
//! \brief   2.16.840.1.101.2.1.12.0.3.0.1
//! \details SDN.700 INFOSEC test objects kafkaTagSetName1 
static const act::byte cvOID_kafkaTagSetName1[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x01};
//! \brief   2.16.840.1.101.2.1.12.0.3.0.2
//! \details SDN.700 INFOSEC test objects kafkaTagSetName2 
static const act::byte cvOID_kafkaTagSetName2[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x02};
//! \brief   2.16.840.1.101.2.1.12.0.3.0.3
//! \details SDN.700 INFOSEC test objects kafkaTagSetName3 
static const act::byte cvOID_kafkaTagSetName3[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x00, 0x03, 0x00, 0x03};
//! \brief   2.16.840.1.101.2.1.12.1.1
//! \details SDN.700 INFOSEC test objects tcp1 
static const act::byte cvOID_tcp1[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x02, 0x01, 0x0C, 0x01, 0x01};
//! \brief   2.16.840.1.101.3.1
//! \details CSOR GAK slabel 
static const act::byte cvOID_slabel[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x01};
//! \brief   2.16.840.1.101.3.2
//! \details CSOR GAK pki 
static const act::byte cvOID_pki[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02};
//! \brief   2.16.840.1.101.3.2.1
//! \details CSOR GAK policy GAK policyIdentifier 
static const act::byte cvOID_GAK_policyIdentifier[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x01};
//! \brief   2.16.840.1.101.3.2.2
//! \details CSOR GAK extended key usage GAK 
static const act::byte cvOID_GAK[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x02};
//! \brief   2.16.840.1.101.3.2.2.1
//! \details CSOR GAK extended key usage kRAKey 
static const act::byte cvOID_kRAKey[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x02, 0x01};
//! \brief   2.16.840.1.101.3.2.3
//! \details CSOR GAK extensions extensions 
static const act::byte cvOID_extensions[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03};
//! \brief   2.16.840.1.101.3.2.3.1
//! \details CSOR GAK extensions kRTechnique 
static const act::byte cvOID_kRTechnique[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x01};
//! \brief   2.16.840.1.101.3.2.3.2
//! \details CSOR GAK extensions kRecoveryCapable 
static const act::byte cvOID_kRecoveryCapable[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x02};
//! \brief   2.16.840.1.101.3.2.3.3
//! \details CSOR GAK extensions kR 
static const act::byte cvOID_kR[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x03, 0x03};
//! \brief   2.16.840.1.101.3.2.4
//! \details CSOR GAK keyrecoveryschemes 
static const act::byte cvOID_keyrecoveryschemes[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x04};
//! \brief   2.16.840.1.101.3.2.5
//! \details CSOR GAK krapola 
static const act::byte cvOID_krapola[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x02, 0x05};
//! \brief   2.16.840.1.101.3.3
//! \details CSOR GAK arpa 
static const act::byte cvOID_arpa[] = { 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x03};
//! \brief   2.16.840.1.113719.1.9
//! \details Novell pki 
static const act::byte cvOID_pki_Novell[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09};
//! \brief   2.16.840.1.113719.1.9.4
//! \details Novell PKI pkiAttributeType 
static const act::byte cvOID_pkiAttributeType[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04};
//! \brief   2.16.840.1.113719.1.9.4.1
//! \details Novell PKI attribute type registeredAttributes 
static const act::byte cvOID_registeredAttributes[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04, 0x01};
//! \brief   2.16.840.1.113719.1.9.4.2
//! \details Novell PKI attribute type relianceLimit 
static const act::byte cvOID_relianceLimit[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x37, 0x01, 0x09, 0x04, 0x02};
//! \brief   2.16.840.1.113730.1
//! \details Netscape cert-extension 
static const act::byte cvOID_cert_extension[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01};
//! \brief   2.16.840.1.113730.1.1
//! \details Netscape certificate extension netscape-cert-type 
static const act::byte cvOID_netscape_cert_type[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x01};
//! \brief   2.16.840.1.113730.1.2
//! \details Netscape certificate extension netscape-base-url 
static const act::byte cvOID_netscape_base_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x02};
//! \brief   2.16.840.1.113730.1.3
//! \details Netscape certificate extension netscape-revocation-url 
static const act::byte cvOID_netscape_revocation_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x03};
//! \brief   2.16.840.1.113730.1.4
//! \details Netscape certificate extension netscape-ca-revocation-url 
static const act::byte cvOID_netscape_ca_revocation_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x04};
//! \brief   2.16.840.1.113730.1.7
//! \details Netscape certificate extension netscape-cert-renewal-url 
static const act::byte cvOID_netscape_cert_renewal_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x07};
//! \brief   2.16.840.1.113730.1.8
//! \details Netscape certificate extension netscape-ca-policy-url 
static const act::byte cvOID_netscape_ca_policy_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x08};
//! \brief   2.16.840.1.113730.1.9
//! \details Netscape certificate extension HomePage-url 
static const act::byte cvOID_HomePage_url[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x09};
//! \brief   2.16.840.1.113730.1.10
//! \details Netscape certificate extension EntityLogo 
static const act::byte cvOID_EntityLogo[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0A};
//! \brief   2.16.840.1.113730.1.11
//! \details Netscape certificate extension UserPicture 
static const act::byte cvOID_UserPicture[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0B};
//! \brief   2.16.840.1.113730.1.12
//! \details Netscape certificate extension netscape-ssl-server-name 
static const act::byte cvOID_netscape_ssl_server_name[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0C};
//! \brief   2.16.840.1.113730.1.13
//! \details Netscape certificate extension netscape-comment 
static const act::byte cvOID_netscape_comment[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x01, 0x0D};
//! \brief   2.16.840.1.113730.2
//! \details Netscape data-type 
static const act::byte cvOID_data_type[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02};
//! \brief   2.16.840.1.113730.2.1
//! \details Netscape data type dataGIF 
static const act::byte cvOID_dataGIF[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x01};
//! \brief   2.16.840.1.113730.2.2
//! \details Netscape data type dataJPEG 
static const act::byte cvOID_dataJPEG[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x02};
//! \brief   2.16.840.1.113730.2.3
//! \details Netscape data type dataURL 
static const act::byte cvOID_dataURL[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x03};
//! \brief   2.16.840.1.113730.2.4
//! \details Netscape data type dataHTML 
static const act::byte cvOID_dataHTML[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x04};
//! \brief   2.16.840.1.113730.2.5
//! \details Netscape data type certSequence 
static const act::byte cvOID_certSequence[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x05};
//! \brief   2.16.840.1.113730.2.6
//! \details Netscape certificate extension certURL 
static const act::byte cvOID_certURL[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x02, 0x06};
//! \brief   2.16.840.1.113730.3
//! \details Netscape directory 
static const act::byte cvOID_directory[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03};
//! \brief   2.16.840.1.113730.3.1
//! \details Netscape directory ldapDefinitions 
static const act::byte cvOID_ldapDefinitions[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01};
//! \brief   2.16.840.1.113730.3.1.1
//! \details Netscape LDAP definitions carLicense 
static const act::byte cvOID_carLicense[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x01};
//! \brief   2.16.840.1.113730.3.1.2
//! \details Netscape LDAP definitions departmentNumber 
static const act::byte cvOID_departmentNumber[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x02};
//! \brief   2.16.840.1.113730.3.1.3
//! \details Netscape LDAP definitions employeeNumber 
static const act::byte cvOID_employeeNumber[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x03};
//! \brief   2.16.840.1.113730.3.1.4
//! \details Netscape LDAP definitions employeeType 
static const act::byte cvOID_employeeType[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x01, 0x04};
//! \brief   2.16.840.1.113730.3.2.2
//! \details Netscape LDAP definitions inetOrgPerson 
static const act::byte cvOID_inetOrgPerson[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x03, 0x02, 0x02};
//! \brief   2.16.840.1.113730.4.1
//! \details Netscape serverGatedCrypto 
static const act::byte cvOID_serverGatedCrypto_Netscape[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x42, 0x04, 0x01};
//! \brief   2.16.840.1.113733.1.6.3
//! \details Verisign Unknown Verisign extension 
static const act::byte cvOID_Unknown_Verisign_extension_1[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x06, 0x03};
//! \brief   2.16.840.1.113733.1.6.6
//! \details Verisign Unknown Verisign extension 
static const act::byte cvOID_Unknown_Verisign_extension_2[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x06, 0x06};
//! \brief   2.16.840.1.113733.1.7.1.1
//! \details Verisign Verisign certificatePolicy 
static const act::byte cvOID_Verisign_certificatePolicy[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01};
//! \brief   2.16.840.1.113733.1.7.1.1.1
//! \details Verisign Unknown Verisign policy qualifier 
static const act::byte cvOID_Unknown_Verisign_policy_qualifier_1[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01, 0x01};
//! \brief   2.16.840.1.113733.1.7.1.1.2
//! \details Verisign Unknown Verisign policy qualifier 
static const act::byte cvOID_Unknown_Verisign_policy_qualifier_2[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x07, 0x01, 0x01, 0x02};
//! \brief   2.16.840.1.113733.1.8.1
//! \details Verisign Verisign SGC CA? 
static const act::byte cvOID_Verisign_SGC_CA[] = { 0x60, 0x86, 0x48, 0x01, 0x86, 0xF8, 0x45, 0x01, 0x08, 0x01};
//! \brief   2.23.42.0
//! \details SET contentType 
static const act::byte cvOID_contentType_SET[] = { 0x67, 0x2A, 0x00};
//! \brief   2.23.42.0.0
//! \details SET contentType PANData 
static const act::byte cvOID_PANData[] = { 0x67, 0x2A, 0x00, 0x00};
//! \brief   2.23.42.0.1
//! \details SET contentType PANToken 
static const act::byte cvOID_PANToken[] = { 0x67, 0x2A, 0x00, 0x01};
//! \brief   2.23.42.0.2
//! \details SET contentType PANOnly 
static const act::byte cvOID_PANOnly[] = { 0x67, 0x2A, 0x00, 0x02};
//! \brief   2.23.42.1
//! \details SET msgExt 
static const act::byte cvOID_msgExt[] = { 0x67, 0x2A, 0x01};
//! \brief   2.23.42.2
//! \details SET field 
static const act::byte cvOID_field[] = { 0x67, 0x2A, 0x02};
//! \brief   2.23.42.2.0
//! \details SET field fullName 
static const act::byte cvOID_fullName[] = { 0x67, 0x2A, 0x02, 0x00};
//! \brief   2.23.42.2.1
//! \details SET field givenName 
static const act::byte cvOID_givenName_SET[] = { 0x67, 0x2A, 0x02, 0x01};
//! \brief   2.23.42.2.2
//! \details SET field familyName 
static const act::byte cvOID_familyName[] = { 0x67, 0x2A, 0x02, 0x02};
//! \brief   2.23.42.2.3
//! \details SET field birthFamilyName 
static const act::byte cvOID_birthFamilyName[] = { 0x67, 0x2A, 0x02, 0x03};
//! \brief   2.23.42.2.4
//! \details SET field placeName 
static const act::byte cvOID_placeName[] = { 0x67, 0x2A, 0x02, 0x04};
//! \brief   2.23.42.2.5
//! \details SET field identificationNumber 
static const act::byte cvOID_identificationNumber[] = { 0x67, 0x2A, 0x02, 0x05};
//! \brief   2.23.42.2.6
//! \details SET field month 
static const act::byte cvOID_month[] = { 0x67, 0x2A, 0x02, 0x06};
//! \brief   2.23.42.2.7
//! \details SET field date 
static const act::byte cvOID_date[] = { 0x67, 0x2A, 0x02, 0x07};
//! \brief   2.23.42.2.8
//! \details SET field address 
static const act::byte cvOID_address[] = { 0x67, 0x2A, 0x02, 0x08};
//! \brief   2.23.42.2.9
//! \details SET field telephone 
static const act::byte cvOID_telephone[] = { 0x67, 0x2A, 0x02, 0x09};
//! \brief   2.23.42.2.10
//! \details SET field amount 
static const act::byte cvOID_amount[] = { 0x67, 0x2A, 0x02, 0x0A};
//! \brief   2.23.42.2.7.11
//! \details SET field accountNumber 
static const act::byte cvOID_accountNumber[] = { 0x67, 0x2A, 0x02, 0x0B};
//! \brief   2.23.42.2.7.12
//! \details SET field passPhrase 
static const act::byte cvOID_passPhrase[] = { 0x67, 0x2A, 0x02, 0x0C};
//! \brief   2.23.42.3
//! \details SET attribute 
static const act::byte cvOID_attribute_SET[] = { 0x67, 0x2A, 0x03};
//! \brief   2.23.42.3.0
//! \details SET attribute cert 
static const act::byte cvOID_cert_SET[] = { 0x67, 0x2A, 0x03, 0x00};
//! \brief   2.23.42.3.0.0
//! \details SET cert attribute rootKeyThumb 
static const act::byte cvOID_rootKeyThumb[] = { 0x67, 0x2A, 0x03, 0x00, 0x00};
//! \brief   2.23.42.3.0.1
//! \details SET cert attribute additionalPolicy 
static const act::byte cvOID_additionalPolicy[] = { 0x67, 0x2A, 0x03, 0x00, 0x01};
//! \brief   2.23.42.4
//! \details SET algorithm 
static const act::byte cvOID_algorithm_SET[] = { 0x67, 0x2A, 0x04};
//! \brief   2.23.42.5
//! \details SET policy 
static const act::byte cvOID_policy_SET[] = { 0x67, 0x2A, 0x05};
//! \brief   2.23.42.5.0
//! \details SET policy root 
static const act::byte cvOID_root[] = { 0x67, 0x2A, 0x05, 0x00};
//! \brief   2.23.42.6
//! \details SET module 
static const act::byte cvOID_module_SET[] = { 0x67, 0x2A, 0x06};
//! \brief   2.23.42.7
//! \details SET certExt 
static const act::byte cvOID_certExt[] = { 0x67, 0x2A, 0x07};
//! \brief   2.23.42.7.0
//! \details SET cert extension hashedRootKey 
static const act::byte cvOID_hashedRootKey[] = { 0x67, 0x2A, 0x07, 0x00};
//! \brief   2.23.42.7.1
//! \details SET cert extension certificateType 
static const act::byte cvOID_certificateType_SET[] = { 0x67, 0x2A, 0x07, 0x01};
//! \brief   2.23.42.7.2
//! \details SET cert extension merchantData 
static const act::byte cvOID_merchantData[] = { 0x67, 0x2A, 0x07, 0x02};
//! \brief   2.23.42.7.3
//! \details SET cert extension cardCertRequired 
static const act::byte cvOID_cardCertRequired[] = { 0x67, 0x2A, 0x07, 0x03};
//! \brief   2.23.42.7.4
//! \details SET cert extension tunneling 
static const act::byte cvOID_tunneling[] = { 0x67, 0x2A, 0x07, 0x04};
//! \brief   2.23.42.7.5
//! \details SET cert extension setExtensions 
static const act::byte cvOID_setExtensions[] = { 0x67, 0x2A, 0x07, 0x05};
//! \brief   2.23.42.7.6
//! \details SET cert extension setQualifier 
static const act::byte cvOID_setQualifier[] = { 0x67, 0x2A, 0x07, 0x06};
//! \brief   2.23.42.8
//! \details SET brand 
static const act::byte cvOID_brand[] = { 0x67, 0x2A, 0x08};
//! \brief   2.23.42.8.1
//! \details SET brand IATA-ATA 
static const act::byte cvOID_IATA_ATA[] = { 0x67, 0x2A, 0x08, 0x01};
//! \brief   2.23.42.8.4
//! \details SET brand VISA 
static const act::byte cvOID_VISA[] = { 0x67, 0x2A, 0x08, 0x04};
//! \brief   2.23.42.8.5
//! \details SET brand MasterCard 
static const act::byte cvOID_MasterCard[] = { 0x67, 0x2A, 0x08, 0x05};
//! \brief   2.23.42.8.30
//! \details SET brand Diners 
static const act::byte cvOID_Diners[] = { 0x67, 0x2A, 0x08, 0x1E};
//! \brief   2.23.42.8.34
//! \details SET brand AmericanExpress 
static const act::byte cvOID_AmericanExpress[] = { 0x67, 0x2A, 0x08, 0x22};
//! \brief   2.23.42.8.6011
//! \details SET brand Novus 
static const act::byte cvOID_Novus[] = { 0x67, 0x2A, 0x08, 0xAE, 0x7B};
//! \brief   2.23.42.9
//! \details SET vendor 
static const act::byte cvOID_vendor[] = { 0x67, 0x2A, 0x09};
//! \brief   2.23.42.9.0
//! \details SET vendor GlobeSet 
static const act::byte cvOID_GlobeSet[] = { 0x67, 0x2A, 0x09, 0x00};
//! \brief   2.23.42.9.1
//! \details SET vendor IBM 
static const act::byte cvOID_IBM[] = { 0x67, 0x2A, 0x09, 0x01};
//! \brief   2.23.42.9.2
//! \details SET vendor CyberCash 
static const act::byte cvOID_CyberCash[] = { 0x67, 0x2A, 0x09, 0x02};
//! \brief   2.23.42.9.3
//! \details SET vendor Terisa 
static const act::byte cvOID_Terisa[] = { 0x67, 0x2A, 0x09, 0x03};
//! \brief   2.23.42.9.4
//! \details SET vendor RSADSI 
static const act::byte cvOID_RSADSI[] = { 0x67, 0x2A, 0x09, 0x04};
//! \brief   2.23.42.9.5
//! \details SET vendor VeriFone 
static const act::byte cvOID_VeriFone[] = { 0x67, 0x2A, 0x09, 0x05};
//! \brief   2.23.42.9.6
//! \details SET vendor TrinTech 
static const act::byte cvOID_TrinTech[] = { 0x67, 0x2A, 0x09, 0x06};
//! \brief   2.23.42.9.7
//! \details SET vendor BankGate 
static const act::byte cvOID_BankGate[] = { 0x67, 0x2A, 0x09, 0x07};
//! \brief   2.23.42.9.8
//! \details SET vendor GTE 
static const act::byte cvOID_GTE[] = { 0x67, 0x2A, 0x09, 0x08};
//! \brief   2.23.42.9.9
//! \details SET vendor CompuSource 
static const act::byte cvOID_CompuSource[] = { 0x67, 0x2A, 0x09, 0x09};
//! \brief   2.23.42.9.10
//! \details SET vendor Griffin 
static const act::byte cvOID_Griffin[] = { 0x67, 0x2A, 0x09, 0x0A};
//! \brief   2.23.42.9.11
//! \details SET vendor Certicom 
static const act::byte cvOID_Certicom[] = { 0x67, 0x2A, 0x09, 0x0B};
//! \brief   2.23.42.9.12
//! \details SET vendor OSS 
static const act::byte cvOID_OSS[] = { 0x67, 0x2A, 0x09, 0x0C};
//! \brief   2.23.42.9.13
//! \details SET vendor TenthMountain 
static const act::byte cvOID_TenthMountain[] = { 0x67, 0x2A, 0x09, 0x0D};
//! \brief   2.23.42.9.14
//! \details SET vendor Antares 
static const act::byte cvOID_Antares[] = { 0x67, 0x2A, 0x09, 0x0E};
//! \brief   2.23.42.9.15
//! \details SET vendor ECC 
static const act::byte cvOID_ECC[] = { 0x67, 0x2A, 0x09, 0x0F};
//! \brief   2.23.42.9.16
//! \details SET vendor Maithean 
static const act::byte cvOID_Maithean[] = { 0x67, 0x2A, 0x09, 0x10};
//! \brief   2.23.42.9.17
//! \details SET vendor Netscape 
static const act::byte cvOID_Netscape[] = { 0x67, 0x2A, 0x09, 0x11};
//! \brief   2.23.42.9.18
//! \details SET vendor Verisign 
static const act::byte cvOID_Verisign[] = { 0x67, 0x2A, 0x09, 0x12};
//! \brief   2.23.42.9.19
//! \details SET vendor BlueMoney 
static const act::byte cvOID_BlueMoney[] = { 0x67, 0x2A, 0x09, 0x13};
//! \brief   2.23.42.9.20
//! \details SET vendor Lacerte 
static const act::byte cvOID_Lacerte[] = { 0x67, 0x2A, 0x09, 0x14};
//! \brief   2.23.42.9.21
//! \details SET vendor Fujitsu 
static const act::byte cvOID_Fujitsu[] = { 0x67, 0x2A, 0x09, 0x15};
//! \brief   2.23.42.9.22
//! \details SET vendor eLab 
static const act::byte cvOID_eLab[] = { 0x67, 0x2A, 0x09, 0x16};
//! \brief   2.23.42.9.23
//! \details SET vendor Entrust 
static const act::byte cvOID_Entrust[] = { 0x67, 0x2A, 0x09, 0x17};
//! \brief   2.23.42.9.24
//! \details SET vendor VIAnet 
static const act::byte cvOID_VIAnet[] = { 0x67, 0x2A, 0x09, 0x18};
//! \brief   2.23.42.9.25
//! \details SET vendor III 
static const act::byte cvOID_III[] = { 0x67, 0x2A, 0x09, 0x19};
//! \brief   2.23.42.9.26
//! \details SET vendor OpenMarket 
static const act::byte cvOID_OpenMarket[] = { 0x67, 0x2A, 0x09, 0x1A};
//! \brief   2.23.42.9.27
//! \details SET vendor Lexem 
static const act::byte cvOID_Lexem[] = { 0x67, 0x2A, 0x09, 0x1B};
//! \brief   2.23.42.9.28
//! \details SET vendor Intertrader 
static const act::byte cvOID_Intertrader[] = { 0x67, 0x2A, 0x09, 0x1C};
//! \brief   2.23.42.9.29
//! \details SET vendor Persimmon 
static const act::byte cvOID_Persimmon[] = { 0x67, 0x2A, 0x09, 0x1D};
//! \brief   2.23.42.9.30
//! \details SET vendor NABLE 
static const act::byte cvOID_NABLE[] = { 0x67, 0x2A, 0x09, 0x1E};
//! \brief   2.23.42.9.31
//! \details SET vendor espace-net 
static const act::byte cvOID_espace_net[] = { 0x67, 0x2A, 0x09, 0x1F};
//! \brief   2.23.42.9.32
//! \details SET vendor Hitachi 
static const act::byte cvOID_Hitachi[] = { 0x67, 0x2A, 0x09, 0x20};
//! \brief   2.23.42.9.33
//! \details SET vendor Microsoft 
static const act::byte cvOID_Microsoft[] = { 0x67, 0x2A, 0x09, 0x21};
//! \brief   2.23.42.9.34
//! \details SET vendor NEC 
static const act::byte cvOID_NEC[] = { 0x67, 0x2A, 0x09, 0x22};
//! \brief   2.23.42.9.35
//! \details SET vendor Mitsubishi 
static const act::byte cvOID_Mitsubishi[] = { 0x67, 0x2A, 0x09, 0x23};
//! \brief   2.23.42.9.36
//! \details SET vendor NCR 
static const act::byte cvOID_NCR[] = { 0x67, 0x2A, 0x09, 0x24};
//! \brief   2.23.42.9.37
//! \details SET vendor e-COMM 
static const act::byte cvOID_e_COMM[] = { 0x67, 0x2A, 0x09, 0x25};
//! \brief   2.23.42.9.38
//! \details SET vendor Gemplus 
static const act::byte cvOID_Gemplus[] = { 0x67, 0x2A, 0x09, 0x26};
//! \brief   2.23.42.10
//! \details SET national 
static const act::byte cvOID_national[] = { 0x67, 0x2A, 0x0A};
//! \brief   2.23.42.10.192
//! \details SET national Japan 
static const act::byte cvOID_Japan[] = { 0x67, 0x2A, 0x0A, 0x81, 0x40};
//! \brief   2.54.1775.2
//! \details SET. Deprecated, use (2 23 42 7 0) instead hashedRootKey 
static const act::byte cvOID_hashedRootKey_old[] = { 0x86, 0x8D, 0x6F, 0x02};
//! \brief   2.54.1775.3
//! \details SET. Deprecated, use (2 23 42 7 0) instead certificateType 
static const act::byte cvOID_certificateType_old[] = { 0x86, 0x8D, 0x6F, 0x03};
//! \brief   2.54.1775.4
//! \details SET. Deprecated, use (2 23 42 7 0) instead merchantData 
static const act::byte cvOID_merchantData_old[] = { 0x86, 0x8D, 0x6F, 0x04};
//! \brief   2.54.1775.5
//! \details SET. Deprecated, use (2 23 42 7 0) instead cardCertRequired 
static const act::byte cvOID_cardCertRequired_old[] = { 0x86, 0x8D, 0x6F, 0x05};
//! \brief   2.54.1775.6
//! \details SET. Deprecated, use (2 23 42 7 0) instead tunneling 
static const act::byte cvOID_tunneling_old[] = { 0x86, 0x8D, 0x6F, 0x06};
//! \brief   2.54.1775.7
//! \details SET. Deprecated, use (2 23 42 7 0) instead setQualifier 
static const act::byte cvOID_setQualifier_old[] = { 0x86, 0x8D, 0x6F, 0x07};
//! \brief   2.54.1775.99
//! \details SET. Deprecated, use (2 23 42 7 0) instead set-data 
static const act::byte cvOID_set_data_old[] = { 0x86, 0x8D, 0x6F, 0x63};

//! \brief   0.4.0.127.0.7.2.2.4
//! \details TR-03110 PACE
static const act::byte cvOID_pace[] = { 0x00, 0x04, 0x00, 0x7f, 0x00, 0x07, 0x02, 0x02, 0x04};

#if defined(ACT_MSC)
#	pragma warning(pop)
#endif
#endif
