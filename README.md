# CrypTool-VS2015
This is a fork of CrypTool to provide support for Visual Studio 2015.

Please visit http://www.cryptool.org for information on the original project.

As of r3717, the code in the CrypTool SVN repository supports compilation using VS2008 and VS2010. In order to enable students and other interested parties to work with CrypTool using the Community Edition of VS2015, the code needs to be refactored quite heavily. Some of the internally used libraries are deprecated, and the goal of this fork is to replace these libraries with a to-be-implemented OpenSSL layer.

IMPORTANT NOTICE: With the very first commit of this repository, the code does not compile without doing some magic behind the scenes. The deprecated libraries have been removed already, and therefore a lot of code sections had to be temporarily deactivated. Also, there are some problems with the linker. As soon as these issues have been sorted out, I will remove this notice.

If you have any questions, don't hesitate to contact me under florian(at)marchal(dot)de.

Florian Marchal (flomar), May 2016
