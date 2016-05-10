//////////////////////////////////////////////////////////////////////////////////
// Name:      actISecretKeyMACKey.h
// Product:   cv act library
// Purpose:   interface for the class CBCMAC
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ISecretKeyMACKey_h
#define ACT_ISecretKeyMACKey_h

#include "actIMACKey.h"

namespace act
{
	class IBlockCipherKey;

	class ISecretKeyMACKey : public IMACKey
	{
	public:
		virtual void SetCipherKey(IBlockCipherKey* cipher) = 0;
		virtual const IBlockCipherKey* GetCipherKey() const = 0;
		virtual IBlockCipherKey* GetCipherKey() = 0;
	};

} // namespace act

#endif // ACT_ISecretKeyMACKey_h
