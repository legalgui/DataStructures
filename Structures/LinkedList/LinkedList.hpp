// Sebastian Galguera under supervision and guide of V. Cubells
// Linked List generic class for datastructure representation

// Guards
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "../Node/Node.hpp"

using datastruct::Node;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Linked List structure using Raw Pointers
  template <class T>
  class LinkedList{

  protected:

    Node<T> * m_first { nullptr };
    int m_size { 0 };

    // Nested class to handle iteration
    class Iterator{

      const LinkedList<T> * m_data;
      int m_position;

    public:

      Iterator(const LinkedList<T> * t_adata, int t_aposition): m_data(t_adata), m_position(t_aposition){}
      Node <T> operator * () const { return *(m_data->at(m_position)); }
      const Iterator & operator ++ () { ++m_position; return *this; }
      bool operator != (const Iterator & t_it) const { return m_position != t_it.m_position; }
    };

  public:

    LinkedList() {}
    virtual ~LinkedList();

    // Data and memory clearing
    virtual void clear();

    virtual Node<T> * first() const;
    virtual int size() const;
    virtual bool empty() const;

    // Node insertion
    virtual void insert(const T &, int);
    virtual void insert(Node<T> *, int);
    void insertFront(const T &);
    void insertFront(Node<T> *);
    void insertBack(const T &);
    void insertBack(Node<T> *);

    // Node removal
    virtual Node<T> * remove(int);
    virtual Node<T> * remove(Node<T> *);
    Node<T> * removeFront();
    Node<T> * removeBack();

    // Node and data access
    virtual Node<T> * at(int) const;
    virtual int at(Node<T> *) const;

    // Search
    bool search(const T &) const;
    virtual int searchAndReturnPosition(const T &) const;
    virtual Node<T> * searchAndReturnNode(const T &);

    // Operator overloading
    Node<T> * operator [](const int);

    template <typename Tn>
    friend std::ostream & operator<<(std::ostream &, const LinkedList<Tn> &);

    // Iterator access
    Iterator begin() const { return { this, 0 }; }
    Iterator end() const { return { this, m_size }; }


    void insertOrdered(const T & element, int dir);
    void insertOrdered(Node<T> * node, int dir);
  };

  // Class specifications
  template <class T>
  void LinkedList<T>::clear(){
    if(empty()){ return; }

    Node<T> * tmp { m_first };

    while(tmp != nullptr){
      m_first = m_first->getNext();
      delete tmp;
      tmp = m_first;
    }

    m_size = 0;
    m_first = nullptr;
  }


 template  <class T>
  LinkedList<T>::~LinkedList(){
    clear();
  }

  template <class T>
  Node<T> * LinkedList<T>::first() const{
    return m_first;
  };

  template <class T>
  int LinkedList<T>::size() const{
    return m_size;
  }

  template <class T>
  bool LinkedList<T>::empty() const{
    return m_size == 0;
  }

  template <class T>
  void LinkedList<T>::insert(const T & t_info, int t_position){
    Node<T> * newNode { new Node<T>(t_info) };
    insert(newNode, t_position);
  }

  template <class T>
  void LinkedList<T>::insert(Node<T> * t_newNode, int t_position){

    if(empty() || t_position <= 0){
      t_newNode->setNext(m_first);
      m_first = t_newNode;
    }else{

      if(t_position > m_size){
        t_position = m_size;
      }

      Node<T> * tmp { at(t_position - 1) };
      t_newNode->setNext(tmp->getNext());
      tmp->setNext(t_newNode);
    }

    ++m_size;
  }

  template <class T>
  void LinkedList<T>::insertFront(const T & t_info){
    insert(t_info, 0);
  }

  template <class T>
  void LinkedList<T>::insertFront(Node<T> * t_newNode){
    insert(t_newNode, 0);
  }

  template <class T>
  void LinkedList<T>::insertBack(const T & t_info){
    insert(t_info, m_size);
  }

  template <class T>
  void LinkedList<T>::insertBack(Node<T> * t_newNode){
    insert(t_newNode, m_size);
  }

  template <class T>
  Node<T> * LinkedList<T>::remove(Node<T> * t_node){
    return remove(at(t_node));
  }

  template <class T>
  Node<T> * LinkedList<T>::remove(int t_position){
    if(empty() || (t_position >= m_size || t_position < 0)){
      return nullptr;
    }

    int pos {0};
    Node<T> * removed;

    if(t_position == 0){
      removed = m_first;
      m_first = m_first->getNext();
    }else{
      Node<T> * prev = at(t_position - 1);
      removed = prev->getNext();
      prev->setNext(removed->getNext());
    }

    --m_size;
    return removed;
  }

  template <class T>
  Node<T> * LinkedList<T>::removeFront(){
    return remove(0);
  }

  template <class T>
  Node<T> * LinkedList<T>::removeBack(){
    return remove(m_size - 1);
  }

  template <class T>
  Node<T> * LinkedList<T>::at(int t_position) const{
    if(empty() || t_position < 0 || t_position >= m_size){
      return nullptr;
    }

    int pos {0};
    Node<T> * tmp { m_first };

    while(pos < t_position){
      tmp = tmp->getNext();
      pos++;
    }

    return tmp;
  }

  template <class T>
  int LinkedList<T>::at(Node<T> * t_node) const{
    if(empty() || t_node == nullptr){
      return -1;
    }
    return searchAndReturnPosition(t_node->getInfo());

  }

  template <class T>
  bool LinkedList<T>::search(const T & t_info) const{
    return searchAndReturnPosition(t_info) >= 0;
  }

  template <class T>
  int LinkedList<T>::searchAndReturnPosition(const T & t_info) const{

    if(empty()){ return -1; }

    int pos { 0 };
    bool found { false };

    Node<T> * tmp { m_first };

    while(tmp != nullptr){
      if(*tmp->getInfo() == *t_info){
        found = true;
        break;
      }
      tmp = tmp->getNext();
      pos++;
    }

    if(found){ return pos; }
    return -1;
  }

  template <class T>
  Node<T> * LinkedList<T>::searchAndReturnNode(const T & t_info){
    if (empty()){ return nullptr; }

    Node<T> * node { nullptr };

    Node<T> * tmp { m_first };

    while(tmp != nullptr && node == nullptr){
      if(*tmp->getInfo() == *t_info){
        node = tmp;
      }
      tmp = tmp->getNext();
    }
    return node;
  }

  template <class T>
  Node<T> * LinkedList<T>::operator [](const int t_position){
    return at(t_position);
  }

  template <class Tn>
  std::ostream & operator<<(std::ostream & t_os, const LinkedList<Tn> & t_linkedList){
    for(const Node<Tn> & node : t_linkedList){
      t_os << *node.getInfo() << std::endl;
    }
    return t_os;
  }
}

#endif /* LINKED_LIST_HPP */
