#!/usr/bin/env perl
#
#use IPC::Open2;

#local(*HIS_OUT, *HIS_IN);  # Create local handles if needed.

#$childpid = open2(*HIS_OUT, *HIS_IN, "./a")
#     or die "can't open pipe to $program: $!";

my $bound = 1000;
my $n = int(rand($bound - 1)) + 1;
my $m = int(rand($bound - 1)) + 1;

my $w = int(rand(1000)) + 10;

my $testcase = "$m $n $w\n";
foreach my $i (1 .. $w) {
    my $beg = int(rand($n));
    my $end = int(rand($n - $beg)) + $beg;
    my $y =   int(rand($m));
    $testcase .= "$beg $y $end $y\n";
}

$testcase .= "0 0 0\n";

#print HIS_IN $testcase;
#$his_output = <HIS_IN>;
#close(HIS_OUT);
#close(README);
#waitpid($childpid, 0);
#print $testcase;
#print $his_output;
print $testcase;
