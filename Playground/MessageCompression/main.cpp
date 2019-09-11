// Sebastian Galguera
// Code to implement Message Compression System

#include <iostream>
#include <vector>

//#include "PriorityHandler.hpp"

//using datastruct::PriorityHandler;


#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../Structures/LinkedList/LinkedList.hpp"
using datastruct::LinkedList;
#include "BinaryTree.h"
#include "Terminal.h"
#include "Tabla.h"


void espacio()
{
    for(int i = 0; i<=15; i++)
    {
        std::cout << " " << std::endl;
    }
}

int huffman(std::string, int &);

int main()
{
    espacio();
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
                    std::cout << "Por favor, de de alta una terminal.\n\nNombre de la terminal: ";
                    std::string nombre;
                    std::cin.ignore();
                    std::getline (std::cin,nombre);

                    std::cout << "Password de la terminal: ";
                    std::string password;
                    std::getline (std::cin,password);

                    listaTerminales.insertBack(new Terminal(nombre, password, terminalID));

                    std::cout << "\n\tTerminal " << nombre << " creada con exito.\n\tEl password es: " << password << " con Posicion: " << terminalID << std::endl << std::endl;
                    terminalID++;

                    break;
                }
                case 2:
                {
                    if (listaTerminales.size() == 0){
                        std::cout << "\nNo hay terminales aun." << std::endl;
                    }
                    else{
                        if (listaTerminales.at(0)->getInfo()->listaMensajesEnviados.size()){

                            std::string sError = listaTerminales.at(0)->getInfo()->listaMensajesEnviados.at(0)->getInfo();
                            huffman(sError, auxHuffman);

                            if (auxHuffman == 1){
                                std::cout << "La terminal " << listaTerminales.at(0)->getInfo()->getNombre() << " no funciona correctamente." << std::endl;
                                std::cout << "Apagando..." << std::endl;
                                listaTerminales.remove(0);
                                terminalID--;

                            }
                            else if (auxHuffman == 0){
                                std::cout << "La terminal " << listaTerminales.at(0)->getInfo()->getNombre() << " funciona correctamente." << std::endl;
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
            std::cout << "\nPor favor, ingrese los datos de acceso.\n\nNombre: ";

            std::string nombre;
            std::cin.ignore();
            std::getline (std::cin,nombre);

            std::cout << "Password: ";
            std::string password;
            std::getline (std::cin,password);

            int acceso = 0;

            for(int i = 0; i < listaTerminales.size(); i++){
                if ((nombre == listaTerminales.at(i)->getInfo()->getNombre()) && (password == listaTerminales.at(i)->getInfo()->getPassword())){
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
                std::cout << "\nBienvenido a la terminal " << listaTerminales.at(auxID)->getInfo()->getNombre() << " con Posicion " << auxID  << std::endl;
                std::cout << "\n1.- Enviar mensaje.\n2.- Ver historial de envios.\n3.- Ver historial de recibidos.\n4.- Salir.\n\nPor favor, seleccione una opcion: ";
                std::cin >> conmutador;
                switch(conmutador)
                {
                    case 1:
                    {

                        std::cout << "\nIngrese el Nombre de la terminal receptora: ";
                        std::string nombre;
                        std::cin.ignore();
                        std::getline(std::cin,nombre);

                        acceso = 0;
                        int auxIDDos;

                        for(int i = 0; i < listaTerminales.size(); i++){
                            if (nombre == listaTerminales.at(i)->getInfo()->getNombre()){
                                acceso = 1;
                                auxIDDos = i;

                                std::cout << "Por favor, ingrese la frase a codificar.\nFrase: ";
                                std::string frase, fraseCopy, codeAux;
                                std::getline (std::cin,frase);
                                fraseCopy = frase;
                                LinkedList<BNode *> listaOrdenadaFrase;

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
                                        BNode *leafNode = new BNode(auxLeafChar, charCount);
                                        listaOrdenadaFrase.insertOrdered(leafNode, 2);
                                    }
                                }
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "          TABLA DE FRECUENCIAS                " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;
                                for(int i = 0; i < listaOrdenadaFrase.size(); i++){
                                    std::cout << *listaOrdenadaFrase.at(i)->getInfo() << std::endl;
                                }

                                /*Aqui comienza la construccion del arbol.*/
                                std::cout << "----------------------------------------------" << std::endl;
                                std::cout << "           CONSTRUCCION DEL ARBOL             " << std::endl;
                                std::cout << "----------------------------------------------" << std::endl;
                                while (listaOrdenadaFrase.size()!=1){

                                    BNode * leftBNode = listaOrdenadaFrase.removeFront()->getInfo();
                                    leftBNode->setPathBinario(0);
                                    std::cout << "left node " << *leftBNode << std::endl;

                                    BNode *  rightBNode = listaOrdenadaFrase.removeFront()->getInfo();
                                    rightBNode->setPathBinario(1);
                                    std::cout << "right node " << *rightBNode<< std::endl;

                                    std::string dataInterna = leftBNode->getCaracter();
                                    dataInterna += rightBNode->getCaracter();
                                    int frecuenciaInterna = (leftBNode->getFrecuencia()+rightBNode->getFrecuencia());
                                    BNode * internalNode = new BNode(dataInterna, frecuenciaInterna);
                                    std::cout <<  "internal node " << *internalNode << std::endl;

                                    internalNode->setParent(NULL);
                                    internalNode->setLeft(leftBNode);
                                    leftBNode->setParent(internalNode);
                                    internalNode->setRight(rightBNode);
                                    rightBNode->setParent(internalNode);
                                    listaOrdenadaFrase.insertOrdered(internalNode, 2);
                                }
                                BinaryTree arbolHuffman(listaOrdenadaFrase.removeFront()->getInfo());
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

                                        BNode * auxBN = arbolHuffman.search(auxString);
                                        Stack<int> stackPath;

                                        stackPath.push(auxBN->getPathBinario());
                                        int k;
                                        std::string code;

                                        while(auxBN->getParent()!=arbolHuffman.getRaiz()){
                                            stackPath.push(auxBN->getParent()->getPathBinario());
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
                                        if (fraseCopy[i] == listTabla.at(j)->getInfo()->getLetra()){
                                                codeAux += listTabla.at(j)->getInfo()->getCode();
                                        }
                                    }
                                }
                                std::cout << codeAux;
                                float asci = 8;
                                float x = (1-(codeAux.size()/(fraseCopy.size()*asci)))*100;
                                std::cout << "\nBits originales: "<< fraseCopy.size()*8 << "\nBits finales: " << codeAux.size() << "\nEconomizacion: %" << x << std::endl;

                                listaTerminales.at(auxID)->getInfo()->setEnviado(codeAux);
                                listaTerminales.at(auxIDDos)->getInfo()->setRecibido(codeAux);
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
                        for (int i = 0; i < listaTerminales.at(auxID)->getInfo()->listaMensajesEnviados.size(); i++){
                            std::cout << listaTerminales.at(auxID)->getInfo()->listaMensajesEnviados.at(i)->getInfo() << std::endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        std::cout << "----------------------------------------------" << std::endl;
                        std::cout << "             HISTORIAL DE RECIBIDOS           " << std::endl;
                        std::cout << "----------------------------------------------" << std::endl;
                        for (int i = 0; i < listaTerminales.at(auxID)->getInfo()->listaMensajesRecibidos.size(); i++){
                            std::cout << listaTerminales.at(auxID)->getInfo()->listaMensajesRecibidos.at(i)->getInfo() << std::endl;
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
                std::cout << "Lo sentimos, nombre o password erroneos.\n" << std::endl;
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

int huffman(std::string binary, int &auxHuffman)
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
