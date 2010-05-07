/*
 
 ATmega32 USART library example
 
 Copyright 2010 Tymon Tobolski
 Politechnika Wroclawska
 
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/usart/usart.h"

USART32(usb);

int main(void){
	sei();
	
	
    for(;;){
        while(usb.empty());
		unsigned char c;
		usb >> c;
		usb << "got: " << c << "\n\r";
    }
    return 0;
}
