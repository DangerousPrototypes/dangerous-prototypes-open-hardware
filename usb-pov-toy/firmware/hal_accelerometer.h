#ifndef HAL_ACCELEROMETER_H
#define HAL_ACCELEROMETER_H

#define ACL_CS LATAbits.LATA2
#define ACL_INT1 PORTAbits.RA1
#define ACL_INT_SETUP() TRISAbits.TRISA1=1
#define LVLTH 0x1A
#define INTRST 0x17
#define CTL1 0x18
#define MCTRL 0x16

typedef enum
{
ACL_REVERSE=0,
ACL_FORWARD
}HAL_ACL_DIRECTION;

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
