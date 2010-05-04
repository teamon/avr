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

#include "buffer.h"
#include <stdlib.h>

Buffer::Buffer(){
	_head = _tail = NULL;
	_size = 0;
}

void Buffer::clear(){
	while(_head != NULL) pop();
}

bool Buffer::empty(){
	return (_head == NULL);
}

void Buffer::push(char c){
	BufferItem *curr = (BufferItem*) malloc(sizeof(BufferItem));
	if(_head == NULL) _head = curr;
	else _tail->next = curr;
	curr->character = c;
	curr->next = NULL;
	_tail = curr;
	_size++;
}

void Buffer::pop(){
	if(_head){
		BufferItem *tmp = _head->next;
		free(_head);
		_head = tmp;
		_size--;
	}
}

char * Buffer::front(){
	return (_head ? &(_head->character) : NULL);
}

int Buffer::size(){
	return _size;
}

unsigned char Buffer::read(){
	unsigned char n = *front();
	pop();
	return n;
}
