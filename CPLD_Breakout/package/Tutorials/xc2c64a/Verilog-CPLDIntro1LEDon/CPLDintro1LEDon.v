module CPLDintro1LEDon(
    LED,  //these are the connections to the module that we expose externally
	 LED_INV, //external pin number is assigned in the UCF file like this:
				//NET "LED"        	LOC =  "P39";
				//NET "LED_INV"    	LOC =  "P38";
    );	

	 
	output LED;//LED D1 is an output from the module
	output LED_INV; //LED_INV is also an output
	
	reg LED;//a register to output LED
	reg LED_INV; //a register to output LED_INV
	
	always //start of the action section
	begin
		LED=1'b1; //Hold the LED D1 on (high)
		LED_INV=1'b0; //Hold LED D2 off (low)
					//other states are 
					//1'b1 HIGH  
					//1'b0 LOW
					//1'bz HiZ (input) 
	end

endmodule
