#ifndef _SERIAL_H_	
	#define _SERIAL_H_
	
  void TIMER_INIT(void);
  void SERIAL_INIT(void);
	void SERIAL_TRANSMIT(unsigned char c);
	void SERIAL_STRING_TX(unsigned char *tx_String);
	void SERIAL_STRING_TX_LN(unsigned char *tx_String);
	
#endif