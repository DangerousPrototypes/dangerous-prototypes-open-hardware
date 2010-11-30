#ifndef HAL_POV_H
#define HAL_POV_H


extern volatile u8 hal_pov_u8endflag;


//enable peripheral interrupts
//enable interrupts
#define hal_pov_setupInt()	INTCONbits.GIEL = 1;INTCONbits.GIEH = 1;

#define BITMAP_RAM_SZ	200 //TODO: adjust

#define hal_pov_disableTmr0()	TM0ON=0//enable the timer

HAL_ACL_DIRECTION hal_acl_IsItReverseOrForward(void);

#define HAL_POV_PORT	PORTB

void hal_pov_setupTmr0(void);
void hal_pov_setupTmr1(void);



#endif
