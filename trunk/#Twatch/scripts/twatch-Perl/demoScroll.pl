#!/usr/bin/perl -w
use ScrollLine;
use Twatch;
use strict;
use Time::HiRes qw(usleep);
use Data::Dumper;
use constant SCROLL_SIZE => 20;

my $line='Test line';
#my $line='12345678901234567890AZERTY';
my $lcd = Twatch::new("192.168.0.40", "1337");
$lcd->clearLCD();
$lcd->backlightOn();

my $sl=ScrollLine::new($line, SCROLL_SIZE, 0);

for(my $i=0; $i<SCROLL_SIZE*2; $i++)
{
	my $z=$sl->scroll();
	#print "i:".$i." - sl:".$z."\n";
	$lcd->printLine($z, 3,1);
	usleep(500000);
}
$lcd->endConnection();
exit(0);
