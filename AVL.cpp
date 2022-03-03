#include "AVL.h"

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
void AVL<T>::addNode(std::unique_ptr<Node<T>> &node, T value) {
	if (node->value > value) {
		node->right++;
		if (node->rightChild == nullptr) {
			node->rightChild = std::make_unique<Node<T>>(value);
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->rightChild, value);
		}
	}
	else if (node->value < value) {
		node->left++;
		if (node->leftChild == nullptr) {
			node->leftChild = std::make_unique<Node<T>>(value);
			checkIfRotateNeeded(node);
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
void AVL<T>::checkIfRotateNeeded(std::unique_ptr<Node<T>> &node) {
	if (node->parrent != nullptr) {
		checkIfRotateNeeded(Node->parrent);
	}
}

template<typename T>
void AVL<T>::rotateLeft(std::unique_ptr<Node<T>> &node) {

}

template<typename T>
void AVL<T>::rotateRight(std::unique_ptr<Node<T>> &node) {

}

template<typename T>
void AVL<T>::print() {
	if (this->root != nullptr) {
		printAll(this->root,0);
	}
}

template<typename T>
void AVL<T>::printAll(std::unique_ptr<Node<T>> &node, int level) {
	if (node->leftChild != nullptr) {
		printAll(node->leftChild, level+1);
	}
	for (int i = 0; i < level; i++) {
		std::cout << "    ";
	}
	std::cout << node->value <<"," << node->left << "," << node->right << std::endl;
	if (node->rightChild != nullptr) {
		printAll(node->rightChild, level+1);
	}
}
