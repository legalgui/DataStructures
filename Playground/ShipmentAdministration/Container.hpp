// Sebastian Galguera
// Container class for Shipment implementation

// Guards
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iostream>
#include <sstream>

#include "Helper.hpp"
#include "Product.hpp"
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

// Namespace enclosing
namespace shipment{
  class Container{

    std::string m_id { "" };
    int m_totalPrice { 0 };
    LinkedList<Product *> * m_products { new LinkedList<Product *>() };

  public:
    Container(std::string, int, bool);
    ~Container();

    std::string getID() const;
    int getTotalPrice() const;

    // Product handlers
    Product * createProduct(const int);
    void addProducts(const int t_quantity);
    LinkedList<Product *> * getProducts() const;
    void handleSingle(Product * t_product);
    void handleDuplicate(Product * t_product, Node<Product *> * t_found);
    void handleNewPrice(Product * t_newProduct, Node<Product *> * t_oldProduct);


    // Operator overloading
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
    if(t_willAdd){ addProducts(t_quantity); }
  }

  Container::~Container(){
    delete m_products;
  }

  void Container::addProducts(const int t_quantity){
    for(int i = 0; i < t_quantity; i++){
      Product * newProduct { createProduct(i) };
      auto oldProduct = m_products->searchAndReturnNode(newProduct);
      if(!oldProduct){
        handleSingle(newProduct);
      }else{
        handleDuplicate(newProduct, oldProduct);
      }
    }
  }

  void Container::handleDuplicate(Product * t_newProduct, Node<Product *> * t_oldProduct){
    std::cout << "Product already in container" << std::endl;

    // Add quantity to old product registry
    t_oldProduct->getInfo()->addQuantity(t_newProduct->getQuantity());

    int price = t_oldProduct->getInfo()->getPrice();

    if(price != t_newProduct->getPrice()){
      handleNewPrice(t_newProduct, t_oldProduct);
      price = t_oldProduct->getInfo()->getPrice();
    }
    m_totalPrice = t_oldProduct->getInfo()->getQuantity() * price;
    delete t_newProduct;
  }


  void Container::handleNewPrice(Product * t_newProduct, Node<Product *> * t_oldProduct){
    std::string label { "The price is different from the stored one\nUpdate? (y/n)" };
    std::string update { shipmentutilities::getValidPrompt<std::string>(label, 20, "Invalid", true) };
    if(update == "Y" || update == "YES"){
      std::cout << "Price was updated!" << std::endl;
      t_oldProduct->getInfo()->setPrice(t_newProduct->getPrice());
    }
  }

  void Container::handleSingle(Product * t_product){
    m_products->insertBack(t_product);
    m_totalPrice += t_product->getQuantity() * t_product->getPrice();
  }

  Product * Container::createProduct(const int t_i){
    std::string label { "\nAdd the information for product " + std::to_string(t_i + 1) + "\n\tContent: " };
    std::string item { shipmentutilities::getValidPrompt<std::string>(label, 20, "Invalid", true) };

    label = "\tQuantity: ";
    std::string qString { shipmentutilities::getValidPrompt<std::string>(label, 20, "Invalid", false) };

    label = "\tPrice: ";
    std::string pString { shipmentutilities::getValidPrompt<std::string>(label, 20, "Invalid", false) };

    std::stringstream ss;

    ss << qString << ' ' << pString;
    int quantity, price;
    ss >> quantity >> price;
    std::cout << std::endl;
    return new Product(item, quantity, price);
  }

  std::string Container::getID() const{
    return m_id;
  }

  int Container::getTotalPrice() const{
    return m_totalPrice;
  }

  LinkedList<Product *> * Container::getProducts() const{
    return m_products;
  }


  std::ostream & operator<<(std::ostream & t_os, const Container & t_container){
    t_os << "\n\t" << "Container: " << t_container.getID() << " - total price: $" << t_container.getTotalPrice() << std::endl;
    t_os << "Items: " << "\n---------" << std::endl;
    auto products = t_container.getProducts();
    for(int i = 0; i < products->size(); i++){
      t_os << *products->at(i)->getInfo() << std::endl;
    }
    return t_os;
  }

}

#endif /* CONTAINER_HPP */
