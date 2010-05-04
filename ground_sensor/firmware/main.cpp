/* Project info here */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../lib/lcd/lcd.h"


LCD lcd;
volatile int adc_value = 0;

SIGNAL (SIG_ADC){
	adc_value = (ADCL | (ADCH << 8));
	ADCSRA |= _BV(ADSC);
}

int main(void){
	// ADC init
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //INIT ADC
	ADMUX = _BV(REFS0);
	
	sei();
	
	lcd << "adc: ";
	
    for(;;){
        lcd.gotoxy(5, 0);
		lcd << adc_value;
		lcd << "     ";
		_delay_ms(50);
	}
    return 0;
}
