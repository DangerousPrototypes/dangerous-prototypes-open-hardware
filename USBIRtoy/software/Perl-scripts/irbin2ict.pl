#!/usr/bin/perl
#
# Convert Danerous Prototypes USB IR Toy .bin file
# to .ict file that can be viewed with IRScope
#
# Usage: irbin2ict.pl test000.bin 
#
# Robert Terzi
# November 2010
# Version: 0.1
#
# License: CC-BY, http://creativecommons.org/licenses/by/3.0/ 
#
# TODO:  This was a quick an dirty hack...
# 1, USB IR Toy .bin files don't contain any information
#    about carrier, sampling rate, etc. 
# 2. Be smart about timeout/end markers to break into different
#    signals and correctly detect beginning of new MARK state.
#
#
# Taken from: http://dangerousprototypes.com/forum/index.php?topic=1482.0
# See the wiki: http://dangerousprototypes.com/docs/USB_IR_Toy:_Perl_scripts_for_signal_analysis#IR_Scope_converter_script 

use strict;
use constant IRTOY_SCALAR => 21.33333;
use constant IRTOY_TIMEOUT => 0xFFFF;

if (scalar(@ARGV) != 1) { 
    die "Usage: irbin2ict test000.bin\n";
}

my $inFile = shift(@ARGV);
    
open(IN, $inFile) || die "Couldn't open $inFile: $!";

binmode IN;

my $bindata = '';
my $buf = '';

while (read(IN,$buf,16384)) {
    $bindata .= $buf;
}

my $bytesRead = length($bindata);

die "Error: Invalid input, not an even number of bytes\n" if ($bytesRead % 2 != 0);

print "Read ",length($bindata)," bytes from $inFile\n";

my @samples;

for (my $i; $i < $bytesRead; $i += 2) {
    my $n = unpack("n",substr($bindata,$i,2));
    if ($n == IRTOY_TIMEOUT) {
	# IR Toy end marker / timeout, 1.7 secs
	# TODO: break into multiple signals?
	if (scalar(@samples) % 2 != 1) {
	    warn ("Data possibly out of sync, 0xFFFF read in mark position");
	    # TODO: resync byte stream with next byte as MARK.
	}
    }
    my $l = int($n * IRTOY_SCALAR + .5);
    if (scalar(@samples) % 2 == 1) {
	$l = 0 - $l;
    }
    push(@samples,$l)
}

# Last sample should always be a space (off period)
if ($samples[$#samples] > 0) {
    push(@samples,-50000);
}


my $outFile = $inFile . ".ict";
if ( -f $outFile ) {
    print STDERR "Output file: $outFile already exists, Overwrite (y/N)?";
    my $ans = <>;
    if (!($ans =~ /^[yY]/)) {
	print STDERR "Exiting...\n";
	exit(1);
    }
}


open(OUT, ">$outFile") || die "Couldn't open output file $outFile: $!\n";


print OUT "irscope 0\ncarrier_frequency 0\n";
print OUT "sample_count ",scalar(@samples),"\n";
print OUT "note=IRToy Sample\n";

foreach my $n (@samples) {
    my $out = $n >= 0 ? "+$n" : "$n";
    print OUT $out,"\n";
}



close(OUT);

print "Wrote $outFile\n";
