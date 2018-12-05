#! /bin/bash


g++ -o huff driver.cpp BitWriterStream.cpp BitReaderStream.cpp HuffmanTree.cpp
g++ -o puff decode.cpp BitWriterStream.cpp BitReaderStream.cpp HuffmanTree.cpp
