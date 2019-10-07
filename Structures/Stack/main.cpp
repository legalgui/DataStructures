// Sebastian Galguera
// Code to try Stack features

#include <iostream>

#include "Stack.hpp"

using datastruct::Stack;

int main(){

  Stack<int *> st;
  st.push(new int(1)); // 0
  st.push(new int(2)); // 1
  st.push(new int(3)); // 2
  st.push(new int(4)); // 3

  while(!st.empty()){
    std::cout << *st.pop()->getInfo() << std::endl;
  }

  return 1;
}
