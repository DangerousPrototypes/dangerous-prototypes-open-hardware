#Copyright (c) 2009 Philippe ALEXANDRE.

# This library is free software; you can redistribute it and/or modify it under
# the same terms as Perl itself, either Perl version 5.8.2 or, at your option,
# any later version of Perl 5 you may have available.

package Twatch;
use strict;
use IO::Socket;
use Time::HiRes qw(usleep); 
use Data::Dumper;

use constant VERSION => 0.1;

#use constant SLEEP => 3000;
use constant SLEEP => 7000;

use constant BACKLIGHT_OFF => 0;
use constant BACKLIGHT_ON => 1;

sub new 
{
	my ($ip, $port, $nbRow, $nbCol) = @_;
	
# verify IP - IPv4 address
	die("Missing IP parameter") if(!defined($ip) || $ip eq '' || length($ip) == 0);
	die ("Bad IP format") if(!is_ipv4($ip));

# verify PORT	
	$port="1337" if(!defined($port) || $port eq '' || length($port) == 0);
	die("Bad port value") if($port < 0 || $port > 65535); 

# row
	if(!defined($nbRow) || $nbRow eq '' || $nbRow == 0)
	{
		$nbRow = 4;
	}

# column
	if(!defined($nbCol) || $nbCol eq '' || $nbCol == 0)
	{
		$nbCol = 20;
	}


# network connection
	my $socket = IO::Socket::INET->new( Proto     => 'tcp',
												 PeerAddr  => $ip,
												 PeerPort  => $port,
	) or die("Cannot connect to twatch at $ip:$port");
	$socket->autoflush(1);
	
	my $self  = {};
	$self->{_IP} = $ip;
	$self->{_PORT} = $port;
	$self->{_BACKLIGHT_STATE} = 0;
	$self->{_DEBUG} = 0;
	$self->{_NBROW} = $nbRow;
	$self->{_NBCOL} = $nbCol;
	$self->{_SOCKET} = $socket;
	bless($self); 
	return $self;
}

sub backlightOn
{
	my ($self) = @_;
	return if($self->{_BACKLIGHT_STATE} == 1);
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x42),chr(0x00);
	$self->{_BACKLIGHT_STATE} = BACKLIGHT_ON;
	usleep(SLEEP);
}

sub backlightOff
{
	my ($self) = @_;

	return if($self->{_BACKLIGHT_STATE} == 0);
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x46);
	$self->{_BACKLIGHT_STATE} = BACKLIGHT_OFF;
	usleep(SLEEP);
}

sub switchBacklight
{
	my ($self) = @_;
	if($self->{_BACKLIGHT_STATE} == BACKLIGHT_OFF)
	{
		$self->backlightOn();
	}
	else
	{
		$self->backlightOff();
	}
}

sub clearLCD
{
	my ($self) = @_;
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x58);
	usleep(SLEEP);
}

sub cursorOn
{
	my ($self) = @_;
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x53);
}

sub cursorOff
{
	my ($self) = @_;
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x54);
}

sub underlineCursorOn
{
	my ($self) = @_;
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x49);
}

sub underlineCursorOff
{
	my ($self) = @_;
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x49);
}

sub printLine
{
	my ($self, $text, $row, $col) = @_;
	my $msg=$text;

	$row=1 if(!defined($row) || $row > $self->{_NBROW} || $row < 1);
	$col=1 if(!defined($col) || $col > $self->{_NBCOL} || $col < 1);
	
	#print "length(text): ".length($text)."\n";
	#print "self->{_NBCOL}: ".$self->{_NBCOL}."\n";
	#print "self->{_NBCOL}-col: ".($self->{_NBCOL}-$col)."\n";

	if(($col + length($text)) > $self->{_NBCOL})
	{
		$msg=substr($text, 0, ($self->{_NBCOL}-$col)+1);
	}
	my $sock = $self->{_SOCKET};
	print $sock chr(0xFE),chr(0x47),chr($col),chr($row);
  print $sock $msg;
	usleep(SLEEP);
}

sub endConnection
{
	my ($self) = @_;
	sleep(2);
	close($self->{_SOCKET});
}

# Source from Data::Validate::IP - (c)  Neil Neely
# http://cpansearch.perl.org/src/NEELY/Data-Validate-IP-0.10/lib/Data/Validate/IP.pm
sub is_ipv4 
{
	my $self = shift if ref($_[0]); 
	my $value = shift;
        
	return unless defined($value);
	
	my(@octets) = $value =~ /^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$/;
	return unless (@octets == 4);
	foreach (@octets) 
	{
		#return unless ($_ >= 0 && $_ <= 255);
		return unless ($_ >= 0 && $_ <= 255 && $_ !~ /^0\d{1,2}$/);
	}
        
	return join('.', @octets);
}

1;
