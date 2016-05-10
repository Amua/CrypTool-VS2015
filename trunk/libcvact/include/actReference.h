// ---------------------------------------------------------------------------
// Name:      actReference.h
// Product:   cv act library
// Purpose:   Simple reference counting base class.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  1/18/2006
// ---------------------------------------------------------------------------

#ifndef ACT_Reference_h
#define ACT_Reference_h

namespace act
{
	class Reference
	{
	protected:
		Reference(long ref_cnt = 0) : m_ref_cnt(ref_cnt) { }
		Reference(const Reference& other) : m_ref_cnt(0) { }

	public:
		virtual ~Reference()	{ }
		long add()				{ return ++m_ref_cnt; }
		long remove()			{ return --m_ref_cnt; }
		long getCount() const	{ return   m_ref_cnt; }

	private:
		volatile long m_ref_cnt;
	};
}

#endif // ACT_Reference_h
