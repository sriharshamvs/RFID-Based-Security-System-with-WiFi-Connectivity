#include <MPCx58AP.h>
#include "SERIAL.h"
#include "string.h"

unsigned int count=0;

/*void SERIAL_INIT(void){
	TMOD&=0xCF; 
	TMOD|=0x20; 
	TH1=0xFA;   // setting buadrate to 9600 bps
	TL1=0x00;
	TR1=1;
	SCON=0x50;
	EA=1;
	ES = 1;
}*/

void SERIAL_INIT(void){
	SCON=0x50;
	PCON |=0X80;
	TMOD&=0xCF; 
	TMOD|=0x20; 
	TH1=0xFF;   // setting buadrate to 115200 bps
	TL1=0x00;
	TR1=1;
	REN=1;
	ES = 1;
} // SERIAL_INIT ends here

void TIMER_INIT(void){
	TMOD=0x00;
	IE=0x00;
	TR0=0;
	TF0=0;
	TMOD|=0x01;
	IE|=0x82;
	TH0=0xF8;   // setting 1ms timer
	TL0=0xCD;
	TR0=1;
} // TIMER_INIT ends here

  // interrupt 1 ends here

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
