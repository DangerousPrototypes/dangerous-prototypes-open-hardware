<?php
#
# Not as much written as thrown together by joost@decock.org
#
# Get updates at http://decock.org/twatch
#

// IP of your #twatch  (better setup a fixed lease in your DHCP server)
$TWATCH_IP = '10.56.0.12';

// Port the #twatch listens on
$TWATCH_PORT = '1337';

// How long do you want to wait for the socket connection? (in seconds)
$TWATCH_TIMEOUT = '3';

// Some commands we'll be using to send to the #twatch
$COMMANDS[backlighton]   = pack("C*", 0xFE, 0x42, 0x00);
$COMMANDS[backlightoff]  = pack("C*", 0xFE, 0x46);
$COMMANDS[cleardisplay]  = pack("C*", 0xFE, 0x58);
$COMMANDS[home]          = pack("C*", 0xFE, 0x48);
$COMMANDS[emptyrow]      = '                    ';

/*  Set up TCP connection to the #twatch
  Arguments:
    &$socket => The file pointer that will be created
  Returns:
    Nothing, socket will be created   
*/
function TwatchConnect(&$socket) {
  GLOBAL $TWATCH_IP, $TWATCH_PORT, $TWATCH_TIMEOUT;
  $socket = fsockopen('tcp://'.$TWATCH_IP, $TWATCH_PORT, $errno, $errstring, $TWATCH_TIMEOUT);
}


/* Close TCP connection to the #twatch
  Arguments:
    &$socket => The file pointer to the open socket
  Returns:
    Nothing, socket will be closed
*/
function TwatchDisconnect(&$socket) {
  fclose($socket);
}


/* Turn #twatch backlight on
  Arguments:
    &$socket => The file pointer to the open socket
  Returns:
    Result of the fwrite(the command) 
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
*/
function TwatchBacklightOn(&$socket) {
  GLOBAL $COMMANDS;  
  return fwrite($socket, $COMMANDS[backlighton]);
}

/* Turn #twatch backlight off
  Arguments:
    &$socket => The file pointer to the open socket
  Returns:
    Result of the fwrite(the command) 
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
*/
function TwatchBacklightOff(&$socket) {
  GLOBAL $COMMANDS;  
  return fwrite($socket, $COMMANDS[backlightoff]);
}

/* Clear the #twatch display
  Arguments:
    &$socket => The file pointer to the open socket
  Returns:
    Result of the fwrite(the command) 
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
*/
function TwatchClearScreen(&$socket) {
  GLOBAL $COMMANDS;  
  return fwrite($socket, $COMMANDS[cleardisplay]);
}

/* Position cursor on the #twatch
  Arguments:
    &$socket => The file pointer to the open socket
    $row     => The row you want to use (1->4) (default is 1)
    $col     => The column you want to use (1->20) (default is 1)
  Returns:
    Result of the fwrite(the command) 
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
*/
function TwatchPosition(&$socket, $row=1, $col=1) {
  // dechex() doesn't seem to do it for values higher then 9
  // and I'm too lazy to figure it out
  $hex = Array( 0 => 0x00, 1 => 0x01, 2 => 0x02, 3 => 0x03, 4 => 0x04, 5 => 0x05, 
                  6 => 0x06, 7 => 0x07, 8 => 0x08, 9 => 0x09, 10 => 0x0A, 
                  11 => 0x0B, 12 => 0x0C, 13 => 0x0D, 14 => 0x0E,    
                  15 => 0x0F, 16 => 0x10, 17 => 0x11, 18 => 0x12, 19 => 0x13 ); 
  $col = $hex[$col];  
  return fwrite($socket, pack("C*", 0xFE, 0x47, $col, dechex($row)));
}

/* Print blob of text on whatever position the cursor is
  Arguments:
    &$socket => The file pointer to the open socket
    $text    => The text you want to print 
  Returns:
    Result of the fwrite(the command) 
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
    bY PRINT i mean 'show in the #twatch display';
    This doesn't do any sort of checking on the input.
*/
function TwatchPrint(&$socket, $text) {
  return fwrite($socket, $text);
}

/* Pass an array with four elements containing the text of the four rows
// Rows are not truncated to 20 chars, so watch out not to spill over
  Arguments:
    &$socket => The file pointer to the open socket
    $rows    => The array containing 4 elements 
                each element should containt the text of one row
    $delay   => The delay (pause) to introduce between each printed line
                Value is in seconds. Default is no delay (-1).
                If you use 1, the first line will be printed, and one
                second later the second line, and so on.
    $align   => How to align the text on each line.
                Possible values:
                  left (default)
                  right
                  center
  Returns:
    Err.. nothing it seems
  Notes:
    fwrite() returns the number of bytes written, or FALSE on error.
    By print I mean 'show in the #twatch display';
    This doesn't do any sort of checking on the input.
*/
function TwatchPrintRows(&$socket, $rows, $delay=-1, $align='left') {
  GLOBAL $COMMANDS;
  foreach ($rows as $row => $text) {
    TwatchPosition($socket, $row);
    if($delay != -1) sleep($delay);
    TwatchPrint($socket, AlignRow($text, $align));
  }
}


/* Aligns an input string by padding it up to 20 chars
  Arguments:
    &$socket => The file pointer to the open socket
    $align   => How to align the text on each line.
                Possible values:
                  left (default)
                  right
                  center
    $padding => The character to pad the string with (default = space)
  Returns:
    The input string padded and aligned
  Notes:
    When the string can't be centered precisely (because it has an 
    uneven length) it will be one char closer to the left then the right.
*/
function AlignRow($row, $align, $padding=' ') {
  if($align=='right') return str_pad($row, 20, $padding, STR_PAD_LEFT);
  elseif($align=='center') {
    $margin = floor((20-strlen($row))/2);
    return str_pad(str_pad('',$margin, $padding,STR_PAD_LEFT).$row, 20, ' ');
  }
  else return  str_pad($row, 20, $padding);
}


/* Scrolls a page (4 lines on the #twatch) upwards line by line
  Arguments:
    &$socket => The file pointer to the open socket
    $text    => The blob of text you want to show
                Possible values:
                  left (default)
                  right
                  center
    $delay   => The delay (pause) to introduce between each printed line
                Value is in seconds. Default is no delay (-1).
                If you use 1, the screen will be filled, and one
                second shifted up a row, and so on.
  Returns:
    Err.. nothing it seems
  Notes:
    Paging upwards seems to be making much more sense then scrolling upward
    You may want to look into TwatchPagePage()
*/
function TwatchScrollPage(&$socket, $text, $delay=-1) {
  GLOBAL $COMMANDS;
  $text = chunk_split($text, 20);
  $text = explode("\r\n",$text);
  $lines = count($text);
  $active_line = 0;
  while($active_line < $lines) {
    for($i=1;$i<=4;$i++) {
      $thisline = $active_line + $i -1;
      if(isset($text[$thisline]) && strlen($text[$thisline])>0) $thistext = $text[$thisline];
      else $thistext = $COMMANDS[emptyrow];
      if(strlen($thistext)<20) $thistext = str_pad($thistext, 20);
      $output .= $thistext;
    }
    TwatchPosition($socket, 1, 1);
    TwatchPrint($socket, $output);
    unset($output);
    if($delay != -1) sleep($delay);
    $active_line++;
  }
}

/* Pages a page (4 lines on the #twatch) so replaces 4 lines by the next 4 lines
  Arguments:
    &$socket => The file pointer to the open socket
    $text    => The blob of text you want to show
    $delay   => The delay (pause) to introduce between each printed page
                Value is in seconds. Default is no delay (-1).
                If you use 1, the page will be printed, and one
                second the next page, and so on.
  Returns:
    Err.. nothing it seems
  Notes:
    You'll probably need some delay here
*/
function TwatchPagePage(&$socket, $text, $delay=-1) {
  GLOBAL $COMMANDS;
  $text = chunk_split($text, 80);
  $text = explode("\r\n",$text);
  $pages = count($text);
  $active_page = 0;
  foreach($text as $thistext) {
    if(strlen($thistext)<80) $thistext = str_pad($thistext, 80);
    TwatchPosition($socket, 1, 1);
    TwatchPrint($socket, $thistext);
    if($delay != -1) sleep($delay);
  }
}

/* Pass an array with four elements containing the text of the four rows
// Rows longer then 20 chars are scrolled right to left, with repeat
  Arguments:
    &$socket => The file pointer to the open socket
    $rows    => The array containing 4 elements 
                each element should containt the text of one row
    $join    => When scrolling through a line multiple times, 
                  join with this string.
                  Default is : ' | ' (without the quotes)
    $repeat  => How many times you want to scroll the longest line. 
                Default is 1
    $delay   => The delay (pause) to introduce between each scroll step
                Value is in seconds. Default is 0.5 seconds.
    $align   => How to align the text on the non-scrolled lines.
                Possible values:
                  left (default)
                  right
                  center
  Returns:
    Err.. nothing it seems
  Notes:
    Lines that are shorter then 20 chars are handles just as in
      TwatchPrintRows. Only longer lines are scrolled.
*/
function TwatchScrollRows(&$socket, $rows, $delay=250000, $repeat=1, $join=' | ', $align='left') {
  $gap = '                    ';
  $joinlen = strlen($join);
  foreach ($rows as $row => $text) {
    $len[$row] = strlen($text);
    if($len[$row] > 20) $scroll[$row] = 1;
    if($len[$row] >= $maxlen) {
      $maxlen = $len[$row];
      $longest = $row;
    }
  }
  $rows[$longest] = substr(str_repeat($rows[$longest].$join, $repeat),0, $joinlen*-1);
  foreach ($rows as $row => $text) {
    if($scroll[$row] == 1) {
      if($row != $longest) {
        $rowrepeat = floor($maxlen*$repeat/($len[$row]+$joinlen));
        if($rowrepeat == 0) $rowrepeat = 1;
        $padrows[$row] = substr(str_repeat($rows[$row].$join, $rowrepeat),0, $joinlen*-1);
      }
      else $padrows[$row] = $rows[$row]; 
      $padrows[$row] = $gap.$padrows[$row].$gap;
    }
    else $padrows[$row] = $rows[$row];
  }
  if(!isset($scroll)) return TwatchPrintRows($socket, $rows, $delay, $align);
  else {
    $step = 0;
    $steps = ($repeat*$maxlen)+21;
    while($step < $steps) {
      foreach ($padrows as $row => $text) {
        if($scroll[$row] == 1) $lines[$row] = substr($padrows[$row], $step, 20);
        else $lines[$row] = AlignRow($rows[$row], $align);
      }
      TwatchPrintRows($socket, $lines);
      if($delay != -1) usleep($delay);
      $step++;
    }
  }
 return $padrows;
}

/* Showes date and time 
  Arguments:
    &$socket => The file pointer to the open socket
    $delay   => The delay (pause) to introduce between each printed line
                Value is in seconds. Default is no delay (-1).
  Returns:
    Err.. nothing it seems
  Notes:
    Is should look like this:
       +------------------+
       | 02 December 2009 |
       | Wednesday  16:47 |
       +------------------+
*/
function TwatchShowTime(&$socket, $delay=-1) {
  setlocale(LC_ALL, 'nl_NL.UTF8');
  $time[1] = '                    '; 
  $time[2] = strftime('%d %B %Y');
  $len = strlen($time[2]);
  $time[2] = AlignRow($time[2],'center');
  $day3 = strftime('%A');
  $time3= strftime('%R');
  $spacer = $len-strlen($day3.$time3);
  $time[3] = $day3.str_pad('',$spacer,' ').$time3;
  $time[3] =  AlignRow($time[3],'center');
  $time[4] = $time[1];
  TwatchPrintRows($socket,$time, $delay, 'center');
  if($delay != -1) sleep($delay);
}

/*  Scroll ascii art text
  Arguments:
    &$socket => The file pointer that will be created
    $text    => The text to scroll
    $delay   => The delay to use between scrolling steps
  Returns:
    Nothing, socket will be created   
*/
function TwatchScrollAscii(&$socket, $text, $delay=-1) {

$ASCII[space][1] = "    ";
$ASCII[space][2] = "    ";
$ASCII[space][3] = "    ";
$ASCII[space][4] = "    ";

$ASCII[a][1] = "   __   ";
$ASCII[a][2] = "  /__\  ";
$ASCII[a][3] = " /(__)\ ";
$ASCII[a][4] = "(__)(__)";

$ASCII[b][1] = " ____  ";
$ASCII[b][2] = "(  _ \ ";
$ASCII[b][3] = " ) _ < ";
$ASCII[b][4] = "(____/ "; 

$ASCII[c][1] = "  ___ ";
$ASCII[c][2] = " / __)";
$ASCII[c][3] = "( (__ ";
$ASCII[c][4] = " \___)";

$ASCII[d][1] = " ____  ";
$ASCII[d][2] = "(  _ \ ";
$ASCII[d][3] = " )(_) )";
$ASCII[d][4] = "(____/ ";

$ASCII[e][1] = " ____ ";
$ASCII[e][2] = "( ___)";
$ASCII[e][3] = " )__) ";
$ASCII[e][4] = "(____)";

$ASCII[f][1] = " ____ ";
$ASCII[f][2] = "( ___)";
$ASCII[f][3] = " )__) ";
$ASCII[f][4] = "(__)  ";

$ASCII[g][1] = "  ___ ";
$ASCII[g][2] = " / __)";
$ASCII[g][3] = "( (_-.";
$ASCII[g][4] = " \___/";

$ASCII[h][1] = " _   _ ";
$ASCII[h][2] = "( )_( )";
$ASCII[h][3] = " ) _ ( ";
$ASCII[h][4] = "(_) (_)";

$ASCII[i][1] = " ____ ";
$ASCII[i][2] = "(_  _)";
$ASCII[i][3] = " _)(_ ";
$ASCII[i][4] = "(____)";

$ASCII[j][1] = "  ____ ";
$ASCII[j][2] = " (_  _)";
$ASCII[j][3] = ".-_)(  ";
$ASCII[j][4] = "\____) ";

$ASCII[k][1] = " _  _ ";
$ASCII[k][2] = "( )/ )";
$ASCII[k][3] = " )  ( ";
$ASCII[k][4] = "(_)\_)";

$ASCII[l][1] = " __   ";
$ASCII[l][2] = "(  )  ";
$ASCII[l][3] = " )(__ ";
$ASCII[l][4] = "(____)";

$ASCII[m][1] = " __  __ ";
$ASCII[m][2] = "(  \/  )";
$ASCII[m][3] = " )    ( ";
$ASCII[m][4] = "(_/\/\_)";

$ASCII[n][1] = " _  _ ";
$ASCII[n][2] = "( \( )";
$ASCII[n][3] = " )  ( ";
$ASCII[n][4] = "(_)\_)";

$ASCII[o][1] = " _____ ";
$ASCII[o][2] = "(  _  )";
$ASCII[o][3] = " )(_)( ";
$ASCII[o][4] = "(_____)";

$ASCII[p][1] = " ____ ";
$ASCII[p][2] = "(  _ \\";
$ASCII[p][3] = " )___/";
$ASCII[p][4] = "(__)  ";

$ASCII[q][1] = " _____ ";
$ASCII[q][2] = "(  _  )";
$ASCII[q][3] = " )(_)( ";
$ASCII[q][4] = "(___/\\\\";

$ASCII[r][1] = " ____ ";
$ASCII[r][2] = "(  _ \\";
$ASCII[r][3] = " )   /";
$ASCII[r][4] = "(_)\_)";

$ASCII[s][1] = " ___ ";
$ASCII[s][2] = "/ __)";
$ASCII[s][3] = "\__ \\";
$ASCII[s][4] = "(___/";

$ASCII[t][1] = " ____ ";
$ASCII[t][2] = "(_  _)";
$ASCII[t][3] = "  )(  ";
$ASCII[t][4] = " (__) ";

$ASCII[u][1] = " __  __ ";
$ASCII[u][2] = "(  )(  )";
$ASCII[u][3] = " )(__)( ";
$ASCII[u][4] = "(______)";

$ASCII[v][1] = " _  _ ";
$ASCII[v][2] = "( \/ )";
$ASCII[v][3] = " \  / ";
$ASCII[v][4] = "  \/  ";

$ASCII[w][1] = " _    _ ";
$ASCII[w][2] = "( \/\/ )";
$ASCII[w][3] = " )    ( ";
$ASCII[w][4] = "(__/\__)";

$ASCII[x][1] = " _  _ ";
$ASCII[x][2] = "( \/ )";
$ASCII[x][3] = " )  ( ";
$ASCII[x][4] = "(_/\_)";

$ASCII[y][1] = " _  _ ";
$ASCII[y][2] = "( \/ )";
$ASCII[y][3] = " \  / ";
$ASCII[y][4] = " (__) ";

$ASCII[z][1] = " ____ ";
$ASCII[z][2] = "(_   )";
$ASCII[z][3] = " / /_ ";
$ASCII[z][4] = "(____)";

     
$ASCII[dash][1] = " ___ ";
$ASCII[dash][2] = "(___)";
$ASCII[dash][3] = "     ";
$ASCII[dash][4] = "     ";

$ASCII[underscore][1] = "       ";
$ASCII[underscore][2] = "       ";
$ASCII[underscore][3] = " _____ ";
$ASCII[underscore][4] = "(_____)";

$ASCII[comma][1] = "  ";
$ASCII[comma][2] = "  ";
$ASCII[comma][3] = "()";
$ASCII[comma][4] = "/ ";

$ASCII[dot][1] = "  ";
$ASCII[dot][2] = "  ";
$ASCII[dot][3] = "  ";
$ASCII[dot][4] = "()";

$ASCII[plus][1] = "   _   ";   
$ASCII[plus][2] = " _| |_ ";
$ASCII[plus][3] = "(_   _)";
$ASCII[plus][4] = "  |_|  ";

$ASCII[emark][1] = "/\\";
$ASCII[emark][2] = ")(";
$ASCII[emark][3] = "\/";
$ASCII[emark][4] = "()";

$ASCII[qmark][1] = " ___ ";
$ASCII[qmark][2] = "(__ )";
$ASCII[qmark][3] = " (_/ ";
$ASCII[qmark][4] = " (_) ";

$ASCII[at][1] = "  __ ";
$ASCII[at][2] = " /  \\";
$ASCII[at][3] = "| ()/";
$ASCII[at][4] = " \__ ";

$ASCII[hash][1] = " | | ";
$ASCII[hash][2] = "-|-|-";
$ASCII[hash][3] = "-|-|-";
$ASCII[hash][4] = " | | ";

$ASCII[0][1] = "  ___  ";
$ASCII[0][2] = " / _ \ ";
$ASCII[0][3] = "( (_) )";
$ASCII[0][4] = " \___/ ";

$ASCII[1][1] = " __ ";
$ASCII[1][2] = "/  )";
$ASCII[1][3] = " )( ";
$ASCII[1][4] = "(__)";

$ASCII[2][1] = " ___  ";
$ASCII[2][2] = "(__ \ ";
$ASCII[2][3] = " / _/ ";
$ASCII[2][4] = "(____)";

$ASCII[3][1] = " ___ ";
$ASCII[3][2] = "(__ )";
$ASCII[3][3] = " (_ \\";
$ASCII[3][4] = "(___/";

$ASCII[4][1] = "  __  ";
$ASCII[4][2] = " /. | ";
$ASCII[4][3] = "(_  _)";
$ASCII[4][4] = "  (_) ";

$ASCII[5][1] = " ___ ";
$ASCII[5][2] = "| __)";
$ASCII[5][3] = "|__ \\";
$ASCII[5][4] = "(___/";

$ASCII[6][1] = "  _  ";
$ASCII[6][2] = " / ) ";
$ASCII[6][3] = "/ _ \\";
$ASCII[6][4] = "\___/";

$ASCII[7][1] = " ___ ";
$ASCII[7][2] = "(__ )";
$ASCII[7][3] = " / / ";
$ASCII[7][4] = "(_/  ";

$ASCII[8][1] = " ___ ";
$ASCII[8][2] = "( _ )";
$ASCII[8][3] = "/ _ \\";
$ASCII[8][4] = "\___/";

$ASCII[9][1] = " ___ ";
$ASCII[9][2] = "/ _ \\";
$ASCII[9][3] = "\_  /";
$ASCII[9][4] = " (_/ ";

  $text = str_split(strtolower($text));
  foreach($text as $char) {
    if($char == '-') $char = 'dash'; 
    elseif($char == '+') $char = 'plus'; 
    elseif($char == '.') $char = 'dot'; 
    elseif($char == ',') $char = 'comma'; 
    elseif($char == '@') $char = 'at'; 
    elseif($char == '#') $char = 'hash'; 
    elseif($char == '!') $char = 'emark'; 
    elseif($char == '?') $char = 'qmark'; 
    elseif($char == '_') $char = 'underscore'; 
    elseif($char == ' ') $char = 'space'; 
    if(isset($ASCII[$char])) $add = $ASCII[$char];
    else $add = $ASCII[space];
    $rows[1] .= $add[1];
    $rows[2] .= $add[2];
    $rows[3] .= $add[3];
    $rows[4] .= $add[4];
  }
  return TwatchScrollRows($socket, $rows, $delay);
}



?>
