// ---------------------------------------------------------------------------
// Name:      actIAuthConstraints.h
// Product:   cv act library
// Purpose:   Interface for authentication object constraints.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  11/17/2009
// ---------------------------------------------------------------------------

#ifndef ACT_IAuthConstraints_h
#define ACT_IAuthConstraints_h

#include "actITokenAuth.h"

namespace act
{
	//
	// IAuthConstraints
	class IAuthConstraints : public IAuthIdRef
	{
	public:
		typedef IAuthIdRefIterator IIterator;

		virtual ITokenFile* GetPath() const = 0;
		virtual AuthConstrainedType GetType(AuthConstrainedMode mode) const = 0;
		virtual void AddConstraint(IAuthIdRef* authIdRef, AuthConstrainedMode mode) = 0;

		/*!
		 * Check authentication constraints.
		 *
		 * \param	auth to check contraints with.
		 * \param   mode to check constrains for.
		 * \return	\a IAuthIdRef of constraint violator, NULL otherwise.
		 */
		virtual IAuthIdRef* Check(ITokenAuth* auth, AuthConstrainedMode mode) const = 0;

		virtual IIterator* Iterator(AuthConstrainedMode mode) const = 0;
	};

} // namespace act

#endif // ACT_IAuthConstraints_h
