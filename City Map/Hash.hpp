//
//  Hash.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 10.01.21.
//

#ifndef Hash_hpp
#define Hash_hpp

#include <functional>

template <typename T>
struct Edge;

template <typename T>
class Node;

namespace std {
template <typename T>
struct hash<Edge<T>> {
    size_t operator()(const Edge<T>& e) const noexcept {
        return hash<Node<T>>{}(e.endpoint);
    }
};

template <typename T>
struct hash<Node<T>> {
    size_t operator()(const Node<T>& v) const noexcept {
        return hash<T>{}(v.get_data());
    }
};
}

#endif /* Hash_hpp */
