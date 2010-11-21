#ifndef HAL_ACCELEROMETER_H
#define HAL_ACCELEROMETER_H

#define ACL_CS LATAbits.LATA2


typedef enum
{
ACL_REVERSE=0,
FORWARD
}HAL_ACL_DIRECTION;




u8 hal_acl_read(u8 r);
void hal_acl_enable(void);

#endif
