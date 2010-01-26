#sample PERL script to convert intel HEX to byte format
# This example is for educational use and it's totally free
#knowledge shouldn't be locked up, demo code shouldn't be licensed
#released into the Public Domain or CC0, your choice.
#use strict;
use Getopt::Std;
getopt ('rw');

if( (($opt_r eq "") && ($opt_r != 1)) || (($opt_w eq "") && ($opt_w != 1)) ){
	print "# Stupid HEX2BIN converter,\n"; 
	print "# \n";
	print "# -r <file> HEX file to read\n";
	print "# -w <file> BIN file to write\n"; 
		die "No file specified.";
}

open FILE, "<", $opt_r or die $!;
open(OUTPUT, ">", $opt_w) or die $!;
binmode OUTPUT; 

while (my $line = <FILE>) { 
	chomp($line);
	my @chars=split(//,$line);

	#check for start char
	if($chars[0] ne ":"){
		die "Error in file format!";
	}
	#only read record type 00
	if( ($chars[7] ne "0") || ($chars[8] ne "0") ) {
		next;
	}
	
	#get byte count
	my $bytecount=(hex($chars[1]) *16) + hex($chars[2]);

	#ignore hex address, assume continous

	#get bytecount bytes, convert to binary and save to file
	for(my $i=0; $i<($bytecount*2); $i+=2){
		my $bv=(hex($chars[9+$i]) *16) + hex($chars[10+$i]);
		print OUTPUT chr($bv); 
		#print "$bv";
	}
	#print "\n";
}
