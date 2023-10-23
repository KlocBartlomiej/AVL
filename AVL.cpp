#include "AVL.h"

template<typename T>
AVL<T>::~AVL() {
	delete root;
}

template<typename T>
void AVL<T>::add(T value) {
	if (this->root == nullptr) {
		this->root = new Node<T>(value);
	}
	else {
		addNode(this->root, value);
	}
}

template<typename T>
void AVL<T>::addNode(Node<T>* node, T value) {
	if (node->value > value) {
		if (node->leftChild == nullptr) {
			node->leftChild = new Node<T>(value);
			node->leftChild->parent = node;
			updateTreeHeight(node);
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->leftChild, value);
		}
	}
	else if (node->value < value) {
		if (node->rightChild == nullptr) {
			node->rightChild = new Node<T>(value);
			node->rightChild->parent = node;
			updateTreeHeight(node);
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->rightChild, value);
		}
	}
	else {
		std::cout << "There is an element with value: " << value << " already in the tree.\n\r";
	}
}

template<typename T>
void AVL<T>::remove(T value) {
	if (root != nullptr) {
		removeNode(root, value);
	}
}

template<typename T>
void AVL<T>::removeNode(Node<T>* startingNode, T value) {
	auto node = search(startingNode, value);
	if (node == nullptr) {
		std::cout << "There is no element with value " << value << " to remove.\n\r";
		return;
	}
	if (node->rightChild == nullptr && node->leftChild == nullptr) {
		if (node->parent != nullptr) {
			if (node->parent->rightChild != nullptr && node->parent->rightChild->value == node->value) {
				node->parent->rightChild = nullptr;
			}
			else {
				node->parent->leftChild = nullptr;
			}
			updateTreeHeight(node->parent);
			checkIfRotateNeeded(node->parent);
			node->parent = nullptr;
		}
		else {
			root = nullptr;
		}
		delete node;
	}
	else if (node->rightChild != nullptr && node->leftChild == nullptr) {
		if (node->parent != nullptr) {
			if (node->parent->rightChild != nullptr && node->parent->rightChild->value == node->value) {
				node->parent->rightChild = node->rightChild;
			}
			else {
				node->parent->leftChild = node->rightChild;
			}
			node->rightChild->parent = node->parent;
			node->rightChild = nullptr;
			updateTreeHeight(node->parent);
			checkIfRotateNeeded(node->parent);
			node->parent = nullptr;
		}
		else {
			node->rightChild->parent = nullptr;
			root = node->rightChild;
		}
		delete node;
	}
	else if (node->rightChild == nullptr && node->leftChild != nullptr) {
		if (node->parent != nullptr) {
			if (node->parent->rightChild != nullptr && node->parent->rightChild->value == node->value) {
				node->parent->rightChild = node->leftChild;
			}
			else {
				node->parent->leftChild = node->leftChild;
			}
			node->leftChild->parent = node->parent;
			node->leftChild = nullptr;
			updateTreeHeight(node->parent);
			checkIfRotateNeeded(node->parent);
			node->parent = nullptr;
		}
		else {
			node->leftChild->parent = nullptr;
			root = node->leftChild;
		}
		delete node;
	}
	else {
		auto nodeToReplace = findBiggestElementInBranch(node->rightChild);
		node->value = nodeToReplace->value;
		removeNode(node->rightChild, nodeToReplace->value);
	}
}

template<typename T>
Node<T>* AVL<T>::findBiggestElementInBranch(Node<T>* node) {
	if (node->leftChild == nullptr) {
		return node;
	}
	else {
		return findBiggestElementInBranch(node->leftChild);
	}
}

template<typename T>
bool AVL<T>::search(T value) {
	if (root != nullptr) {
		return search(root, value) != nullptr;
	}
	else {
		std::cout << "There is no elemnt with value " << value << " in the tree.\n\r";
		return false;
	}
}

template<typename T>
Node<T>* AVL<T>::search(Node<T>* node, T value) {
	if (node->leftChild != nullptr && node->value > value) {
		return search(node->leftChild, value);
	}
	else if (node->rightChild != nullptr && node->value < value) {
		return search(node->rightChild, value);
	}
	else if (node->value == value) {
		return node;
	}
	else {
		std::cout << "There is no elemnt with value " << value << " in the tree.\n\r";
		return nullptr;
	}
}

template<typename T>
void AVL<T>::updateTreeHeight(Node<T>* node) {
	if (node->rightChild != nullptr && node->leftChild != nullptr) {
		if (node->rightChild->treeHeight > node->leftChild->treeHeight) {
			node->treeHeight = node->rightChild->treeHeight + 1;
		}
		else {
			node->treeHeight = node->leftChild->treeHeight + 1;
		}
	}
	else if (node->rightChild != nullptr) {
		node->treeHeight = node->rightChild->treeHeight + 1;
	}
	else if (node->leftChild != nullptr) {
		node->treeHeight = node->leftChild->treeHeight + 1;
	}
	else {
		node->treeHeight = 0;
	}
	if (node != root) {
		updateTreeHeight(node->parent);
	}
}

template<typename T>
void AVL<T>::checkIfRotateNeeded(Node<T>* node) {
	if (node->rightChild != nullptr && node->leftChild == nullptr) {
		if (node->treeHeight == 2) {
			if (node->rightChild->rightChild == nullptr) {
				rotateRight(node->rightChild);
			}
			rotateLeft(node);
		}
	}
	else if (node->rightChild == nullptr && node->leftChild != nullptr) {
		if (node->treeHeight == 2) {
			if (node->leftChild->leftChild == nullptr) {
				rotateLeft(node->leftChild);
			}
			rotateRight(node);
		}
	}
	else if (node->rightChild != nullptr && node->leftChild != nullptr) {
		if (node->leftChild->treeHeight + 2 == node->rightChild->treeHeight) {
			if (node->rightChild->rightChild == nullptr ||
				(node->rightChild->leftChild != nullptr &&
					node->rightChild->leftChild->treeHeight > node->rightChild->rightChild->treeHeight)) {
				rotateRight(node->rightChild);
			}
			rotateLeft(node);
		}
		else if (node->rightChild->treeHeight + 2 == node->leftChild->treeHeight) {
			if (node->leftChild->leftChild == nullptr ||
				(node->leftChild->rightChild != nullptr &&
					node->leftChild->leftChild->treeHeight < node->leftChild->rightChild->treeHeight)) {
				rotateLeft(node->leftChild);
			}
			rotateRight(node);
		}
	}
	if (node->parent != nullptr) {
		checkIfRotateNeeded(node->parent);
	}
}

template<typename T>
void AVL<T>::rotateRight(Node<T>* node) {
	auto child = node->leftChild;
	node->leftChild = child->rightChild;
	if (child->rightChild != nullptr) {
		child->rightChild->parent = node;
	}
	child->rightChild = node;
	if (node->parent == nullptr) {
		root = child;
		child->parent = nullptr;
	}
	else {
		if (node->parent->leftChild == node) {
			node->parent->leftChild = child;
		}
		else {
			node->parent->rightChild = child;
		}
		child->parent = node->parent;
	}
	node->parent = child;
	updateTreeHeight(node);
}

template<typename T>
void AVL<T>::rotateLeft(Node<T>* node) {
	auto child = node->rightChild;
	node->rightChild = child->leftChild;
	if (child->leftChild != nullptr) {
		child->leftChild->parent = node;
	}
	child->leftChild = node;
	if (node == root) {
		root = child;
		child->parent = nullptr;
	}
	else {
		if (node->parent->leftChild == node) {
			node->parent->leftChild = child;
		}
		else {
			node->parent->rightChild = child;
		}
		child->parent = node->parent;
	}
	node->parent = child;
	updateTreeHeight(node);
}

template<typename T>
void AVL<T>::print() {
	if (this->root != nullptr) {
		printAll(this->root, 0);
	}
	std::cout << "\n\r-----\n\r";
}

template<typename T>
void AVL<T>::printAll(Node<T>* node, int level) {
	if (node->rightChild != nullptr) {
		printAll(node->rightChild, level + 1);
	}
	for (int i = 0; i < level; i++) {
		std::cout << "    ";
	}
	std::cout << "value: " << node->value << ", ";
	if (node->rightChild)
		std::cout << "right: " << node->rightChild->value << ", ";
	if (node->leftChild)
		std::cout << "left: " << node->leftChild->value << ", ";
	std::cout << "height: " << node->treeHeight << "\n\r";
	if (node->leftChild != nullptr) {
		printAll(node->leftChild, level + 1);
	}
}