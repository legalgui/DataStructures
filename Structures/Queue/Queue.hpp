// Sebastian Galguera under supervision and guide of V. Cubells
// Queue generic class for datastructure representation

// Guards
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Queue structure inheriting from Linked List
  template <class T>
  class Queue : private LinkedList<T>{

  public:

    Queue() : LinkedList<T>(){};
    virtual ~Queue();

    int size() const override;
    bool empty() const override;

    void enqueue(const T &);
    void enqueue(Node<T> *);

    Node<T> * front();
    Node<T> * dequeue();

    bool operator == (const Queue<T> &) const;
    bool operator != (const Queue<T> &) const;

    template <typename Tn>
    friend std::ostream & operator << (std::ostream &, const Queue<Tn> &);

  };

  template <class T>
  Queue<T>::~Queue(){
    this->clear();
  }

  template <class T>
  int Queue<T>::size() const{
    return LinkedList<T>::size();
  }

  template <class T>
  bool Queue<T>::empty() const{
    return LinkedList<T>::empty();
  }

  template <class T>
  void Queue<T>::enqueue(const T & t_info){
    Node<T> * newNode { new Node<T>(t_info) };
    enqueue(newNode);
  }

  template <class T>
  void Queue<T>::enqueue(Node<T> * t_newNode){
    LinkedList<T>::insertBack(t_newNode);
  }

  template <class T>
  Node<T> * Queue<T>::front(){
    return LinkedList<T>::first();
  }

  template <class T>
  Node<T> * Queue<T>::dequeue(){
    return LinkedList<T>::removeFront();
  }

  template <class T>
  bool Queue<T>::operator == (const Queue<T> & t_queue) const{
    return size() == t_queue.size();
  };

  template <class T>
  bool Queue<T>::operator != (const Queue<T> & t_queue) const{
    return !(*this == t_queue);
  };

  template <typename T>
  std::ostream & operator << (std::ostream & t_os, const Queue<T> & t_queue){
    for (const Node<T> & node : t_queue) {
      t_os << node << std::endl;
    }
    return t_os;
  }
}

#endif /* QUEUE_HPP */
