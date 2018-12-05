/*
 * BitWriterStream.h
 *
 *  Created on: May 3, 2018
 *      Author: Yuun
 */

#ifndef SRC_BITWRITERSTREAM_H_
#define SRC_BITWRITERSTREAM_H_

#include <fstream>

const int BYTE = 8;

class BitWriterStream {
public:
	BitWriterStream();
	BitWriterStream(std::string outputfile);

	virtual ~BitWriterStream();

	int putBit(unsigned int bit);
	int putByte(unsigned char byte);
	void flush();
private:
	unsigned char buffer_;
	int buffer_size;
	std::ofstream outputStream;
};


#endif /* SRC_BITWRITERSTREAM_H_ */
