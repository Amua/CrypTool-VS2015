# CrypTool-VS2015 TODO List

This document contains the most important TODOs for the project.

## Documentation

- update **CrypTool-MFC-Kurs-VC7.ppt** in CrypTool root folder, translate it into English and publish it as a PDF instead of a PPT, and move the result into the master branch with a reference to it in the DEVELOPERS document
- extract information from **readme-source.txt** in CrypTool root folder and integrate it into DEVELOPERS document, in particular the sections about the online help, and then remove the original file
- ~~extend developer documentation with instructions for NSIS (remove documents in 'setup' folder)~~

## Licensing

- remove obsolete licensing files (may be cluttered across the whole code base)

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

## Resources

- REMEMBER: most of the refactored sections only work for the German version, other languages have not been adapted yet to avoid redundant changes in the CrypTool resource file, dealing with Visual Studio's airs and graces is cumbersome enough for a single language
- when everything is said and done, make sure there a NO MORE WARNINGS caused by the resource compiler


## Other

- ~~implement new versioning scheme (i.e. 1.5.x with information from git repository)~~
- clean up the 'setup/template' folder (VS9.0, Secude, etc.) and make sure it's copied into the build folder at build time as a whole, not just the contained DLLs
- rename 'script' folder into 'ctbook' (make sure to handle all side effects)

## Known Crashes

- if the online help is invoked by pressing F1 when hovering over a menu (not a menu item!), CrypTool crashes

## IMPORTANT

All the legacy code which has not been refactored yet is deactivated using the **_UNSTABLE** preprocessor definition. Please do not remove this definition from any of the individual VS2015 project files as long as not all the code has been refactored properly.
