/*
 * HuffmanTree.cpp
 *
 *  Created on: May 2, 2018
 *      Author: Yuun
 */

#include "HuffmanTree.h"

const int COUNT =5;

HuffmanTree::HuffmanTree() {
}

HuffmanTree::HuffmanTree(unsigned int table[]) {
	for (int i = 0; i < UCHAR_MAX + 1; i++) {
			if (table[i] > 0) {
				unsigned char c = i;
				Node<unsigned int, unsigned char>* temp =
						new Node<unsigned int, unsigned char>(table[i], c);
				priority_queue.Push(temp);
			}
	}
	priority_queue.verify();
	int step = 1;
	while (priority_queue.size() > 1) {
		Node<unsigned int, unsigned char>* left = priority_queue.Pop();
		Node<unsigned int, unsigned char>* right = priority_queue.Pop();

		unsigned int combined_freq = left->priority() + right->priority();
		Node<unsigned int, unsigned char>* combinedNode =
				new Node<unsigned int, unsigned char> (combined_freq, left, right);

		priority_queue.Push(combinedNode);
		cerr << "Structure of tree being updated  on step: " << step << endl;
		step++;
		dump(combinedNode, 0);
	}
	root_ = priority_queue.Pop();
}

HuffmanTree::HuffmanTree(BitReaderStream& reader) {
	unsigned long long code_table[UCHAR_MAX + 1] = {0};
	int lengthOf_codes[UCHAR_MAX + 1] = {0};
	
	root_ = new Node<unsigned int, unsigned char>();
	
	for (int i = 0 ; i < UCHAR_MAX + 1; i++) {
		unsigned char ch = i;
		int binary_length = reader.getByte();
		unsigned long long binary_code = 0;
		if (binary_length > 0) {	
			for (int j = 0; j < binary_length; j++) {
				binary_code = binary_code << 1;
				binary_code = binary_code + reader.getBit();
			}
		root_ = build_Tree(root_, ch, binary_length, binary_code);		
		}
	 	code_table[ch] = binary_code;
		lengthOf_codes[ch] = binary_length;
	}
}


HuffmanTree::~HuffmanTree() {
}

void HuffmanTree::Build_table(unsigned long long* code_table, int* codes_length) {
	cerr << "building code table started " << endl;
	cerr << "length of binary " << "\t" << "binary code" << endl;
	Build_tableHelper(code_table, codes_length, root_, 0, 0);
}


void HuffmanTree::decode_message(BitReaderStream& reader, string puffFile, unsigned int num_of_chars) {
	std::ofstream output;
	output.open(puffFile.c_str());

	if (!output) {
		cerr << "Puff file is not successfully opened" << endl;
	}
	
	for (int i = 0; i < num_of_chars; i++) {
		decode_helper(output, reader, root_);
	}
	output.close();
}


void HuffmanTree::Build_tableHelper(unsigned long long* code_table, int* codes_length,
					 Node<unsigned int, unsigned char>* current,
						 int depth, unsigned int binary_code) {
	if (current->left() == NULL  && current->right() == NULL) {
		unsigned char index = current->data();
		bitset<64> bitsetA(binary_code);
		cerr << (char)index << " " << depth << "\t\t";
		cerr << bitsetA << " " << endl;
		codes_length[index] = depth;
		code_table[index] = binary_code;
	} else {
		unsigned int left_track = (binary_code << 1) + 0;
		Build_tableHelper(code_table, codes_length, current->left(), depth + 1, left_track);
		unsigned int right_track = (binary_code << 1) + 1;
		Build_tableHelper(code_table, codes_length, current->right(), depth + 1, right_track);
	}
}


Node<unsigned int, unsigned char>* HuffmanTree::build_Tree(Node<unsigned int, unsigned char>* current,
							 unsigned char ch, int binary_length,
								 unsigned long long binary_code) {
	if (binary_length == 0) {
		current = new Node<unsigned int, unsigned char>(ch);	
		return current;
	} else {
		if (current == NULL) {
			current = new Node<unsigned int , unsigned char>();
		}
		unsigned long long bit = binary_code & (1 << (binary_length - 1));
		bit = bit >> (binary_length - 1); 
		// when bit is 0, go to left node
		if (bit == 0) {
			current->left() = build_Tree(current->left(), ch, binary_length - 1, binary_code);
		} else {
			current->right() = build_Tree(current->right(), ch, binary_length - 1, binary_code);
		}
	return current;	
	}
}

void HuffmanTree::decode_helper(std::ofstream& output, BitReaderStream& reader,
					 Node<unsigned int, unsigned char>* current) {
	if (current == NULL) {
		return;
	} else {
		if (current->left() == NULL && current->right() == NULL) {
			output.put(current->data());	
		} else {
			unsigned bit = reader.getBit();
			if (bit == 0) {
				decode_helper(output, reader, current->left());
			} else if (bit == 1) {
				decode_helper(output, reader, current->right());
			} else {
				cerr << "messages aren't correctly encoded" << endl;
			}	
		}
	}
}


void HuffmanTree::dump(Node<unsigned int, unsigned char>* current, int level) {
	if (current == NULL) {
		return;
	}

	level += COUNT;
	dump(current->right(), level);
	for (int i = COUNT; i < level; i++) {
		cerr << " ";
	}
	if (current->left() == NULL  && current->right() == NULL) {
		cerr << current->priority() << " "<< char(current->data()) << endl;
	} else {
		cerr << current->priority() << endl;
	}
	dump(current->left(), level);

}

void HuffmanTree::verify(unsigned long long* code_table, int* length_table) {
	this->verify_helper(root_, code_table, length_table, 0, 0);
}

void HuffmanTree::verify_helper(Node<unsigned int, unsigned char>* current,
				 unsigned long long* code_table, int* length_table,
					 unsigned long long code_from_tree, int depth) {
	if (current != NULL) {
		if (current->left() == NULL && current->right() == NULL) {
			unsigned char ch = current->data();
			unsigned long long code = code_table[ch];
			int length_ = length_table[ch];
			if (code != code_from_tree) {
				cerr << "character " << ch << " has a problem: "; 
				cerr << "The code created from the tree is different from the actual code" << endl;
				cerr << "Acutal code: " << code << " code from tree: " << code_from_tree << endl;
				return;
			} 
			if (length_ != depth) {
				cerr << "There is a problem with Tree" << endl;
				cerr << "Three has different depth." << endl;
				cerr << "Problem occured here: " <<  ch << endl;	
				return;
			}
		} else {
			unsigned int c_priority = current->priority();
			unsigned int l_priority = current->left()->priority();
			unsigned int r_priority = current->right()->priority();
			if (c_priority != (l_priority + r_priority)) {
				cerr << "Tree isn't formed correctly" << endl;
				cerr <<  "current node's priority isn't sum of children't priority" << endl;
				cerr << "Problem occurred Here: " << current->data() << endl;
			}
		}
		code_from_tree = code_from_tree << 1;
		verify_helper(current->left(), code_table, length_table, code_from_tree, depth + 1);
		code_from_tree += 1;
		verify_helper(current->right(), code_table, length_table, code_from_tree, depth + 1);
	}	
}

