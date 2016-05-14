# CrypTool-VS2015 DEVELOPERS README

This README file is the starting point for all developers interested in contributing to the project.

## Build Requirements

The following is **REQUIRED** to build CrypTool:

- **Microsoft Visual Studio 2015 Community Edition**: You can acquire this IDE from Microsoft for free, but make sure you include the "Microsoft Foundation Classes" (MFC) during installation, otherwise you won't be able to build CrypTool.
- **ActivePerl Free Community Edition**: The [ActiveState Perl](http://www.activestate.com/activeperl) distribution is recommended, but you should be able to work with any Perl version >= 5.00.

The following is **RECOMMENEDED**, but not required, to work with CrypTool:

- **git**: You can use [git](https://git-scm.com/downloads) to organize your code and submit pull requests against this repository, but simply downloading a ZIP archive from this site works as well if you're just interested in building CrypTool and not contributing anything.
- **NSIS Installer**: You can use [NSIS](http://nsis.sourceforge.net/) to build CrypTool setup executables. This is not required, but it makes publishing your work to other people easier.

## Build Instructions

#### Get The CrypTool Source Code

Run **git clone https://github.com/flomar/CrypTool-VS2015** to check out the source code. If you want to work with branches other than the master branch, you can for example run **git checkout experimental** to work with the experimental branch.

#### Make Perl Available

Put the Perl distribution you installed (see above) into your **%PATH%** variable.

#### Building CrypTool

Fire up VS2015 and open the CrypTool solution file **trunk/CrypTool/CrypTool-VS2015.sln**. Choose your preferred solution configuration depending on the desired language, for example "Debug_en" or "Release_en". Then build the solution, set "CrypTool" as start-up project, and run it.

#### Building CrypTool Installers

In order to build a self-extracting CrypTool installer executable, first you have to build CrypTool in the RELEASE configuration of the desired language. For example, if you want to create an English installer, you have to build CrypTool in the "Release_en" configuration. The following languages are supported at the moment: English, German, Polish, Spanish, Serbian, Greek, and French, with their corresponding language identifiers being "en", "de", "pl", "es", "rs", "el", and "fr".

After having build CrypTool, go into the **trunk/setup** folder and run **createsetupdir1lang.bat en && createsetupexe1lang.bat en**. For non-English versions you have to replace "en" with the language identifier of your choice. If you want to create installers for all supported languages in one go, you can run **createsetupdirs.bat && createsetupexes.bat**, but don't forget you have to build CrypTool in the RELEASE configuration for all supported languages prior to creating the installers.

## Remarks

Check out the TODO document for a list of the most pressing issues of the project.

If you have any questions, don't hesitate to contact me under florian(at)marchal(dot)de.

Florian Marchal (flomar), May 2016
