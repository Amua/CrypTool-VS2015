# CrypTool-VS2015 TODO List

This document contains the most important TODOs for the project.

## Documentation

- unify project documentation in master branch
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

## Other

- rename 'script' folder into 'ctbook' (make sure to handle all side effects)

## IMPORTANT

All the legacy code which has not been refactored yet is deactivated using the **_UNSTABLE** preprocessor definition. Please do not remove this definition from any of the individual VS2015 project files as long as not all the code has been refactored properly.
