// ---------------------------------------------------------------------------
// Name:      actITokenFile.h
// Product:   cv act library
// Purpose:   ITokenFile represents a simple smartcard file with path.
//            
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  09/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_TokenFile_h
#define ACT_TokenFile_h

#include "actBlob.h"
#include "actBool.h"
#include "actTokenBase.h"
#include "actIRefCounted.h"

namespace act
{
	class ISCardOS;

	//!
	//! \interface ITokenFile
	// ---------------------------------------------------------------------------
	class ITokenFile : public IRefCounted
	{
	public:
		virtual ITokenFile*		Clone() const = 0;

		virtual bool			Equals(const Blob& path) const = 0;
		virtual bool			Equals(const ISCardOS* os) const = 0;
		virtual bool			Equals(const ITokenFile* other) const = 0;

		virtual bool			IsValid() const = 0;
		virtual bool			IsParent(const ITokenFile* other, Blob& diffpath) const = 0;
		virtual bool			IsParent(const ITokenFile* other, size_t* mismatch = 0) const = 0;

		virtual Blob&			RefCP() = 0;
		virtual const Blob&		GetCP() const = 0;

		virtual Blob&			RefAID() = 0;
		virtual const Blob&		GetAID() const = 0;

		virtual FileType		GetFileType() const = 0;
		virtual size_t			GetFileLength() const = 0;
		virtual const Blob&		GetFilePath() const = 0;
		virtual size_t			GetFullLength() const = 0;
		virtual size_t			GetFullPath(Blob& path) const = 0;

		virtual ITokenFile*		GetRelativeTo() const = 0;
		virtual ITokenFile*		SetRelativeTo(ITokenFile* other) = 0;
		virtual ITokenFile*		MakeRelativeTo(ITokenFile* parent) = 0;
		virtual BOOLean			IsRelativeTo(ITokenFile* other) const = 0;

		virtual void			SetFilePath(const Blob& filepath, FileType filetype) = 0;
		virtual void			SetFilePath(move_from<Blob> filepath, FileType filetype) = 0;

		virtual const Blob&		SelectApp(ISCardOS* os, int selectmode) = 0;
		virtual const Blob&		SelectFile(ISCardOS* os, int selectmode) = 0;

		virtual bool			ProbeFilePath(ISCardOS* os, bool cut_non_existing) = 0;
	};

} // namespace act

#endif // ACT_TokenFile_h
