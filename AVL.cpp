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
		node->right++;
		if (node->rightChild == nullptr) {
			node->rightChild = std::make_shared<Node<T>>(value);
			node->rightChild->parrent = node;
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->rightChild, value);
		}
	}
	else if (node->value < value) {
		node->left++;
		if (node->leftChild == nullptr) {
			node->leftChild = std::make_shared<Node<T>>(value);
			node->leftChild->parrent = node;
			checkIfRotateNeeded(node);
		}
		else {
			addNode(node->leftChild, value);
		}
	}
	else {
		std::cout << "There is an element with value: " << value << " already in the tree." << std::endl;
		if(node->parrent != nullptr) {
			cleaningLeftRightWeight(node->parrent, node);
		}
	}
}
template<typename T>
void AVL<T>::cleaningLeftRightWeight(std::shared_ptr<Node<T>> &parrent, std::shared_ptr<Node<T>> &node) {
	if(parrent->leftChild == node) {
		parrent->left--;
	} else {
		parrent->right--;
	}
	if(parrent->parrent != nullptr) {
		cleaningLeftRightWeight(parrent->parrent, parrent);
	}
}

template<typename T>
void AVL<T>::remove(T value) {
	auto node = search(root, value);
	if(node != nullptr) {
		if(node->leftChild == nullptr && node->rightChild == nullptr) {
			if(node->parrent->leftChild->value == node->value){
				node->parrent->leftChild = nullptr;
			} else {
				node->parrent->rightChild = nullptr;
			}
		} else if(node->leftChild != nullptr) {
			if(node->parrent->leftChild->value == node->value){
				node->parrent->leftChild = node->leftChild;
			} else {
				node->parrent->rightChild = node->leftChild;
			}
			node->leftChild->parrent = node->parrent;
		} else if(node->rightChild != nullptr){
			if(node->parrent->leftChild->value == node->value){
				node->parrent->leftChild = node->rightChild;
			} else {
				node->parrent->rightChild = node->rightChild;
			}
			node->rightChild->parrent = node->parrent;
		} else {
			auto nodeToReplace = findBiggestElementInBranch(node->rightChild);
			nodeToReplace->leftChild = node->leftChild;
			nodeToReplace->leftChild->parrent = nodeToReplace;
			nodeToReplace->rightChild = node->rightChild;
			
			nodeToReplace->rightChild->parrent = nodeToReplace;

			
			nodeToReplace->parrent->leftChild = nullptr;
			nodeToReplace->parrent = node->parrent;
			if(node->parrent->leftChild->value == node->value){
				nodeToReplace->parrent->leftChild = nodeToReplace;
			} else {
				nodeToReplace->parrent->rightChild = nodeToReplace;
			}
		}
		std::cout << "Element with value " << value << " removed successfully." << std::endl;
	} else {
		std::cout << "Couldn't find an element to remove." << std::endl;
	}
}

template<typename T>
std::shared_ptr<Node<T>> AVL<T>::findBiggestElementInBranch(std::shared_ptr<Node<T>> &node) {
	if(node->leftChild == nullptr){
		return node;
	} else {
		return findBiggestElementInBranch(node->leftChild);
	}
}

template<typename T>
bool AVL<T>::search(T value) {
	if (root != nullptr){
		return search(root, value) != nullptr;
	} else {
		std::cout << "There is no elemnt with value " << value << " in the tree." << std::endl;
		return false;
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
		std::cout << "There is no elemnt with value " << value << " in the tree." << std::endl;
		return nullptr;
	}
}

template<typename T>
void AVL<T>::checkIfRotateNeeded(std::shared_ptr<Node<T>> &node) {
	if (node->parrent != nullptr) {
		checkIfRotateNeeded(node->parrent);
	}
}

template<typename T>
void AVL<T>::rotateLeft(std::shared_ptr<Node<T>> &node) {

}

template<typename T>
void AVL<T>::rotateRight(std::shared_ptr<Node<T>> &node) {

}

template<typename T>
void AVL<T>::print() {
	if (this->root != nullptr) {
		printAll(this->root,0);
	}
}

template<typename T>
void AVL<T>::printAll(std::shared_ptr<Node<T>> &node, int level) {
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
