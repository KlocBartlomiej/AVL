#include "AVL.h"

int main(){
    auto tree = std::make_unique<AVL<int>>();
    tree->add(5);
    tree->add(1);
    tree->add(3);
    tree->add(8);
    tree->print();
    return 0;
}