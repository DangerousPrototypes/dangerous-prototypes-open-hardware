;I bought RC helicopter yesterday and it's IR one so first thing I did is to see what IR Toy has to say about it :) First thing i noticed is that when you for example push throttle it I guess sends command and then for next couple seconds continues to emit something like data stream. I recorded couple seconds with irtoy.exe and replayed successfully. Then I wanted to see in OLS how the stream looks... And then I saw that there is limit to 1k for irtoy :(
;Because Im not programmer but occasionally write some  vb code and lately use autoit mostly for simple things I made in autoit simple program to convert irtoy.exe hex data from .bin file to ols file format... quick sample that i tried works ok ... anyway... here is source and compiled exe ... you just select bin file and ols file is created next to it... you can use and modify code as you wish
;
;http://siklosi.users.sbb.rs/irtoy2ols.au3
;http://siklosi.users.sbb.rs/irtoy2ols.exe
;
;Ill go now back to where I started... analyzing RC heli's IR stream :) 
;
; From: http://dangerousprototypes.com/forum/index.php?topic=1183.msg12275#msg12275
$fileo=FileOpenDialog("Select IR Toy generated file",@ScriptDir, "Binary (*.bin)",3) ; fileopen dialog or you can use $file = ConsoleRead() if you want console version
if $fileo="" then
	$m=MsgBox(0,"Error", " No file selected, exiting!")
	Exit
EndIf

;$files= FileSaveDialog("Select OLS file",@scriptdir, "OLS (*.ols)) ; file to save selecting with dialog 
;if $fileo="" then
;	$m=MsgBox(0,"Error", " No destination file selected, exiting!")
;	Exit
;EndIf

$files = stringleft($fileo,StringLen($fileo)-4)&".ols" ;file to save same as original only extension changed to ols
$file1 = FileOpen($fileo,16) ; Open file as Binary (16)
$file2 = FileOpen($files,2) 
ConsoleWrite(StringLeft($fileo,StringLen($fileo)-4)&".ols")
$absolute = 0
$io=0
$size=0
$dtw = 0

;read all to get absolute lenght and size
while 1
$irtoydata=FileRead($file1,2)
If @error = -1 Then ExitLoop

$hexa = Binary(BinaryToString($irtoydata,1))
$decimalno=dec(StringRight($hexa,4))
	if $decimalno < 65535 then 
		$size=$size+1
		$absolute= $absolute + $decimalno
	EndIf
WEnd

;header of ols file
filewriteline($file2,";Size: "&$size)
filewriteline($file2,";Rate: 213333")
filewriteline($file2,";Channels: 32")
filewriteline($file2,";EnabledChannels: 255")
filewriteline($file2,";TriggerPosition: 0")
filewriteline($file2,";Compressed: true")
filewriteline($file2,";AbsoluteLength: "&$absolute+200)
filewriteline($file2,";CursorEnabled: false")
filewriteline($file2,";Cursor0: -9223372036854775808")
filewriteline($file2,";Cursor1: -9223372036854775808")
filewriteline($file2,";Cursor2: -9223372036854775808")
filewriteline($file2,";Cursor3: -9223372036854775808")
filewriteline($file2,";Cursor4: -9223372036854775808")
filewriteline($file2,";Cursor5: -9223372036854775808")
filewriteline($file2,";Cursor6: -9223372036854775808")
filewriteline($file2,";Cursor7: -9223372036854775808")
filewriteline($file2,";Cursor8: -9223372036854775808")
filewriteline($file2,";Cursor9: -9223372036854775808")

FileSetPos($file1,0,0) ; return to begining of file1
while 1

$irtoydata=FileRead($file1,2)
If @error = -1 Then ExitLoop
$hexa = Binary(BinaryToString($irtoydata,1))
$decimalno=dec(StringRight($hexa,4))
$irtime=$decimalno

if $io = 0 then 
	if $decimalno < 65535 then 
		$dtw = $dtw + $decimalno
		filewriteline($file2,"00000000@"&$dtw&@CRLF)
		$io = 1
	EndIf
else 
	if $decimalno < 65535 then
		$dtw = $dtw+$decimalno
	    filewriteline($file2,"00000001@"&$dtw&@CRLF)
		$io = 0
	EndIf	
EndIf

WEnd
$m=MsgBox(0,"All Done","Conversion from irtoy binary to ols format finished! File saved as:"&@cr&$files)
Exit
