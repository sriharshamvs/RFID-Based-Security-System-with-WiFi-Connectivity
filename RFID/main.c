#include "reg52.h"
#include "main.h"
#include "mfrc522.h"
#include <string.h>

unsigned char UID[5],Temp[4];

void FeedBackDelay(void);
void InitializeSystem(void);
void ReadCard(void);
void SERIAL_TRANSMIT(unsigned char c);
void SERIAL_STRING_TX(unsigned char *tx_String);
void SERIAL_STRING_TX_LN(unsigned char *tx_String);
void HEXtoBYTE(unsigned char c);

void main(void){   
	InitializeSystem();
	SERIAL_STRING_TX_LN("Serial Initilized");
	ReadCard();
}

void FeedBackDelay(void){
	feedBack=0;
	delay_10ms(1);
	feedBack=1;
	delay_10ms(1);
}

void ReadCard(void){
  unsigned char tempUID[5]=0,i=0,flag=0;
	unsigned int length=0;
	while(1){
    if(PcdRequest(0x52,Temp)==MI_OK){
      if(PcdAnticoll(tempUID)==MI_OK){
				tempUID[4] = '\0';
				//length = strlen(UID);
				//strcpy(UID,tempUID);
				//SERIAL_STRING_TX(tempUID[i] < 0x10 ? "0" : "");
				for(i=0;i<4;i++){
					HEXtoBYTE(tempUID[i]);
				}
				FeedBackDelay();                   
      }
    }
  } 
}

void InitializeSystem(){
  TMOD&=0xCF; 
	TMOD|=0x20; 
	TH1=0xFA;   // setting buadrate to 9600 bps
	TL1=0x00;
	TR1=1;
	SCON=0x50;
	EA=1;
	ES = 1;
    PcdReset();
    PcdAntennaOff(); 
    PcdAntennaOn();  
	P0=0;
	M500PcdConfigISOType( 'A' );
}

void SERIAL_TRANSMIT(unsigned char tx_char){  // For sending each character
	SBUF=tx_char;  //Store the incoming character in SUBF
	while(TI==0);  // Wait until Tx bit is High
	TI=0;   // Make it 0 once it's high
}

void SERIAL_STRING_TX(unsigned char *tx_String){   // For sending a String
	unsigned int i,stringSize;
	unsigned char temp_char=0;
	
	stringSize = strlen(tx_String); // Calculate the String length
	for(i=0;i<stringSize;i++){
		temp_char = tx_String[i];  
		SERIAL_TRANSMIT(temp_char);  // Send each character to the SERIAL_TRANSMIT function
	}
}

void SERIAL_STRING_TX_LN(unsigned char *tx_String){   // For sending a String
	unsigned int i,stringSize;
	unsigned char temp_char=0;
	
	stringSize = strlen(tx_String); // Calculate the String length
	for(i=0;i<stringSize;i++){
		temp_char = tx_String[i];  
		SERIAL_TRANSMIT(temp_char);  // Send each character to the SERIAL_TRANSMIT function
	}
	SERIAL_TRANSMIT('\r');
	SERIAL_TRANSMIT('\n');
}

/*
void isr_UART(void) interrupt 4 using 1{
  unsigned char i;
	if(TI){
		TI=0;
		for(i=0;i<4;i++){
			SBUF=UID[i];
			while(!TI);
			TI=0;			
		}
	  REN=1;
	}
} 
*/

void HEXtoBYTE(unsigned char c){
	unsigned char t;
	t=c>>4;
	t=t+'0';
	if (t>=(10+'0')){
		t=t+('A'-10-'0');
	}
	SERIAL_TRANSMIT(t); // call to your function here
	t=c&0x0F;
	t=t+'0';
	if (t>=(10+'0')){
		t=t+('A'-10-'0');
	}
SERIAL_TRANSMIT(t); // call to your function here

} 