#ifndef Terminal_h
#define Terminal_h

#include <iostream>
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;

class Terminal {

    std::string nombre;
    std::string password;
    int ID;

public:

    LinkedList<std::string> listaMensajesEnviados;
    LinkedList<std::string> listaMensajesRecibidos;

    Terminal() {}
    Terminal(std::string nombre, std::string password, int ID) : nombre(nombre), password(password), ID(ID)  {}

    void setNombre(std::string nombre){ this->nombre = nombre; };
    std::string getNombre() {return nombre;}

    void setPassword(std::string password){ this->password = password; };
    std::string getPassword() { return password; }

    void setRecibido(std::string recibido){ listaMensajesRecibidos.insertBack(recibido); }
    void setEnviado(std::string enviado){ listaMensajesEnviados.insertBack(enviado); }

    LinkedList<std::string> getRecibido(){ return listaMensajesRecibidos; }
    LinkedList<std::string> getEnviado(){ return listaMensajesEnviados; }
    int getID() {return ID;}

};

#endif
