// Sebastian Galguera under supervision and guide of V. Cubells
// Graph Vertex generic class for datastructure representation

// Guards
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <vector>

#include "Edge.hpp"

using datastruct::Edge;

// Namespace enclosing
namespace datastruct{

  // Class that constitutes a Graph Vertex structure using Raw Pointers
  template <class V, class E>
  class Vertex{

    V m_info;
    std::vector<Edge<V, E> *> m_edges;

  public:

      Vertex() {}
      Vertex(V t_info) : m_info(t_info) {}
      ~Vertex();

      // Information accesors
      V getInfo() const;
      void setInfo(const V &);

      // Edge operations
      std::vector<Edge<V, E> *> * getEdges();
      void addEdge(Edge<V, E> *);
      void removeEdge(Edge<V, E> *);

      // Operator overloading
      bool operator!=(Vertex<V, E> &) const;

      template <class Vn, class En>
      friend std::ostream & operator<<(std::ostream & , const Vertex<Vn, En> &);
  };



  template <class V, class E>
  Vertex<V, E>::~Vertex(){
      for (auto edge : m_edges){
          delete edge;
      }
      m_edges.clear();
  }

  template <class V, class E>
  V Vertex<V, E>::getInfo() const{
      return m_info;
  }

  template <class V, class E>
  void Vertex<V, E>::setInfo(const V & t_value){
      m_info = t_value;
  }

  template <class V, class E>
  std::vector<Edge<V, E> *> * Vertex<V, E>::getEdges(){
      return &m_edges;
  }

  template <class V, class E>
  void Vertex<V, E>::addEdge(Edge<V, E> * t_edge){
      m_edges.push_back(t_edge);
  }

  template <class V, class E>
  void Vertex<V, E>::removeEdge(Edge<V, E> * t_edge){
      auto edgeToDelete = find(m_edges.begin(), m_edges.end(), t_edge);
      m_edges.erase(edgeToDelete);
  }

  template <class V, class E>
  bool Vertex<V, E>::operator!=(Vertex<V, E> & t_other) const{
      return m_info != t_other.m_info;
  }

  template <class V, class E>
  std::ostream & operator<<(std::ostream & t_os , const  Vertex<V, E> & t_vertex){
      t_os << "Vertex: " << t_vertex.m_info << std::endl;

      for (auto edge : t_vertex.m_edges) {
          t_os << *edge;
      }

      return t_os;
  }



}

#endif /* VERTEX_HPP */
