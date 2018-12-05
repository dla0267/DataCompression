/*
 * Driver.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: Yuun
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include "HuffmanTree.h"
#include "BitWriterStream.h"
using namespace std;

void dump(unsigned int table[]);
void code_symbols_table(BitWriterStream& output,
		unsigned long long code_table[], int length[]);
void num_char(BitWriterStream& writerStream, unsigned int number_char);
void encode(BitWriterStream& output, unsigned long long code_table[], int length[], string inputText);
void dump(unsigned long long code_table[], int sizs[]);


int main(int argc, char* argv[]) {

	// input and output file arguments that are passed
	string inputText = argv[1];
	string outfile = inputText.substr(0, inputText.length() - 4) + ".huff";


	ifstream inFile;
	inFile.open(inputText.c_str());
	unsigned int Frequency_table[UCHAR_MAX + 1] = {0};
	unsigned int  num_of_ch = 0;

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		return EXIT_FAILURE;   // call system to stop
	} else {
		unsigned char ascii;
		ascii = inFile.get();
		while(!inFile.eof()) {
			Frequency_table[ascii]++;
			num_of_ch++;
			ascii = inFile.get();
		}
	}
	inFile.close();

	// printing frequency table
	dump(Frequency_table);

	HuffmanTree huffman(Frequency_table);

	//arrays for code_table and length of binary code for each character
	unsigned long long code_table[UCHAR_MAX + 1] = {0};
	int code_length_table[UCHAR_MAX + 1] = {0};

	// update code_table with the binary code for each char
	huffman.Build_table(code_table, code_length_table);
	
	// verifying huffman Tree
	huffman.verify(code_table, code_length_table);

//	dump(code_table, code_length_table);

	BitWriterStream writerStream(outfile);

	code_symbols_table(writerStream, code_table, code_length_table);
	
	num_char(writerStream, num_of_ch);

	encode(writerStream, code_table, code_length_table, inputText); 

	return EXIT_SUCCESS;
}

void code_symbols_table(BitWriterStream& writerStream,
		unsigned long long code_table[], int length[]) {
	for (int i = 0; i < UCHAR_MAX + 1; i++) {
		unsigned long long code = code_table[i];
		int length_ = length[i];
		unsigned char bitcount = static_cast<unsigned char>(length_);
		
		//cerr << char(i) <<" " << length_ << endl;
		//bitset<64> bitsetA(code_table[i]);
		//cerr <<  bitsetA << endl;
		writerStream.putByte(bitcount);
		if (length_ > 0) {
			for (int i = 1; i <= length_; i++) {
				int	shifting_length = length_ - i;
				unsigned long long temp = code & (1 << shifting_length);
				unsigned int bit = (temp >> shifting_length) & 1;
				writerStream.putBit(bit);
			}
			writerStream.flush();
		}
	}


	
}

void num_char(BitWriterStream& writerStream, unsigned int number_char) {
	cerr << "Total number of characters in the input file: " << number_char << endl;
	for (int i = 0; i < 4; i ++) {
		unsigned char temp = static_cast<unsigned char>(number_char);
		writerStream.putByte(temp);
		number_char = number_char >> 8;
	}
}


void encode(BitWriterStream& output, unsigned long long code_table[], int length[], string inputText) {
	ifstream input;
	input.open(inputText.c_str());
	if (input.is_open()) {
		unsigned char ch = input.get();
		while (!input.eof()) {
			unsigned long long code = code_table[ch];
			int length_ = length[ch];
			
			for (int i =0; i < length_; i++) {
				int shift = length_ - i - 1;
				unsigned long long temp = code & (1 << shift);
				unsigned int bit = (temp >> shift) & 1;
				output.putBit(bit);
			}
			ch = input.get();
		}
		output.flush();
	}
	input.close();
}




void dump(unsigned int table[]) {
	cerr << "Frequency Table" << endl;
	cerr << "character" << "\t" << "in hex" << "\t" << "printable(1=printable/0=not printable" << "\t" << "count" << endl;
	unsigned int maxFreq = 0;
	for (unsigned int i = 0; i < 256;  i++) {
		maxFreq = max(table[i], maxFreq);
		unsigned char c = i;
		cerr << c << "\t\t" << std::hex << i  << std::dec  << "\t" << isprint(i) << "\t\t\t\t\t" << table[i] << endl;
	}

	cerr << "The Relative Frequency of character" << endl;
	for (int i = 0; i < UCHAR_MAX + 1; i++) {
		unsigned char ch = i;
		cerr << "ch " << char(i) << ":";
		unsigned int splat = 50 * table[i] / maxFreq; 
		for (int j = 0; j < splat; j++) {
			cerr << "*";
		}
		cerr << endl;
	}
}

void dump(unsigned long long code_table[], int length[]) {

	for (int i = 0; i < UCHAR_MAX + 1; i++) {
		int length_ = length[i];
		if (length_ > 0) {
			unsigned long long code = code_table[i];
			bitset<64> bit(code);
			cerr << (char)i << ": " << length_ << " " << bit << endl;


		}
	}
}

