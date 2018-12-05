/*
 * BitReaderStream.h
 *
 *  Created on: May 6, 2018
 *      Author: Yuun
 */

#ifndef SRC_BITREADERSTREAM_H_
#define SRC_BITREADERSTREAM_H_

#include <fstream>
#include <bitset>
#include <iostream>

using namespace std;


class BitReaderStream {
public:
	BitReaderStream();
	BitReaderStream(std::string outputFile);
	virtual ~BitReaderStream();

	unsigned int getBit();
	unsigned char getByte();

	void close();
private:
	std::ifstream input;
	unsigned char buffer_;
	int buffer_size;	
};

#endif /* SRC_BITREADERSTREAM_H_ */
