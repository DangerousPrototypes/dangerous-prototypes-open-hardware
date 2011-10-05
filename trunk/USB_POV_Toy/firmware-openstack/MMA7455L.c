// Copyright (c) 2011, Markus Gritsch
// CC-BY-SA license

#include <avr/io.h>

#include "MMA7455L.h"

#define MMA_PORT PORTD
#define MMA_DIR  DDRD
#define MMA_IN   PIND

#define MMA_SS   (1<<0)
#define MMA_SCK  (1<<1)
#define MMA_MOSI (1<<2)
#define MMA_MISO (1<<3)

static void swspi_init()
{
    MMA_DIR |= MMA_SS | MMA_SCK | MMA_MOSI;
    MMA_DIR &= ~MMA_MISO;
}

static uint8_t swspi_shift( uint8_t data )
{
    uint8_t i;
    for ( i = 0; i < 8; ++i ) {
        MMA_PORT &= ~MMA_SCK;
        if ( data & 0x80 ) {
            MMA_PORT |= MMA_MOSI;
        } else {
            MMA_PORT &= ~MMA_MOSI;
        }
        data <<= 1;
        if ( MMA_IN & MMA_MISO ) {
            data |= 1;
        }
        MMA_PORT |= MMA_SCK;
    }
    MMA_PORT &= ~MMA_SCK;
    MMA_PORT |= MMA_MOSI;
    return data; // Takes about 8 us to 9 us.
}

void mma_init()
{
    swspi_init();
    MMA_PORT &= ~MMA_SCK;
    MMA_PORT |= MMA_MOSI;
    MMA_PORT |= MMA_SS;
}

void mma_write( uint8_t address, uint8_t value )
{
    MMA_PORT &= ~MMA_SS;
    swspi_shift( 0x80 | ( address << 1 ) );
    swspi_shift( value );
    MMA_PORT |= MMA_SS;
}

uint8_t mma_read( uint8_t address )
{
    uint8_t value;
    MMA_PORT &= ~MMA_SS;
    swspi_shift( address << 1 );
    value = swspi_shift( 0 );
    MMA_PORT |= MMA_SS;
    return value;
}

int16_t mma_read10( uint8_t address )
{
    int16_t value = 0xc000;
    MMA_PORT &= ~MMA_SS;
    swspi_shift( address << 1 );
    value = swspi_shift( 0 ) << 6; // low byte
    swspi_shift( ( address + 1 ) << 1 );
    value |= swspi_shift( 0 ) << 14; // high byte
    MMA_PORT |= MMA_SS;
    return value >> 6;
}

void mma_calibrate_offset( int16_t x, int16_t y, int16_t z )
{
    int16_t offset_x = ( 0 - x ) << 1;
    int16_t offset_y = ( 0 - y ) << 1;
    int16_t offset_z = ( 64 - z ) << 1;
    mma_write( MMA_XOFFL, offset_x & 0x00ff );
    mma_write( MMA_XOFFL + 1, ( offset_x & 0xff00 ) >> 8 );
    mma_write( MMA_YOFFL, offset_y & 0x00ff );
    mma_write( MMA_YOFFL + 1, ( offset_y & 0xff00 ) >> 8 );
    mma_write( MMA_ZOFFL, offset_z & 0x00ff );
    mma_write( MMA_ZOFFL + 1, ( offset_z & 0xff00 ) >> 8 );
}

void mma_wait_until_ready()
{
    while( ( mma_read( MMA_STATUS ) & MMA_DRDY_bit ) == 0 ) {};
}

void mma_get_average( uint8_t power_of_two, int16_t * x, int16_t * y, int16_t * z )
{
    int16_t accu_x = 0;
    int16_t accu_y = 0;
    int16_t accu_z = 0;
    uint8_t i;
    for ( i = 0; i < ( 1 << power_of_two ); ++i ) {
        mma_wait_until_ready();
        accu_x += mma_read10( MMA_XOUT10 );
        accu_y += mma_read10( MMA_YOUT10 );
        accu_z += mma_read10( MMA_ZOUT10 );
    }
    *x = accu_x >> power_of_two;
    *y = accu_y >> power_of_two;
    *z = accu_z >> power_of_two;
}
