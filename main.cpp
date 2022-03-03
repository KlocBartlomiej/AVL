#include "AVL.cpp"

int main(){
    auto tree = std::make_unique<AVL<int>>();
    tree->add(10);
    tree->add(5);
    tree->add(15);
    tree->add(2);
    tree->add(4);
    tree->add(14);
    tree->add(18);
    tree->print();
    tree->remove(10);
    tree->print();
    tree->remove(2);
    tree->print();
    tree->remove(5);
    tree->print();
    tree->remove(15);
    tree->print();
    tree->remove(14);
    tree->print();
    tree->remove(18);
    tree->print();
    tree->remove(4);
    tree->print();
    return 0;
}