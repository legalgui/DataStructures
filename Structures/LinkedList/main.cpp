// Sebastian Galguera
// Code to try Linked List features

#include <iostream>
#include <vector>

#include "LinkedList.hpp"

using datastruct::LinkedList;

int main(){

  LinkedList<int> ll;

  Node<int> * node { new Node<int>(4) };

  ll.insertFront(1);
  ll.insertFront(2);
  ll.insertBack(0);
  ll.removeFront();
  ll.insert(node, 3);

  std::cout << ll.size() << std::endl;
  std::cout << ll.at(node) << std::endl;

  for(auto i = 0; i < ll.size(); i++){
    std::cout << ll.at(i)->getInfo() << std::endl;
  }

  std::cout << ll.search(0) << std::endl;
  ll.searchAndReturnPosition(1);

  return 1;
}
