#ifndef AVL_H_DEFINED
#define AVL_H_DEFINED

#include <iostream>
#include <memory>

template<typename T>
struct Node {
	T value;
	int treeHeight = 0;
	std::shared_ptr<Node<T>> parent;
	std::shared_ptr<Node<T>> leftChild;
	std::shared_ptr<Node<T>> rightChild;

	Node(T value) {
		this->value = value;
	}
};

template<typename T>
class AVL {

public:

	void add(T value);
	void remove(T value);
	bool searchIfExists(T value);
	std::shared_ptr<Node<T>> searchAndReturn(T value);
	void print();

private:

	std::shared_ptr<Node<T>> root;
	void addNode(std::shared_ptr<Node<T>> &node, T value);
	void removeNode(std::shared_ptr<Node<T>> &node, T value);
	void checkIfRotateNeeded(std::shared_ptr<Node<T>> &node);
	void updateTreeHeight(std::shared_ptr<Node<T>> &node);
	void rotateLeft(std::shared_ptr<Node<T>> &node);
	void rotateRight(std::shared_ptr<Node<T>> &node);
	void printAll(std::shared_ptr<Node<T>> &node, int level);
	std::shared_ptr<Node<T>> search(std::shared_ptr<Node<T>> &node, T value);
	std::shared_ptr<Node<T>> findBiggestElementInBranch(std::shared_ptr<Node<T>> &node);
};
#endif