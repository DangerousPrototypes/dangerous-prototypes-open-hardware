#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY http://creativecommons.org/licenses/by/3.0/

use strict;

use constant SCALER => 21.3333;
use constant HEXTXT  => 0; # 1 enabled hex, 0 enable dec 

my $infile = shift || 'test000.bin';

sub round($)
{
	return int( $_[0] + 0.5 );
}

sub fuzzy_chk($$$)
{
	my ( $v, $c, $fuzz ) = @_;
	my $dbg = 0;
	printf "fuzzy_chk($v,$c,$fuzz): %d && %d = %d\n", $v < ( $c + $fuzz ),
	  $v > ( $c - $fuzz ), ( $v < ( $c + $fuzz ) && $v > ( $c - $fuzz ) )
	  if $dbg;
	return ( $v < ( $c + $fuzz ) && $v > ( $c - $fuzz ) );
}

sub get_chunks($)
{
	my ($res) = @_;
	my @ret   = ();
	my @arr   = ();
	my $first = 0;
	my $x     = '';
	while ($res)
	{
		( $x, $res ) = unpack "n a*", $res;
		last if $x == 0xffff;
		$first = $x if ( $first == 0 );
		if ( $x > ( $first * 3 ) )
		{    #pause found. current period is 3 times larger than the first one
			push @ret, [@arr];
			@arr = ();
		}
		else
		{
			push @arr, $x;
		}
	}
	push @ret, [@arr] if $x;
	return \@ret;
} ## end sub get_chunks($)

sub decode_NEC($$$)
{
	my ( $mul, $pkt, $hextxt ) = @_;
	my $i  = 0;
	my $dw = 0;
	my $r0 = @$pkt[0] * $mul;
	if ( !fuzzy_chk( round( $r0 / 100 ), 90, 10 ) )
	{
		return 0,
		  sprintf
		  "Probably not IR-NEC! First period:%.4fus 9000us(+/-1000) expected\n",
		  $r0;
	}
	$r0 = @$pkt[1] * $mul;
	if ( $#{$pkt} == 2 && fuzzy_chk( round( $r0 / 100 ), 22, 5 ) )
	{
		return -1, 'R';
	}
	$r0 = @$pkt[1] * $mul;
	if ( !fuzzy_chk( round( $r0 / 100 ), 45, 5 ) )
	{
		return 0,
		  sprintf
"Probably not IR-NEC! Second period:%.4fus 4500us (+/-500) expected\n",
		  $r0;
	}
	$dw = 0;
	my $j = 31;
	for ( $i = 0; $i < 32; $i++ )
	{
		$r0 = @$pkt[3 + ( $i * 2 )] * $mul;

		#printf "%d %.4f %d\n", 3+($i*2),$r0, round( $r0 / 100 );
		if ( fuzzy_chk( round( $r0 / 100 ), 17, 3 ) )
		{

			$dw |= 1 << ( 31 - $i );

#			printf "[%2d|%2d] '1' %.4fus dw:0x%08x %032b\n",$j--, 3+($i * 2),$r0,$dw,$dw;
		}
		else
		{

			#printf "[%2d|%2d] '0' %.4fus\n", $j--,3+($i * 2),$r0;
		}
	} ## end for ( $i = 0; $i < 32; ...
	$i = 2 + ( $i * 2 );
	if ( $i == $#{$pkt} )
	{
		$r0 = @$pkt[$i] * $mul;

		#		printf "[%d] STOP %.4fus\n", $i, $r0;
	}
	else
	{
		printf " STOP bit missing! %d<>%d\n", $i, $#{$pkt};
	}
	my $a1 = ( $dw >> 24 ) & 0xff;
	my $a2 = ( $dw >> 16 ) & 0xff;
	my $c1 = ( $dw >> 8 ) & 0xff;
	my $c2 = $dw & 0xff;
	if ($hextxt)
	{
		return $dw, sprintf "IR-NEC: Addr1:0x%02X, Addr2:0x%02X, Cmd:0x%02X %s",
		  $a1,
		  $a2, $c1, ( $c1 == ( ( ~$c2 ) & 0xff ) ) ? "OK" : "ERR";
	}
	else
	{
		return $dw, sprintf "IR-NEC: Addr1:0x%02X, Addr2:0x%02X, Cmd:0x%02X %s",
		  $a1,
		  $a2, $c1, ( $c1 == ( ( ~$c2 ) & 0xff ) ) ? "OK" : "ERR";
	}
} ## end sub decode_NEC($$$)

if ( !open( F, $infile ) )
{
	print "Can't open $infile\n";
	print "====================\n";
	print "Usage: $0 <file.bin>\n";
	exit;
}
binmode F;
my $buff;
my $res = '';
while ( read( F, $buff, 1024 ) )
{
	$res .= $buff;
}
close F;

foreach my $pkt ( @{get_chunks($res)} )
{
	my ( $value, $txt ) = decode_NEC( SCALER, $pkt, HEXTXT );
	printf "0x%08X %s\n", $value, $txt;
}
