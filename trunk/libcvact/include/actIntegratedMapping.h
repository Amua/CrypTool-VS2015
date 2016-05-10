//////////////////////////////////////////////////////////////////////////////////
// Name:      actIntegratedMapping.h
// Product:   cv act library
// Purpose:   functions for PACE Integrated Mapping
//
// Copyright: (c) 2014 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IntegratedMapping_h
#define ACT_IntegratedMapping_h

#include "actMode.h"
#include "actBlob.h"
#include "actIKey.h"

namespace act
{
	//
	// References: 
	// [1] ICAO-TR Supplemental Access Control for Machine Readable 
	//     Travel Documents, Release 1.01, November 2010
	// [2] ICAO-SUPPLEMENT 9303, Release 12, April 2013


	//
	// PACE-(EC)DH Integrated Mapping random function Rp(s, t), ICAO [1], [2]
	//
	// Returns a random field element x, 0 < x < p for (EC)DH keys.
	// PACE nonce s and nonce t must be choosen according to ICAO [1], [2].
	// Use the 'AES' or 'TripleDES' cipher string (refer actInit.h factory).
	Blob IMRandomFunction(IKey* key, const char* cipher,
		const Blob& s, const Blob& t); 

	//
	// PACE-(EC)DH Integrated Mapping function fG(x), 0 < x < p, ICAO [1], [2]
	//
	// For DH keys:
	// - Returns a mapped field element g of subprime order.
	// 
	// For ECDH keys:
	// - Returns a mapped curve point G of prime order.
	// - G will be in ASN.1 encoding as indicated in 'output_format'.
	Blob IMMappingFunction(IKey* key, const Blob& x,
		int output_format = UNCOMPRESSED); 

} // namespace act

#endif // ACT_IntegratedMapping_h
