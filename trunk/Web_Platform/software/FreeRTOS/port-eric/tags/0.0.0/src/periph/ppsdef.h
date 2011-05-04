/**********************************************************************/
/*              Header for Pin Re-Mapping peripheral library functions               */
/*********************************************************************/

#ifndef __PPS_H
#define __PPS_H

/*----------------------------------------------------------------------------------------------------*/
/*  Remappable Peripheral Inputs: 																	  */
/*----------------------------------------------------------------------------------------------------*/

#define IN_PIN_PPS_RP0				0					/* Assign RP0 as Input Pin */
#define IN_PIN_PPS_RP1				1					/* Assign RP1 as Input Pin */
#define IN_PIN_PPS_RP2				2					/* Assign RP2 as Input Pin */
#define IN_PIN_PPS_RP3				3					/* Assign RP3 as Input Pin */
#define IN_PIN_PPS_RP4				4					/* Assign RP4 as Input Pin */
#define IN_PIN_PPS_RP5				5					/* Assign RP5 as Input Pin */
#define IN_PIN_PPS_RP6				6					/* Assign RP6 as Input Pin */
#define IN_PIN_PPS_RP7				7					/* Assign RP7 as Input Pin */
#define IN_PIN_PPS_RP8				8					/* Assign RP8 as Input Pin */
#define IN_PIN_PPS_RP9				9					/* Assign RP9 as Input Pin */
#define IN_PIN_PPS_RP10				10					/* Assign RP10 as Input Pin */
#define IN_PIN_PPS_RP11				11					/* Assign RP11 as Input Pin */
#define IN_PIN_PPS_RP12				12					/* Assign RP12 as Input Pin */
#define IN_PIN_PPS_RP13				13					/* Assign RP13 as Input Pin */
#define IN_PIN_PPS_RP14				14					/* Assign RP14 as Input Pin */
#define IN_PIN_PPS_RP15				15					/* Assign RP15 as Input Pin */
#define IN_PIN_PPS_RP16				16					/* Assign RP16 as Input Pin */
#define IN_PIN_PPS_RP17				17					/* Assign RP17 as Input Pin */
#define IN_PIN_PPS_RP18				18					/* Assign RP18 as Input Pin */
#define IN_PIN_PPS_RP19				19					/* Assign RP19 as Input Pin */
#define IN_PIN_PPS_RP20				20					/* Assign RP20 as Input Pin */
#define IN_PIN_PPS_RP21				21					/* Assign RP21 as Input Pin */
#define IN_PIN_PPS_RP22				22					/* Assign RP22 as Input Pin */
#define IN_PIN_PPS_RP23				23					/* Assign RP23 as Input Pin */
#define IN_PIN_PPS_RP24				24					/* Assign RP24 as Input Pin */
#define IN_PIN_PPS_RP25				25					/* Assign RP25 as Input Pin */
#define IN_PIN_PPS_VSS				31					/* Input Pin tied to Vss */



#define IN_FN_PPS_INT1				RPINR0bits.INT1R	/* Assign External Interrupt 1 (INTR1) to the corresponding RPn pin*/
#define IN_FN_PPS_INT2				RPINR1bits.INT2R	/* Assign External Interrupt 2 (INTR2) to the corresponding RPn pin*/

#define IN_FN_PPS_T2CK				RPINR3bits.T2CKR	/* Assign Timer2 External Clock (T2CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T3CK				RPINR3bits.T3CKR	/* Assign Timer3 External Clock (T3CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T4CK				RPINR4bits.T4CKR	/* Assign Timer4 External Clock (T4CK) to the corresponding RPn pin*/
#define IN_FN_PPS_T5CK				RPINR4bits.T5CKR	/* Assign Timer5 External Clock (T5CK) to the corresponding RPn pin*/

#define IN_FN_PPS_IC1				RPINR7bits.IC1R		/* Assign Input Capture 1 (IC1) to the corresponding RPn pin*/
#define IN_FN_PPS_IC2				RPINR7bits.IC2R		/* Assign Input Capture 2 (IC2) to the corresponding RPn pin*/
#define IN_FN_PPS_IC7				RPINR10bits.IC7R	/* Assign Input Capture 7 (IC7) to the corresponding RPn pin*/
#define IN_FN_PPS_IC8				RPINR10bits.IC8R	/* Assign Input Capture 8 (IC8) to the corresponding RPn pin*/

#define IN_FN_PPS_OCFA				RPINR11bits.OCFAR	/* Assign Output Capture A (OCFA) to the corresponding RPn pin*/

#define IN_FN_PPS_FLTA1				RPINR12bits.FLTA1R	/* Assign PWM1 Fault (FLTA1) to the corresponding RPn pin*/
#define IN_FN_PPS_FLTA2				RPINR13bits.FLTA2R	/* Assign PWM2 Fault (FLTA2) to the corresponding RPn pin*/

#define IN_FN_PPS_QEA1				RPINR14bits.QEA1R	/* Assign A (QEA) to the corresponding pin*/
#define IN_FN_PPS_QEB1				RPINR14bits.QEB1R	/* Assign B (QEB) to the corresponding pin*/
#define IN_FN_PPS_QEI1				RPINR15bits.INDX1R	/* Assign QEI INDEX (INDX) to the corresponding RPn pin*/
#define IN_FN_PPS_QEA2				RPINR16bits.QEA2R	/* Assign A (QEA) to the corresponding pin*/
#define IN_FN_PPS_QEB2				RPINR16bits.QEB2R	/* Assign B (QEB) to the corresponding pin*/
#define IN_FN_PPS_QEI2				RPINR17bits.INDX2R	/* Assign QEI INDEX (INDX) to the corresponding RPn pin*/


#define IN_FN_PPS_U1RX				RPINR18bits.U1RXR	/* Assign UART1 Receive (U1RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U1CTS				RPINR18bits.U1CTSR	/* Assign UART1 Clear to Send (U1CTS) to the corresponding RPn pin*/
#define IN_FN_PPS_U2RX				RPINR19bits.U2RXR	/* Assign UART2 Receive (U2RX) to the corresponding RPn pin*/
#define IN_FN_PPS_U2CTS				RPINR19bits.U2CTSR	/* Assign UART2 Clear to Send (U2CTS) to the corresponding RPn pin*/

#define IN_FN_PPS_SDI1				RPINR20bits.SDI1R	/* Assign SPI1 Data Input (SDI1) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK1				RPINR20bits.SCK1R	/* Assign SPI1 Clock Input (SCK1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS1				RPINR21bits.SS1R	/* Assign SPI1 Slave Select Input (SS1IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SDI2				RPINR22bits.SDI2R	/* Assign SPI2 Data Input (SDI2) to the corresponding RPn pin*/
#define IN_FN_PPS_SCK2				RPINR22bits.SCK2R	/* Assign SPI2 Clock Input (SCK2IN) to the corresponding RPn pin*/
#define IN_FN_PPS_SS2				RPINR23bits.SS2R	/* Assign SPI2 Slave Select Input (SS2IN) to the corresponding RPn pin*/

#define IN_FN_PPS_CSDI				RPINR24bits.CSDIR	/* Assign DCI Serial Data Input (CSDIN) to the corresponding RPn pin*/
#define IN_FN_PPS_CSCK				RPINR24bits.CSCKR	/* Assign DCI Serial Clock Input (CSCKIN) to the corresponding RPn pin*/
#define IN_FN_PPS_COFS				RPINR25bits.COFSR	/* Assign DCI Frame Sync Input (COFSIN) to the corresponding RPn pin*/

#define IN_FN_PPS_C1RX				RPINR26bits.C1RXR	/* Assign ECAN1 Receive Input (C1RX) to the corresponding RPn pin*/

			

#define iPPSInput(fn,pin)		fn=pin
#define PPSInput(fn,pin)		iPPSInput(IN_FN_##fn,IN_PIN_##pin)

/*----------------------------------------------------------------------------------------------------*/
/*  Remappable Peripheral Outputs: 																	  */
/*----------------------------------------------------------------------------------------------------*/

#define OUT_FN_PPS_NULL				0x0000				/* RPn tied to default port pin */
#define OUT_FN_PPS_C1OUT			0x0001				/* RPn tied to Comparator1 Output */
#define OUT_FN_PPS_C2OUT			0x0002				/* RPn tied to Comparator2 Output */
#define OUT_FN_PPS_U1TX				0x0003				/* RPn tied to UART1 Transmit */
#define OUT_FN_PPS_U1RTS			0x0004				/* RPn tied to UART1 Ready To Send */
#define OUT_FN_PPS_U2TX				0x0005				/* RPn tied to UART2 Transmit */
#define OUT_FN_PPS_U2RTS			0x0006				/* RPn tied to UART2 Ready To Send */
#define OUT_FN_PPS_SDO1				0x0007				/* RPn tied to SPI1 Data Output */
#define OUT_FN_PPS_SCK1				0x0008				/* RPn tied to SPI1 Clock Output */
#define OUT_FN_PPS_SS1				0x0009				/* RPn tied to SPI1 Slave Select Output */
#define OUT_FN_PPS_SDO2				0x000A				/* RPn tied to SPI2 Data Output */
#define OUT_FN_PPS_SCK2				0x000B				/* RPn tied to SPI2 Clock Output */
#define OUT_FN_PPS_SS2				0x000C				/* RPn tied to SPI2 Slave Select Output */
#define OUT_FN_PPS_CSDO				0x000D				/* RPn tied to DCI Serial Data Output*/
#define OUT_FN_PPS_CSCKOUT			0x000E				/* RPn tied to DCI Serial Clock Output*/
#define OUT_FN_PPS_COFSOUT			0x000F				/* RPn tied to DCI Frame Sync Output*/
#define OUT_FN_PPS_C1TX				0x0010				/* RPn tied to ECAN1 Transmit */
#define OUT_FN_PPS_OC1				0x0012				/* RPn tied to Output Compare 1 */
#define OUT_FN_PPS_OC2				0x0013				/* RPn tied to Output Compare 2 */
#define OUT_FN_PPS_OC3				0x0014				/* RPn tied to Output Compare 3 */
#define OUT_FN_PPS_OC4				0x0015				/* RPn tied to Output Compare 4 */
#define OUT_FN_PPS_UPDN1			0x001A				/* RPn tied to QEI1 UPDN Output */
#define OUT_FN_PPS_UPDN2			0x001B				/* RPn tied to QEI2 UPDN Output */


#define OUT_PIN_PPS_RP0				RPOR0bits.RP0R		/* Assign RP0 as Output Pin */
#define OUT_PIN_PPS_RP1				RPOR0bits.RP1R		/* Assign RP1 as Output Pin */
#define OUT_PIN_PPS_RP2				RPOR1bits.RP2R		/* Assign RP2 as Output Pin */
#define OUT_PIN_PPS_RP3				RPOR1bits.RP3R		/* Assign RP3 as Output Pin */
#define OUT_PIN_PPS_RP4				RPOR2bits.RP4R		/* Assign RP4 as Output Pin */
#define OUT_PIN_PPS_RP5				RPOR2bits.RP5R		/* Assign RP5 as Output Pin */
#define OUT_PIN_PPS_RP6				RPOR3bits.RP6R		/* Assign RP6 as Output Pin */
#define OUT_PIN_PPS_RP7				RPOR3bits.RP7R		/* Assign RP7 as Output Pin */
#define OUT_PIN_PPS_RP8				RPOR4bits.RP8R		/* Assign RP8 as Output Pin */
#define OUT_PIN_PPS_RP9				RPOR4bits.RP9R		/* Assign RP9 as Output Pin */
#define OUT_PIN_PPS_RP10			RPOR5bits.RP10R		/* Assign RP10 as Output Pin */
#define OUT_PIN_PPS_RP11			RPOR5bits.RP11R		/* Assign RP11 as Output Pin */
#define OUT_PIN_PPS_RP12			RPOR6bits.RP12R		/* Assign RP12 as Output Pin */
#define OUT_PIN_PPS_RP13			RPOR6bits.RP13R		/* Assign RP13 as Output Pin */
#define OUT_PIN_PPS_RP14			RPOR7bits.RP14R		/* Assign RP14 as Output Pin */
#define OUT_PIN_PPS_RP15			RPOR7bits.RP15R		/* Assign RP15 as Output Pin */
#define OUT_PIN_PPS_RP16			RPOR8bits.RP16R		/* Assign RP16 as Output Pin */
#define OUT_PIN_PPS_RP17			RPOR8bits.RP17R		/* Assign RP17 as Output Pin */
#define OUT_PIN_PPS_RP18			RPOR9bits.RP18R		/* Assign RP18 as Output Pin */
#define OUT_PIN_PPS_RP19			RPOR9bits.RP19R		/* Assign RP19 as Output Pin */
#define OUT_PIN_PPS_RP20			RPOR10bits.RP20R	/* Assign RP20 as Output Pin */
#define OUT_PIN_PPS_RP21			RPOR10bits.RP21R	/* Assign RP21 as Output Pin */
#define OUT_PIN_PPS_RP22			RPOR11bits.RP22R	/* Assign RP22 as Output Pin */
#define OUT_PIN_PPS_RP23			RPOR11bits.RP23R	/* Assign RP23 as Output Pin */
#define OUT_PIN_PPS_RP24			RPOR12bits.RP24R	/* Assign RP24 as Output Pin */
#define OUT_PIN_PPS_RP25			RPOR12bits.RP25R	/* Assign RP25 as Output Pin */


#define iPPSOutput(pin,fn)		pin=fn
#define PPSOutput(fn,pin)		iPPSOutput(OUT_PIN_##pin,OUT_FN_##fn)
/*----------------------------------------------------------------------------------------------------*/

#define  PPSUnLock  __builtin_write_OSCCONL(OSCCON & 0xbf) 
#define  PPSLock 	__builtin_write_OSCCONL(OSCCON | 0x40)


#endif /*__PPS_H */

