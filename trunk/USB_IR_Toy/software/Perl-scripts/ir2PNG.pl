#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)
use strict;

use constant SCALER => 21.3333;
use constant CHUNKS => 0;    # 1 enable separate files, 0 all stream in one file
use constant FUZZ   => 11;
use constant DIV    => 10;

my $infile = shift || 'test000.bin';

sub round($)
{
	return int( $_[0] + 0.5 );
}

sub get_chunk($)
{
	my ($res) = @_;
	my @ret   = ();
	my $x     = '';
	while ($res)
	{
		( $x, $res ) = unpack "n a*", $res;
		last if $x == 0xffff;
		push @ret, $x;
	}
	return \@ret;
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

sub gd_png($$$$)
{
	my ( $mul, $min, $sum, $ref ) = @_;
	use GD::Image qw( colorAllocate transparent line png);
	my $dbg  = 0;
	my $im_w = 5;
	my $im_b = 10;
	my $im_h = 50;
	my $im_x = round( $sum / $min ) * $im_w;
	my $im_y = $im_h;
	printf "gd_png(%.4f,%d,%d,ref[%d])\n", $mul, $min, $sum, $#{$ref} if $dbg;

	my $im = new GD::Image( $im_x, $im_y );
	printf "GD::Image(%d,%d)\n", $im_x, $im_y if $dbg;

	my $bg = $im->colorAllocate( 255, 255, 255 );
	$im->transparent($bg);
	my $fg = $im->colorAllocate( 250, 96, 192 );
	my $zz = $im->colorAllocate( 255, 10, 10 );
	$im_x = 0;
	my $i = 0;
	my $p = 0;

	foreach my $pulse (@$ref)
	{
		$im_y = ( ( $i++ & 1 ) == 0 ) ? ( $im_h - $im_b ) : $im_b;
		$p = round( $pulse / $min );
		printf "pulse: round(pulse=%d/min=%d)=%d %.4f => ~%.4f (%.4f) %.4f\n",
		  $pulse, $min, $p, $pulse * $mul, ( $pulse * $mul ) / $p,
		  $min * $mul, $pulse * $mul
		  if $dbg;

		# begining vertical line
		$im->line( $im_x, $im_b, $im_x, $im_y, $fg );
		for ( my $a = 0; $a < $p; $a++ )
		{

			# top ruler
			$im->line( $im_x, 0 + $im_b, $im_x, $im_w + $im_b, $zz )
			  if ( ( $a > 0 ) );
			$im->line( $im_x, $im_h - $im_y, $im_x + $im_w, $im_h - $im_y,
					   $fg );
			print "\t$a line(" 
			  . $im_x . ","
			  . ( $im_h - $im_y ) . ","
			  . ( $im_x + $im_w ) . ","
			  . ( $im_h - $im_y )
			  . ",$fg) $im_y\n"
			  if $dbg;
			$im_x += $im_w;
		} ## end for ( my $a = 0; $a < $p...
		if ( ( ( $i - 1 ) & 1 ) == 0 )
		{
			$im->line( $im_x, $im_h - $im_y, $im_x, $im_h - $im_b, $fg );
		}

	} ## end foreach my $pulse (@$ref)

	return $im->png;
} ## end sub gd_png($$$$)

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

my $min  = 0xffff;
my $sum  = 0;
my $i    = 0;
my $data = [];
my $pngfile;
if (CHUNKS)
{
	$data = get_chunks($res);
}
else
{
	$data = [get_chunk($res)];
}

foreach my $pkt (@$data)
{

	#print "============ $i ============\n";
	foreach my $p (@$pkt)
	{
		$min = $p if ( $min > $p );
		$sum += $p;
	}
	my $png = gd_png( SCALER, $min, $sum, $pkt );
	if ($png)
	{
		if (CHUNKS)
		{
			$pngfile = sprintf( "%s%02d.png", $infile, $i++ );
		}
		else
		{
			$pngfile = sprintf( "%s.png", $infile );
		}
		if ( open P, ">$pngfile" )
		{
			binmode P;
			print P $png;
			close P;
			print "Wrote $pngfile\n";
		}else {
			print "Can't create $pngfile!\n";
		}
	} ## end if ($png)
} ## end foreach my $pkt (@$data)
