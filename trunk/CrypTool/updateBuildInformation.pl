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
use Digest::SHA qw(sha512_hex);

#
# ATTENTION: "Major" and "Minor" must be defined, 
# "Stage" is optional and may be an empty string
#
# THE LINES BELOW CONTROL THE BUILD
my $CrypToolVersionMajor = "1";
my $CrypToolVersionMinor = "5";
my $CrypToolVersionStage = "alpha";
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

# mode PRE: update the CrypTool resource file
if($mode eq "PRE") {
	print "Updating CrypTool build information...\n";
	# check if all required parameters are defined
	if(	not defined $CrypToolVersionMajor or not defined $CrypToolVersionMinor) {
		print "WARNING: CrypTool version invalid";
		exit;
	}
	# try to acquire git branch, commit, and commit count used to build CrypTool; 
	# this information is not required for creating a valid CrypTool version, but 
	# it may yield useful information for developers in case of bug reports; if 
	# the git information cannot be obtained, the variables remain undefined
	my $gitBranch = undef;
	my $gitCommit = undef;
	my $gitCommitCount = undef;
	acquireGitInformation(\$gitBranch, \$gitCommit, \$gitCommitCount);
	# this variable will hold the numeric CrypTool version (i.e. "1.5" or "1.5.123")
	my $CrypToolVersion = getCrypToolVersion($CrypToolVersionMajor, $CrypToolVersionMinor, $CrypToolVersionStage, $gitCommitCount);
	# this variable will hold the full CrypTool version (i.e. "1.5 alpha" or "1.5.123 alpha")
	my $CrypToolVersionFull = getCrypToolVersionFull($CrypToolVersionMajor, $CrypToolVersionMinor, $CrypToolVersionStage, $gitCommitCount);
	# this variable will hold the time at which CrypTool was built (i.e. "1970-1-1")
	my $CrypToolBuildTime = getCrypToolBuildTime();
	# this variable will hold the git branch based on which CrypTool was built (if defined)
	my $CrypToolGitBranch = $gitBranch;
	# this variable will hold the git commit based on which CrypTool was built (if defined)
	my $CrypToolGitCommit = $gitCommit;
	# this variable will hold the git commit count based on which CrypTool was built (if defined)
	my $CrypToolGitCommitCount = $gitCommitCount;
	# make a copy of the resource file
	system("copy $fileCrypToolRC $fileCrypToolRC_BACKUP");
	# open the resource file
	my @lineArrayFileCrypToolRC;
	open(FILE, "<$fileCrypToolRC") or die ("Opening $fileCrypToolRC: $!\n");
	@lineArrayFileCrypToolRC = <FILE>;
	close(FILE);
	# update the resource file content
	foreach my $line(@lineArrayFileCrypToolRC) {
		if($line =~ m{ FileVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"FileVersion\", \"$CrypToolVersion\"\n";
		}
		if($line =~ m{ ProductVersion }xms and $line =~ m{ \[CRYPTOOL_VERSION\] }xms) {
			$line = "VALUE \"ProductVersion\", \"$CrypToolVersion\"\n";
		}
		if($line =~ m{ \[CRYPTOOL_VERSION_FULL\] }xms) {
			$line = "IDR_MAINFRAME \"$CrypToolVersionFull\"\n";
		}
		if($line =~ m{ \[CRYPTOOL_BUILD_TIME\] }xms) {
			$line = "IDS_CRYPTOOL_BUILD_TIME \"$CrypToolBuildTime\"\n";
		}
		if($line =~ m{ \[CRYPTOOL_GIT_BRANCH\] }xms) {
			$line = "IDS_CRYPTOOL_GIT_BRANCH \"$CrypToolGitBranch\"\n";
		}
		if($line =~ m{ \[CRYPTOOL_GIT_COMMIT\] }xms) {
			$line = "IDS_CRYPTOOL_GIT_COMMIT \"$CrypToolGitCommit\"\n";
		}
		if($line =~ m{ \[CRYPTOOL_GIT_COMMIT_COUNT\] }xms) {
			$line = "IDS_CRYPTOOL_GIT_COMMIT_COUNT \"$CrypToolGitCommitCount\"\n";
		}
	}
	# re-write the resource file
	open(FILE, ">$fileCrypToolRC") or die ("Opening $fileCrypToolRC $!\n");
	foreach my $line(@lineArrayFileCrypToolRC) {
	  print FILE $line;
	}
	close(FILE);
}

# mode POST: restore the CrypTool resource file
if($mode eq "POST") {
	print "Reverting CrypTool build information changes...\n";
	# copy from resource file backup
	system("copy $fileCrypToolRC_BACKUP $fileCrypToolRC");
	# remove resource file backup
	system("del $fileCrypToolRC_BACKUP");
}

sub executeExternalCommand {
	my $command = shift;
	my $random = rand(1000000);
	my $temporaryFileStdout = "$0." . sha512_hex("$command$random") . ".stdout";
	my $temporaryFileStderr = "$0." . sha512_hex("$command$random") . ".stderr";
	`$command 1>$temporaryFileStdout 2>$temporaryFileStderr`;
	open(FILESTDOUT, "<", $temporaryFileStdout);
	my @linesStdout = <FILESTDOUT>;
	close(FILESTDOUT);
	open(FILESTDERR, "<", $temporaryFileStderr);
	my @linesStderr = <FILESTDERR>;
	close(FILESTDERR);
	`del $temporaryFileStdout`;
	`del $temporaryFileStderr`;
	chomp @linesStdout;
	chomp @linesStderr;
	return (@linesStdout, @linesStderr);
}

sub acquireGitInformation {
	my ($branch, $commit, $count) = @_;
	# the first thing we want to do is find out if git is in the PATH variable; 
	# if we don't have git, we don't touch the input variables at all and return
	if(not isGitInPath()) {
		return;
	}
	# now we can extract information from git
	$$branch = getGitBranch();
	$$commit = getGitCommit();
	$$count = getGitCommitCount();
}

sub isGitInPath {
	my (@linesStdout, @linesStderr) = executeExternalCommand("git --version");
	return (scalar @linesStderr > 0) ? 0 : 1;
}

sub getGitBranch {
	my (@linesStdout, @linesStderr) = executeExternalCommand("git branch");
	foreach my $line (@linesStdout) {
		if($line =~ m{ \A \* \s+ (\w+) \z }xms) {
			return $1;
		}
	}
	return undef;
}

sub getGitCommit {
	my (@linesStdout, @linesStderr) = executeExternalCommand("git log -1");
	foreach my $line (@linesStdout) {
		if($line =~ m{ \A commit \s+ (\w+) \z }xms) {
			return $1;
		}
	}
	return undef;
}

sub getGitCommitCount {
	my (@linesStdout, @linesStderr) = executeExternalCommand("git rev-list --count HEAD");
	foreach my $line (@linesStdout) {
		return $line;
	}
	return undef;
}

sub getCrypToolVersion {
	my ($major, $minor, $stage, $count) = @_;
	# return the CrypTool version
	return "$major.$minor" . (defined $count ? ".$count" : "") . (defined $stage ? " $stage" : "");
}

sub getCrypToolVersionFull {
	my ($major, $minor, $stage, $count) = @_;
	# return the CrypTool full version (version with CrypTool prepended)
	return "CrypTool" . " " . getCrypToolVersion($major, $minor, $stage, $count);
}

sub getCrypToolBuildTime {
	my ($sec,$min,$hour,$day,$month,$yr19,@rest) = localtime(time);
	my $buildTime = (1900+$yr19) . "-" . ($month+1) . "-" . ($day);
	# return the CrypTool build time (as in: "now")
	return $buildTime;
}
