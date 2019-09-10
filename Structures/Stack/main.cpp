// Sebastian Galguera
// Code to try Stack features

#include <iostream>

#include "Stack.hpp"

using datastruct::Stack;

int main(){

  Stack<int> st;
  st.push(1); // 0
  st.push(2); // 1
  st.push(3); // 2
  st.push(4); // 3

  while(!st.empty()){
    std::cout << *st.pop() << std::endl;
  }

  return 1;
}
