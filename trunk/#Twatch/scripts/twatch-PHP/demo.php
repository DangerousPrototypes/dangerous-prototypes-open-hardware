<?php
#
# Not as much written as thrown together by joost@decock.org
#
# Get updates at http://decock.org/twatch
#
include('lib.twatch.php');

$intro = "This \  PHP library for the #twatch obviously ain't no rocket science, but if you want to drive the #twatch from a PHP web interface (as I did) it may be just what you needed.      This demo script will cycle through the available functions so you get a feel of what to expect.";

$functions[1] = "";
$functions[2] = "These functions";
$functions[3] = "are available to you";
$functions[4] = "";

$connect[1] = "TwatchConnect()";
$connect[2] = "Connect to #twatch";
$connect[3] = "over the network.";
$connect[4] = "";

$connectbis[1] = "Obviously we've used";
$connectbis[2] = "the TwatchConnect() ";
$connectbis[3] = "function at the start";
$connectbis[4] = "of this demo";

$disconnect[1] = "TwatchDisconnect()";
$disconnect[2] = "Closes the TCP";
$disconnect[3] = "connection to your";
$disconnect[4] = "#twatch";

$disconnectbis[1] = "Oh, and we'll use ";
$disconnectbis[2] = "that at the end of ";
$disconnectbis[3] = "this demo";
$disconnectbis[4] = "";

$backlight[1] = "Next up:";
$backlight[2] = "TwatchBacklightOn()";
$backlight[3] = "and";
$backlight[4] = "TwatchBacklightOff()";

$backlightoff[1] = "They do what you expect";
$backlightoff[2] = "Turning the ";
$backlightoff[3] = "  backlight off";
$backlightoff[4] = "";

$backlighton[1] = "";
$backlighton[2] = "Or turning it ";
$backlighton[3] = "   back on";
$backlighton[4] = "";

$clearscreen = "TwatchClearScreen() does actually clear the screen";

$position =  "Pass a row and column to TwatchPosition() to place the cursor anywhere you want.";
$position2 = "Next print will start at that position. Use it to fix spelling mistakzs";

$preprint = "TwatchPrint() now...";
$print = "TwatchPrint() will print text to whatever position to cursor is at.";

$preprintrows = "TwatchPrintRows is a bit smarter...";
$printrows1[1] = "TwatchPrintRows()";
$printrows1[2] = "Takes an array of";
$printrows1[3] = "4 values and prints";
$printrows1[4] = "one on each line";

$printrows2[1] = "Lines will be padded";
$printrows2[2] = "times and aligned as";
$printrows2[3] = "you want them";
$printrows2[4] = "to be";

$print = "TwatchPrintRows() an array of 4 elementes to be printed on the will print text to whatever position to cursor is at.";

$align[1] = AlignRow("AlignRow() will pad", 'left');
$align[2] = AlignRow("and align left", 'left');
$align[3] = AlignRow("align center", 'center');
$align[4] = AlignRow("or align right", 'right');

$scrollpage = "TwatchScrollPage() will scroll text upwards. You know, like at the end of a movie?";

$pagepage = "TwatchPagePage() is similar, but will move upwards in blocks of four lines instead of line by line.";

$scrollrows[1] = "TwatchScrollRows()";
$scrollrows[2] = "TwatchScrollRows() takes a 4 value array and scrolls those lines that are longer then 20 chars. The others are just displayed statically";
$scrollrows[3] = "Oh, and also:";
$scrollrows[4] = "It will repeat shorter lines untill the longest is scrolled";

$showtime = "TwatchShowTime() does this...";

$scrollascii = "And finally, there is TwatchScrollAscii...";

$feedback[1] = "Get the PHP lib at ";
$feedback[2] = "decock.org/twatch";
$feedback[3] = "Send feedback to";
$feedback[4] = "joost@decock.org";


TwatchConnect($socket);
TwatchBacklightOff($socket);
TwatchClearSCreen($socket);
sleep(2);
TwatchBacklightOn($socket);
sleep(1);
TwatchPagePage($socket, $intro, 4);
TwatchPrintRows($socket, $functions);
sleep(4);
TwatchPrintRows($socket, $connect);
sleep(4);
TwatchPrintRows($socket, $connectbis);
sleep(4);
TwatchPrintRows($socket, $disconnect);
sleep(4);
TwatchPrintRows($socket, $disconnectbis);
sleep(4);
TwatchPrintRows($socket, $backlight);
sleep(4);
TwatchPrintRows($socket, $backlightoff);
sleep(4);
TwatchBacklightOff($socket);
sleep(3);
TwatchClearSCreen($socket);
sleep(1);
TwatchPrintRows($socket, $backlighton);
TwatchBacklightOn($socket);
sleep(4);
TwatchClearSCreen($socket);
TwatchPrint($socket, $clearscreen);
sleep(4);
TwatchClearSCreen($socket);
sleep(2);
TwatchPrint($socket, 'See :)');
sleep(2);
TwatchClearSCreen($socket);
TwatchPrint($socket, $position);
sleep(4);
TwatchClearSCreen($socket);
TwatchPrint($socket, $position2);
sleep(1);
TwatchPosition($socket, 4, 11);
sleep(1);
TwatchPrint($socket, ' ');
sleep(1);
TwatchPosition($socket, 4, 10);
TwatchPrint($socket, ' ');
sleep(1);
TwatchPosition($socket, 4, 10);
sleep(1);
TwatchPrint($socket, 'e');
TwatchPrint($socket, 's');
TwatchPrint($socket, ' ');
TwatchPrint($socket, ';');
TwatchPrint($socket, ')');
sleep(4);

TwatchClearSCreen($socket);
TwatchPrint($socket, $preprint);
sleep(4);
TwatchPrint($socket, $print);
sleep(4);
TwatchClearSCreen($socket);
TwatchPrint($socket, $preprintrow);
sleep(4);
TwatchPrintRows($socket, $printrows1);
sleep(4);
TwatchPrintRows($socket, $printrows2, 1, 'center');

TwatchClearSCreen($socket);
sleep(4);
TwatchPrintRows($socket, $align, 1);

TwatchClearSCreen($socket);
sleep(4);
TwatchScrollPage($socket, $scrollpage,2);

TwatchClearSCreen($socket);
sleep(4);
TwatchPagePage($socket, $pagepage,5);

TwatchClearSCreen($socket);
sleep(4);
TwatchScrollRows($socket, $scrollrows);

TwatchClearSCreen($socket);
TwatchPrint($socket, $showtime);
sleep(4);
TwatchShowTime($socket);

TwatchClearSCreen($socket);
TwatchPrint($socket, $scrollascii);
sleep(4);
TwatchScrollAscii($socket, 'hi');
sleep(4);
TwatchScrollAscii($socket, 'scroll');
TwatchClearSCreen($socket);
sleep(4);
TwatchPrintRows($socket, $feedback, 1, 'center');
sleep(10);
TwatchBacklightOff($socket);
TwatchBacklightOff($socket);
TwatchBacklightOff($socket);
TwatchBacklightOff($socket);
TwatchBacklightOff($socket);
TwatchDisconnect($socket);
?>
