#ifndef _SOCKET_H_
#define _SOCKET_H_

/*
*
* Types and functions for listening for and opening tcp connections.
* 
* Implementations are in uipsockettask.c
*
*/


#include "file.h"


struct inetaddr_t
{
	unsigned char addr1;
	unsigned char addr2;
	unsigned char addr3;
	unsigned char addr4;
	unsigned short port;
};



//This is for the app task to define and pass a pointer to when they call listen() (see below)
//Return a valid file handle value to accept the connection. The data for the connection will be
//associated with that file handle.
//Return FILE_INVALID_HANDLE to reject the connection. The new incoming connection will be closed
file_handle_t socket_accept(unsigned short local_port, unsigned short *remote_address, unsigned short remote_port);

//Listen for incoming connections on port
//When new connections to the port are established, the accept_callback function will be called (see accept() above)
//You must NOT task_yield() from that call.
//This function will return true if there enough listening port slots avaiable to complete the request.
//It returns false if the port is being listened to already, or there are no more listening slots available.
//The port parameter must be in network byte order (use HTONS() or htons() ) 
bool socket_listen( unsigned short port, file_handle_t (*accept_callback)(unsigned short local_port, unsigned short *remote_address, unsigned short remote_port) );

//Connect to a remote host and associate the file_handle with the connection.
//returns true on success, false on failure (eg, no more uip connection slots available )
//Note that success does not indicate the connection was establshed; watch the file handle's status for state changes.
bool socket_connect( file_handle_t file_handle, struct inetaddr_t *remote_address );

#endif

