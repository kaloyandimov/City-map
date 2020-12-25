//
//  Graph.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stack>
#include <queue>

#include "Edge.hpp"
#include "Edge.cpp"

template <typename T>
using ConstRef = std::reference_wrapper<const T>;

namespace std {
    template <typename T>
    struct hash<ConstRef<T>>;
}

template <typename T>
using Edges = std::unordered_set<Edge<T>>;

template <typename T>
class Graph {
 public:
    bool empty() const;
    bool contains(const T&) const;
    
    void add_vertex(const T&);
    void add_edge(const T&, unsigned, const T&);
    
    bool has_path(const T&, const T&) const;
    bool reaches_all(const T&) const;
    bool makes_circuit(const T&) const;
    
 private:
    std::unordered_map<T, Edges<T>> vertices;
    
    const T& const_map_ref(const T&) const;
};

#endif /* Graph_hpp */
