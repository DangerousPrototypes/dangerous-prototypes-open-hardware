package ScrollLine;
use strict;
use Data::Dumper;

use constant VERSION => 0.1;
use constant LEFT => 0;
use constant RIGHT => 1;

sub new
{
	my ($text, $scrollSize, $direction) = @_;
	die("Text empty") if(!defined($text) || $text eq '' || length($text) == 0);
	die ("Unknown scroll size") if(!defined($scrollSize) || $scrollSize eq '' || length($scrollSize) == 0);

	my $self = {};
	$self->{_TEXT}=$text;
	$self->{_STEP}=1;
	$self->{_STARTPOS}=0;
	if($scrollSize < length($text))
	{
		$self->{_SCROLLSIZE}=length($text);
	}
	else
	{
		$self->{_SCROLLSIZE}=$scrollSize;
		my $l=$scrollSize - length($text);
		for(my $i=0; $i<$l;$i++)
		{
			$self->{_TEXT}.=' ';
		}
	}

	if(!defined($direction) || $direction eq '')
	{
		$self->{_DIRECTION}=0;
	}
	else
	{
		$self->{_DIRECTION}=$direction;
	}
	bless($self);
	return $self;
}

sub changeDirection
{
	my ($self) = @_;
	if($self->{_DIRECTION} == LEFT)
	{
		$self->{_DIRECTION}=RIGHT;
	}
	else
	{
		$self->{_DIRECTION}=LEFT;
	}
}

sub setStep
{
	my ($self, $step) = @_;
	
	return if(!defined($step) || $step eq '' || $step !~ m/\d+$/);
	$self->{_STEP}=$step;
}

sub scroll
{
	my ($self) = @_;
	
	if($self->{_DIRECTION} == RIGHT)
	{
		return $self->_moveRight();
	}
	else
	{
		return $self->_moveLeft();
	}
}

sub _moveLeft
{
	my ($self) = @_;
	my $startPos=$self->{_STARTPOS};
	my $text=$self->{_TEXT};
	my $len=$self->{_SCROLLSIZE};

	my $t = substr($text, $startPos, $len-$startPos); 
	$t .= substr($text, 0, $startPos);
	$self->{_STARTPOS}+=$self->{_STEP};
	$self->{_STARTPOS}=0 if($self->{_STARTPOS} > $len);

	return $t;
}

sub _moveRight
{
	my ($self) = @_;
	my $startPos=$self->{_STARTPOS};
	my $text=$self->{_TEXT};
	my $len=$self->{_SCROLLSIZE};;

	my $t = substr($text, $startPos, $len-$startPos); 
	$t .= substr($text, 0, $startPos);
	$self->{_STARTPOS}-=$self->{_STEP};
	$self->{_STARTPOS}=length($text) if($self->{_STARTPOS} < 0);
	return $t;
	
}

1;
