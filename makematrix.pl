#!/usr/bin/perl

$space=80;
$cols=650;
if (scalar(@ARGV)>0) { $space=$ARGV[0]; }
if (scalar(@ARGV)>1) { $cols=$ARGV[1]; }

$y=0;
while(<STDIN>) 
{

    ($pat)=split(" ");

    $pat=~s/\!/.\n/g;
    $pat=~s/[a-zA-Z]/\*/g;

    print "#P $x $y\n", $pat;

    $x+=$space;
    if ($x>$cols)
    {
	$x=0;
	$y+=$space;
    }
}
