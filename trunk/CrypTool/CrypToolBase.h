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

#ifndef _CRYPTOOLBASE_H_
#define _CRYPTOOLBASE_H_

// flomar, April 2016: during the switch from VS2010 to VS2015, we define 
// the "_UNSTABLE" preprocessor macro in all (!) projects contained in the 
// CrypTool solution; if this macro is defined, certain parts of the code 
// are temporarily inactive in order to compile the code base under VS2015 
// and without "LibEC" and "LibSecude". PLEASE MAKE SURE ALL OCCURENCES OF 
// THIS DEFINITION ARE PROPERLY RESOLVED BEFORE THE CODE IS RELEASED!!!

#include <stdint.h>

// this struct encapsulates an octet string
struct OctetString {
	// construction
	OctetString();
	// the number of octets stored in this octet string (default: zero)
	uint32_t noctets;
	// the actual data (default: zero)
	char *octets;
};

// this namespace encapsulates OpenSSL functionality
namespace OpenSSL {
	// 1. implement hash Functions (note: remove MD2 implementation from legacy code)
	// 2. implement symmetric Cryptography
	// 3. implement asymmetric Cryptography
	// 4. implement certificates (replacement for Secude PSEs)
	// ...
}

#endif
