/*
Macrocells Used Pterms Used Registers Used Pins Used Function Block Inputs Used 
68/72  (95%) 229/360  (64%) 65/72  (91%) 34/34  (100%) 147/216  (69%) 


*/

/*
isim force add {/sram_counter/osc_clock} 1 -radix bin -value 0 -radix bin -time 500 ps -repeat 1 ns 
isim force add {/sram_counter/pic_clock} 1 -radix bin -value 0 -radix bin -time 500 ps -repeat 2 ns 
isim force add {/sram_counter/ext_clock} 1 -radix bin -value 0 -radix bin -time 500 ps -repeat 3 ns 
isim force add {/sram_counter/mode_setup} 0 -radix bin 
isim force add {/sram_counter/mode_run} 0 -radix bin 
isim force add {/sram_counter/mode_read} 0 -radix bin 
isim force add {/sram_counter/pins} 00000000 -radix bin 
isim force add {/sram_counter/trigger_value} 00000001 -radix bin 
isim force add {/sram_counter/trigger_mask} 00000001 -radix bin 
isim force add {/sram_counter/sample_reg} 0000000000111 -radix bin 
isim force add {/sram_counter/mode_clock} 0001 -radix bin 

isim force add {/sram_counter/setup_reg} 00000001 -radix bin 


isim force add {/sram_counter/trigger} 0 -radix bin 
*/
module sram_counter (
pic_clock, 
osc_clock,
sram_clock,
sram_address, 
pins,
mode_setup,
mode_run,
mode_read,
mode_clock,
done
); 
//global
 input wire pic_clock;
 input wire osc_clock;
 input wire [7:0] pins;
 input wire mode_setup;
 input wire mode_run;
 input wire mode_read;
 input wire [3:0] mode_clock;
 
 output wire done;
 output reg [14:0] sram_address;
 output wire sram_clock;
 
 //local
// (* keep = "true" *) reg [7:0] trigger_mask;
 reg trigger_match;
 wire trigger;
 reg [15:0] sample_counter;//holds trigger and sample counter settings
 //reg [7:0] trigger_value;
 //reg [15:8] trigger_mask;
 //reg [28:16] sample_reg; //holds sample count, 
				//SUMP protocol gives samples in /4, 
				//so we can use two bits less thans sample_counter
 reg [28:0] setup_reg; //all registers in one big one works best
 
//registers for the clock divider
 reg [2:0] clock_divider; //subtract from here to divide the clock
 reg div_clock; //divider output signal

 assign master_clock=(mode_clock[0])?div_clock:((mode_clock[1])?osc_clock:((mode_clock[2])?pins[0]:pic_clock));

 //assign trigger=(((pins[7:0] ^ trigger_value[7:0]) & trigger_mask[7:0])==0);
 assign trigger=(((pins[7:0] ^ setup_reg[7:0]) & setup_reg[15:8])==0);
 
 assign done=(sample_counter[15]==0); //we are done when the top bit of sample counter flips to 0
 
 assign sram_clock=(!done||mode_read)?master_clock:1'b0;
  
initial 
 begin
	sram_address=15'b000000000000000;
	sample_counter=16'b1000000000001111;
	//sample_reg=13'b0000000000111;
	clock_divider=3'b000;
	div_clock=1'b0;
	trigger_match=1'b0;
 end
 
always @ (posedge osc_clock)
 begin
	if(clock_divider==3'b000) begin
		clock_divider<=mode_clock[3:1];//reuse clock setup 3:1 as divider value
		div_clock<=div_clock-1;
	end
	else begin
		clock_divider<=clock_divider-1;
	end
 end

always @ (posedge trigger or posedge mode_run)
 begin
 	if(mode_run)begin
		trigger_match<=1'b0;
	end
	else if (trigger) begin
		trigger_match<=1'b1;		
	end 
 end

always @ (posedge master_clock) 
 begin
   if(mode_setup) begin
		setup_reg={setup_reg[27:0], mode_read}; //in setup mode reuse bit 3 as SDI
   end	
	else if(mode_run) begin
	  	sample_counter[15]<=1'b1;
		sample_counter[14:2]<=setup_reg[28:16]; //must use this half-step or there are pterm issues
		sample_counter[1:0]<=2'b00;
		//trigger_match<=1'b0;
	end
	else if (mode_read) begin
		sram_address <= sram_address - 1; //down count
	end
	else if(!done) begin
		sram_address <= sram_address + 1; //up count
		if (trigger_match) begin
			//trigger_match<=1'b1;
			sample_counter<=sample_counter-1;
		end
	end
 end
  
endmodule // End of Module counter
