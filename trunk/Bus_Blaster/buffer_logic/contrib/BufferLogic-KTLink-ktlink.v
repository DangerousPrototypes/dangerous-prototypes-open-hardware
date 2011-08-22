`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:29:26 08/04/2011 
// Design Name: 
// Module Name:    ktlink 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ktlink(
    input ACBUS6,
    input ADBUS0,
    output TCK_SWCLK,
	 
    input ACBUS5,
    input ADBUS1,
    output TDI,
	 
	 input ADBUS5,
	 
    input ACBUS4,
    input ADBUS3,
    inout TMS_SWDIO,
	 
	 input TDO_SWO,
	 output ADBUS2_TDO,
	 
	 input UART_RX,
	 output BDBUS1_RX,
	 
	 input ACBUS2,
	 input ACBUS0,
	 output TRST,
	 
	 input ACBUS3,
	 input ACBUS1,
	 output ADBUS6_SRST,
	 inout SRST,
	 
	 input RTCK,
	 output ADBUS7_RTCK,
	 
	 input JTAG_ENABLE_N //JTAG FIX
    );
	wire ctrlADBUS5 = ADBUS5;
	PULLUP puADBUS5(ctrlADBUS5);
	
	wire ctrlACBUS6 = ACBUS6;
	PULLUP puACBUS6(ctrlACBUS6);
	
	wire ctrlACBUS5 = ACBUS5;
	PULLUP puACBUS5(ctrlACBUS5);
	
	wire ctrlACBUS4 = ACBUS4;
	PULLUP puACBUS4(ctrlACBUS4);
	
	wire ctrlACBUS2 = ACBUS2;
	PULLUP puACBUS2(ctrlACBUS2);
	
	wire ctrlACBUS3 = ACBUS3;
	PULLUP puACBUS3(ctrlACBUS3);
	
	wire TMS_SWDIO_sel = ctrlADBUS5 ? ADBUS3 : ADBUS1;
	
	assign TCK_SWCLK = ctrlACBUS6 ? 1'bz : ADBUS0;
	
	assign TDI = ctrlACBUS5 ? 1'bz : ADBUS1;
	
	assign TMS_SWDIO = ctrlACBUS4 ? 1'bz : TMS_SWDIO_sel;
	
	assign ADBUS2_TDO = ctrlADBUS5 ? TDO_SWO : TMS_SWDIO;
	
	assign BDBUS1_RX = JTAG_ENABLE_N ? (ctrlADBUS5 ? UART_RX : TDO_SWO) : 1'bz; //JTAG FIX
	
	assign TRST = ctrlACBUS2 ? 1'bz : ACBUS0;
	
	assign SRST = ctrlACBUS3 ? 1'bz : ACBUS1;
	assign ADBUS6_SRST = SRST;
	
	assign ADBUS7_RTCK = RTCK;

endmodule
