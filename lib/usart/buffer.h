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

#ifndef _BUFFER_H_
#define _BUFFER_H_


/**
 * @struct BufferItem
 * Buffer item data, internal use only
 * 
 * @ingroup usart
 **/
struct BufferItem {
	char character;
	BufferItem* next;
};

/**
 * @class Buffer
 * FIFO Buffer class
 * 
 * Stores incomming USART characters
 * 
 * @ingroup usart
 **/
class Buffer {
public:
	
	/**
	 * Default constructor
	 **/
	Buffer();
	
	/**
	 * Adds character to the end of buffer
	 * 
	 * @param c - character to add
	 **/
	void push(char c);
	
	/**
	 * Pops first item from list
	 * 
	 * @see read()
	 **/
	void pop();
	
	/**
	 * Clears buffer - removes all items
	 **/
	void clear();
	
	/**
	 * Checks if buffer is empty
	 * 
	 * @return true if there are items in buffer, otherwise false
	 **/
	bool empty();
	
	/**
	 * Returns pointer to first item
	 * 
	 * @returns pointer to first item
	 * @see read()
	 **/
	char * front();
	int size();
	
	/**
	 * Pops first item from list and returns it
	 * 
	 * @return first item
	 * @see pop()
	 **/
	unsigned char read();
	
// private:
	int _size;
	BufferItem *_head, *_tail;
};

#endif
