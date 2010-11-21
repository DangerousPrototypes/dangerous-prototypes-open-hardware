#ifndef HAL_ACCELEROMETER_H
#define HAL_ACCELEROMETER_H

#define ACL_CS LATAbits.LATA2


typedef enum
{
ACL_REVERSE=0,
FORWARD
}HAL_ACL_DIRECTION;

u8 hal_Acl_Read(u8 r);
void hal_Acl_Enable(void);

#endif
