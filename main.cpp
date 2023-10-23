#include "AVL.cpp"

int main() {
    auto tree = std::make_unique<AVL<int>>();
    //TODO: Add google test, so every case will be tested separately. It will reduce time to check what went wrong.
     tree->add(10);
     tree->add(11);
     tree->add(12);
     tree->add(13);
     tree->add(14);
     tree->add(15);
     tree->add(16);
     tree->add(17);
     tree->add(18);
     tree->add(19);
     tree->add(20);
     tree->add(21);
     tree->add(22);
     tree->add(23);
     tree->add(24);
     tree->add(25);
     tree->add(26);
     tree->add(27);
     tree->add(28);
     tree->add(29);
     tree->add(30);
     tree->add(1);
     tree->add(2);
     tree->add(3);
     tree->add(4);
     tree->add(5);
     tree->add(6);
     tree->add(7);
     tree->remove(7);
     tree->remove(8);
     tree->add(7);
     tree->add(8);
     tree->add(9);
     std::cout << "is int with value 30 present in the tree: " << tree->search(30) << "\n\r";
     tree->print();
     tree->remove(10);
     tree->remove(11);
     tree->remove(12);
     tree->remove(13);
     tree->remove(14);
     tree->remove(15);
     tree->remove(16);
     tree->remove(17);
     tree->remove(18);
     tree->remove(19);
     tree->remove(20);
     tree->print();
    return 0;
}