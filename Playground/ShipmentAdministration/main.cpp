// Sebastian Galguera
// Code to implement Shipment System

#include <iostream>
#include <vector>

#include "Helper.hpp"

#include "Product.hpp"
using shipment::Product;

#include "Container.hpp"
using shipment::Container;

#include "Dock.hpp"
using shipment::Dock;

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

#include "../../Structures/Queue/Queue.hpp"
using datastruct::Queue;

namespace utils = shipmentutilities;

void handleProductAddition(Dock &, int);
bool isInStack(Stack<Container *> *, std::string &);
void handleContainerVisualization(Dock &);
void handleStackVisualization(Dock &);
void handleDockVisualization(Dock &);

int main(){

  std::cout << "Welcome to the Shipment Administrator" << std::endl;
  int contLimit { utils::getValidPrompt<int>("Insert the number of products (load) per container: ", 100, "Wrong input", false) };
  int stackLimit { utils::getValidPrompt<int>("Insert the number of containers (height) per stack: ", 100, "Wrong input", false) };
  int dockLimit { utils::getValidPrompt<int>("Insert the number of stacks (length) per dock: ", 100, "Wrong input", false) };

  Dock dock(contLimit, stackLimit, dockLimit);
  int option { 0 };

  while(option != 5){
    utils::printHeader("MAIN MENU");
    option = utils::getValidPrompt<int>("Please, select an option: ", 5, "Incorrect option", false);
    switch(option){
      case 1: {
        handleProductAddition(dock, contLimit);
        break;
      }
      case 2: {
        handleContainerVisualization(dock);
        break;
      }
      case 3: {
        handleStackVisualization(dock);
        break;
      }
      case 4: {
        handleDockVisualization(dock);
        break;
      }
    }
  }
}

void handleProductAddition(Dock & t_dock, int t_contLimit){
  utils::printHeader("Add container");
  t_dock.addContainer(t_contLimit);
};

bool isInStack(Stack<Container *> * t_stack, std::string & t_contID){
  Stack<Container *> * aux { new Stack<Container *>() };
  while(!t_stack->empty()){
    if(t_contID == t_stack->top()->getInfo()->getID()){
      std::cout << *t_stack->top()->getInfo() << std::endl;
      // Push back the auxiliary stack's nodes
      while(!aux->empty()){
        t_stack->push(aux->pop()->getInfo());
      }
      delete aux;
      return true;
    }else{
      aux->push(t_stack->pop()->getInfo());
    }
  }
  // Push back the auxiliary stack's nodes
  while(!aux->empty()){
    t_stack->push(aux->pop()->getInfo());
  }
  delete aux;
  return false;
}

void handleContainerVisualization(Dock & t_dock){
  utils::printHeader("Container information");
  if(t_dock.getDock()->size()){
    std::cout << "Current max container id: " << t_dock.getCurrentContID() - 1 << std::endl;
    std::string contID { utils::getValidPrompt<std::string>("Insert the stack number: ", 10, "Wrong input", false) };
    bool found { false };
    for(auto node : *t_dock.getDock()){
      found = isInStack(node.getInfo(), contID);
    }
    if(!found){
      // Case not found
      std::cout << "Container not found" << std::endl;
    }
  }else{
    std::cout << "The dock is empty" << std::endl;
  }
}

void handleStackVisualization(Dock & t_dock){
  utils::printHeader("Stack information");
  if(t_dock.getDock()->size()){
    std::cout << "Current max stack number: " << t_dock.getDock()->size() - 1 << std::endl;
    int pos { utils::getValidPrompt<int>("Insert the stack number: ", t_dock.getDock()->size() - 1, "Wrong input", false) };
    std::cout << *t_dock.getDock()->at(pos)->getInfo() << std::endl;
  }else{
    std::cout << "The dock is empty" << std::endl;
  }
}

void handleDockVisualization(Dock & t_dock){
  utils::printHeader("The container information");
  for(auto node : *t_dock.getDock()){
    std::cout << *node.getInfo() << std::endl;
  }
  std::cout << "Dock total price: " << t_dock.getDockTotalPrice() << std::endl;
}
