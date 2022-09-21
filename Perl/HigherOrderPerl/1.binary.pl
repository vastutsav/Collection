#!/usr/bin/env perl

use strict;
use warnings;
use Modern::Perl;

sub binary{
	my $a = shift;
	return $a if $a == 0 or $a == 1;
	return binary(int($a/2)).($a%2);
}

my $str = binary(5);
say $str;
