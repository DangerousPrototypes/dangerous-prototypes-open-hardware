#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)

use strict;

use Win32::SerialPort;

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

#default config
my $cfg = {
		   'RS232' => {
					   'port'      => "COM4",
					   'baud'      => 115200,
					   'databits'  => 8,
					   'parity'    => 'none',
					   'stopbits'  => 1,
					   'handshake' => 'none'
		   },
};

sub round($)
{
	return int( $_[0] + 0.5 );
}

sub hexdump
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

sub rs232init($)
{
	my ($cfg) = @_;
	my $rs = new Win32::SerialPort( $cfg->{'RS232'}->{'port'} )
	  or die "Can't open serial port!\n";
	$rs->debug(0);
	$rs->baudrate( $cfg->{'RS232'}->{'baud'} );
	$rs->parity( $cfg->{'RS232'}->{'parity'} );
	$rs->databits( $cfg->{'RS232'}->{'databits'} );
	$rs->handshake( $cfg->{'RS232'}->{'handshake'} );
	$rs->stopbits( $cfg->{'RS232'}->{'stopbits'} );
	$rs->buffers( 1, 1 );
	$rs->read_interval(60);
	$rs->read_char_time(10);
	$rs->read_const_time(20);
	$rs->write_settings or die "Can't init rs232 settings\n";
	return $rs;
} ## end sub rs232init($)

sub rsRx($$)
{
	my ( $rs, $dbg ) = @_;
	my $i     = 0;    # stupid counter to protect against endless loop
	my $bytes = 0;
	my $x;
	my $rx;
	my $rdata = '';
	$dbg = ( $dbg & DEBUG );
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

sub irtoy_chk_end($$)
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

my $prefix = shift || $$ . "test";

# RS232 ...
my $rs = rs232init($cfg);

if ( !irtoy_mode_s( $rs, 0 ) )
{
	die "Can't enter SAMPLING mode!\n";
}

my $mul = PRESCALER;    # here should be a function to set prescaler...
my $res;
my $data = '';
my $f_prefix;
my $min;
my $sum;
my $arr_ref;
my $i = 0;

print "Press key on remote or CTRL+C to terminate\n";
while (1)
{
	$res = rsRx( $rs, CTRL );
	if ($res)
	{
		$data .= $res;
		if ( irtoy_chk_end( $res, CTRL ) )
		{
			$f_prefix = sprintf "%s%03d", $prefix, $i++;
			( $min, $sum, $arr_ref ) =
			  irtoy_process( $mul, $f_prefix . ".bin", CTRL, $data );
			printf "Processed: $f_prefix min=%d(%.4fus),"
			  . " sum=%.4f, multiply=%.4f, len=%d\n",
			  $min, ( $min * $mul ), $sum, $mul, length($data);
			$data = '';
			if ( -f "irtoy.dump" )
			{
				printf "prescaler=%.4f\n", $mul;
				foreach $res (@$arr_ref)
				{
					printf "0x%02x %.4f\n", $res, $res * $mul;
				}
			}
		} ## end if ( irtoy_chk_end( $res...
	} ## end if ($res)
	else
	{
		print "Press key on remote or CTRL+C to terminate\n";
	}
} ## end while (1)

$rs->close();

