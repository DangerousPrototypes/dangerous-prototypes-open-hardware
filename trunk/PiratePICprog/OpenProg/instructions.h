// programmer instructions v0.7.0
#define NOP 				0x00	
#define PROG_RST 			0x01	//		->10B
#define PROG_ID 			0x02	//		->6B
#define CHECK_INS 			0x03	//+1B 	->1B
#define FLUSH				0x04	//no echo	
#define VREG_EN				0x05	
#define VREG_DIS			0x06
#define SET_PARAMETER		0x07	//+3B: 1B parameter, 2B data
	#define SET_T1T2 	0	//T1, T2
	#define SET_T3		1 	//T3(H,L)
	#define SET_timeout	2	//timeout(H,L)
	#define SET_MN		3	//M, N	
#define WAIT_T1				0x08
#define WAIT_T2				0x09
#define WAIT_T3				0x0A
#define WAIT_US				0x0B	//+1B
#define READ_ADC			0x0C	//		->2B
#define SET_VPP				0x0D	//+1B 	->1B
#define EN_VPP_VCC			0x0E	//+1B
#define SET_CK_D			0x0F	//+1B
#define READ_PINS			0x10	//		->1B
#define LOAD_CONF			0x11	//2B			000000
#define LOAD_DATA_PROG		0x12	//2B			000010
#define LOAD_DATA_DATA		0x13	//2B			000011
#define READ_DATA_PROG		0x14	//  	->2B	000100
#define READ_DATA_DATA		0x15	//  	->1B	000101
#define INC_ADDR			0x16	//				000110
#define INC_ADDR_N			0x17	//+1B			000110
#define BEGIN_PROG			0x18	//				001000
#define BULK_ERASE_PROG		0x19	//				001001
#define END_PROG			0x1A	//				001010
#define BULK_ERASE_DATA		0x1B	//				001011
#define END_PROG2			0x1C	//				001110
#define ROW_ERASE_PROG		0x1D	//				010001
#define BEGIN_PROG2 		0x1E	//				011000
#define	CUST_CMD			0x1F	//+1B
#define	PROG_C				0x20	//+2B	->1B	001000&001110
#define CORE_INS			0x21	//+2B			0000
#define SHIFT_TABLAT		0x22	//		->1B	0010
#define TABLE_READ			0x23	//		->1B	1000
#define TBLR_INC_N  		0x24	//+1B	->1+NB	1001
#define TABLE_WRITE			0x25	//+2B			1100
#define TBLW_INC_N  		0x26	//+1+2NB		1101
#define TBLW_PROG			0x27	//+4B			1111
#define TBLW_PROG_INC		0x28	//+4B			1110
#define SEND_DATA			0x29	//+3B
#define READ_DATA			0x2A	//+1B	->1B
#define I2C_INIT			0x2B	//+1B
#define I2C_READ			0x2C	//+3B	->1+NB
#define I2C_WRITE			0x2D	//+3+NB ->1B
#define I2C_READ2			0x2E	//+4B	->1+NB
#define SPI_INIT			0x2F	//+1B
#define SPI_READ			0x30	//+1B	->1+NB
#define SPI_WRITE			0x31	//+1+NB ->1B
#define EXT_PORT			0x32	//+2B
#define AT_READ_DATA		0x33	//+3B 	->1+2NB
#define AT_LOAD_DATA		0x34	//+3+2NB ->1B
#define CLOCK_GEN			0x35	//+1B
#define SIX					0x36	//+3B
#define REGOUT				0x37	//		->2B
#define ICSP_NOP			0x38	//
#define TX16				0x39	//+1+2NB
#define RX16				0x3A	//+1	->1+2NB
#define uW_INIT				0x3B	//
#define uWTX				0x3C	//+1+NB
#define uWRX				0x3D	//+1+NB
#define SIX_LONG			0x3E	//+3B
#define SIX_N				0x3F	//1+3NB ->1B
// special ins.
#define SPI_TEST			0xEF	//+2B	->2B
#define READ_RAM			0xF0	//+2B	->3B
#define WRITE_RAM			0xF1	//+3B	->3B
#define LOOP				0xF2
#define MAX_INS 			0x3F	//last instruction
