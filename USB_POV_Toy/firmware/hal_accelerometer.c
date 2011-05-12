#include "globals.h"



u8 hal_acl_read(u8 r)
{
u8 c;

ACL_CS=0;
hal_spi_rw((r<<1));
c=hal_spi_rw(0xff);
ACL_CS=1;
return c;
}

void hal_acl_write(u8 r, u8 v)//register and value
{
ACL_CS=0;
hal_spi_rw((r<<1)|0b10000000);
hal_spi_rw(v);
ACL_CS=1;
}


void hal_acl_enable(void){
hal_acl_write(MODE_CTRL_REG,0b0001);
hal_acl_write(0x0D,0b10000000); //i2C disable
#if 0
ACL_CS=0;
hal_spi_rw((0x16<<1)|0b10000000);//write setup
hal_spi_rw(0b0001);//low g, measurement
ACL_CS=1;
#endif
}


void hal_acl_config(void)
{
	//setup change interrupt
//16 - mode control
//10 (4g) 10 (level detect)
//00: 8g is selected for measurement range.
//10: 4g is selected for measurement range.
//01: 2g is selected for measurement range.
hal_acl_write(MODE_CTRL_REG, 0b0101);

//18 int or absolute
//xPxxxxxx p=1 positive/negative
	//18Disable any unneeded axis
	//xxZYXxxx
//xxxxxIIx ii=00 level detection

hal_acl_write(CTL1, CTL1_CFG);

//enable interrupt (write 0x00 to 0x17)

hal_acl_write(INT_LATCH_RST, 0b11);
hal_acl_write(INT_LATCH_RST, 0x00);

//
//19 OR or AND
//xxxxxxxA 1=and 0x00 default...

//1a detection threshold

hal_acl_write(LVLTH, 0x7f);
}


HAL_ACL_DIRECTION hal_acl_IsItReverseOrForward(void)
{
unsigned char c;
c=hal_acl_read(ACL_DIRECTION);
if((c&0b10000000))
	{//negative
	return ACL_REVERSE;
	}
return ACL_FORWARD;
}

#if 0
void hal_acl_adjustInterruptLvl(u8 value)
{
}
#endif

void mma_wait_until_ready()
{
	while( ( hal_acl_read( STATUS_REG ) & 0b00000001 ) == 0 ) {};
}

void mma_get_average( u8 power_of_two, int * x, int * y, int * z )
{
    int accu_x = 0;
    int accu_y = 0;
    int accu_z = 0;
    u8 i;
    for ( i = 0; i < ( 1 << power_of_two ); ++i ) {
        mma_wait_until_ready();
        accu_x += hal_acl_read( OUTPUT_X_8BIT );
        accu_y += hal_acl_read( OUTPUT_Y_8BIT );
        accu_z += hal_acl_read( OUTPUT_Z_8BIT );
    }
    *x = ( accu_x + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *y = ( accu_y + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
    *z = ( accu_z + ( 1 << ( power_of_two - 1 ) ) ) >> power_of_two;
}


/*
#define POWER_OF_TWO 5
static volatile int16_t x_array[ 1 << POWER_OF_TWO ];
static volatile int16_t y_array[ 1 << POWER_OF_TWO ];
static volatile int16_t z_array[ 1 << POWER_OF_TWO ];
static volatile int16_t x_moving_average;
static volatile int16_t y_moving_average;
static volatile int16_t z_moving_average;
static volatile uint8_t i;

#if defined(USE_INTERRUPT)
ISR( INT0_vect )
{
    int16_t x = mma_read10( MMA_XOUT10 );
    int16_t y = mma_read10( MMA_YOUT10 );
    int16_t z = mma_read10( MMA_ZOUT10 );
    x_moving_average -= x_array[ i ];
    y_moving_average -= y_array[ i ];
    z_moving_average -= z_array[ i ];
    x_array[ i ] = x;
    y_array[ i ] = y;
    z_array[ i ] = z;
    x_moving_average += x;
    y_moving_average += y;
    z_moving_average += z;
    ++i;
    if ( i >= ( 1 << POWER_OF_TWO ) ) {
        i = 0;
    }
}

void mma_get_moving_average( int16_t * x, int16_t * y, int16_t * z )
{
    *x = ( ( x_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
    *y = ( ( y_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
    *z = ( ( z_moving_average + ( 1 << ( POWER_OF_TWO - 1 ) ) ) ) >> POWER_OF_TWO;
}
#endif
*/