# updateBuildInformation.pl

#
# This script is called as pre-build and as post-build 
# task from within Visual Studio. It updates a couple of 
# resource strings in "CrypTool.rc" to reflect CrypTool 
# version information if invoked with the "PRE" parameter, 
# and it reverts those changes when invoked with the "POST" 
# parameter.
#
# flomar, 2016/05/24
#

use strict;

#
# NOTE: "MAJOR", "MINOR", "REVISION" ***MUST*** BE DEFINED!
# THE "ADDITION" (i.e. 'Beta 10') MAY BE UNDEFINED.
#
# THE LINES BELOW CONTROL THE BUILD
my $CrypToolVersionMajor = "1";
my $CrypToolVersionMinor = "4";
my $CrypToolVersionRevision = "31";
my $CrypToolVersionAddition = "Beta 6c";
# THE LINES ABOVE CONTROL THE BUILD
#

my $mode = undef;

my $fileCrypToolRC = "CrypTool.rc";
my $fileCrypToolRC_BACKUP = "CrypTool-BACKUP.rc";

# some error checking
if(scalar @ARGV < 1) {
	print "Please supply at least one argument, either PRE or POST! Exiting...\n";
	exit;
}
else {
	if($ARGV[0] eq "PRE") {
		$mode = "PRE";
	}
	elsif($ARGV[0] eq "POST") {
		$mode = "POST";
	}
	else {
		print "Please supply at least one argument, either PRE or POST! Exiting...\n";
		exit;
	}
}

# mode PRE: we update the files
if($mode eq "PRE") {
	print "Updating CrypTool build information...\n";
	# determine the build time (as in: "now")
	my ($sec,$min,$hour,$day,$month,$yr19,@rest) = localtime(time);
	my $buildTime = (1900+$yr19) . "-" . ($month+1) . "-" . ($day);
	# check if all necessary parameters are defined
	if(	not defined $CrypToolVersionMajor or 
		not defined $CrypToolVersionMinor or
		not defined $CrypToolVersionRevision) {
		print "WARNING: CrypTool version invalid";
		exit;
	}
	# build the CrypTool version (used throughout the CrypTool application)
	my $CrypToolVersion = $CrypToolVersionMajor . "." . $CrypToolVersionMinor . "." . $CrypToolVersionRevision;
	my $CrypToolVersionFull = $CrypToolVersion;
	# use a version string with an additional tag (if existent)
	if(defined $CrypToolVersionAddition) {
		$CrypToolVersionFull .= " " . $CrypToolVersionAddition;
	}
	# make a copy of the resource file
	system("copy $fileCrypToolRC $fileCrypToolRC_BACKUP");
	# open the resource file
	my @lineArrayFileCrypToolRC;
	open(FILE, "<$fileCrypToolRC") or die ("Opening $fileCrypToolRC: $!\n");
	@lineArrayFileCrypToolRC = <FILE>;
	close(FILE);
	# update the resource file content
	foreach my $line(@lineArrayFileCrypToolRC) {
		# inserting i.e. "CrypTool 1.4.31 Beta 5" (full version)
		if($line =~ m{ \[CRYPTOOL_VERSION_FULL\] }xms) {
			$line = "IDR_MAINFRAME \"CrypTool $CrypToolVersionFull\"\n";
		}
		# inserting i.e. "1.4.31 Beta 5" (version without CrypTool name)
		if($line =~ m{ FileVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"FileVersion\", \"$CrypToolVersion\"\n";
		}
		# inserting i.e. "1.4.31 Beta 5" (version without CrypTool name)
		if($line =~ m{ ProductVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"ProductVersion\", \"$CrypToolVersion\"\n";
		}
	}
	# re-write the resource file
	open(FILE, ">$fileCrypToolRC") or die ("Opening $fileCrypToolRC $!\n");
	foreach my $line(@lineArrayFileCrypToolRC) {
	  print FILE $line;
	}
	close(FILE);
}

# mode POST: restore initial state of the file
if($mode eq "POST") {
	print "Reverting CrypTool build information changes...\n";
	# copy from resource file backup
	system("copy $fileCrypToolRC_BACKUP $fileCrypToolRC");
	# remove resource file backup
	system("del $fileCrypToolRC_BACKUP");
}
