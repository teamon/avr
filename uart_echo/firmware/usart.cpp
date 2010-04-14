/*
Copyright (c) 2010 Tymon Tobolski
 
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
 
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <avr/io.h>
#include <stdlib.h>
#include "usart.h"

/**
 * @def __usart__char2int(c)
 * Converts char into int, e.g. '1' into 1
 * 
 * @param c - char
 * @addtogroup usart
**/
#define __usart__char2int(c) (c - 48)

/**
 * @def __usart__int2char(c)
 * Converts int into char, e.g. 1 into '1'
 * 
 * @param i - int
 * @addtogroup usart
**/
#define __usart__int2char(i) (i + 48)

void Usart::push(char c){
	buf.push(c);
}

unsigned char Usart::read(){
	return buf.read();
}

bool Usart::empty(){
	return buf.empty();
}

char * Usart::readline(){
	char c;
	char * buf = (char*) malloc(sizeof(char)*1024);
	int i = 0;

	while(i < 1024){
		while(empty());
		c = read();
		if(c == '\n') break;
		buf[i] = c;
		i++;
	}
	
	buf[i] = '\0';
	return buf;
}

Usart & Usart::operator<<(const unsigned char byte){
	sendByte(byte);
	return *this;
}

Usart & Usart::operator<<(const char byte){
	sendByte(byte);
	return *this;
}

Usart & Usart::operator<<(char* string){
	while (*string != '\0') sendByte(*string++);
	return *this;
}

Usart & Usart::operator<<(const long number){
	char str[10];
	itoa(number, str, 10);
	*this << str;
	return *this;
}

Usart & Usart::operator<<(const int number){
	*this << (long)number;
	return *this;
}

Usart & Usart::operator>>(unsigned char &c){
	c = read();
	return *this;
}

Usart & Usart::operator>>(int &c){
	unsigned char first = read();
	int n = 0;
	int sign = 1;

	if(first == '-') sign = -1;
	else if(first >= '0' && first <= '9') n = __usart__char2int(first);

	for(;;){
		while(buf.empty());
		unsigned char c = buf.read();
		if(c == '\n') break;
		n *= 10;
		n += __usart__char2int(c);
	}

	c = n*sign;
	return *this;
}


// USARTn specific methods

#if defined(__AVR_ATmega128__)

// USART0
Usart0::Usart0(){
	int ubrr = (int)(F_CPU/USART_BAUD/16) - 1;
	
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (3 << UCSZ00);
}

void Usart0::sendByte(unsigned char byte){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}


// USART1
Usart1::Usart1(){
	int ubrr = (int)(F_CPU/USART_BAUD/16) - 1;
	
	UBRR1H = (unsigned char) (ubrr >> 8);
	UBRR1L = (unsigned char) ubrr;
	UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << USBS0) | (1 << UCSZ11) | (3 << UCSZ10);
}

void Usart1::sendByte(unsigned char byte){
	while (!(UCSR1A & (1<<UDRE1)));
	UDR1 = byte;
}

#elif defined(__AVR_ATmega32__)

// USART32
Usart32::Usart32(){
	int ubrr = (int)(F_CPU/USART_BAUD/16) - 1;
	
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	// UCSRC = (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);
	UCSRC = (1 << URSEL) | (1 << USBS) | (1 << UCSZ1) | (3 << UCSZ0);
}

void Usart32::sendByte(unsigned char byte){
	while (!(UCSRA & (1<<UDRE)));
	UDR = byte;
}

#endif
