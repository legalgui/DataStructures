// Sebastian Galguera
// Product class for Shipment implementation

// Guards
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <sstream>

#include "Product.hpp"
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace shipment{
  class Container{

    std::string m_id { "" };
    int m_totalPrice { 0 };
    LinkedList<Product *> m_products;

  public:
    Container(std::string, int, bool);

    Product * createProduct(const int);
    std::string formatInput(std::string t_item);

    std::string getID() const;
    int getTotalPrice() const;
    void addProducts(const int t_quantity);

    LinkedList<Product *> getProducts() const;

		inline bool operator<(const Container& t_container) const {
			return m_totalPrice < t_container.m_totalPrice;
		}

    inline bool operator>(const Container& t_container) const {
			return m_totalPrice > t_container.m_totalPrice;
		}

    inline bool operator==(const Container& t_container) const {
			return m_id == t_container.getID();
		}

    friend std::ostream & operator<<(std::ostream &, const Container  &);

  };

  Container::Container(std::string t_id, int t_quantity, bool t_willAdd){
    m_id = t_id;
    if(t_willAdd){
        addProducts(t_quantity);
    }
  }

  void Container::addProducts(const int t_quantity){
    for(int i = 0; i < t_quantity; i++){
      Product * product = createProduct(i);
      auto found = m_products.searchAndReturnNode(product);
      if(found){
        std::cout << "Product already in container" << std::endl;
        found->getInfo()->addQuantity(product->getQuantity());
        int price = found->getInfo()->getPrice();
        if(price != product->getPrice()){
          std::cout << "The price is different from the stored one" << std::endl;
          std::cout << "Update? (y/n)";
          std::string update;
          std::getline(std::cin, update);
          update = formatInput(update);
          if(update == "Y" || update == "YES"){
            std::cout << "Price was updated!" << std::endl;
          }else{
            price = product->getPrice();
          }
          m_totalPrice += product->getQuantity() * price;
        }
      }else{
        m_products.insertBack(product);
        m_totalPrice += product->getQuantity() * product->getPrice();
      }
    }
  }

  Product * Container::createProduct(const int t_i){
    std::cout << "Add the information for product " << t_i + 1 << std::endl;
    std::cout << "\tContent: ";
    std::string item;
    std::getline(std::cin, item);
    item = formatInput(item);

    std::cout << "\tQuantity: ";
    std::string qString;
    std::getline(std::cin, qString);

    std::cout << "\tPrice: ";
    std::string pString;
    std::getline(std::cin, pString);

    std::stringstream ss;

    ss << qString << ' ' << pString;
    int quantity, price;
    ss >> quantity >> price;
    std::cout << std::endl;
    return new Product(item, quantity, price);
  }

  std::string Container::formatInput(std::string t_item){
    std::for_each(t_item.begin(), t_item.end(), [](char & c) { c = ::toupper(c);});
    t_item.erase(remove_if(t_item.begin(), t_item.end(), isspace), t_item.end());
    return t_item;
  }

  std::string Container::getID() const{
    return m_id;
  }

  int Container::getTotalPrice() const{
    return m_totalPrice;
  }

  LinkedList<Product *> Container::getProducts() const{
    return m_products;
  }


  std::ostream & operator<<(std::ostream & t_os, const Container & t_container){
    t_os << "\n\t" << "Container: " << t_container.getID() << " - total price: $" << t_container.getTotalPrice() << std::endl;
    t_os << "Items: " << "\n---------" << std::endl;
    auto products = t_container.getProducts();
    for(int i = 0; i < products.size(); i++){
      t_os << *products.at(i)->getInfo() << std::endl;
    }
    return t_os;
  }

}

#endif /* CONTAINER_HPP */
