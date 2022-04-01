#include "BplusTree.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


Node::Node(int size) {
    vector<int> temp(size);
    vector<Node*> temp2(size+1);
    for(int i = 0; i < size+1; i++) {
        temp2[i] == nullptr;
    }
    this->leaf = false;
    this->data = temp;
    this->next = nullptr;
    this->parent = nullptr;
    this->children = temp2;
    this->size = 0;
}

BplusTree::BplusTree(int ord) {
    this->order = ord;
    this->root = nullptr;
}

void BplusTree::insertar(int d) {
    if (root == nullptr) {
        root = new Node(this->order);
        root->data[0] = d;
        root->leaf = true;
        root->size++;
        return;
    }
    else {
        Node* temp = root;
        Node* parent;

        while (temp->leaf == false) {
            parent = temp;
            for (int i = 0; i < temp->size; i++) {
                if (d < temp->data[i]) {
                    temp = temp->children[i];
                    break;
                }
                if (i == temp->size - 1) {
                    temp = temp->children[i+1];
                    break;
                }
            }
        }
        if (temp->size < this->order) {
            int i = 0;
            while (d > temp->data[i] && i < temp->size) {
                i++;
            }
            for (int j = temp->size; j > i; j--) {
                temp->data[j] = temp->data[j-1];
            }
            temp->data[i] = d;
            temp->size++;
            temp->children[temp->size] = temp->children[temp->size-1]; //DUDOSO
            temp->children[temp->size-1] = nullptr; //DUDOSO
        }
        else {
            Node* nodon = new Node(this->order);
            vector<int> vec(this->order+1);

            for (int i = 0; i < this->order; i++) {
                vec[i] = temp->data[i];
            }
            int i = 0;
            while (d > vec[i] && i < this->order) {
                i++;
            }
            for (int j = this->order; j > i; j--) {
                vec[j] = vec[j-1];
            }
            vec[i] = d;
            nodon->leaf = true;
 
            temp->size = (this->order+1) / 2;
            nodon->size = this->order+1 - (this->order+1) / 2;

            temp->children[temp->size] = nodon; //DUDOSO
            nodon->children[nodon->size] = temp->children[this->order]; //DUDOSO
            temp->children[this->order] = nullptr; //DUDOSO

            nodon->next = temp->next;
            temp->next = nodon;
            for (i = 0; i < temp->size; i++) {
                temp->data[i] = vec[i];
            }
            for (i = 0; i < nodon->size; i++) {
                nodon->data[i] = vec[i + temp->size];
            }
            if (temp == root) {
                Node* rootn = new Node(this->order);
 
                temp->parent = rootn;
                nodon->parent = rootn;

                rootn->data[0] = nodon->data[0];
                rootn->children[0] = temp;
                rootn->children[1] = nodon;
                rootn->size = 1;
                this->root = rootn;
            }
            else {
                insert_node(nodon->data[0], find_parent(root, temp), nodon);
            }
        }
    }
}

void BplusTree::insert_node(int d, Node* parent, Node* child) {
 
    if (parent->size < this->order) {
        int i = 0;
        while (d > parent->data[i] && i < parent->size) {
            i++;
        }
        for (int j = parent->size; j > i; j--) {
            parent->data[j] = parent->data[j - 1];
        }
        for (int j = parent->size + 1; j > i + 1; j--) {
            parent->children[j] = parent->children[j - 1];
        }
        parent->data[i] = d;
        parent->size++;
        parent->children[i+1] = child;
        child->parent = parent;
    }
 
    else {
        Node* nodon = new Node(this->order);
        vector<int> vec(this->order+1);
        vector<Node*> nvec(this->order+2);
 
        for (int i = 0; i < this->order; i++) {
            vec[i] = parent->data[i];
        }
        for (int i = 0; i < this->order+1; i++) {
            nvec[i] = parent->children[i];
        }
        int i = 0;
        int j;

        while (d > vec[i] && i < order) {
            i++;
        }
        for (j = this->order; j > i; j--) {
            vec[j] = vec[j-1];
        }
        vec[i] = d;
 
        for (j = this->order+1; j > i+1; j--) {
            nvec[j] = nvec[j-1];
        }
        nvec[i+1] = child;
 
        parent->size = (this->order+1) / 2;
        nodon->size = this->order - (this->order+1) / 2;
        for (i = 0, j = parent->size+1; i < nodon->size; i++, j++) {
            nodon->data[i] = vec[j];
        }
 
        for (i = 0, j = parent->size+1; i < nodon->size+1; i++, j++) {
            nodon->children[i] = nvec[j];
        }
        nodon->leaf = false;

        if (parent == this->root) {
            Node* rootn = new Node(this->order);

            parent->parent = rootn;
            nodon->parent = rootn;

            rootn->data[0] = parent->data[parent->size];
            rootn->children[0] = parent;
            rootn->children[1] = nodon;
            rootn->size = 1;
            this->root = rootn;
        }
 
        else {
            insert_node(parent->data[parent->size], find_parent(this->root, parent), nodon);
        }
    }
}

Node* BplusTree::find_parent(Node* temp, Node* child) {
    
    Node* parent;

    if (temp->leaf || (temp->children[0])->leaf) {
        return nullptr;
    }
    for (int i = 0;
         i < temp->size + 1; i++) {
        if (temp->children[i] == child) {
            parent = temp;
            return parent;
        }
        else {
            parent = find_parent(temp->children[i], child);
            if (parent != nullptr) {
                return parent;
            }
        }
    }
    return parent;
}