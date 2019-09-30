// Sebastian Galguera
// Product class for Shipment implementation

// Guards
#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <iostream>

// Namespace enclosing
namespace shipment{
  class Product{

    std::string m_content { "" };
    int m_quantity { 0 };
    int m_price { 0 };

  public:
    Product(std::string t_content, int t_quantity, int t_price) : m_content(t_content),
    m_quantity(t_quantity), m_price(t_price) {}

    std::string getContent() const;
    int getQuantity() const;
    void setQuantity(const int);
    void addQuantity(const int);

    int getPrice() const;

		inline bool operator<(const Product& t_product) const {
			return (m_quantity * m_price) < (t_product.getQuantity() * t_product.getPrice());
		}

    inline bool operator>(const Product& t_product) const {
			return (m_quantity * m_price) > (t_product.getQuantity() * t_product.getPrice());
		}

    inline bool operator==(const Product& t_product) const {
			return m_content == t_product.getContent();
		}

    friend std::ostream & operator<<(std::ostream &, const Product  &);

  };

  std::string Product::getContent() const{
    return m_content;
  }

  int Product::getQuantity() const{
    return m_quantity;
  }

  void Product::setQuantity(const int t_quantity){
    m_quantity = t_quantity;
  }

  void Product::addQuantity(const int t_quantity){
    m_quantity += t_quantity;
  }

  int Product::getPrice() const{
    return m_price;
  }


  std::ostream & operator<<(std::ostream & t_os, const Product & t_product){
    t_os << t_product.getContent() << " - Qty: " << t_product.getQuantity()
    << " - Price: $" << t_product.getPrice();
    return t_os;
  }

}

#endif /* PRODUCT_HPP */
