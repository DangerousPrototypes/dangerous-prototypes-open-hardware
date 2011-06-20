//JTAGkey logic for Bus Blaster v2
//Verilog version
//Ported from VHDL version by robots
//http://dangerousprototypes.com/forum/viewtopic.php?f=37&t=1659#p16282
// License: CC-0 (public domain)
module jtagkey(
			FT_JTAG_OE ,
			FT_TDO ,
			FT_TDI ,
			FT_TCK ,
			FT_RTCK ,
			FT_TMS ,
			FT_DBGRQ ,
			FT_DBGACK ,
			FT_nSRST_OE ,
			FT_nSRST_IN ,
			FT_nSRST_OUT ,
			FT_nTRST_OE ,
			FT_nTRST_OUT ,
			RTCK ,
			TDO ,
			TCK ,
			TDI ,
			TMS ,
			nSRST,
			nTRST,
			DBGACK ,
			DBGRQ ,
			FT_TARGET_PRESENT,
			TARGET_PRESENT,
			TEST_MODE
			  );

input wire FT_JTAG_OE;
output wire FT_TDO;
input wire FT_TDI;
input wire FT_TCK;
input wire FT_RTCK;
input wire FT_TMS;
input wire FT_DBGRQ;
output wire FT_DBGACK;
input wire FT_nSRST_OE;
output wire FT_nSRST_IN;
input wire FT_nSRST_OUT;
input wire FT_nTRST_OE;
input wire FT_nTRST_OUT;
output wire RTCK;
input wire TDO;
output wire TCK;
output wire TDI;
output wire TMS;
inout wire nSRST;
inout wire nTRST;
input wire DBGACK;
output wire DBGRQ;
output wire FT_TARGET_PRESENT;
input wire TARGET_PRESENT;
input wire TEST_MODE;

always @ (*)
	begin
		if(TEST_MODE==1'b0) begin
			//assign the connections
			//assign jtag_out[3:0]=ADBUS[3:0]; //on JTAG pins we should see ls nibble that we write to ADBUS
			//assign ACBUS[3:0]=jtag_in[3:0]; 
			//assign ACBUS[7:4]=ADBUS[7:4]; //so this 4 pins work, who cares
			//ACBUS <= ADBUS
			FT_nTRST_OUT <= FT_TCK;
			FT_nSRST_OUT <= FT_TDI;
			FT_nTRST_OE  <= FT_TDO;
			FT_nSRST_OE  <= FT_TMS;
			
			//loop back FTDI output
			TDI          <= FT_JTAG_OE;
			TCK          <= FT_TARGET_PRESENT;
			TDO          <= FT_nSRST_IN;
			DBGRQ        <= FT_RTCK;
			//loop back FTDI inputs
			FT_DBGRQ     <= nTRST;
			FT_DBGACK    <= TMS;
			ACBUS6       <= RTCK;
			ACBUS7       <= nSRST;
		end
		else begin
		//need inout: TDO, TMS, rtck, FT_nTRST_OUT, FT_nSRST_OUT, FT_nTRST_OE, FT_nSRST_OE, FT_DBGRQ, FT_TDO, FT_TARGET_PRESENT, FT_nSRST_IN, nTRST, nSRST
			//buffer controlled by FT_JTAG_OE
			TDI <= (FT_JTAG_OE==1'b0)?FT_TDI:1'bZ;
			TMS <= (FT_JTAG_OE==1'b0)?FT_TMS:1'bZ;//FT_TMS when FT_JTAG_OE = '0' else 'Z';
			TCK <= (FT_JTAG_OE==1'b0)?FT_TCK:1'bZ;//FT_TCK when FT_JTAG_OE = '0' else 'Z';
			RTCK <= (FT_JTAG_OE==1'b0)?FT_RTCK:1'bZ;//FT_RTCK when FT_JTAG_OE = '0' else 'Z';
			DBGRQ <= (FT_JTAG_OE==1'b0)?FT_DBGRQ:1'bZ;//FT_DBGRQ when FT_JTAG_OE = '0' else 'Z';*/

			//srst
			FT_nSRST_IN <= nSRST;
			nSRST <= (FT_nSRST_OE==1'b0)?FT_nSRST_OUT:1'bZ; //when FT_nSRST_OE = '0' else 'Z';

			//trst
			nTRST <= (FT_nTRST_OE==1'b0)?FT_nTRST_OUT:1'bZ; //FT_nTRST_OUT when FT_nTRST_OE = '0' else 'Z';

			//inputs
			FT_TDO <= TDO;
			FT_DBGACK <= DBGACK;
			FT_TARGET_PRESENT <= TARGET_PRESENT;				
		end
	end
endmodule

