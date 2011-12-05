
#include <string.h>

#include "iface.h"
#include "buspirate.h"

#define IFACE_CNT (sizeof(iface)/sizeof(struct iface_t))
struct iface_t *iface[] = {
	&buspirate_iface,
	NULL
};

struct iface_t *Iface_GetByName(char *name) {
	struct iface_t *dev;
	int i;

	for (i = 0; iface[i] != NULL; i++) {
		if (strcasecmp(name, iface[i]->name) == 0) {
			return (struct iface_t *)iface[i];
		}
	}
	return NULL;
}
