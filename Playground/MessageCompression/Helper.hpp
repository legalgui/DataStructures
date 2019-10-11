// Sebastian Galguera
// Helper functions and structures for Huffman Coding implementation

// Guards
#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>

// Namespace enclosing
namespace huffmanutilities{

  // Structure for symbol code handling
  struct Table{
    Table(char t_symbol, std::string t_code): m_symbol(t_symbol), m_code(t_code){}
    char m_symbol;
    std::string m_code;

    inline bool operator==(const Table& t_table) const {
      return m_symbol == t_table.m_symbol;
    }
  };
}

#endif /* HELPER_HPP */
