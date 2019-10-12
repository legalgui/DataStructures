// Sebastian Galguera under supervision and guide of V. Cubells
// Binary Tree generic class for datastructure representation

// Guards
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

#include "../BNode/BNode.hpp"
using datastruct::BNode;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Binary Tree structure using Raw Pointers
  template <class T>
  class BinaryTree{

    BNode<T> * m_root { nullptr };
    std::ostream& print(std::ostream&, BNode<T> *);

  public:

    BinaryTree(){};
    virtual ~BinaryTree();

    bool empty();

    // Data and memory clearing
    void clear();
    void clear(BNode<T> *);

    BNode<T> * getRoot() const;
    void setRoot(BNode<T> *);

    // BNode insertion
    bool insert(BNode<T> *, T);
    bool insert(BNode<T> *, BNode<T> *);

    // Tree traversal
    void preOrder() const;
    void preOrder(BNode<T> *) const;
    void inOrder() const;
    void inOrder(BNode<T> *) const;
    void postOrder() const;
    void postOrder(BNode<T> *) const;

    // Leaf identification
    void isLeaf() const;
    void isLeaf(BNode<T> *) const;

    // Depth identification
    int getDepth(BNode<T> *) const;

    // BNode relationships
    void ancestors(BNode<T> *) const;
    void cousins(BNode<T> *, BNode<T> *) const;
    bool validateCousins(BNode<T> *, BNode<T> *) const;
    void siblings(BNode<T> *) const;
    bool validateSiblings(BNode<T> *, BNode<T> *) const;

    // Search
    BNode<T> * search(T);
    BNode<T> * search(T, BNode<T> *);
    bool exists(T);

    // Content operating
    T sumNodes();
    T sumNodes(BNode<T> *);

    // Tree structure modification
    void invert();
    void invert(BNode<T> *);

    template <class Tn>
    friend std::ostream & operator<<(std::ostream &, BinaryTree<Tn> &);
  };

  template <class T>
  BinaryTree<T>::~BinaryTree(){
    clear();
  };

  template <class T>
  bool BinaryTree<T>::empty(){
    return m_root == nullptr;
  };

  template <class T>
  void BinaryTree<T>::clear(){
    clear(m_root);
  };

  template <class T>
  void BinaryTree<T>::clear(BNode<T> * t_node){
    if(t_node){
      clear(t_node->getLeft());
      clear(t_node->getRight());
      delete t_node;
    }
  };

  template <class T>
  BNode<T> * BinaryTree<T>::getRoot() const{
    return m_root;
  };

  template <class T>
  void BinaryTree<T>::setRoot(BNode<T> * t_node){
    if(!empty()){
      t_node->setLeft(m_root);
      m_root->setParent(t_node);
      m_root = t_node;
    }else{
      m_root = t_node;
    }
  };

  template <class T>
  bool BinaryTree<T>::insert(BNode<T> * t_parent, T t_value){
    BNode<T> * newNode { new BNode<T>(t_value) };
    bool inserted = insert(t_parent, newNode);
    if(!inserted) delete newNode;
    return inserted;
  };

  template <class T>
  bool BinaryTree<T>::insert(BNode<T> * t_parent, BNode<T> * t_node){
    bool inserted { false };

    if(empty() || !t_parent){
        setRoot(t_node);
        inserted = true;
    }else{
      if(!t_parent->getLeft()){
        t_parent->setLeft(t_node);
        t_node->setParent(t_parent);
        inserted = true;
      }else if(!t_parent->getRight()){
        t_parent->setRight(t_node);
        t_node->setParent(t_parent);
        inserted = true;
      }
    }
    return inserted;

  };

  template <class T>
  void BinaryTree<T>::preOrder() const{
    preOrder(m_root);
  };

  template <class T>
  void BinaryTree<T>::preOrder(BNode<T> * t_node) const{
    if(t_node){
      std::cout << *t_node->getInfo() << " ";
      preOrder(t_node->getLeft());
      preOrder(t_node->getRight());
    }
  };

  template <class T>
  void BinaryTree<T>::inOrder() const{
    inOrder(m_root);
  };

  template <class T>
  void BinaryTree<T>::inOrder(BNode<T> * t_node) const{
    if(t_node){
      inOrder(t_node->getLeft());
      std::cout << *t_node->getInfo() << " ";
      inOrder(t_node->getRight());
    }
  };

  template <class T>
  void BinaryTree<T>::postOrder() const{
    postOrder(m_root);
  };

  template <class T>
  void BinaryTree<T>::postOrder(BNode<T> * t_node) const{
    if(t_node){
      postOrder(t_node->getLeft());
      postOrder(t_node->getRight());
      std::cout << *t_node->getInfo() << " ";
    }
  };

  template <class T>
  void BinaryTree<T>::isLeaf() const{
    isLeaf(m_root);
  };

  template <class T>
  void BinaryTree<T>::isLeaf(BNode<T> * t_node) const{
    if(t_node){
      if(!t_node->getLeft() && !t_node->getRight()){
        std::cout << *t_node->getInfo() << " ";
      }else{
        isLeaf(t_node->getLeft());
        isLeaf(t_node->getRight());
      }
    }
  };

  template <class T>
  int BinaryTree<T>::getDepth(BNode<T> * t_node) const{
    if(t_node){
      BNode<T> * aux { t_node };
      int depth { 1 };

      while(aux->getParent()){
        depth++;
        aux = aux->getParent();
      }
      return depth;
    }
    return 0;
  };

  template <class T>
  void BinaryTree<T>::ancestors(BNode<T> * t_node) const{
    if(t_node && t_node->getParent()){
      std::cout << *t_node->getParent()->getInfo() << " ";
      ancestors(t_node->getParent());
    }
  };

  template <class T>
  void BinaryTree<T>::cousins(BNode<T> * t_node, BNode<T> * t_root) const{
    if(t_root){
      if(getDepth(t_node) == getDepth(t_root) &&
      validateSiblings(t_node->getParent(), t_root->getParent())){
        std::cout << *t_root->getInfo() << " ";
      }
      cousins(t_node, t_root->getLeft());
      cousins(t_node, t_root->getRight());
    }
  };

  template <class T>
  bool BinaryTree<T>::validateCousins(BNode<T> * t_first, BNode<T> * t_second) const{
    int fDepth = { getDepth(t_first) };
    int sDepth = { getDepth(t_second) };
    return (fDepth == sDepth) && (t_first->getParent() != t_second->getParent());
  };

  template <class T>
  void BinaryTree<T>::siblings(BNode<T> * t_node) const{
    if(t_node){
      if(t_node->getParent()->getLeft() == t_node){
        std::cout << *t_node->getParent()->getRight()->getInfo() << " ";
      }else{
        std::cout << *t_node->getParent()->getLeft()->getInfo() << " ";
      }
    }
    return;
  };

  template <class T>
  bool BinaryTree<T>::validateSiblings(BNode<T> * t_first, BNode<T> * t_second) const{
    if((t_first && t_second) && (t_first != t_second)){
      return t_first->getParent() == t_second->getParent();
    }
    return false;
  };

  template <class T>
  BNode<T> * BinaryTree<T>::search(T t_info){
    return search(t_info, m_root);
  };

  template <class T>
  BNode<T> * BinaryTree<T>::search(T t_info, BNode<T> * t_root){
    BNode<T> * foundNode { nullptr };
    if(t_root){
      if(*t_root->getInfo() == *t_info){
        return t_root;
      }else{
        foundNode = search(t_info, t_root->getLeft());

        if(foundNode){
          return foundNode;
        }

        return search(t_info, t_root->getRight());
      }
    }
    return foundNode;
  };

  template <class T>
  bool BinaryTree<T>::exists(T t_info){
    if(search(t_info)){ return 1; }
    return 0;
  };

  template <class T>
  T BinaryTree<T>::sumNodes(){
    return sumNodes(m_root);
  };

  template <class T>
  T BinaryTree<T>::sumNodes(BNode<T> * t_node){
    static int value;
    if(t_node){
      value += *t_node->getInfo();
      sumNodes(t_node->getLeft());
      sumNodes(t_node->getRight());
    }
    return &value;
  };

  template <class T>
  void BinaryTree<T>::invert(){
    invert(m_root);
  }

  template <class T>
  void BinaryTree<T>::invert(BNode<T> * t_root){
    if(t_root){
      BNode<T> * aux { t_root->getLeft() };
      t_root->setLeft(t_root->getRight());
      t_root->setRight(aux);
      invert(t_root->getLeft());
      invert(t_root->getRight());
    }
  }

  template <class T>
  std::ostream & BinaryTree<T>::print(std::ostream & t_os, BNode<T> * t_node)
  {
      if (t_node) {
          t_os << *t_node;
          print(t_os, t_node->getLeft());
          print(t_os, t_node->getRight());
      }
      return t_os;
  }

  template <class Tn>
  std::ostream & operator<<(std::ostream & t_os, BinaryTree<Tn> & t_binaryTree)
  {
      return t_binaryTree.print(t_os, t_binaryTree.m_root);
  }
}

#endif /* BINARY_TREE_HPP */
