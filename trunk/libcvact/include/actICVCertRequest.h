//////////////////////////////////////////////////////////////////////////////////
// Name:      actICVCertificate.h
// Product:   cv act library
// Purpose:   Implements CV Certificate Request handling according to TR-03110-3, v2.10
//
// Copyright: (c) 2014 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ICVCertRequest_h
#define ACT_ICVCertRequest_h

#include "actICVCertificate.h"

namespace act
{

	class ICVCertRequest
	{
	public:
		virtual ICVCertificate* GetReducedCVCertificate() =0;
		virtual const ICVCertificate* GetReducedCVCertificate() const =0;

		virtual void SetCAReference(const char* issuer ) =0;
		virtual void SetCAReference(const Blob& issuer ) =0;
		virtual void GetCAReference(Blob& issuer ) const =0;

		virtual void GetSignature(Blob& sig) const =0;
		virtual void SetSignature(const Blob& sig) =0;
		virtual bool IsAuthenticated() const =0;

		virtual void Import(const Blob& certblob) =0;
		virtual void Export(Blob& certblob) const =0;

		virtual void Sign(const IKey* privkey) =0;
		virtual int Verify(const IKey* pubkey) const =0;

		virtual ICVCertRequest* Clone() const=0;
		virtual ~ICVCertRequest() {}
		virtual void* GetCreatePointer() const=0;
	};
} // namespace act

#endif

