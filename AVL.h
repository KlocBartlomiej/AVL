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
	/*~Node() { TODO: fix issue with not properly released memory in destructor during removing one node from the tree
		delete parent;
		delete rightChild;
		delete leftChild;
	}*/
};

template<typename T>
class AVL {

public:

	~AVL();/* = default;
	AVL(AVL conts&) = delete;
	AVL(AVL&&) = delete;
	AVL operator=(AVL const&) = delete;
	AVL operator=(AVL&&) = delete;*/
	void add(T value);
	void remove(T value);
	bool search(T value);
	void print();

private:

	Node<T>* root; //TODO: Change it to the smart ptr, so it don't need to be released with delete (no need for destructor)
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