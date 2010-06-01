#ifndef _UIPSOCKETTASK_H_
#define _UIPSOCKETTASK_H_

/*
* Entry point to uip task
*/
void uip_task_main(void);


//These defines are for uIP to call the app
/* UIP_APPSTATE_SIZE: The size of the application-specific state
   stored in the uip_conn structure.

	We need one byte to hold a single file handle to associated with the connection
 */
#define UIP_APPSTATE_SIZE 1

void uip_socket_app(void);

#define FS_STATISTICS 0

#define UIP_APPCALL     uip_socket_app

#endif

