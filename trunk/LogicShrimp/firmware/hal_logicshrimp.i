#line 1 "src\hal_logicshrimp.c"
#line 1 "src\hal_logicshrimp.c"
#line 1 "src/globals.h"

#line 3 "src/globals.h"


typedef unsigned char u8;
typedef unsigned int u16;


#line 1 "C:/MCC18/h/p18cxxx.h"

#line 3 "C:/MCC18/h/p18cxxx.h"

#line 5 "C:/MCC18/h/p18cxxx.h"
#line 7 "C:/MCC18/h/p18cxxx.h"
#line 9 "C:/MCC18/h/p18cxxx.h"
#line 11 "C:/MCC18/h/p18cxxx.h"
#line 13 "C:/MCC18/h/p18cxxx.h"
#line 15 "C:/MCC18/h/p18cxxx.h"
#line 17 "C:/MCC18/h/p18cxxx.h"
#line 19 "C:/MCC18/h/p18cxxx.h"
#line 21 "C:/MCC18/h/p18cxxx.h"
#line 23 "C:/MCC18/h/p18cxxx.h"
#line 25 "C:/MCC18/h/p18cxxx.h"
#line 27 "C:/MCC18/h/p18cxxx.h"
#line 29 "C:/MCC18/h/p18cxxx.h"
#line 31 "C:/MCC18/h/p18cxxx.h"
#line 33 "C:/MCC18/h/p18cxxx.h"
#line 35 "C:/MCC18/h/p18cxxx.h"
#line 37 "C:/MCC18/h/p18cxxx.h"
#line 39 "C:/MCC18/h/p18cxxx.h"
#line 41 "C:/MCC18/h/p18cxxx.h"
#line 43 "C:/MCC18/h/p18cxxx.h"
#line 45 "C:/MCC18/h/p18cxxx.h"
#line 47 "C:/MCC18/h/p18cxxx.h"
#line 49 "C:/MCC18/h/p18cxxx.h"
#line 51 "C:/MCC18/h/p18cxxx.h"
#line 53 "C:/MCC18/h/p18cxxx.h"
#line 55 "C:/MCC18/h/p18cxxx.h"
#line 57 "C:/MCC18/h/p18cxxx.h"
#line 59 "C:/MCC18/h/p18cxxx.h"
#line 61 "C:/MCC18/h/p18cxxx.h"
#line 63 "C:/MCC18/h/p18cxxx.h"
#line 65 "C:/MCC18/h/p18cxxx.h"
#line 67 "C:/MCC18/h/p18cxxx.h"
#line 69 "C:/MCC18/h/p18cxxx.h"
#line 71 "C:/MCC18/h/p18cxxx.h"
#line 73 "C:/MCC18/h/p18cxxx.h"
#line 75 "C:/MCC18/h/p18cxxx.h"
#line 77 "C:/MCC18/h/p18cxxx.h"
#line 1 "C:/MCC18/h/p18f24j50.h"

#line 5 "C:/MCC18/h/p18f24j50.h"
 


#line 9 "C:/MCC18/h/p18f24j50.h"

extern volatile far  unsigned char       RPOR0;
extern volatile far  unsigned char       RPOR1;
extern volatile far  unsigned char       RPOR2;
extern volatile far  unsigned char       RPOR3;
extern volatile far  unsigned char       RPOR4;
extern volatile far  unsigned char       RPOR5;
extern volatile far  unsigned char       RPOR6;
extern volatile far  unsigned char       RPOR7;
extern volatile far  unsigned char       RPOR8;
extern volatile far  unsigned char       RPOR9;
extern volatile far  unsigned char       RPOR10;
extern volatile far  unsigned char       RPOR11;
extern volatile far  unsigned char       RPOR12;
extern volatile far  unsigned char       RPOR13;
extern volatile far  unsigned char       RPOR17;
extern volatile far  unsigned char       RPOR18;
extern volatile far  unsigned char       RPINR1;
extern volatile far  unsigned char       RPINR2;
extern volatile far  unsigned char       RPINR3;
extern volatile far  unsigned char       RPINR4;
extern volatile far  unsigned char       RPINR6;
extern volatile far  unsigned char       RPINR7;
extern volatile far  unsigned char       RPINR8;
extern volatile far  unsigned char       RPINR12;
extern volatile far  unsigned char       RPINR13;
extern volatile far  unsigned char       RPINR16;
extern volatile far  unsigned char       RPINR17;
extern volatile far  unsigned char       RPINR21;
extern volatile far  unsigned char       RPINR22;
extern volatile far  unsigned char       RPINR23;
extern volatile far  unsigned char       RPINR24;
extern volatile far  unsigned char       PPSCON;
extern volatile far  struct {
  unsigned IOLOCK:1;
} PPSCONbits;
extern volatile far  unsigned char       UEP0;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP0bits;
extern volatile far  unsigned char       UEP1;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP1bits;
extern volatile far  unsigned char       UEP2;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP2bits;
extern volatile far  unsigned char       UEP3;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP3bits;
extern volatile far  unsigned char       UEP4;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP4bits;
extern volatile far  unsigned char       UEP5;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP5bits;
extern volatile far  unsigned char       UEP6;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP6bits;
extern volatile far  unsigned char       UEP7;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP7bits;
extern volatile far  unsigned char       UEP8;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP8bits;
extern volatile far  unsigned char       UEP9;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP9bits;
extern volatile far  unsigned char       UEP10;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP10bits;
extern volatile far  unsigned char       UEP11;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP11bits;
extern volatile far  unsigned char       UEP12;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP12bits;
extern volatile far  unsigned char       UEP13;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP13bits;
extern volatile far  unsigned char       UEP14;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP14bits;
extern volatile far  unsigned char       UEP15;
extern volatile far  struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP15bits;
extern volatile far  unsigned char       UIE;
extern volatile far  struct {
  unsigned URSTIE:1;
  unsigned UERRIE:1;
  unsigned ACTVIE:1;
  unsigned TRNIE:1;
  unsigned IDLEIE:1;
  unsigned STALLIE:1;
  unsigned SOFIE:1;
} UIEbits;
extern volatile far  unsigned char       UEIE;
extern volatile far  struct {
  unsigned PIDEE:1;
  unsigned CRC5EE:1;
  unsigned CRC16EE:1;
  unsigned DFN8EE:1;
  unsigned BTOEE:1;
  unsigned :2;
  unsigned BTSEE:1;
} UEIEbits;
extern volatile far  unsigned char       UADDR;
extern volatile far  union {
  struct {
    unsigned ADDR:7;
  };
  struct {
    unsigned ADDR0:1;
    unsigned ADDR1:1;
    unsigned ADDR2:1;
    unsigned ADDR3:1;
    unsigned ADDR4:1;
    unsigned ADDR5:1;
    unsigned ADDR6:1;
  };
} UADDRbits;
extern volatile far  unsigned char       UCFG;
extern volatile far  struct {
  unsigned PPB0:1;
  unsigned PPB1:1;
  unsigned FSEN:1;
  unsigned UTRDIS:1;
  unsigned UPUEN:1;
  unsigned :1;
  unsigned UOEMON:1;
  unsigned UTEYE:1;
} UCFGbits;
extern volatile far  unsigned char       PADCFG1;
extern volatile far  struct {
  unsigned PMPTTL:1;
  unsigned RTSECSEL0:1;
  unsigned RTSECSEL1:1;
} PADCFG1bits;
extern volatile far  unsigned char       REFOCON;
extern volatile far  union {
  struct {
    unsigned RODIV:4;
    unsigned ROSEL:1;
    unsigned ROSSLP:1;
    unsigned :1;
    unsigned ROON:1;
  };
  struct {
    unsigned RODIV0:1;
    unsigned RODIV1:1;
    unsigned RODIV2:1;
    unsigned RODIV3:1;
  };
} REFOCONbits;
extern volatile far  unsigned char       RTCCAL;
extern volatile far  union {
  struct {
    unsigned CAL:8;
  };
  struct {
    unsigned CAL0:1;
    unsigned CAL1:1;
    unsigned CAL2:1;
    unsigned CAL3:1;
    unsigned CAL4:1;
    unsigned CAL5:1;
    unsigned CAL6:1;
    unsigned CAL7:1;
  };
} RTCCALbits;
extern volatile far  unsigned char       RTCCFG;
extern volatile far  struct {
  unsigned RTCPTR0:1;
  unsigned RTCPTR1:1;
  unsigned RTCOE:1;
  unsigned HALFSEC:1;
  unsigned RTCSYNC:1;
  unsigned RTCWREN:1;
  unsigned :1;
  unsigned RTCEN:1;
} RTCCFGbits;
extern volatile far  unsigned char       ODCON3;
extern volatile far  struct {
  unsigned SPI1OD:1;
  unsigned SPI2OD:1;
} ODCON3bits;
extern volatile far  unsigned char       ODCON2;
extern volatile far  struct {
  unsigned U1OD:1;
  unsigned U2OD:1;
} ODCON2bits;
extern volatile far  unsigned char       ODCON1;
extern volatile far  struct {
  unsigned ECCP1OD:1;
  unsigned ECCP2OD:1;
} ODCON1bits;
extern volatile far  unsigned char       ANCON0;
extern volatile far  struct {
  unsigned PCFG0:1;
  unsigned PCFG1:1;
  unsigned PCFG2:1;
  unsigned PCFG3:1;
  unsigned PCFG4:1;
} ANCON0bits;
extern volatile far  unsigned char       ANCON1;
extern volatile far  struct {
  unsigned PCFG8:1;
  unsigned PCFG9:1;
  unsigned PCFG10:1;
  unsigned PCFG11:1;
  unsigned PCFG12:1;
  unsigned :1;
  unsigned VBG2EN:1;
  unsigned VBGEN:1;
} ANCON1bits;
extern volatile far  unsigned char       DSWAKEL;
extern volatile far  struct {
  unsigned DSPOR:1;
  unsigned :1;
  unsigned DSMCLR:1;
  unsigned DSRTC:1;
  unsigned DSWDT:1;
  unsigned DSULP:1;
  unsigned :1;
  unsigned DSFLT:1;
} DSWAKELbits;
extern volatile far  unsigned char       DSWAKEH;
extern volatile far  struct {
  unsigned DSINT0:1;
} DSWAKEHbits;
extern volatile far  unsigned char       DSCONL;
extern volatile far  struct {
  unsigned RELEASE:1;
  unsigned DSBOR:1;
  unsigned ULPWDIS:1;
} DSCONLbits;
extern volatile far  unsigned char       DSCONH;
extern volatile far  struct {
  unsigned RTCWDIS:1;
  unsigned DSULPEN:1;
  unsigned :5;
  unsigned DSEN:1;
} DSCONHbits;
extern volatile far  unsigned char       DSGPR0;
extern volatile far  unsigned char       DSGPR1;
extern volatile far  unsigned char       TCLKCON;
extern volatile far  struct {
  unsigned T3CCP1:1;
  unsigned T3CCP2:1;
  unsigned :2;
  unsigned T1RUN:1;
} TCLKCONbits;
extern volatile far  unsigned char       CVRCON;
extern volatile far  union {
  struct {
    unsigned CVR:4;
    unsigned CVRSS:1;
    unsigned CVRR:1;
    unsigned CVROE:1;
    unsigned CVREN:1;
  };
  struct {
    unsigned CVR0:1;
    unsigned CVR1:1;
    unsigned CVR2:1;
    unsigned CVR3:1;
  };
} CVRCONbits;
extern volatile near unsigned            UFRM;
extern volatile near unsigned char       UFRML;
extern volatile near union {
  struct {
    unsigned FRM:8;
  };
  struct {
    unsigned FRM0:1;
    unsigned FRM1:1;
    unsigned FRM2:1;
    unsigned FRM3:1;
    unsigned FRM4:1;
    unsigned FRM5:1;
    unsigned FRM6:1;
    unsigned FRM7:1;
  };
} UFRMLbits;
extern volatile near unsigned char       UFRMH;
extern volatile near union {
  struct {
    unsigned FRM:3;
  };
  struct {
    unsigned FRM8:1;
    unsigned FRM9:1;
    unsigned FRM10:1;
  };
} UFRMHbits;
extern volatile near unsigned char       UIR;
extern volatile near struct {
  unsigned URSTIF:1;
  unsigned UERRIF:1;
  unsigned ACTVIF:1;
  unsigned TRNIF:1;
  unsigned IDLEIF:1;
  unsigned STALLIF:1;
  unsigned SOFIF:1;
} UIRbits;
extern volatile near unsigned char       UEIR;
extern volatile near struct {
  unsigned PIDEF:1;
  unsigned CRC5EF:1;
  unsigned CRC16EF:1;
  unsigned DFN8EF:1;
  unsigned BTOEF:1;
  unsigned :2;
  unsigned BTSEF:1;
} UEIRbits;
extern volatile near unsigned char       USTAT;
extern volatile near union {
  struct {
    unsigned :1;
    unsigned PPBI:1;
    unsigned DIR:1;
    unsigned ENDP:4;
  };
  struct {
    unsigned :3;
    unsigned ENDP0:1;
    unsigned ENDP1:1;
    unsigned ENDP2:1;
    unsigned ENDP3:1;
  };
} USTATbits;
extern volatile near unsigned char       UCON;
extern volatile near struct {
  unsigned :1;
  unsigned SUSPND:1;
  unsigned RESUME:1;
  unsigned USBEN:1;
  unsigned PKTDIS:1;
  unsigned SE0:1;
  unsigned PPBRST:1;
} UCONbits;
extern volatile near unsigned char       DMABCH;
extern volatile near struct {
  unsigned DMACNTHB:2;
} DMABCHbits;
extern volatile near unsigned char       DMABCL;
extern volatile near unsigned char       RXADDRH;
extern volatile near struct {
  unsigned DMARCPTRHB:4;
} RXADDRHbits;
extern volatile near unsigned char       RXADDRL;
extern volatile near unsigned char       TXADDRH;
extern volatile near struct {
  unsigned DMATXPTRHB:4;
} TXADDRHbits;
extern volatile near unsigned char       TXADDRL;
extern volatile near unsigned char       CMSTAT;
extern volatile near struct {
  unsigned COUT1:1;
  unsigned COUT2:1;
} CMSTATbits;
extern volatile near unsigned char       CMSTATUS;
extern volatile near struct {
  unsigned COUT1:1;
  unsigned COUT2:1;
} CMSTATUSbits;
extern volatile near unsigned char       SSP2CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP2CON2bits;
extern volatile near unsigned char       SSP2CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP2CON1bits;
extern volatile near unsigned char       SSP2STAT;
extern volatile near struct {
  unsigned BF:1;
  unsigned UA:1;
  unsigned R_NOT_W:1;
  unsigned S:1;
  unsigned P:1;
  unsigned D_NOT_A:1;
  unsigned CKE:1;
  unsigned SMP:1;
} SSP2STATbits;
extern volatile near unsigned char       SSP2ADD;
extern volatile near union {
  struct {
    unsigned SSPADD:8;
  };
  struct {
    unsigned MSK0:1;
    unsigned MSK1:1;
    unsigned MSK2:1;
    unsigned MSK3:1;
    unsigned MSK4:1;
    unsigned MSK5:1;
    unsigned MSK6:1;
    unsigned MSK7:1;
  };
} SSP2ADDbits;
extern volatile near unsigned char       SSP2BUF;
extern volatile near unsigned char       T4CON;
extern volatile near union {
  struct {
    unsigned T4CKPS:2;
    unsigned TMR4ON:1;
    unsigned T4OUTPS:4;
  };
  struct {
    unsigned T4CKPS0:1;
    unsigned T4CKPS1:1;
    unsigned :1;
    unsigned T4OUTPS0:1;
    unsigned T4OUTPS1:1;
    unsigned T4OUTPS2:1;
    unsigned T4OUTPS3:1;
  };
} T4CONbits;
extern volatile near unsigned char       PR4;
extern volatile near unsigned char       TMR4;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned RD16:1;
    unsigned T3SYNC:1;
    unsigned :1;
    unsigned T3CKPS:2;
    unsigned TMR3CS:2;
  };
  struct {
    unsigned :4;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
    unsigned TMR3CS0:1;
    unsigned TMR3CS1:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       BAUDCON2;
extern volatile near struct {
  unsigned ABDEN:1;
  unsigned WUE:1;
  unsigned :1;
  unsigned BRG16:1;
  unsigned TXCKP:1;
  unsigned RXDTP:1;
  unsigned RCIDL:1;
  unsigned ABDOVF:1;
} BAUDCON2bits;
extern volatile near unsigned char       SPBRGH2;
extern volatile near unsigned char       BAUDCON;
extern volatile near struct {
  unsigned ABDEN:1;
  unsigned WUE:1;
  unsigned :1;
  unsigned BRG16:1;
  unsigned TXCKP:1;
  unsigned RXDTP:1;
  unsigned RCIDL:1;
  unsigned ABDOVF:1;
} BAUDCONbits;
extern volatile near unsigned char       BAUDCON1;
extern volatile near struct {
  unsigned ABDEN:1;
  unsigned WUE:1;
  unsigned :1;
  unsigned BRG16:1;
  unsigned TXCKP:1;
  unsigned RXDTP:1;
  unsigned RCIDL:1;
  unsigned ABDOVF:1;
} BAUDCON1bits;
extern volatile near unsigned char       BAUDCTL;
extern volatile near struct {
  unsigned ABDEN:1;
  unsigned WUE:1;
  unsigned :1;
  unsigned BRG16:1;
  unsigned TXCKP:1;
  unsigned RXDTP:1;
  unsigned RCIDL:1;
  unsigned ABDOVF:1;
} BAUDCTLbits;
extern volatile near unsigned char       SPBRGH;
extern volatile near unsigned char       SPBRGH1;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned :1;
    unsigned RA5:1;
    unsigned RA6:1;
    unsigned RA7:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned :1;
    unsigned AN4:1;
    unsigned OSC2:1;
    unsigned OSC1:1;
  };
  struct {
    unsigned C1INA:1;
    unsigned C2INA:1;
    unsigned VREF_MINUS:1;
    unsigned VREF_PLUS:1;
    unsigned :1;
    unsigned NOT_SS1:1;
    unsigned CLKO:1;
    unsigned CLKI:1;
  };
  struct {
    unsigned :2;
    unsigned CVREF_MINUS:1;
    unsigned C1INB:1;
    unsigned :1;
    unsigned HLVDIN:1;
  };
  struct {
    unsigned RP0:1;
    unsigned RP1:1;
    unsigned C2INB:1;
    unsigned :2;
    unsigned RCV:1;
  };
  struct {
    unsigned ULPWU:1;
    unsigned :4;
    unsigned RP2:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned AN12:1;
    unsigned AN10:1;
    unsigned AN8:1;
    unsigned AN9:1;
    unsigned :2;
    unsigned KBI2:1;
    unsigned KBI3:1;
  };
  struct {
    unsigned INT0:1;
    unsigned :1;
    unsigned CTEDG1:1;
    unsigned CTEDG2:1;
    unsigned KBI0:1;
    unsigned KBI1:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
  struct {
    unsigned RP3:1;
    unsigned RTCC:1;
    unsigned :2;
    unsigned SCK1:1;
    unsigned SDI1:1;
    unsigned RP9:1;
    unsigned RP10:1;
  };
  struct {
    unsigned :1;
    unsigned RP4:1;
    unsigned VMO:1;
    unsigned VPO:1;
    unsigned SCL1:1;
    unsigned SDA1:1;
  };
  struct {
    unsigned :2;
    unsigned REFO:1;
    unsigned RP6:1;
    unsigned RP7:1;
    unsigned RP8:1;
  };
  struct {
    unsigned :2;
    unsigned RP5:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned :1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned AN11:1;
    unsigned :1;
    unsigned D_MINUS:1;
    unsigned D_PLUS:1;
  };
  struct {
    unsigned T1CK:1;
    unsigned NOT_UOE:1;
    unsigned CTPLS:1;
    unsigned :1;
    unsigned VM:1;
    unsigned VP:1;
    unsigned TX1:1;
    unsigned RX1:1;
  };
  struct {
    unsigned RP11:1;
    unsigned RP12:1;
    unsigned RP13:1;
    unsigned :3;
    unsigned CK1:1;
    unsigned DT1:1;
  };
  struct {
    unsigned :6;
    unsigned RP17:1;
    unsigned SDO1:1;
  };
  struct {
    unsigned :7;
    unsigned RP18:1;
  };
} PORTCbits;
extern volatile near unsigned char       HLVDCON;
extern volatile near union {
  struct {
    unsigned HLVDL:4;
    unsigned HLVDEN:1;
    unsigned IRVST:1;
    unsigned BGVST:1;
    unsigned VDIRMAG:1;
  };
  struct {
    unsigned HLVDL0:1;
    unsigned HLVDL1:1;
    unsigned HLVDL2:1;
    unsigned HLVDL3:1;
  };
} HLVDCONbits;
extern volatile near unsigned char       DMACON2;
extern volatile near union {
  struct {
    unsigned INTLVL:4;
    unsigned DLYCYC:4;
  };
  struct {
    unsigned INTLVL0:1;
    unsigned INTLVL1:1;
    unsigned INTLVL2:1;
    unsigned INTLVL3:1;
    unsigned DLYCYC0:1;
    unsigned DLYCYC1:1;
    unsigned DLYCYC2:1;
    unsigned DLYCYC3:1;
  };
} DMACON2bits;
extern volatile near unsigned char       DMACON1;
extern volatile near struct {
  unsigned DMAEN:1;
  unsigned DLYINTEN:1;
  unsigned DUPLEX0:1;
  unsigned DUPLEX1:1;
  unsigned RXINC:1;
  unsigned TXINC:1;
  unsigned SSCON0:1;
  unsigned SSCON1:1;
} DMACON1bits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned :1;
  unsigned LATA5:1;
  unsigned LATA6:1;
  unsigned LATA7:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned :1;
  unsigned LATC4:1;
  unsigned LATC5:1;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       ALRMVALL;
extern volatile near unsigned char       ALRMVALH;
extern volatile near unsigned char       ALRMRPT;
extern volatile near union {
  struct {
    unsigned ARPT:8;
  };
  struct {
    unsigned ARPT0:1;
    unsigned ARPT1:1;
    unsigned ARPT2:1;
    unsigned ARPT3:1;
    unsigned ARPT4:1;
    unsigned ARPT5:1;
    unsigned ARPT6:1;
    unsigned ARPT7:1;
  };
} ALRMRPTbits;
extern volatile near unsigned char       ALRMCFG;
extern volatile near union {
  struct {
    unsigned ALRMPTR:2;
    unsigned AMASK:4;
    unsigned CHIME:1;
    unsigned ALRMEN:1;
  };
  struct {
    unsigned ALRMPTR0:1;
    unsigned ALRMPTR1:1;
    unsigned AMASK0:1;
    unsigned AMASK1:1;
    unsigned AMASK2:1;
    unsigned AMASK3:1;
  };
} ALRMCFGbits;
extern volatile near unsigned char       TRISA;
extern volatile near struct {
  unsigned TRISA0:1;
  unsigned TRISA1:1;
  unsigned TRISA2:1;
  unsigned TRISA3:1;
  unsigned :1;
  unsigned TRISA5:1;
  unsigned TRISA6:1;
  unsigned TRISA7:1;
} TRISAbits;
extern volatile near unsigned char       TRISB;
extern volatile near struct {
  unsigned TRISB0:1;
  unsigned TRISB1:1;
  unsigned TRISB2:1;
  unsigned TRISB3:1;
  unsigned TRISB4:1;
  unsigned TRISB5:1;
  unsigned TRISB6:1;
  unsigned TRISB7:1;
} TRISBbits;
extern volatile near unsigned char       TRISC;
extern volatile near struct {
  unsigned TRISC0:1;
  unsigned TRISC1:1;
  unsigned TRISC2:1;
  unsigned :1;
  unsigned TRISC4:1;
  unsigned TRISC5:1;
  unsigned TRISC6:1;
  unsigned TRISC7:1;
} TRISCbits;
extern volatile near unsigned char       T3GCON;
extern volatile near union {
  struct {
    unsigned T3GSS0:1;
    unsigned T3GSS1:1;
    unsigned T3GVAL:1;
    unsigned T3GGO_T3DONE:1;
    unsigned T3GSPM:1;
    unsigned T3GTM:1;
    unsigned T3GPOL:1;
    unsigned TMR3GE:1;
  };
  struct {
    unsigned :3;
    unsigned T3GGO:1;
  };
  struct {
    unsigned :3;
    unsigned T3DONE:1;
  };
} T3GCONbits;
extern volatile near unsigned char       RTCVALL;
extern volatile near unsigned char       RTCVALH;
extern volatile near unsigned char       T1GCON;
extern volatile near union {
  struct {
    unsigned T1GSS0:1;
    unsigned T1GSS1:1;
    unsigned T1GVAL:1;
    unsigned T1GGO_T1DONE:1;
    unsigned T1GSPM:1;
    unsigned T1GTM:1;
    unsigned T1GPOL:1;
    unsigned TMR1GE:1;
  };
  struct {
    unsigned :3;
    unsigned T1GGO:1;
  };
  struct {
    unsigned :3;
    unsigned T1DONE:1;
  };
} T1GCONbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near union {
  struct {
    unsigned TUN:6;
    unsigned PLLEN:1;
    unsigned INTSRC:1;
  };
  struct {
    unsigned TUN0:1;
    unsigned TUN1:1;
    unsigned TUN2:1;
    unsigned TUN3:1;
    unsigned TUN4:1;
    unsigned TUN5:1;
  };
} OSCTUNEbits;
extern volatile near unsigned char       RCSTA2;
extern volatile near struct {
  unsigned RX9D:1;
  unsigned OERR:1;
  unsigned FERR:1;
  unsigned ADDEN:1;
  unsigned CREN:1;
  unsigned SREN:1;
  unsigned RX9:1;
  unsigned SPEN:1;
} RCSTA2bits;
extern volatile near unsigned char       PIE1;
extern volatile near union {
  struct {
    unsigned TMR1IE:1;
    unsigned TMR2IE:1;
    unsigned CCP1IE:1;
    unsigned SSP1IE:1;
    unsigned TX1IE:1;
    unsigned RC1IE:1;
    unsigned ADIE:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIE:1;
    unsigned TXIE:1;
    unsigned RCIE:1;
  };
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near union {
  struct {
    unsigned TMR1IF:1;
    unsigned TMR2IF:1;
    unsigned CCP1IF:1;
    unsigned SSP1IF:1;
    unsigned TX1IF:1;
    unsigned RC1IF:1;
    unsigned ADIF:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIF:1;
    unsigned TXIF:1;
    unsigned RCIF:1;
  };
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near union {
  struct {
    unsigned TMR1IP:1;
    unsigned TMR2IP:1;
    unsigned CCP1IP:1;
    unsigned SSP1IP:1;
    unsigned TX1IP:1;
    unsigned RC1IP:1;
    unsigned ADIP:1;
  };
  struct {
    unsigned :3;
    unsigned SSPIP:1;
    unsigned TXIP:1;
    unsigned RCIP:1;
  };
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned LVDIE:1;
    unsigned BCL1IE:1;
    unsigned USBIE:1;
    unsigned CM1IE:1;
    unsigned CM2IE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned LVDIF:1;
    unsigned BCL1IF:1;
    unsigned USBIF:1;
    unsigned CM1IF:1;
    unsigned CM2IF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned LVDIP:1;
    unsigned BCL1IP:1;
    unsigned USBIP:1;
    unsigned CM1IP:1;
    unsigned CM2IP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :3;
    unsigned BCLIP:1;
  };
} IPR2bits;
extern volatile near unsigned char       PIE3;
extern volatile near struct {
  unsigned RTCCIE:1;
  unsigned TMR3GIE:1;
  unsigned CTMUIE:1;
  unsigned TMR4IE:1;
  unsigned TX2IE:1;
  unsigned RC2IE:1;
  unsigned BCL2IE:1;
  unsigned SSP2IE:1;
} PIE3bits;
extern volatile near unsigned char       PIR3;
extern volatile near struct {
  unsigned RTCCIF:1;
  unsigned TMR3GIF:1;
  unsigned CTMUIF:1;
  unsigned TMR4IF:1;
  unsigned TX2IF:1;
  unsigned RC2IF:1;
  unsigned BCL2IF:1;
  unsigned SSP2IF:1;
} PIR3bits;
extern volatile near unsigned char       IPR3;
extern volatile near struct {
  unsigned RTCCIP:1;
  unsigned TMR3GIP:1;
  unsigned CTMUIP:1;
  unsigned TMR4IP:1;
  unsigned TX2IP:1;
  unsigned RC2IP:1;
  unsigned BCL2IP:1;
  unsigned SSP2IP:1;
} IPR3bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned :1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
  unsigned WPROG:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       TXSTA2;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TXSTA2bits;
extern volatile near unsigned char       TXREG2;
extern volatile near unsigned char       RCREG2;
extern volatile near unsigned char       SPBRG2;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :2;
    unsigned ADEN:1;
    unsigned :2;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTAbits;
extern volatile near unsigned char       RCSTA1;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned RCD8:1;
    unsigned :2;
    unsigned ADEN:1;
    unsigned :2;
    unsigned RC9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_RC8:1;
  };
  struct {
    unsigned :6;
    unsigned RC8_9:1;
  };
} RCSTA1bits;
extern volatile near unsigned char       TXSTA;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTAbits;
extern volatile near unsigned char       TXSTA1;
extern volatile near union {
  struct {
    unsigned TX9D:1;
    unsigned TRMT:1;
    unsigned BRGH:1;
    unsigned SENDB:1;
    unsigned SYNC:1;
    unsigned TXEN:1;
    unsigned TX9:1;
    unsigned CSRC:1;
  };
  struct {
    unsigned TXD8:1;
    unsigned :5;
    unsigned TX8_9:1;
  };
  struct {
    unsigned :6;
    unsigned NOT_TX8:1;
  };
} TXSTA1bits;
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       TXREG1;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       RCREG1;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRG1;
extern volatile near unsigned char       CTMUICON;
extern volatile near union {
  struct {
    unsigned IRNG:2;
    unsigned ITRIM:6;
  };
  struct {
    unsigned IRNG0:1;
    unsigned IRNG1:1;
    unsigned ITRIM0:1;
    unsigned ITRIM1:1;
    unsigned ITRIM2:1;
    unsigned ITRIM3:1;
    unsigned ITRIM4:1;
    unsigned ITRIM5:1;
  };
} CTMUICONbits;
extern volatile near unsigned char       CTMUCONL;
extern volatile near struct {
  unsigned EDG1STAT:1;
  unsigned EDG2STAT:1;
  unsigned EDG1SEL0:1;
  unsigned EDG1SEL1:1;
  unsigned EDG1POL:1;
  unsigned EDG2SEL0:1;
  unsigned EDG2SEL1:1;
  unsigned EDG2POL:1;
} CTMUCONLbits;
extern volatile near unsigned char       CTMUCONH;
extern volatile near struct {
  unsigned CTTRIG:1;
  unsigned IDISSEN:1;
  unsigned EDGSEQEN:1;
  unsigned EDGEN:1;
  unsigned TGEN:1;
  unsigned CTMUSIDL:1;
  unsigned :1;
  unsigned CTMUEN:1;
} CTMUCONHbits;
extern volatile near unsigned char       CCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
    unsigned P2M:2;
  };
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} CCP2CONbits;
extern volatile near unsigned char       ECCP2CON;
extern volatile near union {
  struct {
    unsigned CCP2M:4;
    unsigned DC2B:2;
    unsigned P2M:2;
  };
  struct {
    unsigned CCP2M0:1;
    unsigned CCP2M1:1;
    unsigned CCP2M2:1;
    unsigned CCP2M3:1;
    unsigned DC2B0:1;
    unsigned DC2B1:1;
    unsigned P2M0:1;
    unsigned P2M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP2Y:1;
    unsigned CCP2X:1;
  };
} ECCP2CONbits;
extern volatile near unsigned            CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       ECCP2DEL;
extern volatile near union {
  struct {
    unsigned P2DC:7;
    unsigned P2RSEN:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
  };
} ECCP2DELbits;
extern volatile near unsigned char       PWM2CON;
extern volatile near union {
  struct {
    unsigned P2DC:7;
    unsigned P2RSEN:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
  };
} PWM2CONbits;
extern volatile near unsigned char       ECCP2AS;
extern volatile near union {
  struct {
    unsigned PSS2BD:2;
    unsigned PSS2AC:2;
    unsigned ECCP2AS:3;
    unsigned ECCP2ASE:1;
  };
  struct {
    unsigned PSS2BD0:1;
    unsigned PSS2BD1:1;
    unsigned PSS2AC0:1;
    unsigned PSS2AC1:1;
    unsigned ECCP2AS0:1;
    unsigned ECCP2AS1:1;
    unsigned ECCP2AS2:1;
  };
} ECCP2ASbits;
extern volatile near unsigned char       PSTR2CON;
extern volatile near union {
  struct {
    unsigned STRA:1;
    unsigned STRB:1;
    unsigned STRC:1;
    unsigned STRD:1;
    unsigned STRSYNC:1;
    unsigned :1;
    unsigned CMPL0:1;
    unsigned CMPL1:1;
  };
  struct {
    unsigned P2DC0:1;
    unsigned P2DC1:1;
    unsigned P2DC2:1;
    unsigned P2DC3:1;
    unsigned P2DC4:1;
    unsigned P2DC5:1;
    unsigned P2DC6:1;
  };
} PSTR2CONbits;
extern volatile near unsigned char       CCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M:4;
    unsigned DC1B:2;
    unsigned P1M:2;
  };
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} CCP1CONbits;
extern volatile near unsigned char       ECCP1CON;
extern volatile near union {
  struct {
    unsigned CCP1M:4;
    unsigned DC1B:2;
    unsigned P1M:2;
  };
  struct {
    unsigned CCP1M0:1;
    unsigned CCP1M1:1;
    unsigned CCP1M2:1;
    unsigned CCP1M3:1;
    unsigned DC1B0:1;
    unsigned DC1B1:1;
    unsigned P1M0:1;
    unsigned P1M1:1;
  };
  struct {
    unsigned :4;
    unsigned CCP1Y:1;
    unsigned CCP1X:1;
  };
} ECCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near union {
  struct {
    unsigned P1DC:7;
    unsigned P1RSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
  };
} ECCP1DELbits;
extern volatile near unsigned char       PWM1CON;
extern volatile near union {
  struct {
    unsigned P1DC:7;
    unsigned P1RSEN:1;
  };
  struct {
    unsigned P1DC0:1;
    unsigned P1DC1:1;
    unsigned P1DC2:1;
    unsigned P1DC3:1;
    unsigned P1DC4:1;
    unsigned P1DC5:1;
    unsigned P1DC6:1;
  };
} PWM1CONbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near union {
  struct {
    unsigned PSS1BD:2;
    unsigned PSS1AC:2;
    unsigned ECCP1AS:3;
    unsigned ECCP1ASE:1;
  };
  struct {
    unsigned PSS1BD0:1;
    unsigned PSS1BD1:1;
    unsigned PSS1AC0:1;
    unsigned PSS1AC1:1;
    unsigned ECCP1AS0:1;
    unsigned ECCP1AS1:1;
    unsigned ECCP1AS2:1;
  };
} ECCP1ASbits;
extern volatile near unsigned char       PSTR1CON;
extern volatile near struct {
  unsigned STRA:1;
  unsigned STRB:1;
  unsigned STRC:1;
  unsigned STRD:1;
  unsigned STRSYNC:1;
  unsigned :1;
  unsigned CMPL0:1;
  unsigned CMPL1:1;
} PSTR1CONbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTEN:1;
    unsigned ULPSINK:1;
    unsigned ULPEN:1;
    unsigned DS:1;
    unsigned :1;
    unsigned ULPLVL:1;
    unsigned LVDSTAT:1;
    unsigned REGSLP:1;
  };
  struct {
    unsigned SWDTE:1;
  };
} WDTCONbits;
extern volatile near unsigned char       ADCON1;
extern volatile near union {
  struct {
    unsigned ADCS:3;
    unsigned ACQT:3;
    unsigned ADCAL:1;
    unsigned ADFM:1;
  };
  struct {
    unsigned ADCS0:1;
    unsigned ADCS1:1;
    unsigned ADCS2:1;
    unsigned ACQT0:1;
    unsigned ACQT1:1;
    unsigned ACQT2:1;
  };
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned ADON:1;
    unsigned GO_NOT_DONE:1;
    unsigned CHS:4;
    unsigned VCFG:2;
  };
  struct {
    unsigned :1;
    unsigned GO_DONE:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
    unsigned VCFG0:1;
    unsigned VCFG1:1;
  };
  struct {
    unsigned :1;
    unsigned DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSP1CON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSP1CON2bits;
extern volatile near unsigned char       SSPCON2;
extern volatile near union {
  struct {
    unsigned SEN:1;
    unsigned RSEN:1;
    unsigned PEN:1;
    unsigned RCEN:1;
    unsigned ACKEN:1;
    unsigned ACKDT:1;
    unsigned ACKSTAT:1;
    unsigned GCEN:1;
  };
  struct {
    unsigned :1;
    unsigned ADMSK1:1;
    unsigned ADMSK2:1;
    unsigned ADMSK3:1;
    unsigned ADMSK4:1;
    unsigned ADMSK5:1;
  };
} SSPCON2bits;
extern volatile near unsigned char       SSP1CON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSP1CON1bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near union {
  struct {
    unsigned SSPM:4;
    unsigned CKP:1;
    unsigned SSPEN:1;
    unsigned SSPOV:1;
    unsigned WCOL:1;
  };
  struct {
    unsigned SSPM0:1;
    unsigned SSPM1:1;
    unsigned SSPM2:1;
    unsigned SSPM3:1;
  };
} SSPCON1bits;
extern volatile near unsigned char       SSP1STAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
} SSP1STATbits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_NOT_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_NOT_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
  struct {
    unsigned :2;
    unsigned R_W:1;
    unsigned :2;
    unsigned D_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSP1ADD;
extern volatile near union {
  struct {
    unsigned SSPADD:8;
  };
  struct {
    unsigned MSK0:1;
    unsigned MSK1:1;
    unsigned MSK2:1;
    unsigned MSK3:1;
    unsigned MSK4:1;
    unsigned MSK5:1;
    unsigned MSK6:1;
    unsigned MSK7:1;
  };
} SSP1ADDbits;
extern volatile near unsigned char       SSPADD;
extern volatile near union {
  struct {
    unsigned SSPADD:8;
  };
  struct {
    unsigned MSK0:1;
    unsigned MSK1:1;
    unsigned MSK2:1;
    unsigned MSK3:1;
    unsigned MSK4:1;
    unsigned MSK5:1;
    unsigned MSK6:1;
    unsigned MSK7:1;
  };
} SSPADDbits;
extern volatile near unsigned char       SSP1BUF;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near union {
  struct {
    unsigned T2CKPS:2;
    unsigned TMR2ON:1;
    unsigned T2OUTPS:4;
  };
  struct {
    unsigned T2CKPS0:1;
    unsigned T2CKPS1:1;
    unsigned :1;
    unsigned T2OUTPS0:1;
    unsigned T2OUTPS1:1;
    unsigned T2OUTPS2:1;
    unsigned T2OUTPS3:1;
  };
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned RD16:1;
    unsigned T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS:2;
    unsigned TMR1CS:2;
  };
  struct {
    unsigned :4;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
    unsigned TMR1CS0:1;
    unsigned TMR1CS1:1;
  };
} T1CONbits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned NOT_CM:1;
    unsigned :1;
    unsigned IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
    unsigned CM:1;
  };
} RCONbits;
extern volatile near unsigned char       CM2CON;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
} CM2CONbits;
extern volatile near unsigned char       CM2CON1;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
} CM2CON1bits;
extern volatile near unsigned char       CM1CON;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
} CM1CONbits;
extern volatile near unsigned char       CM1CON1;
extern volatile near union {
  struct {
    unsigned CCH:2;
    unsigned CREF:1;
    unsigned EVPOL:2;
    unsigned CPOL:1;
    unsigned COE:1;
    unsigned CON:1;
  };
  struct {
    unsigned CCH0:1;
    unsigned CCH1:1;
    unsigned :1;
    unsigned EVPOL0:1;
    unsigned EVPOL1:1;
  };
} CM1CON1bits;
extern volatile near unsigned char       OSCCON;
extern volatile near union {
  struct {
    unsigned SCS:2;
    unsigned :1;
    unsigned OSTS:1;
    unsigned IRCF:3;
    unsigned IDLEN:1;
  };
  struct {
    unsigned SCS0:1;
    unsigned SCS1:1;
    unsigned :2;
    unsigned IRCF0:1;
    unsigned IRCF1:1;
    unsigned IRCF2:1;
  };
} OSCCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near union {
  struct {
    unsigned T0PS:3;
    unsigned PSA:1;
    unsigned T0SE:1;
    unsigned T0CS:1;
    unsigned T08BIT:1;
    unsigned TMR0ON:1;
  };
  struct {
    unsigned T0PS0:1;
    unsigned T0PS1:1;
    unsigned T0PS2:1;
  };
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned INT3IF:1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned INT3IE:1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned INT3F:1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned INT3E:1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned INT3IP:1;
    unsigned TMR0IP:1;
    unsigned INTEDG3:1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :1;
    unsigned INT3P:1;
    unsigned T0IP:1;
    unsigned :4;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned RBIE:1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned PEIE_GIEL:1;
    unsigned GIE_GIEH:1;
  };
  struct {
    unsigned :1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned :1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :6;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near union {
  struct {
    unsigned STKPTR:5;
    unsigned :1;
    unsigned STKUNF:1;
    unsigned STKFUL:1;
  };
  struct {
    unsigned SP0:1;
    unsigned SP1:1;
    unsigned SP2:1;
    unsigned SP3:1;
    unsigned SP4:1;
    unsigned :2;
    unsigned STKOVF:1;
  };
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;

#pragma varlocate 14 RPOR0
#pragma varlocate 14 RPOR1
#pragma varlocate 14 RPOR2
#pragma varlocate 14 RPOR3
#pragma varlocate 14 RPOR4
#pragma varlocate 14 RPOR5
#pragma varlocate 14 RPOR6
#pragma varlocate 14 RPOR7
#pragma varlocate 14 RPOR8
#pragma varlocate 14 RPOR9
#pragma varlocate 14 RPOR10
#pragma varlocate 14 RPOR11
#pragma varlocate 14 RPOR12
#pragma varlocate 14 RPOR13
#pragma varlocate 14 RPOR17
#pragma varlocate 14 RPOR18
#pragma varlocate 14 RPINR1
#pragma varlocate 14 RPINR2
#pragma varlocate 14 RPINR3
#pragma varlocate 14 RPINR4
#pragma varlocate 14 RPINR6
#pragma varlocate 14 RPINR7
#pragma varlocate 14 RPINR8
#pragma varlocate 14 RPINR12
#pragma varlocate 14 RPINR13
#pragma varlocate 14 RPINR16
#pragma varlocate 14 RPINR17
#pragma varlocate 14 RPINR21
#pragma varlocate 14 RPINR22
#pragma varlocate 14 RPINR23
#pragma varlocate 14 RPINR24
#pragma varlocate 14 PPSCON
#pragma varlocate 14 PPSCONbits
#pragma varlocate 15 UEP0
#pragma varlocate 15 UEP0bits
#pragma varlocate 15 UEP1
#pragma varlocate 15 UEP1bits
#pragma varlocate 15 UEP2
#pragma varlocate 15 UEP2bits
#pragma varlocate 15 UEP3
#pragma varlocate 15 UEP3bits
#pragma varlocate 15 UEP4
#pragma varlocate 15 UEP4bits
#pragma varlocate 15 UEP5
#pragma varlocate 15 UEP5bits
#pragma varlocate 15 UEP6
#pragma varlocate 15 UEP6bits
#pragma varlocate 15 UEP7
#pragma varlocate 15 UEP7bits
#pragma varlocate 15 UEP8
#pragma varlocate 15 UEP8bits
#pragma varlocate 15 UEP9
#pragma varlocate 15 UEP9bits
#pragma varlocate 15 UEP10
#pragma varlocate 15 UEP10bits
#pragma varlocate 15 UEP11
#pragma varlocate 15 UEP11bits
#pragma varlocate 15 UEP12
#pragma varlocate 15 UEP12bits
#pragma varlocate 15 UEP13
#pragma varlocate 15 UEP13bits
#pragma varlocate 15 UEP14
#pragma varlocate 15 UEP14bits
#pragma varlocate 15 UEP15
#pragma varlocate 15 UEP15bits
#pragma varlocate 15 UIE
#pragma varlocate 15 UIEbits
#pragma varlocate 15 UEIE
#pragma varlocate 15 UEIEbits
#pragma varlocate 15 UADDR
#pragma varlocate 15 UADDRbits
#pragma varlocate 15 UCFG
#pragma varlocate 15 UCFGbits
#pragma varlocate 15 PADCFG1
#pragma varlocate 15 PADCFG1bits
#pragma varlocate 15 REFOCON
#pragma varlocate 15 REFOCONbits
#pragma varlocate 15 RTCCAL
#pragma varlocate 15 RTCCALbits
#pragma varlocate 15 RTCCFG
#pragma varlocate 15 RTCCFGbits
#pragma varlocate 15 ODCON3
#pragma varlocate 15 ODCON3bits
#pragma varlocate 15 ODCON2
#pragma varlocate 15 ODCON2bits
#pragma varlocate 15 ODCON1
#pragma varlocate 15 ODCON1bits
#pragma varlocate 15 ANCON0
#pragma varlocate 15 ANCON0bits
#pragma varlocate 15 ANCON1
#pragma varlocate 15 ANCON1bits
#pragma varlocate 15 DSWAKEL
#pragma varlocate 15 DSWAKELbits
#pragma varlocate 15 DSWAKEH
#pragma varlocate 15 DSWAKEHbits
#pragma varlocate 15 DSCONL
#pragma varlocate 15 DSCONLbits
#pragma varlocate 15 DSCONH
#pragma varlocate 15 DSCONHbits
#pragma varlocate 15 DSGPR0
#pragma varlocate 15 DSGPR1
#pragma varlocate 15 TCLKCON
#pragma varlocate 15 TCLKCONbits
#pragma varlocate 15 CVRCON
#pragma varlocate 15 CVRCONbits


#line 2210 "C:/MCC18/h/p18f24j50.h"
 
#line 2212 "C:/MCC18/h/p18f24j50.h"
#line 2213 "C:/MCC18/h/p18f24j50.h"


#line 2216 "C:/MCC18/h/p18f24j50.h"
 
#line 2218 "C:/MCC18/h/p18f24j50.h"
#line 2219 "C:/MCC18/h/p18f24j50.h"
#line 2220 "C:/MCC18/h/p18f24j50.h"
#line 2221 "C:/MCC18/h/p18f24j50.h"

#line 2223 "C:/MCC18/h/p18f24j50.h"
#line 2224 "C:/MCC18/h/p18f24j50.h"
#line 2225 "C:/MCC18/h/p18f24j50.h"
#line 2226 "C:/MCC18/h/p18f24j50.h"
#line 2227 "C:/MCC18/h/p18f24j50.h"


#line 2231 "C:/MCC18/h/p18f24j50.h"
 
#line 2233 "C:/MCC18/h/p18f24j50.h"


#line 2236 "C:/MCC18/h/p18f24j50.h"
#line 77 "C:/MCC18/h/p18cxxx.h"

#line 79 "C:/MCC18/h/p18cxxx.h"
#line 81 "C:/MCC18/h/p18cxxx.h"
#line 83 "C:/MCC18/h/p18cxxx.h"
#line 85 "C:/MCC18/h/p18cxxx.h"
#line 87 "C:/MCC18/h/p18cxxx.h"
#line 89 "C:/MCC18/h/p18cxxx.h"
#line 91 "C:/MCC18/h/p18cxxx.h"
#line 93 "C:/MCC18/h/p18cxxx.h"
#line 95 "C:/MCC18/h/p18cxxx.h"
#line 97 "C:/MCC18/h/p18cxxx.h"
#line 99 "C:/MCC18/h/p18cxxx.h"
#line 101 "C:/MCC18/h/p18cxxx.h"
#line 103 "C:/MCC18/h/p18cxxx.h"
#line 105 "C:/MCC18/h/p18cxxx.h"
#line 107 "C:/MCC18/h/p18cxxx.h"
#line 109 "C:/MCC18/h/p18cxxx.h"
#line 111 "C:/MCC18/h/p18cxxx.h"
#line 113 "C:/MCC18/h/p18cxxx.h"
#line 115 "C:/MCC18/h/p18cxxx.h"
#line 117 "C:/MCC18/h/p18cxxx.h"
#line 119 "C:/MCC18/h/p18cxxx.h"
#line 121 "C:/MCC18/h/p18cxxx.h"
#line 123 "C:/MCC18/h/p18cxxx.h"
#line 125 "C:/MCC18/h/p18cxxx.h"
#line 127 "C:/MCC18/h/p18cxxx.h"
#line 129 "C:/MCC18/h/p18cxxx.h"
#line 131 "C:/MCC18/h/p18cxxx.h"
#line 133 "C:/MCC18/h/p18cxxx.h"
#line 135 "C:/MCC18/h/p18cxxx.h"
#line 137 "C:/MCC18/h/p18cxxx.h"
#line 139 "C:/MCC18/h/p18cxxx.h"
#line 141 "C:/MCC18/h/p18cxxx.h"
#line 143 "C:/MCC18/h/p18cxxx.h"
#line 145 "C:/MCC18/h/p18cxxx.h"
#line 147 "C:/MCC18/h/p18cxxx.h"
#line 149 "C:/MCC18/h/p18cxxx.h"
#line 151 "C:/MCC18/h/p18cxxx.h"
#line 153 "C:/MCC18/h/p18cxxx.h"
#line 155 "C:/MCC18/h/p18cxxx.h"
#line 157 "C:/MCC18/h/p18cxxx.h"
#line 159 "C:/MCC18/h/p18cxxx.h"
#line 161 "C:/MCC18/h/p18cxxx.h"
#line 163 "C:/MCC18/h/p18cxxx.h"
#line 165 "C:/MCC18/h/p18cxxx.h"
#line 167 "C:/MCC18/h/p18cxxx.h"
#line 169 "C:/MCC18/h/p18cxxx.h"
#line 171 "C:/MCC18/h/p18cxxx.h"
#line 173 "C:/MCC18/h/p18cxxx.h"
#line 175 "C:/MCC18/h/p18cxxx.h"
#line 177 "C:/MCC18/h/p18cxxx.h"
#line 179 "C:/MCC18/h/p18cxxx.h"
#line 181 "C:/MCC18/h/p18cxxx.h"
#line 183 "C:/MCC18/h/p18cxxx.h"
#line 185 "C:/MCC18/h/p18cxxx.h"
#line 187 "C:/MCC18/h/p18cxxx.h"
#line 189 "C:/MCC18/h/p18cxxx.h"
#line 191 "C:/MCC18/h/p18cxxx.h"
#line 193 "C:/MCC18/h/p18cxxx.h"
#line 195 "C:/MCC18/h/p18cxxx.h"
#line 197 "C:/MCC18/h/p18cxxx.h"
#line 199 "C:/MCC18/h/p18cxxx.h"
#line 201 "C:/MCC18/h/p18cxxx.h"
#line 203 "C:/MCC18/h/p18cxxx.h"
#line 205 "C:/MCC18/h/p18cxxx.h"
#line 207 "C:/MCC18/h/p18cxxx.h"
#line 209 "C:/MCC18/h/p18cxxx.h"
#line 211 "C:/MCC18/h/p18cxxx.h"
#line 213 "C:/MCC18/h/p18cxxx.h"
#line 215 "C:/MCC18/h/p18cxxx.h"
#line 217 "C:/MCC18/h/p18cxxx.h"
#line 219 "C:/MCC18/h/p18cxxx.h"
#line 221 "C:/MCC18/h/p18cxxx.h"
#line 223 "C:/MCC18/h/p18cxxx.h"
#line 225 "C:/MCC18/h/p18cxxx.h"
#line 227 "C:/MCC18/h/p18cxxx.h"
#line 229 "C:/MCC18/h/p18cxxx.h"
#line 231 "C:/MCC18/h/p18cxxx.h"
#line 233 "C:/MCC18/h/p18cxxx.h"
#line 235 "C:/MCC18/h/p18cxxx.h"
#line 237 "C:/MCC18/h/p18cxxx.h"
#line 239 "C:/MCC18/h/p18cxxx.h"
#line 241 "C:/MCC18/h/p18cxxx.h"
#line 243 "C:/MCC18/h/p18cxxx.h"
#line 245 "C:/MCC18/h/p18cxxx.h"
#line 247 "C:/MCC18/h/p18cxxx.h"
#line 249 "C:/MCC18/h/p18cxxx.h"
#line 251 "C:/MCC18/h/p18cxxx.h"
#line 253 "C:/MCC18/h/p18cxxx.h"
#line 255 "C:/MCC18/h/p18cxxx.h"
#line 257 "C:/MCC18/h/p18cxxx.h"
#line 259 "C:/MCC18/h/p18cxxx.h"
#line 261 "C:/MCC18/h/p18cxxx.h"
#line 263 "C:/MCC18/h/p18cxxx.h"
#line 265 "C:/MCC18/h/p18cxxx.h"
#line 267 "C:/MCC18/h/p18cxxx.h"
#line 269 "C:/MCC18/h/p18cxxx.h"
#line 271 "C:/MCC18/h/p18cxxx.h"
#line 273 "C:/MCC18/h/p18cxxx.h"
#line 275 "C:/MCC18/h/p18cxxx.h"
#line 277 "C:/MCC18/h/p18cxxx.h"
#line 279 "C:/MCC18/h/p18cxxx.h"
#line 281 "C:/MCC18/h/p18cxxx.h"
#line 283 "C:/MCC18/h/p18cxxx.h"
#line 285 "C:/MCC18/h/p18cxxx.h"
#line 287 "C:/MCC18/h/p18cxxx.h"
#line 289 "C:/MCC18/h/p18cxxx.h"
#line 291 "C:/MCC18/h/p18cxxx.h"
#line 293 "C:/MCC18/h/p18cxxx.h"
#line 295 "C:/MCC18/h/p18cxxx.h"
#line 297 "C:/MCC18/h/p18cxxx.h"
#line 299 "C:/MCC18/h/p18cxxx.h"
#line 301 "C:/MCC18/h/p18cxxx.h"
#line 303 "C:/MCC18/h/p18cxxx.h"
#line 305 "C:/MCC18/h/p18cxxx.h"
#line 307 "C:/MCC18/h/p18cxxx.h"
#line 309 "C:/MCC18/h/p18cxxx.h"
#line 311 "C:/MCC18/h/p18cxxx.h"
#line 313 "C:/MCC18/h/p18cxxx.h"
#line 315 "C:/MCC18/h/p18cxxx.h"
#line 317 "C:/MCC18/h/p18cxxx.h"
#line 319 "C:/MCC18/h/p18cxxx.h"
#line 321 "C:/MCC18/h/p18cxxx.h"
#line 323 "C:/MCC18/h/p18cxxx.h"
#line 325 "C:/MCC18/h/p18cxxx.h"
#line 327 "C:/MCC18/h/p18cxxx.h"
#line 329 "C:/MCC18/h/p18cxxx.h"
#line 331 "C:/MCC18/h/p18cxxx.h"
#line 333 "C:/MCC18/h/p18cxxx.h"
#line 335 "C:/MCC18/h/p18cxxx.h"
#line 337 "C:/MCC18/h/p18cxxx.h"
#line 339 "C:/MCC18/h/p18cxxx.h"
#line 341 "C:/MCC18/h/p18cxxx.h"
#line 343 "C:/MCC18/h/p18cxxx.h"
#line 345 "C:/MCC18/h/p18cxxx.h"
#line 347 "C:/MCC18/h/p18cxxx.h"
#line 349 "C:/MCC18/h/p18cxxx.h"
#line 351 "C:/MCC18/h/p18cxxx.h"
#line 353 "C:/MCC18/h/p18cxxx.h"
#line 355 "C:/MCC18/h/p18cxxx.h"
#line 357 "C:/MCC18/h/p18cxxx.h"
#line 359 "C:/MCC18/h/p18cxxx.h"
#line 361 "C:/MCC18/h/p18cxxx.h"
#line 363 "C:/MCC18/h/p18cxxx.h"
#line 365 "C:/MCC18/h/p18cxxx.h"
#line 367 "C:/MCC18/h/p18cxxx.h"
#line 369 "C:/MCC18/h/p18cxxx.h"
#line 371 "C:/MCC18/h/p18cxxx.h"
#line 373 "C:/MCC18/h/p18cxxx.h"
#line 375 "C:/MCC18/h/p18cxxx.h"
#line 377 "C:/MCC18/h/p18cxxx.h"
#line 379 "C:/MCC18/h/p18cxxx.h"
#line 381 "C:/MCC18/h/p18cxxx.h"
#line 383 "C:/MCC18/h/p18cxxx.h"
#line 385 "C:/MCC18/h/p18cxxx.h"
#line 387 "C:/MCC18/h/p18cxxx.h"
#line 389 "C:/MCC18/h/p18cxxx.h"
#line 391 "C:/MCC18/h/p18cxxx.h"
#line 393 "C:/MCC18/h/p18cxxx.h"
#line 395 "C:/MCC18/h/p18cxxx.h"
#line 397 "C:/MCC18/h/p18cxxx.h"
#line 399 "C:/MCC18/h/p18cxxx.h"
#line 401 "C:/MCC18/h/p18cxxx.h"
#line 403 "C:/MCC18/h/p18cxxx.h"
#line 405 "C:/MCC18/h/p18cxxx.h"
#line 407 "C:/MCC18/h/p18cxxx.h"
#line 409 "C:/MCC18/h/p18cxxx.h"
#line 411 "C:/MCC18/h/p18cxxx.h"
#line 413 "C:/MCC18/h/p18cxxx.h"
#line 415 "C:/MCC18/h/p18cxxx.h"
#line 417 "C:/MCC18/h/p18cxxx.h"
#line 419 "C:/MCC18/h/p18cxxx.h"
#line 421 "C:/MCC18/h/p18cxxx.h"
#line 423 "C:/MCC18/h/p18cxxx.h"
#line 425 "C:/MCC18/h/p18cxxx.h"
#line 427 "C:/MCC18/h/p18cxxx.h"
#line 429 "C:/MCC18/h/p18cxxx.h"
#line 431 "C:/MCC18/h/p18cxxx.h"
#line 433 "C:/MCC18/h/p18cxxx.h"
#line 435 "C:/MCC18/h/p18cxxx.h"
#line 437 "C:/MCC18/h/p18cxxx.h"
#line 439 "C:/MCC18/h/p18cxxx.h"
#line 441 "C:/MCC18/h/p18cxxx.h"
#line 443 "C:/MCC18/h/p18cxxx.h"
#line 445 "C:/MCC18/h/p18cxxx.h"
#line 447 "C:/MCC18/h/p18cxxx.h"
#line 449 "C:/MCC18/h/p18cxxx.h"
#line 451 "C:/MCC18/h/p18cxxx.h"
#line 453 "C:/MCC18/h/p18cxxx.h"
#line 455 "C:/MCC18/h/p18cxxx.h"
#line 457 "C:/MCC18/h/p18cxxx.h"
#line 459 "C:/MCC18/h/p18cxxx.h"
#line 461 "C:/MCC18/h/p18cxxx.h"
#line 463 "C:/MCC18/h/p18cxxx.h"
#line 465 "C:/MCC18/h/p18cxxx.h"
#line 467 "C:/MCC18/h/p18cxxx.h"
#line 469 "C:/MCC18/h/p18cxxx.h"
#line 471 "C:/MCC18/h/p18cxxx.h"
#line 473 "C:/MCC18/h/p18cxxx.h"
#line 475 "C:/MCC18/h/p18cxxx.h"
#line 477 "C:/MCC18/h/p18cxxx.h"
#line 479 "C:/MCC18/h/p18cxxx.h"
#line 481 "C:/MCC18/h/p18cxxx.h"
#line 483 "C:/MCC18/h/p18cxxx.h"
#line 485 "C:/MCC18/h/p18cxxx.h"
#line 487 "C:/MCC18/h/p18cxxx.h"
#line 489 "C:/MCC18/h/p18cxxx.h"
#line 491 "C:/MCC18/h/p18cxxx.h"
#line 493 "C:/MCC18/h/p18cxxx.h"
#line 495 "C:/MCC18/h/p18cxxx.h"
#line 497 "C:/MCC18/h/p18cxxx.h"
#line 499 "C:/MCC18/h/p18cxxx.h"
#line 501 "C:/MCC18/h/p18cxxx.h"
#line 503 "C:/MCC18/h/p18cxxx.h"
#line 505 "C:/MCC18/h/p18cxxx.h"
#line 507 "C:/MCC18/h/p18cxxx.h"
#line 509 "C:/MCC18/h/p18cxxx.h"
#line 511 "C:/MCC18/h/p18cxxx.h"
#line 513 "C:/MCC18/h/p18cxxx.h"
#line 515 "C:/MCC18/h/p18cxxx.h"
#line 517 "C:/MCC18/h/p18cxxx.h"
#line 519 "C:/MCC18/h/p18cxxx.h"
#line 521 "C:/MCC18/h/p18cxxx.h"
#line 523 "C:/MCC18/h/p18cxxx.h"
#line 525 "C:/MCC18/h/p18cxxx.h"
#line 527 "C:/MCC18/h/p18cxxx.h"
#line 529 "C:/MCC18/h/p18cxxx.h"
#line 531 "C:/MCC18/h/p18cxxx.h"
#line 533 "C:/MCC18/h/p18cxxx.h"
#line 535 "C:/MCC18/h/p18cxxx.h"
#line 537 "C:/MCC18/h/p18cxxx.h"
#line 539 "C:/MCC18/h/p18cxxx.h"
#line 541 "C:/MCC18/h/p18cxxx.h"
#line 543 "C:/MCC18/h/p18cxxx.h"
#line 545 "C:/MCC18/h/p18cxxx.h"
#line 547 "C:/MCC18/h/p18cxxx.h"
#line 549 "C:/MCC18/h/p18cxxx.h"
#line 551 "C:/MCC18/h/p18cxxx.h"

#line 553 "C:/MCC18/h/p18cxxx.h"
#line 9 "src/globals.h"




#line 1 "src/HardwareProfile.h"

#line 3 "src/HardwareProfile.h"


#line 6 "src/HardwareProfile.h"


#line 9 "src/HardwareProfile.h"
#line 10 "src/HardwareProfile.h"

#line 12 "src/HardwareProfile.h"



#line 16 "src/HardwareProfile.h"
#line 17 "src/HardwareProfile.h"


#line 20 "src/HardwareProfile.h"
#line 21 "src/HardwareProfile.h"

#line 23 "src/HardwareProfile.h"
#line 13 "src/globals.h"

#line 1 "C:/MCC18/h/GenericTypeDefs.h"

#line 45 "C:/MCC18/h/GenericTypeDefs.h"
 


#line 49 "C:/MCC18/h/GenericTypeDefs.h"

 
#line 52 "C:/MCC18/h/GenericTypeDefs.h"
#line 54 "C:/MCC18/h/GenericTypeDefs.h"
#line 55 "C:/MCC18/h/GenericTypeDefs.h"
#line 56 "C:/MCC18/h/GenericTypeDefs.h"

#line 58 "C:/MCC18/h/GenericTypeDefs.h"
#line 59 "C:/MCC18/h/GenericTypeDefs.h"
#line 60 "C:/MCC18/h/GenericTypeDefs.h"

 
#line 1 "C:/MCC18/h/stddef.h"
 

#line 4 "C:/MCC18/h/stddef.h"

typedef unsigned char wchar_t;


#line 10 "C:/MCC18/h/stddef.h"
 
typedef signed short int ptrdiff_t;
typedef signed short int ptrdiffram_t;
typedef signed short long int ptrdiffrom_t;


#line 20 "C:/MCC18/h/stddef.h"
 
typedef unsigned short int size_t;
typedef unsigned short int sizeram_t;
typedef unsigned short long int sizerom_t;


#line 34 "C:/MCC18/h/stddef.h"
 
#line 36 "C:/MCC18/h/stddef.h"


#line 41 "C:/MCC18/h/stddef.h"
 
#line 43 "C:/MCC18/h/stddef.h"

#line 45 "C:/MCC18/h/stddef.h"
#line 62 "C:/MCC18/h/GenericTypeDefs.h"
 

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;     
typedef enum _BIT { CLEAR = 0, SET } BIT;

#line 68 "C:/MCC18/h/GenericTypeDefs.h"
#line 69 "C:/MCC18/h/GenericTypeDefs.h"
#line 70 "C:/MCC18/h/GenericTypeDefs.h"

 
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;

 
#line 79 "C:/MCC18/h/GenericTypeDefs.h"
#line 81 "C:/MCC18/h/GenericTypeDefs.h"

 
typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
 
#line 88 "C:/MCC18/h/GenericTypeDefs.h"
typedef unsigned short long UINT24;
#line 90 "C:/MCC18/h/GenericTypeDefs.h"
typedef unsigned long int   UINT32;      
 
#line 93 "C:/MCC18/h/GenericTypeDefs.h"
#line 95 "C:/MCC18/h/GenericTypeDefs.h"

typedef union
{
    UINT8 Val;
    struct
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union 
{
    UINT16 Val;
    UINT8 v[2] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

 
#line 144 "C:/MCC18/h/GenericTypeDefs.h"
typedef union
{
    UINT24 Val;
    UINT8 v[3] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
    } bits;
} UINT24_VAL, UINT24_BITS;
#line 183 "C:/MCC18/h/GenericTypeDefs.h"

typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8  v[4] ;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct 
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
    } bits;
} UINT32_VAL;

 
#line 245 "C:/MCC18/h/GenericTypeDefs.h"
#line 332 "C:/MCC18/h/GenericTypeDefs.h"

 

 
typedef void                    VOID;

typedef char                    CHAR8;
typedef unsigned char           UCHAR8;

typedef unsigned char           BYTE;                            
typedef unsigned short int      WORD;                            
typedef unsigned long           DWORD;                           
 

typedef unsigned long long      QWORD;                           
typedef signed char             CHAR;                            
typedef signed short int        SHORT;                           
typedef signed long             LONG;                            
 

typedef signed long long        LONGLONG;                        
typedef union
{
    BYTE Val;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] ;
    struct 
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2] ;
    BYTE v[4] ;
    struct 
    {
        WORD LW;
        WORD HW;
    } word;
    struct 
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct 
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
    } bits;
} DWORD_VAL;

 
typedef union
{
    QWORD Val;
    DWORD d[2] ;
    WORD w[4] ;
    BYTE v[8] ;
    struct 
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct 
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
         BYTE b32:1;
         BYTE b33:1;
         BYTE b34:1;
         BYTE b35:1;
         BYTE b36:1;
         BYTE b37:1;
         BYTE b38:1;
         BYTE b39:1;
         BYTE b40:1;
         BYTE b41:1;
         BYTE b42:1;
         BYTE b43:1;
         BYTE b44:1;
         BYTE b45:1;
         BYTE b46:1;
         BYTE b47:1;
         BYTE b48:1;
         BYTE b49:1;
         BYTE b50:1;
         BYTE b51:1;
         BYTE b52:1;
         BYTE b53:1;
         BYTE b54:1;
         BYTE b55:1;
         BYTE b56:1;
         BYTE b57:1;
         BYTE b58:1;
         BYTE b59:1;
         BYTE b60:1;
         BYTE b61:1;
         BYTE b62:1;
         BYTE b63:1;
    } bits;
} QWORD_VAL;

#line 547 "C:/MCC18/h/GenericTypeDefs.h"

#line 549 "C:/MCC18/h/GenericTypeDefs.h"
#line 14 "src/globals.h"



#line 1 "src/usb_config.h"



#line 5 "src/usb_config.h"

#line 7 "src/usb_config.h"
#line 8 "src/usb_config.h"

#line 10 "src/usb_config.h"
#line 11 "src/usb_config.h"

#line 13 "src/usb_config.h"
#line 14 "src/usb_config.h"

#line 16 "src/usb_config.h"

#line 18 "src/usb_config.h"


#line 21 "src/usb_config.h"

#line 23 "src/usb_config.h"

#line 25 "src/usb_config.h"

#line 27 "src/usb_config.h"

#line 29 "src/usb_config.h"
#line 30 "src/usb_config.h"
#line 31 "src/usb_config.h"

#line 33 "src/usb_config.h"

#line 35 "src/usb_config.h"
#line 36 "src/usb_config.h"
#line 37 "src/usb_config.h"

#line 39 "src/usb_config.h"
#line 40 "src/usb_config.h"
#line 41 "src/usb_config.h"
#line 42 "src/usb_config.h"

#line 44 "src/usb_config.h"



#line 48 "src/usb_config.h"
#line 17 "src/globals.h"








#line 1 "src/hal_sram.h"

#line 3 "src/hal_sram.h"

typedef enum
{
SPI_0=0,
SPI_1,
SPI_2,
SPI_3
}SPI_GROUP;

u8 * hal_sram_ParallelRWByte(u8 data);

#line 15 "src/hal_sram.h"
#line 25 "src/globals.h"

#line 1 "src/hal_logicshrimp.h"

#line 3 "src/hal_logicshrimp.h"


#line 6 "src/hal_logicshrimp.h"
#line 7 "src/hal_logicshrimp.h"
#line 8 "src/hal_logicshrimp.h"

#line 10 "src/hal_logicshrimp.h"
#line 26 "src/globals.h"


#line 29 "src/globals.h"
#line 30 "src/globals.h"



#line 34 "src/globals.h"
#line 1 "src\hal_logicshrimp.c"





void hal_logicshrimp_init(void)
{
TRISCbits.TRISC0=0; TRISBbits.TRISB5=0 ;
LATCbits.LATC0=0  ;
LATBbits.LATB5=0  ;
}
