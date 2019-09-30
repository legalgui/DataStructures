// Sebastian Galguera
// Code to try Linked List features

#include <iostream>
#include <vector>

#include "LinkedList.hpp"

using datastruct::LinkedList;

int main(){

  LinkedList<int *> ll;

  Node<int *> * node { new Node<int *>(new int(4)) };

  ll.insertFront(new int(1));
  ll.insertFront(new int(2));
  ll.insertBack(new int(0));
  ll.removeFront();
  ll.insert(node, 3);

  std::cout << ll.size() << std::endl;
  std::cout << ll.at(node) << std::endl;

  for(auto i = 0; i < ll.size(); i++){
    std::cout << *ll.at(i)->getInfo() << std::endl;
  }

  std::cout << ll.search(new int(0)) << std::endl;
  ll.searchAndReturnPosition(new int(1));

  return 1;
}
