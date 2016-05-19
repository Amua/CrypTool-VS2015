# CrypTool-VS2015 TODO List

This document contains the most important TODOs for the project.

## Documentation

- update **CrypTool-MFC-Kurs-VC7.ppt** in CrypTool root folder, translate it into English and publish it as a PDF instead of a PPT, and move the result into the master branch with a reference to it in the DEVELOPERS document
- extract information from **readme-source.txt** in CrypTool root folder and integrate it into DEVELOPERS document, in particular the sections about the online help, and then remove the original file
- ~~extend developer documentation with instructions for NSIS (remove documents in 'setup' folder)~~

## Licensing

- remove obsolete licensing files (may be cluttered across the whole code base)

## Code

- sanitize VS2015 project files (remove obsolete files, unify build configurations, etc.)
- fix resource compiler warnings (i.e. complaints about resource strings being too long, etc.)
- remove MD2 implementations (no longer supported by updated OpenSSL version)
- implement OpenSSL-based abstraction layer to replace legacy code (see CrypToolBase.{h|cpp} files)
- replace all instances of "CRYPTOOL_BASE" with the appropriate resource strings, but don't bother with this until the source is set for release as the constant refactoring may make maintaining the intended naming convention (i.e. CRYPTOOL_BASE_UTILITIES_xxx, CRYPTOOL_BASE_CRYPTOGRAPHY_xxx, etc.) a nightmare
- speed up the CrypTool::ByteString implementation: the constant re-allocation of memory, for example when concatenating byte strings, is significantly dragging down overall performance (this is particularly evident when using the key from password dialog with an iteration count of 10000 or higher)

## Other

- rename 'script' folder into 'ctbook' (make sure to handle all side effects)

## IMPORTANT

All the legacy code which has not been refactored yet is deactivated using the **_UNSTABLE** preprocessor definition. Please do not remove this definition from any of the individual VS2015 project files as long as not all the code has been refactored properly.
