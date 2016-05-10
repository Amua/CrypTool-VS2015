// ---------------------------------------------------------------------------
// Name:      actISCardBehavior.h
// Product:   cv act library
// Purpose:   Interfaces for smartcard key behavior.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/28/2010
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardBehavior_h
#define ACT_ISCardBehavior_h

#include "actBlob.h"
#include "actTokenBase.h"

#include "actIRefCounted.h"

namespace act
{
	class ISCardOS;

	class ITokenFile;
	class ITokenKey;
	class ITokenBlockCipher;
	class ITokenBlockCipherKey;

	class SCardToken;

	//
	// scmd_mse
	struct scmd_mse
	{
		ProfileType	pt;
		int			mode;
		byte		ofs_keyid;
		byte		ofs_algid;
		byte		p1;
		byte		p2;
		byte_array	data;
	};

	//
	// ISCardBehavior
	class ISCardBehavior : public IRefCounted
	{
	protected:
		virtual ~ISCardBehavior() { }

	public:
		virtual void SelectKey(SCardToken* token, ITokenFile* file) const = 0;
		virtual void Encrypt(const ITokenBlockCipher* cipher, const byte* in, byte* out) const = 0;
		virtual void Decrypt(const ITokenBlockCipher* cipher, const byte* in, byte* out) const = 0;
		virtual void ManageSecurityEnvironment(const ITokenBlockCipherKey* key, const FileInfo& fi, int mode) const = 0;
		virtual void ManageSecurityEnvironment(const ITokenKey* key, const FileInfo& fi, int mode, byte alg_id) const = 0;
	};

} // namespace act

#endif // ACT_ISCardBehavior_h
