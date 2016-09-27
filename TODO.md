# CrypTool-VS2015 TODO List

This document contains the most important TODOs for the project.

## Documentation

- update **CrypTool-MFC-Kurs-VC7.ppt** in CrypTool root folder, translate it into English and publish it as a PDF instead of a PPT, and move the result into the master branch with a reference to it in the DEVELOPERS document
- extract information from **readme-source.txt** in CrypTool root folder and integrate it into DEVELOPERS document, in particular the sections about the online help, and then remove the original file
- ~~extend developer documentation with instructions for NSIS (remove documents in 'setup' folder)~~

## Licensing

- remove obsolete licensing files (may be cluttered across the whole code base)
- update licensing information in installer (license-{LANGUAGE}.rtf files): move version information to 1.5, and remove all obsolete information (such as references to Secude, for example)

## Code

- implement OpenSSL-based abstraction layer to replace legacy code (see CrypToolBase.{h|cpp} files) [**WIP**]
- sanitize VS2015 project files (remove obsolete files, unify build configurations, etc.)
- ~~fix resource compiler warnings (i.e. complaints about resource strings being too long, etc.)~~
- remove MD2 implementations (no longer supported by updated OpenSSL version)
- replace all instances of "CRYPTOOL_BASE" with the appropriate resource strings, but don't bother with this until the source is set for release as the constant refactoring may make maintaining the intended naming convention (i.e. CRYPTOOL_BASE_UTILITIES_xxx, CRYPTOOL_BASE_CRYPTOGRAPHY_xxx, etc.) a nightmare
- speed up the CrypTool::ByteString implementation: the constant re-allocation of memory, for example when concatenating byte strings, is significantly dragging down overall performance (this is particularly evident when using the key from password dialog with an iteration count of 10000 or higher)
- the implementations for hashing documents (the threaded ones) are leaking memory somewhere, investigate and fix it
- finish refactoring symmetric cryptography: MARS, RC6, Serpent, Twofish, DESX (supported by OpenSSL!), DESL, DESXL
- finish refactoring asymmetric cryptography: improve error checking and user notification (i.e. when entering a wrong private key password, etc...)
- implement replacement for Secude's PSE: finish "CertificateStore" implementation (adhere to OpenSSL CLI output for parameter display, honor custom CrypTool certificate extensions for PKCS#12 import/export, etc...)
- fix side-channel attack implementation: internally, everything Secude-related has been replaced with new byte-string-based implementations, but the attack doesn't work correctly yet, and for some reason it's prone to crashing
- add user feedback for symmetric decryption: if the user enters a wrong key, nothing happens (at least nothing the user can see) because internally OpenSSL throws an error due to padding-related errors; one option would be to simply display an error message, another would be to also dump the (partial) result of the failed decryption process
- implement digital signatures: sign, verify, and extract operations as well as the signature demo visualization [**WIP**]
- fix monospaced fonts in signature extraction dialog; after doing so, maybe move the whole monospaced font functionality into the Utilities namespace of the base layer

## Resources

- REMEMBER: most of the refactored sections only work for the German version, other languages have not been adapted yet to avoid redundant changes in the CrypTool resource file, dealing with Visual Studio's airs and graces is cumbersome enough for a single language
- when everything is said and done, make sure there a NO MORE WARNINGS caused by the resource compiler


## Other

- ~~implement new versioning scheme (i.e. 1.5.x with information from git repository)~~
- clean up the 'setup/template' folder (VS9.0, Secude, etc.) and make sure it's copied into the build folder at build time as a whole, not just the contained DLLs
- rename 'script' folder into 'ctbook' (make sure to handle all side effects)

## Known Crashes and Other Problems

- if the online help is invoked by pressing F1 when hovering over a menu (not a menu item!), CrypTool crashes
- side-channel attack implementation is not yet final, but it shouldn't crash regardless (it does when trudy reaches a certain number of forged messages)
- digital signatures won't work for RIPEMD160; don't know if this is an OpenSSL problem or a problem with my implementation

## IMPORTANT

All the legacy code which has not been refactored yet is deactivated using the **_UNSTABLE** preprocessor definition. Please do not remove this definition from any of the individual VS2015 project files as long as not all the code has been refactored properly.
