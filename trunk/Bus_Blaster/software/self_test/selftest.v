`timescale 1ns / 1ps

module selftest (
jtag_out,
jtag_in,
ADBUS,
ACBUS
);
//global
input wire [7:0] ADBUS;
input wire [3:0] jtag_in;

output wire [7:0] ACBUS;
output wire [3:0] jtag_out;

//assign the connections
assign ACBUS[3:0]=jtag_in[3:0];
assign ACBUS[7:4]=jtag_in[3:0];

assign jtag_out[3:0]=(ADBUS[7:4]==ADBUS[3:0])?ADBUS[3:0]:3'b000;
 
endmodule // End of Module

/*
robot's jtagkey in VHDL, needs to be added to the self test in verilog
`define ADBUS[0] FT_JTAG_OE //need to redefine the logic
//test trigger?
entity jtagkey is
    Port ( FT_JTAG_OE : in  STD_LOGIC;
           FT_TDO : out  STD_LOGIC;
           FT_TDI : in  STD_LOGIC;
           FT_TCK : in  STD_LOGIC;
			  FT_RTCK : in  STD_LOGIC;
           FT_TMS : in  STD_LOGIC;
			  FT_DBGRQ : in STD_LOGIC;
			  FT_DBGACK : out STD_LOGIC;
           FT_nSRST_OE : in  STD_LOGIC;
           FT_nSRST_IN : out  STD_LOGIC;
           FT_nSRST_OUT : in  STD_LOGIC;
           FT_nTRST_OE : in  STD_LOGIC;
           FT_nTRST_OUT : in  STD_LOGIC;
           RTCK : out  STD_LOGIC;
           TDO : in  STD_LOGIC;
           TCK : out  STD_LOGIC;
           TDI : out  STD_LOGIC;
           TMS : out  STD_LOGIC;
           nSRST : inout  STD_LOGIC;
           nTRST : inout  STD_LOGIC;
           DBGACK : in  STD_LOGIC;
           DBGRQ : out  STD_LOGIC;
			  FT_TARGET_PRESENT : out STD_LOGIC;
			  TARGET_PRESENT : in STD_LOGIC
			  );
end jtagkey;

architecture Behavioral of jtagkey is

begin
	-- buffer controlled by FT_JTAG_OE
	TDI <= FT_TDI when FT_JTAG_OE = '0' else 'Z';
	TMS <= FT_TMS when FT_JTAG_OE = '0' else 'Z';
	TCK <= FT_TCK when FT_JTAG_OE = '0' else 'Z';
	RTCK <= FT_RTCK when FT_JTAG_OE = '0' else 'Z';
	DBGRQ <= FT_DBGRQ when FT_JTAG_OE = '0' else 'Z';

	-- srst
	FT_nSRST_IN <= nSRST;
	nSRST <= FT_nSRST_OUT when FT_nSRST_OE = '0' else 'Z';
	
	-- trst
	nTRST <= FT_nTRST_OUT when FT_nTRST_OE = '0' else 'Z';

	-- inputs
	FT_TDO <= TDO;
	FT_DBGACK <= DBGACK;
	FT_TARGET_PRESENT <= TARGET_PRESENT;

end Behavioral;
*/