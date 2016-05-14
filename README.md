# CrypTool-VS2015

This is a fork of CrypTool 1 to provide support for Visual Studio 2015.

Please visit http://www.cryptool.org for information on the original project.

The code in this repository was forked from r3717 of the CrypTool SVN repository. It was refactored quite heavily to enable students and other interested parties to work with CrypTool using the free-to-use Community Edition of VS2015. Older IDEs like VS2008 or VS2010 are not supported, please refer to the original CrypTool SVN repository for legacy support.

The long-term goal of this project is to refactor all the legacy code so that CrypTool is no longer dependent on a set of deprecated libraries, but instead using a to-be-implemented OpenSSL-based abstraction layer.

This repository contains two main branches: **master** and **experimental**.

- The **master** branch contains code which can be compiled successfully. However, due to the nature of this project, not even the code in the master branch can really be considered stable before all refactoring is finished.
- The **experimental** branch contains the most recent features and fixes, therefore the code may not even compile successfully. As soon as a certain degree of stability is reached, this branch is continuously merged into the master branch.

Please take a look at the DEVELOPERS document if you're interested in contributing.

If you have any questions, don't hesitate to contact me under florian(at)marchal(dot)de.

Florian Marchal (flomar), May 2016
