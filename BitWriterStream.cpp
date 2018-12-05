/*
 * BitWriterStream.cpp
 *
 *  Created on: May 3, 2018
 *      Author: Yuun
 */

#include "BitWriterStream.h"
using namespace std;

BitWriterStream::BitWriterStream() {
	buffer_ = 0;
	buffer_size = 0;
	outputStream.open("/Users/Yuun/Desktop/assignment2/Assignment2/src/wordcount.txt");
}

BitWriterStream::BitWriterStream(std::string outputfile){
	buffer_ = 0;
	buffer_size = 0;
	outputStream.open(outputfile.c_str());
}


BitWriterStream::~BitWriterStream() {
	flush();
	outputStream.close();
}

int BitWriterStream::putBit(unsigned int bit) {
	if (bit > 1) {
		return 0;
	}

	if (bit == 0 || bit == 1) {
		buffer_ = (buffer_ << 1) + bit;
		buffer_size++;
	}
	if (buffer_size == BYTE) {
		flush();
	}
	return 1;
}

int BitWriterStream::putByte(unsigned char byte) {
	buffer_ = byte;
	buffer_size = BYTE;
	flush();
	return 1;
}

void BitWriterStream::flush() {
	if (buffer_size != 0) {
		buffer_ = buffer_ << (8 - buffer_size);
		outputStream.put(buffer_);
		buffer_size = 0;
		buffer_ = 0;
	}
}

