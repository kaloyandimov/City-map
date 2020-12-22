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

#include "Edge.hpp"
#include "Edge.cpp"

template <typename T>
using Edges = std::unordered_set<Edge<T>>;

template <typename T>
class Graph {
 public:
    bool empty() const;
    
    void add_vertex(const T&);
    void add_edge(const T&, unsigned, const T&);
    
 private:
    std::unordered_map<T, Edges<T>> vertices;
};

#endif /* Graph_hpp */
