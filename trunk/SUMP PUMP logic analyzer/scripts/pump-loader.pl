#sample PERL script to program PUMP ROM 
# This example is for educational use and it's totally free
#knowledge shouldn't be locked up, demo code shouldn't be licensed
#released into the Public Domain or CC0, your choice.

#NOTE:
# Developed with ActivePerl: http://www.activestate.com/activeperl/
#
# For windows: configure your COM port below
# you'll also need Win32::Serialport http://search.cpan.org/~bbirth/Win32-SerialPort-0.19/lib/Win32/SerialPort.pm
#
# For others: use the Device::SerialPort version and modify the serial port name
# you'll need Device::SerialPort  http://search.cpan.org/~cook/Device-SerialPort-1.002/SerialPort.pm

sub ascii_to_hex ($){
	## Convert each ASCII character to a two-digit hex number.
	(my $str = shift) =~ s/(.|\n)/sprintf("%02lx", ord $1)/eg;
	return $str;
}

#
#
#	GET COMMAND LINE OPTIONS
#
use Getopt::Long;
#GetOptions #('esir:w:p:l:');
my $results = GetOptions(
			"e"=>\my $opt_e,
            "s"=>\my $opt_s,
            "i"=>\my $opt_i,
            "p=s"=>\my $opt_p,
            "w=s"=> \my $opt_w,
            "r=s"=> \my $opt_r,
            "l=i"=> \my $opt_l );

			

if( (($opt_r eq "") && ($opt_r != 1)) && 
	(($opt_w eq "") && ($opt_w != 1)) &&
	(($opt_i!=1)) &&
	(($opt_e!=1)) &&
	(($opt_s!=1)) ){
	print "# PUMP ROM programmer,\n"; 
	print "# \n";
	print "# -p <port> serial port to use\n"; 
	print "# -w <file> BIN file to write\n";
	print "# -r <file> read ROM to file\n"; 
	print "# -e erase ROM\n";
	print "# -s ROM status byte\n";
	print "# -i ROM JEDEC ID\n";
	print "# -l <pages> limit write or read to first <pages>\n";	
		die "No file specified.";
}

my $serport;

if (defined ($opt_p)){
	$serport=$opt_p;
}else{
	$serport="COM5";
}
print "Using: $serport\n";

my $pagelimit;
if(defined ($opt_l)){
	$pagelimit=$opt_l;
}else{
	$pagelimit=2048;
}
print "Read/write: $pagelimit pages\n";

# Set up the serial port for Windows
use Win32::SerialPort;
my $port = Win32::SerialPort->new($serport); #change to your com port
#setup serial port for Linux
#use Device::SerialPort;
#my $port = Device::SerialPort->new("$mysport"); #change to your com port

#port configuration  115200/8/N/1
$port->databits(8);
$port->baudrate(115200);
$port->parity("none");
$port->stopbits(1);
$port->buffers(1, 1); #1 byte or it buffers everything forever
$port->write_settings		|| undef $port; #set
unless ($port)			{ die "couldn't write_settings"; }

print "PUMP-Loader v0.1\n";
#
#
#	Grab ROM chip ID
#
#
print "Reading JEDEC ID: 0x";
$port->write("\x01\x00\x00\x00");
select(undef,undef,undef, .02); #sleep for fraction of second for data to arrive #sleep(1);
my $JEDECid=$port->read(4);
print ascii_to_hex $JEDECid;
print "\n";

if($JEDECid eq "\x1f\x24\x00\x00"){
	print "Found ATMEL AT45DB041D\n";
}else{
	die "Incorrect flash, or flash not found!\n";
}

#
#
#	Get status bit
#
#
if(defined $opt_s){
	print "Read status byte: ";
	$port->write("\x05\x00\x00\x00");

	select(undef,undef,undef, .02); #sleep for fraction of second for data to arrive #sleep(1);
	printf "0x%02X ", ord($port->read(1));
	print "\ndone.\n";
	exit;
}

#
#
#	Erase entire chip
#
#
if(defined $opt_e){
	print "Erasing ROM chip (may take 12 seconds): \n";
	$port->write("\x04\x00\x00\x00");

	select(undef,undef,undef, 12); #sleep for fraction of second for data to arrive #sleep(1);
	if($port->read(1) ne "\x01"){
		die "Erase failed!\n";
	}else{
		print "done.\n";
	}

}

#
#
#	Write a page of data
#
#
my $pagecnt=0;
if(defined $opt_w){
	print "Writting page: \n";

	open FILE, $opt_w or die $!; 
	binmode FILE; 
	my ($buf, $data, $n, $i); 
	while (($n = read FILE, $data, 264) != 0) { 
		if($pagecnt> ($pagelimit-1) ){
			next;
		}
		print "$pagecnt\n"; 	
		$port->write("\x02");#address is 4 don't care+upper 4, 7lsb + 1 don't care, 0
		my $pagecntbits=(($pagecnt>>7)&0xff);#PAGE to write (upper bits of page number)
		$port->write(chr $pagecntbits);
		$pagecntbits=(($pagecnt<<1)&0xff); #lower 7 bits of page number
		$port->write(chr $pagecntbits);
		$port->write("\x00");
		$port->write($data); 

		$n=264-$n; #pad short pages with 00s
		for($i=0; $i<$n; $i++){
			$port->write("\x00"); 	
		}

		my $crc = unpack "%8C*", $data; 
		$crc = (0x100 - $crc) % 0x100; 
		$port->write(chr $crc);

		select(undef,undef,undef, .02); #sleep for fraction of second for data to arrive #sleep(1);
		if($port->read(1) ne "\x01"){
			die "Write failed!\n";
		}
		$pagecnt++;
	} 
	close(FILE); 
	print "done.\n";
}
#
#
#	Read a page of data
# 	our memory has 2048 pages
#
#
if(defined $opt_r){
	print "Reading page: \n";
	my $readpages=$pagelimit;
	open(OUTPUT, ">", $opt_r) or die $!;
	binmode OUTPUT; 
	for (my $i=0; $i<$readpages; $i++){
		print "$i\n"; 
	
		$port->write("\x03");#write page command
		my $pagecntbits=(($i>>7)&0xff); #PAGE to start reading (upper bits)
		$port->write(chr $pagecntbits);
		$pagecntbits=(($i<<1)&0xff); #lower 7 bits of page #
		$port->write(chr $pagecntbits);
		$port->write("\x00");
		$port->write($data); 
		
		select(undef,undef,undef, .02); #sleep for fraction of second for data to arrive #sleep(1);
		my $readflash=$port->read(264);
		print OUTPUT $readflash; 
		
		#loop, remove and do it right
#		for(my $j=0; $j<264; $j++){
#			select(undef,undef,undef, .002); #sleep for fraction of second for data to arrive #sleep(1);
#			my $readflash=$port->read(1);
#			#printf "0x%02X ", ord($readflash); 
#			print OUTPUT $readflash; 
#		}
	}
	print "done.\n";
}