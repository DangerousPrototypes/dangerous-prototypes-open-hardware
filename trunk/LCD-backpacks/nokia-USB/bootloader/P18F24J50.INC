        LIST

;==========================================================================
;  MPASM PIC18F24J50 processor include
; 
;  (c) Copyright 1999-2009 Microchip Technology, All rights reserved
;==========================================================================

        NOLIST

;==========================================================================
;  This header file defines configurations, registers, and other useful
;  bits of information for the PIC18F24J50 microcontroller.  These names
;  are taken to match the data sheets as closely as possible.
;
;  Note that the processor must be selected before this file is included.
;  The processor may be selected the following ways:
;
;       1. Command line switch:
;               C:\MPASM MYFILE.ASM /PIC18F24J50
;       2. LIST directive in the source file
;               LIST   P=PIC18F24J50
;       3. Processor Type entry in the MPASM full-screen interface
;       4. Setting the processor in the MPLAB Project Dialog
;==========================================================================

;==========================================================================
;
;       Verify Processor
;
;==========================================================================
        IFNDEF __18F24J50
           MESSG "Processor-header file mismatch.  Verify selected processor."
        ENDIF

;==========================================================================
;       18xxxx Family        EQUates
;==========================================================================
FSR0            EQU 0
FSR1            EQU 1
FSR2            EQU 2

FAST            EQU 1

W               EQU 0
A               EQU 0
ACCESS          EQU 0
BANKED          EQU 1
;==========================================================================

;==========================================================================
;       16Cxxx/17Cxxx Substitutions
;==========================================================================
  #define DDRA  TRISA      ; PIC17Cxxx SFR substitution
  #define DDRB  TRISB      ; PIC17Cxxx SFR substitution
  #define DDRC  TRISC      ; PIC17Cxxx SFR substitution
  #define DDRD  TRISD      ; PIC17Cxxx SFR substitution
  #define DDRE  TRISE      ; PIC17Cxxx SFR substitution

;==========================================================================
;
;       Register Definitions
;
;==========================================================================

;----- Register Files -----------------------------------------------------
RPOR0            EQU  H'0EC6'
RPOR1            EQU  H'0EC7'
RPOR2            EQU  H'0EC8'
RPOR3            EQU  H'0EC9'
RPOR4            EQU  H'0ECA'
RPOR5            EQU  H'0ECB'
RPOR6            EQU  H'0ECC'
RPOR7            EQU  H'0ECD'
RPOR8            EQU  H'0ECE'
RPOR9            EQU  H'0ECF'
RPOR10           EQU  H'0ED0'
RPOR11           EQU  H'0ED1'
RPOR12           EQU  H'0ED2'
RPOR13           EQU  H'0ED3'
RPOR17           EQU  H'0ED7'
RPOR18           EQU  H'0ED8'
RPINR1           EQU  H'0EE7'
RPINR2           EQU  H'0EE8'
RPINR3           EQU  H'0EE9'
RPINR4           EQU  H'0EEA'
RPINR6           EQU  H'0EEC'
RPINR7           EQU  H'0EED'
RPINR8           EQU  H'0EEE'
RPINR12          EQU  H'0EF2'
RPINR13          EQU  H'0EF3'
RPINR16          EQU  H'0EF6'
RPINR17          EQU  H'0EF7'
RPINR21          EQU  H'0EFB'
RPINR22          EQU  H'0EFC'
RPINR23          EQU  H'0EFD'
RPINR24          EQU  H'0EFE'
PPSCON           EQU  H'0EFF'
UEP0             EQU  H'0F26'
UEP1             EQU  H'0F27'
UEP2             EQU  H'0F28'
UEP3             EQU  H'0F29'
UEP4             EQU  H'0F2A'
UEP5             EQU  H'0F2B'
UEP6             EQU  H'0F2C'
UEP7             EQU  H'0F2D'
UEP8             EQU  H'0F2E'
UEP9             EQU  H'0F2F'
UEP10            EQU  H'0F30'
UEP11            EQU  H'0F31'
UEP12            EQU  H'0F32'
UEP13            EQU  H'0F33'
UEP14            EQU  H'0F34'
UEP15            EQU  H'0F35'
UIE              EQU  H'0F36'
UEIE             EQU  H'0F37'
UADDR            EQU  H'0F38'
UCFG             EQU  H'0F39'
PADCFG1          EQU  H'0F3C'
REFOCON          EQU  H'0F3D'
RTCCAL           EQU  H'0F3E'
RTCCFG           EQU  H'0F3F'
ODCON3           EQU  H'0F40'
ODCON2           EQU  H'0F41'
ODCON1           EQU  H'0F42'
ANCON0           EQU  H'0F48'
ANCON1           EQU  H'0F49'
DSWAKEL          EQU  H'0F4A'
DSWAKEH          EQU  H'0F4B'
DSCONL           EQU  H'0F4C'
DSCONH           EQU  H'0F4D'
DSGPR0           EQU  H'0F4E'
DSGPR1           EQU  H'0F4F'
TCLKCON          EQU  H'0F52'
UFRM             EQU  H'0F60'
UFRML            EQU  H'0F60'
UFRMH            EQU  H'0F61'
UIR              EQU  H'0F62'
UEIR             EQU  H'0F63'
USTAT            EQU  H'0F64'
UCON             EQU  H'0F65'
DMABCH           EQU  H'0F66'
DMABCL           EQU  H'0F67'
RXADDRH          EQU  H'0F68'
RXADDRL          EQU  H'0F69'
TXADDRH          EQU  H'0F6A'
TXADDRL          EQU  H'0F6B'
CMSTAT           EQU  H'0F70'
CMSTATUS         EQU  H'0F70'
SSP2CON2         EQU  H'0F71'
SSP2CON1         EQU  H'0F72'
SSP2STAT         EQU  H'0F73'
SSP2ADD          EQU  H'0F74'
SSP2BUF          EQU  H'0F75'
T4CON            EQU  H'0F76'
PR4              EQU  H'0F77'
TMR4             EQU  H'0F78'
T3CON            EQU  H'0F79'
TMR3L            EQU  H'0F7A'
TMR3H            EQU  H'0F7B'
BAUDCON2         EQU  H'0F7C'
SPBRGH2          EQU  H'0F7D'
BAUDCON          EQU  H'0F7E'
BAUDCON1         EQU  H'0F7E'
BAUDCTL          EQU  H'0F7E'
SPBRGH           EQU  H'0F7F'
SPBRGH1          EQU  H'0F7F'
PORTA            EQU  H'0F80'
PORTB            EQU  H'0F81'
PORTC            EQU  H'0F82'
HLVDCON          EQU  H'0F85'
DMACON2          EQU  H'0F86'
DMACON1          EQU  H'0F88'
LATA             EQU  H'0F89'
LATB             EQU  H'0F8A'
LATC             EQU  H'0F8B'
ALRMVALL         EQU  H'0F8E'
ALRMVALH         EQU  H'0F8F'
ALRMRPT          EQU  H'0F90'
ALRMCFG          EQU  H'0F91'
TRISA            EQU  H'0F92'
TRISB            EQU  H'0F93'
TRISC            EQU  H'0F94'
T3GCON           EQU  H'0F97'
RTCVALL          EQU  H'0F98'
RTCVALH          EQU  H'0F99'
T1GCON           EQU  H'0F9A'
OSCTUNE          EQU  H'0F9B'
RCSTA2           EQU  H'0F9C'
PIE1             EQU  H'0F9D'
PIR1             EQU  H'0F9E'
IPR1             EQU  H'0F9F'
PIE2             EQU  H'0FA0'
PIR2             EQU  H'0FA1'
IPR2             EQU  H'0FA2'
PIE3             EQU  H'0FA3'
PIR3             EQU  H'0FA4'
IPR3             EQU  H'0FA5'
EECON1           EQU  H'0FA6'
EECON2           EQU  H'0FA7'
TXSTA2           EQU  H'0FA8'
TXREG2           EQU  H'0FA9'
RCREG2           EQU  H'0FAA'
SPBRG2           EQU  H'0FAB'
RCSTA            EQU  H'0FAC'
RCSTA1           EQU  H'0FAC'
TXSTA            EQU  H'0FAD'
TXSTA1           EQU  H'0FAD'
TXREG            EQU  H'0FAE'
TXREG1           EQU  H'0FAE'
RCREG            EQU  H'0FAF'
RCREG1           EQU  H'0FAF'
SPBRG            EQU  H'0FB0'
SPBRG1           EQU  H'0FB0'
CTMUICON         EQU  H'0FB1'
CTMUCONL         EQU  H'0FB2'
CTMUCONH         EQU  H'0FB3'
CCP2CON          EQU  H'0FB4'
ECCP2CON         EQU  H'0FB4'
CCPR2            EQU  H'0FB5'
CCPR2L           EQU  H'0FB5'
CCPR2H           EQU  H'0FB6'
ECCP2DEL         EQU  H'0FB7'
PWM2CON          EQU  H'0FB7'
ECCP2AS          EQU  H'0FB8'
PSTR2CON         EQU  H'0FB9'
CCP1CON          EQU  H'0FBA'
ECCP1CON         EQU  H'0FBA'
CCPR1            EQU  H'0FBB'
CCPR1L           EQU  H'0FBB'
CCPR1H           EQU  H'0FBC'
ECCP1DEL         EQU  H'0FBD'
PWM1CON          EQU  H'0FBD'
ECCP1AS          EQU  H'0FBE'
PSTR1CON         EQU  H'0FBF'
WDTCON           EQU  H'0FC0'
ADCON1           EQU  H'0FC1'
ADCON0           EQU  H'0FC2'
ADRES            EQU  H'0FC3'
ADRESL           EQU  H'0FC3'
ADRESH           EQU  H'0FC4'
SSP1CON2         EQU  H'0FC5'
SSPCON2          EQU  H'0FC5'
SSP1CON1         EQU  H'0FC6'
SSPCON1          EQU  H'0FC6'
SSP1STAT         EQU  H'0FC7'
SSPSTAT          EQU  H'0FC7'
SSP1ADD          EQU  H'0FC8'
SSPADD           EQU  H'0FC8'
SSP1BUF          EQU  H'0FC9'
SSPBUF           EQU  H'0FC9'
T2CON            EQU  H'0FCA'
PR2              EQU  H'0FCB'
TMR2             EQU  H'0FCC'
T1CON            EQU  H'0FCD'
TMR1L            EQU  H'0FCE'
TMR1H            EQU  H'0FCF'
RCON             EQU  H'0FD0'
CM2CON           EQU  H'0FD1'
CM2CON1          EQU  H'0FD1'
CM1CON           EQU  H'0FD2'
CM1CON1          EQU  H'0FD2'
OSCCON           EQU  H'0FD3'
T0CON            EQU  H'0FD5'
TMR0L            EQU  H'0FD6'
TMR0H            EQU  H'0FD7'
STATUS           EQU  H'0FD8'
FSR2L            EQU  H'0FD9'
FSR2H            EQU  H'0FDA'
PLUSW2           EQU  H'0FDB'
PREINC2          EQU  H'0FDC'
POSTDEC2         EQU  H'0FDD'
POSTINC2         EQU  H'0FDE'
INDF2            EQU  H'0FDF'
BSR              EQU  H'0FE0'
FSR1L            EQU  H'0FE1'
FSR1H            EQU  H'0FE2'
PLUSW1           EQU  H'0FE3'
PREINC1          EQU  H'0FE4'
POSTDEC1         EQU  H'0FE5'
POSTINC1         EQU  H'0FE6'
INDF1            EQU  H'0FE7'
WREG             EQU  H'0FE8'
FSR0L            EQU  H'0FE9'
FSR0H            EQU  H'0FEA'
PLUSW0           EQU  H'0FEB'
PREINC0          EQU  H'0FEC'
POSTDEC0         EQU  H'0FED'
POSTINC0         EQU  H'0FEE'
INDF0            EQU  H'0FEF'
INTCON3          EQU  H'0FF0'
INTCON2          EQU  H'0FF1'
INTCON           EQU  H'0FF2'
PROD             EQU  H'0FF3'
PRODL            EQU  H'0FF3'
PRODH            EQU  H'0FF4'
TABLAT           EQU  H'0FF5'
TBLPTR           EQU  H'0FF6'
TBLPTRL          EQU  H'0FF6'
TBLPTRH          EQU  H'0FF7'
TBLPTRU          EQU  H'0FF8'
PC               EQU  H'0FF9'
PCL              EQU  H'0FF9'
PCLATH           EQU  H'0FFA'
PCLATU           EQU  H'0FFB'
STKPTR           EQU  H'0FFC'
TOS              EQU  H'0FFD'
TOSL             EQU  H'0FFD'
TOSH             EQU  H'0FFE'
TOSU             EQU  H'0FFF'

;----- PPSCON Bits -----------------------------------------------------
IOLOCK           EQU  H'0000'


;----- UEP0 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP1 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP2 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP3 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP4 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP5 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP6 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP7 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP8 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP9 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP10 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP11 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP12 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP13 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP14 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UEP15 Bits -----------------------------------------------------
EPSTALL          EQU  H'0000'
EPINEN           EQU  H'0001'
EPOUTEN          EQU  H'0002'
EPCONDIS         EQU  H'0003'
EPHSHK           EQU  H'0004'


;----- UIE Bits -----------------------------------------------------
URSTIE           EQU  H'0000'
UERRIE           EQU  H'0001'
ACTVIE           EQU  H'0002'
TRNIE            EQU  H'0003'
IDLEIE           EQU  H'0004'
STALLIE          EQU  H'0005'
SOFIE            EQU  H'0006'


;----- UEIE Bits -----------------------------------------------------
PIDEE            EQU  H'0000'
CRC5EE           EQU  H'0001'
CRC16EE          EQU  H'0002'
DFN8EE           EQU  H'0003'
BTOEE            EQU  H'0004'
BTSEE            EQU  H'0007'


;----- UADDR Bits -----------------------------------------------------
ADDR0            EQU  H'0000'
ADDR1            EQU  H'0001'
ADDR2            EQU  H'0002'
ADDR3            EQU  H'0003'
ADDR4            EQU  H'0004'
ADDR5            EQU  H'0005'
ADDR6            EQU  H'0006'


;----- UCFG Bits -----------------------------------------------------
PPB0             EQU  H'0000'
PPB1             EQU  H'0001'
FSEN             EQU  H'0002'
UTRDIS           EQU  H'0003'
UPUEN            EQU  H'0004'
UOEMON           EQU  H'0006'
UTEYE            EQU  H'0007'


;----- PADCFG1 Bits -----------------------------------------------------
PMPTTL           EQU  H'0000'
RTSECSEL0        EQU  H'0001'
RTSECSEL1        EQU  H'0002'


;----- REFOCON Bits -----------------------------------------------------
ROSEL            EQU  H'0004'
ROSSLP           EQU  H'0005'
ROON             EQU  H'0007'

RODIV0           EQU  H'0000'
RODIV1           EQU  H'0001'
RODIV2           EQU  H'0002'
RODIV3           EQU  H'0003'


;----- RTCCAL Bits -----------------------------------------------------
CAL0             EQU  H'0000'
CAL1             EQU  H'0001'
CAL2             EQU  H'0002'
CAL3             EQU  H'0003'
CAL4             EQU  H'0004'
CAL5             EQU  H'0005'
CAL6             EQU  H'0006'
CAL7             EQU  H'0007'


;----- RTCCFG Bits -----------------------------------------------------
RTCPTR0          EQU  H'0000'
RTCPTR1          EQU  H'0001'
RTCOE            EQU  H'0002'
HALFSEC          EQU  H'0003'
RTCSYNC          EQU  H'0004'
RTCWREN          EQU  H'0005'
RTCEN            EQU  H'0007'


;----- ODCON3 Bits -----------------------------------------------------
SPI1OD           EQU  H'0000'
SPI2OD           EQU  H'0001'


;----- ODCON2 Bits -----------------------------------------------------
U1OD             EQU  H'0000'
U2OD             EQU  H'0001'


;----- ODCON1 Bits -----------------------------------------------------
ECCP1OD          EQU  H'0000'
ECCP2OD          EQU  H'0001'


;----- ANCON0 Bits -----------------------------------------------------
PCFG0            EQU  H'0000'
PCFG1            EQU  H'0001'
PCFG2            EQU  H'0002'
PCFG3            EQU  H'0003'
PCFG4            EQU  H'0004'


;----- ANCON1 Bits -----------------------------------------------------
PCFG8            EQU  H'0000'
PCFG9            EQU  H'0001'
PCFG10           EQU  H'0002'
PCFG11           EQU  H'0003'
PCFG12           EQU  H'0004'
VBG2EN           EQU  H'0006'
VBGEN            EQU  H'0007'


;----- DSWAKEL Bits -----------------------------------------------------
DSPOR            EQU  H'0000'
DSMCLR           EQU  H'0002'
DSRTC            EQU  H'0003'
DSWDT            EQU  H'0004'
DSULP            EQU  H'0005'
DSFLT            EQU  H'0007'


;----- DSWAKEH Bits -----------------------------------------------------
DSINT0           EQU  H'0000'


;----- DSCONL Bits -----------------------------------------------------
RELEASE          EQU  H'0000'
DSBOR            EQU  H'0001'
ULPWDIS          EQU  H'0002'


;----- DSCONH Bits -----------------------------------------------------
RTCWDIS          EQU  H'0000'
DSULPEN          EQU  H'0001'
DSEN             EQU  H'0007'


;----- TCLKCON Bits -----------------------------------------------------
T3CCP1           EQU  H'0000'
T3CCP2           EQU  H'0001'
T1RUN            EQU  H'0004'


;----- UFRML Bits -----------------------------------------------------
FRM0             EQU  H'0000'
FRM1             EQU  H'0001'
FRM2             EQU  H'0002'
FRM3             EQU  H'0003'
FRM4             EQU  H'0004'
FRM5             EQU  H'0005'
FRM6             EQU  H'0006'
FRM7             EQU  H'0007'


;----- UFRMH Bits -----------------------------------------------------
FRM8             EQU  H'0000'
FRM9             EQU  H'0001'
FRM10            EQU  H'0002'


;----- UIR Bits -----------------------------------------------------
URSTIF           EQU  H'0000'
UERRIF           EQU  H'0001'
ACTVIF           EQU  H'0002'
TRNIF            EQU  H'0003'
IDLEIF           EQU  H'0004'
STALLIF          EQU  H'0005'
SOFIF            EQU  H'0006'


;----- UEIR Bits -----------------------------------------------------
PIDEF            EQU  H'0000'
CRC5EF           EQU  H'0001'
CRC16EF          EQU  H'0002'
DFN8EF           EQU  H'0003'
BTOEF            EQU  H'0004'
BTSEF            EQU  H'0007'


;----- USTAT Bits -----------------------------------------------------
PPBI             EQU  H'0001'
DIR              EQU  H'0002'

ENDP0            EQU  H'0003'
ENDP1            EQU  H'0004'
ENDP2            EQU  H'0005'
ENDP3            EQU  H'0006'


;----- UCON Bits -----------------------------------------------------
SUSPND           EQU  H'0001'
RESUME           EQU  H'0002'
USBEN            EQU  H'0003'
PKTDIS           EQU  H'0004'
SE0              EQU  H'0005'
PPBRST           EQU  H'0006'


;----- CMSTAT Bits -----------------------------------------------------
COUT1            EQU  H'0000'
COUT2            EQU  H'0001'


;----- CMSTATUS Bits -----------------------------------------------------
COUT1            EQU  H'0000'
COUT2            EQU  H'0001'


;----- SSP2CON2 Bits -----------------------------------------------------
SEN              EQU  H'0000'
RSEN             EQU  H'0001'
PEN              EQU  H'0002'
RCEN             EQU  H'0003'
ACKEN            EQU  H'0004'
ACKDT            EQU  H'0005'
ACKSTAT          EQU  H'0006'
GCEN             EQU  H'0007'

ADMSK1           EQU  H'0001'
ADMSK2           EQU  H'0002'
ADMSK3           EQU  H'0003'
ADMSK4           EQU  H'0004'
ADMSK5           EQU  H'0005'


;----- SSP2CON1 Bits -----------------------------------------------------
CKP              EQU  H'0004'
SSPEN            EQU  H'0005'
SSPOV            EQU  H'0006'
WCOL             EQU  H'0007'

SSPM0            EQU  H'0000'
SSPM1            EQU  H'0001'
SSPM2            EQU  H'0002'
SSPM3            EQU  H'0003'


;----- SSP2STAT Bits -----------------------------------------------------
BF               EQU  H'0000'
UA               EQU  H'0001'
R_NOT_W          EQU  H'0002'
S                EQU  H'0003'
P                EQU  H'0004'
D_NOT_A          EQU  H'0005'
CKE              EQU  H'0006'
SMP              EQU  H'0007'


;----- SSP2ADD Bits -----------------------------------------------------
MSK0             EQU  H'0000'
MSK1             EQU  H'0001'
MSK2             EQU  H'0002'
MSK3             EQU  H'0003'
MSK4             EQU  H'0004'
MSK5             EQU  H'0005'
MSK6             EQU  H'0006'
MSK7             EQU  H'0007'


;----- T4CON Bits -----------------------------------------------------
TMR4ON           EQU  H'0002'

T4CKPS0          EQU  H'0000'
T4CKPS1          EQU  H'0001'
T4OUTPS0         EQU  H'0003'
T4OUTPS1         EQU  H'0004'
T4OUTPS2         EQU  H'0005'
T4OUTPS3         EQU  H'0006'


;----- T3CON Bits -----------------------------------------------------
TMR3ON           EQU  H'0000'
RD16             EQU  H'0001'
T3SYNC           EQU  H'0002'

T3CKPS0          EQU  H'0004'
T3CKPS1          EQU  H'0005'
TMR3CS0          EQU  H'0006'
TMR3CS1          EQU  H'0007'


;----- BAUDCON2 Bits -----------------------------------------------------
ABDEN            EQU  H'0000'
WUE              EQU  H'0001'
BRG16            EQU  H'0003'
TXCKP            EQU  H'0004'
RXDTP            EQU  H'0005'
RCIDL            EQU  H'0006'
ABDOVF           EQU  H'0007'


;----- BAUDCON Bits -----------------------------------------------------
ABDEN            EQU  H'0000'
WUE              EQU  H'0001'
BRG16            EQU  H'0003'
TXCKP            EQU  H'0004'
RXDTP            EQU  H'0005'
RCIDL            EQU  H'0006'
ABDOVF           EQU  H'0007'


;----- BAUDCON1 Bits -----------------------------------------------------
ABDEN            EQU  H'0000'
WUE              EQU  H'0001'
BRG16            EQU  H'0003'
TXCKP            EQU  H'0004'
RXDTP            EQU  H'0005'
RCIDL            EQU  H'0006'
ABDOVF           EQU  H'0007'


;----- BAUDCTL Bits -----------------------------------------------------
ABDEN            EQU  H'0000'
WUE              EQU  H'0001'
BRG16            EQU  H'0003'
TXCKP            EQU  H'0004'
RXDTP            EQU  H'0005'
RCIDL            EQU  H'0006'
ABDOVF           EQU  H'0007'


;----- PORTA Bits -----------------------------------------------------
RA0              EQU  H'0000'
RA1              EQU  H'0001'
RA2              EQU  H'0002'
RA3              EQU  H'0003'
RA5              EQU  H'0005'
RA6              EQU  H'0006'
RA7              EQU  H'0007'


AN0              EQU  H'0000'
AN1              EQU  H'0001'
AN2              EQU  H'0002'
AN3              EQU  H'0003'
AN4              EQU  H'0005'
OSC2             EQU  H'0006'
OSC1             EQU  H'0007'

C1INA            EQU  H'0000'
C2INA            EQU  H'0001'
VREF_MINUS       EQU  H'0002'
VREF_PLUS        EQU  H'0003'
NOT_SS1          EQU  H'0005'
CLKO             EQU  H'0006'
CLKI             EQU  H'0007'

CVREF_MINUS      EQU  H'0002'
C1INB            EQU  H'0003'
HLVDIN           EQU  H'0005'

RP0              EQU  H'0000'
RP1              EQU  H'0001'
C2INB            EQU  H'0002'
RCV              EQU  H'0005'

ULPWU            EQU  H'0000'
RP2              EQU  H'0005'


;----- PORTB Bits -----------------------------------------------------
RB0              EQU  H'0000'
RB1              EQU  H'0001'
RB2              EQU  H'0002'
RB3              EQU  H'0003'
RB4              EQU  H'0004'
RB5              EQU  H'0005'
RB6              EQU  H'0006'
RB7              EQU  H'0007'


AN12             EQU  H'0000'
AN10             EQU  H'0001'
AN8              EQU  H'0002'
AN9              EQU  H'0003'
KBI2             EQU  H'0006'
KBI3             EQU  H'0007'

INT0             EQU  H'0000'
CTEDG1           EQU  H'0002'
CTEDG2           EQU  H'0003'
KBI0             EQU  H'0004'
KBI1             EQU  H'0005'
PGC              EQU  H'0006'
PGD              EQU  H'0007'

RP3              EQU  H'0000'
RTCC             EQU  H'0001'
SCK1             EQU  H'0004'
SDI1             EQU  H'0005'
RP9              EQU  H'0006'
RP10             EQU  H'0007'

RP4              EQU  H'0001'
VMO              EQU  H'0002'
VPO              EQU  H'0003'
SCL1             EQU  H'0004'
SDA1             EQU  H'0005'

REFO             EQU  H'0002'
RP6              EQU  H'0003'
RP7              EQU  H'0004'
RP8              EQU  H'0005'

RP5              EQU  H'0002'


;----- PORTC Bits -----------------------------------------------------
RC0              EQU  H'0000'
RC1              EQU  H'0001'
RC2              EQU  H'0002'
RC4              EQU  H'0004'
RC5              EQU  H'0005'
RC6              EQU  H'0006'
RC7              EQU  H'0007'


T1OSO            EQU  H'0000'
T1OSI            EQU  H'0001'
AN11             EQU  H'0002'
D_MINUS          EQU  H'0004'
D_PLUS           EQU  H'0005'

T1CK             EQU  H'0000'
NOT_UOE          EQU  H'0001'
CTPLS            EQU  H'0002'
VM               EQU  H'0004'
VP               EQU  H'0005'
TX1              EQU  H'0006'
RX1              EQU  H'0007'

RP11             EQU  H'0000'
RP12             EQU  H'0001'
RP13             EQU  H'0002'
CK1              EQU  H'0006'
DT1              EQU  H'0007'

RP17             EQU  H'0006'
SDO1             EQU  H'0007'

RP18             EQU  H'0007'


;----- HLVDCON Bits -----------------------------------------------------
HLVDEN           EQU  H'0004'
IRVST            EQU  H'0005'
BGVST            EQU  H'0006'
VDIRMAG          EQU  H'0007'

HLVDL0           EQU  H'0000'
HLVDL1           EQU  H'0001'
HLVDL2           EQU  H'0002'
HLVDL3           EQU  H'0003'


;----- DMACON2 Bits -----------------------------------------------------
INTLVL0          EQU  H'0000'
INTLVL1          EQU  H'0001'
INTLVL2          EQU  H'0002'
INTLVL3          EQU  H'0003'
DLYCYC0          EQU  H'0004'
DLYCYC1          EQU  H'0005'
DLYCYC2          EQU  H'0006'
DLYCYC3          EQU  H'0007'


;----- DMACON1 Bits -----------------------------------------------------
DMAEN            EQU  H'0000'
DLYINTEN         EQU  H'0001'
DUPLEX0          EQU  H'0002'
DUPLEX1          EQU  H'0003'
RXINC            EQU  H'0004'
TXINC            EQU  H'0005'
SSCON0           EQU  H'0006'
SSCON1           EQU  H'0007'


;----- LATA Bits -----------------------------------------------------
LATA0            EQU  H'0000'
LATA1            EQU  H'0001'
LATA2            EQU  H'0002'
LATA3            EQU  H'0003'
LATA5            EQU  H'0005'
LATA6            EQU  H'0006'
LATA7            EQU  H'0007'



;----- LATB Bits -----------------------------------------------------
LATB0            EQU  H'0000'
LATB1            EQU  H'0001'
LATB2            EQU  H'0002'
LATB3            EQU  H'0003'
LATB4            EQU  H'0004'
LATB5            EQU  H'0005'
LATB6            EQU  H'0006'
LATB7            EQU  H'0007'



;----- LATC Bits -----------------------------------------------------
LATC0            EQU  H'0000'
LATC1            EQU  H'0001'
LATC2            EQU  H'0002'
LATC4            EQU  H'0004'
LATC5            EQU  H'0005'
LATC6            EQU  H'0006'
LATC7            EQU  H'0007'



;----- ALRMRPT Bits -----------------------------------------------------
ARPT0            EQU  H'0000'
ARPT1            EQU  H'0001'
ARPT2            EQU  H'0002'
ARPT3            EQU  H'0003'
ARPT4            EQU  H'0004'
ARPT5            EQU  H'0005'
ARPT6            EQU  H'0006'
ARPT7            EQU  H'0007'


;----- ALRMCFG Bits -----------------------------------------------------
CHIME            EQU  H'0006'
ALRMEN           EQU  H'0007'

ALRMPTR0         EQU  H'0000'
ALRMPTR1         EQU  H'0001'
AMASK0           EQU  H'0002'
AMASK1           EQU  H'0003'
AMASK2           EQU  H'0004'
AMASK3           EQU  H'0005'


;----- TRISA Bits -----------------------------------------------------
TRISA0           EQU  H'0000'
TRISA1           EQU  H'0001'
TRISA2           EQU  H'0002'
TRISA3           EQU  H'0003'
TRISA5           EQU  H'0005'
TRISA6           EQU  H'0006'
TRISA7           EQU  H'0007'



;----- TRISB Bits -----------------------------------------------------
TRISB0           EQU  H'0000'
TRISB1           EQU  H'0001'
TRISB2           EQU  H'0002'
TRISB3           EQU  H'0003'
TRISB4           EQU  H'0004'
TRISB5           EQU  H'0005'
TRISB6           EQU  H'0006'
TRISB7           EQU  H'0007'



;----- TRISC Bits -----------------------------------------------------
TRISC0           EQU  H'0000'
TRISC1           EQU  H'0001'
TRISC2           EQU  H'0002'
TRISC4           EQU  H'0004'
TRISC5           EQU  H'0005'
TRISC6           EQU  H'0006'
TRISC7           EQU  H'0007'



;----- T3GCON Bits -----------------------------------------------------
T3GSS0           EQU  H'0000'
T3GSS1           EQU  H'0001'
T3GVAL           EQU  H'0002'
T3GGO_T3DONE     EQU  H'0003'
T3GSPM           EQU  H'0004'
T3GTM            EQU  H'0005'
T3GPOL           EQU  H'0006'
TMR3GE           EQU  H'0007'

T3GGO            EQU  H'0003'

T3DONE           EQU  H'0003'


;----- T1GCON Bits -----------------------------------------------------
T1GSS0           EQU  H'0000'
T1GSS1           EQU  H'0001'
T1GVAL           EQU  H'0002'
T1GGO_T1DONE     EQU  H'0003'
T1GSPM           EQU  H'0004'
T1GTM            EQU  H'0005'
T1GPOL           EQU  H'0006'
TMR1GE           EQU  H'0007'

T1GGO            EQU  H'0003'

T1DONE           EQU  H'0003'


;----- OSCTUNE Bits -----------------------------------------------------
PLLEN            EQU  H'0006'
INTSRC           EQU  H'0007'

TUN0             EQU  H'0000'
TUN1             EQU  H'0001'
TUN2             EQU  H'0002'
TUN3             EQU  H'0003'
TUN4             EQU  H'0004'
TUN5             EQU  H'0005'


;----- RCSTA2 Bits -----------------------------------------------------
RX9D             EQU  H'0000'
OERR             EQU  H'0001'
FERR             EQU  H'0002'
ADDEN            EQU  H'0003'
CREN             EQU  H'0004'
SREN             EQU  H'0005'
RX9              EQU  H'0006'
SPEN             EQU  H'0007'


;----- PIE1 Bits -----------------------------------------------------
TMR1IE           EQU  H'0000'
TMR2IE           EQU  H'0001'
CCP1IE           EQU  H'0002'
SSP1IE           EQU  H'0003'
TX1IE            EQU  H'0004'
RC1IE            EQU  H'0005'
ADIE             EQU  H'0006'

SSPIE            EQU  H'0003'
TXIE             EQU  H'0004'
RCIE             EQU  H'0005'


;----- PIR1 Bits -----------------------------------------------------
TMR1IF           EQU  H'0000'
TMR2IF           EQU  H'0001'
CCP1IF           EQU  H'0002'
SSP1IF           EQU  H'0003'
TX1IF            EQU  H'0004'
RC1IF            EQU  H'0005'
ADIF             EQU  H'0006'

SSPIF            EQU  H'0003'
TXIF             EQU  H'0004'
RCIF             EQU  H'0005'


;----- IPR1 Bits -----------------------------------------------------
TMR1IP           EQU  H'0000'
TMR2IP           EQU  H'0001'
CCP1IP           EQU  H'0002'
SSP1IP           EQU  H'0003'
TX1IP            EQU  H'0004'
RC1IP            EQU  H'0005'
ADIP             EQU  H'0006'

SSPIP            EQU  H'0003'
TXIP             EQU  H'0004'
RCIP             EQU  H'0005'


;----- PIE2 Bits -----------------------------------------------------
CCP2IE           EQU  H'0000'
TMR3IE           EQU  H'0001'
LVDIE            EQU  H'0002'
BCL1IE           EQU  H'0003'
USBIE            EQU  H'0004'
CM1IE            EQU  H'0005'
CM2IE            EQU  H'0006'
OSCFIE           EQU  H'0007'

BCLIE            EQU  H'0003'


;----- PIR2 Bits -----------------------------------------------------
CCP2IF           EQU  H'0000'
TMR3IF           EQU  H'0001'
LVDIF            EQU  H'0002'
BCL1IF           EQU  H'0003'
USBIF            EQU  H'0004'
CM1IF            EQU  H'0005'
CM2IF            EQU  H'0006'
OSCFIF           EQU  H'0007'

BCLIF            EQU  H'0003'


;----- IPR2 Bits -----------------------------------------------------
CCP2IP           EQU  H'0000'
TMR3IP           EQU  H'0001'
LVDIP            EQU  H'0002'
BCL1IP           EQU  H'0003'
USBIP            EQU  H'0004'
CM1IP            EQU  H'0005'
CM2IP            EQU  H'0006'
OSCFIP           EQU  H'0007'

BCLIP            EQU  H'0003'


;----- PIE3 Bits -----------------------------------------------------
RTCCIE           EQU  H'0000'
TMR3GIE          EQU  H'0001'
CTMUIE           EQU  H'0002'
TMR4IE           EQU  H'0003'
TX2IE            EQU  H'0004'
RC2IE            EQU  H'0005'
BCL2IE           EQU  H'0006'
SSP2IE           EQU  H'0007'


;----- PIR3 Bits -----------------------------------------------------
RTCCIF           EQU  H'0000'
TMR3GIF          EQU  H'0001'
CTMUIF           EQU  H'0002'
TMR4IF           EQU  H'0003'
TX2IF            EQU  H'0004'
RC2IF            EQU  H'0005'
BCL2IF           EQU  H'0006'
SSP2IF           EQU  H'0007'


;----- IPR3 Bits -----------------------------------------------------
RTCCIP           EQU  H'0000'
TMR3GIP          EQU  H'0001'
CTMUIP           EQU  H'0002'
TMR4IP           EQU  H'0003'
TX2IP            EQU  H'0004'
RC2IP            EQU  H'0005'
BCL2IP           EQU  H'0006'
SSP2IP           EQU  H'0007'


;----- EECON1 Bits -----------------------------------------------------
WR               EQU  H'0001'
WREN             EQU  H'0002'
WRERR            EQU  H'0003'
FREE             EQU  H'0004'
WPROG            EQU  H'0005'


;----- TXSTA2 Bits -----------------------------------------------------
TX9D             EQU  H'0000'
TRMT             EQU  H'0001'
BRGH             EQU  H'0002'
SENDB            EQU  H'0003'
SYNC             EQU  H'0004'
TXEN             EQU  H'0005'
TX9              EQU  H'0006'
CSRC             EQU  H'0007'


;----- RCSTA Bits -----------------------------------------------------
RX9D             EQU  H'0000'
OERR             EQU  H'0001'
FERR             EQU  H'0002'
ADDEN            EQU  H'0003'
CREN             EQU  H'0004'
SREN             EQU  H'0005'
RX9              EQU  H'0006'
SPEN             EQU  H'0007'

RCD8             EQU  H'0000'
ADEN             EQU  H'0003'
RC9              EQU  H'0006'

NOT_RC8          EQU  H'0006'

RC8_9            EQU  H'0006'


;----- RCSTA1 Bits -----------------------------------------------------
RX9D             EQU  H'0000'
OERR             EQU  H'0001'
FERR             EQU  H'0002'
ADDEN            EQU  H'0003'
CREN             EQU  H'0004'
SREN             EQU  H'0005'
RX9              EQU  H'0006'
SPEN             EQU  H'0007'

RCD8             EQU  H'0000'
ADEN             EQU  H'0003'
RC9              EQU  H'0006'

NOT_RC8          EQU  H'0006'

RC8_9            EQU  H'0006'


;----- TXSTA Bits -----------------------------------------------------
TX9D             EQU  H'0000'
TRMT             EQU  H'0001'
BRGH             EQU  H'0002'
SENDB            EQU  H'0003'
SYNC             EQU  H'0004'
TXEN             EQU  H'0005'
TX9              EQU  H'0006'
CSRC             EQU  H'0007'

TXD8             EQU  H'0000'
TX8_9            EQU  H'0006'

NOT_TX8          EQU  H'0006'


;----- TXSTA1 Bits -----------------------------------------------------
TX9D             EQU  H'0000'
TRMT             EQU  H'0001'
BRGH             EQU  H'0002'
SENDB            EQU  H'0003'
SYNC             EQU  H'0004'
TXEN             EQU  H'0005'
TX9              EQU  H'0006'
CSRC             EQU  H'0007'

TXD8             EQU  H'0000'
TX8_9            EQU  H'0006'

NOT_TX8          EQU  H'0006'


;----- CTMUICON Bits -----------------------------------------------------
IRNG0            EQU  H'0000'
IRNG1            EQU  H'0001'
ITRIM0           EQU  H'0002'
ITRIM1           EQU  H'0003'
ITRIM2           EQU  H'0004'
ITRIM3           EQU  H'0005'
ITRIM4           EQU  H'0006'
ITRIM5           EQU  H'0007'


;----- CTMUCONL Bits -----------------------------------------------------
EDG1STAT         EQU  H'0000'
EDG2STAT         EQU  H'0001'
EDG1SEL0         EQU  H'0002'
EDG1SEL1         EQU  H'0003'
EDG1POL          EQU  H'0004'
EDG2SEL0         EQU  H'0005'
EDG2SEL1         EQU  H'0006'
EDG2POL          EQU  H'0007'


;----- CTMUCONH Bits -----------------------------------------------------
CTTRIG           EQU  H'0000'
IDISSEN          EQU  H'0001'
EDGSEQEN         EQU  H'0002'
EDGEN            EQU  H'0003'
TGEN             EQU  H'0004'
CTMUSIDL         EQU  H'0005'
CTMUEN           EQU  H'0007'


;----- CCP2CON Bits -----------------------------------------------------
CCP2M0           EQU  H'0000'
CCP2M1           EQU  H'0001'
CCP2M2           EQU  H'0002'
CCP2M3           EQU  H'0003'
DC2B0            EQU  H'0004'
DC2B1            EQU  H'0005'
P2M0             EQU  H'0006'
P2M1             EQU  H'0007'

CCP2Y            EQU  H'0004'
CCP2X            EQU  H'0005'


;----- ECCP2CON Bits -----------------------------------------------------
CCP2M0           EQU  H'0000'
CCP2M1           EQU  H'0001'
CCP2M2           EQU  H'0002'
CCP2M3           EQU  H'0003'
DC2B0            EQU  H'0004'
DC2B1            EQU  H'0005'
P2M0             EQU  H'0006'
P2M1             EQU  H'0007'

CCP2Y            EQU  H'0004'
CCP2X            EQU  H'0005'


;----- ECCP2DEL Bits -----------------------------------------------------
P2RSEN           EQU  H'0007'

P2DC0            EQU  H'0000'
P2DC1            EQU  H'0001'
P2DC2            EQU  H'0002'
P2DC3            EQU  H'0003'
P2DC4            EQU  H'0004'
P2DC5            EQU  H'0005'
P2DC6            EQU  H'0006'


;----- PWM2CON Bits -----------------------------------------------------
P2RSEN           EQU  H'0007'

P2DC0            EQU  H'0000'
P2DC1            EQU  H'0001'
P2DC2            EQU  H'0002'
P2DC3            EQU  H'0003'
P2DC4            EQU  H'0004'
P2DC5            EQU  H'0005'
P2DC6            EQU  H'0006'


;----- ECCP2AS Bits -----------------------------------------------------
ECCP2ASE         EQU  H'0007'

PSS2BD0          EQU  H'0000'
PSS2BD1          EQU  H'0001'
PSS2AC0          EQU  H'0002'
PSS2AC1          EQU  H'0003'
ECCP2AS0         EQU  H'0004'
ECCP2AS1         EQU  H'0005'
ECCP2AS2         EQU  H'0006'


;----- PSTR2CON Bits -----------------------------------------------------
STRA             EQU  H'0000'
STRB             EQU  H'0001'
STRC             EQU  H'0002'
STRD             EQU  H'0003'
STRSYNC          EQU  H'0004'
CMPL0            EQU  H'0006'
CMPL1            EQU  H'0007'

P2DC0            EQU  H'0000'
P2DC1            EQU  H'0001'
P2DC2            EQU  H'0002'
P2DC3            EQU  H'0003'
P2DC4            EQU  H'0004'
P2DC5            EQU  H'0005'
P2DC6            EQU  H'0006'


;----- CCP1CON Bits -----------------------------------------------------
CCP1M0           EQU  H'0000'
CCP1M1           EQU  H'0001'
CCP1M2           EQU  H'0002'
CCP1M3           EQU  H'0003'
DC1B0            EQU  H'0004'
DC1B1            EQU  H'0005'
P1M0             EQU  H'0006'
P1M1             EQU  H'0007'

CCP1Y            EQU  H'0004'
CCP1X            EQU  H'0005'


;----- ECCP1CON Bits -----------------------------------------------------
CCP1M0           EQU  H'0000'
CCP1M1           EQU  H'0001'
CCP1M2           EQU  H'0002'
CCP1M3           EQU  H'0003'
DC1B0            EQU  H'0004'
DC1B1            EQU  H'0005'
P1M0             EQU  H'0006'
P1M1             EQU  H'0007'

CCP1Y            EQU  H'0004'
CCP1X            EQU  H'0005'


;----- ECCP1DEL Bits -----------------------------------------------------
P1RSEN           EQU  H'0007'

P1DC0            EQU  H'0000'
P1DC1            EQU  H'0001'
P1DC2            EQU  H'0002'
P1DC3            EQU  H'0003'
P1DC4            EQU  H'0004'
P1DC5            EQU  H'0005'
P1DC6            EQU  H'0006'


;----- PWM1CON Bits -----------------------------------------------------
P1RSEN           EQU  H'0007'

P1DC0            EQU  H'0000'
P1DC1            EQU  H'0001'
P1DC2            EQU  H'0002'
P1DC3            EQU  H'0003'
P1DC4            EQU  H'0004'
P1DC5            EQU  H'0005'
P1DC6            EQU  H'0006'


;----- ECCP1AS Bits -----------------------------------------------------
ECCP1ASE         EQU  H'0007'

PSS1BD0          EQU  H'0000'
PSS1BD1          EQU  H'0001'
PSS1AC0          EQU  H'0002'
PSS1AC1          EQU  H'0003'
ECCP1AS0         EQU  H'0004'
ECCP1AS1         EQU  H'0005'
ECCP1AS2         EQU  H'0006'


;----- PSTR1CON Bits -----------------------------------------------------
STRA             EQU  H'0000'
STRB             EQU  H'0001'
STRC             EQU  H'0002'
STRD             EQU  H'0003'
STRSYNC          EQU  H'0004'
CMPL0            EQU  H'0006'
CMPL1            EQU  H'0007'


;----- WDTCON Bits -----------------------------------------------------
SWDTEN           EQU  H'0000'
ULPSINK          EQU  H'0001'
ULPEN            EQU  H'0002'
DS               EQU  H'0003'
ULPLVL           EQU  H'0005'
LVDSTAT          EQU  H'0006'
REGSLP           EQU  H'0007'

SWDTE            EQU  H'0000'


;----- ADCON1 Bits -----------------------------------------------------
ADCAL            EQU  H'0006'
ADFM             EQU  H'0007'

ADCS0            EQU  H'0000'
ADCS1            EQU  H'0001'
ADCS2            EQU  H'0002'
ACQT0            EQU  H'0003'
ACQT1            EQU  H'0004'
ACQT2            EQU  H'0005'


;----- ADCON0 Bits -----------------------------------------------------
ADON             EQU  H'0000'
GO_NOT_DONE      EQU  H'0001'

GO_DONE          EQU  H'0001'
CHS0             EQU  H'0002'
CHS1             EQU  H'0003'
CHS2             EQU  H'0004'
CHS3             EQU  H'0005'
VCFG0            EQU  H'0006'
VCFG1            EQU  H'0007'

DONE             EQU  H'0001'

GO               EQU  H'0001'

NOT_DONE         EQU  H'0001'


;----- SSP1CON2 Bits -----------------------------------------------------
SEN              EQU  H'0000'
RSEN             EQU  H'0001'
PEN              EQU  H'0002'
RCEN             EQU  H'0003'
ACKEN            EQU  H'0004'
ACKDT            EQU  H'0005'
ACKSTAT          EQU  H'0006'
GCEN             EQU  H'0007'

ADMSK1           EQU  H'0001'
ADMSK2           EQU  H'0002'
ADMSK3           EQU  H'0003'
ADMSK4           EQU  H'0004'
ADMSK5           EQU  H'0005'


;----- SSPCON2 Bits -----------------------------------------------------
SEN              EQU  H'0000'
RSEN             EQU  H'0001'
PEN              EQU  H'0002'
RCEN             EQU  H'0003'
ACKEN            EQU  H'0004'
ACKDT            EQU  H'0005'
ACKSTAT          EQU  H'0006'
GCEN             EQU  H'0007'

ADMSK1           EQU  H'0001'
ADMSK2           EQU  H'0002'
ADMSK3           EQU  H'0003'
ADMSK4           EQU  H'0004'
ADMSK5           EQU  H'0005'


;----- SSP1CON1 Bits -----------------------------------------------------
CKP              EQU  H'0004'
SSPEN            EQU  H'0005'
SSPOV            EQU  H'0006'
WCOL             EQU  H'0007'

SSPM0            EQU  H'0000'
SSPM1            EQU  H'0001'
SSPM2            EQU  H'0002'
SSPM3            EQU  H'0003'


;----- SSPCON1 Bits -----------------------------------------------------
CKP              EQU  H'0004'
SSPEN            EQU  H'0005'
SSPOV            EQU  H'0006'
WCOL             EQU  H'0007'

SSPM0            EQU  H'0000'
SSPM1            EQU  H'0001'
SSPM2            EQU  H'0002'
SSPM3            EQU  H'0003'


;----- SSP1STAT Bits -----------------------------------------------------
BF               EQU  H'0000'
UA               EQU  H'0001'
R_NOT_W          EQU  H'0002'
S                EQU  H'0003'
P                EQU  H'0004'
D_NOT_A          EQU  H'0005'
CKE              EQU  H'0006'
SMP              EQU  H'0007'

R                EQU  H'0002'
D                EQU  H'0005'

R_W              EQU  H'0002'
D_A              EQU  H'0005'

NOT_W            EQU  H'0002'
NOT_A            EQU  H'0005'

NOT_WRITE        EQU  H'0002'
NOT_ADDRESS      EQU  H'0005'

READ_WRITE       EQU  H'0002'
DATA_ADDRESS     EQU  H'0005'

I2C_READ         EQU  H'0002'
I2C_START        EQU  H'0003'
I2C_STOP         EQU  H'0004'
I2C_DAT          EQU  H'0005'


;----- SSPSTAT Bits -----------------------------------------------------
BF               EQU  H'0000'
UA               EQU  H'0001'
R_NOT_W          EQU  H'0002'
S                EQU  H'0003'
P                EQU  H'0004'
D_NOT_A          EQU  H'0005'
CKE              EQU  H'0006'
SMP              EQU  H'0007'

R                EQU  H'0002'
D                EQU  H'0005'

R_W              EQU  H'0002'
D_A              EQU  H'0005'

NOT_W            EQU  H'0002'
NOT_A            EQU  H'0005'

NOT_WRITE        EQU  H'0002'
NOT_ADDRESS      EQU  H'0005'

READ_WRITE       EQU  H'0002'
DATA_ADDRESS     EQU  H'0005'

I2C_READ         EQU  H'0002'
I2C_START        EQU  H'0003'
I2C_STOP         EQU  H'0004'
I2C_DAT          EQU  H'0005'


;----- SSP1ADD Bits -----------------------------------------------------
MSK0             EQU  H'0000'
MSK1             EQU  H'0001'
MSK2             EQU  H'0002'
MSK3             EQU  H'0003'
MSK4             EQU  H'0004'
MSK5             EQU  H'0005'
MSK6             EQU  H'0006'
MSK7             EQU  H'0007'


;----- SSPADD Bits -----------------------------------------------------
MSK0             EQU  H'0000'
MSK1             EQU  H'0001'
MSK2             EQU  H'0002'
MSK3             EQU  H'0003'
MSK4             EQU  H'0004'
MSK5             EQU  H'0005'
MSK6             EQU  H'0006'
MSK7             EQU  H'0007'


;----- T2CON Bits -----------------------------------------------------
TMR2ON           EQU  H'0002'

T2CKPS0          EQU  H'0000'
T2CKPS1          EQU  H'0001'
T2OUTPS0         EQU  H'0003'
T2OUTPS1         EQU  H'0004'
T2OUTPS2         EQU  H'0005'
T2OUTPS3         EQU  H'0006'


;----- T1CON Bits -----------------------------------------------------
TMR1ON           EQU  H'0000'
RD16             EQU  H'0001'
T1SYNC           EQU  H'0002'
T1OSCEN          EQU  H'0003'

T1CKPS0          EQU  H'0004'
T1CKPS1          EQU  H'0005'
TMR1CS0          EQU  H'0006'
TMR1CS1          EQU  H'0007'


;----- RCON Bits -----------------------------------------------------
NOT_BOR          EQU  H'0000'
NOT_POR          EQU  H'0001'
NOT_PD           EQU  H'0002'
NOT_TO           EQU  H'0003'
NOT_RI           EQU  H'0004'
NOT_CM           EQU  H'0005'
IPEN             EQU  H'0007'

BOR              EQU  H'0000'
POR              EQU  H'0001'
PD               EQU  H'0002'
TO               EQU  H'0003'
RI               EQU  H'0004'
CM               EQU  H'0005'


;----- CM2CON Bits -----------------------------------------------------
CREF             EQU  H'0002'
CPOL             EQU  H'0005'
COE              EQU  H'0006'
CON              EQU  H'0007'

CCH0             EQU  H'0000'
CCH1             EQU  H'0001'
EVPOL0           EQU  H'0003'
EVPOL1           EQU  H'0004'


;----- CM2CON1 Bits -----------------------------------------------------
CREF             EQU  H'0002'
CPOL             EQU  H'0005'
COE              EQU  H'0006'
CON              EQU  H'0007'

CCH0             EQU  H'0000'
CCH1             EQU  H'0001'
EVPOL0           EQU  H'0003'
EVPOL1           EQU  H'0004'


;----- CM1CON Bits -----------------------------------------------------
CREF             EQU  H'0002'
CPOL             EQU  H'0005'
COE              EQU  H'0006'
CON              EQU  H'0007'

CCH0             EQU  H'0000'
CCH1             EQU  H'0001'
EVPOL0           EQU  H'0003'
EVPOL1           EQU  H'0004'


;----- CM1CON1 Bits -----------------------------------------------------
CREF             EQU  H'0002'
CPOL             EQU  H'0005'
COE              EQU  H'0006'
CON              EQU  H'0007'

CCH0             EQU  H'0000'
CCH1             EQU  H'0001'
EVPOL0           EQU  H'0003'
EVPOL1           EQU  H'0004'


;----- OSCCON Bits -----------------------------------------------------
OSTS             EQU  H'0003'
IDLEN            EQU  H'0007'

SCS0             EQU  H'0000'
SCS1             EQU  H'0001'
IRCF0            EQU  H'0004'
IRCF1            EQU  H'0005'
IRCF2            EQU  H'0006'


;----- T0CON Bits -----------------------------------------------------
PSA              EQU  H'0003'
T0SE             EQU  H'0004'
T0CS             EQU  H'0005'
T08BIT           EQU  H'0006'
TMR0ON           EQU  H'0007'

T0PS0            EQU  H'0000'
T0PS1            EQU  H'0001'
T0PS2            EQU  H'0002'


;----- STATUS Bits -----------------------------------------------------
C                EQU  H'0000'
DC               EQU  H'0001'
Z                EQU  H'0002'
OV               EQU  H'0003'
N                EQU  H'0004'


;----- INTCON3 Bits -----------------------------------------------------
INT1IF           EQU  H'0000'
INT2IF           EQU  H'0001'
INT3IF           EQU  H'0002'
INT1IE           EQU  H'0003'
INT2IE           EQU  H'0004'
INT3IE           EQU  H'0005'
INT1IP           EQU  H'0006'
INT2IP           EQU  H'0007'

INT1F            EQU  H'0000'
INT2F            EQU  H'0001'
INT3F            EQU  H'0002'
INT1E            EQU  H'0003'
INT2E            EQU  H'0004'
INT3E            EQU  H'0005'
INT1P            EQU  H'0006'
INT2P            EQU  H'0007'


;----- INTCON2 Bits -----------------------------------------------------
RBIP             EQU  H'0000'
INT3IP           EQU  H'0001'
TMR0IP           EQU  H'0002'
INTEDG3          EQU  H'0003'
INTEDG2          EQU  H'0004'
INTEDG1          EQU  H'0005'
INTEDG0          EQU  H'0006'
NOT_RBPU         EQU  H'0007'

INT3P            EQU  H'0001'
T0IP             EQU  H'0002'
RBPU             EQU  H'0007'


;----- INTCON Bits -----------------------------------------------------
RBIF             EQU  H'0000'
INT0IF           EQU  H'0001'
TMR0IF           EQU  H'0002'
RBIE             EQU  H'0003'
INT0IE           EQU  H'0004'
TMR0IE           EQU  H'0005'
PEIE_GIEL        EQU  H'0006'
GIE_GIEH         EQU  H'0007'

INT0F            EQU  H'0001'
T0IF             EQU  H'0002'
INT0E            EQU  H'0004'
T0IE             EQU  H'0005'
PEIE             EQU  H'0006'
GIE              EQU  H'0007'

GIEL             EQU  H'0006'
GIEH             EQU  H'0007'


;----- STKPTR Bits -----------------------------------------------------
STKUNF           EQU  H'0006'
STKFUL           EQU  H'0007'

SP0              EQU  H'0000'
SP1              EQU  H'0001'
SP2              EQU  H'0002'
SP3              EQU  H'0003'
SP4              EQU  H'0004'



;==========================================================================
;
;       RAM Definitions
;
;==========================================================================
       __MAXRAM  H'0FFF'
       __BADRAM  H'0ED4'-H'0ED6'
       __BADRAM  H'0ED9'-H'0EE6'
       __BADRAM  H'0EEB'
       __BADRAM  H'0EEF'-H'0EF1'
       __BADRAM  H'0EF4'-H'0EF5'
       __BADRAM  H'0EF8'-H'0EFA'
       __BADRAM  H'0F00'-H'0F25'
       __BADRAM  H'0F3A'-H'0F3B'
       __BADRAM  H'0F43'-H'0F47'
       __BADRAM  H'0F50'-H'0F51'
       __BADRAM  H'0F53'-H'0F5F'
       __BADRAM  H'0F6C'-H'0F6F'
       __BADRAM  H'0F83'-H'0F84'
       __BADRAM  H'0F87'
       __BADRAM  H'0F8C'-H'0F8D'
       __BADRAM  H'0F95'-H'0F96'
       __BADRAM  H'0FD4'

;==========================================================================
;
;   IMPORTANT: For the PIC18 devices, the __CONFIG directive has been
;              superseded by the CONFIG directive.  The following settings
;              are available for this device.
;
;   Watchdog Timer:
;     WDTEN = OFF          Disabled - Controlled by SWDTEN bit
;     WDTEN = ON           Enabled
;
;   PLL Prescaler Selection bits:
;     PLLDIV = 12          Divide by 12 (48 MHz oscillator input)
;     PLLDIV = 10          Divide by 10 (40 MHz oscillator input)
;     PLLDIV = 6           Divide by 6 (24 MHz oscillator input)
;     PLLDIV = 5           Divide by 5 (20 MHz oscillator input)
;     PLLDIV = 4           Divide by 4 (16 MHz oscillator input)
;     PLLDIV = 3           Divide by 3 (12 MHz oscillator input)
;     PLLDIV = 2           Divide by 2 (8 MHz oscillator input)
;     PLLDIV = 1           No prescale (4 MHz oscillator input drives PLL directly)
;
;   Stack Overflow/Underflow Reset :
;     STVREN = OFF         Disabled
;     STVREN = ON          Enabled
;
;   Extended Instruction Set:
;     XINST = OFF          Disabled
;     XINST = ON           Enabled
;
;   CPU System Clock Postscaler:
;     CPUDIV = OSC4_PLL6   CPU system clock divide by 6
;     CPUDIV = OSC3_PLL3   CPU system clock divide by 3
;     CPUDIV = OSC2_PLL2   CPU system clock divide by 2
;     CPUDIV = OSC1        No CPU system clock divide
;
;   Code Protect:
;     CP0 = ON             Program memory is code-protected
;     CP0 = OFF            Program memory is not code-protected
;
;   Oscillator:
;     OSC = INTOSC         INTOSC
;     OSC = INTOSCO        INTOSCO (CLKO-RA6)
;     OSC = INTOSCPLL      INTOSCPLL
;     OSC = INTOSCPLLO     INTOSCPLLO (CLKO-RA6)
;     OSC = HS             HS, USB-HS
;     OSC = HSPLL          HS+PLL, USB-HS+PLL
;     OSC = EC             EC (CLKO-RA6), USB-EC
;     OSC = ECPLL          EC+PLL (CLKO-RA6), USB-EC+PLL
;
;   T1OSCEN Enforcement:
;     T1DIG = OFF          Secondary Oscillator clock source may not be selected
;     T1DIG = ON           Secondary Oscillator clock source may be selected
;
;   Low-Power Timer1 Oscillator:
;     LPT1OSC = ON         Low-power operation
;     LPT1OSC = OFF        High-power operation
;
;   Fail-Safe Clock Monitor:
;     FCMEN = OFF          Disabled
;     FCMEN = ON           Enabled
;
;   Internal External Oscillator Switch Over Mode:
;     IESO = OFF           Disabled
;     IESO = ON            Enabled
;
;   Watchdog Postscaler:
;     WDTPS = 1            1:1
;     WDTPS = 2            1:2
;     WDTPS = 4            1:4
;     WDTPS = 8            1:8
;     WDTPS = 16           1:16
;     WDTPS = 32           1:32
;     WDTPS = 64           1:64
;     WDTPS = 128          1:128
;     WDTPS = 256          1:256
;     WDTPS = 512          1:512
;     WDTPS = 1024         1:1024
;     WDTPS = 2048         1:2048
;     WDTPS = 4096         1:4096
;     WDTPS = 8192         1:8192
;     WDTPS = 16384        1:16384
;     WDTPS = 32768        1:32768
;
;   DSWDT Clock Select:
;     DSWDTOSC = T1OSCREF  DSWDT uses T1OSC/T1CKI
;     DSWDTOSC = INTOSCREF DSWDT uses INTRC
;
;   RTCC Clock Select:
;     RTCOSC = INTOSCREF   RTCC uses INTRC
;     RTCOSC = T1OSCREF    RTCC uses T1OSC/T1CKI
;
;   Deep Sleep BOR:
;     DSBOREN = OFF        Disabled
;     DSBOREN = ON         Enabled
;
;   Deep Sleep Watchdog Timer:
;     DSWDTEN = OFF        Disabled
;     DSWDTEN = ON         Enabled
;
;   Deep Sleep Watchdog Postscaler:
;     DSWDTPS = 2          1:2 (2.1 ms)
;     DSWDTPS = 8          1:8 (8.3 ms)
;     DSWDTPS = 32         1:32 (33 ms)
;     DSWDTPS = 128        1:128 (132 ms)
;     DSWDTPS = 512        1:512 (528 ms)
;     DSWDTPS = 2048       1:2,048 (2.1 seconds)
;     DSWDTPS = 8192       1:8,192 (8.5 seconds)
;     DSWDTPS = K32        1:32,768 (34 seconds)
;     DSWDTPS = K131       1:131,072 (135 seconds)
;     DSWDTPS = K524       1:524,288 (9 minutes)
;     DSWDTPS = M2         1:2,097,152 (36 minutes)
;     DSWDTPS = M8         1:8,388,608 (2.4 hours)
;     DSWDTPS = M33        1:33,554,432 (9.6 hours)
;     DSWDTPS = M134       1:134,217,728 (38.5 hours)
;     DSWDTPS = M536       1:536,870,912 (6.4 days)
;     DSWDTPS = G2         1:2,147,483,648 (25.7 days)
;
;   IOLOCK One-Way Set Enable bit:
;     IOL1WAY = OFF        The IOLOCK bit (PPSCON<0>) can be set and cleared as needed
;     IOL1WAY = ON         The IOLOCK bit (PPSCON<0>) can be set once
;
;   MSSP address masking:
;     MSSP7B_EN = MSK5     5 Bit address masking mode
;     MSSP7B_EN = MSK7     7 Bit address masking mode
;
;   Write/Erase Protect Page Start/End Location:
;     WPFP = PAGE_0        Write Protect Program Flash Page 0
;     WPFP = PAGE_1        Write Protect Program Flash Page 1
;     WPFP = PAGE_2        Write Protect Program Flash Page 2
;     WPFP = PAGE_3        Write Protect Program Flash Page 3
;     WPFP = PAGE_4        Write Protect Program Flash Page 4
;     WPFP = PAGE_5        Write Protect Program Flash Page 5
;     WPFP = PAGE_6        Write Protect Program Flash Page 6
;     WPFP = PAGE_7        Write Protect Program Flash Page 7
;     WPFP = PAGE_8        Write Protect Program Flash Page 8
;     WPFP = PAGE_9        Write Protect Program Flash Page 9
;     WPFP = PAGE_10       Write Protect Program Flash Page 10
;     WPFP = PAGE_11       Write Protect Program Flash Page 11
;     WPFP = PAGE_12       Write Protect Program Flash Page 12
;     WPFP = PAGE_13       Write Protect Program Flash Page 13
;     WPFP = PAGE_14       Write Protect Program Flash Page 14
;     WPFP = PAGE_15       Write Protect Program Flash Page 15
;
;   Write/Erase Protect Region Select bit (valid when WPDIS = 0):
;     WPEND = PAGE_0       Page 0 to WPFP<5:0> erase/write-protected
;     WPEND = PAGE_WPFP    Pages WPFP<5:0> to (Configuration Words page) write/erase protected
;
;   Write/Erase Protect Configuration Region :
;     WPCFG = ON           Configuration Words page erase/write-protected
;     WPCFG = OFF          Configuration Words page not erase/write-protected
;
;   Write Protect Disable bit:
;     WPDIS = ON           WPFP[5:0], WPEND, and WPCFG bits enabled
;     WPDIS = OFF          WPFP[5:0], WPEND, and WPCFG bits ignored
;
;==========================================================================
_DEVID1          EQU  H'3FFFFE'
_DEVID2          EQU  H'3FFFFF'


        LIST
