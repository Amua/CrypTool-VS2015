BUILD INSTRUCTIONS FOR LIBGMP
=============================

1) You need a Microsoft IDE, VS2015 has been successfully tested.

2) Download the current source release from "http://www.mpir.org".

3) Follow the build instructions in "build.vc14\readme.txt".

4) Fire up VS2015 and open "mpir.sln".

5) Build "lib_mpir_gc" and "lib_mpir_cxx" in DEBUG and RELEASE configurations.

6) Copy the following files from the build folder into the CrypTool folder:
* build.vc14\lib_mpir_gc\win32\Debug\mpir.lib -> libgmp\lib\mpird.lib
* build.vc14\lib_mpir_gc\win32\Release\mpir.lib -> libgmp\lib\mpir.lib
* build.vc14\lib_mpir_cxx\win32\Debug\mpirxx.lib -> libgmp\lib\mpirxxd.lib
* build.vc14\lib_mpir_cxx\win32\Release\mpirxx.lib -> libgmp\lib\mpirxx.lib

I hope this helped. Send an email to florian(at)marchal(dot)de if you run into any problems.

Florian Marchal, May 2016