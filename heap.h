/*
 * Heap.h
 *
 *  Created on: Apr 27, 2018
 *      Author: Yuun
 */

#ifndef SRC_HEAP_H_
#define SRC_HEAP_H_

#include "Node.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T, typename Compare=std::less<T> >
class Heap {
private:
	int size_;
	vector<T> storage_;
	Compare compare;

	void swap(int idx1, int idx2);
	void HeapSort(vector<T>& array);
	void print();

	

public:
	Heap();
	virtual ~Heap();

	void Push(T item);
	T Pop();
	bool is_empty() const;
	int size();
	
	void verify();
};

template<typename T, typename Compare>
Heap<T, Compare>::Heap() {
	storage_.push_back(T());
	size_ = 0;
}

template<typename T, typename Compare>
Heap<T, Compare>::~Heap() {}

template<typename T, typename Compare>
int Heap<T, Compare>::size() {
	return size_;
}

template<typename T, typename Compare>
void Heap<T, Compare>::Push(T item) {
	storage_.push_back(item);
	size_++;
	int index = size_;
	while (index > 1) {
		int parent_idx = index / 2;
		T child = storage_[index];
		T parent = storage_[parent_idx];
		if (compare(child, parent)) {
			swap(index, parent_idx);
			index = index / 2;
		} else {
			index = -1;
		}
	}
}

// It returns the address of the Node pointer.
template<typename T, typename Compare>
T Heap<T, Compare>::Pop() {
	// check if size = 0 or not?
	T min = storage_[1];
	storage_[1] = storage_[size_];
	storage_.pop_back();
	size_--;

	int index = 1;
	while (index < size_ / 2 && index > 0) {
		int l_child = index * 2;
		int r_child = index * 2 + 1;
		T current = storage_[index];
		T left = storage_[l_child];
		T right = storage_[r_child];
		if (compare(left, right)) {
			if (compare(left, current)) {
				swap(l_child, index);
				index = l_child;
			} else {
				index = -1;
			}
		} else {
			if (compare(right, current)) {
				swap(r_child, index);
				index = r_child;
			} else {
				index = -1;
			}
		}
	}
	return min;
}

template<typename T, typename Compare>
bool Heap<T, Compare>::is_empty() const {
	return size_ == 0;
}

template<typename T, typename Compare>
void Heap<T, Compare>::print() {
	for (int i = 1; i <= size_; i++) {
		cerr << storage_[i] << endl;
	}
}

template<typename T, typename Compare>
void Heap<T, Compare>::swap(int idx1, int idx2) {
	T temp = storage_[idx1];
	storage_[idx1] = storage_[idx2];
	storage_[idx2] = temp;
}

template<typename T, typename Compare>
void  Heap<T, Compare>::HeapSort(vector<T>& array) {
	for (int i = 0; i < array.size(); i++) {
		this->Push(array[i]);
	}

	for (int i = 0; i < array.size(); i++) {
		array[i] = this->Pop();
	}
}


// function to verify the heap property
template<typename T, typename Compare>
void  Heap<T, Compare>::verify() {

	cerr << "Heap property check" << endl;

	for (int i = 1; i < size_/2; i++) {
		T parent = storage_[i];
		T left = storage_[i*2];
		T right = storage_[i*2 + 1];
		if (compare(left, parent) || compare(right, parent)) {
			cerr << "Heap Property is violated here."  << endl;
			return;
		}
	}
	if (size_ % 2 == 1) {
		T parent = storage_[size_ / 2];
		T last_child = storage_[size_ - 1];
		if (compare(last_child, parent)) {
			cerr<< "Heap property is violated here" << endl;
			return;
		}
		
	}
	cerr << "Heap property is not violated" << endl;
}



#endif /* SRC_HEAP_H_ */





