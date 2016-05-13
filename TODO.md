# CrypTool-VS2015 TODO List

This document contains the most important TODOs for the project.

## Documentation

- unify project documentation in master branch
- update "CrypTool-MFC-Kurs-VC7.ppt" in CrypTool root folder (and rename it to something in English)
- update "readme-source.txt" in CrypTool root folder, in particular the parts about the online help
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
