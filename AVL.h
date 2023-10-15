#ifndef AVL_H_DEFINED
#define AVL_H_DEFINED

#include <iostream>
#include <memory>

template<typename T>
struct Node {
	T value;
	int treeHeight = 0;
	Node<T>* parent = nullptr;
	Node<T>* rightChild = nullptr;
	Node<T>* leftChild = nullptr;

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

	Node<T>* root;
	void addNode(Node<T>* node, T value);
	void removeNode(Node<T>* node, T value);
	void checkIfRotateNeeded(Node<T>* node);
	void updateTreeHeight(Node<T>* node);
	void rotateLeft(Node<T>* node);
	void rotateRight(Node<T>* node);
	void printAll(Node<T>* node, int level);
	Node<T>* search(Node<T>* node, T value);
	Node<T>* findBiggestElementInBranch(Node<T>* node);
};
#endif