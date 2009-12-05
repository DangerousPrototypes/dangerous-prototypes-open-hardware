#!/usr/bin/perl -w
use Twatch;
use strict;
use Data::Dumper;
use Time::HiRes qw(usleep); 

sub showLines
{
	my ($lcd)=@_;

	die if(!defined($lcd));
	$lcd->clearLCD();
	$lcd->printLine("123456789012345678901234567890", 1, 1);
	$lcd->printLine("ABCDEFGHIJKLMONPQRSTUVWXYZ", 2, 1);
	$lcd->printLine("abcdefghijklmonpqrstuvwxyz", 3, 1);
	# Truncate line
	$lcd->printLine("123456789012345678901234567890", 4, 10);
	sleep(4);
}

sub showChr
{
	my ($lcd)=@_;

	die if(!defined($lcd));
	$lcd->clearLCD();
	my $text='';
	my $l=1;
	my $nbCol=20;
	
	for(my $i=0; $i<256; $i++)
	{
		my $n=sprintf("%d:%c", $i, $i);
		my $lng=length($text) + length($n);
		if($lng <= $nbCol)
		{
			$text .= $n.' ';
		}
		else
		{
			$lcd->printLine($text, $l, 0);
			#print "l($l): $text\n";
			$l++;
			$text = $n.' ';
			if($l >= 5)
			{
				$l = 1;
				#print "Line $l >= 5 - i: $i\n";
				sleep(5);
				$lcd->clearLCD();
			}
		}
	}
	if(length($text)>0)
	{
		$lcd->printLine($text, $l, 0);
	}
}

sub pong
{
	my ($lcd) = @_;

	die if(!defined($lcd));
	my $chr=255;
	my $x=1;
	my $y=1;
	my $xs=0;
	my $ys=0;
	my $maxX=4;
	my $maxY=20;
	my $minX=1;
	my $minY=1;

	my $nb=0;
	$lcd->clearLCD();
	while($nb < 100)
	{
		$lcd->clearLCD();
		$lcd->printLine(chr($chr), $x, $y);
		#print "X: $x, Y: $y --- xs: $xs, ys: $ys\n";
		usleep(90000);

		if($xs == 0)
		{
			$x++;
		}
		else
		{
			$x--;
		}

		if($ys == 0)
		{
			$y++;
		}
		else
		{
			$y--;
		}

		if($x >= $maxX)
		{
			$xs=1;
		}
		elsif($x <= $minX)
		{
			$xs=0;
		}

		if($y >= $maxY)
		{
			$ys=1;
		}
		elsif($y <= $minY)
		{
			$ys=0;
		}

		$nb++;
	}

	$lcd->clearLCD();
}

sub goodBye
{
	my ($lcd) = @_;
	$lcd->clearLCD();
	$lcd->printLine("-= GoodBye =-", 2, 4);
}

my $lcd = Twatch::new("192.168.0.40", "1337");

$lcd->backlightOn();

showLines($lcd);
showChr($lcd);
pong($lcd);
goodBye($lcd);

#$lcd->backlightOff();
$lcd->endConnection();

exit 0;
