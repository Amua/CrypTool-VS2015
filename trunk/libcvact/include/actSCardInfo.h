// ---------------------------------------------------------------------------
// Name:      actSCardInfo.h
// Product:   cv act library
// Purpose:   Default ATR Card OS mapping
//
// Copyright: (c) 2003 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  08/27/2003
// ---------------------------------------------------------------------------

#ifndef ACT_SCARDINFO_H
#define ACT_SCARDINFO_H

#include <actISlot.h>

namespace act
{
	// ---------------------------------------------------------------------------
	static const ATRCardInfo ATRCardInfo_Map[] =
	{
		// ATR without historical bytes
		{ "Ambiguous ATR",	"3bf00000008131fe4500", "ffff00ffffffffffff00" },	// JCOP v2.4.2
		{ "Ambiguous ATR",	"3b80800101", 0 },									// G&D Mobile Security Card 3.x, JCOP v2.4.2 contactless

		// ActivCard
		{ "ActivCard Gold Cyberflex Access V4 64K SM 2.1", "3b6500002905010201", 0 },
		{ "ActivCard Gold Schlumberger Cyberflex Access #1", "3b6500009c02020701", 0 },
		{ "ActivCard Gold Schlumberger Cyberflex Access #2", "3b6500009c02020702", 0 },
		{ "ActivCard Gold Schlumberger Cyberflex Access V4 sm1.3", "3b660000009c11010103", 0 },
		{ "ActivCard Gold Cyberflex Access V4 Bio SM 3.1", "3b660000009c11010301", 0 },
		{ "ActivCard Gold Gemplus GXP PRO 64K", "3b6b00008065b08301037483009000", 0 },
		{ "ActivCard Gold Gemplus GemXpresso", "3f6d000080318065b00501025e92009000", 0 },
		{ "ActivCard Gold Gemplus GXP PRO 64K", "3b7b9400008065b08301037483009000", 0 },
		{ "ActivCard Gold Cosmopolic V4", "3b7f1800000031c0739e010b6452d90400829000", 0 },
		{ "ActivCard Gold", "3b8540206801010204", 0 },
		{ "ActivCard Gold", "3b8540fe6801010204", 0 },
		{ "ActivCard Gold Schlumberger Cryptoflex 16K", "3b8540ff6301010301", 0 },
		{ "ActivCard Gold Schlumberger Sema Cryptoflex 8k", "3b8640206801010204ac", 0 },
		{ "ActivCard Gold GND", "3bff1800ff8031fe45536d4072744361666545787065727465", 0 },

		// Aladdin
		{ "Aladdin eToken R2 2242", "3b811f00cc52", 0 },

		// Atmel
		{ "Atmel memory card AT88SC0204C", "3bb2110010800002", 0 },

		// Austria Card
		{ "AustriaCard ACOS EMV-A03", "3bbf11008131fe45410310000000000000000000000000f7", 0 },
		{ "AustriaCard ACOS", "3bbf11008131fe4541433100000000000000000000000096", 0 },
		{ "AustriaCard ACOS EMV-A01", "3bbf11008131fe4541433100000000022790400000000063", 0 },
		{ "AustriaCard ACOS A03", "3bbf18008131fe4541434f000000000000000000000000e1", 0 },

		{ "AustriaCard ACOS EMV-D01", "3be900008131fe45454d5620303320200699", 0 },
		{ "AustriaCard ACOS EMV-D01", "3b86800144492030324d65", 0 }, // contactless
		{ "AustriaCard ACOS EMV-D01", "3be600ff8131fe4544492030324d70", 0 },
		{ "AustriaCard ACOS EMV-A04/A05", "3bbf11008131fe45455041000000000228505900000000d2", 0 },
		{ "AustriaCard ACOS EMV-A04/A05", "3bbf11008131fe45455041000000000000000000000000f1", 0 },
		{ "AustriaCard ACOS EMV-A04/A05", "3bbf13008131fe45455041000000000000000000000000f3", 0 },

		// Austria Card Javacard
		{ "AustriaCard JCOP V2.4.1", "3b7a1800ff4a434f50563234314143", 0 }, // T=0
		{ "AustriaCard JCOP V2.4.1", "3bfa1800008131fe454a434f5056323431414300", "ffffffffffffffffffffffffffffffffffffff00" }, // T=1
		{ "AustriaCard JCOP V2.4.1", "3b8a80014a434f5056323431414300", "ffffffffffffffffffffffffffff00" }, // T=1

		{ "AustriaCard JCOP V2.4.1", "3b791800ff5257414e44415f4944", 0 }, // T=0, 'RWANDA_ID'
		{ "AustriaCard JCOP V2.4.1", "3bf91800008131fe455257414e44415f494400", "ffffffffffffffffffffffffffffffffffff00" }, // T=1, 'RWANDA_ID'
		{ "AustriaCard JCOP V2.4.1", "3b8980015257414e44415f494400", "ffffffffffffffffffffffffff00" }, // T=1, 'RWANDA_ID'

		{ "AustriaCard JCOP 21 V2.2", "3b7a1800ff4a434f5032315632325f", 0 }, // T=0
		{ "AustriaCard JCOP 21 V2.2", "3bfa1800008131fe454a434f5032315632325f00", "ffffffffffffffffffffffffffffffffffffff00" }, // T=1

		{ "AustriaCard JCOP 31/72 V2.3.1", "3b6800ff4a434f5033314d34", 0 }, // T=0
		{ "AustriaCard JCOP 31/72 V2.3.1", "3b8880014a434f5033314d3464", 0 }, // T=1

		{ "AustriaCard JCOP 31 V2.2", "3b7a1800ff4a434f5033315632325f", 0 }, // T=0
		{ "AustriaCard JCOP 31 V2.2", "3bfa1800008131fe454a434f5033315632325f00", "ffffffffffffffffffffffffffffffffffffff00" }, // T=1
		{ "AustriaCard JCOP 31 V2.2", "3b8a80014a434f5033315632325f00", "ffffffffffffffffffffffffffff00" }, // T=1

		{ "AustriaCard JCOP 41 V2.4", "3b7a1800ff4a434f5034315632345f", 0 }, // T=0
		{ "AustriaCard JCOP 41 V2.4", "3bfa1800008131fe454a434f5034315632345f00", "ffffffffffffffffffffffffffffffffffffff00" }, // T=1
		{ "AustriaCard JCOP 41 V2.4", "3b8a80014a434f5034315632345f00", "ffffffffffffffffffffffffffff00" }, // T=1

		// Datakey
		{ "Datakey DCOS model 320", "3bff1300ff8131fe5d8025a00000005657444b33323005003f", 0 },

		// G & D
		{ "G&D STARCOS S2.1", "3bbf18008131705253544152434f532053323120439000fd", 0 },
		{ "G&D STARCOS S2.1", "3bbf18008131705553544152434f532053323120439000fa", 0 },
		{ "G&D STARCOS SPK2.1C", "3bbf1800c02031705253544152434f5320533231204390009c", 0 },
		{ "G&D STARCOS SPK 2.2", "3bb794008131fe6553504b32329000d0", 0 },
		{ "G&D STARCOS SPK 2.3", "3bb794008131fe6553504b32339000d1", 0 },
		{ "G&D STARCOS SPK 2.4", "3bb718008131fe6553504b323490005a", 0 },
		{ "G&D STARCOS SPK 2.4", "3bb71800c03e31fe6553504b3234900025", 0 },

		{ "G&D STARCOS 3.0", "3bbb1800c01031fe4580670412b003030000810138", 0 },			// creational state
		{ "G&D STARCOS 3.0", "3bbb1800c01031fe4580670412b00303000081053c", 0 },
		{ "G&D STARCOS 3.0", "3b89800180670412b00303000049", 0 },
		{ "G&D STARCOS 3.1", "3b8d0180655343010d067394211b81012e", 0 },					// creational state
		{ "G&D STARCOS 3.1", "3b8d0180655343010d067394211b81052a", 0 },
		{ "G&D STARCOS 3.2", "3b9f9681b1fe451f070064051eb20031b0739621db01900058", 0 },	// creational state
		{ "G&D STARCOS 3.2", "3b9f9681b1fe451f070064051eb20031b0739621db0590005c", 0 },
		{ "G&D STARCOS 3.4", "3bdb18ff8131fe458067041bb42a000a028101d9", 0 },			// creational state
		{ "G&D STARCOS 3.4", "3bdb18ff8131fe458067041bb42a000a028105dd", 0 },
		{ "G&D STARCOS 3.4", "3bdd96ff81b1fe451f038031b052010364041bb42281011f", 0 },	// HBA G1, Version 2.3.2, creational state
		{ "G&D STARCOS 3.4", "3bdd96ff81b1fe451f038031b052010364041bb42281051b", 0 },	// HBA G1, Version 2.3.2
		{ "G&D STARCOS 3.5", "3bdb96ff8131fe4580670534b50201c0a1810138", 0 },			// creational state
		{ "G&D STARCOS 3.5", "3bdb96ff8131fe4580670534b50201c0a181053c", 0 },

		{ "G&D STARCOS 3.4 (Health Card)", "3bd896ff8131fe458064041bb42a81055b", 0 },                // VKplus 2010
		{ "G&D STARCOS 3.4 (Health Card)", "3bd818ff8131fe458064041bb42a8105d5", 0 },                // VKplus 2012
		{ "G&D STARCOS 3.4 (Health Card)", "3bdb96ff8131fe458067041bb42200c081810512", 0 },          // VKplus 2012 (test card 1)
 
		{ "G&D STARCOS 3.4", "3bd818ff81b1fe451f038064041ab403810561", 0 },				// D-TRUST multicard advanced 3.x 

		// G & D JavaCard

		// SCE 64 XMC2:
		{ "G&D Sm@rtCafe Expert 64 (XMC2)",				"3b0f404d4f504153530000000000000000", "ffffffffffffffffff0000000000000000" },
		// SCE 64 Starkey400 cold:   (will use a common ATR mask in CSP/MD registries)
		{ "G&D Sm@rtCafe Expert 64 (cfg1, StarKey400)",	"3bfd9400ff8131fe458073002113574a544861314a0047", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg2, StarKey400)",	"3bfd9400ff8131fe458073002113574a5448613147004a", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg3, StarKey400)",	"3bfd9400ff8131fe458073002113574a54486131480045", 0 },
		// SCE 64 cold:   (will use a common ATR mask in CSP/MD registries)
		{ "G&D Sm@rtCafe Expert 64 (cfg1)", "3bfd1800ff80b1fe451f078073002113574a544861314a0052", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg2)", "3bfd1800ff80b1fe451f078073002113574a5448613147005f", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg3)", "3bfd1800ff80b1fe451f078073002113574a54486131480050", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg4)", "3bfd1800ff80b1fe451f078073002113574a544861314b0053", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg5)", "3bfd1800ff80b1fe451f078073002113574a544861314c0054", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg8)", "3bfd1800ff80b1fe451f078073002113574a54486131490051", 0 },
		// SCE 64 warm:    (will use a common ATR mask in CSP/MD registries)
		{ "G&D Sm@rtCafe Expert 64 (cfg1)", "3b6d00ff8073002113574a544861314a00", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg2)", "3b6d00ff8073002113574a544861314700", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg3)", "3b6d00ff8073002113574a544861314800", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg4)", "3b6d00ff8073002113574a544861314b00", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg5)", "3b6d00ff8073002113574a544861314c00", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg8)", "3b6d00ff8073002113574a544861314900", 0 },
		// SCE 64 T1 only:    (will use a common ATR mask in CSP/MD registries)
		{ "G&D Sm@rtCafe Expert 64 (cfg1)", "3bfd1800ff8131fe458073002113574a544861314a00cb", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg2)", "3bfd1800ff8131fe458073002113574a544861314700c6", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg3)", "3bfd1800ff8131fe458073002113574a544861314800c9", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg4)", "3bfd1800ff8131fe458073002113574a544861314b00ca", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg5)", "3bfd1800ff8131fe458073002113574a544861314c00cd", 0 },
		{ "G&D Sm@rtCafe Expert 64 (cfg8)", "3bfd1800ff8131fe458073002113574a544861314900c8", 0 },

		{ "G&D Sm@rtCafe", "3b6900ff536d40727443616665", 0 },
		{ "G&D Sm@rtCafe 1.1", "3bbf1100c01031fe44534d405254204341464520312e3143c1", 0 },
		{ "G&D Sm@rtCafe Expert 2.0", "3bff1800ff8031fe45534653452d43583332322d561803087c", 0 },
		{ "G&D Sm@rtCafe Expert 3.0", "3bf81800008131fe450073c8401300900093", 0 },
		{ "G&D Sm@rtCafe Expert 3.1", "3bf81800008031fe450073c8401300900092", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (cd144)", "3b7a18000073667465206364313434", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (cd080)", "3b7a180000736674652d6364303830", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (sfte)", "3bf41800008031fe4573667465e2", 0},
		{ "G&D Sm@rtCafe Expert 3.2 (sfte)", "3b7418000073667465", 0 },													// sfte, T=0
		{ "G&D Sm@rtCafe Expert 3.2 (sfte-nf)", "3bf71800008031fe45736674652d6e66c4", 0},
		{ "G&D Sm@rtCafe Expert 3.2 USB Token", "3b880173c840130090009b6a", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (cd080-nf)", "3bfd1800008031fe45736674652063643038302d6e66d1", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (cd144-nf)", "3bfd1800008031fe45736674652063643134342d6e66d8", 0 },
		{ "G&D Sm@rtCafe Expert 5.0 (SF-4CC-01)", "3b7918000053462d3443432d3031", 0 },									// T=0
		{ "G&D Sm@rtCafe Expert 5.0 (SF-4CC-01)", "3bf91800008031fe4553462d3443432d3031cb", 0 },						// T=1

		{ "G&D Sm@rtCafe Expert 6.0 (CD081-F)",  "3bfd1800008031fe4553434536302d43443038312d46c4", 0 },					// SCE60-CD081-F
		{ "G&D Sm@rtCafe Expert 6.0 (CD081-F)",  "3b8d800153434536302d43443038312d4627", 0 },							// SCE60-CD081-F contactless
		{ "G&D Sm@rtCafe Expert 6.0 (CC081-F)",  "3bfd1800008131fe4553434536302d43433038312d46c2", 0 },					// SCE60-CC081-F USB-Token

		{ "G&D Sm@rtCafe Expert 6.0 (CD081-nF)", "3bfe1800008031fe4553434536302d43443038312d6e46a9", 0 }, 				// SCE60-CD081-nF
		{ "G&D Sm@rtCafe Expert 6.0 (CD081-nF)", "3b8e800153434536302d43443038312d6e464a", 0 },							// SCE60-CD081-nF contactless
		{ "G&D Sm@rtCafe Expert 6.0 (CC081-nF)", "3bfe1800008131fe4553434536302d43433038312d6e46af", 0 }, 				// SCE60-CC081-nF USB-Token

		{ "G&D Sm@rtCafe Expert 6.0 (CD145-F)",  "3bfd1800008031fe4553434536302d43443134352d46cd", 0 },					// SCE60-CD145-F
		{ "G&D Sm@rtCafe Expert 6.0 (CD145-F)",  "3b8d800153434536302d43443134352d462e", 0 },							// SCE60-CD145-F contactless
		{ "G&D Sm@rtCafe Expert 6.0 (CC145-F)",  "3bfd1800008131fe4553434536302d43433134352d46cb", 0 },					// SCE60-CC145-F USB-Token

		{ "G&D Sm@rtCafe Expert 6.0 (CD145-nF)", "3bfe1800008031fe4553434536302d43443134352d6e46a0", 0 }, 				// SCE60-CD145-nF
		{ "G&D Sm@rtCafe Expert 6.0 (CD145-nF)", "3b8e800153434536302d43443134352d6e4643", 0 },							// SCE60-CD145-nF contactless
		{ "G&D Sm@rtCafe Expert 6.0 (CC145-nF)", "3bfe1800008131fe4553434536302d43433134352d6e46a6", 0 }, 				// SCE60-CC145-nF USB-Token

		{ "G&D Sm@rtCafe Expert 7.0", "3bf90000008031fe4553434537000000000000", "ffff00ff00f0ffffffffffffff000000000000" }, // T=1
		{ "G&D Sm@rtCafe Expert 7.0",           "3b89800153434537000000000000",           "ffffffffffffffff000000000000" },	// T=CL

		// G & D JavaCard DI (contactless)
		{ "G&D Sm@rtCafe Expert 3.1", "3bfe9100ff918171fe40004138004133b1020073c8401300908f", 0 },						// SCM SDI010, Firmware V6.28
		{ "G&D Sm@rtCafe Expert 3.1", "3bfe9100ff918171fe40004138004133b10073c840130090008d", 0 },						// SCM SDI010, Firmware V6.32
		{ "G&D Sm@rtCafe Expert 3.1", "3b8880010073c8401300900071", 0 },												// SCM SDI010, Firmware V7.09
		{ "G&D Sm@rtCafe Expert 3.2 (cd144)", "3b8a80017366746520636431343419", 0 },
		{ "G&D Sm@rtCafe Expert 3.2 (cd080)", "3b8a8001736674652d63643038301d", 0 },
		{ "G&D Sm@rtCafe Expert 5.0 (SF-4CC-01)", "3b89800153462d3443432d303128", 0 },

		// G & D Mobile Security Card
		{ "G&D Mobile Security Card 3.x", "3bb91800c00a31fe4553504b32354449900033", 0 },
		{ "G&D Mobile Security Card 3.x", "3b034d5343", 0 },

		// certgate
		// NOTE: last update 10/2/2013
		// NOTE: based on file://../../sci_common.src/Cards/Certgate.inc
		{ "certgate microSD V1 Rev1 (JCOP v2.2 S3 512MB)", "3be900008131fe454a434f503231563232a1", 0 },
		{ "certgate microSD V1 Rev1 (JCOP v2.2 S3 512MB) ISO14443 Proxy", "3b8980014a434f5032315632324b", 0 },
		{ "certgate microSD V1 Rev2 (JCOP v2.3.1 S3 1024MB)", "3bfa1300008131fe454a434f5032315632333191", 0 },
		{ "certgate microSD V1 Rev2 (JCOP v2.3.1 S3 1024MB) ISO14443 Proxy", "3b8a80014a434f5032315632333178", 0 },
		{ "certgate microSD V1 Rev3 (JCOP v2.3.1 S6 1024MB)", "3bfa1300008131fe454a434f5034315632323196", 0 },
		{ "certgate microSD V1 Rev3 (JCOP v2.3.1 S6 1024MB) ISO14443 Proxy", "3b8a80014a434f503431563232317f", 0 },
		{ "certgate microSD V2 Rev1 (Sm@rtcafe Expert v5.0 2048MB) ISO7816 (ASSD BB)", "3b0fff2750483230534653100000000000", "ffffffffffffffffffffffff0000000000" },
		{ "certgate microSD V2 Rev1 (Sm@rtcafe Expert v5.0 2048MB) ISO14443 Proxy (ASSD BB)", "3b8f8001ff275048323053465310000000000000", "ffffffffffffffffffffffffffff000000000000" },
		{ "certgate microSD V2 Rev1 (Sm@rtcafe Expert v5.0 2048MB)", "3bf71800008031fe4543475346533032a5", 0 },
		{ "certgate microSD V2 Rev2 (JCOP v2.4.1 R3 4096MB) ISO7816 (ASSD BB)", "3b0fff2750484734304453200000000000", "ffffffffffffffffffffffff0000000000" },
		{ "certgate microSD V2 Rev2 (JCOP v2.4.1 R3 4096MB) ISO14443 Proxy (ASSD BB)", "3b8f8001ff275048473430445320000000000000", "ffffffffffffffffffffffffffff000000000000" },
		{ "Philips ISO Creditcard Rev1 (JCOP v2.2)", "3be900008131fe454a434f503431563232a7", 0 },
		{ "Philips ISO Creditcard Rev1 (JCOP v2.2) ISO14443", "3b8980014a434f5034315632324d", 0 },

		// Gemplus
		{ "Gemplus GemXpresso Pro R3", "3b7b9400008065b08301007483009000", "fffffffffffffffffffff0ffffffffff" },		// cold
		{ "Gemplus GemXpresso Pro R3", "3b6b00008065b08301007483009000", "fffffffffffffffffff0ffffffffff" },			// warm
		{ "Gemplus GemXpresso Pro R3 E32 PK", "3b7a9400008065a20101013d72d643", 0 },

		{ "Gemplus GemGATE  16K", "3b00003155025e0000000000", "ffff00ffffffa8273b000031" },
		{ "Gemplus GemSAFE 8K", "3b00006508005e0000000000", "ffff00ffff00a8273b000065" },
		{ "Gemplus GemSAFE IS 16K", "3b00006509005e0000000000", "ffff00ffff00a8273b000065" },
		{ "Gemplus GemSAFE 4K", "3b00650401005e000000", "ffffffe5ff00a8273b00" },
		{ "Gemplus GemSAFE Multos 32K", "3b0080e0040000000000000000000000000000", "ffffffffff000000000080e004000000000000" },
		{ "Gemplus GemSAFE Multos", "3b0080e0840000000000000000000000000000", "ffffffffff000000000080e084000000000000" },
		{ "Gemplus GemClub Memo", "3b025301", 0 },
		{ "Gemplus GemSAFE Windows", "3b1340d0016e0100000000000000", "ffffffffffffff273b1340d0016e" },
		{ "Gemplus MPCOS-3DES 64K EMV Filter", "3b240080729443", 0 },
		{ "Gemplus GemSAFE Card CSP v1.0", "3b27008065a200010137", 0 },
		{ "Gemplus GPK2000s", "3b27008065a202028237", 0 },
		{ "Gemplus GPK2000sp", "3b27008065a202038237", 0 },
		{ "Gemplus GPK4000s", "3b27008065a204010137", 0 },
		{ "Gemplus GPK4000sp", "3b27008065a205010137", 0 },
		{ "Gemplus GPK4000, RSA 512 bits Sign", "3b27008065a206010137", 0 },
		{ "Gemplus GPK4000", "3b27008065a20c010137", 0 },
		{ "Gemplus GemSAFE Smart Card (4K)", "3b27008065a200010137", "ffffffffffff00ffffff" },
		{ "Gemplus GPK 4000, RSA 1024 bits Sign", "3b27008065a28c3b2700", 0 },
		{ "Gemplus Moeda Electronica Bradesco", "3b29008072a445640000d015", 0 },
		{ "Gemplus MPCOS-3DES 8K", "3b29008072a4456400ff0010", 0 },
		{ "Gemplus MPCOS EMV 1 Byte sectors", "3b2a008065a20100000072d641", "ffffffffffffff000000ffffff" },
		{ "Gemplus MPCOS_EMV 4 Byte sectors", "3b2a008065a20100000072d643", "ffffffffffffff000000ffffff" },
		{ "Gemplus GemSAFE Multos 16K", "3b320080316b00000000000000000000000000000000", "ffffffffffff000000000080316b0000000000000000" },
		{ "Gemplus GemXplore Xpresso V3", "3b3b00008060ae030c000083009000", "ffff00fffff0ffffff0000ff00ffff" },
		{ "Gemplus GemXplore Xpresso V3", "3b3b00008060af030c000083009000", "ffff00fffff0ffffff0000ff00ffff" },
		{ "Gemplus GemXplore Xpresso V3", "3b3b00008060ae030d000083009000", "ffff00fffff0ffffff0000ff00ffff" },
		{ "Gemplus GemXplore Xpresso V3", "3b3b00008060af030d000083009000", "ffff00fffff0ffffff0000ff00ffff" },
		{ "Gemplus GemXplore'Xpresso V3 64K", "3b3b11008069af030c016f83009000", 0 },
		{ "Gemplus GemXplore'Xpresso V3 64K", "3b3b11008069af030c016f83019000", 0 },
		{ "Gemplus GemXplore Xpresso V3 B1P", "3b3b94008065af030d0174830f9000", 0 },
		{ "Gemplus GemXpresso PRO 64 PK SIM", "3b3f95008065af0312016f7332211b83009000", 0 },
		{ "Gemplus GemClub 1K", "3b6800008066a2060201320e", 0 },
		{ "Gemplus GemXpresso Lite with EMV", "3b6d000080318065b00601017783009000", 0 },
		{ "Gemplus DeLaRue ProlifIC", "3b6d00000031c071d66434c70100849000", 0 },
		{ "Gemplus HSBC Visa/MasterCard credit card", "3b6d00000031c071d66438d00300849000", 0 },
		{ "Gemplus Blue for American Express@Business", "3b6d00ff003180718e6448d50200829000", 0 },
		{ "Gemplus Australian ANZ First Visa Card from the ANZ", "3b6e0000003180718665016702a00a839000", 0 },
		{ "Gemplus Nat West Master Card", "3b6e00000031807186654744230102839000", 0 },
		{ "Gemplus GemXpresso 211is", "3b6e000080318065b00302015e8300009000", 0 },
		{ "Gemplus FirstUSA Visa", "3b6e000080318065b00301015e8300009000", 0 },
		{ "Gemplus FIN-ID PKCS#15", "3b9f0040000067114346495345105266ff819000", "ffff00f000ffffffffffffffffffffffffffffff" },
		{ "Gemplus GemSAFE Smart Card 8K", "3ba70040008065a208000000", "ffffffff00ffffffff000000" },
		{ "Gemplus GPK4000sdo", "3ba70040148065a214010137", 0 },
		{ "Gemplus GPK8000", "3ba70040188065a208010152", 0 },
		{ "Gemplus GPK16000", "3ba70040188065a209010152", 0 },
		{ "Gemplus GPK16000", "3ba70040188065a209010252", 0 },
		{ "Gemplus std", "3ba70040188065a209010352", 0 },
//		{ "Gemplus GemGATE PKCS#15", "3bf2000000c000300000c80300", "ffff000000f000f00000ffff00" },
//		{ "Gemplus SECCOS", "3bff0000ff8131004565000000000000000000000000000000", "ffff00ffffffff00ffff000000000000000000000000000000" },
//		{ "Gemplus SECCOS", "3bff00ff8131004565000000000000000000000000000000", "ffffffffffff00ffff000000000000000000000000000000" },
		{ "Gemplus GemSAFE Java Card", "3f008080b0015e0000000000000000", "ffffffffff0000003f008080b0015e" },
		{ "Gemplus GemXplore", "3f2f008059af0201013000000a0e83069f12", 0 },
		{ "Gemplus GemXplore 98 V1 16K", "3f2f008069af0307035200000a0e833e9f16", 0 },
		{ "Gemplus GSM-SIM e-plus (1800MHz)", "3f2f008069ae0202013600000a0e833e9f16", 0 },
		{ "Gemplus GSM-SIM D2 CallYa (900MHz)", "3f2f008069af0204013600020a0e833e9f16", 0 },
		{ "Gemplus GSM-SIM Debitel D2 (900MHz)", "3f2f008069af03070352000d0a0e833e9f16", 0 },
		{ "Gemplus GSM-SIM Virgin Mobile", "3f2f008069af0307035a00150a0e833e9f16", 0 },
		{ "Gemplus MCOS 16K DES Sample Card", "3f6c000024a03000ff00000100049000", 0 },
		{ "Gemplus MCOS 24k EEPROM", "3f6c000025a0308976000004010c9000", 0 },
		{ "Gemplus GemXpresso 211PK", "3f6d000080318065b00501025e83009000", 0 },

		// Gemalto
		{ "Gemalto TOP IM GX4", "3b7d94000080318065b0831148c883009000", 0 },											// cold
		{ "Gemalto TOP IM GX4", "3b6d000080318065b0831148c883009000", 0 },												// warm
		{ "Gemalto Cyberflex 64K", "3b959540ffae01030000", 0 },															// T=0

		// GSM-SIM
		{ "GSM-SIM BEN (1800MHz)", "3b0a20620c014f53459914aa", 0 },
		{ "GSM-SIM DNA Finland", "3b1f11806a323746495345128c02ff079000", 0 },
		{ "GSM-SIM Sonera", "3b1f94806a163246495345158ce6ff079000", 0 },
		{ "GSM-SIM SFR", "3b3c94004b3125a21013144783839000", 0 },
		{ "GSM-SIM T-Mobil D1 (900MHz)", "3b8300121096", 0 },
		{ "GSM-SIM Victorvox D1 (900MHz)", "3b85001202010096", 0 },
		{ "GSM-SIM Viag Interkom E2 Loop GSM (1800MHz)", "3b85008725013802", 0 },
		{ "GSM-SIM Telfort (Netherlands) 900 MHz", "3b85008725013900", 0 },
		{ "GSM-SIM BT Cellnet", "3b8900912691060001220100", 0 },
		{ "GSM-SIM T-Mobil D1 (900MHz)", "3b8a0091010016000116010096", 0 },
		{ "GSM-SIM Orange-UK (1800)", "3b999400910891060001060600", 0 },
		{ "GSM-SIM Victorvox D1 (900MHz)", "3b9a940091010017000123100096", 0 },
		{ "GSM-SIM Card T-D1 (900MHz)", "3b9a940091010017000123110096", 0 },
		{ "GSM-SIM Libertel (900MHz)", "3baa00401447473247543553343830", 0 },
		{ "GSM-SIM Viag Interkom E2 Loop (1800MHz)", "3bba9400401447473352533731365330", 0 },
		{ "GSM-SIM French card (900MHz)", "3f69000024af01700101ff9000", 0 },

		// IBM
		{ "IBM MFC 3.5 file system smart card", "3bef00ff813152454d46432049424d2034304839363031fb", 0 },
		{ "IBM MFC 4.1 file system smart card", "3bef00ff8131664549424d204d46433430303230383331a1", 0 },
		{ "IBM eCash", "3bef00ff813166456563202049424d20332e3120202020", 0 },
		{ "IBM eCash", "3bef00ff813166456563202049424d20332e3120202020cf", 0 },

		// JCOP 21
		{ "JCOP 21 V2.2", "3be900008131fe454a434f503231563232a1", 0 },
		{ "JCOP 21 V2.2", "3bf91000008131fe454a434f50323156323200", "fffff0ff00ffffffffffffffffffffffffff00" },
		{ "JCOP 21 V2.3.1", "3b7a1800ff4a434f50323156323331", 0 },														// T=0
		{ "JCOP 21 V2.3.1", "3bfa1000008131fe454a434f5032315632333100", "fffff0ff00ffffffffffffffffffffffffffff00" },	// T=1
		{ "JCOP 21 V2.4.1", "3b7a1800004a434f50323156323431", 0 },														// T=0
		{ "JCOP 21 V2.4.1", "3bfa1000008131fe454a434F5032315632343100", "fffff0ff00ffffffffffffffffffffffffffff00" },	// T=1
		
		// JCOP 31
		{ "JCOP 31 V2.1", "3bfc9100ff918171fe40004128001177b04a434f503331e6", 0 },										// TODO: MTE: Check, this is invalid!
		{ "JCOP 31 V2.2", "3bf91000008131fe454a434f50333156323200", "fffff0ff00ffffffffffffffffffffffffff00" },
		{ "JCOP 31 V2.2", "3be900008131fe454a434f50333156323200", "ffffff00ffffffffffffffffffffffffff00" },				// no TA1
		{ "JCOP 31 V2.2", "3b8980014a434f50333156323200", "ffffffffffffffffffffffffff00" },								// contactless
		{ "JCOP 31 V2.3.1", "3bfa1000008131fe454a434f5033315632333100", "fffff0ff00ffffffffffffffffffffffffffff00" },
		{ "JCOP 31 V2.3.1", "3bea00008131fe454a434f5033315632333100", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 31 V2.3.1", "3b8a80014a434f5033315632333100", "ffffffffffffffffffffffffffff00" },						// contactless
		{ "JCOP 31 V2.3.1", "3b7a1800ff4a434f50333156323331", 0 },
		{ "JCOP 31 V2.4", "3bf91000008131fe454a434f50333156323400", "fffff0ff00ffffffffffffffffffffffffff00" },
		{ "JCOP 31 V2.4", "3be900008131fe454a434f50333156323400", "ffffff00ffffffffffffffffffffffffff00" },				// no TA1
		{ "JCOP 31 V2.4", "3b8980014a434f50333156323400", "ffffffffffffffffffffffffff00" },								// contactless
		{ "JCOP 31 36GDT", "3beb0000813120454a434f503331333647445478", 0 },
		{ "JCOP 31 V2.4.1", "3bfa1000008131fe454a434F5033315632343100", "fffff0ff00ffffffffffffffffffffffffffff00" },	// T=1
		{ "JCOP 31 V2.4.1", "3bea00008131fe454a434f5033315632343100", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 31 V2.4.1", "3b8a80014a434f5033315632343100", "ffffffffffffffffffffffffffff00" },						// contactless
		{ "JCOP 31 V2.4.1", "3b7a1800004a434f50333156323431", 0 },														// T=0 (assumed, based on 21 V2.4.1)

		// JCOP 41
		{ "JCOP 41 V2.2", "3bf91000008131fe454a434f50343156323200", "fffff0ff00ffffffffffffffffffffffffff00" },
		{ "JCOP 41 V2.2", "3be900008131fe454a434f50343156323200", "ffffff00ffffffffffffffffffffffffff00" },				// no TA1
		{ "JCOP 41 V2.2", "3b8980014a434f50343156323200", "ffffffffffffffffffffffffff00" },								// contactless
		{ "JCOP 41 V2.2", "3b8980014a434f5034315632324d", 0 },															// contactless, SCM SDI010, Firmware V7.09
		{ "JCOP 41 V2.2", "3bfe9100ff918171fe40004128001133b04a434f5034315632c3", 0 },									// contactless, SCM SDI010, Firmware V6.32
		{ "JCOP 41 V2.2.1", "3b7a1800ff4a434f50343156323231", 0 },														// T=0
		{ "JCOP 41 V2.2.1", "3bfa1000008131fe454a434f5034315632323100", "fffff0ff00ffffffffffffffffffffffffffff00" },
		{ "JCOP 41 V2.2.1", "3bea00008131fe454a434f5034315632323100", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 41 V2.2.1", "3b8a80014a434f5034315632323100", "ffffffffffffffffffffffffffff00" },						// contactless
		{ "JCOP 41 V2.2.1", "3bfe9100ff918171fe40004138001133b04a434f5034315632d3", 0 },								// contactless
		{ "JCOP 41 V2.2.1 (IDptoken 200)", "3b8a01434f50343156323231ff4a", 0 },
		{ "JCOP 41 V2.3.1", "3b7a1800ff4a434f50343156323331", 0 },														// T=0
		{ "JCOP 41 V2.3.1", "3bfa1000008131fe454a434f5034315632333100", "fffff0ff00ffffffffffffffffffffffffffff00" },
		{ "JCOP 41 V2.3.1", "3bea00008131fe454a434f5034315632333100", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 41 V2.3.1", "3b8a80014a434f5034315632333100", "ffffffffffffffffffffffffffff00" },						// contactless
		{ "JCOP 41 V2.3.2", "3b7a1800ff4a434f50343156323332", 0 },														// T=0
		{ "JCOP 41 V2.3.2", "3bfa1000008131fe454a434f5034315632333200", "fffff0ff00ffffffffffffffffffffffffffff00" },
		{ "JCOP 41 V2.3.2", "3bea00008131fe454a434f5034315632333200", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 41 V2.3.2", "3b8a80014a434f5034315632333200", "ffffffffffffffffffffffffffff00" },						// contactless
		{ "JCOP 41 V2.4.1", "3b7a1800004a434f50343156323431", 0 },														// T=0 (assumed, based on 21 V2.4.1)
		{ "JCOP 41 V2.4.1", "3bfa1000008131fe454a434f5034315632343100", "fffff0ff00ffffffffffffffffffffffffffff00" },
		{ "JCOP 41 V2.4.1", "3bea00008131fe454a434f5034315632343100", "ffffff00ffffffffffffffffffffffffffff00" },		// no TA1
		{ "JCOP 41 V2.4.1", "3b8a80014a434f5034315632343100", "ffffffffffffffffffffffffffff00" },						// contactless

		// JCOP other
		{ "JCOP V2.3.2",    "3be800008131fe450073c8400000900000", "ffffffffffffffffffffffffffffffff00" },				// V2.3.2
		{ "JCOP V2.3.2",    "3b8880010073c8400000900000", "ffffffffffffffffffffffff00" },								// V2.3.2 contactless
		{ "JCOP V2.4.1",    "3bf81000008131fe454a434f507632343100", "fffff0ff00ffffffffffffffffffffffff00" },			// prerelease
		{ "JCOP V2.4.1",    "3b8880014a434f507632343100", "ffffffffffffffffffffffff00" },								// contactless
		{ "JCOP V2.4.1+",   "3b8c80014a434f50763234326265746100", "ffffffffffffffffffffffffffffffff00" },				// v2.4.2beta contactless
		{ "JCOP V2.4.2 R1", "3bfa1300008131fe454a434f5076323432523100", "ffffffffffffffffffffffffffffffffffffff00" },	// v2.4.2 R1
		{ "JCOP V2.4.2 R1", "3b8a80014a434f5076323432523100", "ffffffffffffffffffffffffffff00" },	                    // v2.4.2 R1 contactless
		{ "JCOP V2.4.2 R2", "3bf90000008131fe454a434f50323432523200", "ffff00ffffffffffffffffffffffffffffff00" },		// v2.4.2 R2
 		{ "JCOP V2.4.2 R2", "3b8900014a434f50323432523200", "ffff00ffffffffffffffffffff00" },	                        // v2.4.2 R2 contactless
		{ "JCOP V2.4.2 R3", "3bf90000008131fe454a434f50323432523300", "ffff00ff00ffffffffffffffffffffffffff00" },		// v2.4.2 R3
		{ "JCOP V2.4.2 R3", "3b8900014a434f50323432523300", "ffff00ffffffffffffffffffff00" },	                        // v2.4.2 R3 contactless
		{ "Yubikey NEO R3 (JCOP V2.4.2 R2)", "3b8c8001597562696b65794e454f723300", "ffffffffffffffffffffffffffffffff00" },	// v2.4.2 R2 contactless
		{ "Yubikey NEO OTP+CCID (JCOP V2.4.2 R2)",	"3bfa00000000000000597562696b65794e454f00", "ffff00000000000000ffffffffffffffffffff00" }, // v2.4.2 R2
		{ "HID Crescendo iCLASS Px G8H", "3bdf96ff8131fe455a018048494443313158587300011b09", 0 },						// JCOP V2.4.1

		// JCOP old
		{ "JCOP bio31", "3b6600ff4a434f503331", 0 },
		{ "JCOP 20", "3bf61800ff8131fe454a434f5032300e", 0 },
		{ "JCOP 30/16", "3be600ff8131fe454a434f50303307", 0 },
		{ "JCOP 10/16", "3be600ff8131fe454a434f50313005", 0 },
		{ "JCOP 20/16", "3be600ff8131fe454a434f50323006", 0 },
		{ "JCOP 31bio", "3be600ff8131fe454a434f50333106", 0 },

		// Dexa
		{ "Dexa Crossfire v1", "3b0a000000000000004465786120434620763100", "ff0f00000000000000ffffffffffffffffffff00" },
		{ "Dexa Crossfire v1 (contactless)", "3b0a00004465786120434620763100", "ff0f0000ffffffffffffffffffff00" },

		// E.ON
		{ "EONCardV1", "3bf90000008131fe45454f4e43617264563100", "ffff00ff00ffffffffffffffffffffffffff00" },			// T=1
		{ "EONCardV1", "3b890001454f4e43617264563100", "ffff00ffffffffffffffffffff00" },								// T=CL
		{ "EONCardV2", "3bf90000008131fe45454f4e43617264563200", "ffff00ff00ffffffffffffffffffffffffff00" },			// T=1
		{ "EONCardV2", "3b890001454f4e43617264563200", "ffff00ffffffffffffffffffff00" },								// T=CL
		
		// idvation
		{ "JCOP V2.4.1 (AHC v1.0)", "3bf81000008131fe454148432076312e3000", "fffff0ff00ffffffffffffffffffffffff00" },   // AHC v1.0 (custom idvation)

		// ePasslet-Suite, MChip/4, JCOP 2.4.1 R3 or 2.4.2 R3
		{ "JCOP V2.4.[1/2] MChip/4", "3bfa1300008131fe450031c173c8400000900009", "ffffffffffffffffffffffffffffff0fffffff0f" },	// T=1
		{ "JCOP V2.4.[1/2] MChip/4", "3bea00008131fe450031c173c840000090000a", "ffffffffffffffffffffffffffff0fffffff0f" },		// T=1 warm
		{ "JCOP V2.4.[1/2] with CPA", "000000000031c173c8400000900000", "00000000ffffffffffffffffffff00" },						// T=1

		// ePasslet-Suite
		{ "GoID Card V1", "3b8000014244522d476f4944436172642d763100", "fff000ffffffffffffffffffffffffffffffff00" },

		// Infineon
		{ "Infineon jTOP V2 16K",         "3b6d000080318065409086015183079000", 0 },
		{ "Infineon JCLX32 jTOP v21",     "3bee00008131fe458031806640908b12171383019000ed", 0 },
		{ "Infineon SLJ 52GDL 150CL",     "3bfe0000008031fe45803180664090a51000008301900000", "ffff00ff00f0ffffffffffffffffffffff0000ffffffff00" },
		{ "Infineon SLJ 52GDL 160CL",             "3b7e000000803180664090a510000083019000",   "ffff00ff00f0ffffffffffffff0000ffffffff" }, // T = 0, On Card Debugger
		{ "Infineon SLJ 52GDL 128",         "3bfd0000008031fe45534c4a35324778787979797a5200", "ffff00ff00f0ffffffffffffffffffffffffffffffff00" }, // T=1
		{ "Infineon SLJ 52GDL 128",                             "3b88800100000011778183006d", 0 }, // T=CL
		{ "Infineon JCLX80 jTOP 20ID",    "3bfe0000008031fe45803180664090a45600008301900000", "ffff00ff00ffffffffffffffffffffffff0000ffffffff00" },
		{ "Infineon JCLX80 jTOP 20ID v2", "3bfe0000008031fe45803180664090a41600008301900000", "ffff00ff00ffffffffffffffffffffffff0000ffffffff00" },
		{ "Infineon JCLX80 jTOP 20ID v3", "3bfe0000008031fe45803180664090a21600008301900000", "ffff00ff00ffffffffffffffffffffffff0000ffffffff00" },
		{ "Infineon JCLX80 jTOP 20ID v3",           "3b8e0001803180664090a21600008301900000", "ffff00ffffffffffffffffff0000ffffffff00" }, // contactless
		{ "Infineon jTOP",                                      "3b888001000000007783b3004e", 0 }, // contactless (JCLX80, SLJ 52GDL, may be others)

		// Infineon CV-ATR
		{ "Infineon SLJ 52GDL 160CL", "3bfc0000008131fe458031cd664090a5102ee0810100", "ffff00ffffffffffffffffffffffffffffffffffff00" },	// T = 1
		{ "Infineon SLJ 52GDL 150CL", "3bfc0000008131fe458031cd664090a5102e10810100", "ffff00ffffffffffffffffffffffffffffffffffff00" },	// T = 1
		{ "Infineon SLJ 52GDL 160CL", "3b7c0000008031cd664090a5102ee08101", "ffff00ffffffffffffffffffffffffffff" },				// T = 0
		{ "Infineon SLJ 52GDL 150CL", "3b7c0000008031cd664090a5102e108101", "ffff00ffffffffffffffffffffffffffff" },				// T = 0

		// TruSign (iEstonia Identity Card)
		{ "Infineon JCLX80 jTOP 20ID v2", "3bfe1000008031fe45803180664090a4162a00830f900000", "fffff0ff00ffffffffffffffffffffffffffffffffffff00" }, // blank card
		{ "Infineon JCLX80 jTOP 20ID v2", "3bf91800008031fe45654944202f20504b49fe", 0 },															// personalized


		// Oberthur
		{ "Oberthur EMV Visa Electron", "3b6d00000031c071d66438d00200849000", 0 },
		{ "Oberthur Galactic V2", "3b7d110000003180718e6452d90100829000", 0 },
		{ "Oberthur Galactic", "3b7d110000003180718e6486d60100819000", 0 },
		{ "Oberthur Galactic", "3b7d110000003180718e6486d90100829000", 0 },
		{ "Oberthur CosmopolIC V4 DoD CAC", "3b7f1100000031c053cac4016452d90400829000", 0 },
		{ "Oberthur Galactic V3", "3b7f1800000031c0739e010b6452d90300829000", 0 },
		{ "Oberthur CosmopolIC", "3b7f1800000031c0739e010b6452d90400829000", 0 },
		{ "Oberthur CosmopolIC 64K v5.2D", "3b7b1800000031c06477e30300829000", 0 },

		// HID
		{ "HID Crescendo C700 (JC2s)", "3bde18ff8031fe458059017f4849444a43327300011b83", 0 },
		{ "HID Crescendo C700 (JC2s)", "3b8f8001804f0ca0000003060a001d000000007f", 0 }, // contactless
		{ "HID Crescendo C700", "3bdf18ff8131fe4580590180484944433730307300011b33", 0 },
		{ "HID Crescendo C700", "3b8f8001804f0ca0000003060a001f000000007d", 0 }, // contactless

		// ORGA
		{ "ORGA OpenPlatform - PK", "3b6600ff4a434f503230", 0 },
		{ "ORGA Micardo EC 2.0", "3b6600ff4d4943323045", 0 },							// warm reset
		{ "ORGA cryptovision card", "3bbc11008030907363762053433a562e312e3043", 0 },
		{ "ORGA cryptovision card", "3bbc11008030907363762053433a562e312e3220", 0 },
		{ "ORGA Micardo P2.1", "3b6f00ff0068d276000028ff051e3180009000", 0 },			// warm reset
		{ "ORGA Micardo EC 2.0", "3bf69400ff8031fe494d49433230459b", 0 },
		{ "ORGA Micardo P2.1", "3bff9400ff80b1fe451f030068d276000028ff051e318000900023", 0 },
		{ "ORGA Micardo EC 2.3", "3bff9400ff80b1fe451f030068d276000028ff052331800090001e", 0 },
	
		// RSA SecurID
		{ "RSA SecurID 3100", "3b1f11806a803446495345539436ff079000", 0 },
		{ "RSA SecurID 5100", "3b76110000009c11010203", 0 },
		{ "RSA SecurID SID800", "3b6f00ff525341536563757249442852293130", 0 },

		// Samsung
		{ "Samsung JavaCard", "3b6800000073c84011009000", 0 },

		// Schlumberger
		{ "Schlumberger Multiflex 3k", "3b021450", 0 },
		{ "Schlumberger Cryptoflex ActivCard Gold", "3b056801010205", 0 },
		{ "Schlumberger Cyberflex Access Augmented Crypto", "3b169481100601812f", 0 },
		{ "Schlumberger Cyberflex Access Crypto", "3b169481100601813f", 0 },
		{ "Schlumberger Cyberflex Access 16K", "3b1694811006010000", "ffffffffffffff0000" },
		{ "Schlumberger Cyberflex Access Developer 32k", "3b17139c120201010740", 0 },
		{ "Schlumberger Multiflex 8k", "3b19145590010101000508b0", 0 },
		{ "Schlumberger Multiflex 4k", "3b19145590010201000504b0", 0 },
		{ "Schlumberger Multiflex 8k", "3b19145901010f01000508b0", 0 },
		{ "Schlumberger Payflex 4k SAM", "3b230000364181", 0 },
		{ "Schlumberger Payflex 1k User", "3b2300351180", 0 },
		{ "Schlumberger Payflex 1k SAM", "3b2300351181", 0 },
		{ "Schlumberger Cyberflex Access Campus", "3b2300351380", 0 },
		{ "Schlumberger MicroPayflex", "3b23003513ff", 0 },
		{ "Schlumberger Multiflex 8k", "3b3215000680", 0 },
		{ "Schlumberger Multiflex 8k DES", "3b3215000695", 0 },
		{ "Schlumberger Payflex 4k User", "3b630000364180", 0 },
		{ "Schlumberger Cyberflex Palmera", "3b6500009c11010103", 0 },
		{ "Schlumberger MicroPayflex S card", "3b6900002494010301000100a9", 0 },
		{ "Schlumberger Cyberflex 32K e-gate", "3b759400006202020101", 0 },
		{ "Schlumberger Cyberflex 32K e-gate", "3b759400006202020201", 0 },
		{ "Schlumberger Cyberflex Access 32K", "3b76110000009c11010202", 0 },
		{ "Schlumberger Cryptoflex Key Generation", "3b8540206801010305", 0 },
		{ "Schlumberger Cryptoflex 8k", "3b8540206801010501", 0 },
		{ "Schlumberger Cryptoflex 8k", "3b8540206801010000", "ffffffffffffff0000" },
		{ "Schlumberger Cryptoflex e-gate", "3b950040ff6201010000", "ffff00ffffffffff0000" },
		{ "Schlumberger Cryptoflex 8k v2", "3b951540006801020000", "ffffffff00ffffff0000" },
		{ "Schlumberger Cryptoflex 32K e-gate", "3b951840ff6201020104", 0 },
		{ "Schlumberger CryptoFlex 32Ko", "3b951840ff6402010102", 0 },
		{ "Schlumberger CryptoFlex 16Ko", "3b959440ff6301010201", 0 },
		{ "Schlumberger Visa Cash card, Bank of America", "3bab00813140458031c0650806800000000084", 0 },
		{ "Schlumberger Cryptoflex DES", "3be2000040204905", 0 },
		{ "Schlumberger Cryptoflex Key Generation", "3be2000040204907", 0 },
		{ "Schlumberger Cryptoflex 4k", "3be2000040204900", "ffffffffffffff00" },

		// SECCOS 6 (Student Card)
		// NOTE: Do not change the order, must be on top of generic SECCOS 6 masked info string
		{ "SECCOS 6 (Student Card)", "3bff9600ff8131fe456563110c5302500010ab0b2123065063", 0 }, // cold, Test Card
		{ "SECCOS 6 (Student Card)", "3bef00ff8131fe456563110c5302500010ab0b21230650e5", 0 },   // warm, Test Card
		{ "SECCOS 6 (Student Card)", "3bff9600ff8131fe456563110c5302500010ab0b214f06500f", 0 }, // cold
		{ "SECCOS 6 (Student Card)", "3bef00ff8131fe456563110c5302500010ab0b214f065089", 0 },   // warm
		{ "SECCOS 6 (Student Card)", "3bff9600ff8131fe456563110c5302500010ab0b2142065002", 0 }, // cold
		{ "SECCOS 6 (Student Card)", "3bef00ff8131fe456563110c5302500010ab0b2142065084", 0 },   // warm

		// SECCOS 6
		{ "SECCOS 6", "3bff0000ff8131fe4565630000000000000000000000000000", "ffff00ffffffffffffffff0000000000000000000000000000" }, // cold
		{ "SECCOS 6", "3bef00ff8131fe4565630000000000000000000000000000", "ffffffffffffffffffff0000000000000000000000000000" }, // warm
		{ "SECCOS 6", "3b8780018031c073d621c033", 0 }, // contactless

		// Siemens
		{ "Siemens SICRYPT Base CSP V2", "3b80000000000000005c504353800000d276000038000000", "ff80000000000000ffffffffff800000ffffffffff000000" },
		{ "Siemens CardOS/M2 V2.01(SLE44CxxS)", "3b8281317643c002c5", 0 },
		{ "Siemens CardOS M2 Combi V2.02 (SLE44R42S)", "3b8281317643c103c5", 0 },
		{ "Siemens CardOS M/V1.4 (SLE44C80S)", "3bb7110081319043a500000000000000", "ffffffffffffffffff00000000000000" },
		{ "Siemens CardOS EM/V1.4 (SLE44CR80S)", "3bb7110081319053b5ffffffffffffff", "ffffffffffffffffff00000000000000" },
		{ "Siemens CardOS M4.0", "3be200ffc11031fe55c8029c", 0 },
		{ "Siemens CardOS M3.0 (SLE66CX160S)", "3be900ffc11031fe55c80120504e34303132ad", 0 },
		{ "Siemens CardOS M4.01 (SLE66CX320P)", "3bf29800ffc11031fe55c80315", 0 },
		{ "Siemens CardOS M4.01a (SLE66CX322P)", "3bf29800ffc11031fe55c80412", 0 },
		{ "Siemens CardOS V4.2", "3bf21800ffc10a31fe55c8068a", 0 },
		{ "Siemens CardOS V4.3", "3bf2180002c10a31fe55c80776", 0 },
		{ "Siemens CardOS V4.3B", "3bf2180002c10a31fe58c80874", 0 },
		{ "Siemens CardOS V4.2B", "3bf2180002c10a31fe58c80975", 0 },
		{ "Siemens CardOS V4.2B DI", "3bf2180002c10a31fe58c80a76", 0 }, // DI
		{ "Siemens CardOS V4.2B DI", "3b8880010000c80a3381b100c8", 0 }, // DI contactless
		{ "Siemens CardOS V4.2C", "3bf2180002c10a31fe58c80b77", 0 },
		{ "Siemens CardOS V4.4", "3bd21802c10a31fe58c80d51", 0 },
		{ "Siemens CardOS V5.0", "3bd218008131fe58c90114", 0 },
		{ "Siemens CardOS V5.3 DI", "3b828001c902c8", 0 }, // contactless
		{ "Siemens CardOS V5.3 DI", "3bd218008131fe58c90217", 0 },
		{ "Siemens CardOS V5.3",    "3bd218008131fe58c90316", 0 },

		{ "Siemens CardOS V4.2", "3bf41800ffc10a31fe555634637635", 0 },							// ATR by cv
		{ "Siemens CardOS V4.3", "3bf4180002c10a31fe5556346376c8", 0 },							// ATR by cv
		{ "Siemens CardOS V4.3B", "3bf4180002c10a31fe5856346376c5", 0 },						// ATR by cv
		{ "Siemens CardOS V4.3B EC", "3bf6180002c10a31fe58563463765f45dd", 0 },					// ATR by cv for ECC
		{ "Siemens CardOS V4.2B", "3bf6180002c10a31fe5856343262637697", 0 },					// ATR by cv
		{ "Siemens CardOS V4.2B DI", "3bf8180002c10a31fe58563432624449637694", 0 },				// ATR by cv
		{ "Siemens CardOS V4.2C", "3bf6180002c10a31fe5856343263637696", 0 },					// ATR by cv
		{ "Siemens CardOS V4.4", "3bd51802c10a31fe585634346376d0", 0 },							// ATR by cv
		{ "Siemens CardOS M4.01(a)", "3bf49800ffc11031fe554d346376b4", 0 },						// ATR by cv
		{ "Siemens CardOS M4.01", "3bf49800ffc11031fe5553696747c2", 0 },						// ATR by cv for SigG
		{ "Siemens CardOS M4.01a MoC", "3bf69800ffc11031fe554d3463765f4da4", 0 },				// ATR by cv for MoC
		{ "Siemens CardOS M4.01a EC", "3bf69800ffc11031fe554d3463765f45ac", 0 },				// ATR by cv for ECC

		{ "Siemens CardOS V4.3B (SwissSign)", "3bfa180002c10a31fe584b53776973735369676e89", 0 },// ATR by SwissSign
		{ "Siemens CardOS V4.4 (SwissSign)", "3bda1802c10a31fe584b53776973735369676ea9", 0 },	// ATR by SwissSign

		{ "Siemens CardOS V4.2", "3bff1800ffc10a31fe55006b0508c806012101434e531031803f", 0 },	// ATR by CNS, 2004.02.20
		{ "Siemens CardOS V4.3", "3bff180002c10a31fe55006b0508c807012101434e53103180c3", 0 },	// ATR by CNS, 2004.02.20
		{ "Siemens CardOS V4.2", "3bff1800ffc10a31fe55006b0508c806011101434e531031800f", 0 },	// ATR by CNS, 2005.03.11
		{ "Siemens CardOS V4.3", "3bff180002c10a31fe55006b0508c807011101434e53103180f3", 0 },	// ATR by CNS, 2005.03.11
		{ "Siemens CardOS V4.3B", "3bff180002c10a31fe58006b0508c808011101434e53103180f1", 0 },	// ATR by CNS, 2005.03.11

		{ "Siemens M3-Module (Motorola SC-28)", "3bef00ff8131604565630402110000000000a532a50111b6", 0 },
		{ "Siemens GeldKarte v2 (Germany)", "3bef00ff8131504565630000000000000000000000000000", "ffffffffffffffffffff0000000000000000000000000000" },

		// Telesec (unsupported)
		{ "Telesec TCOS 1.2", "3ba8008171465d0054434f53312e320065", 0 },
		{ "Telesec TCOS 1.2 CeloCom Card", "3ba8008171465d0054434f53312e324b2e", 0 },
		{ "Telesec TCOS 1.2", "3ba8008171465d0054434f53312e324b2e00", 0 },
		{ "Telesec TCOS 2.01 (SLE44)", "3bba13008131865d0064050a0201318090008b", 0 },
 		{ "Telesec TCOS 2.02 (SLE66)", "3bba14008131865d0064051402023180900091", 0 },
		{ "Telesec TCOS 2.03 (SLE66P)", "3bba96008131865d0064056002033180900066", 0 },
		{ "Telesec TCOS 2.03 (SLE66P)", "3bba96008131865d0064057b0203318090007d", 0 },
		{ "Telesec TCOS 2.xx (USB Token)", "3bba96008131869d00640561020331809000a7", 0 },

		// Telesec / T-Systems
		{ "TCOS 3.0 R1", "3bbf96008131fe5d00640411030131c073f701d00090007d", 0 },
//		{ "TCOS 3.0 R2", "3bbfb6008131fe5d00640428030231c073f701d000900067", 0 },
//		{ "TCOS 3.0 R2", "3b898001006404280302009000d1", 0 },							// contactless ATS
		{ "TCOS 3.0 R4", "00000000000000006405a0030431c073f701d000900000", "00000000000000ffffffffffffffffffffffffffffff00" },
//		{ "TCOS 3.0 R4", "00000000304c47127783d50000", "00000000ffffffffffffffff00" },	// contactless ATQB

		// Mifare
		{ "Mifare Standard (1k EEPROM) - ISO 14443 Type A", "3b8f8001804f0ca000000306030001000000006a", 0 },
		{ "1k contactless Mifare", "3b09410411dd822f000088", 0 },
		{ "Mifare (4k EEPROM)", "3b8f8001804f0ca0000003060300020000000069", 0 },
		{ "Mifare (4k EEPROM)", "3bf59100ff918171fe400041180000001d", 0 },
		{ "Mifare Desfire SAM Module", "3bde18ff81f1fb34001f074445534669726553414d56312e30d2", 0 },
		{ "Mifare ProX T=CL", "3b8680014a434f50333012", 0 },
		{ "Mifare", "3bf59100ff918171fe400041080000000d", 0 },
		{ "Mifare Ultralight", "3bf59100ff918171fe4000410000000005", 0 },
		{ "Mifare DESFire", "3bf79100ff918171fe40004120001177818040", 0 },
		{ "Mifare 1k or 4k", "3bf59100ff918171fe400041880000008d", 0 },

		// others
		{ "Precise Biometrics", "3b959540ffd0001a0101", 0 },							// ???
		{ "CardLogix", "00434C582D313030", 0 },							// ???
		{ "Krankenversicherten Karte", "3b04a2131091", 0 },				// ???
		{ "Nokia branded SC (Setec)", "3b1f110067804246495345105266ff819000", 0 },
		{ "RSA SecurID 3100", "3b1f11806a803446495345539436ff079000", 0 },
		{ "Conax", "3b240000000045", "FFFFFF000000FF" },
		{ "RBS Advanta Platinum Reserve Master Card", "3b6500005801010080", 0 },
		{ "Postbank Chippas (chipknip) Netherlands", "3b6700002920006f789000", 0 },
		{ "Pay-TV card from Casema Cable Television, Netherland", "3f67250026140020689000", 0 },
		{ "Swedish cashcard (proton)", "3b6725002a200040689000", 0 },
		{ "Swedish cashcard (proton)", "3b6725002a200045689000", 0 },
		{ "Bull TB1000", "3b6725006224330300", "ffffffffffffffff00" },	// ???
		{ "SUN SunRay's 370-4328-01", "3b6900002494010201000101a9", 0 },
		{ "PayFlex", "3b6900005792020101000100a9", 0 },					// ???
		{ "PayFlex", "3b69110000005792020101000100", 0 },					// ???
		{ "Lloyds TSB Visa Credit/Debit Card", "3b6a00008031c0a1020301328116", 0 },
		{ "SmartEMV prototype", "3b6b0000003180642da0020c8c6127", 0 },
		{ "Bull Odyssey 1.2 (Javacard 2.0)", "3b6b00000031806443b002008c6127", 0 },
		{ "Datacard Group Aptura Development Card V1.1b", "3b6c0000101010300000000000000000", 0 },
		{ "Navigo (contact mode)", "3b6f0000805a08030300000024220ee7829000", 0 },
		{ "USA DOD-CAC", "3b7d110000003180718e6486d60100819000", 0 },
		{ "Sagem Windows for smart cards", "3b7e130000006a116354054800000001229000", "ffffffffffffffffffffffff000000ffffffff" },
		{ "ticket card for Collogne/Bonn", "3b8281317643c103c5", 0 },
		{ "Telekom Paycard", "3b87813140434d4643203133316f", 0 },
		{ "Setec / FINEID", "3b9f94401e0067114346495345105266ff819000", 0 },
		{ "RSA SecurID 3100", "3b9f94401e0067164346495345105266ff819000", 0 },
		{ "Dallas Semiconductor iButton, JIB", "3bad0040ff80318065b00501015e83009000", 0 },
		{ "SamOS 2.7", "3bb0110081319073f2", 0 },
		{ "GG3RS732S0", "3bba94004014", 0 },								// ???
		{ "Austrian Quick E-purse", "3bbf11008131454545504100000000000000000000000000", "ffffffffffffffffffffffffffffff00000000ffff000000" },
		{ "SmarTEC", "3be000008131204030", 0 },
		{ "VRR Ticket", "3be70000918131fe410110300100908049", 0 },		// ???
		{ "GCOS-MDK", "3bea00ff813120750064051401023100900027", 0 },
		{ "Dutch University accesscard", "3beb0000813142454e4c436853434b303430312b", 0 },
		{ "Dutch Post (Chipper)", "3beb0000813142454e4c4368697070657230310a", 0 },
		{ "Electronic Identification Card from the FNMT", "3bef00004014802543455245535701160101039000", 0 },
		{ "Electronic Purse (Elton Senegal)", "3bef00ff81312045426173696343617264205a43332e33bc", 0 },
		{ "ZeitControl BasicCard Enhanced 2.3", "3bef00ff81312045426173696343617264205a43322e33bd", 0 },
		{ "ZeitControl BasicCard Enhanced 3.3", "3bef00ff81312075426173696343617264205a43332e338c", 0 },
		{ "ZeitControl BasicCard Enhanced 3.7", "3bef00ff81312075426173696343617264205a43332e3788", 0 },
		{ "ZeitControl BasicCard Enhanced 3.9", "3bef00ff81312075426173696343617264205a43332e3986", 0 },
		{ "UNI-Card", "3bef00ff813142450038", "ffffffffffffffff00ff" },
		{ "ZeitControl BasicCard Compact 1.1", "3bef00ff81315045426173696343617264205a43312e31cc", 0 },
		{ "Geldkarte v2", "3bef00ff8131504565630000000000000000000000000000", 0 },
		{ "Geldkarte from Deutsche Bank, Thomson-Chip", "3bef00ff813160456563060314025000065108115e014190", 0 },
		{ "ComCard MFC 4.1", "3bef00ff8131864549424d204d4643343030303038333143", 0 },
		{ "DeLaRue DX", "3bfa110002406043c602f8030300009000", 0 },			// ???
		{ "ESTEID Estonian Identity Card", "3bfe9400ff80b1fa451f034573744549442076657220312e3043", 0 },
		{ "Acer TravelMate", "3bff110000817140420000210131425200006300000000900000", "ffffffffffffffffffffffffffffffffffffff00000000ffffff" },
		{ "Acer TravelMate", "3bff110000817140420000210131425200056300000000900000", "ffffffffffffffffffffffffffffffffffffff00000000ffffff" },
		{ "Stadtsparkasse Haltern Maestrocard/Geldkarte", "3bff1300ff8131fe45656311045002800008540004230502a5", 0 },
		{ "Postbank Maestrocard/Geldkarte", "3bff1800ff81313c4565630d02310250001090002600041009", 0 },
		{ "Geldkarte (Germany)", "3bff1800ff81313c4565630d02310280001224300020041059", 0 },
		{ "Landesbank baden-Württemberg Geldkarte", "3bff1800ff8131fe4565630d0450028000089009700005002a", 0 },
		{ "Geldkarte v3 (Germany)", "3bff1800ff8131504565630000000000000000000000000000", "ffffffffffffffffffffff0000000000000000000000000000" },
		{ "Citizencard of the People of Ulm in Germany", "3bff9400ff80b1fe451f030068d276000028ff051e318000900023", 0 },
		{ "DigiCash Facility Card", "3f05dc20fc0001", 0 },
		{ "Porta Moedas Multibanco", "3f2d0027a051827d00000052000c9000", 0 },
		{ "D-Trust card", "3f6525083304209000", 0 },
		{ "Sesam Vitale (french health card)", "3f6525002209699000", 0 },
		{ "Sesam Vitale (french health card)", "3f6525002209f99000", 0 },
		{ "Sesam Vitale (french health card)", "3f6525002c09699000", 0 },
		{ "Sesam Vitale (french health card)", "3f6525002c09f99000", 0 },
		{ "Bull Scot 5", "3f6525002b09eb9000", 0 },
		{ "France Telecom card (ex Pastel card)", "3f6525082204689000", 0 },
		{ "Carte Bancaire (french banking card)", "3f65250000046c9000", "3F65250000046C9000" },
		{ "Postcard (Switzerland)", "3f65356402046c9040", 0 },
		{ "Carte Grand Voyageur (SNCF)", "3f6725002a20000f689000", 0 },
		{ "Swiss Cash card", "3f6725002a200040689f00", 0 },
		{ "Dutch ChipKnip, Proton", "3f6725002a200040689000", 0 },
		{ "Dutch ChipKnip, Proton", "3f6725002a200041689000", 0 },
		{ "DTV Card P1", "3f7613250421b0114a5003", 0 },
		{ "Viaccess card", "3f7718250029140062689000", 0 },
		{ "DTV Card P2", "3f7812250140b0034a50204855", 0 },
		{ "DTV Card P4", "3f7813250340b020ffff4a5000", 0 },
		{ "DTV Card P3", "3f7f13250338b004ffff4a500000294855550000", 0 },
		{ "BSkyB Series 11 (DSS satellite TV card)", "3f7e11250540b00800004d59000000534b0b07", 0 },
		{ "ExtremeHu3 (DSS satellite TV card)", "3f7f13250338b004ffff4a500000294855000000", "ffffffffffffffffffffffffffffffffff000000" },
		{ "NTL digial TV card (Nagravision)", "3fff9500ff918171a04700444e4153503031312052657642", 0 },

		// end of map
		{ 0, 0, 0 }
	};

} // namespace act

#endif // ACT_SCARDINFO_H
