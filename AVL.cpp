#include "AVL.h"

template<typename T>
void AVL<T>::add(T value) {
	if (this->root == nullptr) {
		this->root = std::make_shared<Node<T>>(value);
	}
	else {
		addNode(this->root, value);
	}
}

template<typename T>
void AVL<T>::addNode(std::shared_ptr<Node<T>> &node, T value) {
	if (node->value > value) {
		if (node->rightChild == nullptr) {
			node->rightChild = std::make_shared<Node<T>>(value);
			node->rightChild->parent = node;
			updateTreeHeight(node);
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->rightChild, value);
		}
	}
	else if (node->value < value) {
		if (node->leftChild == nullptr) {
			node->leftChild = std::make_shared<Node<T>>(value);
			node->leftChild->parent = node;
			updateTreeHeight(node);
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->leftChild, value);
		}
	}
	else {
		std::cout << "There is an element with value: " << value << " already in the tree.\n\r";
	}
}

template<typename T>
void AVL<T>::remove(T value) {
	if(root != nullptr){
		removeNode(root,value);
	}
}

template<typename T>
void AVL<T>::removeNode(std::shared_ptr<Node<T>> &startingNode, T value) {
	auto node = search(startingNode, value);
	if(node != nullptr) {
		if(node->leftChild == nullptr && node->rightChild == nullptr) {
			if(node->parent != nullptr) {
				if(node->parent->leftChild != nullptr && node->parent->leftChild->value == node->value) {
					node->parent->leftChild = nullptr;
				} else {
					node->parent->rightChild = nullptr;
				}
				updateTreeHeight(node->parent);
				checkIfRotateNeeded(node->parent);
				node->parent = nullptr;
			} else {
				root = nullptr;
			}
		} else if(node->leftChild != nullptr && node->rightChild == nullptr) {
			if(node->parent != nullptr) {
				if(node->parent->leftChild != nullptr && node->parent->leftChild->value == node->value) {
					node->parent->leftChild = node->leftChild;
				} else {
					node->parent->rightChild = node->leftChild;
				}
			node->leftChild->parent = node->parent;
			node->leftChild = nullptr;
			updateTreeHeight(node->parent);
			checkIfRotateNeeded(node->parent);
			node->parent = nullptr;
			} else {
				node->leftChild->parent = nullptr;
				root = node->leftChild;
			}
		} else if(node->leftChild == nullptr && node->rightChild != nullptr) {
			if(node->parent != nullptr) {
				if(node->parent->leftChild != nullptr && node->parent->leftChild->value == node->value) {
					node->parent->leftChild = node->rightChild;
				} else {
					node->parent->rightChild = node->rightChild;
				}
			node->rightChild->parent = node->parent;
			node->rightChild = nullptr;
			updateTreeHeight(node->parent);
			checkIfRotateNeeded(node->parent);
			node->parent = nullptr;
			} else {
				node->rightChild->parent = nullptr;
				root = node->rightChild;
			}
		} else {
			auto nodeToReplace = findBiggestElementInBranch(node->leftChild);
			node->value = nodeToReplace->value;
			removeNode(node->leftChild,nodeToReplace->value);
		}
	}
}

template<typename T>
std::shared_ptr<Node<T>> AVL<T>::findBiggestElementInBranch(std::shared_ptr<Node<T>> &node) {
	if(node->rightChild == nullptr) {
		return node;
	} else {
		return findBiggestElementInBranch(node->rightChild);
	}
}

template<typename T>
bool AVL<T>::searchIfExists(T value) {
	if (root != nullptr) {
		return search(root, value) != nullptr;
	} else {
		std::cout<<"There is no elemnt with value "<<value<<" in the tree.\n\r";
		return false;
	}
}

template<typename T>
std::shared_ptr<Node<T>> AVL<T>::searchAndReturn(T value) {
	if (root != nullptr) {
		return search(root, value);
	} else {
		std::cout<<"There is no elemnt with value "<<value<<" in the tree.\n\r";
		return nullptr;
	}
}

template<typename T>
std::shared_ptr<Node<T>> AVL<T>::search(std::shared_ptr<Node<T>> &node, T value) {
	if (node->rightChild != nullptr && node->value > value) {
		return search(node->rightChild, value);
	}
	else if (node->leftChild != nullptr && node->value < value) {
		return search(node->leftChild, value);
	}
	else if (node->value == value) {
		return node;
	} else {
		std::cout<<"There is no elemnt with value "<<value<<" in the tree.\n\r";
		return nullptr;
	}
}

template<typename T>
void AVL<T>::updateTreeHeight(std::shared_ptr<Node<T>> &node) {
	if(node->leftChild != nullptr && node->rightChild != nullptr){
		if(node->leftChild->treeHeight > node->rightChild->treeHeight){
			node->treeHeight = node->leftChild->treeHeight + 1;
		} else {
			node->treeHeight = node->rightChild->treeHeight + 1;
		}
	} else if(node->leftChild != nullptr) {
		node->treeHeight = node->leftChild->treeHeight + 1;
	} else if(node->rightChild != nullptr) {
		node->treeHeight = node->rightChild->treeHeight + 1;
	} else {
		node->treeHeight = 0;
	}
	if(node != root) {
		updateTreeHeight(node->parent);
	}
}

template<typename T>
void AVL<T>::checkIfRotateNeeded(std::shared_ptr<Node<T>> &node) {
	// if(node->leftChild != nullptr && node->rightChild == nullptr) {
	// 	if(node->leftSubtreeHeight == 2){
	// 		if(node->leftChild->leftChild == nullptr) {
	// 			rotateLeft(node->leftChild);
	// 		}
	// 		rotateRight(node);
	// 	}
	// } else if(node->leftChild == nullptr && node->rightChild != nullptr) {
	// 	if(node->rightSubtreeHeight == 2){
	// 		if(node->rightChild->rightChild == nullptr) {
	// 			rotateRight(node->rightChild);
	// 		}
	// 		rotateLeft(node);
	// 	}
	// } else if(node->leftChild != nullptr && node->rightChild != nullptr) {
	// 	if(node->rightSubtreeHeight + 2 == node->leftSubtreeHeight){
	// 		if(node->rightChild->rightChild == nullptr) {
	// 			rotateRight(node->rightChild);
	// 		}
	// 		rotateLeft(node);
	// 	} else if(node->leftSubtreeHeight + 2 == node->rightSubtreeHeight) {
	// 		if(node->leftChild->leftChild == nullptr) {
	// 			rotateLeft(node->leftChild);
	// 		}
	// 		rotateRight(node);
	// 	}
	// }
	// if (node->parent != nullptr) {
	// 	checkIfRotateNeeded(node->parent);
	// }
}

template<typename T>
void AVL<T>::rotateRight(std::shared_ptr<Node<T>>& node) {
	auto son = node->leftChild;
	node->parent.swap(son->parent);
	if (son->rightChild) {
		node->parent.swap(son->rightChild);
		node->parent.swap(node->leftChild);
	}
	else {
		node->parent.swap(son->rightChild->parent);
		node->leftChild.swap(son->rightChild);
		son->rightChild = node;
	}	
	if (node == root) {
		root = son;
	}
}

template<typename T>
void AVL<T>::rotateLeft(std::shared_ptr<Node<T>>& node) {
	auto son = node->rightChild;
	node->parent.swap(son->parent);
	if (son->leftChild) {
		node->parent.swap(son->leftChild);
		node->parent.swap(node->rightChild);
	}
	else {
		node->parent.swap(son->leftChild->parent);
		node->rightChild.swap(son->leftChild);
		son->leftChild = node;
	}
	if (node == root) {
		root = son;
	}
}

template<typename T>
void AVL<T>::print() {
	if (this->root != nullptr) {
		printAll(this->root,0);
	}
	std::cout<<"\n\r-----\n\r";
}

template<typename T>
void AVL<T>::printAll(std::shared_ptr<Node<T>> &node, int level) {
	if (node->leftChild != nullptr) {
		printAll(node->leftChild, level+1);
	}
	for (int i = 0; i < level; i++) {
		std::cout<<"    ";
	}
	std::cout<<node->value<<","<<node->treeHeight<<"\n\r";
	if (node->rightChild != nullptr) {
		printAll(node->rightChild, level+1);
	}
}
