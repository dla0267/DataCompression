/*
 * HuffmanTree.h
 *
 *  Created on: May 2, 2018
 *      Author: Yuun
 */

#ifndef SRC_HUFFMANTREE_H_
#define SRC_HUFFMANTREE_H_
#include <string>
#include "Node.h"
#include "Heap.h"
#include <limits.h>
#include <bitset>
#include "BitReaderStream.h"
#include <iostream>
#include <fstream>

using namespace std;


class HuffmanTree {
public:
	HuffmanTree();
	HuffmanTree(unsigned int table[]);
	HuffmanTree(BitReaderStream& reader);
	virtual ~HuffmanTree();

	void Build_table(unsigned long long* code_table, int* codes_length);
	void decode_message(BitReaderStream& reader, string puffFile, unsigned int num_of_chars);
	
	void verify(unsigned long long* code_table, int* codes_length);	
private:
	Heap<Node<unsigned int, unsigned char>*,
		CompareNode<unsigned int, unsigned char> > priority_queue;

	Node<unsigned int, unsigned char>* root_;

	void Build_tableHelper(unsigned long long* code_table, int* codes_length,
			Node<unsigned int, unsigned char>* current,
			int depth, unsigned int binary_code);


	Node<unsigned int, unsigned char>*  build_Tree(Node<unsigned int, unsigned char>* current,
		 unsigned char ch, int binary_length, unsigned long long binary_code);	
	
	void decode_helper(std::ofstream& output, BitReaderStream& reader,
				 Node<unsigned int, unsigned char>* current);
	void dump(Node<unsigned int, unsigned char>* current, int level);

	void verify_helper(Node<unsigned int, unsigned char>* current,
			unsigned long long* code_table, int* codes_length,
			unsigned long long code_from_tree, int depth);
};


#endif /* SRC_HUFFMANTREE_H_ */
