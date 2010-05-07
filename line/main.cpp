/* Project info here */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../lib/usart/usart.h"

#define min(a,b) ((a) < (b) ? (a) : (b))

USART32(usb);

unsigned char command = 0;
int pwm_value = 0;
char dir = 0;
volatile int adc_value =0, enc_value=0;

SIGNAL (SIG_INTERRUPT0){
	if(PINB & (1 << PB0)) enc_value--;
	else enc_value++;
}

SIGNAL (SIG_ADC){
	adc_value = (ADCL | (ADCH << 8));
	ADCSRA |= _BV(ADSC);
}

void init(){
	MCUCR |= (1 << ISC01) | (1 << ISC00); // encoder, raising edge fires interrupt
	GICR  |= (1 << INT0); // INT0 enabled
	
	// TCNT1 = 0xC2F7;
	// TIMSK = _BV(TOIE1);
	// TIFR |= _BV(TOV1);
	
	// pwm interrupt offblast
	TCCR1A = _BV(WGM10) | _BV(WGM11) | _BV(COM1A1);
	TCCR1B = _BV(CS11);
	
	// ADC init
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADSC) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); //INIT ADC
	ADMUX = _BV(REFS0);
	
	DDRB &= ~(1 << PB0);
	DDRD = (1 << PD6) | (1 << PD5);
	
	OCR1A = 0;
}


int main(void){
	init();
    sei();
	
	
	for(;;){
		
		if(usb.gotLine()){
			usb >> command;
			usb >> pwm_value;
			
			while(!usb.empty()){
				unsigned char c;
				usb >> c;
				if(c == '\n') break;
			}
			
			char d =- 1;
			
			switch(command){
				case 'S': // stop
					pwm_value = 0;
					break;
				case 'F': // forward
					d = 1;
					break;
				case 'B': // backward
					d = 0;
					break;
			}
			
			if(d != dir){
				dir = d;
				if(dir >= 0){
					// stop, change dir
					OCR1A = 0;
					_delay_ms(100);
					PORTD |= (dir << PD6);
					PORTD = (1 << PD5) | (dir << PD6);
				}
			}
			
			OCR1A = min(pwm_value, 500);
		}
		
		usb << "A=" << adc_value << ":E=" << enc_value << "\n";
	}
	
    return 0;
}
