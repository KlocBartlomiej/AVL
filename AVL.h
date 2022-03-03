#ifndef AVL_H_DEFINED
#define AVL_H_DEFINED

#include <iostream>
#include <memory>

template<typename T>
struct Node {
	T value;
	int left = 0;
	int right = 0;
	std::unique_ptr<Node<T>> parrent;
	std::unique_ptr<Node<T>> leftChild;
	std::unique_ptr<Node<T>> rightChild;

	Node(T value) {
		this->value = value;
	}
};

template<typename T>
class AVL {

public:

	void add(T value);
	void remove(T value);
	bool search(T value);
	void print();

private:

	std::unique_ptr<Node<T>> root;

	void addNode(std::unique_ptr<Node<T>> &node, T value);
	void checkIfRotateNeeded(std::unique_ptr<Node<T>> &node);
	void rotateLeft(std::unique_ptr<Node<T>> &node);
	void rotateRight(std::unique_ptr<Node<T>> &node);
	void printAll(std::unique_ptr<Node<T>> &node, int level);
};
#endif