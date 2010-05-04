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

#ifndef _USART_H_
#define _USART_H_

/**
 * @defgroup usart USART Library for Atmega128
 * 
 * @brief Interrupt UART library for Atmega128 using the built-in UART with transmit
 * and receive circular buffers. 
 *
 * This library can be used to transmit and receive data through the built in UART. 
 *
 * An interrupt is generated when the UART has finished transmitting or
 * receiving a byte. The interrupt handling routines use circular buffers
 * for buffering received and transmitted data.
 * 
 * @version 0.1
 * @author Tymon Tobolski http://teamon.eu
 **/

#include "buffer.h"

/**
 * @file usart.h
 */

/**
 * @def USART_BAUD
 * 
 * Defines USART baud rate if not previously defined
 * 
 * @ingroup usart
 **/
#ifndef USART_BAUD
#define USART_BAUD 9600L
#endif

/**
 * @class Usart
 * 
 * Base class for Usart0 and Usart1
 * @ingroup usart
 **/
class Usart {
public:
	
	/**
	 * Pushes character into input buffer
	 * 
	 * @param c - character to push
	 **/
	void push(char c);
	
	/**
	 * Reads single character from Usart input buffer
	 * 
	 * @return character
	 **/
	unsigned char read();
	
	/**
	 * Checks if Usart input buffer is empty
	 * 
	 * @return true if there are items in buffer, otherwise false
	 **/
	bool empty();
	
	
	/**
	 * Reads line from buffer
	 * Waits until \n is present
	 *
	 * @return line of characters (without \n)
	 **/
	char * readline();
	
    bool gotLine();
	
	/**
	 * Sends unsigned char to Usart
	 * 
	 * @param c - character
	 * @return Usart object
	 **/
	Usart & operator<<(const unsigned char c);
	
	/**
	 * Sends char to Usart
	 * 
	 * @param c - character
	 * @return Usart object
	 **/
	Usart & operator<<(const char c);
	
	/**
	 * Sends string to Usart
	 * 
	 * @param string - string (char* pointer)
	 * @return Usart object
	 **/
	Usart & operator<<(char* string);
	
	/**
	 * Sends number to Usart
	 * 
	 * @param number - integer number
	 * @return Usart object
	 **/
	Usart & operator<<(const int number);
	
	/**
	 * Sends number to Usart
	 * 
	 * @param number - long number
	 * @return Usart object
	 **/
	Usart & operator<<(const long number);
	
	/**
	 * Reads char from Usart
	 * 
	 * @param c - char variable to write to
	 * @return Usart object
	 **/
	Usart & operator>>(unsigned char &c);
	
	/**
	 * Reads number from Usart
	 * 
	 * @param c - int variable to write to
	 * @return Usart object
	 **/
	Usart & operator>>(int &c);
	
	/**
	 * Sends byte to Usart
	 * 
	 * @param byte - character
	 **/
	virtual void sendByte(unsigned char byte){};
	
private:
	Buffer buf; /**< Input buffer */
};

#if defined(__AVR_ATmega128__)

/**
 * @def USART0(u)
 * 
 * Creates new object of type Usart0 and registers USART receive interrupt
 * 
 * @param u - name of USART0 variable
 * @ingroup usart
 **/
#define USART0(u) Usart0 u; ISR(USART0_RX_vect){ int c; c = UDR0; u.push(c); }

/**
 * @def USART1(u)
 * 
 * Creates new object of type Usart1 and registers USART receive interrupt
 * 
 * @param u - name of USART1 variable
 * @ingroup usart
 **/
#define USART1(u) Usart1 u; ISR(USART1_RX_vect){ int c; c = UDR1; u.push(c); }

/**
 * @class Usart0
 * 
 * Atmega128 USART0 interface
 * @ingroup usart
 **/
class Usart0: public Usart {
public:
	Usart0();
	void sendByte(unsigned char byte);
};

/**
 * @class Usart1
 * 
 * Atmega128 USART1 interface
 * @ingroup usart
 **/
class Usart1: public Usart {
public:
	Usart1();
	void sendByte(unsigned char byte);
};

#elif defined(__AVR_ATmega32__)

/**
 * @def USART32(u)
 * 
 * Creates new object of type Usart32 and registers USART receive interrupt
 * 
 * @param u - name of USART32 variable
 * @ingroup usart
 **/
#define USART32(u) Usart32 u; ISR(USART_RXC_vect){ int c; c = UDR; u.push(c); }

/**
 * @class Usart32
 * 
 * Atmega32 USART interface
 * @ingroup usart
 **/
class Usart32: public Usart {
public:
	Usart32();
	void sendByte(unsigned char byte);
};

#endif

#endif
