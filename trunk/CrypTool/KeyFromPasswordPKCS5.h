/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#ifndef _KEYFROMPASSWORDPKCS5_H_
#define _KEYFROMPASSWORDPKCS5_H_

#include <string.h>
#include <math.h>

// original implementation: Roger Oyono, 2001
class CKeyFromPasswordPKCS5 {
public:
	CKeyFromPasswordPKCS5();
	virtual ~CKeyFromPasswordPKCS5();
public:
	int password_based_key_deriv_funct(CString Passwort, CString Salt, CString dkLen, int AlgId, CString zaehler);
public:
	char *str1;
	OctetString Salt_octetstring;
	OctetString help3;
	OctetString help2;
	OctetString Passwort_octetstring;
	OctetString hash;
	char *str;
	int err;
#ifndef _UNSTABLE
	L_NUMBER hashwert[MAXLGTH];
#endif
	int base;
};

#endif
