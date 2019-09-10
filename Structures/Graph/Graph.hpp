// Sebastian Galguera under supervision and guide of V. Cubells
// Graph generic class for datastructure representation

// Guards
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <algorithm>
#include <map>

#include "Vertex.hpp"

using datastruct::Edge;
using datastruct::Vertex;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Graph structure using Raw Pointers
  template <class V, class E>
  class Graph{

    std::string m_name;
    std::vector<Vertex<V, E> *> m_nodes;

  public:

    Graph() {}
    Graph(std::string t_name): m_name(t_name) {}
    ~Graph();

    // Vertex operators
    void addVertex(Vertex<V, E> *);

    // Edge operators
    void addEdge(Vertex<V, E> *, Vertex<V, E> *, const E &);
    void removeEdge(Vertex<V, E> *, Vertex<V, E> *, const E &);
    bool isComplete();

    // Operator overloading
    template <class Vn, class En>
    friend std::ostream & operator<<(std::ostream &, const Graph<Vn, En> &);
  };

  template <class V, class E>
  Graph<V, E>::~Graph(){
      return;
  }

  template <class V, class E>
  void Graph<V, E>::addVertex(Vertex<V, E> * t_vertex){
      return;
  }

  template <class V, class E>
  void Graph<V, E>::addEdge(Vertex<V, E> * t_source, Vertex<V, E> * t_target, const E & t_info){
      return;
  }

  template <class V, class E>
  void Graph<V, E>::removeEdge(Vertex<V, E> * t_source, Vertex<V, E> * t_target, const E & t_info){
      return;
  }

  template <class V, class E>
  bool Graph<V, E>::isComplete(){
      return;
  }

  template <class V, class E>
  std::ostream & operator<<(std::ostream & os, const Graph<V, E> & graph){
      return;
  }


}

#endif /* GRAPH_HPP */
