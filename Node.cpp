///*
// * Node.cpp
// *
// *  Created on: May 2, 2018
// *      Author: Yuun
// */
////
////#include "Node.h"
//
//template<typename T, typename Compare>
//Heap<T, Compare>::Heap() {
//	storage_.push_back(T());
//	size_ = 0;
//}
//
//template<typename T, typename Compare>
//Heap<T, Compare>::~Heap() {}
//
//template<typename T, typename Compare>
//int Heap<T, Compare>::size() {
//	return size_;
//}
//
//template<typename T, typename Compare>
//void Heap<T, Compare>::Push(T item) {
//	storage_.push_back(item);
//	size_++;
//	// bubbling up if necessary
//	int index = size_;
//	while (index > 1) {
//		if (storage_[index/2]->priority() > storage_[index]->priority()) {
//			cerr << "higher property: " << storage_[index/2]->priority() << endl;
//			cerr << "lower property: " << storage_[index]->priority() << endl;
//			cerr << endl;
//			swap(index / 2, index);
//		}
//		index = index / 2;
//	}
//}
//
//
//
//// It returns the address of the Node pointer.
//template<typename T, typename Compare>
//T Heap<T, Compare>::Pop() {
//	if (size_ == 0) {
//		return nullptr;
//	}
//	T min = storage_[1];
//	storage_[1] = storage_[size_];
//	storage_.pop_back();
//	size_--;
//	bubbleDown(1);
//	return min;
//}
//
//template<typename T, typename Compare>
//bool Heap<T, Compare>::is_empty() const {
//	return size_ == 0;
//}
//
//template<typename T, typename Compare>
//void Heap<T, Compare>::print() {
//	for (int i = 1; i <= size_; i++) {
//		cout << storage_[i]->priority() << "\t"<< storage_[i]->data() << endl;
//	}
//}
//
//template<typename T, typename Compare>
//void Heap<T, Compare>::swap(int parent_index, int index) {
//	T temp = storage_[parent_index];
//	storage_[parent_index] = storage_[index];
//	storage_[index] = temp;
//}
//
//template<typename T, typename Compare>
//void Heap<T, Compare>::bubbleDown(int index) {
//	int l_child = index * 2;
//	int smallerPriority_id;
//	if (size_ < l_child) {
//		return;
//	}
//	if (l_child != size_ && storage_[l_child]->priority() > storage_[l_child + 1]->priority()) {
//		l_child++;
//	}
//	smallerPriority_id = l_child;
//	if (storage_[smallerPriority_id]->priority() < storage_[index]->priority()) {
//		swap(index, smallerPriority_id);
//		bubbleDown(smallerPriority_id);
//	}
//
//}
//
//template<typename T, typename Compare>
//void  Heap<T, Compare>::HeapSort(vector<T>& array) {
//	for (int i = 0; i < array.size(); i++) {
//		this->Push(array[i]);
//	}
//
//	for (int i = 0; i < array.size(); i++) {
//		array[i] = this->Pop()->priority();
//	}
//}
