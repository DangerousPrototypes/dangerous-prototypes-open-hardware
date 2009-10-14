print "5 bit inverse byte lookup table:\n";
print "lookup[] = {\n";
$i=0;

for($i=0;$i<32; $i++){
	$j=0;
	if($i & 0x01){
		$j|=0x10;
	}
		if($i & 0x02){
		$j|=0x08;
	}
		if($i & 0x04){
		$j|=0x04;
	}
		if($i & 0x08){
		$j|=0x02;
	}
		if($i & 0x10){
		$j|=0x01;
	}
	
	#print "$i:$j\n"; #debug
	print "$j, "
}
print "\n}\n";