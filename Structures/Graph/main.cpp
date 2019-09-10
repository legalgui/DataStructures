// Sebastian Galguera
// Code to try BinaryTree features

#include <iostream>
#include <array>

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Graph.hpp"

using datastruct::Graph;

// Avoiding macros
namespace graphtestdata{
  class Specs{
  public:
    static constexpr int NPEOPLE { 3 };
    static constexpr bool ISCOMPLETE { 1 };
  };
};

typedef graphtestdata::Specs Specs;
typedef std::array<Vertex<std::string, int> *, Specs::NPEOPLE> VertexArray;
typedef Graph<std::string, int> StringGraph;

void ensembleGraph(StringGraph &, VertexArray &);
void initVertexArray(VertexArray &);

int main(){
    srand (time(NULL));

    // Array of pointers to Vertex
    VertexArray vertex;
    // String and Int Graph
    StringGraph relationships("Connections");

    initVertexArray(vertex);
    ensembleGraph(relationships, vertex);

    std::cout << relationships << std::endl;
    std::cout << "IS GRAPH COMPLETE?" << std::endl;
    std::cout << relationships.isComplete() << std::endl;

  return 1;
}

// Function to ensemble graph from vertex
void ensembleGraph(StringGraph & t_graph, VertexArray & t_vertex){

  for(auto vertex : t_vertex){
    t_graph.addVertex(vertex);
  }

  if(Specs::ISCOMPLETE){
    for(int i = 0; i < t_vertex.size(); i++){
      for(int j = 0; j < t_vertex.size(); j++){
          if(i != j){
            t_graph.addEdge(t_vertex[i], t_vertex[j], rand() % 10 + 1);
          }
      }
    }
  }else{
    for(int i = 1; i < t_vertex.size(); i++){
      t_graph.addEdge(t_vertex[0], t_vertex[i], rand() % 10 + 1);
    }
  }
}

// Function to initialize the Vertex pointers array
void initVertexArray(VertexArray & t_vertex){
  std::array<std::string, Specs::NPEOPLE> names = {"SGO", "NDL", "RED"};
  for(int i = 0; i < Specs::NPEOPLE; i++){
    t_vertex[i] = new Vertex<std::string, int>(names[i]);
  }
}
