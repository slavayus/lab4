#!/usr/bin/perl -T
use strict;
use warnings;

my $result = check_args();

if ($result) {
    exit($result)
}


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
