#include <intrins.h>
#include "mfrc522.h"
#include <string.h> 
#include "OLED.h"

#define MAXRLEN 18

  

/////////////////////////////////////////////////////////////////////
//	PCD Request
/////////////////////////////////////////////////////////////////////
char PcdRequest(unsigned char req_code,unsigned char *pTagType){
   char status;  
   unsigned int  unLen;
   unsigned char ucComMF522Buf[MAXRLEN]; 
   ClearBitMask(Status2Reg,0x08);
   WriteRawRC(BitFramingReg,0x07);
   SetBitMask(TxControlReg,0x03);
   ucComMF522Buf[0] = req_code;
   status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
   if ((status == MI_OK) && (unLen == 0x10)){    
       *pTagType     = ucComMF522Buf[0];
       *(pTagType+1) = ucComMF522Buf[1];
   }
   else{
		status = MI_ERR;   
	 }   
   return status;
}

/////////////////////////////////////////////////////////////////////
//	PCD Anti Collision
/////////////////////////////////////////////////////////////////////  
char PcdAnticoll(unsigned char *pSnr){
    char status;
    unsigned char i,snr_check=0;
    unsigned int  unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);
    if (status == MI_OK){
    	 for (i=0; i<4; i++){   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];
       }
       if (snr_check != ucComMF522Buf[i]){
				status = MI_ERR;
			 }
    }    
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//  PCD RESET
/////////////////////////////////////////////////////////////////////
char PcdReset(void){
    MF522_RST=1;
    _nop_();
    MF522_RST=0;
    _nop_();
    MF522_RST=1;
     _nop_();
    WriteRawRC(CommandReg,PCD_RESETPHASE);
    _nop_();
    WriteRawRC(ModeReg,0x3D);            
    WriteRawRC(TReloadRegL,30);           
    WriteRawRC(TReloadRegH,0);
    WriteRawRC(TModeReg,0x8D);
    WriteRawRC(TPrescalerReg,0x3E);
    WriteRawRC(TxAutoReg,0x40);     
    return MI_OK;
}
//////////////////////////////////////////////////////////////////////
//	PCD ISO Type
//////////////////////////////////////////////////////////////////////
char M500PcdConfigISOType(unsigned char type){
   if (type == 'A'){                     //ISO14443_A 
       ClearBitMask(Status2Reg,0x08);
       WriteRawRC(ModeReg,0x3D);
       WriteRawRC(RxSelReg,0x86);
       WriteRawRC(RFCfgReg,0x7F);   
   	   WriteRawRC(TReloadRegL,30);
			 WriteRawRC(TReloadRegH,0);
       WriteRawRC(TModeReg,0x8D);
	     WriteRawRC(TPrescalerReg,0x3E);
	      
		 delay_10ms(1);
     		 //OLED_Clear();
		 PcdAntennaOn();
		 		//OLED_Clear();

   }
   else{
		return -1; 
	 }
   return MI_OK;
}
////////////////////////////////////////////////////////////////////////////
//   This function is an SPI driver Used to Read the data from MFRC522    //
////////////////////////////////////////////////////////////////////////////
unsigned char ReadRawRC(unsigned char Address){
     unsigned char i, ucAddr;
     unsigned char ucResult=0;
     MF522_SCK = 1;
     MF522_NSS = 0;
     ucAddr = ((Address<<1)&0x7E)|0x80;
		 for(i=8;i>0;i--){
         MF522_SI = ((ucAddr&0x80)==0x80);
         MF522_SCK = 0;
         ucAddr <<= 1;
         MF522_SCK = 1;
     }
     for(i=8;i>0;i--){
         MF522_SCK = 0;
         ucResult <<= 1;
         ucResult|=(bit)MF522_SO;
         MF522_SCK = 1;
     }
    MF522_NSS = 1;
    return ucResult;
} 

////////////////////////////////////////////////////////////////////////////
//   This function is an SPI driver Used to Write the data to MFRC522     //
////////////////////////////////////////////////////////////////////////////
void WriteRawRC(unsigned char Address, unsigned char value){  
    unsigned char i, ucAddr;
    MF522_SCK = 1;
    MF522_NSS = 0;
    ucAddr = ((Address<<1)&0x7E);
    for(i=8;i>0;i--){
        MF522_SI = ((ucAddr&0x80)==0x80);
        MF522_SCK = 0;
        ucAddr <<= 1;
        MF522_SCK = 1;
    }
    for(i=8;i>0;i--){
        MF522_SI = ((value&0x80)==0x80);
        MF522_SCK = 0;
        value <<= 1;
        MF522_SCK = 1;
    }
    MF522_NSS = 1;
}

/////////////////////////////////////////////////////////////////////
//		Used to Set the Bit Mask 																		 //
/////////////////////////////////////////////////////////////////////
void SetBitMask(unsigned char reg,unsigned char mask){
    char tmp = 0x00;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}

/////////////////////////////////////////////////////////////////////
//	Used to Clear Bit Mask																				 //
/////////////////////////////////////////////////////////////////////
void ClearBitMask(unsigned char reg,unsigned char mask){
    char tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
}

/////////////////////////////////////////////////////////////////////
//	PCD Communication With MFRC522
/////////////////////////////////////////////////////////////////////
char PcdComMF522( unsigned char Command,
                  unsigned char *pInData,
                  unsigned char InLenByte,
                  unsigned char *pOutData,
                  unsigned int  *pOutLenBit )
{
    char status = MI_ERR;
    unsigned char irqEn   = 0x00;
    unsigned char waitFor = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;
    switch (Command){
       case PCD_AUTHENT:
          irqEn   = 0x12;
          waitFor = 0x10;
          break;
       case PCD_TRANSCEIVE:
          irqEn   = 0x77;
          waitFor = 0x30;
          break;
       default:
         break;
    }
    WriteRawRC(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<InLenByte; i++){
			WriteRawRC(FIFODataReg, pInData[i]);    
		}
    WriteRawRC(CommandReg, Command);
    if (Command == PCD_TRANSCEIVE){
			SetBitMask(BitFramingReg,0x80);
		}
    i = 2000;
    do{
			n = ReadRawRC(ComIrqReg);
      i--;
    }while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);
    if (i!=0){    
         if(!(ReadRawRC(ErrorReg)&0x1B)){
             status = MI_OK;
             if (n & irqEn & 0x01){
							status = MI_NOTAGERR;
						 }
             if (Command == PCD_TRANSCEIVE){
               	n = ReadRawRC(FIFOLevelReg);
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits){
					*pOutLenBit = (n-1)*8 + lastBits;
				}
                else{
					*pOutLenBit = n*8;
				}
                if (n == 0){
					n = 1;
				}
                if (n > MAXRLEN){
					n = MAXRLEN;
				}
                for (i=0; i<n; i++){
					pOutData[i] = ReadRawRC(FIFODataReg);
				}
			}
         }
         else{
			status = MI_ERR;
		 }       
   }
   SetBitMask(ControlReg,0x80);           // stop timer now
   WriteRawRC(CommandReg,PCD_IDLE); 
   return status;
}
/////////////////////////////////////////////////////////////////////
//	PCD Antenna ON
/////////////////////////////////////////////////////////////////////
void PcdAntennaOn(){
    unsigned char i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03)){
        SetBitMask(TxControlReg, 0x03);
    }
}
/////////////////////////////////////////////////////////////////////
// PCD Antenna OFF
/////////////////////////////////////////////////////////////////////
void PcdAntennaOff(){
    ClearBitMask(TxControlReg, 0x03);
}

///////////////////////////////////////////////////////////////////////
// Delay 10ms
///////////////////////////////////////////////////////////////////////

void delay_10ms(unsigned int _10ms){
#ifndef NO_TIMER2
    RCAP2LH = RCAP2_10ms;
    T2LH    = RCAP2_10ms;
    TR2 = TRUE;
    while (_10ms--){
	    while (!TF2);
	    TF2 = FALSE;
    }
    TR2 = FALSE;
#else
    while (_10ms--){
	    delay_50us(19);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid )
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(20);
	    if (CmdValid)
	        return;
	    delay_50us(19);
	    if (CmdValid)
	        return;
    }
#endif
}