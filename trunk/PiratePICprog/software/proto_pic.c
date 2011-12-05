
#include <stdio.h>

#include "pic12.h"
#include "pic16.h"
#include "pic18.h"
#include "pic24.h"

#include "proto_pic.h"

struct proto_ops_t *proto_ops[] = {
	&pic12_proto,
	&pic16_proto,
	&pic18_proto,
	&pic24_proto,
	NULL
};

struct proto_ops_t *Proto_GetOps(enum proto_t protocol) {
	struct proto_ops_t *ops;
	int i;

	for (i = 0; proto_ops[i] != NULL; i++) {
		if (proto_ops[i]->type == protocol) {
			return (struct proto_ops_t *)proto_ops[i];
		}
	}
	return NULL;
}
