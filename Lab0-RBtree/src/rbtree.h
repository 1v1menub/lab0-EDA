#ifndef RBTREE_H
#define RBTREE_H

#include <vector>

using namespace std;

// Lista de colores del arbol
enum Color {RED,BLACK};

struct Nodo{
    // Atributos
    int dato;
    int color;

    // Relacion con otros Nodos
    Nodo *left;
    Nodo *right;
    Nodo *father;

    // Constructor
    Nodo(int);
};

class RBtree
{
private:
    Nodo *root;
    Nodo *insertarNodo(Nodo* &, Nodo* &);
    void RBremove(Nodo* &puntero, int caso);
    void corregirArbol(Nodo* &);

    int getColor(Nodo* &);
    void setColor(Nodo* &, int );

    void rotarIzquierda(Nodo* &);
    void rotarDerecha  (Nodo* &);

public:
    RBtree();
    void insertar(int);
    void remover(int valor);

    ~RBtree();

    vector<int> inorder();
    void inorderaux(Nodo* node, vector<int> &vec);
    vector<int> preorder();
    void preorderaux(Nodo* node, vector<int> &vec);
    vector<int> postorder();
    void postorderaux(Nodo* node, vector<int> &vec);
};

 




#endif