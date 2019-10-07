// Sebastian Galguera from lessons of V. Cubells
// Node generic class for data structures

// Guards
#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a unitary container that links to other UC
  template <class T>
  class Node{

    T m_info;
    Node<T> * m_next { nullptr };

  public:

    Node() {};
    Node(const T & t_info): m_info(t_info){};
    Node(const Node<T> &);

    virtual ~Node();

    // Content accesors
    T getInfo() const;
    void setInfo(const T &);

    // Next element accesors
    Node<T> * getNext() const;
    void setNext(Node<T> *);

    template <typename Tn>
    friend std::ostream & operator<<(std::ostream &, const Node<Tn> &);
  };

  // Class specifications
  template <class T>
  Node<T>::Node(const Node<T> & t_other){
    m_info = t_other.m_info;
    m_next = t_other.m_next;
  }

  template <class T>
  Node<T>::~Node(){
    if(std::is_pointer<T>::value){
      m_info.~T();
    }
    m_next = nullptr;
  }

  template <class T>
  void Node<T>::setInfo(const T & t_info){
    m_info = t_info;
  }

  template <class T>
  T Node<T>::getInfo() const{
    return m_info;
  }

  template <class T>
  Node<T> * Node<T>::getNext() const{
    return m_next;
  }

  template <class T>
  void Node<T>::setNext(Node<T> * t_next){
    m_next = t_next;
  }

  template <typename T>
  std::ostream & operator<<(std::ostream & t_os, const Node<T> & t_node){
    t_os << t_node.m_info;
    return t_os;
  }

}

#endif /* NODE_HPP */
