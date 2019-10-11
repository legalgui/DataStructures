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
    // Function to print compression summary
    void printSummary(std::string & t_code, std::string & t_msg){
      float asci = 8;
      float percentage = (1 - (t_code.size() / (t_msg.size() * asci))) * 100;
      std::cout << "\nOriginal size (in bits): "<< t_msg.size() * 8 << std::endl;
      std::cout << "Compressed size (in bits): " << t_code.size() << std::endl;
      std::cout <<  "\nSaving: %" << percentage << std::endl;
    }

    // Function to print titles
    void printHeader(std::string t_title){
      std::cout << "\n----------------------------------------------" << std::endl;
      std::cout << "         " << t_title << "         " << std::endl;
      std::cout << "----------------------------------------------" << std::endl;

      if(t_title == "MAIN MENU"){
        std::cout << "\n 1. Use as Admin.\n 2. Use as User.\n 0. Quit.\n\n";
      }else if(t_title == "ADMIN MENU"){
        std::cout << "\n 1. Create Terminal.\n 2. Simulate error.\n 3. Quit.\n";
      }else if(t_title == "TERMINAL MENU"){
        std::cout << "\n1. Send message.\n2. See sent history.\n3. See received history.\n4. Quit.\n\n";
      }else if(t_title == "ERROR SIMULATOR"){
        std::cout << "For demonstration purposes, just the four first bits will be taken: " << std::endl;;
        std::cout << "The message sequence is: ";
      }
    };

    // Print error
    int printError(std::string t_e){
      std::cout << "\n-------------------------------" << std::endl;
      std::cout << "Error: " << t_e << std::endl;
      std::cout << std::endl;
      return 1;
    };
  }

  namespace input{
    template <typename T>
    T prompt(const std::string){};

    // Template specifications
    template <>
    std::string prompt(const std::string t_label){
      std::cout << t_label << " ";
      std::string str;
      std::getline(std::cin, str);
      return str;
    }

    template <>
    int prompt(const std::string t_label){
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
    T promptUser(std::string t_label, double t_limit, std::string t_e){
      T prompted{};
      bool flag = false;
      while(!flag){
          prompted = prompt<T>(t_label);
          validatePrompt<T>(prompted, t_limit) ? flag = true : output::printError(t_e);
      };
      return prompted;
    }

  }

}

#endif /* CONSOLEUTILITIES_HPP */
