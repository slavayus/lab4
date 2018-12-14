#!/usr/bin/perl -T
use strict;
use warnings;
use Fcntl;
use File::Basename;

sub copy_files();

my $buffer_size = 3;

my $result = check_args();

if ($result) {
    exit($result)
}

copy_files();

sub copy_files() {
    if ($#ARGV == 1) {
        if (-d $ARGV[1] || -d $ARGV[0]) {
            $result = copy_file_to_dir($ARGV[0], $ARGV[1])
        }
        else {
            $result = copy_file_to_file();
        }
    }
    else {
        $result = copy_all_files_to_dir();
    }
}

!$result or die "Something went wrong";


sub copy_all_files_to_dir() {
    my $destination_dir = $ARGV[$#ARGV];
    for (my $i = 0; $i < $#ARGV; ++$i) {
        my $cp_result = copy_file_to_dir($ARGV[$i], $destination_dir);
        if ($cp_result < 0) {
            return 3;
        }
    }
    return 0;
}

sub copy_file_to_dir() {
    if (-d $_[0]) {
        print("cp: omitting directory '$_[0]'\n");
        return 0;
    }
    my $source_file = open_source_file($_[0]);
    my $filemode = (stat($source_file))[2];
    my $destination_file = open_destination_dir($_[0], $_[1], $filemode);
    copy_file_data($source_file, $destination_file);
    close($source_file);
    close($destination_file);
    return 0
}

sub copy_file_to_file() {
    my $source_file = open_source_file($ARGV[0]);
    my $filemode = (stat($source_file))[2];
    my $destination_file = open_destination_file($ARGV[1], $filemode);
    copy_file_data($source_file, $destination_file);
    close($source_file);
    close($destination_file);
    return 0
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

sub copy_file_data {
    my $buffer;
    my $read;
    while ($read = sysread($_[0], $buffer, $buffer_size)) {
        my $write_bytes = syswrite($_[1], $buffer, $buffer_size);
        if ($write_bytes < 0) {
            die "Can't write data to file"
        }
    }

    !$read or die "Can't read data from file";
}

sub open_source_file {
    sysopen(my $fh, $_[0], O_RDONLY)
        or die "Can't open < source file: $!";
    return $fh
}

sub open_destination_file {
    my $file = $_[0];
    unless ($file =~ /^(.*)$/) {
        die "filename '$file' has invalid characters.\n";
    }
    $file = $1;

    sysopen(my $fh, $file, O_WRONLY | O_CREAT, $_[1])
        or die "Can't open > destination file: $!";
    return $fh
}

sub open_destination_dir {
    my $dir = $_[1] . "/" . basename($_[0]);
    unless ($dir =~ /^(.*)$/) {
        die "dirname '$dir' has invalid characters.\n";
    }
    $dir = $1;

    sysopen(my $fh, $dir, O_WRONLY | O_CREAT, $_[2])
        or die "Can't open > destination dir: $!";
    return $fh
}