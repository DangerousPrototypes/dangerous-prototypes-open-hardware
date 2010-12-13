#include "globals.h"




void hal_logicshrimp_init(void)
{
hal_logicshrimp_pinsetup();
hal_logicshrimp_setClockGate(OFF);
hal_logicshrimp_setBufferEnable(OFF);
}
