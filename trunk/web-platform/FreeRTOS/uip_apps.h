/*
 * Contains app state which is common to all uIP apps
 */
#ifndef _UIP_APPS_H
#define _UIP_APPS_H


#include "webserver.h"
#include "dhcpc.h"

typedef union {
	struct httpd_state httpd;
} uip_tcp_appstate_t;

typedef union {
	// struct dhcpc_state dhcpc;
} uip_udp_appstate_t;


#endif
