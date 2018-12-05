/*
 * Node.h
 *
 *  Created on: May 2, 2018
 *      Author: Yuun
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <functional>

template<typename Priority, typename Data>
class Node{
public:
	Node();
	Node(Data data);
	Node(Priority priority, Data data);
	Node(Priority priority, Node<Priority, Data>* left, Node<Priority, Data>* right);

	const Priority& priority() const;
	Data& data();
	Node<Priority, Data>*& left();
	Node<Priority, Data>*& right();

	bool operator<(Node<Priority, Data>& source);
	bool operator<=(Node<Priority, Data>& source);
	bool operator>(Node<Priority, Data>& source);
	bool operator>=(Node<Priority, Data>& source);
	bool operator==(Node<Priority, Data>& source);
	bool operator!=(Node<Priority, Data>& source);

	friend std::ostream& operator<<(std::ostream& output,
			const Node<Priority, Data>& source) {
		if (source.data_ !=  -1) {
			output << source.data_ << "\t";
		}
		output << source.priority_;
		return output;
	}
private:
	Priority priority_;
	Data data_;
	Node<Priority, Data>* left_;
	Node<Priority, Data>* right_;

};

template<typename Priority, typename Data>
Node<Priority, Data>::Node() : priority_(), data_(-1), left_(NULL), right_(NULL) {
}

template<typename Priority, typename Data>
Node<Priority, Data>::Node(Data data) : priority_(), data_(data), left_(NULL), right_(NULL) {}


template<typename Priority, typename Data>
Node<Priority, Data>::Node(Priority priority, Data data) {
	priority_ = priority;
	data_ = data;
	left_ = NULL;
	right_ = NULL;
}

template<typename Priority, typename Data>
Node<Priority, Data>::Node(Priority priority, Node<Priority, Data>* left, Node<Priority, Data>* right) {
	priority_ = priority;
	left_ = left;
	right_ = right;
}

template<typename Priority, typename Data>
const Priority& Node<Priority, Data>::priority() const {
	return priority_;
}


template<typename Priority, typename Data>
Data& Node<Priority, Data>::data() {
	return data_;
}


template<typename Priority, typename Data>
Node<Priority, Data>*& Node<Priority, Data>::left() {
	return left_;
}


template<typename Priority, typename Data>
Node<Priority, Data>*& Node<Priority, Data>::right() {
	return right_;
}


template<typename Priority, typename Data>
bool Node<Priority, Data>::operator<(Node<Priority, Data>& source) {
	return priority_ < source->priority_;
}

template<typename Priority, typename Data>
bool Node<Priority, Data>::operator>(Node<Priority, Data>& source) {
	return priority_ > source->priority_;
}

template<typename Priority, typename Data>
bool Node<Priority, Data>::operator>=(Node<Priority, Data>& source) {
	return priority_ ==source->priority_ || priority_ > source->priority_;
}

template<typename Priority, typename Data>
bool Node<Priority, Data>::operator<=(Node<Priority, Data>& source) {
	return priority_ ==source->priority_ || priority_ < source->priority_;
}

template<typename Priority, typename Data>
bool Node<Priority, Data>::operator!=(Node<Priority, Data>& source) {
	return priority_ !=source->priority_;
}

template<typename Priority, typename Data>
bool Node<Priority, Data>::operator==(Node<Priority, Data>& source) {
	return priority_ ==source->priority_;
}

template<typename Priority, typename Data>
struct CompareNode: public std::binary_function<Node<Priority, Data>*,
		Node<Priority, Data>*, bool> {
	bool operator()(const Node<Priority, Data>* lhs_Node,
			const Node<Priority, Data>* rhs_Node) {
		return lhs_Node->priority() < rhs_Node->priority();
	}
};

#endif /* SRC_NODE_H_ */
