// Sebastian Galguera
// Code to try BNode features

#include <iostream>

#include "BNode.hpp"

using datastruct::BNode;

int main(){
  
  BNode<int> parent(0);
  BNode<int> center(1);
  BNode<int> left(2);
  BNode<int> right(3);

  center.setParent(&parent);
  center.setLeft(&left);
  center.setRight(&right);

  std::cout << "Parent " << *center.getParent() << std::endl;
  std::cout << "Left " << *center.getLeft() << std::endl;
  std::cout << "Right " << *center.getRight() << std::endl;

  return 1;
}
