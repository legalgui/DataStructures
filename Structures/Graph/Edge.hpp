// Sebastian Galguera under supervision and guide of V. Cubells
// Graph Edge generic class for datastructure representation

// Guards
#ifndef EDGE_HPP
#define EDGE_HPP

// Namespace enclosing
namespace datastruct{

  template <class V, class E>
  class Vertex;

  // Class that constitutes a Graph Edge structure using Raw Pointers
  template <class V, E>
  class Edge{

    E m_info;
    Vertex<V, E> * target = nullptr;

  public:

    Edge() {}
    Edge(const E t_info, const Vertex<V, E> * t_target): m_info(t_info), m_target(t_target) {};
    ~Edge() { t_target = nullptr; }

    // Information accesors
    E getInfo() const;
    void setInfo(const E &);

    // Target accesors
    Vertex<V, E> * getTarget() const;
    void setTarget(const Vertex<V, E> *);

    // Operator overloading
    template <class Vn, class En>
    friend std::ostream & operator<<(std::ostream & , const  Edge<Vn, En> &);
  };

  // Class specifications
  template <class V, class E>
  E Edge<V, E>::getInfo() const{
    return m_info;
  }

  template <class V, class E>
  void Edge<V, E>::setInfo(const E & t_value){
      m_info = t_value;
  }

  template <class V, class E>
  Vertex<V, E> * Edge<V, E>::getTarget() const{
      return m_target;
  }

  template <class V, class E>
  void Edge<V, E>::setTarget(const Vertex<V, E> * t_vertex){
      m_target = t_vertex;
  }

  template <class V, class E>
  std::ostream & operator<<(std::ostream & t_os , const  Edge<V, E> & t_edge){
      t_os << t_edge.info << " ---> " << t_edge.getTarget()->getInfo() << std::endl;
      return t_os;
  }


}

#endif /* EDGE_HPP */
