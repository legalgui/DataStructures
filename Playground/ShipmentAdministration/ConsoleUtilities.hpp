// Sebastian Galguera
// Helper functions for Console Use

// Guards
#ifndef CONSOLEUTILITIES_HPP
#define CONSOLEUTILITIES_HPP

#include <sstream>
#include <iostream>

// Namespace enclosing
namespace consoleutilities{

  // Output handlers
  namespace output{

    // Function to print titles
    void printHeader(std::string t_title){
      std::cout << "\n----------------------------------------------" << std::endl;
      std::cout << "         " << t_title << "         " << std::endl;
      std::cout << "----------------------------------------------" << std::endl;

      if(t_title == "MAIN MENU"){
        std::cout << "\n 1. Add container.\n 2. Get container info.\n 3. Get stack info.\n 4. Get dock info\n 5. Exit.\n ";
      }
    }

    // Print error
    int printError(std::string t_e){
      std::cout << "\n-------------------------------" << std::endl;
      std::cout << "Error: " << t_e << std::endl;
      std::cout << std::endl;
      return 1;
    };
  }

  namespace input{

    // Format input
    std::string formatInput(std::string t_item){
      std::for_each(t_item.begin(), t_item.end(), [](char & c) { c = ::toupper(c);});
      t_item.erase(remove_if(t_item.begin(), t_item.end(), isspace), t_item.end());
      return t_item;
    }

    template <typename T>
    T prompt(const std::string, const bool){};

    // Template specifications
    template <>
    std::string prompt(const std::string t_label, const bool t_willFormat){
      std::cout << t_label;
      std::string str;
      std::getline(std::cin, str);

      if(t_willFormat){
        return formatInput(str);
      }
      return str;
    }

    template <>
    int prompt(const std::string t_label, const bool t_willFormat){
      std::cout << t_label << " ";
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
    bool validatePrompt(T, double){}

    // String specification
    template <>
    bool validatePrompt<std::string>(std::string t_prompt, double t_limit){
      if(t_prompt.size() > t_limit){
        return 0;
      }
      return 1;
    }

    // Int specification
    template <>
    bool validatePrompt<int>(int t_prompt, double t_limit){
      if(t_prompt > t_limit || t_prompt < 0){
        return 0;
      }
      return 1;
    }

    // Get valid prompt with template specification
    template <typename T>
    T promptUser(std::string t_label, double t_limit, std::string t_e, bool t_willFormat){
      T prompted{};
      bool flag = false;
      while(!flag){
        prompted = prompt<T>(t_label, t_willFormat);
        validatePrompt<T>(prompted, t_limit) ? flag = true : output::printError(t_e);
      };
      return prompted;
    }

  }

}

#endif /* CONSOLEUTILITIES_HPP */
