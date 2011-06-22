//this file enables different services in the Microchip stack
//see the example in ..\TCPIP Demo App\ in the Microchip Stack code for all possible options
#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

//define the services to enable
//see the example in ..\TCPIP Demo App in the Microchip Stack code for all possible options
#define STACK_USE_ICMP_SERVER			
#define STACK_USE_DHCP_CLIENT			
#define STACK_USE_ANNOUNCE	
#define STACK_USE_TCP		
#define STACK_USE_DNS			

//MAC, IP settings, etc
#define MY_DEFAULT_HOST_NAME			"MCHPBOARD"

#define MY_DEFAULT_MAC_BYTE1            (0x00)	
#define MY_DEFAULT_MAC_BYTE2            (0x04)	
#define MY_DEFAULT_MAC_BYTE3            (0xA3)	
#define MY_DEFAULT_MAC_BYTE4            (0x00)	
#define MY_DEFAULT_MAC_BYTE5            (0x00)	
#define MY_DEFAULT_MAC_BYTE6            (0x00)	

#define MY_DEFAULT_IP_ADDR_BYTE1        (169ul)
#define MY_DEFAULT_IP_ADDR_BYTE2        (254ul)
#define MY_DEFAULT_IP_ADDR_BYTE3        (1ul)
#define MY_DEFAULT_IP_ADDR_BYTE4        (1ul)

#define MY_DEFAULT_MASK_BYTE1           (255ul)
#define MY_DEFAULT_MASK_BYTE2           (255ul)
#define MY_DEFAULT_MASK_BYTE3           (0ul)
#define MY_DEFAULT_MASK_BYTE4           (0ul)

#define MY_DEFAULT_GATE_BYTE1           (169ul)
#define MY_DEFAULT_GATE_BYTE2           (254ul)
#define MY_DEFAULT_GATE_BYTE3           (1ul)
#define MY_DEFAULT_GATE_BYTE4           (1ul)

#define MY_DEFAULT_PRIMARY_DNS_BYTE1	(169ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	(254ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	(1ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	(1ul)

#define MY_DEFAULT_SECONDARY_DNS_BYTE1	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	(0ul)

//use microchip stack in client more
#define STACK_CLIENT_MODE

//TCP Socket configuration
#define TCP_ETH_RAM_SIZE					(3900ul)
#define TCP_PIC_RAM_SIZE					(0ul)
#define TCP_SPI_RAM_SIZE					(0ul)
#define TCP_SPI_RAM_BASE_ADDRESS			(0x00)

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
		{TCP_PURPOSE_DEFAULT, TCP_ETH_RAM, 400, 400},
		{TCP_PURPOSE_GENERIC_TCP_CLIENT, TCP_ETH_RAM, 400, 400},
//		{TCP_PURPOSE_GENERIC_TCP_CLIENT, TCP_ETH_RAM, 125, 100},
	};
	#define END_OF_TCP_CONFIGURATION
#endif

//we don't use this, but it's needed to prevent compiler errors
#define MAX_UDP_SOCKETS     (10u)
#define UDP_USE_TX_CHECKSUM		
#define MAX_HTTP_CONNECTIONS	(2u)

#endif

