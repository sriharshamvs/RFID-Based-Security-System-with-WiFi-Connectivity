/*--------------------------------------------------------------------------
MPCx58AP.H

Header file for the low voltage Flash MegaWin MPC89E58A	QFP Packages
with P4 Port Definitions
Copyright (c) 2006 NGE Service & Consultancy. All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __MPCx58AP_H__
#define __MPCx58AP_H__

/*------------------------------------------------
Byte Registers
------------------------------------------------*/
sfr P0      = 0x80;
sfr SP      = 0x81;
sfr DPL     = 0x82;
sfr DPH     = 0x83;
sfr SPISTAT	= 0x84;
sfr SPICTL	= 0x85;
sfr SPIDAT	= 0x86;
sfr PCON    = 0x87;
sfr TCON    = 0x88;
sfr TMOD    = 0x89;
sfr TL0     = 0x8A;
sfr TL1     = 0x8B;
sfr TH0     = 0x8C;
sfr TH1     = 0x8D;
sfr AUXR		= 0x8E;
sfr STRETCH	= 0x8F;
sfr P1      = 0x90;
sfr P1M0		= 0x91;
sfr P1M1		= 0x92;
sfr P0M0		= 0x93;
sfr P0M1		= 0x94;
sfr P2M0		= 0x95;
sfr P2M1		= 0x96;
sfr EVRCR	= 0x97;
sfr SCON    = 0x98;
sfr SBUF    = 0x99;
sfr S2BUF	= 0x9A;
sfr P2      = 0xA0;
sfr AUXR1	= 0xA2;
sfr AUXTC1	= 0xA6;
sfr TSTWD	= 0xA7;
sfr IE      = 0xA8;
sfr SADDR	= 0xA9;
sfr P3      = 0xB0;
sfr P3M0		= 0xB1;
sfr P3M1		= 0xB2;
sfr P4M0		= 0xB3;
sfr P4M1		= 0xB4;
sfr IPH		= 0xB7;
sfr IP      = 0xB8;
sfr SADEN	= 0xB9;
sfr S2BRT	= 0xBA;
sfr ADCVL	= 0xBE;
sfr XICON	= 0xC0;
sfr ADCTL	= 0xC5;
sfr ADCV		= 0xC6;
sfr T2CON   = 0xC8;
sfr T2MOD   = 0xC9;
//sfr RCAP2L  = 0xCA;
sfr   RCAP2LH =   0xCA;
sfr   T2LH    =   0xCC;
sfr RCAP2H  = 0xCB;
//sfr TL2     = 0xCC;
sfr TH2     = 0xCD;
sfr SVAR		= 0xCE;
sfr SBK		= 0xCF;
sfr PSW     = 0xD0;
sfr KBPATN	= 0xD5;
sfr KBCON	= 0xD6;
sfr KBMASK	= 0xD7;
sfr CCON		= 0xD8;
sfr CMOD		= 0xD9;
sfr CCAPM0	= 0xDA;
sfr CCAPM1	= 0xDB;
sfr CCAPM2	= 0xDC;
sfr CCAPM3	= 0xDD;
sfr CCAPM4	= 0xDE;
sfr CCAPM5	= 0xDF;

sfr ACC     = 0xE0;	// Accumulator

sfr WDTCR	= 0xE1;	// WDT Control Register

sfr IFD		= 0xE2;	// ISP Flash Data
sfr IFADRH	= 0xE3;	// ISP Flash Address HIGH
sfr IFADRL	= 0xE4;	// ISP Flash Address LOW
sfr IFMT		= 0xE5;	// ISP Mode Table
sfr SCMD		= 0xE6;	// ISP Serial Command
sfr ISPCR	= 0xE7;	// ISP Control Register

sfr P4		= 0xE8;	// Port 4

sfr CL		= 0xE9;	// PCA Base Timer LOW

sfr CCAP0L	= 0xEA;	// PCA Module 0 Capture Register Low
sfr CCAP1L	= 0xEB;	// PCA Module 1 Capture Register Low
sfr CCAP2L	= 0xEC;	// PCA Module 2 Capture Register Low
sfr CCAP3L	= 0xED;	// PCA Module 3 Capture Register Low
sfr CCAP4L	= 0xEE;	// PCA Module 4 Capture Register Low
sfr CCAP5L	= 0xEF;	// PCA Module 5 Capture Register Low

sfr B       = 0xF0;	// B Register

sfr PCAPWM0	= 0xF2;	// PCA PWM mode auxiliary register 0
sfr PCAPWM1	= 0xF3;	// PCA PWM mode auxiliary register 1
sfr PCAPWM2	= 0xF4;	// PCA PWM mode auxiliary register 2
sfr PCAPWM3	= 0xF5;	// PCA PWM mode auxiliary register 3
sfr PCAPWM4	= 0xF6;	// PCA PWM mode auxiliary register 4
sfr PCAPWM5	= 0xF7;	// PCA PWM mode auxiliary register 5

sfr CH		= 0xF9;	// PCA Base Timer High

sfr CCAP0H	= 0xFA;	// PCA Module 0 Capture Register High
sfr CCAP1H	= 0xFB;	// PCA Module 1 Capture Register High
sfr CCAP2H	= 0xFC;	// PCA Module 2 Capture Register High
sfr CCAP3H	= 0xFE;	// PCA Module 3 Capture Register High
sfr CCAP4H	= 0xFE;	// PCA Module 4 Capture Register High
sfr CCAP5H	= 0xFF;	// PCA Module 5 Capture Register High

/*------------------------------------------------
P0 Bit Registers
------------------------------------------------*/
sbit P0_0 = 0x80;
sbit P0_1 = 0x81;
sbit P0_2 = 0x82;
sbit P0_3 = 0x83;
sbit P0_4 = 0x84;
sbit P0_5 = 0x85;
sbit P0_6 = 0x86;
sbit P0_7 = 0x87;

/*------------------------------------------------
SPISTAT Bit Registers
------------------------------------------------*/
sbit SPISTAT_0	= 0x84;
sbit SPISTAT_1	= 0x85;
sbit SPISTAT_2	= 0x86;
sbit SPISTAT_3	= 0x87;
sbit SPISTAT_4	= 0x88;
sbit SPISTAT_5	= 0x89;
sbit WCOL 		= 0x8A;
sbit SPIF 		= 0x8B;

/*------------------------------------------------
SPICTL Bit Registers
------------------------------------------------*/
sbit SPR0 		= 0x85;
sbit SPR1 		= 0x86;
sbit CPHA 		= 0x87;
sbit CPOL		= 0x88;
sbit MSTR		= 0x89;
sbit DORD		= 0x8A;
sbit SPEN		= 0x8B;
sbit SSIG		= 0x8C;

/*------------------------------------------------
PCON Bit Values
------------------------------------------------*/
#define IDL_    0x01

#define STOP_   0x02
#define PD_     0x02    /* Alternate definition */

#define GF0_    0x04
#define GF1_    0x08
#define SMOD_   0x80

/*------------------------------------------------
TCON Bit Registers
------------------------------------------------*/
sbit IT0  = 0x88;
sbit IE0  = 0x89;
sbit IT1  = 0x8A;
sbit IE1  = 0x8B;
sbit TR0  = 0x8C;
sbit TF0  = 0x8D;
sbit TR1  = 0x8E;
sbit TF1  = 0x8F;

/*------------------------------------------------
TMOD Bit Values
------------------------------------------------*/
#define T0_M0_   0x01
#define T0_M1_   0x02
#define T0_CT_   0x04
#define T0_GATE_ 0x08
#define T1_M0_   0x10
#define T1_M1_   0x20
#define  T1_CT_   0x40
#define T1_GATE_ 0x80

#define T1_MASK_ 0xF0
#define T0_MASK_ 0x0F

/*------------------------------------------------
P1 Bit Registers
------------------------------------------------*/
sbit P1_0 = 0x90;
sbit P1_1 = 0x91;
sbit P1_2 = 0x92;
sbit P1_3 = 0x93;
sbit P1_4 = 0x94;
sbit P1_5 = 0x95;
sbit P1_6 = 0x96;
sbit P1_7 = 0x97;

sbit T2   = 0x90;       /* External input to Timer/Counter 2, clock out */
sbit T2EX = 0x91;       /* Timer/Counter 2 capture/reload trigger & dir ctl */

/*------------------------------------------------
SCON Bit Registers
------------------------------------------------*/
sbit RI   = 0x98;
sbit TI   = 0x99;
sbit RB8  = 0x9A;
sbit TB8  = 0x9B;
sbit REN  = 0x9C;
sbit SM2  = 0x9D;
sbit SM1  = 0x9E;
sbit SM0  = 0x9F;

/*------------------------------------------------
P2 Bit Registers
------------------------------------------------*/
sbit P2_0 = 0xA0;
sbit P2_1 = 0xA1;
sbit P2_2 = 0xA2;
sbit P2_3 = 0xA3;
sbit P2_4 = 0xA4;
sbit P2_5 = 0xA5;
sbit P2_6 = 0xA6;
sbit P2_7 = 0xA7;

/*------------------------------------------------
IE Bit Registers
------------------------------------------------*/
sbit EX0  = 0xA8;       /* 1=Enable External interrupt 0 */
sbit ET0  = 0xA9;       /* 1=Enable Timer 0 interrupt */
sbit EX1  = 0xAA;       /* 1=Enable External interrupt 1 */
sbit ET1  = 0xAB;       /* 1=Enable Timer 1 interrupt */
sbit ES   = 0xAC;       /* 1=Enable Serial port interrupt */
sbit ET2  = 0xAD;       /* 1=Enable Timer 2 interrupt */

sbit EA   = 0xAF;       /* 0=Disable all interrupts */

/*------------------------------------------------
P3 Bit Registers (Mnemonics & Ports)
------------------------------------------------*/
sbit P3_0 = 0xB0;
sbit P3_1 = 0xB1;
sbit P3_2 = 0xB2;
sbit P3_3 = 0xB3;
sbit P3_4 = 0xB4;
sbit P3_5 = 0xB5;
sbit P3_6 = 0xB6;
sbit P3_7 = 0xB7;

sbit RXD  = 0xB0;       /* Serial data input */
sbit TXD  = 0xB1;       /* Serial data output */
sbit INT0 = 0xB2;       /* External interrupt 0 */
sbit INT1 = 0xB3;       /* External interrupt 1 */
sbit T0   = 0xB4;       /* Timer 0 external input */
sbit T1   = 0xB5;       /* Timer 1 external input */
sbit WR   = 0xB6;       /* External data memory write strobe */
sbit RD   = 0xB7;       /* External data memory read strobe */

/*------------------------------------------------
IP Bit Registers
------------------------------------------------*/
sbit PX0  = 0xB8;
sbit PT0  = 0xB9;
sbit PX1  = 0xBA;
sbit PT1  = 0xBB;
sbit PS   = 0xBC;
sbit PT2  = 0xBD;

/*------------------------------------------------
XICON Bit Registers
------------------------------------------------*/
sbit IT2  = 0xC0;
sbit IE2  = 0xC1;
sbit EX2  = 0xC2;
sbit PX2  = 0xC3;
sbit IT3  = 0xC4;
sbit IE3  = 0xC5;
sbit EX3  = 0xC6;
sbit PX3  = 0xC7;

/*------------------------------------------------
T2CON Bit Registers
------------------------------------------------*/
sbit CP_RL2= 0xC8;      /* 0=Reload, 1=Capture select */
sbit C_T2 = 0xC9;       /* 0=Timer, 1=Counter */
sbit TR2  = 0xCA;       /* 0=Stop timer, 1=Start timer */
sbit EXEN2= 0xCB;       /* Timer 2 external enable */
sbit TCLK = 0xCC;       /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
sbit RCLK = 0xCD;       /* 0=Serial clock uses Timer 1 overflow, 1=Timer 2 */
sbit EXF2 = 0xCE;       /* Timer 2 external flag */
sbit TF2  = 0xCF;       /* Timer 2 overflow flag */

/*------------------------------------------------
T2MOD Bit Values
------------------------------------------------*/
#define DCEN_   0x01    /* 1=Timer 2 can be configured as up/down counter */
#define T2OE_   0x02    /* Timer 2 output enable */

/*------------------------------------------------
PSW Bit Registers
------------------------------------------------*/
sbit P    = 0xD0;
sbit FL   = 0xD1;
sbit OV   = 0xD2;
sbit RS0  = 0xD3;
sbit RS1  = 0xD4;
sbit F0   = 0xD5;
sbit AC   = 0xD6;
sbit CY   = 0xD7;

/*------------------------------------------------
P3 Bit Registers (Mnemonics & Ports)
------------------------------------------------*/
sbit P4_0 = P4^0;
sbit P4_1 = P4^1;
sbit P4_2 = P4^2;
sbit P4_3 = P4^3;
sbit P4_4 = P4^4;
sbit P4_5 = P4^5;
sbit P4_6 = P4^6;
sbit P4_7 = P4^7;

/*------------------------------------------------
Interrupt Vectors:
Interrupt Address = (Number * 8) + 3
------------------------------------------------*/
#define IE0_VECTOR	0  /* 0x03 External Interrupt 0 */
#define TF0_VECTOR	1  /* 0x0B Timer 0 */
#define IE1_VECTOR	2  /* 0x13 External Interrupt 1 */
#define TF1_VECTOR	3  /* 0x1B Timer 1 */
#define SIO_VECTOR	4  /* 0x23 Serial port */

#define TF2_VECTOR	5  /* 0x2B Timer 2 */
#define EX2_VECTOR	5  /* 0x2B External Interrupt 2 */

#define IE2_VECTOR	6  /* 0x33 External Interrupt 2 */
#define IE3_VECTOR	7  /* 0x3B External Interrupt 3 */

#endif

