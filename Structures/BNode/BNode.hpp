// Sebastian Galguera from lessons of V. Cubells
// Binary Node generic class for Binary Tree

// Guards
#ifndef BNODE_HPP
#define BNODE_HPP

#include <iostream>

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a unitary container that links to three UC
  template <class T>
  class BNode{

    T m_info;
    BNode<T> * m_parent { nullptr };
    BNode<T> * m_left { nullptr };
    BNode<T> * m_right { nullptr };

  public:

    BNode() { }
    BNode(const T & t_info): m_info (t_info){};
    BNode(const BNode<T> &);

    virtual ~BNode();


    T getInfo() const;
    void setInfo(const T &);

    BNode<T> * getParent() const;
    void setParent(BNode<T> *);

    BNode<T> * getLeft() const;
    void setLeft(BNode<T> *);

    BNode<T> * getRight() const;
    void setRight(BNode<T> *);

    template <typename Tn>
    friend std::ostream & operator<<(std::ostream &, const BNode<Tn>  &);
  };

  template <class T>
  BNode<T>::BNode(const BNode<T> & t_other){
      m_info = t_other.m_info;
      m_parent = t_other.m_parent;
      m_left = t_other.m_left;
      m_right = t_other.m_right;
  }

  template <class T>
  BNode<T>::~BNode(){
      m_info.~T();
      m_left = m_right = m_parent = nullptr;
  }

  template <typename T>
  T BNode<T>::getInfo() const{
    return m_info;
  }

  template <typename T>
  void BNode<T>::setInfo(const T & t_value){
    m_info = t_value;
  }


  template <typename T>
  BNode<T> * BNode<T>::getParent() const{
    return m_parent;
  }

  template <typename T>
  void BNode<T>::setParent(BNode<T> * t_value){
    m_parent = t_value;
  }


  template <typename T>
  BNode<T> * BNode<T>::getLeft() const{
    return m_left;
  }

  template <typename T>
  void BNode<T>::setLeft(BNode<T> * t_value){
    m_left = t_value;
  }

  template <typename T>
  BNode<T> * BNode<T>::getRight() const{
    return m_right;
  }

  template <typename T>
  void BNode<T>::setRight(BNode<T> * t_value){
    m_right = t_value;
  }

  template <class T>
  std::ostream & operator<<(std::ostream & t_os, const BNode<T>  & t_node){
      t_os << t_node.m_info;
      return t_os;
  }
}

#endif
