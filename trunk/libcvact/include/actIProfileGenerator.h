// ---------------------------------------------------------------------------
// Name:      actIProfileGenerator.h
// Product:   cv act library
// Purpose:   IProfileGenerator interface, used togehter with ITokenInitializer
//			  to write a profile to the token, f.e. PKCS#15 etc.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/27/2009
// ---------------------------------------------------------------------------

#ifndef ACT_IProfileGenerator_h
#define ACT_IProfileGenerator_h

#include "actISCardCmdEvtSrc.h"
#include "actITokenInitializer.h"

namespace act
{
	class EFDIR;
	class ISCardOS;
	class ITokenFile;

	//
	// IProfileGenerator
	class IProfileGenerator : public ISCardCmdEvtSrc
	{
	public:
		virtual ITokenFile* GetPath() const = 0;
		virtual void GetNamedAC(NamedAC ac, Blob& value) = 0;

		virtual bool Supports(const TIData& data) const = 0;

		virtual void Prepare(TIData& data, EFDIR* ef_dir) const = 0;
		virtual void Prepare(TIData& data, ISCardOS* os) = 0;
		virtual void WriteProfile(ISCardOS* os) = 0;

		virtual void Finalize(TIData& data, ISCardOS* os) = 0;
	};

} // namespace act

#endif // ACT_IProfileGenerator_h
