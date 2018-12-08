#!/usr/bin/perl -T
use strict;
use warnings;
use Fcntl;

my $result = check_args();

if ($result) {
    exit($result)
}

my $source_file = open_source_file();
my $filemode = (stat($source_file))[2];
my $destination_file = open_destination_file($filemode);
printf("Source file = %s", $source_file);
printf("Source file = %s", $destination_file);


sub check_args {
    if ($#ARGV == -1) {
        printf("missing file operand\n");
        return 1
    }
    if ($#ARGV == 0) {
        printf("missing destination file operand after '%s'\n", $ARGV[0]);
        return 2
    }
    return 0
}

sub open_source_file {
    sysopen(my $fh, "1", O_RDONLY)
        or die "Can't open < source file: $!";
    return $fh
}

sub open_destination_file {
    sysopen(my $fh, "2", O_WRONLY | O_CREAT, $_[0])
        or die "Can't open > destination file: $!";
    return $fh
}