//
//  Graph.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#include "Graph.hpp"

template <typename T>
bool Graph<T>::empty() const {
    return vertices.empty();
}

template <typename T>
void Graph<T>::add_vertex(const T& v) {
    vertices[v];
}

template <typename T>
void Graph<T>::add_edge(const T& head, unsigned weight, const T& tail) {
    add_vertex(head);
    add_vertex(tail);
    
    vertices[head].emplace(tail, weight);
}
