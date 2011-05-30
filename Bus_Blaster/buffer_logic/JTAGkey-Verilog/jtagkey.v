//JTAGkey logic for Bus Blaster v2
//Verilog version
//Ported from VHDL version by robots
//http://dangerousprototypes.com/forum/viewtopic.php?f=37&t=1659#p16282
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


	//buffer controlled by FT_JTAG_OE
assign TDI = (FT_JTAG_OE==1'b0)?FT_TDI:1'bZ;
assign 	TMS = (FT_JTAG_OE==1'b0)?FT_TMS:1'bZ;//FT_TMS when FT_JTAG_OE = '0' else 'Z';
assign 	TCK = (FT_JTAG_OE==1'b0)?FT_TCK:1'bZ;//FT_TCK when FT_JTAG_OE = '0' else 'Z';
assign 	RTCK = (FT_JTAG_OE==1'b0)?FT_RTCK:1'bZ;//FT_RTCK when FT_JTAG_OE = '0' else 'Z';
assign 	DBGRQ = (FT_JTAG_OE==1'b0)?FT_DBGRQ:1'bZ;//FT_DBGRQ when FT_JTAG_OE = '0' else 'Z';*/

	//srst
assign 	FT_nSRST_IN = nSRST;
assign 	nSRST = (FT_nSRST_OE==1'b0)?FT_nSRST_OUT:1'bZ; //when FT_nSRST_OE = '0' else 'Z';
	
	//trst
assign 	nTRST = (FT_nTRST_OE==1'b0)?FT_nTRST_OUT:1'bZ; //FT_nTRST_OUT when FT_nTRST_OE = '0' else 'Z';

	//inputs
assign 	FT_TDO = TDO;
assign 	FT_DBGACK = DBGACK;
assign 	FT_TARGET_PRESENT = TARGET_PRESENT;


endmodule

