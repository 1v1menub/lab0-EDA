#include "rbtree.h"
#include "rbtree.cpp"
#include <iostream>

int main() {
    auto rbt = new RBtree();
    rbt->insertar(5);
    rbt->insertar(3);
    rbt->insertar(9);
    rbt->insertar(1);
    rbt->insertar(7);
    rbt->insertar(8);
    rbt->insertar(10);
    rbt->insertar(6);
    rbt->insertar(4);
    rbt->insertar(2);
    rbt->remover(8);
    auto lista = rbt->inorder();
    for (auto i: lista) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    lista = rbt->preorder();
    for (auto i: lista) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    lista = rbt->postorder();
    for (auto i: lista) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}