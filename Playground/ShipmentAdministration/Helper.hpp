// Sebastian Galguera
// Utility functions for shipment classes

// Guards
#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <sstream>

// Namespace enclosing
namespace shipmentutilities{

  std::string promptUser(const std::string, const bool);
  std::string formatInput(std::string);

  std::string promptUser(const std::string t_label, const bool t_willFormat){
    std::cout << t_label;
    std::string str;
    std::getline(std::cin, str);
    if(t_willFormat){
      return formatInput(str);
    }
    return str;
  }

  std::string formatInput(std::string t_item){
    std::for_each(t_item.begin(), t_item.end(), [](char & c) { c = ::toupper(c);});
    t_item.erase(remove_if(t_item.begin(), t_item.end(), isspace), t_item.end());
    return t_item;
  }

}

#endif /* HELPER_HPP */
