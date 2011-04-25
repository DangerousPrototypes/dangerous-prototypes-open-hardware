#ifndef HAL_ACCELEROMETER_H
#define HAL_ACCELEROMETER_H

#define ACL_CS LATAbits.LATA2
#define ACL_INT1 PORTAbits.RA1
//#define hal_acl_IntSetup() //TRISAbits.TRISA1=0


typedef enum
{
ACL_REVERSE=0,
ACL_FORWARD
}HAL_ACL_DIRECTION;


typedef enum
{
OUTPUT_X_LSB_10BIT=0x00,
OUTPUT_X_MSB_10BIT=0x01,
OUTPUT_Y_LSB_10BIT=0x02,
OUTPUT_Y_MSB_10BIT=0x03,
OUTPUT_Z_LSB_10BIT=0x04,
OUTPUT_Z_MSB_10BIT=0x05,

OUTPUT_X_8BIT=0x06,
OUTPUT_Y_8BIT=0x07,
OUTPUT_Z_8BIT=0x08,
STATUS_REG=0x09,

DETECTION_SRC_REG=0x0A,

MODE_CTRL_REG=0x16,
INT_LATCH_RST=0x17,
CTL1=0x18,

LVLTH=0x1A
}MMA745x_COMMANDS;



	//xxZYXxxx
#define ACL_X 0b1000
#define ACL_Y 0b10000
#define ACL_Z 0b100000
#define CTL1_CFG ACL_Y | ACL_Z //disable unwanted interrupts
#define ACL_DIRECTION 0x06



HAL_ACL_DIRECTION hal_acl_IsItReverseOrForward(void);
void hal_acl_config(void);
u8 hal_acl_read(u8 r);
void hal_acl_enable(void);
void hal_acl_write(u8 r, u8 v);
#endif
