// Sebastian Galguera
// Priority Handler for Huffman implementation

// Guards
#ifndef PRIORITY_HANDLER_HPP
#define PRIORITY_HANDLER_HPP

// Datastructures
#include "../../Structures/Queue/Queue.hpp"
using datastruct::Queue;

// Namespace enclosing
namespace queuesimulationutilities{

  // Class that constitutes a Piority Handler for Huffman Compression
  template <class T>
  class PriorityHandler{

    Queue<T> * m_queue;

  public:
    PriorityHandler() {}
    PriorityHandler(Queue<T> * t_queue) : m_queue(t_queue) {}

    Queue<T> * getQueue();

    void syncEnqueue(const T &);

    // Function to set list
    void bind(Queue<T> *);

  };

  template <class T>
  Queue<T> * PriorityHandler<T>::getQueue(){
    return m_queue;
  };

  template <class T>
  void PriorityHandler<T>::syncEnqueue(const T & t_event){
    if(m_queue->empty()){
      t_event->setTimeOfEventStart(t_event->getTimeOfArrival());
    }else{
      T previous { m_queue->last()->getInfo() };
      if(t_event->getTimeOfArrival() < previous->getTimeOfEventEnd()){
        t_event->setTimeOfEventStart(previous->getTimeOfEventEnd());
      }else{
        t_event->setTimeOfEventStart(t_event->getTimeOfArrival());
        t_event->setTimeWastedByStaff(previous);
      }
    }
    t_event->setTimeOfEventEnd(t_event->getTimeOfEventStart() + t_event->getDuration());
    m_queue->enqueue(t_event);
  };


  template <class T>
  void PriorityHandler<T>::bind(Queue<T> * t_queue){
    m_queue = t_queue;
  }

}


#endif /* PRIORITY_HANDLER_HPP */
