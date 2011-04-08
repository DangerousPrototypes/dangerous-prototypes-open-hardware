#! /usr/bin/env perl
#
#
# Anton Todorov
# CC BY (http://creativecommons.org/licenses/by/3.0/)

use strict;

unless ( eval {require USBIRToy} )
{
	die "USBIRToy.pm is missing!\n";
}

my $prefix = shift || $$ . "test";

# init RS232 ...
my $rs = rs232init();
# set mode to 's'
if ( !irtoy_mode_s( $rs, 0 ) )
{
	die "Can't enter SAMPLING mode!\n";
}

# set prescaler
my $mul = irtoy_setPrescaler( $rs, 7 );
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
	$res = rsRx( $rs, 0 );
	if ($res)
	{
		$data .= $res;
		if ( irtoy_chkEnd( $res, 0 ) )
		{
			$f_prefix = sprintf "%s%03d", $prefix, $i++;
			( $min, $sum, $arr_ref ) =
			  irtoy_process( $mul, $f_prefix . ".bin", 0, $data );
			printf "Processed: '$f_prefix.bin' min=%d(%.4fus),"
			  . " sum=%.4fus, multiply=%.4f, len=%d\n",
			  $min, ( $min * $mul ), $sum * $mul, $mul, length($data);
			if ( -f "irtoy.dump" )
			{
				printf "prescaler=%.4f\n", $mul;
				foreach $res (@$arr_ref)
				{
					printf "0x%02x %.4f\n", $res, $res * $mul;
				}
			}
			$data = '';
		} ## end if ( irtoy_chkEnd( $res...
	} ## end if ($res)
	else
	{
		print "Press key on remote or CTRL+C to terminate\n";
	}
} ## end while (1)

$rs->close();
