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

//define connctions for LCD
#define LCD_RS	0 	//define MCU pin connected to LCD RS
#define LCD_E	1	//define MCU pin connected to LCD E

#define LCD_D4	2	//define MCU pin connected to LCD D3
#define LCD_D5	3	//define MCU pin connected to LCD D4
#define LCD_D6	4	//define MCU pin connected to LCD D5
#define LCD_D7	5	//define MCU pin connected to LCD D6

#define LCD_DP PORTB	//define MCU port connected to LCD data pins
#define LCD_CP PORTB	//define MCU port connected to LCD control pins
#define LCD_DDR DDRB	//define MCU direction register for port connected to LCD data pins
#define LCD_CDR DDRB	//define MCU direction register for port connected to LCD control pins


#ifndef _LCD_H_
#define _LCD_H_

/**
 * @defgroup lcd LCD Library
 * 
 * @brief Simple LCD interface
 * 
 * @version 0.1
 * @author Tymon Tobolski http://teamon.eu
**/

/**
 * @enum LCDCursor
 * Defines cursor mode
 * @ingroup lcd
**/

/**
 * @class LCD
 * 
 * 74HC164 LCD display interface
 * 
 * @ingroup lcd
**/
class LCD {
public:
	/**
	 * Default constructor.
	 * Initializes display
	**/
	LCD();
	
	/**
	 * Sends command to display
	 * 
	 * @param c - command
	**/
	void cmd(unsigned char c);
	
	/**
	 * Clears display
	**/
	void clear();
	
	/**
	 * Moves cursor to X Y position
	 * 
	 * @param x - x position
	 * @param y - y position
	**/
	void gotoxy(unsigned char x, unsigned char y);
	
	/**
	 * Defines custom character
	 * 
	 * @param dfn - character description table
	 * @param code - character code
	**/
	void define(const unsigned char * dfn, unsigned char code);
	
	/**
	 * Shifts cursor n positions
	 * 
	 * if n > 0 - shift right
	 * else - shift left
	 * 
	 * @param n - number of positions
	**/
	void shift(char n);
	
	/**
	 * Turns on cursor
	**/
	void cursorOn();
	
	/**
	 * Turns off cursor
	**/
	void cursorOff();
	
	/**
	 * Blink cursor
	**/
	void cursorBlink();
	
	/**
	 * Makes display blank, but does not clear it
	**/
	void blank();
	
	/**
	 * Makes display visible
	**/
	void visible();
	
	/**
	 * Sends unsigned char to lcd
	 * 
	 * @param c - character
	 * @return LCD object
	**/
	LCD & operator<<(const unsigned char c);
	
	/**
	 * Sends char to LCD
	 * 
	 * @param c - character
	 * @return LCD object
	**/
	LCD & operator<<(const char c);
	
	/**
	 * Sends char to LCD
	 * 
	 * @param string - string constant
	 * @return LCD object
	**/
	LCD & operator<<(const char * string);
	
	/**
	 * Sends string to LCD
	 * 
	 * @param string - string (char* pointer)
	 * @return LCD object
	**/
	LCD & operator<<(char* string);
	
	/**
	 * Sends number to LCD
	 * 
	 * @param number - integer number
	 * @return LCD object
	**/
	LCD & operator<<(const int number);
	
	/**
	 * Sends number to LCD
	 * 
	 * @param number - long number
	 * @return LCD object
	**/
	LCD & operator<<(const long number);	
};

#endif
