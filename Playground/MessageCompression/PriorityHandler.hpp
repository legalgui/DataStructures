// Sebastian Galguera
// Priority Linked List class for datastructure representation

// Guards
#ifndef PRIORITY_HANDLER_HPP
#define PRIORITY_HANDLER_HPP

#include "../../Structures/LinkedList/LinkedList.hpp"

using datastruct::LinkedList;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Stack structure inheriting from Linked List
  template <class T>
  class PriorityHandler{

    LinkedList<T> * m_list = new LinkedList<T>();

  public:
    PriorityHandler() {}
    PriorityHandler(LinkedList<T> * t_list) : m_list(t_list) {}
    ~PriorityHandler();

    LinkedList<T> * getList();
    void insertOrdered(T, std::string);

    // Utility functions for the ordered insertion
    int getPosition(T & t_element, std::string & t_dir);
    void advance(int & position, bool t_cond);

  };

  // Class specifications
  template <class T>
  PriorityHandler<T>::~PriorityHandler(){
    //m_list->clear();
  };

  template <class T>
  LinkedList<T> * PriorityHandler<T>::getList(){
    return m_list;
  };

  template <class T>
  void PriorityHandler<T>::insertOrdered(T t_element, std::string t_dir){
    if(m_list->empty()){
      m_list->insertBack(t_element);
    }else{
      int position = getPosition(t_element, t_dir);
      m_list->insert(t_element, position);
    }
  }

  template <class T>
  int PriorityHandler<T>::getPosition(T & t_element, std::string & t_dir){
    int position = 0;
    bool cond = t_element > m_list->at(position)->getInfo();

    if(t_dir == "asc"){ advance(position, cond);
    }else{ advance(position, !cond); }

    return position;
  }

  template <class T>
  void PriorityHandler<T>::advance(int & t_position, bool t_cond){
    while(t_position < m_list->size() && t_cond){ ++t_position; }
  }

}


#endif /* PRIORITY_HANDLER_HPP */
