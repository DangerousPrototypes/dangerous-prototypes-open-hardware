#!/usr/bin/perl -w
#By: noxin (http://whereisian.com/forum/index.php?topic=146.msg825#msg825)
#I bought the #twatch to be a remote screen for my monitoring system.   Since I'm more familiar with perl than python, I #hacked this together.   Horrible code, I know, it's functional and meets my goals.
#Normally, it just pushes data to the screen, but if something goes critical, it'll turn on the backlight to draw #attention.

use 5.005;
use strict;
use Getopt::Std;
use IO::Socket;
use Fcntl;

############################################################
# Configurable part. Set it according your setup.
############################################################

# Host which runs lcdproc daemon (LCDd)
my $SERVER = "192.168.11.116";

# Port on which LCDd listens to requests
my $PORT = "1337";
my $DEBUG = "0";

############################################################
# End of user configurable parts
############################################################

my $progname = $0;
   $progname =~ s#.*/(.*?)$#$1#;

# declare functions
sub error($@);
sub lineout($@);
sub debugmsg($@);

## main routine ##
my %opt = ();
my @BBOUT;
my $LCD = "";

debugmsg("Starting Process");
debugmsg("Opening Connection");
# Connect to the server...
my $remote = IO::Socket::INET->new(
      Proto     => 'tcp',
      PeerAddr  => $SERVER,
      PeerPort  => $PORT,
   )
   or  error(1, "cannot connect to LCDd daemon at $SERVER:$PORT");
debugmsg("Connection Complete");

# Make sure our messages get there right away
$remote->autoflush(1);

sleep (1);   # Give server plenty of time to notice us...

LCDOFF();
sleep(1);

while (1) {
   my $liner1 = "";
   debugmsg("Main loop...");

   my @liner = `/usr/lib/hobbit/server/bin/bb localhost "hobbitdboard fields=hostname,testname,ackmsg,color"`;
   my @BBYEL  = grep {/\|yellow/} @liner;
   my @BBRED  = grep {/\|\|red/} @liner;
   my @BBBLU  = grep {/\|blue/} @liner;
   my @BBPUR  = grep {/\|purple$/} @liner;
   debugmsg("Status: R: ",scalar(@BBRED)," Y: ",scalar(@BBYEL)," B: ",scalar(@BBBLU)," P: ",scalar(@BBPUR));
   if ( scalar(@BBRED) gt 0 ) {
      LCDON();
   } else { LCDOFF(); }
   lineout(1,5,"Hobbit Status ");
   $liner1="Red : ".scalar(@BBRED)." ";
   lineout(2, 2, $liner1);
   $liner1="Yel : ".scalar(@BBYEL)."  ";
   lineout(2, 12, $liner1);
   $liner1="Blu : ".scalar(@BBBLU)." ";
   lineout(3, 2, $liner1);
   $liner1="Pur : ".scalar(@BBPUR)." ";
   lineout(3, 12, $liner1);
   $liner1=`date +%D\\ %H:%M`;
   chomp $liner1;
   lineout(4, 4, $liner1);
   # wait a bit
   debugmsg("Output Complete, sleeping");
   sleep(30);
}

close($remote)  or  error(1, "close() failed: $!");
exit;

sub lineout($@)
{
# Move to Pos 1,1
   my $lrow = $_[0];
   my $lcol = $_[1];
   my $lout = $_[2];
   ##print "$lrow $lcol $lout\n";
   debugmsg("Moving to ",$lrow,$lcol," printing : ",$lout);
   print $remote chr(0xFE),chr(0x47),chr(${lcol}),chr(${lrow});
   print $remote $lout;
}
## print out error message and eventually exit ##
# Synopsis:  error($status, $message)
sub error($@)
{
my $status = shift;
my @msg = @_;

  print STDERR $progname . ": " . join(" ", @msg) . "\n";

  exit($status)  if ($status);
}

sub debugmsg($@) {
   if ( $DEBUG gt 0 ) {
     my $BBDATE=`date`;
     chomp $BBDATE;
     print $BBDATE." ".join(" ", @_)."\n";
   }
}

sub LCDON {
   if ( $LCD ne 0 ) {
   debugmsg("Turning LCD On");
   print $remote chr(0xFE),chr(0x42);
   print $remote chr(0xFE),chr(0x47),chr(0x01),chr(0x01);
   print $remote chr(0xFE),chr(0x58);
   $LCD = 0;
   sleep(1);
   }
}

sub LCDOFF {
   if ( $LCD ne 1 ) {
   debugmsg("Turning LCD Off");
   print $remote chr(0xFE),chr(0x46);
   print $remote chr(0xFE),chr(0x47),chr(0x01),chr(0x01);
   print $remote chr(0xFE),chr(0x58);
   $LCD = 1;
   sleep(1);
   }
}
