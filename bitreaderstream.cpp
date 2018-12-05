/*
 * BitReaderStream.cpp
 *
 *  Created on: May 6, 2018
 *      Author: Yuun
 */

#include "BitReaderStream.h"

BitReaderStream::BitReaderStream() {
	buffer_ = 0;
	buffer_size = 0;
		
}

BitReaderStream::BitReaderStream(std::string huffFile) {
	buffer_ = 0;
	buffer_size = 0;
	input.open(huffFile.c_str());	

}


BitReaderStream::~BitReaderStream() {
	input.close();
}

unsigned int BitReaderStream::getBit() {
	if (buffer_size == 0) {
		buffer_ = input.get();
		buffer_size = 8;
	}
	unsigned int bit = buffer_ & (1 << (buffer_size - 1));
	bit = bit >> (buffer_size -1);
	buffer_size--;
	return bit;
}

unsigned char BitReaderStream::getByte() {
	buffer_ = input.get();
	buffer_size = 0;
	//std::bitset<8> test(buffer_);
	//cerr << test << endl;
	return buffer_;
}
