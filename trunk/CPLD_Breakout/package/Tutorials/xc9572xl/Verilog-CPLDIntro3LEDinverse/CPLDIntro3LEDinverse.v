module CPLDIntro3LEDinverse(
    LED,  //these are the connections to the module that we expose externally
     LED_INV, //external pin number is assigned in the UCF file like this:
     BUTTON //
                //NET "LED"            LOC =  "P39";
                //NET "LED_INV"        LOC =  "P38";
    );        //NET "BUTTON"        LOC =  "P18";

     
    output LED;//LED D1 is an output from the module
    output LED_INV; //LED_INV is also an output
   
    input BUTTON; //button is an input signal
   
    reg LED;//a register to output LED
    reg LED_INV; //a register to output LED_INV
   
    wire BUTTON; //input button is a wire
   
    always @ (BUTTON) //start of the action section
    begin
        LED=BUTTON; //Set reg LED to the value of wire BUTTON
        LED_INV=!BUTTON; //Set reg LED_INV opposite of wire BUTTON
    end

endmodule