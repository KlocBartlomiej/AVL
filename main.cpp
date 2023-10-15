#include "AVL.cpp"

int main(){
    auto tree = std::make_unique<AVL<int>>();
    tree->add(1);
    tree->add(3);
    tree->add(2);
    tree->print();
    tree->add(15);
    tree->add(12);
    tree->add(8);
    tree->print();
    tree->remove(15);
    tree->print();
    tree->remove(8);
    tree->print();
    tree->remove(1);
    tree->print();
    return 0;
}