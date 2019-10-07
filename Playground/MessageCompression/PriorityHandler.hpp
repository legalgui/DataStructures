// Sebastian Galguera
// Priority Handler for Huffman implementation

// Guards
#ifndef PRIORITY_HANDLER_HPP
#define PRIORITY_HANDLER_HPP

#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace huffmanutilities{

  // Class that constitutes a Piority Handler for Huffman Compression
  template <class T>
  class PriorityHandler{

    LinkedList<T> * m_list { new LinkedList<T>() };

  public:
    PriorityHandler() {}
    PriorityHandler(LinkedList<T> * t_list) : m_list(t_list) {}
    ~PriorityHandler();

    LinkedList<T> * getList();
    void insertOrdered(T);

    // Utility functions for the ordered insertion
    int getPosition(T &);
    void advance(int &, T &);

  };

  // Class specifications
  template <class T>
  PriorityHandler<T>::~PriorityHandler(){
    delete m_list;
  };

  template <class T>
  LinkedList<T> * PriorityHandler<T>::getList(){
    return m_list;
  };

  template <class T>
  void PriorityHandler<T>::insertOrdered(T t_element){
    if(m_list->empty()){
      m_list->insertBack(t_element);
    }else{
      int position = getPosition(t_element);
      m_list->insert(t_element, position);
    }
  }

  template <class T>
  int PriorityHandler<T>::getPosition(T & t_element){
    int position { 0 };
    advance(position, t_element);
    return position;
  }

  template <class T>
  void PriorityHandler<T>::advance(int & t_position, T & t_element){
    while(t_position < m_list->size() && (*t_element->getInfo() > *m_list->at(t_position)->getInfo()->getInfo())){
      ++t_position;
    }
  }

}


#endif /* PRIORITY_HANDLER_HPP */
