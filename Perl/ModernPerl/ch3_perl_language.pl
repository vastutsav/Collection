#!/usr/bin/env perl

use strict;
use warnings;

use Modern::Perl;
use Data::Dumper qw(Dumper);

sub some_function {
	return ('x','zazzles');
}

my @values = ('a', 'b', 'c', 'd');
my @indexes = (1,2);

print Dumper @values;
print Dumper @indexes;
say @values[@indexes];

@values[@indexes] = some_function;
print Dumper @values;

my $element = @values[@indexes]; # last item of the intermediate array is moved to $element
say $element;

my $scalar = @values; # the number of elements is moved to $scalar
say "1. scalar = $scalar";

($scalar) = @values; # the first element is moved to $scalar
say "2. scalar = $scalar";

my $heredoc=<<'END_HEREDOC';
	Hi, this is a random heredoc. This line has been indented and it shall remain so.
The 2nd line is not indented. No extra whitespaces will be added to the start of the line.


Bye.
END_HEREDOC

say $heredoc;
say "Heyo";

my $tmp = some_function; #last item of the list returned by the function is stored in $tmp
say "1. tmp = $tmp";

say "QWER";
$tmp = () = some_function; #number of items returned by the function is stored in $tmp. this is because the functions response is converted to a list and then to scalar.
say "2. tmp = $tmp";

my $a;
$tmp = ($a) = some_function; #number of items returned by the function is stored in $tmp. this is because the functions response is converted to a list and then to scalar. $a stores the first item
say "3. tmp = $tmp \t \$a = $a";

$a = some_function; #last element in $a
say "\$a = $a";

($a) = some_function; #first element is $a
say "\$a = $a";

my $i = 'cow';

for my $i (1 .. 2)
{
	say "$i * $i = ", $i * $i;
}

say $i;

$i = 'horse';

for $i (1 .. 2)
{
	say "$i * $i = ", $i * $i;
}

say $i;

#my $call_sign = 'KBMIZ';
my $call_sign = 'ZZZ';
say "1. \$call_sign = $call_sign";

my $next_sign = ++$call_sign; # incerementing a string variable
say "\$next_sign = $next_sign";
say "2. \$call_sign = $call_sign";

my @arr = qw(Alpha Beta Gamma Theta Delta);
say join "<->", @arr;
$#arr = 2;
say join "---", @arr;
$#arr = 5;
say join "===", @arr;

my @arrSplice = qw(alpha beta gamma delta);
my ($winner, $runnerup) = splice @arrSplice, 0, 2;
say "winner and runnerup = $winner and $runnerup";
say "first element of arrSplice is $arrSplice[0]";


my @cats = qw(Oppenheimer Fermi Feynman Teller);
say "cats 1";
say join "<>", @cats;
@cats[-1] = some_function;
say "cats 2";
say join "<>", @cats;
$cats[-1] = some_function;
local $" = '> <';
say "cats 3";
say "<@cats>";

my %addresses =
(
	Leonardo => '1123 Fib Place',
	Utako    => 'Cantor Hotel, Room 1',
	Victor   => 'Blue Spark',
	'Sue-Linn'  => 'Mont Blanc'
);

say $addresses{Victor};
say $addresses{'Sue-Linn'}; # quotes are needed because the key has '-' character in it

sub get_some_address_from_name{
	return $addresses{+shift};
}

say get_some_address_from_name 'Utako';

say "Have Warnie's address" 
if exists $addresses{Warnie}; 
# exists does not check the boolean nature of the hash value; a hash key may exist even if its value evaluates to false

$addresses{Leibniz} = undef;

say "Gottfried lives at $addresses{Leibniz}"
if exists  $addresses{Leibniz}
&& defined $addresses{Leibniz};
# If a hash key exists, its value may be undef. Check that with defined


for my $addressee (keys %addresses) {
	say "Found adderss for $addressee";
}

for my $address(values %addresses) {
	say "Someone lives at $address";
}

while (my ($addressee, $address) = each %addresses){ # was unable to figure out a for loop version of this
	say "$addressee stays at $address";
}

# hashes has a single iterator. in order to reset to iterator, we need to use keys or values keyword

# using hash slices, we can merge 2 hashes

my %other_addresses = 
(
	Alice 	=> '111 Computer Street',
	Bob	=> '420 Fake Boulevard'
);

@addresses{keys %other_addresses} = values %other_addresses;


say "After merging the hashes";
while (my ($addressee, $address) = each %addresses){ # was unable to figure out a for loop version of this
	say "$addressee stays at $address";
}

# creating a set out of hash
my @fruits = qw(apple grapes banana mango apple banana orange);
my %set;
undef @set{@fruits};

say "+++++++ Printing unique fruits ++++++";
foreach (keys %set) {
	say "fruit=> $_";
}

# creating a cache of computed items
# defined-or assignment operator //=
# checks definedness
# if the value is not defined, then assignment operation is performed
sub expensive_operation{
	my $a=shift;
	say "expesive operation called for $a";
	$a*$a;
}

my %my_cache;

my @numbers = (1,2,3,1,2,3,4,5);

foreach (@numbers) {
	$my_cache{$_} //= expensive_operation($_); # function is called only if data has not been computed
}

foreach (@numbers) {
	say "$_ => $my_cache{$_}";
}

# boolean-or operator ||=
# checks truthiness 
# if value is false, then the assignment operation is done
sub checkin{
	my $a = shift;
	say "$a checked in the hotel";
	1;
}

my %guest_checkin =
(
	alice 		=> 0,
	bob 		=> 0,
	charlie 	=> 1,
	david		=> 0
);

my @guests = qw(alice bob charlie david eve);

foreach (@guests) {
	$guest_checkin{$_} ||= checkin($_);
}

foreach (@guests) {
	if ($guest_checkin{$_}) {
		say "$_ is in the hotel";
	} else {
		say "$_ did not check in";
	}
}

