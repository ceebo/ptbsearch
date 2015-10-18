#!/usr/bin/env perl

# Get number of lines
open TEMP, $ARGV[0];
1 while(<TEMP>);
my $all = $.;
close TEMP;

# Main loop of ptb2
open PATLIST, $ARGV[0];
while (<PATLIST>)
{
    @flds = split(" ");

    if(scalar(@flds) < 2){
        $gen0 = 18;
    }else{
        $gen0 = $flds[1];
    }
   
    if(scalar(@flds)< 4){
        $gen1 = $ARGV[2];
    }elsif($ARGV[2] < $flds[4]){
        $gen1 = $ARGV[2];
    }else{
        $gen1 = $flds[4];
    }
   
    $pat = $flds[0];
    $pat =~ s/!/.\n/g;

    open OUTPAT, "> temp";
    print OUTPAT $pat;
    close OUTPAT;

    print STDERR "==========$./$all==========\n";
    system("./ptb2 temp $ARGV[1] $gen1 0 $gen0 1");

}
close PATLIST;
unlink "temp"
