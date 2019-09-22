// Sebastian Galguera
// Helper functions and structures for Huffman Coding implementation

// Guards
#ifndef HELPER_HPP
#define HELPER_HPP

// Namespace enclosing
namespace huffmanutilities{

  // Structure for symbol code handling
  struct Table{
    Table(char t_symbol, std::string t_code): symbol(t_symbol), code(t_code){}
    char m_symbol;
    std::string m_code;
  };


  // Session handlers
  namespace session{

    // Function for logging in
    bool login(LinkedList<Terminal *> & t_terminals, int & sessionID){
      std::cout << "\nPlease, specify the login information.\n\n Name: ";

      std::string name;
      std::cin.ignore();
      std::getline(std::cin,name);

      std::cout << "Password: ";
      std::string password;
      std::getline(std::cin, password);

      for(int i = 0; i < t_terminals.size(); i++){
        auto terminal = t_terminals.at(i)->getInfo();
        if ((name == terminal->getName()) && (password == terminal->getPassword())){
          sessionID = i;
          return true;
        }
      }
      return false;
    }


    // Function to connect to other terminal
    bool connect(LinkedList<Terminal *> & t_terminals, int & t_targetID){
      std::cout << "\nSpecify the name of the receiving Terminal: ";
      std::string name;
      std::cin.ignore();
      std::getline(std::cin,name);

      for(int i = 0; i < t_terminals.size(); i++){
        auto terminal = t_terminals.at(i)->getInfo();
        if (name == terminal->getName()){
          t_targetID = i;
          return true;
        }
      }
      return false;
    }
  }

  // Output handlers
  namespace output{
    // Function to print compression summary
    void printSummary(std::string & t_code, std::string & t_msg){
      float asci = 8;
      float percentage = (1 - (t_code.size() / (t_msg.size() * asci))) * 100;
      std::cout << "\nOriginal size (in bits): "<< t_msg.size() * 8 << std::endl;
      std::cout << "Compressed size (in bits): " << t_code.size() << std::endl;
      std::cout <<  "\nSaving: %" << percentage << std::endl;
    }

    // Function to print titles
    void printHeader(std::string t_title){
      std::cout << "\n----------------------------------------------" << std::endl;
      std::cout << "         " << t_title << "         " << std::endl;
      std::cout << "----------------------------------------------" << std::endl;

      if(t_title == "MAIN MENU"){
        std::cout << "\n 1. Use as Admin.\n 2. Use as User.\n 0. Quit.\n\n Please, select an option: ";
      }else if(t_title == "ADMIN MENU"){
        std::cout << "\n 1. Create Terminal.\n 2. Simulate error.\n 3. Quit.\n Please, select an option: ";
      }else if(t_title == "TERMINAL MENU"){
        std::cout << "\n1. Send message.\n2. See sent history.\n3. See received history.\n4. Quit.\n\n Please, select an option: ";
      }else if(t_title == "ERROR SIMULATOR"){
        std::cout << "For demonstration purposes, just the four first bits will be taken: " << std::endl;;
        std::cout << "The message sequence is: ";
      }
    };
  }

  namespace terminalhandling{
    void createTerminal(LinkedList<Terminal *> & t_terminals, int & t_terminalID){
      std::cout << " Please, specify the Terminal information.\n\n Name: ";

      std::string name;
      std::cin.ignore();
      std::getline(std::cin,name);

      std::cout << " Password: ";
      std::string password;
      std::getline(std::cin,password);

      t_terminals.insertBack(new Terminal(name, password, t_terminalID));

      std::cout << "\n\tTerminal " << name << " creation succesful." << std::endl;
      std::cout << "\tThe password is: " << password;
      std::cout << " with Position: " << t_terminalID << "\n" << std::endl;
      t_terminalID++;
    }

    // Function to simulate a random error and correct signal via Hamming Code
    bool hammingCode(std::string t_bin){
      int bits[7];
      output::printHeader("ERROR SIMULATOR");

      for (int i = 0; i < 4; i++){ std::cout << t_bin[i] << " "; }

      for (int i = 0; i <= 4; i++){
        if (i != 3){
          if(t_bin[i] == '0'){ bits[i] = 0;
          }else{ bits[i] = 1; }
        }
      }

      bits[6] = bits[0]^bits[2]^bits[4];
      bits[5] = bits[0]^bits[1]^bits[4];
      bits[3] = bits[0]^bits[1]^bits[2];

      printf("\nThe sequence with parity bits is: \n");
      for (int i = 0; i < 7; i++) { std::cout << bits[i] << " "; }

      std::cout << "\nVerifying if there's a problem..." << std::endl;

      srand (time(NULL));
      int v1 { rand() % 2 };
      int v2 { rand() % 8 };
      int parity[7];
      int bit { 3 } ;

      if (v1 == 0){
          bit = 0;
      }else{
        for(int i = 0; i < 7; i++){ parity[i] = bits[i]; }
        if (parity[v2] == 0){ parity[v2] = 1;
        }else{ parity[v2] = 0; }

        int bitOne, bitTwo, bitThree;
        bitOne = parity[6]^parity[4]^parity[2]^parity[0];
        bitTwo = parity[5]^parity[4]^parity[1]^parity[0];
        bitThree = parity[3]^parity[2]^parity[1]^parity[0];
        bit = bitThree * 4 + bitTwo * 2 + bitOne;
      }

      if(bit == 0){
        std::cout << "\nNo error was found." << std::endl;
        return false;
      }else{
        std::cout << "\nError in position: " << 8 - bit << "\nThe corrected message is: " << std::endl;;
        if(parity[7 - bit] == 0){ parity[7 - bit] = 1;
        }else{ parity[7 - bit] = 0; }
        for (int i = 0; i < 7; i++){ printf("%d ",parity[i]); }
        return true;
      }
      return false;
    }

    // Function to run a terminal test
    void terminalTest(LinkedList<Terminal *> & t_terminals, int & t_terminalID){
      if(t_terminals.size()){
        std::cout << "\tSimulating random error in the first terminal and first message." << std::endl;
        auto testTerminal = t_terminals.at(0)->getInfo();

        if(testTerminal->getSent()->size()){

          std::string sError = testTerminal->getSent()->at(0)->getInfo();

          // Case there was an error and the hamming code corrected it
          if(hammingCode(sError)){
            std::cout << "The terminal " << testTerminal->getName() << " is not working properly." << std::endl;
            std::cout << "Shutting down..." << std::endl;
            t_terminals.remove(0);
            t_terminalID--;
          }else{
            std::cout << "The terminal " << testTerminal->getName() << " is working correctly." << std::endl;
          }
        }else{
          std::cout << "This terminal doesn't have sent messages." << std::endl;
        }
      }else{
        std::cout << "\n There are no terminals yet." << std::endl;
      }
    }
  }

  namespace huffman{

    // Function to fill the symbol queue
    void fillSymbolQueue(PriorityHandler<BNode<Symbol *> *> & t_ph,
      std::string & t_msg, std::string & t_msgCpy){

      std::cout << "Please, insert your message.\nMessage: ";
      std::getline (std::cin,t_msg);
      t_msgCpy = t_msg;

      for (int i = 0; i < t_msg.size(); i++){
        char auxChar = t_msg[i];
        if (auxChar != '-'){
          int charCount = 1;
          for(int j = i+1; j < t_msg.size(); j++){
            if(auxChar == t_msg[j]){
              t_msg[j] = '-';
              charCount++;
            }
          }
          std::string auxLeafChar { auxChar };
          BNode<Symbol *> *leafNode { new BNode<Symbol *>(new Symbol(auxLeafChar, charCount)) };
          t_ph.insertOrdered(leafNode);
        }
      }
    }

    // Function to get the huffman tree
    BinaryTree<Symbol *>  getTree(PriorityHandler<BNode<Symbol *> *> & t_ph){
      while (t_ph.getList()->size()!=1){

          // Create left and right nodes
          BNode<Symbol *> * left { t_ph.getList()->removeFront()->getInfo() };
          left->getInfo()->setBinaryPath(0);
          std::cout << "Left node " << *left->getInfo()  << std::endl;

          BNode<Symbol *> * right { t_ph.getList()->removeFront()->getInfo() };
          right->getInfo()->setBinaryPath(1);
          std::cout << "Right node " << *right->getInfo() << std::endl;

          // Create internal node
          std::string internalSymbol { left->getInfo()->getSymbol() };

          internalSymbol += right->getInfo()->getSymbol();

          int internalFrequency { (left->getInfo()->getFrequency() + right->getInfo()->getFrequency()) };

          BNode<Symbol *> * internal { new BNode<Symbol *>(new Symbol(internalSymbol, internalFrequency)) };
          std::cout <<  "Internal node " << *internal->getInfo() << std::endl;

          internal->setParent(NULL);

          internal->setLeft(left);
          left->setParent(internal);

          internal->setRight(right);
          right->setParent(internal);

          t_ph.insertOrdered(internal);
      }

      BinaryTree<Symbol *> huffmanTree;
      huffmanTree.setRoot(t_ph.getList()->removeFront()->getInfo());
      return huffmanTree;
    }

    // Function to search specific BNode without in-class template specification
    BNode<Symbol *> * searchHuffmanTree(Symbol * t_info, BNode<Symbol *> * t_root){
      BNode<Symbol *> * foundNode { nullptr };
      if(t_root){
        if(*t_root->getInfo() == *t_info){
          return t_root;
        }else{
          foundNode = searchHuffmanTree(t_info, t_root->getLeft());
          if(foundNode){ return foundNode; }
          return searchHuffmanTree(t_info, t_root->getRight());
        }
      }
      return foundNode;
    }

    // Function to get the tables
    LinkedList<Table *> getTables(BinaryTree<Symbol *> & t_huffmanTree, std::string t_msg){

      LinkedList<Table *> tables;

      for (int i = 0; i < t_msg.size(); i++){
        if (t_msg[i] != '-'){
          std::string auxString { t_msg[i] };
          // Get the node for the given symbol
          BNode<Symbol *> * auxBN { searchHuffmanTree(new Symbol(auxString, 0), t_huffmanTree.getRoot()) };

          Stack<int> stackPath;
          stackPath.push(auxBN->getInfo()->getBinaryPath());

          // Traverse binary path to the top
          while(auxBN->getParent() != t_huffmanTree.getRoot()){
              stackPath.push(auxBN->getParent()->getInfo()->getBinaryPath());
              auxBN = auxBN->getParent();
          }

          // Reverse the binary path by popping
          std::string code;
          while(!stackPath.empty()){
              std::ostringstream convert;
              convert << stackPath.pop()->getInfo();
              code += convert.str();
          }

          std::cout << "Symbol " << t_msg[i] << " Code " << code << std::endl;
          tables.insertBack(new Table(t_msg[i], code));;
        }
      }

      return tables;
    }

    // Translate compression
    std::string getCompression(LinkedList<Table *> & t_tables, std::string & t_msg){
      std::string code;
      for(int i = 0; i < t_msg.size(); i++){
          for(int j = 0; j < t_tables.size(); j++){
              if(t_msg[i] == t_tables.at(j)->getInfo()->m_symbol){
                      code += t_tables.at(j)->getInfo()->m_code;
              }
          }
      }
      return code;
    }
  }

}

#endif /* HELPER_HPP */
