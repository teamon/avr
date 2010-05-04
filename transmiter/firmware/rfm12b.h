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

#ifndef _RFM12B_H_
#define _RFM12B_H_

/**
 * @defgroup rfm12b RFM12B Transceiver library
 *
 * This library can be used to transmit and receive data through the RFM12B Transceiver. 
 * 
 * @version 0.1
 * @author Tymon Tobolski http://teamon.eu
**/

/**
 * @file rfm12b.h
**/

/**
 * @class RFM12B_Base
 *
 * Base class for Transmiter and Receiver
 * @ingroup rfm12b
**/ 
class RFM12B_Base {
private:
	unsigned char buffer[16];
	char buffer_pos = 0;

public:
	
	/**
	 * Writes command to device
	 *
	 * @param cmd - command
	**/
	void writeCmd(unsigned int cmd);
	
	/**
	 * Initialize port
	**/
	void portInit();
	
	/**
	 * General iitialization
	**/
	void init();
	
	/**
	 * 
	**/ 
	void sendByte(unsigned char data);
	void sendPackage();
	unsigned char receive();
};

#endif
