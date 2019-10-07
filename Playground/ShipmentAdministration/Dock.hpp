// Sebastian Galguera
// Dock class for Shipment implementation

// Guards
#ifndef DOCK_HPP
#define DOCK_HPP

#include <iostream>
#include <sstream>

#include "Helper.hpp"
#include "Product.hpp"
#include "Container.hpp"

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

namespace utils = shipmentutilities;

// Namespace enclosing
namespace shipment{
  class Dock{

    static int m_currentContID;
    static int m_currentDockID;

    int m_ID;
    int m_currentStack { 0 };
    int m_contLimit { 0 };
    int m_stackLimit { 0 };
    int m_dockLimit { 0 };
    int m_totalPrice { 0 };

    LinkedList<Stack<Container *> *> * m_dock { new LinkedList<Stack<Container *> *>()};

  public:
    Dock(int t_contLimit, int t_stackLimit, int t_dockLimit) :
    m_contLimit(t_contLimit), m_stackLimit(t_stackLimit), m_dockLimit(t_dockLimit),
    m_ID(m_currentDockID++) {}
    ~Dock();

    // Dock handling
    void addContainer(int, bool);
    void addStackAndProduct(int, bool);
    void addProduct(int, bool);

    // Information getters
    int getContainerTotalPrice(std::string);
    int getStackTotalPrice(int);
    int getDockTotalPrice();
    int getCurrentContID();
    int getID();

    LinkedList<Stack<Container *> *> * getDock();
  };

  int Dock::m_currentContID { 0 };
  int Dock::m_currentDockID { 0 };

  Dock::~Dock(){
    delete m_dock;
  }

  void Dock::addContainer(int t_numProducts, bool t_willAdd = true){
    if(m_dock->empty()){
      addStackAndProduct(t_numProducts, t_willAdd);
    }else if(m_dock->first()->getInfo()->size() < m_stackLimit){
      addProduct(t_numProducts, t_willAdd);
    }else if(m_dock->size() < m_dockLimit){
      std::cout << "Stack is full, starting new stack" << std::endl;
      addStackAndProduct(t_numProducts, t_willAdd);
    }else {
      utils::printError("The dock is full");
    }
  }

  void Dock::addStackAndProduct(int t_numProducts, bool t_willAdd){
    Container * container { new Container(std::to_string(m_currentContID++), t_numProducts, t_willAdd) };
    Stack<Container *> * stack { new Stack<Container *>() };
    stack->push(container);
    m_dock->insertFront(stack);
    m_totalPrice += container->getTotalPrice();
  }

  void Dock::addProduct(int t_numProducts, bool t_willAdd){
    Container * container { new Container(std::to_string(m_currentContID++), t_numProducts, t_willAdd) };
    m_dock->first()->getInfo()->push(container);
    m_totalPrice += container->getTotalPrice();
  }

  int Dock::getContainerTotalPrice(std::string t_id){
    return 1;
  }

  int Dock::getStackTotalPrice(int t_stackNum){
    return 1;
  }

  int Dock::getDockTotalPrice(){
    return m_totalPrice;
  }

  int Dock::getCurrentContID(){
    return m_currentContID;
  }

  int Dock::getID(){
    return m_ID;
  }

  LinkedList<Stack<Container *> *> * Dock::getDock(){
    return m_dock;
  }

}

#endif /* DOCK_HPP */
