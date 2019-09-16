// Sebastian Galguera
// Symbol class for Huffman Coding implementation

// Guards
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

// Namespace enclosing
namespace huffmanutilities{
  class Symbol{
    std::string m_symbol { "" };
    int m_frequency { 0 };
    int m_binPath { 0 };

  public:
    Symbol(std::string t_symbol, int t_frequency) : m_symbol(t_symbol), m_frequency(t_frequency) {}

    std::string getSymbol() const;
    int getFrequency() const ;

    int getBinaryPath() const;
    void setBinaryPath(const int);

		inline bool operator<(const Symbol& t_symbol) const {
			return m_frequency < t_symbol.getFrequency();
		}

    inline bool operator>(const Symbol& t_symbol) const {
			return m_frequency > t_symbol.getFrequency();
		}

    inline bool operator==(const Symbol& t_symbol) const {
			return m_symbol == t_symbol.getSymbol();
		}

    friend std::ostream & operator<<(std::ostream &, const Symbol  &);

  };

  std::string Symbol::getSymbol() const{
    return m_symbol;
  }

  int Symbol::getFrequency() const{
    return m_frequency;
  }

  int Symbol::getBinaryPath() const{
    return m_binPath;
  }

  void Symbol::setBinaryPath(const int t_binPath){
    m_binPath = t_binPath;
  }

  std::ostream & operator<<(std::ostream & t_os, const Symbol & t_symbol){
    t_os << t_symbol.getSymbol() << " - " << t_symbol.getFrequency();
    return t_os;
  }

}

#endif /* SYMBOL_HPP */
