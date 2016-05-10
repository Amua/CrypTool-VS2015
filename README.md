# CrypTool-VS2015

This is a fork of CrypTool to provide support for Visual Studio 2015.

Please visit http://www.cryptool.org for information on the original project.

The code in this repository was forked from r3717 of the CrypTool SVN repository. It was refactored quite heavily to enable students and other interested parties to work with CrypTool using the free-to-use Community Edition of VS2015. Older IDEs like VS2008 or VS2010 are not supported by the code in this repository.

As of May 2016, there are two main branches: master and experimental. The master branch does not contain any code yet, as it is a long way from being considered stable. The code in the experimental branch is a work in progress, but it can be compiled out of the box. However, please note that runtime behavior in some areas is undefined due to the fact that a lot of temporarily deactivated legacy code has not been refactored yet.

The long-term goal of this project is to refactor all the legacy code so that it is no longer dependent on a set of deprecated libraries, but using a to-be-implemented OpenSSL-based abstraction layer instead.

Please take a look at the DEVELOPERS document if you're interested in contributing.

If you have any questions, don't hesitate to contact me under florian(at)marchal(dot)de.

Florian Marchal (flomar), May 2016
