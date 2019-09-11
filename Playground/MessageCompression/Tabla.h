// Sebastian Galguera
// Table class for Huffman Coding implementation

// Guards
#ifndef TABLE_HPP
#define TABLE_HPP

class Tabla{
  char letra;
  std::string code;

public:
  Tabla(char letra, std::string code): letra(letra), code(code){}
  char getLetra(){ return letra; };
  std::string getCode(){ return code; };
};


#endif /* TABLE_HPP */
