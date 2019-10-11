// Sebastian Galguera
// Code to implement Message Compression System

#include <time.h>

// General helpers
#include "ConsoleUtilities.hpp"
namespace input = consoleutilities::input;
namespace output = consoleutilities::output;

// Problem specifics
#include "HuffmanCompressor.hpp"
using huffmanutilities::HuffmanCompressor;

#include "Terminal.hpp"
using huffmanutilities::Terminal;

#include "Helper.hpp"
using huffmanutilities::Table;

#include "TerminalUtilities.hpp"
namespace session = huffmanutilities::terminalutilities::session;
namespace handling = huffmanutilities::terminalutilities::handling;

// Data structures
#include "../../Structures/BinaryTree/BinaryTree.hpp"
using datastruct::BinaryTree;

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

int main(){
  output::printHeader("COMMUNICATIONS SIMULATOR");
  int selectedOpt { 1 };
  int terminalID { 0 };
  int sessionID;
  LinkedList<Terminal *> terminals;

  while(selectedOpt != 0){
    // 0 for quitting
    output::printHeader("MAIN MENU");
    selectedOpt = input::promptUser<int>("Option:", 2, "Invalid Option");

    switch(selectedOpt){

      case 1:{
        // Admin section
        while(selectedOpt != 3){
          output::printHeader("ADMIN MENU");
          selectedOpt = input::promptUser<int>("\nOption:", 3, "Invalid Option");
          switch(selectedOpt){
            case 1:{ handling::createTerminal(terminals, terminalID); break; }
            case 2:{ handling::terminalTest(terminals, terminalID); break; }
          }
        }
        break;
      } // Admin section end
      case 2:{
        output::printHeader("USER MENU");
        bool loggedIn { session::login(terminals, sessionID) };

        if(loggedIn){
          while(selectedOpt != 4){
            // Terminal section
            std::cout << "\n Welcome to Terminal  " << terminals.at(sessionID)->getInfo()->getName() << std::endl;
            output::printHeader("TERMINAL MENU");
            selectedOpt = input::promptUser<int>("Option:", 4, "Invalid Option");
            switch(selectedOpt){

              case 1:{
                // Message sending
                int targetID { 0 };
                bool connected { session::connect(terminals, targetID) };
                if(connected){

                  HuffmanCompressor hc;

                  std::string message {
                    input::promptUser<std::string>("Message (min 2 different characters):", 15, "Invalid input, max(15)")
                  };

                  int verbose {
                    input::promptUser<int>("Verbose? (0 = no, 1 = yes):", 1, "Invalid input, just 0 or 1")
                  };

                  hc.compress(message, verbose);

                  // Get the compressed message
                  std::string compMsg = hc.getCompMsg();
                  std::string msg = hc.getMsg();
                  output::printSummary(compMsg, msg);
                  terminals.at(sessionID)->getInfo()->addSent(&compMsg);
                  terminals.at(targetID)->getInfo()->addReceived(&compMsg);

                }else{
                  output::printError("The terminal does not exist.");
                }
                break;
              } // End of message sending

              case 2:{
                output::printHeader("SENT HISTORY");
                if(terminals.at(sessionID)->getInfo()->getSent()->size()){
                  std::cout << *terminals.at(sessionID)->getInfo()->getSent() << std::endl;
                }else{
                  std::cout << "There are no sent messages yet." << std::endl;
                }
                break;
              }

              case 3:{
                output::printHeader("RECEIVED HISTORY");
                if(terminals.at(sessionID)->getInfo()->getReceived()->size()){
                  std::cout << *terminals.at(sessionID)->getInfo()->getReceived() << std::endl;
                }else{
                  std::cout << "There are no received messages yet." << std::endl;
                }
                break;
              }
            } // End of nested switch
          }
        }else{
          output::printError("Login information contains errors.");
        }
        break;
      }case 0:{
        std::cout << "Goodbye " << std::endl;
        break;
      }
    } // End of outer switch
  } // End of while
}
