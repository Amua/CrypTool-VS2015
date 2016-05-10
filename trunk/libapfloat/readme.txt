BUILD INSTRUCTIONS FOR APFLOAT
==============================

1) You need a Microsoft IDE, VS2015 has been successfully tested.

2) Download the following packages from "http://apfloat.org":
* the apfloat base package (i.e. "apf241.zip")
* the files for Windows GUI (i.e. "32_vc_a.zip")
* the files for Windows threading support (i.e. "win32_ta.zip")

3) Now, extract all ZIP files in the same directory (i.e. "apfloat").

NOTE: Follow the instructions on the apfloat site; it is important HOW and IN WHICH ORDER you extract the ZIP files, see option "-o" of your ZIP program.

4) Open the file "apfloat/makefile" and make changes as follows:

4a) Find the "OPTS" parameter, and replace the option "/GX" with "/EHsc".

4b) Add the option "/MTd" if you want to build a DEBUG library, and "/MT" if you want to build a RELEASE library, respectively.

5) In order to make apfloat satisfy our CrypTool needs, apply the following patches contained in the "patch" directory:
* apint.h.patch
* apifunc.cpp.patch
* makeprim.cpp.patch

6) Now you're ready to build. Go into the "apfloat" directory and call "NMAKE" to compile the library.

7) When done building the libraries, do the following, move header files and libraries into the proper locations.

7a) Put the header files into the following location:
* trunk/libapfloat/include (debug and release are identical)

7b) Put the libraries into the following location:
* trunk/libapfloat/lib/apfloatd.lib (debug library)
* trunk/libapfloat/lib/apfloat.lib (release library)

I hope this helped. Send an email to florian(at)marchal(dot)de if you run into any problems.

Florian Marchal, May 2016