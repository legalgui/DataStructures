// Sebastian Galguera
// Code to implement Message Compression System

//using datastruct::PriorityHandler;
#include <sstream>

#include <time.h>


#include "../../Structures/BinaryTree/BinaryTree.hpp"
using datastruct::BinaryTree;

#include "../../Structures/Stack/Stack.hpp"
using datastruct::Stack;

#include "PriorityHandler.hpp"
using huffmanutilities::PriorityHandler;

#include "Symbol.hpp"
using huffmanutilities::Symbol;

#include "Terminal.hpp"
using huffmanutilities::Terminal;


struct Tabla{
  Tabla(char symbol, std::string code): symbol(symbol), code(code){}
  char symbol;
  std::string code;
};

template <class T>
BNode<T> * searchTree(T t_info, BNode<T> * t_root){
  BNode<T> * foundNode = nullptr;
  if(t_root){
    if(*t_root->getInfo() == *t_info){
      return t_root;
    }else{
      foundNode = searchTree(t_info, t_root->getLeft());

      if(foundNode){
        return foundNode;
      }

      return searchTree(t_info, t_root->getRight());
    }
  }
  return foundNode;
};

int huff(std::string, int &);

int main()
{
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "          COMUNICACIONES SA. DE CV.           " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    int conmutador = 1;
    int terminalID = 0;
    int auxID, auxHuffman;

    LinkedList<Terminal *> listaTerminales;

    while(conmutador!=0){

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "               MENU PRINCIPAL                 " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    std::cout << "\n1.- Usar como administrador.\n2.- Usar como usuario.\n0.- Salir.\n\nPor favor, seleccione una opcion: ";
    std::cin >> conmutador;

    switch(conmutador)
    {
        case 1:
        {
            while(conmutador!=3){
            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "               MENU ADMINISTRADOR             " << std::endl;
            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "\n1.- Agregar Terminal.\n2.- Iniciar simulador de errores.\n3.- Salir.\nPor favor, seleccione una opcion: ";

            std::cin >> conmutador;

            switch(conmutador)
            {
                case 1:
                {
                    std::cout << "Por favor, de de alta una terminal.\n\nname de la terminal: ";
                    std::string name;
                    std::cin.ignore();
                    std::getline (std::cin,name);

                    std::cout << "Password de la terminal: ";
                    std::string password;
                    std::getline (std::cin,password);

                    listaTerminales.insertBack(new Terminal(name, password, terminalID));

                    std::cout << "\n\tTerminal " << name << " creada con exito.\n\tEl password es: " << password << " con Posicion: " << terminalID << std::endl << std::endl;
                    terminalID++;

                    break;
                }
                case 2:
                {
                    if (listaTerminales.size() == 0){
                        std::cout << "\nNo hay terminales aun." << std::endl;
                    }
                    else{
                        if (listaTerminales.at(0)->getInfo()->getSent()->size()){

                            std::string sError = listaTerminales.at(0)->getInfo()->getSent()->at(0)->getInfo();
                            huff(sError, auxHuffman);

                            if (auxHuffman == 1){
                                std::cout << "La terminal " << listaTerminales.at(0)->getInfo()->getName() << " no funciona correctamente." << std::endl;
                                std::cout << "Apagando..." << std::endl;
                                listaTerminales.remove(0);
                                terminalID--;

                            }
                            else if (auxHuffman == 0){
                                std::cout << "La terminal " << listaTerminales.at(0)->getInfo()->getName() << " funciona correctamente." << std::endl;
                            }
                        }
                        else{
                            std::cout << "Esta terminal aun no tiene mensajes enviados." << std::endl;
                        }
                    }
                    break;
                }
                default:
                {
                    std::cout << "Opcion invalida." << std::endl;
                }
                }
            }
            break;
        }/*Final del administrador.*/
        case 2:
        {
            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "                MENU USUARIO                  " << std::endl;
            std::cout << "----------------------------------------------" << std::endl;
            std::cout << "\nPor favor, ingrese los datos de acceso.\n\nname: ";

            std::string name;
            std::cin.ignore();
            std::getline (std::cin,name);

            std::cout << "Password: ";
            std::string password;
            std::getline (std::cin,password);

            int acceso = 0;

            for(int i = 0; i < listaTerminales.size(); i++){
                if ((name == listaTerminales.at(i)->getInfo()->getName()) && (password == listaTerminales.at(i)->getInfo()->getPassword())){
                    acceso = 1;
                    auxID = i;
                }
            }
            if (acceso == 1)
            {
                while(conmutador!=4){
                std::cout << "----------------------------------------------" << std::endl;
                std::cout << "               MENU TERMINAL                  " << std::endl;
                std::cout << "----------------------------------------------" << std::endl;
                std::cout << "\nBienvenido a la terminal " << listaTerminales.at(auxID)->getInfo()->getName() << " con Posicion " << auxID  << std::endl;
                std::cout << "\n1.- Enviar mensaje.\n2.- Ver historial de envios.\n3.- Ver historial de recibidos.\n4.- Salir.\n\nPor favor, seleccione una opcion: ";
                std::cin >> conmutador;
                switch(conmutador)
                {
                    case 1:
                    {

                        std::cout << "\nIngrese el name de la terminal receptora: ";
                        std::string name;
                        std::cin.ignore();
                        std::getline(std::cin,name);

                        acceso = 0;
                        int auxIDDos;

                        for(int i = 0; i < listaTerminales.size(); i++){
                            if (name == listaTerminales.at(i)->getInfo()->getName()){
                                acceso = 1;
                                auxIDDos = i;

                                std::cout << "Por favor, ingrese la frase a codificar.\nFrase: ";
                                std::string frase, fraseCopy, codeAux;
                                std::getline (std::cin,frase);
                                fraseCopy = frase;
                                LinkedList<BNode<Symbol *> *> listaOrdenadaFrase;

                                /*Aqui se identifican los caracteres y las frecuencias, construyendo los nodos.*/
                                for (int i = 0; i < frase.size(); i++){
                                    char auxChar = frase[i];
                                    if (auxChar != '-'){
                                        int charCount = 1;
                                        for (int j = i+1; j < frase.size(); j++){
                                            if (auxChar == frase[j]){
                                            frase[j] = '-';
                                            charCount++;
                                            }
                                        }
                                        std::string auxLeafChar;
                                        std::stringstream sAux;
                                        sAux << auxChar;
                                        sAux >> auxLeafChar;
                                        BNode<Symbol *> *leafNode = new BNode<Symbol *>(new Symbol(auxLeafChar, charCount));
                                        PriorityHandler<BNode<Symbol *> *> ph(&listaOrdenadaFrase);
                                        ph.insertOrdered(leafNode);
                                    }
                                }
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "          TABLA DE FRECUENCIAS                " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;
                                for(int i = 0; i < listaOrdenadaFrase.size(); i++){
                                    std::cout << *listaOrdenadaFrase.at(i)->getInfo()->getInfo() << std::endl;
                                }

                                /*Aqui comienza la construccion del arbol.*/
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "           CONSTRUCCION DEL ARBOL             " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;
                                while (listaOrdenadaFrase.size()!=1){

                                    BNode<Symbol *> * leftBNode = listaOrdenadaFrase.removeFront()->getInfo();
                                    leftBNode->getInfo()->setBinaryPath(0);
                                    std::cout << "left node " << *leftBNode->getInfo()  << std::endl;

                                    BNode<Symbol *> *  rightBNode = listaOrdenadaFrase.removeFront()->getInfo();
                                    rightBNode->getInfo()->setBinaryPath(1);
                                    std::cout << "right node " << *rightBNode->getInfo() << std::endl;

                                    std::string dataInterna = leftBNode->getInfo()->getSymbol();
                                    dataInterna += rightBNode->getInfo()->getSymbol();
                                    int frecuenciaInterna = (leftBNode->getInfo()->getFrequency()+rightBNode->getInfo()->getFrequency());
                                    BNode<Symbol *> * internalNode = new BNode<Symbol *>(new Symbol(dataInterna, frecuenciaInterna));
                                    std::cout <<  "internal node " << *internalNode->getInfo() << std::endl;

                                    internalNode->setParent(NULL);
                                    internalNode->setLeft(leftBNode);
                                    leftBNode->setParent(internalNode);
                                    internalNode->setRight(rightBNode);
                                    rightBNode->setParent(internalNode);
                                    PriorityHandler<BNode<Symbol *> *> ph(&listaOrdenadaFrase);
                                    ph.insertOrdered(internalNode);
                                    //listaOrdenadaFrase.insertOrdered(internalNode, 2);
                                }
                                BinaryTree<Symbol *> arbolHuffman;
                                arbolHuffman.setRoot(listaOrdenadaFrase.removeFront()->getInfo());
                                LinkedList<Tabla *> listTabla;

                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "         TABLA DE CONVERSIONES                " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;

                                for (int i = 0; i < frase.size(); i++){
                                    if (frase[i] != '-'){
                                        std::string auxString;
                                        std::stringstream sAuxDos;
                                        sAuxDos << frase[i];
                                        sAuxDos >> auxString;


                                        BNode<Symbol *> * auxBN = searchTree<Symbol *>(new Symbol(auxString, 0), arbolHuffman.getRoot());
                                        Stack<int> stackPath;
                                        stackPath.push(auxBN->getInfo()->getBinaryPath());
                                        int k;
                                        std::string code;

                                        while(auxBN->getParent()!=arbolHuffman.getRoot()){
                                            stackPath.push(auxBN->getParent()->getInfo()->getBinaryPath());
                                            auxBN = auxBN->getParent();
                                        }

                                        while(!stackPath.empty()){
                                            std::ostringstream convert;
                                            convert << stackPath.pop()->getInfo();
                                            code += convert.str();
                                        }
                                        std::cout << "Letra " << frase[i] << " Codigo " << code << std::endl;
                                        listTabla.insertBack(new Tabla(frase[i], code));;
                                    }
                                }
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "           COMPRESION DE FRASE                " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "Frase original: " << fraseCopy << "\nFrase comprimida: ";

                                for (int i = 0; i < frase.size(); i++){
                                    for (int j = 0; j < listTabla.size(); j++){
                                        if (fraseCopy[i] == listTabla.at(j)->getInfo()->symbol){
                                                codeAux += listTabla.at(j)->getInfo()->code;
                                        }
                                    }
                                }
                                std::cout << codeAux;
                                float asci = 8;
                                float x = (1-(codeAux.size()/(fraseCopy.size()*asci)))*100;
                                std::cout << "\nBits originales: "<< fraseCopy.size()*8 << "\nBits finales: " << codeAux.size() << "\nEconomizacion: %" << x << std::endl;

                                listaTerminales.at(auxID)->getInfo()->setSent(codeAux);
                                listaTerminales.at(auxIDDos)->getInfo()->setReceived(codeAux);
                            }
                        }
                        if(acceso == 0){
                            std::cout << "\nLo sentimos, terminal inexistente." << std::endl;
                        }
                        break;
                    }/*Final del envio de mensaje*/
                    case 2:
                    {
                        std::cout << "----------------------------------------------" << std::endl;
                        std::cout << "             HISTORIAL DE ENVIOS              " << std::endl;
                        std::cout << "----------------------------------------------" << std::endl;
                        for (int i = 0; i < listaTerminales.at(auxID)->getInfo()->getSent()->size(); i++){
                            std::cout << listaTerminales.at(auxID)->getInfo()->getSent()->at(i)->getInfo() << std::endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        std::cout << "----------------------------------------------" << std::endl;
                        std::cout << "             HISTORIAL DE RECIBIDOS           " << std::endl;
                        std::cout << "----------------------------------------------" << std::endl;
                        for (int i = 0; i < listaTerminales.at(auxID)->getInfo()->getReceived()->size(); i++){
                            std::cout << listaTerminales.at(auxID)->getInfo()->getReceived()->at(i)->getInfo() << std::endl;
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                 }/*Fin del switch anidado*/
                }
            }
            else{
                std::cout << "Lo sentimos, name o password erroneos.\n" << std::endl;
            }
            break;
        }
        default:
        {
            std::cout << "Lo sentimos, opcion invalida\n";
        }

    }/*Fin del switch*/
    }/*Fin del while*/
}

int huff(std::string binary, int &auxHuffman)
{
   int bits[7],paridad[7],i,bitOne,bitTwo,bitThree,bit;

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "           SIMULADOR DE ERRORES               " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Se tomaran los primeros cuatro bits del mensaje: " << binary << std::endl;;
	std::cout << "La secuencia del mensaje es: ";
	for (int i = 0; i<4; i++)
	{
	    std::cout << binary[i] << " ";
	}

    for (int i = 0; i<=4; i++)
	{
	    if (i != 3)
	    {
	    if(binary[i] == '0')
	    {
	        bits[i] = 0;
	    }
	    else
	    {
	       bits[i] = 1;
	    }
	    }
	}
	bits[6]=bits[0]^bits[2]^bits[4];
	bits[5]=bits[0]^bits[1]^bits[4];
	bits[3]=bits[0]^bits[1]^bits[2];
	printf("\nLa secuencia con bits de paridad es: \n");
	for (i=0;i<7;i++) {
		std::cout << bits[i] << " ";
	}
	std::cout << "\nVerificando si existe algún error..." << std::endl;
	srand (time(NULL));
	int v1 = rand() % 2;
	int v2 = rand() % 8;
	if (v1 == 0){
	    bit = 0;
	}
	else
	{
	    for(int i = 0; i < 7; i++){
	        paridad[i] = bits[i];
	    }
	    if (paridad[v2] == 0){
	        paridad[v2] = 1;
	    }
	    else{
            paridad[v2] = 0;
        }


	    bitOne=paridad[6]^paridad[4]^paridad[2]^paridad[0];
	    bitTwo=paridad[5]^paridad[4]^paridad[1]^paridad[0];
	    bitThree=paridad[3]^paridad[2]^paridad[1]^paridad[0];
	    bit=bitThree*4+bitTwo*2+bitOne ;
	}

	if(bit==0) {
		std::cout << "\nNo se encontro ningun error.";
		auxHuffman = 0;
	} else {
		std::cout << "\nError en la posicion: " << 8-bit << "\nEl mensaje corregido: ";
		if(paridad[7-bit]==0)
		 			paridad[7-bit]=1; else
		 			paridad[7-bit]=0;
		for (i=0;i<7;i++) {
			printf("%d ",paridad[i]);
		}
			auxHuffman = 1;
			std::cout << std::endl;
	}

	std::cout << std::endl;
  return 0;
}
