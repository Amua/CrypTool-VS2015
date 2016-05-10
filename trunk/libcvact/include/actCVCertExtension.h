//////////////////////////////////////////////////////////////////////////////////
// Name:      actCVCertExtension.h
// Product:   cv act library
// Purpose:   Implements CV Certificate Extension handling according to TR-03110-3, v2.10
//
// Copyright: (c) 2014 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_CVCertExtension_H
#define ACT_CVCertExtension_H

#include "actBlob.h"

namespace act
{
	class CVCertExtension
	{
	public:
		CVCertExtension();
		CVCertExtension(const Blob& oid, const Blob& value);
		CVCertExtension(const char* oid, const Blob& value);

		void GetOID(Blob& oid) const;
		void GetOIDString(Blob& oid) const;
		void SetOID(const Blob& oid); 
		void SetOIDString(const char* oid);
		
		void GetValue(Blob& value) const;	// value contains a concatenation of n context specific
		void SetValue(const Blob& value);	// data objects (octet strings including tag and length)

		Blob GetDataObject(size_t i) const;	// returns the value of data object i = 0, 1, ...

		void GetDER(Blob& der) const;
		void SetDER(const Blob& der);

		bool IsPresent() const { return !mValue.empty(); }

	private:
		Blob mOID;
		Blob mValue;
	};

} // namespace act

#endif // ACT_CVCertExtension_H
