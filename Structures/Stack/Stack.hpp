// Sebastian Galguera under supervision and guide of V. Cubells
// Stack generic class for datastructure representation

// Guards
#ifndef STACK_HPP
#define STACK_HPP

#include "../LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Stack structure inheriting from Linked List
  template <class T>
  class Stack : private LinkedList<T>{

  public:

    Stack(): LinkedList<T>(){};
    virtual ~Stack();

    int size() const override;
    bool empty() const override;

    // View of data on top of the stack
    Node<T> * top();
    Node<T> * pop();

    // Data insertion to top of the stack
    void push(const T &);
    void push(Node<T> *);

    bool operator == (const Stack<T> &) const;
    bool operator != (const Stack<T> &) const;

    template <typename Tn>
    friend std::ostream & operator<<(std::ostream &, const Stack<Tn> &);
  };

  // Class specifications
  template <class T>
  Stack<T>::~Stack(){
    this->clear();
  }

  template <class T>
  int Stack<T>::size() const{
    return LinkedList<T>::size();
  }

  template <class T>
  bool Stack<T>::empty() const{
    return LinkedList<T>::empty();
  }

  template <class T>
  Node<T> * Stack<T>::top(){
    return LinkedList<T>::at(size() - 1);
  }

  template <class T>
  Node<T> * Stack<T>::pop(){
    return LinkedList<T>::removeBack();
  }

  template <class T>
  void Stack<T>::push(const T & t_info){
    Node<T> * newNode { new Node<T>(t_info) };
    push(newNode);
  };

  template <class T>
  void Stack<T>::push(Node<T> * t_newNode){
    LinkedList<T>::insertBack(t_newNode);
  };

  template <class T>
  bool Stack<T>::operator == (const Stack<T> & t_stack) const{
    return size() == t_stack.size();
  };

  template <class T>
  bool Stack<T>::operator != (const Stack<T> & t_stack) const{
    return !(*this == t_stack);
  };

  template <typename T>
  std::ostream & operator<<(std::ostream & t_os, const Stack<T> & t_stack){
    for (const Node<T> & node : t_stack) {
      t_os << node << std::endl;
    }
    return t_os;
  }
}

#endif /* STACK_HPP */
