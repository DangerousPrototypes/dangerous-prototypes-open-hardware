/*
 * This file handles interaction between FreeRTOS and uIP
 */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uip.h"
#include "uip_arp.h"
#include "uip_task.h"
#include "nic_dma.h"
#include "nic.h"
#include "ff.h"
#include "diskio.h"
#include "logger.h"

#ifdef UIP_CONF_EXTERNAL_BUFFER
u8_t uip_buf[UIP_BUFSIZE+2] __attribute__((space(dma)));   // The packet buffer that contains incoming packets.
#else
#warning "uIP is using internal buffer - This probably won't work with DMA"
#endif


#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
struct uip_eth_addr mac = { { UIP_ETHADDR0, UIP_ETHADDR1, UIP_ETHADDR2, UIP_ETHADDR3, UIP_ETHADDR4, UIP_ETHADDR5 } } ;
void telnetd_init(void);
extern FATFS FatFS;

void vUipTask( void *pvParameters ) 
{
	struct timer periodic_timer, arp_timer;
	portBASE_TYPE i;
	int ret;
 	xSemaphoreHandle dmaSemaphore;
	DIR dir;
	FILINFO fileinfo;


/*		
	while(disk_status(0) == STA_NOINIT) {
		log_message("Waiting for disk...\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
*/
	// ...need to perform a file operation to do that
	log_message("Reading SD Card...\n");
	ret = f_opendir(&dir, "");
	if (ret == 0) {
		while(f_readdir(&dir, &fileinfo) == FR_OK) {
			if (!fileinfo.fname[0]) break;
	//		log_message("FILE: %s", fileinfo.fname);

		}
	} else {
		log_message("Failed to open dir\n");
	}
	log_message("fs_type=%d csize=%d\n",  FatFS.fs_type, FatFS.csize);

	f_chdir("/WWW");

	timer_set(&periodic_timer, CLOCK_SECOND / 2);
  	timer_set(&arp_timer, CLOCK_SECOND * 10);

 	dmaSemaphore = nic_init(); 
    uip_log("nic init\n");

    // init uIP
    uip_init();
    uip_log("uip init\n");

    // init ARP cache
   	uip_arp_init();
   	uip_log("arp init\n");

	dhcpc_init(&mac, 6);
	//telnetd_init();
	httpd_init();

	while(1) {
		if (xSemaphoreTake(dmaSemaphore, 500 / portTICK_RATE_MS) == pdTRUE) {
            uip_len = uip_dma_rx_last_packet_length;
         	// packet received - buffer is already acquired
			// uip_log("RX packet\r\n");
		} else {
		    uip_len = 0;
		}
		if(uip_len > 0) {
	    	if(BUF->type == htons(UIP_ETHTYPE_IP)) {
				uip_arp_ipin();
				uip_input();
				/* If the above function invocation resulted in data that
		   		should be sent out on the network, the global variable
		   		uip_len is set to a value > 0. */
				if(uip_len > 0) {
			  		uip_arp_out();
			  		nic_send();
				} else {
					nic_rx_maybe();
				}
	    	} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
		   		should be sent out on the network, the global variable
		   		uip_len is set to a value > 0. */
				if(uip_len > 0) {
		  			nic_send();
				} else {
					nic_rx_maybe();
				}
	   		} else {
				uip_log("Unknown packet discarded\n");
				nic_rx_maybe();
			}
	    } else if(timer_expired(&periodic_timer)) {
			/* No packet was received. 
			 * Instead we check if it is time that we do the			 * periodic processing. 
			 */
			timer_reset(&periodic_timer);	      	for(i = 0; i < UIP_CONNS; i++) {
				uip_periodic(i);
				/* If the above function invocation resulted in data that
			   	should be sent out on the network, the global variable
		   		uip_len is set to a value > 0. */
				if(uip_len > 0) {
		  			uip_arp_out();
		  			nic_send();
				}
      		}
#if UIP_UDP
      		for(i = 0; i < UIP_UDP_CONNS; i++) {
				uip_udp_periodic(i);
				/* If the above function invocation resulted in data that
	   			should be sent out on the network, the global variable
	   			uip_len is set to a value > 0. */
				if(uip_len > 0) {
	  				uip_arp_out();
	  				nic_send();
				}
      		}
#endif /* UIP_UDP */
			/*
			 * ARP periodic processing
			 */
			if(timer_expired(&arp_timer)) {
				timer_reset(&arp_timer);
				uip_arp_timer();
      		}
    	}
		taskYIELD();
	} // end while	
}

void uip_log(char *m) {
	log_message("%s", m);
}


void dhcpc_configured(const struct dhcpc_state *s) {
	uip_sethostaddr(s->ipaddr);
	uip_setnetmask(s->netmask);
	uip_setdraddr(s->default_router);
	log_message("dhcp configured. My IP=%d.%d.%d.%d\n", uip_ipaddr1(s->ipaddr), uip_ipaddr2(s->ipaddr),uip_ipaddr3(s->ipaddr), uip_ipaddr4(s->ipaddr));
}

void uip_appcall(void) {
	switch (uip_conn->lport) {
		case HTONS(80):
			httpd_appcall();
			break;
		default:
			log_message("uip_apcall lport=%d\n", uip_conn->lport);
			break;
	}	
}

void uip_udp_appcall(void) {
	switch (uip_udp_conn->lport) {
		case HTONS(DHCPC_CLIENT_PORT):
			dhcpc_appcall();
			break;
		default:
			log_message("uip_udp_apcall for unknown port %d\n", uip_udp_conn->lport);
	}
}
