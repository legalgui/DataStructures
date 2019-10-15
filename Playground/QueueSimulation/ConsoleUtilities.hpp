// Sebastian Galguera
// Helper functions for Console Use

// Guards
#ifndef CONSOLEUTILITIES_HPP
#define CONSOLEUTILITIES_HPP

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
    }

    void printTime(int t_time){
      if((t_time % 60) <= 9){
        std::cout << t_time / 60 << ":0" << t_time % 60 << std::endl;
      }else{
        std::cout << t_time / 60 << ":" << t_time % 60 << std::endl;
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

}

#endif /* CONSOLEUTILITIES_HPP */
