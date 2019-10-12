// Sebastian Galguera
// Code to try Queue features

#include <iostream>

#include "Queue.hpp"

using datastruct::Queue;

int main(){

  Queue<int *> q;
  q.enqueue(new int(1));
  q.enqueue(new int(2));
  q.enqueue(new int(3));

  while(!q.empty()){
    std::cout << *q.dequeue()->getInfo() << std::endl;
  }


  return 1;
}
