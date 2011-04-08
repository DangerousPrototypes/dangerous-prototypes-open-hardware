#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)

use strict;

use constant SCALER => 21.3333;
use constant HEXTXT => 1;         # 1 enabled hex, 0 enable dec

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

sub decode_PAN($$$)
{
	my ( $mul, $pkt, $hextxt ) = @_;
	my $i   = 0;
	my $dw  = 0;
	my $min = 0xffff;
	my $dbg=0;
	foreach $dw (@$pkt)
	{
		$min = $dw if $min > $dw;
		printf "[%3d] %.4f\n", $i++, $dw * $mul if $dbg;
		#printf "[%3d] %.4f|%.4f|%.4f\n", $i++, $dw * $mul, $min * $mul,( $dw / $min ) if $dbg;
	}
	print "\n" if $dbg;

	my $r0 = @$pkt[0] * $mul;
	if ( !fuzzy_chk( round( $r0 / 100 ), 35, 10 ) )
	{
		return 0,
		  sprintf
		  "Probably not IR-PAN! First period:%.4fus 3500us(+/-1000) expected\n",
		  $r0;
	}
	$r0 = @$pkt[1] * $mul;
	if ( !fuzzy_chk( round( $r0 / 100 ), 17, 5 ) )
	{
		return 0,
		  sprintf
"Probably not IR-PAN! Second period:%.4fus 1700us (+/-500) expected\n",
		  $r0;
	}
	$dw = 0;
	my $bytes = ( $#{$pkt} - 2 ) / 16;
	printf "bytes=%.4f %d\n",$bytes,$#{$pkt} if $dbg;
	my $j;
	my @arr = ();
	for ( $i = 0; $i < ( $#{$pkt} - 2 ) / 16; $i++ )
	{
		my $bit = 7;
		$arr[$i] = 0;
		for ( $j = 0; $j < 16; $j+=2 )
		{
			$r0=@$pkt[3+16*$i+$j];
			$arr[$i] |= 1 << ( $bit) if $r0 > ( $min * 2 );
			#printf "[%3d] 0x%02X, %08b, %.4f\n", 3+16*$i+$j, $arr[$i], $arr[$i], $r0 * $mul;
			$bit--;
		}
		printf "($i) 0x%02X, %08b next:%d\n", $arr[$i], $arr[$i], 1+16*$i+$j if $dbg;
	}

	$i = 2+16*($i-1)+$j;
	if ( $i == $#{$pkt} )
	{
		$r0 = @$pkt[$i] * $mul;
		#printf "[%d] STOP %.4fus\n", $i, $r0;
	}
	else
	{
		printf " STOP bit missing! %d<>%d\n", $i, $#{$pkt};
	}
	my $txt='';
	if ($hextxt)
	{
		foreach $i (@arr){
			$txt.=sprintf" 0x%02x(%08b)",$i,$i;
		}
	}
	else
	{
		foreach $i (@arr){
			$txt.=sprintf" %d",$i;
		}
	}
		return \@arr, "IR-PAN:$txt";
} ## end sub decode_PAN($$$)

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
	my ( $value, $txt ) = decode_PAN( SCALER, $pkt, HEXTXT );
	printf "%s\n", $txt;
}
