#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>
#include <iostream>
#include <algorithm> 

using namespace std;

struct Node {
    bool leaf;
    int size;
    vector<int> data;
    Node* next;
    Node* parent;
    vector<Node*> children;
    
    Node(int size);
};

class BplusTree {
private:
    int order;
    Node* root;

    void insert_node(int d, Node* parent, Node* child);
    Node* find_parent(Node* temp, Node* child);

public:
    BplusTree(int ord);
    void insertar(int);
    void borrar(int);

    ~BplusTree();
};


#endif