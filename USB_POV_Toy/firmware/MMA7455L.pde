// Copyright (c) 2011, Markus Gritsch
// CC-BY-SA license

#include <util/delay.h>

#include "MMA7455L.h"

void setup()
{
    Serial.begin(115200);

    mma_init();
    _delay_ms( 1 ); // Wait Time for I2C/SPI ready after power on.
    _delay_ms( 20 ); // Turn On Response Time.

    uint8_t i2cad = mma_read( MMA_I2CAD );
    Serial.println( i2cad, HEX ); // should be 0x1D
    mma_write( MMA_I2CAD, i2cad |= MMA_I2CDIS_bit ); // disable I2C

    uint8_t ctl1 = mma_read( MMA_CTL1 );
    mma_write( MMA_CTL1, ctl1 |= MMA_DFBW_bit ); // high output data rate

    mma_write( MMA_MCTL, 0b00000101 ); // 2g range; measurement mode

    mma_calibrate_offset( -15, -23, 65 );
}

void loop()
{
    //mma_wait_until_ready();
    //
    //Serial.print( (int8_t)mma_read( MMA_XOUT8 ) ); Serial.print( "\t" );
    //Serial.print( (int8_t)mma_read( MMA_YOUT8 ) ); Serial.print( "\t" );
    //Serial.print( (int8_t)mma_read( MMA_ZOUT8 ) ); Serial.println();
    //
    //Serial.print( mma_read10( MMA_XOUT10 ) ); Serial.print( "\t" );
    //Serial.print( mma_read10( MMA_YOUT10 ) ); Serial.print( "\t" );
    //Serial.print( mma_read10( MMA_ZOUT10 ) ); Serial.println();

    long start = micros();
    int16_t x, y, z;
    mma_get_average( 4, &x, &y, &z );
    Serial.print( x ); Serial.print( "\t" );
    Serial.print( y ); Serial.print( "\t" );
    Serial.print( z ); Serial.print( "\t" );
    Serial.print( micros() - start ); Serial.println();
}
