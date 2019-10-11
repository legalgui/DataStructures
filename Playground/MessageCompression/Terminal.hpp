// Sebastian Galguera
// Terminal class for Huffman Coding implementation

// Guards
#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <iostream>

// Datastructures
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace huffmanutilities{

  // Class that constitutes a terminal for exampling
  class Terminal {

      std::string m_name;
      std::string m_password;
      int m_ID;

  public:

      LinkedList<std::string *> * m_sentMsg = new LinkedList<std::string *>();
      LinkedList<std::string *> * m_recievedMsg = new LinkedList<std::string *>();

      Terminal() {}
      Terminal(std::string t_name, std::string t_password, int t_ID) : m_name(t_name), m_password(t_password), m_ID(t_ID)  {}
      ~Terminal();

      void setName(const std::string);
      std::string getName() const ;

      void setPassword(const std::string);
      std::string getPassword() const ;

      void addReceived(std::string *);
      LinkedList<std::string *> * getReceived() const;

      void addSent(std::string *);
      LinkedList<std::string *> * getSent() const;

      int getID() const;

      inline bool operator<(const Terminal& t_terminal) const {
  			return m_name == t_terminal.getName();
  		}

      inline bool operator>(const Terminal& t_terminal) const {
  			return  m_name == t_terminal.getName();
  		}

      inline bool operator==(const Terminal& t_terminal) const {
  			return m_name == t_terminal.getName();
  		}
  };

  Terminal::~Terminal(){
    delete m_sentMsg;
    delete m_recievedMsg;
  };

  void Terminal::setName(const std::string t_name){
    m_name = t_name;
  };

  std::string Terminal::getName() const {
    return m_name;
  };

  void Terminal::setPassword(const std::string t_password){
    m_password = t_password;
  };

  std::string Terminal::getPassword() const{
    return m_password;
  };

  void Terminal::addReceived(std::string * t_received){
    m_recievedMsg->insertBack(t_received);
  };

  LinkedList<std::string *> * Terminal::getReceived() const {
    return m_recievedMsg;
  };

  void Terminal::addSent(std::string * t_sent){
    m_sentMsg->insertBack(t_sent);
  };

  LinkedList<std::string *> * Terminal::getSent() const {
    return m_sentMsg;
  };

  int Terminal::getID() const {
    return m_ID;
  };
}

#endif /* TERMINAL_HPP */
