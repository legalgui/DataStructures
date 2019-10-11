// Sebastian Galguera
// Huffman Compressor for Huffman implementation

// Guards
#ifndef HUFFMAN_COMPRESSOR_HPP
#define HUFFMAN_COMPRESSOR_HPP

// General helpers
#include "ConsoleUtilities.hpp"
using namespace consoleutilities;
namespace input = consoleutilities::input;
namespace output = consoleutilities::output;

// Problem specifics
#include "PriorityHandler.hpp"
#include "Symbol.hpp"
#include "Terminal.hpp"
#include "Helper.hpp"

// Data structures
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

#include "../../Structures/BNode/BNode.hpp"
using datastruct::BNode;

#include "../../Structures/BinaryTree/BinaryTree.hpp"
using datastruct::BinaryTree;

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

// Namespace enclosing
namespace huffmanutilities{

  // Class that constitutes a Piority Handler for Huffman Compression
  class HuffmanCompressor{

    std::string m_msg;
    std::string m_msgCpy;
    std::string m_compressedMsg;

    // Symbol Queue and its Priority Handler
    LinkedList<BNode<Symbol *> *> m_symbolQueue;
    PriorityHandler<BNode<Symbol *> *> m_ph;

    // Huffman Tree
    BinaryTree<Symbol *> m_huffmanTree;

    // Tables List
    LinkedList<Table *>  m_tables;

  public:
    HuffmanCompressor(){}

    std::string getMsg();
    std::string getCompMsg();

    void compress(std::string, bool);
    void run(bool);

    // Tree utility functions
    BNode<Symbol *> * createNode(std::string, int, bool);

    // Process functions
    void buildSymbolQueue(const char);
    void printFrequencyTable();
    void buildTree(bool);
    void buildTables(const char, const bool);
    void buildCompression(bool);

  };

  std::string HuffmanCompressor::getMsg(){
    return m_msg;
  };

  std::string HuffmanCompressor::getCompMsg(){
    return m_compressedMsg;
  };

  void HuffmanCompressor::compress(std::string t_msg, bool t_isVerbose){
    m_msg = m_msgCpy = t_msg;
    run(t_isVerbose);
  };

  void HuffmanCompressor::run(bool t_isVerbose){
    m_ph.bind(&m_symbolQueue);
    buildSymbolQueue('<');
    if(t_isVerbose){ printFrequencyTable(); }
    buildTree(t_isVerbose);
    buildTables('<', t_isVerbose);
    buildCompression(t_isVerbose);
  };

  // Function to fill the symbol queue
  void HuffmanCompressor::buildSymbolQueue(const char t_special){
    char auxChar;
    int charCount;
    for(int i = 0; i < m_msgCpy.size(); i++){
      auxChar = m_msgCpy[i];
      if(auxChar != t_special){
        charCount = 1;
        for(int j = i+1; j < m_msgCpy.size(); j++){
          if(auxChar == m_msgCpy[j]){
            m_msgCpy[j] = t_special;
            charCount++;
          }
        }
        std::string auxLeafChar { auxChar };
        BNode<Symbol *> *leafNode { new BNode<Symbol *>(new Symbol(auxLeafChar, charCount)) };
        m_ph.insertOrdered(leafNode);
      }
    }
  }

  void HuffmanCompressor::printFrequencyTable(){
    // Create the frequency table
    output::printHeader("FREQUENCY TABLE");
    for(int i = 0; i < m_symbolQueue.size(); i++){
        std::cout << *m_symbolQueue.at(i)->getInfo()->getInfo() << std::endl;
    }
  }

  // Function to get node from Priority Handler and set path
  BNode<Symbol *> * HuffmanCompressor::createNode(std::string t_label, int t_path, bool t_isVerbose){
    BNode<Symbol *> * node { m_ph.getList()->removeFront()->getInfo() };
    node->getInfo()->setBinaryPath(t_path);
    if(t_isVerbose){
      std::cout << t_label << " " << node->getInfo()->getSymbol() << std::endl;
    }
    return node;
  }

  // Function to get the huffman tree
  void HuffmanCompressor::buildTree(bool t_isVerbose){
    if(t_isVerbose){
      output::printHeader("TREE CONSTRUCTION");
    }
    while (m_ph.getList()->size()!=1){

        // Create left and right nodes
        BNode<Symbol *> * left { createNode("Left node", 0, t_isVerbose) };
        BNode<Symbol *> * right { createNode("Right node", 1, t_isVerbose) };

        // Create internal node
        std::string internalSymbol { left->getInfo()->getSymbol() };
        internalSymbol += right->getInfo()->getSymbol();

        int internalFrequency { (left->getInfo()->getFrequency() + right->getInfo()->getFrequency()) };

        BNode<Symbol *> * internal { new BNode<Symbol *>(new Symbol(internalSymbol, internalFrequency)) };
        if(t_isVerbose){
          std::cout <<  "Internal node " << *internal->getInfo() << std::endl;
        }

        internal->setParent(NULL);
        internal->setLeft(left);
        internal->setRight(right);

        left->setParent(internal);
        right->setParent(internal);

        m_ph.insertOrdered(internal);
    }

    m_huffmanTree.setRoot(m_ph.getList()->removeFront()->getInfo());
  }

  // Function to get the tables
  void HuffmanCompressor::buildTables(const char t_special, const bool t_isVerbose){
    if(t_isVerbose){
      output::printHeader("CONVERSION TABLE");
    }

    for (int i = 0; i < m_msgCpy.size(); i++){
      if (m_msgCpy[i] != t_special){
        std::string auxString { m_msgCpy[i] };

        // Get the node for the given symbol
        BNode<Symbol *> * auxBN { m_huffmanTree.search(new Symbol(auxString, 0), m_huffmanTree.getRoot()) };

        Stack<int *> stackPath;
        stackPath.push(new int(auxBN->getInfo()->getBinaryPath()));

        // Traverse binary path to the top
        while(auxBN->getParent() != m_huffmanTree.getRoot()){
            stackPath.push(new int(auxBN->getParent()->getInfo()->getBinaryPath()));
            auxBN = auxBN->getParent();
        }

        // Reverse the binary path by popping
        std::string code;
        while(!stackPath.empty()){
            std::ostringstream convert;
            convert << *stackPath.pop()->getInfo();
            code += convert.str();
        }

        if(t_isVerbose){
          std::cout << "Symbol " << m_msgCpy[i] << " Code " << code << std::endl;
        }
        m_tables.insertBack(new Table(m_msgCpy[i], code));;
      }
    }

  }

  // Translate compression
  void HuffmanCompressor::buildCompression(bool t_isVerbose){
    for(int i = 0; i < m_msg.size(); i++){
        for(int j = 0; j < m_tables.size(); j++){
            if(m_msg[i] == m_tables.at(j)->getInfo()->m_symbol){
                    m_compressedMsg += m_tables.at(j)->getInfo()->m_code;
            }
        }
    }

    if(t_isVerbose){
      output::printHeader("COMPRESSED MESSAGE");
      std::cout << "Original message: " << m_msg << "\nCompressed message: ";
      std::cout << m_compressedMsg << std::endl;
    }
  }
}


#endif /* HUFFMAN_COMPRESSOR_HPP */
