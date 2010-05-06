/* Project info here */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../lib/usart/usart.h"

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
