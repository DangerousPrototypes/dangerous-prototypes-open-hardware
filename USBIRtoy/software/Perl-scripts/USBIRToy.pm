#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)

use constant RESET            => 0x00;
use constant MODE_S           => ord('s');
use constant SAMPLE_TIMER_CMD => 0x05;

use constant PRESCALER => 21.3333;

use constant CTRL       => 0b0000;
use constant DEBUG      => 0b0001;
use constant GETRAWDATA => 0b0010;
use constant DECODE     => 0b0100;
use constant SKIP_RX    => 0b1000;

use constant RS_RX_MAXLOOPS => 1000;

#
# $rounded = round($float);
sub round($)
{
	return int( $_[0] + 0.5 );
}
#
# $txt = hexDump($data, $bool_print_ascii);
sub hexDump
{
	my ( $data, $ctrl ) = @_;
	my $t;
	my $r = '';
	my $x = '';
	while ($data)
	{
		( $t, $data ) = unpack "C a*", $data;
		$r .= sprintf "%#.2x ", $t;
		$x .= sprintf "%c", ( $t > 20 && $t < 128 ) ? $t : "." if $ctrl;

	}
	$r .= "[$x]" if $ctrl;
	return $r;
}

#
# my $rsCfgHashref my $cfg = {
#           'port'      => "/dev/ttyACM0",
#           'baud'      => 115200,
#           'databits'  => 8,
#           'parity'    => 'none',
#           'stopbits'  => 1,
#           'handshake' => 'none'};
# $rs232Obj = rs232init($rsCfgHashref);
sub rs232init
{
	my ($cfg) = @_;
	my $rs;
	my $guess;
	if ( eval {require Win32::SerialPort} )
	{
		$guess = defined( $cfg->{'port'} ) ? $cfg->{'port'} : 'COM4';
		$rs = new Win32::SerialPort($guess)
		  or die "Can't open serial port! Win32::SerialPort($guess)\n";

		#$rs->read_interval(60);                 #Win32 only
	}
	elsif ( eval {require Device::SerialPort} )
	{
		$guess = defined( $cfg->{'port'} ) ? $cfg->{'port'} : '/dev/ttyACM0';
		$rs = new Device::SerialPort($guess)
		  or die "Can't open serial port! Device::SerialPort($guess)\n";
	}
	else
	{
		print "Can't initiate COM port!\n";
		print
		  "Required Device::SerialPort or Win32::SerialPort module missing!\n",;
		exit;
	}
	$rs->baudrate( defined( $cfg->{'baud'} ) ? $cfg->{'baud'}   : 115200 );
	$rs->parity( defined( $cfg->{'parity'} ) ? $cfg->{'parity'} : 'none' );
	$rs->databits( defined( $cfg->{'databits'} ) ? $cfg->{'databits'} : 8 );
	$rs->handshake(
				defined( $cfg->{'handshake'} ) ? $cfg->{'handshake'} : 'none' );
	$rs->stopbits( defined( $cfg->{'stopbits'} ) ? $cfg->{'stopbits'} : 1 );

	$rs->buffers( 1, 1 );
	$rs->read_interval(60);
	$rs->read_char_time(10);
	$rs->read_const_time(20);
	$rs->write_settings or die "Can't init rs232 settings\n";
	return $rs;
} ## end sub rs232init

#
# my $rxdata = rsRX($rs232Obj, $functionControlBits);
sub rsRx($$)
{
	my ( $rs, $ctrl ) = @_;
	my $i     = 0;    # stupid counter to protect against endless loop
	my $bytes = 0;
	my $x;
	my $rx;
	my $rdata = '';
	$dbg = ( $ctrl & DEBUG );
	print "\n>>> rsRx():" if $dbg;

	while ( ( $x, $rx ) = $rs->read(1) )
	{
		if ( $x == 0 )
		{
			if ( $bytes > 0 )
			{
				last;
			}
			elsif ( $i++ > RS_RX_MAXLOOPS )
			{    # max loops
				print " [maxloops]" if $dbg;
				last;
			}
			select( undef, undef, undef, .02 );
		}
		else
		{
			$rdata .= $rx;
			$bytes++;
		}
	} ## end while ( ( $x, $rx ) = $rs...
	if ( $dbg && length($rdata) )
	{
		printf "%s", hexdump( $rdata, 1 );
		printf " (i=%d)\n", $i;
	}
	return $rdata;
} ## end sub rsRx($$)

#
# my $transmittedBytesCount = rsTxByte($rs232Obj, $FunctionControlBits, $ByteToSend);
sub rsTxByte($$$)
{
	my ( $rs, $ctrl, $byte ) = @_;
	my $i = 0;
	my $x;
	my $rx;
	my $dbg = ( $ctrl & DEBUG );
	printf " rsTxByte(ctrl:%04b)(0x%02x=0b%08b=%d)\n", $ctrl, $byte, $byte,
	  $byte
	  if $dbg;
	$x = $rs->write( pack( "C", $byte & 0xff ) );
	printf "rsTxByte(): 0x%02x -> $x\n", $byte if $dbg;
	return $x;
}

#
# my $receivedData = rsTxRx($rs232Obj,$FunctionControlBits,$ByteToSend);
sub rsTxRx($$$)
{
	my ( $rs, $ctrl, $byte ) = @_;
	my $i = 0;
	my $x;
	my $rx;
	my $dbg        = ( $ctrl & DEBUG );
	my $getrawdata = ( $ctrl & GETRAWDATA );
	my $skiprx     = ( $ctrl & SKIP_RX );
	if ($dbg)
	{

		if ($getrawdata)
		{
			print "< RAW";
		}
		else
		{
			print "< ___";
		}
	}
	printf " rsTxRx(ctrl:%04b)(0x%02x=0b%08b=%d)\n", $ctrl, $byte, $byte, $byte
	  if $dbg;
	$x = $rs->write( pack( "C", $byte & 0xff ) );
	if ($skiprx)
	{
		print "SKIP_RX\n";
		return;
	}
	select( undef, undef, undef, .01 );
	$rx = rsRx( $rs, CTRL );
	if ($getrawdata)
	{
		printf " rawRx:%s", hexdump( $rx, 1 ) if $dbg;
	}
	else
	{
		$rx = unpack( "C", $rx );
		if ( $rx == 1 )
		{
			printf " [OK %#.2x]", $rx if $dbg && !$getrawdata;
		}
		else
		{
			printf " [NOK %#.2x]", $rx if $dbg && !$getrawdata;
		}
	}
	printf "\n", $ctrl if $dbg;

	return $rx;
} ## end sub rsTxRx($$$)

#
# $prescaler = irtoy_setPrescaler($rs232Obj,$proposed value);
#This function should set prescaler (cmd:0x05, folowed by prescaler???)
# FIXME at the moment it returns only default PRESCALER value. 
sub irtoy_setPrescaler
{
	my ( $rs, $val ) = @_;
	return PRESCALER;

	#return (PRESCALER/(8-$val)); # FIXME
}

#
# irtoy_reset($rs232Obj, $FunctionControlBits);
# sends commands to reset USBIRToy
sub irtoy_reset($$)
{
	my ( $rs, $ctrl ) = @_;
	my $i;
	my $res;
	my $dbg = ( $ctrl & DEBUG );
	for ( $i = 0; $i < 5; $i++ )
	{
		$res = rsTxByte( $rs, $ctrl, RESET );
		printf "$i == $res\n" if $dbg;
	}
}

#
# $result = irtoy_mode_s($rs232Obj, $FunctionControlBits);
# sends command to set Sampling mode
sub irtoy_mode_s($$)
{
	my ( $rs, $ctrl ) = @_;

	#reset USB IR Toy
	irtoy_reset( $rs, $ctrl );

	my $res = rsTxRx( $rs, $ctrl | GETRAWDATA, MODE_S );
	if ( $res eq "S01" )
	{
		print "Sampling mode enabled!\n";
		return 1;
	}
	return 0;
}

#
# $result = irtoy_chkEnd($data, $FunctionControlBits);
# loops $data searching for 0xffff, returns 1 if found
sub irtoy_chkEnd($$)
{
	my ( $data, $ctrl ) = @_;
	my $dbg = ( $ctrl & DEBUG );
	my $l   = length($data);
	my $x;
	printf "toy_chk_end(): len=%d 0x%04x\n", $l, unpack( "n", $data ) if $dbg;
	while ( length($data) )
	{
		( $x, $data ) = unpack( "n a*", $data );

		#printf "irtoy_chk_end(): 0x%04x\n",$x if $dbg;
		if ( $x == 0xffff )
		{
			printf "toy_chk_end(): '1' 0x%04x\n", $x if $dbg;
			return 1;
		}
	}
	printf "toy_chk_end(): '0' 0x%04x\n", $x if $dbg;
	return 0;
} ## end sub irtoy_chk_end($$)

#
# ($min,$sum,$array_ref) = irtoy_process($multiply, $filename, $FunctionControlBits, $data)
sub irtoy_process($$$$)
{
	my ( $mul, $file, $ctrl, $data ) = @_;
	my $dbg = ( $ctrl & DEBUG );
	my $x;
	my $i   = 0;
	my $min = 0xffff;
	my $sum = 0;
	my @arr = ();
	my $l   = length($data);

	printf "process(): elements:%d/2=%d multiply=%.4f\n", $l, ( $l / 2 ), $mul
	  if $dbg;
	open O, ">$file";
	binmode O;

	while ( length($data) )
	{
		( $x, $data ) = unpack( "n a*", $data );
		print O pack( "n", $x );
		printf "[%4d] 0x%04x=%6d %s\n", $i, $x, $x * $mul,
		  ( ( $i & 1 ) == 0 ) ? "H" : "L"
		  if $dbg;
		last if ( $x == 0xffff );
		$sum += $x;
		push @arr, $x;
		$min = $x if $min > $x;
		$i++;
	}
	close O;
	printf "process(): min=0x%04x, sum:%d/min=%.4f=round(%d)\n",
	  $min, $sum, ( $sum / $min ), round( $sum / $min )
	  if $dbg;
	return $min, $sum, \@arr;
} ## end sub irtoy_process($$$$)

1;
