#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

//hardware version string
#define HW_VER 0x01

//firmware version string
#define FW_VER_H 0x02
#define FW_VER_L 0x00

#define BootloaderJump() _asm goto 0x16 _endasm

//these are unneeded, but the stack complains if they're not defined
//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISCbits.TRISC2    
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISCbits.TRISC2    
#define USB_BUS_SENSE       1 

#endif 
