//
//  Edge.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <functional>

template <typename T>
struct Edge {
    Edge(const T&, unsigned);
    
    T endpoint;
    unsigned weight;
};

template <typename T>
bool operator==(const Edge<T>&, const Edge<T>&);

namespace std {
    template <typename T>
    struct hash<Edge<T>>;
}

#endif /* Edge_hpp */
