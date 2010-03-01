/*****************************************************************************
*  "A Very Simple Application" from the uIP 0.9 documentation
*****************************************************************************/

#include "app.h"

void example1_init(void)
{
	uip_listen(HTONS(23));
}


void example1_app(void)
{
	if(uip_connected() || uip_rexmit()){
		uip_send("welcome\n", 8);
	}
	if(uip_newdata())
	{
		uip_send("ok\n", 3);
	}
}
