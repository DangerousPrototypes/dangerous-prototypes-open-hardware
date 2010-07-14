
#include <string.h>


#include "buspirate.h"

#include "iface.h"

#define IFACE_CNT (sizeof(iface)/sizeof(struct iface_t))
const struct iface_t iface[] = {
	{
		.name = "buspirate",
		.Init = BP_Init,
		.DataLow = BP_DataLow,
		.DataHigh = BP_DataHigh,
		.ClockLow = BP_ClockLow,
		.ClockHigh = BP_ClockHigh,
		.MCLRLow = BP_MCLRLow,
		.MCLRHigh = BP_MCLRHigh,
		.SetBitOrder = BP_SetBitOrder,
		.SendBytes = BP_BulkByteWrite,
		.SendBits = BP_BulkBitWrite,
		.PIC416Read = BP_PIC416Read,
		.PIC416Write = BP_PIC416Write,
		.PIC424Read = BP_PIC424Read,
		.PIC424Write = BP_PIC424Write
	}
};

struct iface_t *Iface_GetByName(char *name) {
	int i;

	for (i = 0; i < IFACE_CNT; i++) {
		if (strcmp(name, iface[i].name) == 0) {
			return (struct iface_t *)&iface[i];
		}
	}
	return 0;
}
