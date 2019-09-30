#include <iostream>
#include "Container.hpp"
#include "Product.hpp"

using shipment::Product;
using shipment::Container;

int main(){
  //Product p = Product("Caca", 12, 10);
  Container * c = new Container("0001", 2, true);
  std::cout << *c << std::endl;
}
