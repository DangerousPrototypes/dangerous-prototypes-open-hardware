#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)

use strict;

use constant SCALER => 21.3333;
use constant HEXTXT => 1;         # 1 enabled hex, 0 enable dec
use constant FUZZ   => 11;
use constant DIV    => 10;

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

sub decode_man($)
{
	my ($ref) = @_;
	my $first = @$ref[0];
	my @ret   = (0);
	my $i     = 0;
	my $dbg   = 0;
	my $bit;
	print "decode_man():\n" if $dbg;
	foreach my $d (@$ref)
	{
		$bit = ( ( $i & 1 ) == 0 ) ? 1 : 0;
		printf "[%3d] d:%02X $bit", $i, $d if $dbg;
		push @ret, $bit;
		if ( $d > ( $first + round( $first * 0.5 ) ) )
		{
			print " $bit" if $dbg;
			push @ret, $bit;
		}
		printf " ret%d:%d", $#ret, $ret[$#ret - 1] if $dbg > 1;
		print "\n" if $dbg;
		$i++;
	}
	push @ret, 0 if ( $#ret & 1 ) == 0;
	printf "decode_man(): @ret len=%d\n", $#ret if $dbg;
	return \@ret;
} ## end sub decode_man($)

sub decode_RC5($$$)
{
	my ( $mul, $pkt, $hextxt ) = @_;
	my $dbg = 0;
	my $i   = 0;
	my $dw  = 0;
	my $r0  = @$pkt[0] * $mul;
	if ( !fuzzy_chk( round( $r0 / DIV ), 89, FUZZ ) )
	{
		return 0,
		  sprintf
"Probably not IR-RC5! First period:%.4fus %d 890us(+/-110) expected\n",
		  $r0, round( $r0 / DIV );
	}
	my $bs = decode_man($pkt);
	my $l  = $#{$bs} + 1;
	printf "decode_RC5(): length=$l\n" if $dbg;
	my $bits = ( $l / 2 ) - 1;
	my $res  = 0;
	for ( my $i = 0; $i < $#{$bs}; $i += 2 )
	{
		printf "[%3d] %d%d\n", $i, @$bs[$i], @$bs[$i + 1] if $dbg;
		$res |= ( @$bs[$i + 1] ) << ( $bits-- );
	}
	if ( $l == 28 )
	{
		if ($hextxt)
		{
			return $res, sprintf "S1:%d S2:%d T:%d Addr:0x%02X Cmd:0x%02X",
			  ( $res >> 13 ) & 1, ( $res >> 12 ) & 1, ( $res >> 11 ) & 1,
			  ( $res >> 6 ) & 0x1F, $res & 0x3F;
		}
		else
		{
			return $res, sprintf "S1:%d S2:%d T:%d Addr:%d Cmd:%d",
			  ( $res >> 13 ) & 1, ( $res >> 12 ) & 1, ( $res >> 11 ) & 1,
			  ( $res >> 6 ) & 0x1F, $res & 0x3F;
		}
	}
	else
	{
		return $res, sprintf "%b ", $res;
	}
} ## end sub decode_RC5($$$)

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
	my ( $value, $txt ) = decode_RC5( SCALER, $pkt, HEXTXT );
	printf "0x%08X %s\n", $value, $txt;
}
