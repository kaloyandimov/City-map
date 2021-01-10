//
//  Graph.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <unordered_map>

#include "Node.hpp"

template <typename T>
class Graph {
 public:
    bool empty() const;
    std::size_t size() const;
    bool contains(const T&) const;
    
    void add_vertex(const T&);
    void add_edge(const T&, unsigned, const T&);
    
 private:
    std::unordered_map<T, Node<T>> nodes;
    
    const T& referenced(const T&) const;
};

template <typename T>
bool Graph<T>::empty() const {
    return nodes.empty();
}

template <typename T>
std::size_t Graph<T>::size() const {
    return nodes.size();
}

template <typename T>
bool Graph<T>::contains(const T& x) const {
    return nodes.find(x) != nodes.end();
}

template <typename T>
void Graph<T>::add_vertex(const T& x) {
    if (!contains(x)) {
        nodes[x];
        
        nodes[x] = {referenced(x)};
    }
}

template <typename T>
void Graph<T>::add_edge(const T& head, unsigned weight, const T& tail) {
    add_vertex(head);
    add_vertex(tail);

    nodes[head].add_edge(nodes[tail], weight);
}

template <typename T>
const T& Graph<T>::referenced(const T& x) const {
    return nodes.find(x)->first;
}

#endif /* Graph_hpp */
