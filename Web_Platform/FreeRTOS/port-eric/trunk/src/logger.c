#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

#ifdef QUEUED_LOGGER
 // Currently this is broken... 
xQueueHandle messageQueue;

static message_t next_msg;

void log_init(void) {
	xTaskCreate( vLogTask, ( signed char * ) "LOG", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}

static void vLogTask( void *pvParameters ) {
	const char *p, *p2;
	message_param_t *param;

	messageQueue =  xQueueCreate( MESSAGE_Q_SIZE, sizeof(message_t));
	
	for (;;) {	
		xQueueReceive( messageQueue, &next_msg, portMAX_DELAY);
		printf("LOG:");
		p=next_msg.msg;
		param = next_msg.params;
		while(*p) {
			if (*p == '%') {
				p++;
				if (*p == '%') {
					p++;
					putchar('%');
				} else {
					if (next_msg.num_params) {
						p2 = param->param.string_param;
						while(*p2) {
							putchar(*p2);
							p2++;
						}
						vPortFree(param->param.string_param);
						next_msg.num_params--;
						param++;
					} else {
						/* no params left - output the placeholder */
						putchar('%');
						putchar(*p);
					}
					p++;
				}
			} else {
				putchar(*p);
				p++;
			}
		}
		vPortFree(param);
	}
}


const char PARAM_MARKER[] =  "%s";

void log_message(const char *fmt, ...) {
	va_list args;
	message_t msg;
	message_param_t *param;
	char *str;
	int num_params=0;
	const char *p = fmt;
	while(*p) {
		if (strncmp(PARAM_MARKER, p, 2)==0) {
			num_params++;
			p+=2;
		} else {
			p++;
		}
	}
	msg.msg = (char *)fmt;
	msg.num_params = num_params;
	if (num_params == 0) {
		msg.params = NULL;
	} else {
		msg.params = (message_param_t *)pvPortMalloc(msg.num_params * sizeof(message_param_t));
	}
	va_start(args, fmt);
	param = msg.params;
	while(--num_params>0) {
		str = va_arg(args, char *);
		param->type=PARAM_TYPE_STRING;
		param->param.string_param = pvPortMalloc(strlen(str)+1);	
		strcpy(param->param.string_param, str);
	}
	va_end(args);
	// TODO - handle lost messages
	xQueueSend( messageQueue, &msg, 1);
}

#else
// ...so just use serialise data to the serial port and use vprintf
static xSemaphoreHandle serial_mutex;

void log_init(void) {
	serial_mutex =  xSemaphoreCreateMutex();
}

void log_message(const char *fmt, ...) {
	if (xSemaphoreTake(serial_mutex, 500/portTICK_RATE_MS) == pdTRUE) {
		va_list args;
    	va_start(args, fmt);
    	vprintf(fmt, args);
    	va_end(args);
		xSemaphoreGive(serial_mutex);
	}
}
#endif
