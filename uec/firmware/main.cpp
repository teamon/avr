/* Project info here */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"

USART32(usb);

int main(void){
	sei();
	
    for(;;){
        while (usb.empty());
		unsigned char c;
		usb >> c;
		usb << c;
    }
    return 0;
}
