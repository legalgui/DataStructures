// Sebastian Galguera
// Terminal utilities for Huffman Coding implementation

// Guards
#ifndef TERMINALUTILITIES_HPP
#define TERMINALUTILITIES_HPP

#include <iostream>

// General helpers
#include "ConsoleUtilities.hpp"
namespace input = consoleutilities::input;
namespace output = consoleutilities::output;

// Project specifics
#include "Terminal.hpp"

// Datastructures
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;


// Namespace enclosing
namespace huffmanutilities{
  namespace terminalutilities{
    // Session handlers
    namespace session{

      // Function for logging in
      bool login(LinkedList<Terminal *> & t_terminals, int & sessionID){
        std::cout << "\nPlease, specify the login information.\n";
        std::string name { input::promptUser<std::string>("Name:", 5, "Input is incorrect, max 5 characters") };
        std::string password { input::promptUser<std::string>("Passowrd:", 5, "Input is incorrect, max 5 characters") };

        for(int i = 0; i < t_terminals.size(); i++){
          auto terminal { t_terminals.at(i)->getInfo() };
          if ((name == terminal->getName()) && (password == terminal->getPassword())){
            sessionID = i;
            return true;
          }
        }
        return false;
      }


      // Function to connect to other terminal
      bool connect(LinkedList<Terminal *> & t_terminals, int & t_targetID){
        std::cout << "\nSpecify the name of the receiving Terminal";
        std::string name { input::promptUser<std::string>("\nName:", 5, "Input is incorrect, max 5 characters") };

        for(int i = 0; i < t_terminals.size(); i++){
          auto terminal { t_terminals.at(i)->getInfo() };
          if (name == terminal->getName()){
            t_targetID = i;
            return true;
          }
        }
        return false;
      }
    }

    namespace handling{
      void createTerminal(LinkedList<Terminal *> & t_terminals, int & t_terminalID){
        std::cout << "\n Please, specify the Terminal information.\n";

        std::string name { input::promptUser<std::string>("Name:", 5, "Input is incorrect, max 5 characters") };
        std::string password { input::promptUser<std::string>("Password:", 5, "Input is incorrect, max 5 characters") };

        t_terminals.insertBack(new Terminal(name, password, t_terminalID));

        std::cout << "\n\tTerminal " << name << " creation succesful." << std::endl;
        std::cout << "\tThe password is: " << password;
        std::cout << " with Position: " << t_terminalID << "\n" << std::endl;
        t_terminalID++;
      }

      // Function to simulate a random error and correct signal via Hamming Code
      bool hammingCode(std::string t_bin){
        int bits[7];
        output::printHeader("ERROR SIMULATOR");

        for (int i = 0; i < 4; i++){ std::cout << t_bin[i] << " "; }

        for (int i = 0; i <= 4; i++){
          if (i != 3){
            if(t_bin[i] == '0'){ bits[i] = 0;
            }else{ bits[i] = 1; }
          }
        }

        bits[6] = bits[0]^bits[2]^bits[4];
        bits[5] = bits[0]^bits[1]^bits[4];
        bits[3] = bits[0]^bits[1]^bits[2];

        printf("\nThe sequence with parity bits is: \n");
        for (int i = 0; i < 7; i++) { std::cout << bits[i] << " "; }

        std::cout << "\nVerifying if there's a problem..." << std::endl;

        srand (time(NULL));
        int v1 { rand() % 2 };
        int v2 { rand() % 8 };
        int parity[7];
        int bit { 3 } ;

        if (v1 == 0){
            bit = 0;
        }else{
          for(int i = 0; i < 7; i++){ parity[i] = bits[i]; }
          if (parity[v2] == 0){ parity[v2] = 1;
          }else{ parity[v2] = 0; }

          int bitOne, bitTwo, bitThree;
          bitOne = parity[6]^parity[4]^parity[2]^parity[0];
          bitTwo = parity[5]^parity[4]^parity[1]^parity[0];
          bitThree = parity[3]^parity[2]^parity[1]^parity[0];
          bit = bitThree * 4 + bitTwo * 2 + bitOne;
        }

        if(bit == 0){
          std::cout << "\nNo error was found." << std::endl;
          return false;
        }else{
          output::printError("\nError in position: " + std::to_string(8 - bit) + "\nThe corrected message is: ");
          if(parity[7 - bit] == 0){ parity[7 - bit] = 1;
          }else{ parity[7 - bit] = 0; }
          for (int i = 0; i < 7; i++){ printf("%d ",parity[i]); }
          return true;
        }
        return false;
      }

      // Function to run a terminal test
      void terminalTest(LinkedList<Terminal *> & t_terminals, int & t_terminalID){
        if(t_terminals.size()){
          std::cout << "\tSimulating random error in the first terminal and first message." << std::endl;
          auto testTerminal { t_terminals.at(0)->getInfo() };

          if(testTerminal->getSent()->size()){

            std::string * sError { testTerminal->getSent()->at(0)->getInfo() };
            // Case there was an error and the hamming code corrected it
            if(hammingCode(*sError)){
              std::cout << "The terminal " << testTerminal->getName() << " is not working properly." << std::endl;
              std::cout << "Shutting down..." << std::endl;
              t_terminals.remove(0);
              t_terminalID--;
            }else{
              std::cout << "The terminal " << testTerminal->getName() << " is working correctly." << std::endl;
            }
          }else{
            output::printError("Cannot start test, terminal doesn't have sent messages.");
          }
        }else{
          output::printError("Cannot start test, there are no terminals yet.");
        }
      }
    }
  }
}

#endif /* TERMINALUTILITIES_HPP */
