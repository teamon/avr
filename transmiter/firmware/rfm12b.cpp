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

#include "rfm12b.h"
	
void RFM12B_Base::writeCmd(unsigned int cmd);
	
void RFM12B_Base::portInit();
	
void RFM12B_Base::init();
	
void RFM12B_Base::sendByte(unsigned char data);

void RFM12B_Base::sendPackage();

unsigned char RFM12B_Base::receive();

void RFM12B_Base::operator<<(unsigned char c){
	buffer[buffer_pos] = c; // add to buffer
	buffer_pos++;
	
	// send package if buffer is full
	if(buffer_pos >= 16) {
		sendPackage();
		buffer_pos = 0;
	}
	return *this;
}


void RFM12B_Base::operator<<(char* string){
	while (*string != '\0') sendByte(*string++);
	return *this;
}


void RFM12B_Base::flush(){
	// fill buffer with zeros
	for(int i = buffer_pos; i < 16; i++){
		buffer[i] = 0;
	}
	
	sendPackage();
	buffer_pos = 0;
}
