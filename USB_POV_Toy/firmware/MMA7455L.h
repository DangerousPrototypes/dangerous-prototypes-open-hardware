// Copyright (c) 2011, Markus Gritsch
// CC-BY-SA license

#ifndef _MMA7455L_H_
#define _MMA7455L_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

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

static void swspi_init();
static uint8_t swspi_shift( uint8_t data );

void mma_init();
void mma_write( uint8_t address, uint8_t value );
uint8_t mma_read( uint8_t address );
int16_t mma_read10( uint8_t address );

void mma_calibrate_offset( int16_t x, int16_t y, int16_t z );
void mma_wait_until_ready();
void mma_get_average( uint8_t power_of_two, int16_t * x, int16_t * y, int16_t * z );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MMA7455L_H_
