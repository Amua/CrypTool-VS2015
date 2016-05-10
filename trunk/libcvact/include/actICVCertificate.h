//////////////////////////////////////////////////////////////////////////////////
// Name:      actICVCertificate.h
// Product:   cv act library
// Purpose:   Implements CV Certificate handling according to BSI TR-03110-3, v2.10
//
// Copyright: (c) 2014 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ICVCertificate_h
#define ACT_ICVCertificate_h

#include "actBasics.h"
#include "actICertificate.h"
#include "actCVCertExtension.h"

namespace act
{
	class IKey;
	class Blob;
	class Date;

	enum CVCertTags
	{
		CV_CERT_TAG									= 0x7F21,
		CV_CERT_BODY_TAG							= 0x7F4E,
		CV_CERT_PROFILE_ID_TAG						= 0x5F29,
		CV_CERT_AUTH_REF_TAG						= 0x42,
		CV_CERT_PUBKEY_TAG							= 0x7F49,
		CV_CERT_HOLDER_REF_TAG						= 0x5F20,
		CV_CERT_HOLDER_AT_TAG						= 0x7F4C,
		CV_CERT_EFFECTIVE_DATE_TAG					= 0x5F25,
		CV_CERT_EXPIRATION_DATE_TAG					= 0x5F24,
		CV_CERT_SIGNATURE_TAG						= 0x5F37,

		// extension tags
		CV_CERT_EXTENSIONS_TAG						= 0x65,
		CV_CERT_DISCRETIONARY_DATA_TEMPLATE_TAG		= 0x73
	};

	class ICVCertificate : public ICertificate
	{
	public:
		virtual ICVCertificate* Clone() const = 0;

		virtual void SetEffectiveDate(const Date& effective) = 0;	// NotBefore
		virtual void SetExpirationDate(const Date& expiration) = 0; // NotAfter
		virtual void GetEffectiveDate(Date& effective) const = 0;
		virtual void GetExpirationDate(Date& vnafter) const = 0;

		virtual bool CheckValidity(const Date& date) const = 0;

		virtual void SetProfileIdentifier(int pi) = 0;
		virtual int GetProfileIdentifier() const = 0;

		virtual void SetCAReference(const char* issuer) = 0;
		virtual void SetCAReference(const Blob& issuer) = 0;
		virtual void GetCAReference(Blob& issuer) const = 0;

		virtual void SetHolderReference(const char* subject) = 0;
		virtual void SetHolderReference(const Blob& subject) = 0;
		virtual void GetHolderReference(Blob& subject) const = 0;

		virtual void SetHolderAuthorizationTemplate(const Blob& chat) = 0;
		virtual void GetHolderAuthorizationTemplate(Blob& chat) const = 0;

		virtual void SetEACePassportTemplate(byte mask) = 0;
		virtual byte GetEACePassportTemplate() const = 0;

		virtual void SetPublicKeyTLV(const Blob& pktlv) = 0;
		virtual void GetPublicKeyTLV(Blob& pktlv) const = 0;
		virtual void GetPublicKeyMechanism(Blob& oid) const = 0;

		virtual void GetEncodedSignature(Blob& tlv_sig) const = 0;
		virtual void GetSignature(Blob& sig) const = 0;
		virtual void SetSignature(const Blob& sig) = 0;

		virtual void GetTBSCertificate(Blob& tbs_cert) const = 0;

		virtual CVCertExtension GetExtension(const char* oid) const = 0;
		virtual CVCertExtension GetExtension(const act::Blob& oidbl) const = 0;
		virtual void SetExtension(const CVCertExtension &ext) = 0;
		virtual CVCertExtension GetNextExtension(const CVCertExtension& ext) const = 0;
		virtual void RemoveExtension(const char* oid) = 0;
	};

} // namespace act

#endif // ACT_ICVCertificate_h
