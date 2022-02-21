#pragma once
#include <iostream>
#include <memory>

template<typename T>
struct Node {
	T value;
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

	void addNode(std::unique_ptr<Node<T>> node, T value);
	void checkIfRotateNeeded(std::unique_ptr<Node<T>> node);
	void rotateLeft(std::unique_ptr<Node<T>> node);
	void rotateRight(std::unique_ptr<Node<T>> node);
	void printAll(std::unique_ptr<Node<T>> node, int level);
};

#include "AVL.tpp"
template<typename T>
void AVL<T>::add(T value) {
	if (this->root == nullptr) {
		this->root = std::make_unique<Node<T>>(value);
	}
	else {
		addNode(this->root, value);
	}
}

template<typename T>
void AVL<T>::addNode(std::unique_ptr<Node<T>> node, T value) {
	if (node->value > value) {
		if (node->rightChild == nullptr) {
			node->rightChild = std::make_unique<Node<T>>(value);
		}
		else {
			addNode(node->rightChild, value);
		}
	}
	else if (node < value) {
		if (node->leftChild == nullptr) {
			node->leftChild = std::make_unique<Node<T>>(value);
		}
		else {
			addNode(node->leftChild, value);
		}
	}
	else {
		std::cout << "There is an element with value: " << value << " already in the tree." << std::endl;
	}
}

template<typename T>
void AVL<T>::remove(T value) {

}

template<typename T>
bool AVL<T>::search(T value) {

}

template<typename T>
void AVL<T>::checkIfRotateNeeded(std::unique_ptr<Node<T>> node) {

}

template<typename T>
void AVL<T>::rotateLeft(std::unique_ptr<Node<T>> node) {

}

template<typename T>
void AVL<T>::rotateRight(std::unique_ptr<Node<T>> node) {

}

template<typename T>
void AVL<T>::print() {
	if (this->root != nullptr) {
		printAll(this.root,0);
	}
}

template<typename T>
void AVL<T>::printAll(std::unique_ptr<Node<T>> node, int level) {
	if (node->leftChild != nullptr) {
		printAll(node->leftChild, level++);
		for (int i = 0; i < level; i++) {
			std::cout << "    ";
		}
		std::cout << node->leftChild->value << std::endl;
	}
	std::cout << node->value << std::endl;
	if (node->rightChild != nullptr) {
		printAll(node->rightChild, level++);
		for (int i = 0; i < level; i++) {
			std::cout << "    ";
		}
		std::cout << node->rightChild->value << std::endl;
	}
}
