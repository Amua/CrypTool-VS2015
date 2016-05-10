//////////////////////////////////////////////////////////////////////////////////
// Name:      actInit.h
// Product:   cv act library
// Purpose:   initialize the map entries of the objects
//
// Copyright: (c) 2007 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
// remarks:
//			  declare NO_SMARTCARD: no smartcard support required. 
//////////////////////////////////////////////////////////////////////////////////

#ifndef actInit_h
#define actInit_h

#include "actEnv.h"
#include "actKeyKit.h"
#include "actKeyReg.h"
#include "actKeyInfoKit.h"
#include "actKeyInfoReg.h"
#include "actBlockCipherKit.h"
#include "actBlockCipherReg.h"
#include "actBlockCipherModeReg.h"
#include "actBlockCipherModeKit.h"
#include "actStreamCipherKit.h"
#include "actStreamCipherReg.h"
#include "actHashKit.h"
#include "actHashReg.h"
#include "actEMSAReg.h"
#include "actEMSAKit.h"
#include "actDerivatorReg.h"
#include "actDerivatorKit.h"
#include "actPaddingReg.h"
#include "actPaddingKit.h"
#include "actCertificateReg.h"
#include "actCertificateKit.h"
#include "actX509KeyReg.h"
#include "actX509SignReg.h"
#include "actX509SignHashReg.h"
#include "actX509Kit.h"
#include "actDefaultRNG.h"
#include "actRNGKit.h"

#ifndef NO_SMARTCARD
//	NOTE: To Enable support for additional smartcards / profiles define:
#	if 0
#		define ACT_SUPPORT_SIGNTRUST_SC32
#	endif
#	include "actSCardOSReg.h"
#	include "actSCardOSKit.h"
#	include "actSCardTokenReg.h"
#	include "actSCardTokenKit.h"
#	include "actSubsystemReg.h"
#	include "actSubsystemKit.h"
#	include "actSlotMonitorReg.h"
#	include "actSlotMonitorKit.h"
#	include "actTokenConfigReg.h"
#	include "actTokenConfigKit.h"
#	include "actTokenFileCacheReg.h"
#	include "actTokenFileCacheKit.h"
#	include "actTokenExtensionReg.h"
#	include "actTokenExtensionKit.h"
#	include "actTokenInitializerReg.h"
#	include "actTokenInitializerKit.h"
#	include "actTokenAuthProtocolReg.h"
#	include "actTokenAuthProtocolKit.h"
#	include "actJCAppletKit.h"
#	include "actJCAppletReg.h"
#	include "actPKCS15BehaviorReg.h"
#	include "actPKCS15BehaviorKit.h"
#	include "actProfileGeneratorReg.h"
#	include "actProfileGeneratorKit.h"
#endif // NO_SMARTCARD

#if defined(ACT_WIN32) \
&& !defined(ACT_MINGW) \
&& !defined(ACT_IOS)
#	define  ACT_INIT_MS_CAPI
#endif

namespace act
{
	// ------------------------------------------------------------------------
	const KeyMapEntry KeyMap[] =
	{
		{ "BlockCipher",					CreateBlockCipherKey	},
		{ "StreamCipher",					CreateStreamCipherKey	},

		{ "IES",							CreateIESKey			},
		{ "DSA",							CreateDSAKey			},
		{ "RSA",							CreateRSAKey			},
		{ "ECDSA",							CreateECDSAKey			},
		{ "ECGDSA",							CreateECGDSAKey			},

		{ "DH",								CreateDHKey				},
		{ "ECDH",							CreateECDHKey			},

		{ "HashMAC",						CreateHashMACKey		},
		{ "CBCMAC",							CreateCBCMACKey			},
		{ "SecretKeyMAC",					CreateSecretKeyMACKey	},
		{ "RetailCFBMAC",					CreateRetailCFBMACKey	},
		{ "iMAC3",							Create_iMAC3Key			},	//!< ISO9797-1 M2 Alg 3 MAC8
		{ "CMAC",							CreateCMACKey			},	//!< NIST 800-38B CMAC
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const KeyInfoMapEntry KeyInfoMap[] =
	{
		{ "PKCS8",							CreatePKCS8				},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const BlockCipherMapEntry BlockCipherMap[] = 
	{
		{ "AES",							CreateRijndael			},
		{ "DES",							CreateDES				},	//!< StarCOS 3.x needs it to encrypt the PIN
		{ "TripleDES",						CreateTripleDES			},
		{ "CAST128",						CreateCAST128			},
		{ "BlowFish",						CreateBlowFish			},
		{ "Mars",							CreateMars				},
		{ "Serpent",						CreateSerpent			},
		{ "Rijndael",						CreateRijndael			},
		{ "TwoFish",						CreateTwoFish			},
		{ "RC2",							CreateRC2				},
		//{ "RC6",							CreateRC6				},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const BlockCipherModeMapEntry BlockCipherModeMap[] = 
	{
		{ "ECB",							CreateECBMode			},	//!< StarCOS 3.x needs it to encrypt the PIN
		{ "CBC",							CreateCBCMode			},	//!< SwissSign PZ2007 SM
		{ "CFB",							CreateCFBMode			},
		{ "OFB",							CreateOFBMode			},
		{ "CTR",							CreateCTRMode			},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const StreamCipherMapEntry StreamCipherMap[] = 
	{
		{ "ARC4",							CreateARC4				},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const HashMapEntry HashMap[] = 
	{
		{ "MD2",							CreateMD2				},
		{ "MD4",							CreateMD4				},
		{ "MD5",							CreateMD5				},
		{ "RIPEMD128",						CreateRipemd128			},
		{ "RIPEMD160",						CreateRipemd160			},
		// { "SHA0",						CreateSHA0				},	//!< deprecated
		{ "SHA1",							CreateSHA1				},	//!< Needed by Certificate Details: Fingerprint(SHA1)
		{ "SHA224",							CreateSHA224			},
		{ "SHA256",							CreateSHA256			},	//!< Needed for seed polling of any PRNG
		{ "SHA384",							CreateSHA384			},
		{ "SHA512",							CreateSHA512			},
		{ "DummyHash",						CreateDummyHash			},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const EMSAMapEntry EMSAMap[] = 
	{
		{ "DummyEMSA",						CreateDummyEMSA			},	//!< Used for "Hash on Card"
		{ "EMSA1",							CreateEMSA1				},
		{ "PKCS1V1_5EMSA",					CreatePKCS1V1_5EMSA		},
		{ "TLS_EMSA",						CreateTLS_EMSA			},
		{ "PKCS1_PSS_EMSA",					CreatePKCS1_PSS_EMSA	},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const DerivatorMapEntry DerivatorMap[] = 
	{
		{ "KDF1",							CreateKDF1				},	//!< IEEE P1363 KDF1
		{ "KDF2",							CreateX963KDF			},	//!< IEEE P1363 KDF2 (= X963KDF)
		{ "X963KDF",						CreateX963KDF			},	//!< ANSI X9.63 KDF
		{ "TLS1PRF",						CreateTLS1PRF			},	//!< RFC-5246 and RFC-4346 TLS PRF
		{ "PBKDF1",							CreatePBKDF1			},	//!< PKCS#5 PBKDF1
		{ "PBKDF2",							CreatePBKDF2			},	//!< PKCS#5 PBKDF2
		{ "EACKDF",							CreateEACKDF			},	//!< EAC 2.01, BSI TR-03110 A.2.3
		{ "SessionKDF",						CreateEACKDF			},	//!< BSI TR-03111 (= EACKDF)
		{ "NIST_SP800_108KDF",				CreateNIST_SP800_108KDF	},	//!< Counter Mode (GP SCP 03 mode)
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const PaddingMapEntry PaddingMap[] = 
	{
		{ "PKCS5",							CreatePKCS5Pad			},
		{ "RSAES",							CreatePKCS1V1_5EMEPad	},	//!< Required, default
		{ "OAEP", CreatePKCS1_OAEP									},
		{ "ISO",							CreateOneAndZerosPad	},	//!< EAC 2.01 - PACE, TA, CA requirements
		{ "ISO9796", CreateISO9796Pad								},
		{ "NOPAD",							CreateNoPad				},	//!< Required, default
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const CertificateMapEntry CertificateMap[] = 
	{
		{ "X509",							CreateX509Certificate	},
		{ "CV",								CreateCVCertificate		},	//!< EAC 2.01 - TA, CA requirements
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const CRLMapEntry CRLMap[] = 
	{
		{ "X509",							CreateX509CRL			},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509KeyMapEntry X509KeyMap[] =
	{
		{ "1.2.840.113549.1.1.1",	CreateRSAKey,	X509ToRSA,		RSAToX509	},	//!< rsaEncryption
		{ "1.2.840.113549.1.1.7",	CreateRSAKey,	X509ToRSA,		RSAToX509	},	//!< id-RSAES-OAEP
		{ "1.2.840.113549.1.1.10",	CreateRSAKey,	X509ToRSA,		RSAToX509	},	//!< id-RSASSA-PSS
		{ "2.5.8.1.1",				CreateRSAKey,	X509ToRSA,		RSAToX509	},	//!< id-ea-rsa 
		{ "1.2.840.10040.4.1",		CreateDSAKey,	X509ToDSA,		DSAToX509	},
		{ "1.3.14.3.2.20",			CreateDSAKey,	X509ToDSA,		DSAToX509	},
		{ "1.3.14.3.2.12",			CreateDSAKey,	X509ToDSA,		DSAToX509	},	//!< secude DSA oid
		{ "1.2.840.10046.2.1",		CreateDHKey,	X509ToDH,		DHToX509	},
		{ "1.2.840.10045.2.1",		CreateECDSAKey,	X509ToECDSA,	ECDSAToX509 },
		{ "1.2.840.10045.2.1",		CreateECDHKey,	X509ToECDSA,	ECDSAToX509 },	//!< Workaround for ECDHKey to OID mapping
		{ 0, 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509SignMapEntry X509SignMap[] =
	{
		{ CreateRSAKey,		RSAGetAlgID,	RSASetAlgID		},
		{ CreateDSAKey,		DSAGetAlgID,	DSASetAlgID		},
		{ CreateECDSAKey,	ECDSAGetAlgID,	ECDSASetAlgID	},
		{ CreateDHKey,		DHGetAlgID,		DHSetAlgID		},
		{ CreateECDHKey,	ECDHGetAlgID,	ECDHSetAlgID	},
		{ 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509SignHashMapEntry X509SignHashMap[] =
	{
		// RSA
		{ "1.2.840.113549.1.1.2",	"MD2",			"RSA"	},			//!< md2WithRSAEncryption
		{ "1.2.840.113549.1.1.3",	"MD4",			"RSA"	},			//!< md4WithRSAEncryption
		{ "1.2.840.113549.1.1.4",	"MD5",			"RSA"	},			//!< md5WithRSAEncryption
		{ "1.2.840.113549.1.1.5",	"SHA1",			"RSA"	},			//!< shaWithRSAEncryption
		{ "1.3.14.3.2.29",			"SHA1",			"RSA"	},
		{ "1.2.840.113549.1.1.11",	"SHA256",		"RSA"	},			//!< sha256WithRSAEncryption
		{ "1.2.840.113549.1.1.12",	"SHA384",		"RSA"	},			//!< sha384WithRSAEncryption
		{ "1.2.840.113549.1.1.13",	"SHA512",		"RSA"	},			//!< sha512WithRSAEncryption
		{ "1.2.840.113549.1.1.14",	"SHA224",		"RSA"	},			//!< sha224WithRSAEncryption
		{ "1.3.36.3.3.1.2",			"RIPEMD160",	"RSA"	},
		{ "1.3.36.3.3.1.3",			"RIPEMD128",	"RSA"	},
		// DSA
		{ "1.2.840.10040.4.3",		"SHA1",			"DSA"	},
		{ "1.3.14.3.2.28",			"SHA1",			"DSA"	},
		{ "1.3.14.3.2.27",			"SHA1",			"DSA"	},			//!< secude DSA oid
		{ "2.16.840.1.101.3.4.3.1",	"SHA224",		"DSA"	},			//!< dsa-with-sha224
		{ "2.16.840.1.101.3.4.3.2",	"SHA256",		"DSA"	},			//!< dsa-with-sha256
		// ECDSA
		{ "1.2.840.10045.4.1",		"SHA1",			"ECDSA"	},			//!< ecdsa-with-Sha1
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDSA"	},			//!< ecdsa-with-Sha1 (deprecated)
		{ "1.2.840.10045.4.3.1",	"SHA224",		"ECDSA"	},			//!< ecdsa-with-Sha224
		{ "1.2.840.10045.4.3.2",	"SHA256",		"ECDSA"	},			//!< ecdsa-with-Sha256
		{ "1.2.840.10045.4.3.3",	"SHA384",		"ECDSA"	},			//!< ecdsa-with-Sha384
		{ "1.2.840.10045.4.3.4",	"SHA512",		"ECDSA"	},			//!< ecdsa-with-Sha512

		{ "0.4.0.127.0.7.4.1.1",	"SHA1",			"ECDSA"	},			//!< BSI
		{ "0.4.0.127.0.7.4.1.2",	"SHA224",		"ECDSA"	},
		{ "0.4.0.127.0.7.4.1.3",	"SHA256",		"ECDSA"	},
		{ "0.4.0.127.0.7.4.1.4",	"SHA384",		"ECDSA"	},
		{ "0.4.0.127.0.7.4.1.5",	"SHA512",		"ECDSA"	},
		// DH
		{ "1.3.6.1.5.5.7.6.4",		"SHA1",			"DH"	},			//!< DH-POP
		// ECDH
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDH"	},			//!< "ECDH-POP"
		{ 0, 0, 0 }
	};

#ifndef NO_SMARTCARD
	// ------------------------------------------------------------------------
	//! /note Only lower case historical bytes !
	const SCardOSMapEntry SCardOSMap[] = 
	{
		/*
		{ "0064050a020131809000",			CreateTCOS             },	//!< NetKey (TCOS V2R1)
		{ "00640560020331809000",			CreateTCOS             },	//!< NetKey (TCOS V2R3)
		{ "0064057b020331809000",			CreateTCOS             },	//!< NetKey (TCOS V2R?)
		{ "00640514020231809000",			CreateTCOS             },	//!< etrust (TCOS V2R2)
		{ "00640561020331809000",			CreateTCOS             },	//!< TCOS USB Crypt Token
		{ "0068d276000028ff051e3180009000", CreateMicardOS         },	//!< Micardo P2.1
		{ "4d4943323045",					CreateMicardo20E       },	//!< Micardo EC 2.0
		{ "0068d276000028ff05233180009000",	CreateMicardo23E       },	//!< Micardo EC 2.3
		*/

		// ACOS
		{ "454d56203033202006",				CreateACOS_D01         },	//!< Austria Card ACOS EMV-D01
		{ "44492030324d",					CreateACOS_D01         },	//!< Austria Card ACOS EMV-D01 contactless
		{ "455041000000000228505900000000",	CreateACOS_A04         },	//!< Austria Card ACOS EMV-A04/A05
		{ "455041000000000000000000000000",	CreateACOS_A04         },	//!< Austria Card ACOS EMV-A04/A05

		// CardOS
		{ "c802",							CreateCardOS_M4        },	//!< CardOS M4.0     siemens profile
		{ "c803",							CreateCardOS_M4        },	//!< CardOS M4.01    siemens profile
		{ "c804",							CreateCardOS_M4        },	//!< CardOS M4.01a   siemens profile
		{ "4d346376",						CreateCardOS_M4        },	//!< CardOS M4.01(a)      cv profile
		{ "4d3463765f4d",					CreateCardOS_M4_MoC    },	//!< CardOS M4.01_M       cv profile
		{ "4d3463765f45",					CreateCardOS_M4_ECC    },	//!< CardOS M4.01_E       cv profile
		{ "c806",							CreateCardOS_V4        },	//!< CardOS V4.2
		{ "c807",							CreateCardOS_V4        },	//!< CardOS V4.3
		{ "c808",							CreateCardOS_V4        },	//!< CardOS V4.3B
		{ "c809",							CreateCardOS_V4        },	//!< CardOS V4.2B
		{ "c80a",							CreateCardOS_V4        },	//!< CardOS V4.2B DI
		{ "0000c80a3381b100",				CreateCardOS_V4        },	//!< CardOS V4.2B DI contactless
		{ "c80b",							CreateCardOS_V4        },	//!< CardOS V4.2C
		{ "c80d",							CreateCardOS_V4        },	//!< CardOS V4.4
		{ "c901",							CreateCardOS_V4        },	//!< CardOS V5.0
		{ "c902",							CreateCardOS_V4        },	//!< CardOS V5.3 DI
		{ "c903",							CreateCardOS_V4        },	//!< CardOS V5.3
		{ "56346376",						CreateCardOS_V4        },	//!< CardOS V4.2/4.3/4.3B cv profile
		{ "563432626376",					CreateCardOS_V4        },	//!< CardOS V4.2b         cv profile
		{ "5634326244496376",				CreateCardOS_V4        },	//!< CardOS V4.2b DI      cv profile
		{ "563432636376",					CreateCardOS_V4        },	//!< CardOS V4.2c         cv profile
		{ "5634346376",						CreateCardOS_V4        },	//!< CardOS V4.4          cv profile
		{ "5635306376",						CreateCardOS_V4        },	//!< CardOS V4.4          cv profile
		{ "563463765f45",					CreateCardOS_V4_ECC    },	//!< CardOS V4.3B ECC     cv profile
		{ "006b0508c806012101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.2         CNS profile, 2004.02.20
		{ "006b0508c807012101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.3         CNS profile, 2004.02.20
		{ "006b0508c808012101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.3B        CNS profile, 2004.02.20
		{ "006b0508c806011101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.2         CNS profile, 2005.03.11
		{ "006b0508c807011101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.3         CNS profile, 2005.03.11
		{ "006b0508c808011101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.3B        CNS profile, 2005.03.11
		{ "006b0508c808011101434e53103180",	CreateCardOS_V4        },	//!< CardOS V4.3B        CNS profile, 2005.03.11
		{ "4b53776973735369676e",			CreateCardOS_V4        },	//!< CardOS V4.3B/V4.4   ATR by SwissSign

		// STARCOS
		{ "53504b32339000",					CreateStarCOS_2_3      },	//!< G&D STARCOS SPK 2.3
		{ "53504b32349000",					CreateStarCOS_2_4      },	//!< G&D STARCOS SPK 2.4
		{ "80670412b0030300008101",			CreateStarCOS_3_0      },	//!< G&D STARCOS 3.0 (creational state)
		{ "80670412b0030300008105",			CreateStarCOS_3_0      },	//!< G&D STARCOS 3.0
		{ "80670412b003030000",				CreateStarCOS_3_0      },	//!< G&D STARCOS 3.0 contactless
		{ "80655343010d067394211b8101",		CreateStarCOS_3_1      },	//!< G&D STARCOS 3.1 (creational state)
		{ "80655343010d067394211b8105",		CreateStarCOS_3_1      },	//!< G&D STARCOS 3.1
		{ "0064051eb20031b0739621db019000",	CreateStarCOS_3_2      },	//!< G&D STARCOS 3.2 (creational state)
		{ "0064051eb20031b0739621db059000",	CreateStarCOS_3_2      },	//!< G&D STARCOS 3.2
		{ "8067041bb42a000a028101",			CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4 (creational state)
		{ "8067041bb42a000a028105",			CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4
		{ "8031b052010364041bb4228105",		CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4 (HBA G1, Version 2.3.2)
		{ "8031b052010364041bb4228101",		CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4 (HBA G1, Version 2.3.2, creational state)
		{ "80670534b50201c0a18101",			CreateStarCOS_3_5      },	//!< G&D STARCOS 3.5 (creational state)
		{ "80670534b50201c0a18105",			CreateStarCOS_3_5      },	//!< G&D STARCOS 3.5

		{ "8064041bb42a8105",				CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4 (Health Card), VKplus 2010/12
		{ "8067041bb42200c0818105",			CreateStarCOS_3_4      },	//!< G&D STARCOS 3.4 (Health Card), VKplus 2012 (test card 1)
		   
		{ "8064041ab4038105",				CreateStarCOS_3_4      },	//!< D-TRUST multicard advanced 3.x 

		// SECCOS (NOTE: used for sc/i card registry mapping)
		{ "6563110c5302500010ab0b21230650",	CreateSECCOS_6         },	//!< SECCOS 6
		{ "8031c073d621c0",					CreateSECCOS_6         },	//!< SECCOS 6 contactless 

		// TCOS
		{ "00640411030131c073f701d0009000",	CreateTCOS_3_0_1       },	//!< TCOS 3.0 R1 NetKey 3.0
		{ "00640428030231c073f701d0009000",	CreateTCOS_3_0_2       },	//!< TCOS 3.0 R2 IDKey
		{ "006404280302009000",	            CreateTCOS_3_0_2       },	//!< TCOS 3.0 R2 IDKey contactless ATS
		{ "006405a0030431c073f701d0009000", CreateTCOS_3_0_4       },	//!< TCOS 3.0 R4 Signature Card Version 2.0 R1 NetKey
//		{ "304c47127783d500",               CreateTCOS_3_0_4       },	//!< TCOS 3.0 R4 Signature Card Version 2.0 R1 NetKey contactless ATQB

		// JavaCards
		{ "8073002113574a544861314a00",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg1)
		{ "8073002113574a544861314700",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg2)
		{ "8073002113574a544861314800",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg3)
		{ "8073002113574a544861314b00",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg4)
		{ "8073002113574a544861314c00",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg5)
		{ "8073002113574a544861314900",		CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (cfg8)
		{ "404d4f504153530000000000000000",	CreateJavaCardOS_2_2   },	//!< G&D SmartCafe Expert 64  (XMC2)

		{ "534653452d43583332322d56180308", CreateJavaCardOS_2_1_1 },	//!< G&D SmartCafe Expert 2.0
		{ "0073c84013009000",				CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.0 / 3.1 / 3.1 contactless
		{ "4138004133b1020073c840130090",	CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.1 contactless (SCM SDI010, Firmware V6.28)
		{ "4138004133b10073c84013009000",	CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.1 contactless (SCM SDI010, Firmware V6.32)
		{ "73667465206364313434",			CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 PIV 144 KB
		{ "736674652D6364303830",			CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 PIV 80 KB
		{ "73667465",						CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 (sfte)
		{ "736674652d6e66",					CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 (sfte-nf)
		{ "73c840130090009b",				CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 USB Token
		{ "736674652063643038302d6e66",		CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 (sfte cd080-nf)
		{ "736674652063643134342d6e66",		CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 3.2 (sfte cd144-nf)
		{ "53462d3443432d3031",				CreateJavaCardOS_2_2_1 },	//!< G&D SmartCafe Expert 5.0
		{ "53434536302d43443038312d46",		CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CD081-F)
		{ "53434536302d43433038312d46",		CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CC081-F)
		{ "53434536302d43443038312d6e46",	CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CD081-nF)
		{ "53434536302d43433038312d6e46",	CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CC081-nF)
		{ "53434536302d43443134352d46",		CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CD145-F)
		{ "53434536302d43433134352d46",		CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CC145-F)
		{ "53434536302d43443134352d6e46",	CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CD145-nF)
		{ "53434536302d43433134352d6e46",	CreateJavaCardOS_3_0_1 },	//!< G&D SmartCafe Expert 6.0 (SCE60-CC145-nF)
		{ "53504b323544499000",				CreateJavaCardOS_2_2_1 },	//!< G&D Mobile Security Card 3.x
		{ "4d5343",							CreateJavaCardOS_2_2_1 },	//!< G&D Mobile Security Card 3.x

		{ "43475346533032",					CreateJavaCardOS_2_2_2 },	//!< certgate microSD (G&D SmartCafe Expert 5.0)
		{ "ff2750483230530000000000000000", CreateJavaCardOS_2_2_2 },	//!< certgate microSD (G&D SmartCafe Expert 5.0) contactless

		//{ "4a434f503230",					CreateJavaCardOS_2_1   },	//!< JCOP 20
		{ "4a434f503231563232",				CreateJavaCardOS_2_2_1 },	//!< JCOP 21 V2.2
		{ "4a434f50323156323331",			CreateJavaCardOS_2_2_1 },	//!< JCOP 21 V2.3.1
		{ "4a434f50323156323431",			CreateJavaCardOS_2_2_2 },	//!< JCOP 21 V2.4.1
		{ "4a434f503331563231",				CreateJavaCardOS_2_1   },	//!< JCOP 31 V2.1
		{ "4a434f503331563232",				CreateJavaCardOS_2_2_1 },	//!< JCOP 31 V2.2
		{ "4a434f50333156323331",			CreateJavaCardOS_2_2_1 },	//!< JCOP 31 V2.3.1
		{ "4a434f503331563234",				CreateJavaCardOS_2_2_1 },	//!< JCOP 31 V2.4
		{ "4a434f50333156323431",			CreateJavaCardOS_2_2_2 },	//!< JCOP 31 V2.4.1
		//{ "4a434f5033313336474454",		CreateJavaCardOS_2_2_1 },	//!< JCOP 31 36GDT
		{ "4a434f503431563232",				CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.2 / V2.2 contactless
		{ "4128001133b04a434f5034315632",	CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.2 contactless (SCM SDI010, Firmware V6.32)
		{ "4a434f50343156323231",			CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.2.1
		{ "4138001133b04a434f5034315632",	CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.2.1 contactless
		{ "4a434f50343156323331",			CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.3.1
		{ "4a434f50343156323332",			CreateJavaCardOS_2_1_1 },	//!< JCOP 41 V2.3.2
		{ "4a434f503431563234",				CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.4
		{ "4a434f50343156323431",			CreateJavaCardOS_2_2_2 },	//!< JCOP 41 V2.4.1
		{ "434f50343156323231ff",			CreateJavaCardOS_2_2_1 },	//!< JCOP 41 V2.2.1 (IDptoken 200)

		{ "4a434f50563231",					CreateJavaCardOS_2_1   },	//!< JCOP V2.1
		{ "4a434f50563232",					CreateJavaCardOS_2_2_1 },	//!< JCOP V2.2
		{ "4a434f5056323231",				CreateJavaCardOS_2_2_1 },	//!< JCOP V2.2.1
		{ "4a434f50563233",					CreateJavaCardOS_2_2_1 },	//!< JCOP V2.3
		{ "4a434f5056323331",				CreateJavaCardOS_2_2_1 },	//!< JCOP V2.3.1
		{ "4a434f5056323332",				CreateJavaCardOS_2_1_1 },	//!< JCOP V2.3.2
		{ "0073c84000009000",				CreateJavaCardOS_2_1_1 },	//!< JCOP V2.3.2
		{ "4a434f50563234",					CreateJavaCardOS_2_2_1 },	//!< JCOP V2.4
		{ "4a434f5056323431",				CreateJavaCardOS_2_2_2 },	//!< JCOP V2.4.1
		{ "4a434f5076323431",				CreateJavaCardOS_2_2_2 },	//!< JCOP v2.4.1 (yes, lowercase 'v')
		{ "4a434f5056323432",				CreateJavaCardOS_2_2_2 },	//!< JCOP V2.4.2
		{ "4a434f507632343262657461",		CreateJavaCardOS_2_2_2 },	//!< JCOP v2.4.2 beta (2.4.1+)
		{ "4a434f50763234325231",			CreateJavaCardOS_3_0_1 },	//!< JCOP v2.4.2 R1
		{ "4a434f503234325232",				CreateJavaCardOS_3_0_1 },	//!< JCOP v2.4.2 R2
		{ "4a434f503234325233",				CreateJavaCardOS_3_0_1 },	//!< JCOP v2.4.2 R3

		// ePasslet-Suite
		{ "4356455053313031",				CreateJavaCardOS_2_2_2 },	//!< 4RDE1 JCOP 2.4.1
		{ "0031c173c84000009000",			CreateJavaCardOS_2_2_2 },	//!< 4RDE0 MChip/4 (T1)
		{ "0031c173c84040009000",			CreateJavaCardOS_2_2_2 },	//!< 4RDE0 MChip/4 (T1, extended length)
		{ "4244522d476f4944436172642d7631",	CreateJavaCardOS_3_0_1 },	//!< BDR-GoIDCard-v1 auf ePS-2.1

		// OEM customer
		{ "44657861204346207631",			CreateJavaCardOS_2_2_2 },	//!< Dexa CF v1 (JCOP V2.4.1)
		{ "454f4e436172645631",				CreateJavaCardOS_2_2_2 },	//!< EONCardV1 (JCOP V2.4.1)
		{ "454f4e436172645632",				CreateJavaCardOS_2_2_2 },	//!< EONCardV2 (JCOP V2.4.1 R3)
		{ "4148432076312e30",				CreateJavaCardOS_2_2_2 },	//!< AHC v1.0 (JCOP V2.4.1)
		{ "597562696b65794e454f7233",		CreateJavaCardOS_3_0_1 },	//!< YubikeyNEOr3 (JCOP V2.4.2 R2)
		{ "597562696b65794e454f",			CreateJavaCardOS_3_0_1 },	//!< YubikeyNEO OTP+CCID (JCOP V2.4.2 R2)
		{ "5a018048494443313158587300011b",	CreateJavaCardOS_2_2_1 },	//!< HID Crescendo iCLASS Px G8H, JCOP V2.4.1

		{ "4a434f5033314d34",				CreateJavaCardOS_2_2_1 },	//!< Austriacard JCOP31M4
		{ "4a434f5032315632325f",			CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP 21 V2.2, T0, T1
		{ "4a434f5033315632325f",			CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP 31 V2.2, T0, T1
		{ "4a434f5034315632345f",			CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP 41 V2.4, T0, T1
		{ "4a434f50563234314143",			CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP V2.4.1,  T0, T1
		
		{ "5257414e44415f4944",				CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP V2.4.1 'RWANDA_ID'
		{ "44654c61527565",					CreateJavaCardOS_2_2_1 },	//!< AustriaCard JCOP V2.4.1 'DeLaRue'

		// Infineon (NOTE: used for sc/i card registry mapping, atr mask detection below)
		{ "803180664090a5102e1083019000",	CreateJavaCardOS_3_0_4 },	//!< Infineon SLJ 52GDL 150CL
		{ "534c4a35324778787979797a52",		CreateJavaCardOS_3_0_4 },	//!< Infineon SLJ 52GDL 128
		{ "0000001177818300",				CreateJavaCardOS_3_0_4 },	//!< Infineon SLJ 52GDL 128 contactless
		{ "803180664090a4561b1183019000",	CreateJavaCardOS_2_2_1 },	//!< Infineon JCLX80 jTOP 20ID vX
		{ "000000007783b300",				CreateJavaCardOS_2_2_1 },	//!< Infineon jTOP contactless (JCLX80, SLJ 52GDL, may be others)

		// Infineon CV-ATR
		{ "8031cd664090a5102ee08101",		CreateJavaCardOS_3_0_4 },	//!< Infineon SLJ 52GDL 160CL (OCD)
		{ "8031cd664090a5102e108101",		CreateJavaCardOS_3_0_4 },	//!< Infineon SLJ 52GDL 150CL
		
		{ "80318065b0831148c883009000",		CreateJavaCardOS_2_2_1 },	//!< Gemalto TOP IM GX4
		//{ "80318065b08301029083009000",	CreateJavaCardOS_2_2_1 },	//!< Gemalto I-DENTITY CARD
		{ "8065b08301017483009000",			CreateJavaCardOS_2_1_1 },	//!< Gemplus GemXpresso Pro R3
		{ "8065b08301037483009000",			CreateJavaCardOS_2_1_1 },	//!< Gemplus GemXpresso Pro R3
		//{ "8065a20101013d72d643",			CreateJavaCardOS_2_1_1 },	//!< Gemplus GemXpresso Pro R3 E32 PK

		{ "0031c06477e30300829000",			CreateJavaCardOS_2_1_1 },	//!< Oberthur CosmopolIC 64K v5.2D

		{ "8059017f4849444a43327300011b",	CreateJavaCardOS_2_2_2 },	//!< HID Crescendo C700 (JC2s) ("Standard JavaCard, T0/1, Platform Default Packages")
		{ "804f0ca0000003060a001d00000000", CreateJavaCardOS_2_2_2 },	//!< HID Crescendo C700 (JC2s) contactless

		{ ACT_ISO7816OS_NAME,				CreateISO7816OS        },	//!< use ISO7816OS as fallback
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardOSAtrMaskEntry SCardOSAtrMaskMap[] =
	{
		{	// certgate microSD V2 2048MB Sm@rtcafe Expert v5.0 Rev1 BB
			_H("\x3b\x0f\xff\x27\x50\x48\x32\x30\x53\x46\x53\x10\x00\x00\x00\x00\x00"),
			_H("\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// certgate microSD V2 2048MB Sm@rtcafe Expert v5.0 Rev1 BB-ISO14443
			_H("\x3b\x8f\x80\x01\xff\x27\x50\x48\x32\x30\x53\x46\x53\x10\x00\x00\x00\x00\x00\x00"),
			_H("\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// certgate Smartcafe Expert 5.0 NFC
			_H("\x3b\x8f\x80\x01\xff\x27\x50\x48\x32\x30\x53\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
			_H("\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// G&D SmartCafe Expert 7.0
			_H("\x3b\xf9\x00\x00\x00\x80\x31\xfe\x45\x53\x43\x45\x37\x00\x00\x00\x00\x00\x00"),
			_H("\xff\xff\x00\xff\x00\xf0\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00"),
			CreateJavaCardOS_3_0_4
		},
		{	// G&D SmartCafe Expert 7.0 contactless
			_H("\x3b\x89\x80\x01\x53\x43\x45\x37\x00\x00\x00\x00\x00\x00"),
			_H("\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00"),
			CreateJavaCardOS_3_0_4
		},
		{	// Infineon SLJ 52GDL 150CL
			_H("\x3b\xfe\x00\x00\x00\x80\x31\xfe\x45\x80\x31\x80\x66\x40\x90\xa5\x10\x00\x00\x83\x01\x90\x00\x00"),
			_H("\xff\xff\x00\xff\x00\xf0\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff\x00"),
			CreateJavaCardOS_3_0_4
		},
		{	// Infineon SLJ 52GDL 160CL (T = 0)
			_H("\x3b\x7e\x00\x00\x00\x80\x31\x80\x66\x40\x90\xa5\x10\x00\x00\x83\x01\x90\x00"),
			_H("\xff\xff\x00\xff\x00\xf0\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff"),
			CreateJavaCardOS_3_0_4
		},
		{	// Infineon JCLX80 jTOP 20ID
			_H("\x3b\xfe\x00\x00\x00\x80\x31\xfe\x45\x80\x31\x80\x66\x40\x90\xa4\x56\x00\x00\x83\x01\x90\x00\x00"),
			_H("\xff\xff\x00\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// Infineon JCLX80 jTOP 20ID v2
			_H("\x3b\xfe\x00\x00\x00\x80\x31\xfe\x45\x80\x31\x80\x66\x40\x90\xa4\x16\x00\x00\x83\x01\x90\x00\x00"),
			_H("\xff\xff\x00\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// Infineon JCLX80 jTOP 20ID v3
			_H("\x3b\xfe\x00\x00\x00\x80\x31\xfe\x45\x80\x31\x80\x66\x40\x90\xa2\x16\x00\x00\x83\x01\x90\x00\x00"),
			_H("\xff\xff\x00\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	// Infineon JCLX80 jTOP 20ID v3 contactless
			_H("\x3b\x8e\x00\x01\x80\x31\x80\x66\x40\x90\xa2\x16\x00\x00\x83\x01\x90\x00\x00"),
			_H("\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\xff\xff\xff\xff\x00"),
			CreateJavaCardOS_2_2_1
		},
		{	_H(""), _H(""), 0
		},
	};

	// ------------------------------------------------------------------------
	const SCardOSFactoryEntry SCardOSMapEx[] = 
	{
		{ DetectSECCOS_6,						CreateSECCOS_6				},
		{ DetectSECCOS_5,						CreateSECCOS_5				},
		{ DetectCVEPS,							CreateCVEPS					},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardOSDerivationMapEntry SCardOSDerivationMap[] =
	{
		{ "JCOSECC",							DeriveJavaCardOS_ECC		},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardTokenMapEntry SCardTokenMap[] = 
	{
		// EF.DIR based tokens ALWAYS first!
		{ IsMDPACEToken,						CreateMDPACEToken			},	//!< PACE (MDMF)
		{ IsEBAProfile,							CreateEBAToken				},	//!< Budru eBA
		{ IsEPAProfile,							CreateEPAToken				},	//!< Passport

		// PKCS#15
		{ IsM4PKCS15Profile,					CreateM4PKCS15Profile		},
		{ IsV4PKCS15ECProfile,					CreateV4PKCS15ECProfile		},
		{ IsV4PKCS15Profile,					CreateV4PKCS15Profile		},
		{ IsJCPKCS15ECProfile,					CreateJCPKCS15ECProfile		},
		{ IsJCPKCS15v2ECProfile,				CreateJCPKCS15v2ECProfile	},	//!< PKCS#15v2 alias ISO 7816/15
		{ IsJCPKCS15Profile,					CreateJCPKCS15Profile		},
		{ IsJCPKCS15v2Profile,					CreateJCPKCS15v2Profile		},	//!< PKCS#15v2 alias ISO 7816/15
		{ IsACOSPKCS15Profile,					CreateACOSPKCS15Profile		},
		{ IsStarCOSPKCS15Profile,				CreateStarCOSPKCS15Profile	},

		// ACOS
		{ IsACOScvProfile,						CreateACOScvProfile			},

		// JavaCardOS
		{ IsJCProfile,							CreateJCProfile				},
		// { IsJavaCardAppletManager,			CreateJavaCardAppletManager	},

		// CardOS
		{ IsM4cvMoCProfile,						CreateM4cvMoCProfile		},
		{ IsM4cvECProfile,						CreateM4cvECProfile			},
		{ IsV4cvECProfile,						CreateV4cvECProfile			},
		{ IsV4cvProfile,						CreateV4cvProfile			},
		{ IsM4cvProfile,						CreateM4cvProfile			},
		// { IsV4CNSProfile,					CreateV4CNSProfile			},

		// third party profiles
		{ IsStudentCardProfile,					CreateStudentCardProfile	},	//!< SECCOS
		{ IsTCOSPKCS15Profile,					CreateTCOSPKCS15Profile		},	//!< TCOS virtual PKCS#15 profiles
#		if defined(ACT_SUPPORT_SIGNTRUST_SC32)
		{ IsSigntrustToken,						CreateSigntrustToken		},	//!< STARCOS
#		endif
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardTokenNameMapEntry SCardTokenNameMap[] = 
	{
		{ "PACE",								CreatePACEToken				},	//!< PACE only
		{ 0, 0 }
	};

	//!
	//! \brief \c Key to \ref ITokenConfig factory method mapping.
	//! \note  \c Key is context specific!
	// ------------------------------------------------------------------------
	const TokenConfigReg::Entry TokenConfigMap[] =
	{
		{ "ePA",								ACT_FACTORY(mEACConfig)		},	//!< mEAC-MF
		{ "PACE",								ACT_FACTORY(mEACConfig)		},	//!< mEAC-MF
		{ "MDPACE",								ACT_FACTORY(mEACConfig)		},	//!< mEAC-MF
		{ "NIMC01",								ACT_FACTORY(NIMC01Config)	},	//!< Nigeria
		{ Default,								ACT_FACTORY(TokenConfig)	},	//!< Default
		{ 0, 0 }
	};

	//!
	//! \brief \c ATR Historical Bytes to \ref ITokenFileCache factory method mapping.
	// ------------------------------------------------------------------------
	const TokenFileCacheReg::Entry TokenFileCacheMap[] =
	{
		{ Default,								ACT_FACTORY(TokenFileCache)	},	//!< Default
		{ "006405a0030431c073f701d0009000",		ACT_FACTORY(TCOSSigCardV2)	},	//!< TCOS 3.0 Signature Card V2.0 R1 with Netkey application
		{ "00640411030131c073f701d0009000",		ACT_FACTORY(TCOSSigCardV1)	},	//!< TCOS 3.0 Signature Card V1.0 with Netkey application
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenExtensionMapEntry TokenExtensionMap[] =
	{
		{ "MDProfileExt",						CreateMDProfileExt			},	//!< Minidriver FS Profile Extension
#		if defined(ACT_INIT_MS_CAPI)
		{ "EACv201-TA",							CreateEACv2xTAwithCAPI		},
#		endif
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenAuthProtocolMapEntry TokenAuthProtocolMap[] =
	{
		{ "PkiMD-PACE",							CreatePACEPkiMD				},
		{ "EACv2x-PACE",						CreatePACEmEACv2x			},
		{ "EACv2x-PCSC-PACE",					CreatePCSCPACEmEACv2x		},
		{ "EACv201-TA",							CreateTAmEACv201			},
		{ "EACv201-CA",							CreateCAmEACv201			},
		{ "BAC",								CreateBACmEACv1x			},
		{ "TCOS-QES-SM",						CreateTokenAuthTCOSv301QES	},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenInitializerMapEntry TokenInitializerMap[] =
	{
		{ "JCV",								CreateJCInitializer			},
		{ "PKI",								CreateJCInitializer			},
		{ "PKI-ECC",							CreateJCInitializer			},
		{ "PKI-PACE",							CreateJCInitializer			},
		{ "JavaCardOS",							CreateJCInitializer			},
		{ "CardOS V4.2",						CreateV4Initializer			},
		{ "CardOS V4.3",						CreateV4Initializer			},
		{ "CardOS V4.3B",						CreateV4Initializer			},
		{ "CardOS V4.2B",						CreateV4Initializer			},
		{ "CardOS V4.2B DI",					CreateV4Initializer			},
		{ "CardOS V4.2C",						CreateV4Initializer			},
		{ "CardOS V4.4",						CreateV4Initializer			},
		{ "CardOS V5.0",						CreateV4Initializer			},
		{ "CardOS V5.3 DI",						CreateV4Initializer			},
		{ "CardOS V5.3",						CreateV4Initializer			},
		{ "CardOS M4",							CreateM4Initializer			},
		{ "CardOS M4.01",						CreateM4Initializer			},
		{ "CardOS M4.01a",						CreateM4Initializer			},
		{ "ACOS",								CreateACOSInitializer		},
		{ "StarCOS",							CreateStarCOSInitializer	},
		{ "SECCOS",								CreateSECCOSInitializer		},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const ProfileGeneratorMapEntry ProfileGeneratorMap[] =
	{
		{ "PKI-2.X",							CreateJCPKCS15Pki2x			},
		{ "PKI-3.X",							CreateJCPKCS15Pki3x			},
		{ "PKI-3.0100",							CreateJCPKCS15Pki3x			},
		{ "PKI-3.0101",							CreateJCPKCS15Pki3x			},
		{ "PKI-3.0102",							CreateJCPKCS15Pki3x			},
		{ "PKI-3.0110",							CreateJCPKCS15Pki3x			},
		{ "PKI-3.0112",							CreateJCPKCS15Pki3x			},
		// Minidriver 
		{ "PKI-MD-2.X",							CreateJCPKCS15Pki2x			},
		{ "PKI-MD-3.X",							CreateJCPKCS15Pki3x			},
		{ "PKI-MD-3.0100",						CreateJCPKCS15Pki3x			},
		{ "PKI-MD-3.0101",						CreateJCPKCS15Pki3x			},
		{ "PKI-MD-3.0102",						CreateJCPKCS15Pki3x			},
		{ "PKI-MD-3.0110",						CreateJCPKCS15Pki3x			},
		{ "PKI-MD-3.0112",						CreateJCPKCS15Pki3x			},
		// Minidriver MDMF with PACE
		{ "PKI-MD-PACE-2.1xx",					CreateJCPKCS15MDMFPki21xx	},	//!< ePKIApplet version >= 2.126
		{ "PKI-MD-PACE-3.0101",					CreateJCPKCS15MDMFPki3x		},
		{ "PKI-MD-PACE-3.0102",					CreateJCPKCS15MDMFPki3x		},
		{ "PKI-MD-PACE-3.0110",					CreateJCPKCS15MDMFPki3x		},
		{ "PKI-MD-PACE-3.0112",					CreateJCPKCS15MDMFPki3x		},
		// Pki/SigG ePA-MF with PACE
		{ "mEAC-PACE-3.0101",					CreateJCPKCS15EACPkiS3x		},	//!< post issuance
		{ "mEAC-PACE-3.0102",					CreateJCPKCS15EACPkiS3x		},	//!< post issuance
		// Pki/eBA ePA-MF with PACE
		{ "mEAC-PACE-eBA-3.0101",				CreateJCPKCS15EACeBA3		},	//!< post issuance
		{ "mEAC-PACE-eBA-3.0102",				CreateJCPKCS15EACeBA3		},	//!< post issuance
		{ "mEAC-PACE-eBA-3.0110",				CreateJCPKCS15EACeBA3		},	//!< post issuance
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const PKCS15BehaviorMapEntry PKCS15BehaviorMap[] =
	{
		// NOTE: 12/18/2015,					SCI >= 6.5
		{ "cv cryptovision gmbh (c) v1.2ns",	CreateStarCOSPKCS15ECBehavior	},	//!< StarCOS ECC

		// NOTE: 11/06/2014,					SCI >= 6.3
		{ "cv cryptovision gmbh (c) v1.1n",		CreateV4PKCS15Behavior		},

		// NOTE: 11/28/2012,					SCI >= 6.x
		{ "cv cryptovision gmbh (c) v1.1ns",	CreateStarCOSPKCS15Behavior	},
		{ "cv cryptovision gmbh (c) v1.1j",		CreateJCPKCS15Behavior		},
		{ "cv cryptovision gmbh (c) v1.1jEAC",	CreateJCPKCS15EACBehavior	},
		{ "cv cryptovision gmbh (c) v1.1jPACE",	CreateJCPKCS15PACEBehavior	},

		// NOTE: 11/28/2012,					SCI < 6.0.0
		{ "cv cryptovision gmbh (c) v1.0j",		CreateJCPKCS15Behavior		},
		{ "cv cryptovision gmbh (c) v1.0jEAC",	CreateJCPKCS15EACBehavior	},
		{ "cv cryptovision gmbh (c) v1.0ns",	CreateStarCOSPKCS15Behavior	},
		{ "cv cryptovision gmbh (c) v1.0n",		CreateV4PKCS15Behavior		},
		{ "cv cryptovision gmbh (c) v1.0na",	CreateACOSPKCS15Behavior	},
		{ "cv cryptovision gmbh (c) v1.0nt",	CreateTCOS30PKCS15Behavior	},

		// cryptovision derived (or equal to) behavior
		{ "Dexa Systems, Inc. (c) v 1.0 cf",	CreateJCPKCS15Behavior		},
		{ "Dexa Systems, Inc. (c) v 1.1 cf",	CreateJCPKCS15Behavior		},
		{ "Dexa Systems, Inc. (c) v 1.1 cfEAC",	CreateJCPKCS15EACBehavior	},
		{ "Dexa Systems, Inc. (c) v 1.1 cfPACE", CreateJCPKCS15PACEBehavior	},
		{ "NIMC01",								CreateJCPKCS15Behavior		},	//!< Nigeria
		{ "eHealth Card cv cryptovision GmbH",	CreateJCPKCS15Behavior		},
		{ "Swiss Post (c) VKplus G2",			CreateECHBehavior			},
		{ "Bdr_eBa_3.0",						CreateEBABehavior			},
		{ "BDR-GoIDCard-v1",					CreateEBABehavior			},
		{ "Bundesdruckerei GmbH",				CreateEBABehavior			},

		// third party behavior
		{ "A.E.T. Europe B.V.",					CreateSafeSignBehavior		},
		{ "TC TrustCenter",						CreateTCTCSafeSignBehavior	},
		{ "Giesecke&Devrient GmbH",				CreateStarSignBehavior		},
		{ "D-TRUST GmbH (C)",					CreateDTRUSTBehavior		},
		{ "Siemens AG (C)",						CreateHiPathBehavior		},
		{ "SwissSign",							CreateHiPathBehavior		},
		{ "Technology Nexus",					CreateNexusBehavior			},
		{ "Volkswagen AG",						CreateVWBehavior			},
		{ "Signature Application",				CreateStudentCardBehavior	},	//!< use token label

		{ "",									CreatePKCS15Behavior		},	//!< default
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SubsystemMapEntry SubsystemMap[] = 
	{
		{ "PCSC",	CreatePCSCSystem,			CreatePCSCSystemEx			},

#	if !defined(ACT_IOS)
		{ "CTAPI",	CreateCTAPISystem,			0	},
		{ "PKCS11",	CreatePKCS11System,			0	},

#	endif
#	if defined(ACT_INIT_MS_CAPI)
		{ "CSP",	CreateCSPSystem,			0	},

#	endif
		{ 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SlotMonitorRegEntry SlotMonitorMap[] = 
	{
#	if !defined(ACT_IOS)
		{ "PCSC",   { CreatePCSCSlotMonitor,	CreatePCSCSystemSlotMonitor } },
		{ "CTAPI",  { CreateSlotMonitor,		0 } },
		{ "PKCS11",	{ CreateSlotMonitor,		0 } },

#	endif
#	if defined(ACT_INIT_MS_CAPI)
		{ "CSP",	{ CreateSlotMonitor,		0 } },

#	endif
		{ 0, { 0, 0 } }
	};

	// ------------------------------------------------------------------------
	const JCardAppletEntry JCardAppletMap[] = 
	{
		// AID if it is equal to 0 then all AID are able
		//     function  returns true if the Applet can used
		//                  creates an new applet
		//                                 number of PIN's Key's Certificate's
		//  if they are -1 then it will be checked
		//  if they are biger or equal to 0 they are const
		{ "D276000098C00000", IsJCProfileApplet, CreateJCProfileApplet, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 }
	};
#endif // NO_SMARTCARD

	// ------------------------------------------------------------------------
	const char* GetVersion();

	// ------------------------------------------------------------------------
	inline void Init(bool bAlwaysInit = false)
	{
		static bool loaded = false;
		if(loaded == true && bAlwaysInit == false)
			return;

		KeyReg::Insert(KeyMap);
		KeyInfoReg::Insert(KeyInfoMap);
		BlockCipherReg::Insert(BlockCipherMap);
		BlockCipherModeReg::Insert(BlockCipherModeMap);
		StreamCipherReg::Insert(StreamCipherMap);
		HashReg::Insert(HashMap);
		EMSAReg::Insert(EMSAMap);
		DerivatorReg::Insert(DerivatorMap);
		PaddingReg::Insert(PaddingMap);
		CertificateReg::Insert(CertificateMap);
		CRLReg::Insert(CRLMap);
		X509KeyReg::Insert(X509KeyMap);
		X509SignReg::Insert(X509SignMap);
		X509SignHashReg::Insert(X509SignHashMap);

#ifndef NO_SMARTCARD
		SubsystemReg::Insert(SubsystemMap);
		SlotMonitorReg::Insert(SlotMonitorMap);
		SCardOSReg::Insert(SCardOSMap);
		SCardOSReg::Insert(SCardOSMapEx);
		SCardOSReg::Insert(SCardOSAtrMaskMap);
		SCardOSDerivationReg::Insert(SCardOSDerivationMap);
		SCardTokenReg::Insert(SCardTokenMap);
		SCardTokenNameReg::Insert(SCardTokenNameMap);
		TokenConfigReg::Insert(TokenConfigMap);
		TokenFileCacheReg::Insert(TokenFileCacheMap);
		TokenExtensionReg::Insert(TokenExtensionMap);
		TokenInitializerReg::Insert(TokenInitializerMap);
		TokenAuthProtocolReg::Insert(TokenAuthProtocolMap);
		ProfileGeneratorReg::Insert(ProfileGeneratorMap);
		PKCS15BehaviorReg::Insert(PKCS15BehaviorMap);
		JCardAppletReg::Insert(JCardAppletMap);
#endif
		CreateFastRNG = CreateFIPS186;
		CreateStrongRNG = CreateFIPS186K4;
		loaded = true;
	}

} // namespace act 

#endif // actInit_h
