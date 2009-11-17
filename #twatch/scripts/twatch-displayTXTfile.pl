#!/usr/bin/perl
# $Id$

# (c) 2009 Lars Engels <lars@0x20.net>
# Distributed under the 2-clause BSD license.

#http://whereisian.com/forum/index.php?topic=153.msg878#msg878
#I found some time to hack down a Perl script based on noxin's work to feed my #twatch.
#At the moment you can tell it to print the content of a file to the LCD.
#There's a function to truncate long lines to 20 characters, so the text is not wrapped. I also wrote some functions that I found at X7JAY7X's LCD Page.
#Still missing is a function to scroll long text. I already have written some code that does this on a console. so it should be not a big problem to use that code later.
#I'd like the script to listen to key presses, so one can turn the backlight on or off.
#Thanks to noxin for the initial ideas. There are stille some LOC of his code in it, so I hope it's okay to distribute this code under the BSD license.


use strict;
use warnings;
use IO::Socket;
use POSIX qw(strftime);

use constant NUM_ROWS => 4;
use constant NUM_COLS => 20;
use constant DEBUG => 0;

# Hostname / IP Adress of the #twatch device
my $host = '192.168.10.149';
my $port = '1337';
my $srcfile = '/tmp/vrr.txt';

my $me = $0;

############# BEGIN MAIN ##############

my $backlight = 0;

### $SIG{'INT'} = 'toggle_backlight';

debugmsg('Starting Process');
debugmsg('Opening Connection');
# Connect to the server...
my $remote = IO::Socket::INET->new(
      Proto     => 'tcp',
      PeerAddr  => $host,
      PeerPort  => $port,
) or errormsg(1, "cannot connect to LCDd daemon at $host:$port");
debugmsg('Connection Complete');

# Make sure our messages get there right away
$remote->autoflush(1);

lcd_on();

while (1) {
   debugmsg('Starting main loop...');

   open(FP, '<', $srcfile);
   my @filecontent = <FP>;
   close FP;
   chomp(@filecontent);
   my $count = 1;
   foreach my $line (@filecontent) {
        if ($line !~ /^----/) {
                if ($count > NUM_ROWS) {
                        sleep(5);
                        $count = 1;
                }
                println_trunc($count, 1, $line);
        } elsif ($count == 1) {
                next;
        }
        $count++;
   }
}

lcd_off();

close($remote) or errormsg(1, "close() failed: $!");
exit;

#####################################
######### Begin subroutines #########
#####################################

sub println {
        # print one line on the LCD
        # Synopsis: println($row, $col, $text)
        my $row = shift;
        my $col = shift;
        my $text = shift;
        debugmsg("Moving to ",$row,$col," printing: ",$text);
        print $remote chr(0xFE),chr(0x47),chr(${col}),chr(${row});
        print $remote $text;
}

sub println_trunc {
        # truncate a line to NUM_COLS characters and print them on the LCD
        # Synopsis: println_trunc($row, $col, $text)
        my $row = shift;
        my $col = shift;
        my $text = shift;
        debugmsg("Moving to ",$row,$col," printing (truncated): ", substr($text, 0, NUM_COLS));
        print $remote chr(0xFE),chr(0x47),chr(${col}),chr(${row});
        print $remote substr($text, 0, NUM_COLS); # only print first NUM_COLS chars
}

sub errormsg {
        # Print error messages
        # Synopsis: errormsg($status, $message)
        my $status = shift;
        my @msg = @_;
        print STDERR $me . ": " . join(" ", @msg) . "\n";
        exit($status) if ($status);
}

sub debugmsg {
        # Print debug messages if DEBUG is true
        # Synopsis: debugmsg($text);
        if (DEBUG) {
                my $date = strftime("%F %T", localtime);
                print $date." ".join(" ", @_)."\n";
        }
}

sub lcd_on {
        # Turn LCD backlight on
        # Synopsis: lcd_on()
        if ($backlight eq 0) {
                debugmsg("Turning LCD On");
                print $remote chr(0xFE),chr(0x42);
                $backlight = 1;
        }
}

sub lcd_off {
        # Turn LCD backlight off
        # Synopsis: lcd_off()
        if ( $backlight eq 1 ) {
                debugmsg("Turning LCD Off");
                print $remote chr(0xFE),chr(0x46);
                $backlight = 0;
        }
}

sub set_brightness {
        # set LCD brightness to a level between 1 and 255
        # Synopsis: set_brightness($level)
        # XXX: Currently not available in firmware
        my $brightness_level = shift;
        debugmsg("Setting brightness level to $brightness_level");
        print $remote chr(0xFE),chr(0x98),chr($brightness_level);

}

sub toggle_backlight {
        # Toggle backlight on or off
        # Synopsis: toggle_backlight()
        if ($backlight eq 0) {
                lcd_on();
        } else {
                lcd_off();
        }
}

sub clear_lcd {
        # Delete all characters on the LCD
        # Synopsis: clear_lcd()
        print $remote chr(0xFE),chr(0x58);
}

sub block_curs_on {
        # Turn on block cursor mode
        # Synopsis: block_curs_on()
        print $remote chr(0xFE),chr(0x53);
}

sub block_curs_off {
        # Turn off block cursor mode
        # Synopsis: block_curs_off()
        print $remote chr(0xFE),chr(0x54);
}

sub go_home {
        # Go to the top left position
        # Synopsis: go_home()
        print $remote chr(0xFE),chr(0x48);
}

sub underline_on {
        # Turn cursor underline on
        # Synopsis: underline_on()
        print $remote chr(0xFE),chr(0x48);
}

sub underline_off {
        # Turn cursor underline off
        # Synopsis: underline_off()
        print $remote chr(0xFE),chr(0x49);
}

sub scroll_line {
        # Scroll a single line
        # Synopsis: scroll_line($row, $speed, $text)
        # XXX: To be implemented...
        my $row = shift;
        my $speed = shift;
        my @text = split //, $_;
}


### command reference: http://www.freewebs.com/x7jay7x/Blank%20Page%205.htm
### -[254]
### - Backlight On Command, (066  000)
### Turns LCD backlight on.
### - Backlight Off Command, (070)
### Turns LCD backlight off.
### - Position Command, (071 [col] [row]) 0x47
### Moves the cursor to the specified [col] and [row].  Columns have the values
### 1 to 40; rows have the values 1 to 4.  These values depend on the LCD type you
### are using.  For example, a 4x20 LCD would have a column of 1 to 20 and a row of
### 1 to 4.
###  - Home Command, (072)
### Returns the cursor to the home position.  The home position is the top left
### of the display.
### - Underline Cursor On, (074)
### Turns the underline cursor on.  This shows where the current text insertion
### point is.  The underline cursor is off by default.
### - Underline Cursor Off, (075)
### Turns the underline cursor off.
### - Custom Character Command, (078 [c] [8 bytes]) 0x4e
### The display can hold up to 8 custom characters defined using this command.
### After the control command of [78d] is send, the number of the custom character
### to be defined [c] is given.  The value of [c] is from 0 to 7.  The next 8 bytes
### define to character.
### - Block Cursor On, (083)
### Turns the block cursor on.  This shows the current text insertion point.
### Block cursor is off by default.
### - Block Cursor Off, (084)
### Turns off block cursor.
### - Clear Display Command, (088)
### Clears the contents of the display screen and sets the cursor to the home position.
### - Backlight Brightness, (152 [b])
### Controls the LCD Backlight Brightness.  After the command of 152, [b] is a value of 0 to 255d.  The brightness is a percentage of the total 255.
