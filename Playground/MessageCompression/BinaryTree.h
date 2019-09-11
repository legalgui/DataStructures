#ifndef BinaryTree_BinaryTree_h
#define BinaryTree_BinaryTree_h

#include <iostream>
#include "BNode.h"
#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;



class BinaryTree
{
    BNode * root = NULL;
    std::ostream& print(std::ostream& os, BNode * node);

public:

    LinkedList<int> listaPathBinario;
    Stack<int> stackCode;
    BinaryTree();
    BinaryTree(BNode * content);

    ~BinaryTree();
    void clear();
    void clear(BNode * node);

    bool empty();
    BNode * getRaiz();

    bool insert(std::string caracter, int frecuencia, BNode * parent);

    friend std::ostream& operator<<(std::ostream& os, BinaryTree &arbol);

    int level(BNode * node);

    BNode * getParent(std::string caracter);

    BNode * search (std::string caracter);
    BNode * search (std::string caracter, BNode * node);
};


BinaryTree::BinaryTree() { }


BinaryTree::BinaryTree(BNode * content)
{
    root = content;
}


BinaryTree::~BinaryTree()
{
    clear(root);
}


void BinaryTree::clear()
{
    clear(root);
}


void BinaryTree::clear(BNode * node)
{
    if (node)
    {

        clear(node->getLeft());
        clear(node->getRight());

        delete node;
    }
}


bool BinaryTree::empty()
{
    return (root == NULL);
}


BNode * BinaryTree::getRaiz()
{
    return root;
}


bool BinaryTree::insert(std::string caracter, int frecuencia, BNode * parent)
{

    if (!parent)
    {
        root = new BNode(caracter, frecuencia);
    }
    else
    {
        if (!parent->getLeft())
        {
            BNode * nuevo = new BNode(caracter, frecuencia);
            nuevo->setParent(parent);
            parent->setLeft(nuevo);
        }
        else if (!parent->getRight())
        {
            BNode * nuevo = new BNode(caracter, frecuencia);
            nuevo->setParent(parent);
            parent->setRight(nuevo);
        }
        else
            return false;
    }
    return true;
}



int BinaryTree::level(BNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    BNode * aux = node;
    int level = 1;
    while (aux->getParent())
    {
        ++level;
        aux = aux->getParent();
    }
    return level;
}


BNode * BinaryTree::search(std::string caracter)
{
    return search(caracter, root);
}


BNode * BinaryTree::search(std::string caracter, BNode * node)
{
    BNode * encontrado = NULL;
    if (node)
    {
        if (node->getCaracter() == caracter)
        {
            return node;
        }
        else
        {
            encontrado = search(caracter, node->getLeft());
            if (encontrado)
            {
                return encontrado;
            }
            return search(caracter, node->getRight());
        }
    }
    return encontrado;
}


BNode * BinaryTree::getParent(std::string caracter)
{
    BNode * node = search(caracter);
    return node->getParent();
}


std::ostream& BinaryTree::print(std::ostream& os, BNode * node)
{
    if (node) {
        os << *node;
        print(os, node->getLeft());
        print(os, node->getRight());
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, BinaryTree &arbol)
{
    return arbol.print(os, arbol.root);
}

#endif
