// Sebastian Galguera
// Code to implement Message Compression System

#include <sstream>

#include <time.h>

#include "../../Structures/BinaryTree/BinaryTree.hpp"
using datastruct::BinaryTree;

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

#include "PriorityHandler.hpp"
#include "Symbol.hpp"
#include "Terminal.hpp"
#include "Helper.hpp"
using namespace huffmanutilities;
using namespace huffmanutilities::session;
using namespace huffmanutilities::output;
using namespace huffmanutilities::terminalhandling;
using namespace huffmanutilities::huffman;


int main(){
  printHeader("COMMUNICATIONS SIMULATOR");
  int selectedOpt { 1 };
  int terminalID { 0 };
  int sessionID;
  LinkedList<Terminal *> terminals;

  while(selectedOpt != 0){
    // 0 for quitting
    printHeader("MAIN MENU");
    std::cin >> selectedOpt;

    switch(selectedOpt){

      case 1:{
        // Admin section
        while(selectedOpt != 3){
          printHeader("ADMIN MENU");
          std::cin >> selectedOpt;
          switch(selectedOpt){
            case 1:{
              createTerminal(terminals, terminalID);
              break;
            }

            case 2:{
              terminalTest(terminals, terminalID);
              break;
            }

            default:{
              std::cout << "Invalid Option." << std::endl;
              break;
            }
          }
        }
        break;
      } // Admin section end
      case 2:{
        printHeader("USER MENU");
        bool loggedIn = login(terminals, sessionID);

        if(loggedIn){
          while(selectedOpt != 4){
            // Terminal section
            std::cout << "\n Welcome to Terminal  " << terminals.at(sessionID)->getInfo()->getName() << std::endl;
            printHeader("TERMINAL MENU");
            std::cin >> selectedOpt;
            switch(selectedOpt){

              case 1:{
                // Message sending
                int targetID { 0 };
                bool connected = connect(terminals, targetID);
                if(connected){
                  LinkedList<BNode<Symbol *> *> symbolQueue;
                  PriorityHandler<BNode<Symbol *> *> ph(&symbolQueue);
                  std::string message, messageCopy;
                  fillSymbolQueue(ph, message, messageCopy);

                  // Create the frequency table
                  printHeader("FREQUENCY TABLE");
                  for(int i = 0; i < symbolQueue.size(); i++){
                      std::cout << *symbolQueue.at(i)->getInfo()->getInfo() << std::endl;
                  }

                  // Tree construction
                  printHeader("TREE CONSTRUCTION");
                  BinaryTree<Symbol *> huffmanTree { getTree(ph) };

                  // Get the conversion table
                  printHeader("CONVERSION TABLE");
                  LinkedList<Table *> tables { getTables(huffmanTree, message) };

                  // Get the compressed message
                  printHeader("COMPRESSED MESSAGE");
                  std::cout << "Original message: " << messageCopy << "\nCompressed message: ";
                  std::string codeAux { getCompression(tables, messageCopy) };
                  std::cout << codeAux;

                  printSummary(codeAux, messageCopy);

                  terminals.at(sessionID)->getInfo()->addSent(codeAux);
                  terminals.at(targetID)->getInfo()->addReceived(codeAux);

                }else{
                  std::cout << "\nThe terminal does not exist." << std::endl;
                }
                break;
              } // End of message sending

              case 2:{
                printHeader("SENT HISTORY");
                if(terminals.at(sessionID)->getInfo()->getSent()->size()){
                  std::cout << *terminals.at(sessionID)->getInfo()->getSent() << std::endl;
                }else{
                    std::cout << "No messages have been sent." << std::endl;
                }
                break;
              }

              case 3:{
                printHeader("RECEIVED HISTORY");
                if(terminals.at(sessionID)->getInfo()->getReceived()->size()){
                  std::cout << *terminals.at(sessionID)->getInfo()->getReceived() << std::endl;
                }else{
                    std::cout << "No messages have been received." << std::endl;
                }
                break;
              }
              default:{ break; }
            } // End of nested switch
          }
        }else{
          std::cout << "Login information contains errors.\n" << std::endl;
        }
        break;
      }case 0:{
        std::cout << "Goodbye " << std::endl;
        break;
      }
      default:{ std::cout << "Invalid option\n"; }
    } // End of outer switch
  } // End of while
}
