#!/usr/bin/env perl

use Modern::Perl;

sub factorial {
	my $n = shift;
	return 1 if $n == 0;
	return $n*factorial($n-1);
}

say factorial(20);
