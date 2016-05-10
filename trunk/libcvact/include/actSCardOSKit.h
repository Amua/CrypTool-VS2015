// ---------------------------------------------------------------------------
// Name:      actSCardOSKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS object
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/13/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardOSKit_h
#define ACT_SCardOSKit_h

namespace act
{
	class ISCardOS;
	class ISCardAccess;

	/*
	ISCardOS* CreateMicardOS(ISCardAccess*);
	ISCardOS* CreateMicardo20E(ISCardAccess*);
	ISCardOS* CreateMicardo23E(ISCardAccess* ac);
	*/

	bool IsACOS(CreateSCardOSPtr ptr);
		ISCardOS* CreateACOS_D01(ISCardAccess*);
		ISCardOS* CreateACOS_A04(ISCardAccess*);

	bool IsCardOS_M4(CreateSCardOSPtr ptr);
		ISCardOS* CreateCardOS_M4(ISCardAccess*);
		ISCardOS* CreateCardOS_M4_MoC(ISCardAccess*);

	bool IsCardOS_M4_ECC(CreateSCardOSPtr ptr);
		ISCardOS* CreateCardOS_M4_ECC(ISCardAccess*);

	bool IsCardOS_V4(CreateSCardOSPtr ptr);
		ISCardOS* CreateCardOS_V4(ISCardAccess*);

	bool IsCardOS_V4_ECC(CreateSCardOSPtr ptr);
		ISCardOS* CreateCardOS_V4_ECC(ISCardAccess*);

	bool IsSECCOS(CreateSCardOSPtr ptr);
		ISCardOS* CreateSECCOS_5(ISCardAccess*);
		bool      DetectSECCOS_5(const Blob&, ISCardAccess*);
		ISCardOS* CreateSECCOS_6(ISCardAccess*);
		bool      DetectSECCOS_6(const Blob&, ISCardAccess*);

	bool IsStarCOS(CreateSCardOSPtr ptr);
		ISCardOS* CreateStarCOS_2_3(ISCardAccess*);
		ISCardOS* CreateStarCOS_2_4(ISCardAccess*);
		ISCardOS* CreateStarCOS_3_0(ISCardAccess*);
		ISCardOS* CreateStarCOS_3_1(ISCardAccess*);
		ISCardOS* CreateStarCOS_3_2(ISCardAccess*);
		ISCardOS* CreateStarCOS_3_4(ISCardAccess*);
		ISCardOS* CreateStarCOS_3_5(ISCardAccess*);

	bool IsTCOS(CreateSCardOSPtr ptr);
		ISCardOS* CreateTCOS_3_0_1(ISCardAccess*);
		ISCardOS* CreateTCOS_3_0_2(ISCardAccess*);
		ISCardOS* CreateTCOS_3_0_4(ISCardAccess*);

	//
	// Java Card
	// ---------------------------------------------------------------------------
	bool IsJavaCardOS(CreateSCardOSPtr ptr);
		ISCardOS* CreateJavaCardOS_3_0_4(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_3_0_3(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_3_0_2(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_3_0_1(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_3_0(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_2_2(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_2_1(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_2(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_1_2(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_1_1(ISCardAccess*);
		ISCardOS* CreateJavaCardOS_2_1(ISCardAccess*);

		ISCardOS* DeriveJavaCardOS_ECC(ISCardOS*);

	bool IsCVEPS(CreateSCardOSPtr);
		ISCardOS* CreateCVEPS(ISCardAccess*);
		ISCardOS* CreateJCOP_CVEPS_1_0_0(ISCardAccess*);
		ISCardOS* CreateJCOP_CVEPS_1_0_1(ISCardAccess*);

	bool DetectCVEPS(const Blob&, ISCardAccess*);

	//
	// ISO 7816 OS - Fallback
	// ---------------------------------------------------------------------------
	bool IsISO7816OS(CreateSCardOSPtr);
		ISCardOS* CreateISO7816OS(ISCardAccess*);

	//
	// Passport OS
	// ---------------------------------------------------------------------------
	bool IsBACOS(CreateSCardOSPtr);
		ISCardOS* CreateBACOS(ISCardAccess* ac);

	bool IsEACOS(CreateSCardOSPtr);
		ISCardOS* CreateEACOS(ISCardAccess* ac);

	bool IsEACOS201(CreateSCardOSPtr);
		ISCardOS* CreateEACOS201(ISCardAccess* ac);

	bool IsEACOS210(CreateSCardOSPtr);
		ISCardOS* CreateEACOS210(ISCardAccess* ac);

	bool IsEPAOS(CreateSCardOSPtr);
		ISCardOS* CreateEPAOS(ISCardAccess* ac);


	// ---------------------------------------------------------------------------
	inline bool IsACOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateACOS_D01
			|| ptr == CreateACOS_A04;
	}

	// ---------------------------------------------------------------------------
	inline bool IsCardOS_M4(CreateSCardOSPtr ptr)
	{
		return ptr == CreateCardOS_M4
			|| ptr == CreateCardOS_M4_MoC;
	}

	// ---------------------------------------------------------------------------
	inline bool IsCardOS_M4_ECC(CreateSCardOSPtr ptr)
	{
		return ptr == CreateCardOS_M4_ECC;
	}

	// ---------------------------------------------------------------------------
	inline bool IsCardOS_V4(CreateSCardOSPtr ptr)
	{
		return ptr == CreateCardOS_V4;
	}

	// ---------------------------------------------------------------------------
	inline bool IsCardOS_V4_ECC(CreateSCardOSPtr ptr)
	{
		return ptr == CreateCardOS_V4_ECC;
	}

	// ---------------------------------------------------------------------------
	inline bool IsSECCOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateSECCOS_5
			|| ptr == CreateSECCOS_6;
	}

	// ---------------------------------------------------------------------------
	inline bool IsStarCOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateStarCOS_2_3
			|| ptr == CreateStarCOS_2_4
			|| ptr == CreateStarCOS_3_0
			|| ptr == CreateStarCOS_3_1
			|| ptr == CreateStarCOS_3_2
			|| ptr == CreateStarCOS_3_4
		    || ptr == CreateStarCOS_3_5;
	}

	// ---------------------------------------------------------------------------
	inline bool IsTCOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateTCOS_3_0_1
			|| ptr == CreateTCOS_3_0_2
			|| ptr == CreateTCOS_3_0_4;
	}

	// ---------------------------------------------------------------------------
	inline bool IsJavaCardOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateJavaCardOS_3_0_4
			|| ptr == CreateJavaCardOS_3_0_3
			|| ptr == CreateJavaCardOS_3_0_2
			|| ptr == CreateJavaCardOS_3_0_1
			|| ptr == CreateJavaCardOS_3_0
			|| ptr == CreateJavaCardOS_2_2_2
			|| ptr == CreateJavaCardOS_2_2_1
			|| ptr == CreateJavaCardOS_2_2
			|| ptr == CreateJavaCardOS_2_1_2
			|| ptr == CreateJavaCardOS_2_1_1
			|| ptr == CreateJavaCardOS_2_1
			|| IsCVEPS(ptr);
	}

	// ---------------------------------------------------------------------------
	inline bool IsCVEPS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateCVEPS
			|| ptr == CreateJCOP_CVEPS_1_0_0
			|| ptr == CreateJCOP_CVEPS_1_0_1;
	}

	// ---------------------------------------------------------------------------
	inline bool IsISO7816OS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateISO7816OS;
	}

	//
	// Passport OS
	// ---------------------------------------------------------------------------
	inline bool IsBACOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateBACOS;
	}

	// ---------------------------------------------------------------------------
	inline bool IsEACOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateEACOS;
	}

	// ---------------------------------------------------------------------------
	inline bool IsEACOS201(CreateSCardOSPtr ptr)
	{
		return ptr == CreateEACOS201;
	}

	// ---------------------------------------------------------------------------
	inline bool IsEACOS210(CreateSCardOSPtr ptr)
	{
		return ptr == CreateEACOS210;
	}

	// ---------------------------------------------------------------------------
	inline bool IsEPAOS(CreateSCardOSPtr ptr)
	{
		return ptr == CreateEPAOS;
	}

} // namespace act

#endif // ACT_SCardOSKit_h
