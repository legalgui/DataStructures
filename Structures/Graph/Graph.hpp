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
    for (auto node : m_nodes){
        delete node;
    }
    m_nodes.clear();
  }

  template <class V, class E>
  void Graph<V, E>::addVertex(Vertex<V, E> * t_vertex){
    m_nodes.push_back(t_vertex);
  }

  template <class V, class E>
  void Graph<V, E>::addEdge(Vertex<V, E> * t_source, Vertex<V, E> * t_target, const E & t_info){
    Edge<V, E> * edge = new Edge<V, E>(t_info, t_target);
    t_source->addEdge(edge);
  }

  template <class V, class E>
  void Graph<V, E>::removeEdge(Vertex<V, E> * t_source, Vertex<V, E> * t_target, const E & t_info){
    for(auto edge : *t_source->getEdges()){
      if(edge->getTarget() == t_target && edge->getInfo() == t_info){
        t_source->removeEdge(edge);
      }
    }
  }

  template <class V, class E>
  bool Graph<V, E>::isComplete(){
    bool complete = true;
    std::map<V, int> paths;
    int complementary = m_nodes.size() - 1;

    for(auto vertex : m_nodes){

      // Check if there's less edges than destinations
      // To see if we can have an early stop
      if(vertex->getEdges()->size() < complementary){
        complete = false;
        break;
      }

      // Check that there aren't two edges to the same destination
      // In case there wasn't an early stop
      for(auto edge : *vertex->getEdges()){
        paths[edge->getTarget()->getInfo()]++;
      }

      if(paths.size() < complementary){
        complete = false;
        break;
      }
      paths.clear();
    }

    return complete;
  }

  template <class V, class E>
  std::ostream & operator<<(std::ostream & t_os, const Graph<V, E> & t_graph){
    t_os << "--- Graph: " << t_graph.m_name << " ---" << std::endl;
    for (auto node : t_graph.m_nodes){
        t_os << *node;
    }
    return t_os;
  }


}

#endif /* GRAPH_HPP */
