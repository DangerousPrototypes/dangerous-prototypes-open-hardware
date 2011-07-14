//JTAGkey logic for Bus Blaster v2 with hardware self-test feature
//http://dangerousprototypes.com/docs/Bus_Blaster_v2_manufacturing_resources#Hardware_selftest
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
			TEST_MODE_0,
			TEST_MODE_1,
			TEST_MODE_2,
			ACBUS6,
			ACBUS7
			  );

inout wire FT_JTAG_OE;
inout wire FT_TDO;
inout wire FT_TDI;
inout wire FT_TCK;
inout wire FT_RTCK;
inout wire FT_TMS;
inout wire FT_DBGRQ;
inout wire FT_DBGACK;
inout wire FT_nSRST_OE;
inout wire FT_nSRST_IN;
inout wire FT_nSRST_OUT;
inout wire FT_nTRST_OE;
inout wire FT_nTRST_OUT;
inout wire RTCK;
inout wire TDO;
inout wire TCK;
inout wire TDI;
inout wire TMS;
inout wire nSRST;
inout wire nTRST;
inout wire DBGACK;
inout wire DBGRQ;
inout wire FT_TARGET_PRESENT;
inout wire TARGET_PRESENT;

//extra pins
output wire ACBUS6;
output wire ACBUS7;

//control pins for test mode
input wire TEST_MODE_0;
inout wire TEST_MODE_1;
input wire TEST_MODE_2;
wire TEST_MODE;

//need : TDO, TMS, rtck, FT_nTRST_OUT, FT_nSRST_OUT, FT_nTRST_OE, FT_nSRST_OE, FT_DBGRQ, FT_TDO, FT_TARGET_PRESENT, FT_nSRST_IN, nTRST, nSRST
//three IO pins select test mode
assign TEST_MODE = (TEST_MODE_0)? 1'b0:1'b1; // && TEST_MODE_1 && TEST_MODE_2
assign TEST_MODE_1 =TEST_MODE;

//buffer controlled by FT_JTAG_OE
assign TDI = 	(!TEST_MODE)?((FT_JTAG_OE==1'b0)?FT_TDI:1'bZ):FT_JTAG_OE;
assign TMS = 	(!TEST_MODE)?((FT_JTAG_OE==1'b0)?FT_TMS:1'bZ):1'bZ;
assign TCK = 	(!TEST_MODE)?((FT_JTAG_OE==1'b0)?FT_TCK:1'bZ):FT_TARGET_PRESENT;
assign RTCK = 	(!TEST_MODE)?((FT_JTAG_OE==1'b0)?FT_RTCK:1'bZ): 1'bz;
assign DBGRQ =	(!TEST_MODE)?((FT_JTAG_OE==1'b0)?FT_DBGRQ:1'bZ):FT_RTCK;

//srst
assign FT_nSRST_IN = (!TEST_MODE)?nSRST:1'bZ;
assign nSRST = (!TEST_MODE)?((FT_nSRST_OE==1'b0)?FT_nSRST_OUT:1'bZ): 1'bZ;

//trst
assign nTRST = (!TEST_MODE)?((FT_nTRST_OE==1'b0)?FT_nTRST_OUT:1'bZ): 1'bz;

//inouts
assign FT_TDO 				= (!TEST_MODE)?TDO:1'bz;
assign FT_DBGACK 			= (!TEST_MODE)?DBGACK:TMS;
assign FT_TARGET_PRESENT= (!TEST_MODE)?TARGET_PRESENT:1'bz;	

//bidirectional for testing
assign FT_nTRST_OUT = (!TEST_MODE)?1'bZ: FT_TCK;
assign FT_nSRST_OUT = (!TEST_MODE)?1'bZ: FT_TDI;
assign FT_nTRST_OE = (!TEST_MODE)?1'bZ: FT_TDO;
assign FT_nSRST_OE = (!TEST_MODE)?1'bZ:FT_TMS;
assign ACBUS6 = (!TEST_MODE)?1'bZ:RTCK ;
assign ACBUS7 = (!TEST_MODE)?1'bZ:nSRST ;
assign FT_DBGRQ = (!TEST_MODE)?1'bZ:nTRST ;
assign TDO = (!TEST_MODE)?1'bZ:FT_nSRST_IN;
endmodule

