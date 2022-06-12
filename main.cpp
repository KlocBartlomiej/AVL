#include "AVL.cpp"

int main(){
    auto tree = std::make_unique<AVL<int>>();
    tree->add(1);
    tree->add(2);
    tree->add(3);
    tree->print();
    return 0;
}