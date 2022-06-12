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
	} else if(parrent->rightChild == node) {
		parrent->right--;
	}
	if(parrent->parrent != nullptr) {
		cleaningLeftRightWeight(parrent->parrent, parrent);
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
			if(node->parrent != nullptr) {
				if(node->parrent->leftChild != nullptr && node->parrent->leftChild->value == node->value) {
					node->parrent->leftChild = nullptr;
					node->parrent->left--;
				} else {
					node->parrent->rightChild = nullptr;
					node->parrent->right--;
				}
				cleaningLeftRightWeight(node->parrent,node);
				checkIfRotateNeeded(node->parrent);
			} else {
				root = nullptr;
			}
		} else if(node->leftChild != nullptr && node->rightChild == nullptr) {
			if(node->parrent != nullptr) {
				if(node->parrent->leftChild != nullptr && node->parrent->leftChild->value == node->value) {
					node->parrent->leftChild = node->leftChild;
					node->parrent->left--;
				} else {
					node->parrent->rightChild = node->leftChild;
					node->parrent->right--;
				}
			node->leftChild->parrent = node->parrent;
			cleaningLeftRightWeight(node->parrent,node);
			checkIfRotateNeeded(node->parrent);
			} else {
				node->leftChild->parrent = nullptr;
				root = node->leftChild;
			}
		} else if(node->leftChild == nullptr && node->rightChild != nullptr) {
			if(node->parrent != nullptr) {
				if(node->parrent->leftChild != nullptr && node->parrent->leftChild->value == node->value) {
					node->parrent->leftChild = node->rightChild;
					node->parrent->left--;
				} else {
					node->parrent->rightChild = node->rightChild;
					node->parrent->right--;
				}
			node->rightChild->parrent = node->parrent;
			cleaningLeftRightWeight(node->parrent,node);
			checkIfRotateNeeded(node->parrent);
			} else {
				node->rightChild->parrent = nullptr;
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
bool AVL<T>::search(T value) {
	if (root != nullptr) {
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
	if(node->leftChild != nullptr && node->rightChild == nullptr) {
		if(node->left == 2){
			if(node->leftChild->leftChild == nullptr) {
				rotateLeft(node->leftChild);
			}
			rotateRight(node);
		}
	} else if(node->leftChild == nullptr && node->rightChild != nullptr) {
		if(node->right == 2){
			if(node->rightChild->rightChild == nullptr) {
				rotateRight(node->rightChild);
			}
			rotateLeft(node);
		}
	} else if(node->leftChild != nullptr && node->rightChild != nullptr) {
		if(node->right + 2 == node->left){
			if(node->rightChild->rightChild == nullptr) {
				rotateRight(node->rightChild);
			}
			rotateLeft(node);
		} else if(node->left + 2 == node->right) {
			if(node->leftChild->leftChild == nullptr) {
				rotateLeft(node->leftChild);
			}
			rotateRight(node);
		}
	}
	pomoc(node);
	if (node->parrent != nullptr) {
		checkIfRotateNeeded(node->parrent);
	}
}

template<typename T>
void pomoc(std::shared_ptr<Node<T>> &node) {
	std::cout<<"-----"<<std::endl;
	if(node->leftChild != nullptr){
		std::cout<<"node->leftChild: "<<node->leftChild->value<<std::endl;
	} else {
		std::cout<<"node->leftChild: nullptr"<<std::endl;
	}
	if(node->rightChild != nullptr){
		std::cout<<"node->rightChild: "<<node->rightChild->value<<std::endl;
	} else {
		std::cout<<"node->rightChild: nullptr"<<std::endl;
	}
	if(node->parrent != nullptr){
		std::cout<<"node->parrent: "<<node->parrent->value<<std::endl;
	} else {
		std::cout<<"node->parrent: nullptr"<<std::endl;
	}
	std::cout<<"node: "<<node->value<<std::endl;
}

template<typename T>
void AVL<T>::rotateRight(std::shared_ptr<Node<T>>& node) {
	auto son = node->leftChild;
	node->parrent.swap(son->parrent);
	if (son->rightChild) {
		node->parrent.swap(son->rightChild);
		node->parrent.swap(node->leftChild);
	}
	else {
		node->parrent.swap(son->rightChild->parrent);
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
	node->parrent.swap(son->parrent);
	if (son->leftChild) {
		node->parrent.swap(son->leftChild);
		node->parrent.swap(node->rightChild);
	}
	else {
		node->parrent.swap(son->leftChild->parrent);
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
	std::cout<<std::endl<<"-----"<<std::endl;
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
