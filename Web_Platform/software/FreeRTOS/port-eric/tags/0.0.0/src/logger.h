#ifndef _MESSAGE_LOG_H
#define _MESSAGE_LOG_H

#include "rtos/FreeRTOS.h"
#include "rtos/queue.h"
#include "rtos/semphr.h"

#define MESSAGE_Q_SIZE 20

extern xQueueHandle messageQueue;

#define PARAM_TYPE_SHORT 1
#define PARAM_TYPE_CHAR 2
#define PARAM_TYPE_STRING 3

struct message_param_struct {
	portBASE_TYPE type;
	union {
		portCHAR	*string_param;
		portCHAR	char_param;
		portLONG	long_param;
		portSHORT	short_param;
	} param;
};

typedef struct message_param_struct message_param_t;

typedef struct {
	const char *msg;
	portBASE_TYPE num_params;
	message_param_t *params;
} message_t;

void log_init(void);
void log_message(const char *fmt, ...);

#endif
