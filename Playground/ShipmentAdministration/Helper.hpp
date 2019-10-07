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
  void printHeader(std::string);

  template <typename T>
  T promptUser(const std::string t_label, const bool t_willFormat){};

  // Template specifications
  template <>
  std::string promptUser(const std::string t_label, const bool t_willFormat){
    std::cout << t_label;
    std::string str;
    std::getline(std::cin, str);

    if(t_willFormat){
      return formatInput(str);
    }
    return str;
  }

  // Print error
  int printError(std::string e){
    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Error: " << e << std::endl;
    std::cout << std::endl;
    return 1;
  }


  template <>
  int promptUser(const std::string t_label, const bool t_willFormat){
    std::cout << t_label;
    std::string str;
    std::getline(std::cin, str);

    std::stringstream ss;
    ss << str;
    int num { 0 };
    ss >> num;
    return num;
  }

  // Validate prompt for specification
  // TO DO: Custom type specification with lambda or function pointer
  template <typename T>
  bool validatePrompt(T prompt, double limit){}

  // Get valid prompt with template specification
  template <typename T>
  T getValidPrompt(std::string label, double limit, std::string e, bool t_willFormat){
    T prompt{};
    bool flag = false;
    while(!flag){
        prompt = promptUser<T>(label, t_willFormat);
        validatePrompt<T>(prompt, limit) ? flag = true : printError(e);
    };
    return prompt;
  }

  // String specification
  template <>
  bool validatePrompt<std::string>(std::string prompt, double limit){
    if(prompt.size() > limit){
      return 0;
    }
    return 1;
  }

  // Int specification
  template <>
  bool validatePrompt<int>(int prompt, double limit){
    if(prompt > limit || prompt < 0){
      return 0;
    }
    return 1;
  }

  // Format input
  std::string formatInput(std::string t_item){
    std::for_each(t_item.begin(), t_item.end(), [](char & c) { c = ::toupper(c);});
    t_item.erase(remove_if(t_item.begin(), t_item.end(), isspace), t_item.end());
    return t_item;
  }

  void printHeader(std::string t_title){
    std::cout << "\n----------------------------------------------" << std::endl;
    std::cout << "         " << t_title << "         " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    if(t_title == "MAIN MENU"){
      std::cout << "\n 1. Add container.\n 2. Get container info.\n 3. Get stack info.\n 4. Get dock info\n 5. Exit.\n ";
    }
  }
}

#endif /* HELPER_HPP */
