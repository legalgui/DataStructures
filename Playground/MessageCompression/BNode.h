#ifndef BNode_h
#define BNode_h

#include <iostream>


class BNode {
    std::string caracter;
    int frecuencia;
    int pathBinario = 0;
    BNode * right = NULL;
    BNode * left = NULL;
    BNode * parent = NULL;
    
public:
    
    BNode() {}
    BNode(std::string caracter, int frecuencia) : caracter(caracter), frecuencia(frecuencia) {}
    ~BNode();
    
    std::string getCaracter();
    void setCaracter(std::string value);
    
    
    int getFrecuencia();
    void setFrecuencia(int value);
    
    BNode * getRight();
    void setRight(BNode * value);
    
    BNode * getLeft();
    void setLeft(BNode * value);
    
    void setParent(BNode * value);
    BNode * getParent();
    
    void setPathBinario(int value);
    int getPathBinario();
    
    friend std::ostream& operator<<(std::ostream&, BNode&);
};

BNode::~BNode() {
    left = right = NULL;
}

std::string BNode::getCaracter() {
    return caracter;
}

void BNode::setCaracter(std::string value) {
    caracter = value;
}

int BNode::getFrecuencia() {
    return frecuencia;
}

void BNode::setFrecuencia(int value) {
    frecuencia = value;
}

BNode * BNode::getRight() {
    return right;
}

void BNode::setRight(BNode * value) {
    right = value;
}

BNode * BNode::getLeft() {
    return left;
}

void BNode::setLeft(BNode * value) {
    left = value;
}

void BNode::setParent(BNode * value)
{
    parent = value;
}

BNode * BNode::getParent()
{
    return parent;
}

void BNode::setPathBinario(int value)
{
    pathBinario = value;
}

int BNode::getPathBinario()
{
    return pathBinario;
}

std::ostream& operator <<(std::ostream& os, BNode& BNode) {
    os << "Caracter: " << BNode.caracter << " Frecuencia: " << BNode.frecuencia << " Path " << BNode.pathBinario;
    return os;
}

#endif
