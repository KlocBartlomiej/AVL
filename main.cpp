#include "AVL.cpp"

int main(){
    auto tree = std::make_unique<AVL<int>>();
    tree->search(5);
    tree->add(5);
    tree->search(5);
    tree->add(13);
    tree->add(9);
    tree->add(15);
    tree->add(2);
    tree->add(1);
    tree->add(3);
    tree->add(3);
    tree->add(7);
    tree->add(8);
    tree->add(6);
    tree->add(11);
    tree->add(12);
    tree->add(10);
    tree->print();
    if(tree->search(999)){
        std::cout << "element 999 is in the tree" << std::endl;
    }
    if(tree->search(8)){
        std::cout << "element 8 is in the tree" << std::endl;
    }
    return 0;
}