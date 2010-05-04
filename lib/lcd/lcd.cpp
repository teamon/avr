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

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "lcd.h"

#ifndef LCD_RS
	#error "LCD_RS not defined"
#endif

#ifndef LCD_E
	#error "LCD_E not defined"
#endif

#ifndef LCD_D4
	#error "LCD_D4 not defined"
#endif

#ifndef LCD_D5
	#error "LCD_D5 not defined"
#endif

#ifndef LCD_D6
	#error "LCD_D6 not defined"
#endif

#ifndef LCD_D7
	#error "LCD_D7 not defined"
#endif

#ifndef LCD_DP
	#error "LCD_DP not defined"
#endif

#ifndef LCD_CP
	#error "LCD_CP not defined"
#endif

#ifndef LCD_DDR
	#error "LCD_DDR not defined"
#endif

#ifndef LCD_CDR
	#error "LCD_CDR not defined"
#endif


LCD::LCD(){
	_delay_ms(15);
	LCD_DP=0x00;
	LCD_CP=0x00;
	LCD_DDR|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCD_CDR|=1<<LCD_E|1<<LCD_RS;
    //--------- Write 0x03 -----------
	LCD_DP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(5);
	//--------- Write 0x03 -----------
	LCD_DP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------- Write 0x03 ------------
	LCD_DP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|1<<LCD_D4;
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	//--------- Enable Four Bit Mode ----------
	LCD_DP&=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x2
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Set Interface Length ----------
	LCD_DP|=0<<LCD_D7|0<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x2 - 4 bits
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	LCD_DP|=1<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x8 - 2 lines, 5x7
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Turn off the Display ----------
	LCD_DP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	LCD_DP|=1<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x8 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
   //------------ Clear the Display -----------
	LCD_DP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	LCD_DP|=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|1<<LCD_D4; //Write 0x1
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
   //-------- Set Cursor Move Direction --------
	LCD_DP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	LCD_DP|=0<<LCD_D7|1<<LCD_D6|1<<LCD_D5|0<<LCD_D4; //Write 0x6 - Increment the Cursor
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
   //---------- Enable Display/Cursor ----------
	LCD_DP&=0<<LCD_D7|0<<LCD_D6|0<<LCD_D5|0<<LCD_D4; //Write 0x0 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	LCD_DP|=1<<LCD_D7|1<<LCD_D6|1<<LCD_D5|1<<LCD_D4; //Write 0xF - Display on, cursor on, blink on 
	LCD_CP|=1<<LCD_E|0<<LCD_RS;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
}
	
void LCD::cmd(unsigned char c){
	//4 MSB bits
	LCD_DP=((c>>2)&0b00111100);
	LCD_CP|=1<<LCD_E;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
	//4 LSB bits
	LCD_DP=((c<<2)&0b00111100);
	LCD_CP|=1<<LCD_E;		
	_delay_ms(1);
	LCD_CP&=~(1<<LCD_E);
	_delay_ms(1);
}

void LCD::clear(){
	cmd(0x01);
}

void LCD::gotoxy(unsigned char x, unsigned char y){
	// remap lines into proper order
	switch(y){
		case 0:  cmd(1<<7 | (0x00 + x)); break;
		case 1:  cmd(1<<7 | (0x40 + x)); break;
		case 2:  cmd(1<<7 | (0x14 + x)); break;
		case 3:  cmd(1<<7 | (0x54 + x)); break;
		default: cmd(1<<7 | (0x00 + x));
	}
}

void LCD::define(const unsigned char * dfn, unsigned char code){
	unsigned char a = (code << 3) | 0x40;
	for(int i=0; i<8; i++){
		cmd(a++);
//		*this << (unsigned char)*(dfn+i);
                *this << (unsigned char)pgm_read_byte(dfn+i);
	}
}

void LCD::shift(char n){
	if(n > 0) while(n--) cmd(0x14); // shift right
	else while(n++) cmd(0x10); // shift left
}

void LCD::cursorOn(){
	cmd(0x0E);
}

void LCD::cursorOff(){
	cmd(0x0C);
}

void LCD::cursorBlink(){
	cmd(0x0F);
}

void LCD::blank(){
	cmd(0x08);
}

void LCD::visible(){
	cmd(0x0C);
}

LCD & LCD::operator<<(const unsigned char c){
	LCD_DP=((c>>2)&0b00111100);
	LCD_CP|=1<<LCD_RS|1<<LCD_E;
	_delay_ms(1);
	LCD_CP&=0<<LCD_E|0<<LCD_RS;	
	_delay_ms(1);
    //4 LSB bits
	LCD_DP=((c<<2)&0b00111100);
	LCD_CP|=1<<LCD_RS|1<<LCD_E;
	_delay_ms(1);
	LCD_CP&=0<<LCD_E|0<<LCD_RS;	
	_delay_ms(1);
	return *this;
}

LCD & LCD::operator<<(const char c){
	*this << (unsigned char)c;
	return *this;
}

LCD & LCD::operator<<(const char * string){
	*this << (char*)string;
	return *this;
}


LCD & LCD::operator<<(char* string){
	while(*string != '\0') *this << *string++;
	return *this;
}

LCD & LCD::operator<<(const int number){
	*this << (long) number;
	return *this;
}

LCD & LCD::operator<<(const long number){
	char str[10];
	itoa(number, str, 10);
	*this << str;
	return *this;
}
