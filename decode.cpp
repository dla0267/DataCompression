

#include <iostream>
#include <fstream>
#include <limits.h>
#include "HuffmanTree.h"
#include "BitReaderStream.h"
#include <string>

using namespace std;

unsigned int readNums(BitReaderStream& reader);


int main(int argc, char* argv[]) {
	
	string huffFile = argv[1];
	string puffFile = huffFile.substr(0, huffFile.length() - 4) + "puff";
	
	
	unsigned int code_symbols_table[UCHAR_MAX + 1] = {0};	
	int lengthOfCode_symbols[UCHAR_MAX + 1];
	
	BitReaderStream reader(huffFile);
	
	// building huffman tree to decode 
	HuffmanTree huffman(reader);
	
	// record the number of all the character occurences	
	unsigned int num_of_chars = readNums(reader);
	// decode message back to original message.
	huffman.decode_message(reader, puffFile, num_of_chars);

	return EXIT_SUCCESS;
}



unsigned int readNums(BitReaderStream& reader) {
	unsigned int num_of_chars = 0;
	for (int i = 0; i < 4; i++) {
		num_of_chars += reader.getByte() << i * 8;
	}
	return num_of_chars;
}
