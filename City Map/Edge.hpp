//
//  Edge.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#ifndef Edge_hpp
#define Edge_hpp

#include "Hash.hpp"

template <typename T>
class Node;

template <typename T>
using Reference = std::reference_wrapper<const T>;

template <typename T>
struct Edge {
    Edge(const Node<T>&, unsigned);
    
    Reference<Node<T>> endpoint;
    unsigned weight;
};

template <typename T>
Edge(T, unsigned) -> Edge<T>;

template <typename T>
Edge<T>::Edge(const Node<T>& _endpoint, unsigned _weight):
    endpoint{_endpoint},
    weight{_weight} {}

template <typename T>
bool operator==(const Edge<T>& lhs, const Edge<T>& rhs) {
    return lhs.endpoint.get() == rhs.endpoint.get();
}

#endif /* Edge_hpp */
