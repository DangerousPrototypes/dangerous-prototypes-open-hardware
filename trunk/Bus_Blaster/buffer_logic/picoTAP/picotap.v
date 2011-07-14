//picoTAP logic for Bus Blaster v2
//Verilog version
//Ported from VHDL JTAGKEY version by robots
//http://dangerousprototypes.com/forum/viewtopic.php?f=37&t=1659#p16282
module picotap(
           FT_TDO ,
           FT_TDI ,
           FT_TCK ,
           FT_TMS ,
           FT_nTRST_OUT ,
           TDO ,
           TCK ,
           TDI ,
           TMS ,
			  nTRST
			  );

output wire FT_TDO;
input wire FT_TDI;
input wire FT_TCK;
input wire FT_TMS;
input wire FT_nTRST_OUT;
input wire TDO;
output wire TCK;
output wire TDI;
output wire TMS;
output wire nTRST;

	//outputs
assign TDI = FT_TDI;
assign 	TMS = FT_TMS;
assign 	TCK = FT_TCK;
assign 	nTRST = FT_nTRST_OUT; 

	//inputs
assign 	FT_TDO = TDO;

endmodule

