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


