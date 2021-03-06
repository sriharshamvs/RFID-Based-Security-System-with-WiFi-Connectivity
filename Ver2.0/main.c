#include "MPCx58AP.h"
#include "mfrc522.h"
#include "SERIAL.h"
#include "OLED.h"
#include <string.h>

#define RXBUFFSIZE	20
#define RXBUFFSIZE	20
#define WiFiReset 	P3_2

#define RELAY		P2_7
#define HIGH 		1
#define LOW 		0

void InitializeSystem(void);  
void FeedBackDelay(void);
void InitializeSystem(void);
void ReadCard(void);
void HEXtoBYTE(unsigned char c);
void delayPCD(void);

void DELAY_1(unsigned int delayCount);
void CONNECT_TO_WIFI(unsigned char* , unsigned char*);
void SendDatatToCloud(unsigned char *uploadData);
void WiFiInit(void);
void Comparecard();

bit powerON=0;
bit exit = 0;
bit readyFLAG=0;
bit processFLAG=0;
bit TwoSecFLAG=0;

unsigned char Temp[4],UID2[4]= 0,UID1[4],UID3[4];
static unsigned char HEXcount=0;

static unsigned char rxBytes=0;
static unsigned int TimerCount=0;
unsigned char Response[20];
const char* SSID = "Startrek";
const char* PWD = "Face fade12#";
unsigned char RECIEVEbuffer[RXBUFFSIZE+1];
unsigned char workingBUFFER[RXBUFFSIZE];
unsigned char ipBuffer[20]=0;
unsigned char step=0;
unsigned char MATCHED=0;
unsigned char MEMBER=0;

char status=0;

const char READY_CONDITION[] =  {"ready"};
const char OK[] = {"OK"};
const char CIFSR_STAIP[] = {"+CIFSR:STAIP,"};

unsigned char UploadDataToCloud[]={"GET /update?key=RJ4ZCZX8AV7V1XRL&field1="};

unsigned char CARD1[4]={0x74,0xBE,0xF2,0x66};
unsigned char CARD2[4]={0xB7,0xE5,0xDC,0xE1};	
unsigned char CARD3[4]={0x37,0x84,0xF1,0xE1};
unsigned char CARD4[4]={0x07,0xAB,0xAF,0xBF};
unsigned char tempUID[4]=0;

void main(void){  
  unsigned char forcount=0;
  P0=0x00;
	P1=0x00;
	P2=0x00;
	UID2[0] = 1;  		// to make UDI1[0] not equal 
	InitializeSystem();
	OLED_Clear();
	OLED_SetCursor(1,0);  //Set cursor at 1st-line 0th-Position
  OLED_DisplayString("Place Card       ");	
	OLED_SetCursor(2,0);
	OLED_DisplayString("Door Closed   ");
	while(1){
		ReadCard();	
		Comparecard();		
		for(forcount=0;forcount<4;forcount++) {
			UID3[forcount]=UID1[forcount];
		}
	}
} // main closes here
		
void InitializeSystem(void){
	TIMER_INIT();		// Initializing Timer
	SERIAL_INIT();  // Initializing UART
	SERIAL_STRING_TX("Jai Sri RAM");
	OLED_Init();
	OLED_SetCursor(1,0);  //Set cursor at 1st-line 0th-Position
  OLED_DisplayString("System Initializing");
	OLED_SetCursor(2,0);  //Set cursor at 1st-line 0th-Position
  OLED_DisplayString("Serial Initialized");
	powerON=0;
	DELAY_1(2000);
	SERIAL_STRING_TX("AT+RST");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	WiFiInit();
	DELAY_1(100);
	PcdReset();
	PcdAntennaOff();
	PcdAntennaOn();  
	M500PcdConfigISOType( 'A' );
	OLED_SetCursor(4,0);  //Set cursor at 1st-line 0th-Position
	OLED_DisplayString("PCD Initialized");
	DELAY_1(1000);
}

void FeedBackDelay(void){
	feedBack=0;
	delay_10ms(1);
	feedBack=1;
	delay_10ms(1);
}

void ReadCard(void){
  unsigned char i=0,flag=0;
	unsigned int length=0;
  if(PcdRequest(0x52,Temp)==MI_OK){
		if(PcdAnticoll(UID1)==MI_OK){
			HEXcount=0;
			for(i=0;i<4;i++){
				HEXtoBYTE(UID1[i]);
			}
			/*OLED_SetCursor(5,0);  //Set cursor at 1st-line 0th-Position
			for(i=0;i<8;i++){
				OLED_DisplayChar(UID2[i]);
			}*/
		}
  }
	rxBytes=0;	
	DELAY_1(100);
	DELAY_1(100);
}

void Comparecard(void){  
		if(UID1[0]==CARD1[0] && UID1[1]==CARD1[1] && UID1[2]==CARD1[2] && UID1[3]==CARD1[3]){
		MATCHED=1;
		MEMBER=1;			// 74BEF266
		RELAY = HIGH ;
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Opened");
		OLED_SetCursor(4,0);
		OLED_DisplayString("MEMBER = 1");
		OLED_SetCursor(6,0);
		OLED_DisplayString("Uploading Data     ");
		DELAY_1(100);
		DELAY_1(100);
		SendDatatToCloud("GET /update?key=RJ4ZCZX8AV7V1XRL&field1=100");
		DELAY_1(100);
		RELAY = LOW;
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Closed");
		
	}
	if(UID1[0]==CARD2[0]&& UID1[1]==CARD2[1]&&UID1[2]==CARD2[2]&&UID1[3]==CARD2[3]){
		MATCHED=1;
		MEMBER=2;  //B7E5DCE1
		RELAY = HIGH ;
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Opened");
		OLED_SetCursor(4,0);
		OLED_DisplayString("MEMBER = 2");
		OLED_SetCursor(6,0);
		OLED_DisplayString("Uploading Data     ");
		DELAY_1(100);
		DELAY_1(100);
		SendDatatToCloud("GET /update?key=RJ4ZCZX8AV7V1XRL&field1=200");
		DELAY_1(100);
		RELAY = LOW;
		DELAY_1(100);
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Closed");
	}
  
  if(UID1[0]==CARD4[0] && UID1[1]==CARD4[1] && UID1[2]==CARD4[2] && UID1[3]==CARD4[3]){
		MATCHED=1;
		MEMBER=1;			// 74BEF266
		RELAY = HIGH ;
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Opened");
		OLED_SetCursor(4,0);
		OLED_DisplayString("MEMBER = 4");
		OLED_SetCursor(6,0);
		OLED_DisplayString("Uploading Data     ");
		DELAY_1(100);
		DELAY_1(100);
		SendDatatToCloud("GET /update?key=RJ4ZCZX8AV7V1XRL&field1=400");
		DELAY_1(100);
		RELAY = LOW;
		OLED_SetCursor(2,0);
		OLED_DisplayString("Door Closed");		
	}	

	UID1[0]=0;
	MEMBER =  0;
	MATCHED = 0;
}

void delayPCD(void){
	unsigned int i=0;
	for (i=0;i<65000;i++);
	for (i=0;i<65000;i++);
}

void HEXtoBYTE(unsigned char c){
	unsigned char t;
	static unsigned char HEXindex=0;
	if(HEXcount<4){	
		t=c>>4;
		t=t+'0';
		if (t>=(10+'0')){
		t=t+('A'-10-'0');
	}
	
	UID2[HEXindex]=t;
	//SERIAL_TRANSMIT(t); // call to your function here
	HEXindex++;
	t=c&0x0F;
	t=t+'0';
	if (t>=(10+'0')){
		t=t+('A'-10-'0');
	}
	//SERIAL_TRANSMIT(t); // call to your function here
	UID2[HEXindex]=t;
	HEXcount++;
	HEXindex++;
}
	if(HEXcount>=4){
		HEXindex=0;
	}
}

void CONNECT_TO_WIFI(unsigned char* SSID, unsigned char* PWD){
	//unsigned char temp_ssid_char,temp_pwd_char;
	//unsigned int index=0,count=0,j=0,i=0;	
	unsigned int i=0,SSID_Length, PWD_Length,j=0;
	bit status=0;
	bit ipBIT=0;
	OLED_Clear();
	SSID_Length = strlen(SSID);
	PWD_Length = strlen(PWD);
	
	/*SERIAL_STRING_TX("AT+CWJAP=");
	SERIAL_TRANSMIT('"');
	for(i=0;i<SSID_Length;i++){
		temp_ssid_char = SSID[i];
		SERIAL_TRANSMIT(temp_ssid_char);
	}
	SERIAL_TRANSMIT('"');
	SERIAL_TRANSMIT(',');
	SERIAL_TRANSMIT('"');
	for(i=0;i<PWD_Length;i++){
		temp_pwd_char = PWD[i];
		SERIAL_TRANSMIT(temp_pwd_char);
	}
	SERIAL_TRANSMIT('"');
	*/
	
	SERIAL_STRING_TX("AT");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	
	OLED_SetCursor(2,0);  //Set cursor at 1st-line 0th-Position	
	OLED_DisplayString("Connecting......");
	DELAY_1(1000);
	
	SERIAL_STRING_TX("AT+CWJAP=\"Startrek\",\"Face fade12#\""); //this can also be used.
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	DELAY_1(2000);
	
	//while(TwoSecFLAG!=1);
	SERIAL_STRING_TX("AT+CIFSR");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);	
	DELAY_1(100);	
	
	OLED_SetCursor(3,0);  //Set cursor at 1st-line 0th-Position	
	OLED_DisplayString("Connected to WiFi");
	DELAY_1(2000);
	OLED_SetCursor(4,0);  //Set cursor at 1st-line 0th-Position	
	OLED_DisplayString("Uploading Init Data");
	DELAY_1(1000);
	
	DELAY_1(100);
	SendDatatToCloud("GET /update?key=RJ4ZCZX8AV7V1XRL&field1=900");
	DELAY_1(100);
	
	rxBytes=0;
} // CONNECT_TO_WIFI ends here.


void SendDatatToCloud(unsigned char *uploadData){
	SERIAL_STRING_TX("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	DELAY_1(100);
	DELAY_1(100);
	SERIAL_STRING_TX("AT+CIPSEND=47");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	DELAY_1(100);
	DELAY_1(100);
	
	SERIAL_STRING_TX(uploadData);
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);

	DELAY_1(100);
	DELAY_1(100);
	SERIAL_STRING_TX("AT+CIPCLOSE");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	
	SERIAL_STRING_TX("AT");
	SERIAL_TRANSMIT(0x0D);
	SERIAL_TRANSMIT(0x0A);
	OLED_SetCursor(6,0);
	OLED_DisplayString("Uploaded Data      ");
	
	DELAY_1(1500);
}

void SERIAL_RECIEVE(void) interrupt 4{
	unsigned char value;
	if(RI){		// enter the condition when RI is one
		value=SBUF;  // Store SBUF to a variable
		RECIEVEbuffer[rxBytes]=value;
	  
		if(RECIEVEbuffer[rxBytes]==0x0A && RECIEVEbuffer[rxBytes-1]==0x0D && powerON==0){  // Reading power On Sequence.
			rxBytes=0;
			powerON=1;
		}
		if(RECIEVEbuffer[rxBytes]==0x0A && RECIEVEbuffer[rxBytes-1]==0x0D && powerON==1){ // To Read Regular Response.
			//rxBytes=0;
			processFLAG=1;
		}
		if(rxBytes>RXBUFFSIZE && value!=0x0D && powerON==1) { // To Avoid 0x0D in the last byte at power On.
			rxBytes--;
			RECIEVEbuffer[rxBytes]=0x0D;
		}
		if(rxBytes>RXBUFFSIZE && powerON==1){ // When Buffer Overflow.
			rxBytes=0;
		}
		rxBytes++;		
	  RI=0;  // Make Recieve Flag to zero
	}
	
} // interrupt 4 ends here

void TimerInterrupt(void) interrupt 1{
	static unsigned int count;
	TR0=0;
	TH0=0xF8;
	TL0=0xCD;
	TR0=1;
	count++;
	if(count==1000){
		count=0;
		P0_7=~P0_7;
	}
}

void DELAY_1(unsigned int delayCount){
	unsigned int i,j;
	for(i=0;i<delayCount;i++){
	for(j=0;j<1000;j++);
	}
}

void WiFiInit(void){
unsigned char index=0;
unsigned int readyStatus=0,j=0;	
	OLED_SetCursor(3,0);  //Set cursor at 1st-line 0th-Position
	OLED_DisplayString("Initializing WiFi");
	
	WiFiReset = 0;
	DELAY_1(100);
	WiFiReset = 1;
	DELAY_1(100);
	
	while(processFLAG){
		processFLAG=0;
		for(index=0;index<rxBytes;index++){
			workingBUFFER[index]=RECIEVEbuffer[index+1];
		}
		rxBytes=0;
		if(strcmp(workingBUFFER,"ready")){
			step=1;
		}
  	DELAY_1(100);
		if(step==1){
			SERIAL_STRING_TX("AT+CWMODE=1");
		  SERIAL_TRANSMIT(0x0D);
		  SERIAL_TRANSMIT(0x0A); 	
		  DELAY_1(100);
			step=2;
		}
		if(step==2){
			SERIAL_STRING_TX("AT+CWLAP");
			SERIAL_TRANSMIT(0x0D);
		  SERIAL_TRANSMIT(0x0A);
		  DELAY_1(2500);
			step=3;
		}
		if(step==3){
			CONNECT_TO_WIFI(SSID,PWD);
			DELAY_1(500);
			step=4;
			break;
		}
	}
}
