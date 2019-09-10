// Sebastian Galguera
// Code to try BinaryTree features

#include <iostream>
#include <array>
#include <math.h>

#include "BinaryTree.hpp"

using datastruct::BinaryTree;

// Avoiding macros
namespace bttestdata{
  class Specs{
  public:
    static constexpr int CHILDREN { 2 };
    static constexpr int NELEMENTS { 15 };
  };
};

typedef bttestdata::Specs Specs;
typedef std::array<BNode<int> *, Specs::NELEMENTS> BPTRArray;

bool ensembleTree(BPTRArray &, BinaryTree<int> &);
void initBPTRArray(BPTRArray &);

int main(){

  // Array of pointers to BNodes
  BPTRArray nodes;
  BinaryTree<int> btree;

  initBPTRArray(nodes);

  ensembleTree(nodes, btree);

  // Tree Traverse
  std::cout << "PRE ORDER" << std::endl;
  btree.preOrder();
  std::cout << "\n" << std::endl;

  std::cout << "IN ORDER" << std::endl;
  btree.inOrder();
  std::cout << "\n" << std::endl;

  std::cout << "POST ORDER" << std::endl;
  btree.postOrder();
  std::cout << "\n" << std::endl;

  // Tree properties verifier
  std::cout << "LEAVES" << std::endl;
  btree.isLeaf();
  std::cout << "\n" << std::endl;

  std::cout << "ANCESTORS" << std::endl;
  btree.ancestors(nodes[8]);
  std::cout << "\n" << std::endl;

  std::cout << "SIBLINGS" << std::endl;
  btree.siblings(nodes[6]);
  std::cout << "\n" << std::endl;

  std::cout << "VALIDATE SIBLINGS" << std::endl;
  std::cout << btree.validateSiblings(nodes[7], nodes[8]);
  std::cout << "\n" << std::endl;

  std::cout << "COUSINS" << std::endl;
  btree.cousins(nodes[11], nodes[0]);
  std::cout << "\n" << std::endl;

  std::cout << "VALIDATE COUSINS" << std::endl;
  std::cout << btree.validateCousins(nodes[10], nodes[13]);
  std::cout << "\n" << std::endl;

  std::cout << "SUM NODES" << std::endl;
  std::cout << btree.sumNodes(nodes[0]);
  std::cout << "\n" << std::endl;

  std::cout << "SEARCH FOR NODE" << std::endl;
  BNode<int> * found = btree.search(7);
  if(found){ std::cout << *found; }
  std::cout << "\n" << std::endl;

  std::cout << "CHECK IF VALUE IS IN TREE" << std::endl;
  std::cout << btree.exists(1);
  std::cout << "\n" << std::endl;

  std::cout << "INVERTING TREE" << std::endl;
  btree.invert();
  btree.preOrder();
  std::cout << "\n" << std::endl;

  return 1;
}

// Function to ensemble tree from list 1 - 15
bool ensembleTree(BPTRArray & t_nodes, BinaryTree<int> & t_btree){

  t_btree.setRoot(t_nodes[0]);
  int inserted = 0;

  for(auto i = 0; i < floor(t_nodes.size() / Specs::CHILDREN); i++){
    for(auto j = 1 + i; j < 3 + i; j++){
      inserted += t_btree.insert(t_nodes[i], t_nodes[i + j]);
    }
  }
  return (inserted - Specs::NELEMENTS) == 0;
}

// Function to initialize the BNode pointers array
void initBPTRArray(BPTRArray & t_nodes){
  for(auto i = 0; i < t_nodes.size(); i++){
    t_nodes[i] = new BNode<int>(i + 1);
  }
}
