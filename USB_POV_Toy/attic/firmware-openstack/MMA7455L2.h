// Copyright (c) 2011, Markus Gritsch
// CC-BY-SA license

#ifndef _MMA7455L_H_
#define _MMA7455L_H_

#define MMA_XOUT10 0x00
#define MMA_YOUT10 0x02
#define MMA_ZOUT10 0x04

#define MMA_XOUT8 0x06
#define MMA_YOUT8 0x07
#define MMA_ZOUT8 0x08

#define MMA_STATUS 0x09 // Status Register (Read only)
#define MMA_DRDY_bit (1<<0) // 1: Data is ready
#define MMA_DOVR_bit (1<<1) // 1: Data is over written
#define MMA_PERR_bit (1<<2) // 1: Parity error is detected in trim data

#define MMA_I2CAD 0x0d // I2C Device Address
#define MMA_I2CDIS_bit (1<<7) // 1: I2C is disabled

#define MMA_XOFFL 0x10
#define MMA_YOFFL 0x12
#define MMA_ZOFFL 0x14

#define MMA_MCTL 0x16 // Mode Control Register

#define MMA_CTL1 0x18 // Control 1
#define MMA_DFBW_bit (1<<7) // Digital filter band width (0: 62.5 Hz, 1: 125 Hz)


#endif // _MMA7455L_H_
