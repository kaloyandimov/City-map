//
//  Node.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 10.01.21.
//

#ifndef Node_hpp
#define Node_hpp

#include <unordered_set>

#include "Edge.hpp"

template <typename T>
class Node {
 public:
    Node(const T& = T());
    
    void add_edge(const Node<T>&, unsigned);
    
    const T& get_data() const;
    const std::unordered_set<Edge<T>>& get_edges() const;
    
    bool operator==(const Node<T>&) const;
    
 private:
    Reference<T> data;
    std::unordered_set<Edge<T>> edges;
};

template <typename T>
Node(T) -> Node<T>;

template <typename T>
Node<T>::Node(const T& _data):
    data{_data} {}

template <typename T>
void Node<T>::add_edge(const Node<T>& endpoint, unsigned weight) {
    edges.emplace(endpoint, weight);
}

template <typename T>
const T& Node<T>::get_data() const {
    return data;
}

template <typename T>
const std::unordered_set<Edge<T>>& Node<T>::get_edges() const {
    return edges;
}

template <typename T>
bool Node<T>::operator==(const Node<T>& other) const {
    return data.get() == other.data.get();
}

#endif /* Node_hpp */
