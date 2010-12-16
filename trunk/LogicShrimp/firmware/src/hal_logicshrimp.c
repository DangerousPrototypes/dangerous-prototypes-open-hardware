#include "globals.h"




void hal_logicshrimp_init(void)
{
hal_logicshrimp_pinsetup();
hal_logicshrimp_setClockGate(PORT_OFF);
hal_logicshrimp_setBufferEnable(PORT_OFF);
}
