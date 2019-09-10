// Sebastian Galguera
// Code to try Node features

#include <iostream>
#include <array>

#include "Node.hpp"

using datastruct::Node;

int main(){

  Node<std::string> nodeOne("I am last (nodeOne)");
  Node<std::string> nodeTwo("I am first (nodeTwo)");
  Node<std::string> nodeThree("I am second (nodeThree)");

  nodeOne.setNext(&nodeTwo);
  nodeTwo.setNext(&nodeThree);
  nodeThree.setNext(&nodeOne);

  std::array<Node<std::string>, 3> nodeArr;

  nodeArr[0] = nodeOne; // Last
  nodeArr[1] = nodeTwo; // First
  nodeArr[2] = nodeThree; // Second

  for(auto element : nodeArr){
    std::cout << element.getNext()->getInfo() << std::endl;
  }

  return 1;
}
