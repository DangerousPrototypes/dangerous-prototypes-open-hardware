//this file enables different services in the Microchip stack
//see the example in ..\TCPIP Demo App\ in the Microchip Stack code for all possible options
#ifndef __TCPIPConfig
#define __TCPIPConfig

#include "GenericTypeDefs.h"
#include "Compiler.h"

//define the services to enable
//see the example in ..\TCPIP Demo App in the Microchip Stack code for all possible options
#define STACK_USE_ICMP_SERVER			
#define STACK_USE_DHCP_CLIENT			
#define STACK_USE_ANNOUNCE	
#define STACK_USE_HTTP2_SERVER
#define STACK_USE_DNS	

//storage for HTTP2 server
//use HTTP2 server with FAT SD card
#define STACK_USE_MDD
#define MDD_ROOT_DIR_PATH "\\"
/* 
//old settings from EEPROM HTTP server
#define STACK_USE_MPFS2	
#define MPFS_USE_EEPROM		
#define USE_EEPROM_25LC1024	
#define MPFS_RESERVE_BLOCK  0x1000
*/
#define MAX_MPFS_HANDLES	0x07 //not used, but must define or error


//MAC, IP settings, etc
#define MY_DEFAULT_HOST_NAME			"DP-WP"

#define MY_DEFAULT_MAC_BYTE1            0x00	
#define MY_DEFAULT_MAC_BYTE2            0x04	
#define MY_DEFAULT_MAC_BYTE3            0xA3	
#define MY_DEFAULT_MAC_BYTE4            0x00	
#define MY_DEFAULT_MAC_BYTE5            0x10	
#define MY_DEFAULT_MAC_BYTE6            0x05	

//be sure to use XXXul to avoid warnings
#define MY_DEFAULT_IP_ADDR_BYTE1        192ul
#define MY_DEFAULT_IP_ADDR_BYTE2        168ul
#define MY_DEFAULT_IP_ADDR_BYTE3        1ul
#define MY_DEFAULT_IP_ADDR_BYTE4        100ul

#define MY_DEFAULT_MASK_BYTE1           255ul
#define MY_DEFAULT_MASK_BYTE2           255ul
#define MY_DEFAULT_MASK_BYTE3           0ul
#define MY_DEFAULT_MASK_BYTE4           0ul

#define MY_DEFAULT_GATE_BYTE1           192ul
#define MY_DEFAULT_GATE_BYTE2           168ul
#define MY_DEFAULT_GATE_BYTE3           1ul
#define MY_DEFAULT_GATE_BYTE4           1ul

#define MY_DEFAULT_PRIMARY_DNS_BYTE1	192ul
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	168ul
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	1ul
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	1ul

#define MY_DEFAULT_SECONDARY_DNS_BYTE1	0ul
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	0ul
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	0ul
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	0ul

//use microchip stack in client more
#define STACK_CLIENT_MODE

//TCP configuration
#define TCP_ETH_RAM_SIZE					3900ul
#define TCP_PIC_RAM_SIZE					0ul
#define TCP_SPI_RAM_SIZE					0ul
#define TCP_SPI_RAM_BASE_ADDRESS			0x00

//Define names of socket types
#define TCP_SOCKET_TYPES
	#define TCP_PURPOSE_GENERIC_TCP_CLIENT 0
	#define TCP_PURPOSE_GENERIC_TCP_SERVER 1
	#define TCP_PURPOSE_TELNET 2
	#define TCP_PURPOSE_FTP_COMMAND 3
	#define TCP_PURPOSE_FTP_DATA 4
	#define TCP_PURPOSE_TCP_PERFORMANCE_TX 5
	#define TCP_PURPOSE_TCP_PERFORMANCE_RX 6
	#define TCP_PURPOSE_UART_2_TCP_BRIDGE 7
	#define TCP_PURPOSE_HTTP_SERVER 8
	#define TCP_PURPOSE_DEFAULT 9
	#define TCP_PURPOSE_BERKELEY_SERVER 10
	#define TCP_PURPOSE_BERKELEY_CLIENT 11
#define END_OF_TCP_SOCKET_TYPES

#if defined(__TCP_C)
	#define TCP_CONFIGURATION
	ROM struct
	{
		BYTE vSocketPurpose;
		BYTE vMemoryMedium;
		WORD wTXBufferSize;
		WORD wRXBufferSize;
	} TCPSocketInitializer[] =
	{
		{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 200, 200},
		{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 200, 200},
		{TCP_PURPOSE_HTTP_SERVER, TCP_ETH_RAM, 200, 200},

	};
	#define END_OF_TCP_CONFIGURATION
#endif

//we don't use this, but it's needed to prevent compiler errors
#define MAX_UDP_SOCKETS     10
#define UDP_USE_TX_CHECKSUM		

//HTTP2 options
#define MAX_HTTP_CONNECTIONS	2
#define HTTP_DEFAULT_FILE		"index.htm"
#define HTTPS_DEFAULT_FILE		"index.htm"
#define HTTP_DEFAULT_LEN		10		
#define HTTP_MPFS_UPLOAD		"mpfsupload"
#define HTTP_USE_POST				
#define HTTP_USE_COOKIES			
//#define HTTP_USE_AUTHENTICATION		
#define STACK_USE_HTTP_APP_RECONFIG	

#endif

