// Sebastian Galguera
// Code to try Queue features

#include <iostream>

#include "Queue.hpp"

using datastruct::Queue;

int main(){

  Queue<int> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  while(!q.empty()){
    std::cout << *q.dequeue() << std::endl;
  }
  
  return 1;
}
