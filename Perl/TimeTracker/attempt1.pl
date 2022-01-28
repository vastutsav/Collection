#!/usr/bin/env perl

use strict;
use warnings;

use Modern::Perl;

my $filename="taskfile.txt";

my $datetime = localtime();
say $datetime;


say "enter activity and task";
my $task = <>;

open(FH, '>>', $filename);

print FH "$datetime:$task";

close(FH);
