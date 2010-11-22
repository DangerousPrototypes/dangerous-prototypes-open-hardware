#ifndef HAL_ACCELEROMETER_H
#define HAL_ACCELEROMETER_H

#define ACL_CS LATAbits.LATA2
#define ACL_INT1 PORTAbits.RB1
#define ACL_INT_SETUP() TRISAbits.TRISA1=1
#define LVLTH 0x1A
#define INTRST 0x17
#define CTL1 0x18
#define MCTRL 0x16

typedef enum
{
ACL_REVERSE=0,
FORWARD
}HAL_ACL_DIRECTION;




u8 hal_acl_read(u8 r);
void hal_acl_enable(void);
void hal_acl_write(u8 r, u8 v);
#endif
