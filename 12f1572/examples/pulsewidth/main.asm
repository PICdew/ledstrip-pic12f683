;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.1 #9093 (Nov  1 2014) (Linux)
; This file was generated Sun Nov 23 01:08:26 2014
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"main.c"
	list	p=12f1572
	radix dec
	include "p12f1572.inc"
;--------------------------------------------------------
; config word(s)
;--------------------------------------------------------
	__config _CONFIG1, 0x39e4
	__config _CONFIG2, 0x3fff
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_STATUSbits
	extern	_BSRbits
	extern	_INTCONbits
	extern	_PORTAbits
	extern	_PIR1bits
	extern	_PIR2bits
	extern	_PIR3bits
	extern	_T1CONbits
	extern	_T1GCONbits
	extern	_T2CONbits
	extern	_TRISAbits
	extern	_PIE1bits
	extern	_PIE2bits
	extern	_PIE3bits
	extern	_OPTION_REGbits
	extern	_PCONbits
	extern	_WDTCONbits
	extern	_OSCTUNEbits
	extern	_OSCCONbits
	extern	_OSCSTATbits
	extern	_ADCON0bits
	extern	_ADCON1bits
	extern	_ADCON2bits
	extern	_LATAbits
	extern	_CM1CON0bits
	extern	_CM1CON1bits
	extern	_CMOUTbits
	extern	_BORCONbits
	extern	_FVRCONbits
	extern	_DACCON0bits
	extern	_DACCON1bits
	extern	_APFCONbits
	extern	_APFCON0bits
	extern	_ANSELAbits
	extern	_PMCON1bits
	extern	_VREGCONbits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_BAUDCONbits
	extern	_WPUAbits
	extern	_ODCONAbits
	extern	_SLRCONAbits
	extern	_INLVLAbits
	extern	_IOCAPbits
	extern	_IOCANbits
	extern	_IOCAFbits
	extern	_CWG1DBRbits
	extern	_CWG1DBFbits
	extern	_CWG1CON0bits
	extern	_CWG1CON1bits
	extern	_CWG1CON2bits
	extern	_PWMENbits
	extern	_PWMLDbits
	extern	_PWMOUTbits
	extern	_PWM1PHLbits
	extern	_PWM1PHHbits
	extern	_PWM1DCLbits
	extern	_PWM1DCHbits
	extern	_PWM1PRLbits
	extern	_PWM1PRHbits
	extern	_PWM1OFLbits
	extern	_PWM1OFHbits
	extern	_PWM1TMRLbits
	extern	_PWM1TMRHbits
	extern	_PWM1CONbits
	extern	_PWM1INTCONbits
	extern	_PWM1INTEbits
	extern	_PWM1INTFbits
	extern	_PWM1INTFLGbits
	extern	_PWM1CLKCONbits
	extern	_PWM1LDCONbits
	extern	_PWM1OFCONbits
	extern	_PWM2PHLbits
	extern	_PWM2PHHbits
	extern	_PWM2DCLbits
	extern	_PWM2DCHbits
	extern	_PWM2PRLbits
	extern	_PWM2PRHbits
	extern	_PWM2OFLbits
	extern	_PWM2OFHbits
	extern	_PWM2TMRLbits
	extern	_PWM2TMRHbits
	extern	_PWM2CONbits
	extern	_PWM2INTEbits
	extern	_PWM2INTFbits
	extern	_PWM2CLKCONbits
	extern	_PWM2LDCONbits
	extern	_PWM2OFCONbits
	extern	_PWM3PHLbits
	extern	_PWM3PHHbits
	extern	_PWM3DCLbits
	extern	_PWM3DCHbits
	extern	_PWM3PRLbits
	extern	_PWM3PRHbits
	extern	_PWM3OFLbits
	extern	_PWM3OFHbits
	extern	_PWM3TMRLbits
	extern	_PWM3TMRHbits
	extern	_PWM3CONbits
	extern	_PWM3INTEbits
	extern	_PWM3INTFbits
	extern	_PWM3CLKCONbits
	extern	_PWM3LDCONbits
	extern	_PWM3OFCONbits
	extern	_STATUS_SHADbits
	extern	_INDF0
	extern	_INDF1
	extern	_PCL
	extern	_STATUS
	extern	_FSR0
	extern	_FSR0L
	extern	_FSR0H
	extern	_FSR1
	extern	_FSR1L
	extern	_FSR1H
	extern	_BSR
	extern	_WREG
	extern	_PCLATH
	extern	_INTCON
	extern	_PORTA
	extern	_PIR1
	extern	_PIR2
	extern	_PIR3
	extern	_TMR0
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_T1GCON
	extern	_TMR2
	extern	_PR2
	extern	_T2CON
	extern	_TRISA
	extern	_PIE1
	extern	_PIE2
	extern	_PIE3
	extern	_OPTION_REG
	extern	_PCON
	extern	_WDTCON
	extern	_OSCTUNE
	extern	_OSCCON
	extern	_OSCSTAT
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_ADCON0
	extern	_ADCON1
	extern	_ADCON2
	extern	_LATA
	extern	_CM1CON0
	extern	_CM1CON1
	extern	_CMOUT
	extern	_BORCON
	extern	_FVRCON
	extern	_DACCON0
	extern	_DACCON1
	extern	_APFCON
	extern	_APFCON0
	extern	_ANSELA
	extern	_PMADR
	extern	_PMADRL
	extern	_PMADRH
	extern	_PMDAT
	extern	_PMDATL
	extern	_PMDATH
	extern	_PMCON1
	extern	_PMCON2
	extern	_VREGCON
	extern	_RCREG
	extern	_TXREG
	extern	_SPBRG
	extern	_SPBRGL
	extern	_SPBRGH
	extern	_RCSTA
	extern	_TXSTA
	extern	_BAUDCON
	extern	_WPUA
	extern	_ODCONA
	extern	_SLRCONA
	extern	_INLVLA
	extern	_IOCAP
	extern	_IOCAN
	extern	_IOCAF
	extern	_CWG1DBR
	extern	_CWG1DBF
	extern	_CWG1CON0
	extern	_CWG1CON1
	extern	_CWG1CON2
	extern	_PWMEN
	extern	_PWMLD
	extern	_PWMOUT
	extern	_PWM1PH
	extern	_PWM1PHL
	extern	_PWM1PHH
	extern	_PWM1DC
	extern	_PWM1DCL
	extern	_PWM1DCH
	extern	_PWM1PR
	extern	_PWM1PRL
	extern	_PWM1PRH
	extern	_PWM1OF
	extern	_PWM1OFL
	extern	_PWM1OFH
	extern	_PWM1TMR
	extern	_PWM1TMRL
	extern	_PWM1TMRH
	extern	_PWM1CON
	extern	_PWM1INTCON
	extern	_PWM1INTE
	extern	_PWM1INTF
	extern	_PWM1INTFLG
	extern	_PWM1CLKCON
	extern	_PWM1LDCON
	extern	_PWM1OFCON
	extern	_PWM2PH
	extern	_PWM2PHL
	extern	_PWM2PHH
	extern	_PWM2DC
	extern	_PWM2DCL
	extern	_PWM2DCH
	extern	_PWM2PR
	extern	_PWM2PRL
	extern	_PWM2PRH
	extern	_PWM2OF
	extern	_PWM2OFL
	extern	_PWM2OFH
	extern	_PWM2TMR
	extern	_PWM2TMRL
	extern	_PWM2TMRH
	extern	_PWM2CON
	extern	_PWM2INTE
	extern	_PWM2INTF
	extern	_PWM2CLKCON
	extern	_PWM2LDCON
	extern	_PWM2OFCON
	extern	_PWM3PH
	extern	_PWM3PHL
	extern	_PWM3PHH
	extern	_PWM3DC
	extern	_PWM3DCL
	extern	_PWM3DCH
	extern	_PWM3PR
	extern	_PWM3PRL
	extern	_PWM3PRH
	extern	_PWM3OF
	extern	_PWM3OFL
	extern	_PWM3OFH
	extern	_PWM3TMR
	extern	_PWM3TMRL
	extern	_PWM3TMRH
	extern	_PWM3CON
	extern	_PWM3INTE
	extern	_PWM3INTF
	extern	_PWM3CLKCON
	extern	_PWM3LDCON
	extern	_PWM3OFCON
	extern	_STATUS_SHAD
	extern	_WREG_SHAD
	extern	_BSR_SHAD
	extern	_PCLATH_SHAD
	extern	_FSR0L_SHAD
	extern	_FSR0_SHAD
	extern	_FSR0H_SHAD
	extern	_FSR1L_SHAD
	extern	_FSR1_SHAD
	extern	_FSR1H_SHAD
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_init
	global	_isr
	global	_main
	global	_result_width_h
	global	_result_width_l
	global	_resultier

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_main_0	udata
_resultier	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_main_0	udata
r0x1004	res	1
r0x1005	res	1
r0x1006	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_main_0	idata
_result_width_h
	db	0x00


ID_main_1	idata
_result_width_l
	db	0x00

;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code 0x0000
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; interrupt and initialization code
;--------------------------------------------------------
c_interrupt	code	0x4
__sdcc_interrupt
;***
;  pBlock Stats: dbName = I
;***
;entry:  _isr	;Function start
; 0 exit points
;; Starting pCode block
_isr	;Function start
; 0 exit points
;	.line	43; "main.c"	void isr (void) __interrupt (1){
	CLRF	PCLATH
;	.line	44; "main.c"	GIE = 0;
	BANKSEL	_INTCONbits
	BCF	_INTCONbits,7
;	.line	45; "main.c"	if(IOCIF){                // IOC?
	BTFSS	_INTCONbits,0
	GOTO	_00110_DS_
;	.line	46; "main.c"	result_width_h = TMR1H;
	MOVF	_TMR1H,W
	BANKSEL	_result_width_h
	MOVWF	_result_width_h
;	.line	47; "main.c"	result_width_l = TMR1L;
	BANKSEL	_TMR1L
	MOVF	_TMR1L,W
	BANKSEL	_result_width_l
	MOVWF	_result_width_l
;	.line	48; "main.c"	TMR1H          = 0;     // reset timer 1
	BANKSEL	_TMR1H
	CLRF	_TMR1H
;	.line	49; "main.c"	TMR1L          = 0;     // "
	CLRF	_TMR1L
_00110_DS_
;	.line	51; "main.c"	IOCAF = 0;
	BANKSEL	_IOCAF
	CLRF	_IOCAF
;	.line	52; "main.c"	GIE = 1;
	BANKSEL	_INTCONbits
	BSF	_INTCONbits,7
END_OF_INTERRUPT
	RETFIE	

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_main	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _init
;   _init
;4 compiler assigned registers:
;   r0x1004
;   r0x1005
;   r0x1006
;   r0x1007
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	56; "main.c"	init();
	CALL	_init
_00120_DS_
;	.line	60; "main.c"	resultier=result_width_h <<8 | result_width_l;
	BANKSEL	_result_width_h
	MOVF	_result_width_h,W
	BANKSEL	r0x1006
	MOVWF	r0x1006
	MOVWF	r0x1004
	CLRF	r0x1005
;;102	MOVF	r0x1004,W
;;99	CLRF	r0x1007
	BANKSEL	_result_width_l
	MOVF	_result_width_l,W
	BANKSEL	_resultier
	MOVWF	_resultier
	BANKSEL	r0x1004
	MOVWF	r0x1004
	CLRF	r0x1005
;;101	MOVF	r0x1004,W
;;100	IORWF	r0x1007,W
	MOVF	r0x1006,W
	BANKSEL	_resultier
	MOVWF	(_resultier + 1)
;;swapping arguments (AOP_TYPEs 1/3)
;;unsigned compare: left >= lit(0x1F5=501), size=2
;	.line	61; "main.c"	if (resultier > 500){
	MOVLW	0x01
	SUBWF	(_resultier + 1),W
	BTFSS	STATUS,2
	GOTO	_00133_DS_
	MOVLW	0xf5
	SUBWF	_resultier,W
_00133_DS_
	BTFSS	STATUS,0
	GOTO	_00120_DS_
;;genSkipc:3247: created from rifx:0xbf9d97d4
;;unsigned compare: left < lit(0x258=600), size=2
;	.line	62; "main.c"	if (resultier < 600){
	MOVLW	0x02
	BANKSEL	_resultier
	SUBWF	(_resultier + 1),W
	BTFSS	STATUS,2
	GOTO	_00134_DS_
	MOVLW	0x58
	SUBWF	_resultier,W
_00134_DS_
	BTFSC	STATUS,0
	GOTO	_00120_DS_
;;genSkipc:3247: created from rifx:0xbf9d97d4
;	.line	63; "main.c"	LATA5 =  1;// just debugging
	BANKSEL	_LATAbits
	BSF	_LATAbits,5
;	.line	64; "main.c"	LATA5 =  1;// just debugging
	BSF	_LATAbits,5
;	.line	65; "main.c"	LATA5 =  1;// just debugging
	BSF	_LATAbits,5
;	.line	66; "main.c"	LATA5 =  0;// just debugging
	BCF	_LATAbits,5
;	.line	67; "main.c"	result_width_h = 0;
	BANKSEL	_result_width_h
	CLRF	_result_width_h
;	.line	68; "main.c"	result_width_l = 0;
	BANKSEL	_result_width_l
	CLRF	_result_width_l
	GOTO	_00120_DS_
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
_init	;Function start
; 2 exit points
;	.line	12; "main.c"	INTCON  = 0;    // Clear interrupt flag bits
	BANKSEL	_INTCON
	CLRF	_INTCON
;	.line	13; "main.c"	GIE     = 1;    // Global irq enable
	BSF	_INTCONbits,7
;	.line	14; "main.c"	IOCIE   = 1;    // interrupt on change enable
	BSF	_INTCONbits,3
;	.line	15; "main.c"	IOCAN2  = 1;    // irq on negative edge (RA2/pin5)
	BANKSEL	_IOCANbits
	BSF	_IOCANbits,2
;	.line	16; "main.c"	IOCAP2  = 1;    // irq on positive edge (RA2/pin5)
	BSF	_IOCAPbits,2
;	.line	19; "main.c"	ANSELA  = 0;
	BANKSEL	_ANSELA
	CLRF	_ANSELA
;	.line	20; "main.c"	ADCON0  = 0;
	BANKSEL	_ADCON0
	CLRF	_ADCON0
;	.line	21; "main.c"	ADCON1  = 0;
	CLRF	_ADCON1
;	.line	22; "main.c"	ADCON2  = 0;
	CLRF	_ADCON2
;	.line	23; "main.c"	CM1CON0 = 0;
	BANKSEL	_CM1CON0
	CLRF	_CM1CON0
;	.line	24; "main.c"	CM1CON1 = 0;
	CLRF	_CM1CON1
;	.line	26; "main.c"	IRCF3   = 1;    // rc osc 8MHz
	BANKSEL	_OSCCONbits
	BSF	_OSCCONbits,6
;	.line	27; "main.c"	IRCF2   = 1;    // "
	BSF	_OSCCONbits,5
;	.line	28; "main.c"	IRCF1   = 1;    // "
	BSF	_OSCCONbits,4
;	.line	29; "main.c"	IRCF0   = 0;    // "
	BCF	_OSCCONbits,3
;	.line	31; "main.c"	TRISA5  = 0;    // output for red led     - pin2
	BCF	_TRISAbits,5
;	.line	32; "main.c"	TRISA2  = 1;    // input  for ir receiver - pin5
	BSF	_TRISAbits,2
;	.line	34; "main.c"	TMR1CS0 = 0;    // timer 1 use internal clock
	BANKSEL	_T1CONbits
	BCF	_T1CONbits,6
;	.line	35; "main.c"	TMR1CS1 = 0;    // "
	BCF	_T1CONbits,7
;	.line	37; "main.c"	T1CKPS0 = 1;    // prescaler 1:8
	BSF	_T1CONbits,4
;	.line	38; "main.c"	T1CKPS1 = 1;    // "
	BSF	_T1CONbits,5
;	.line	40; "main.c"	TMR1ON  = 1;    // start to count
	BSF	_T1CONbits,0
	RETURN	
; exit point of _init


;	code size estimation:
;	   71+   24 =    95 instructions (  238 byte)

	end
