<?php
//create a counter.txt file, CHMOD it to 0777, be sure to enter 0 to start or you get an error
//open counter file
$file="counter.txt";
$fp = fopen ($file, "r");
$count = fread ($fp, filesize ($file));
fclose($fp); 

//convert to integer, increment, convert to string...
$count = (string)( ( (int)($count) ) + 1 );

//save the incremented number
$fp = fopen ($file, "w");
fwrite ($fp, $count);
fclose($fp);

//send a transparent 1px image
$file = "1px.png";
header("Cache-Control: no-cache");
header("Pragma: no-cache");
header("Content-type: image/png");
header("Content-size: " . filesize($file));
readfile($file);
?>