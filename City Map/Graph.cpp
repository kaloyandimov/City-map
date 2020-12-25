//
//  Graph.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#include "Graph.hpp"

namespace std {
    template <typename T>
    struct hash<ConstRef<T>> {
        size_t operator()(ConstRef<T> x) const noexcept {
            return hash<T>{}(x);
        }
    };
}

template <typename T>
bool Graph<T>::empty() const {
    return vertices.empty();
}

template <typename T>
bool Graph<T>::contains(const T& x) const {
    return vertices.find(x) != vertices.end();
}

template <typename T>
void Graph<T>::add_vertex(const T& x) {
    vertices[x];
}

template <typename T>
void Graph<T>::add_edge(const T& head, unsigned weight, const T& tail) {
    add_vertex(head);
    add_vertex(tail);
    
    vertices[head].emplace(tail, weight);
}

template <typename T>
bool Graph<T>::has_path(const T& begin, const T& end) const {
    std::unordered_set<ConstRef<T>> traversed;
    std::queue<ConstRef<T>> to_be_traversed;
    
    if (contains(begin) && contains(end)) {
        to_be_traversed.push(const_map_ref(begin));
        traversed.insert(const_map_ref(begin));
    }
    
    while (!to_be_traversed.empty()) {
        const T& curr{to_be_traversed.front()};
        to_be_traversed.pop();
        
        for (const Edge<T>& e: vertices.at(curr)) {
            const T& next{const_map_ref(e.endpoint)};
            
            if (next == end) return true;
            
            if (traversed.find(next) == traversed.end()) {
                to_be_traversed.push(next);
                traversed.insert(next);
            }
        }
    }
    
    return false;
}

template <typename T>
const T& Graph<T>::const_map_ref(const T& x) const {
    return vertices.find(x)->first;
}

template <typename T>
bool Graph<T>::reaches_all(const T& x) const {
    std::unordered_set<ConstRef<T>> traversed;
    std::queue<ConstRef<T>> to_be_traversed;
    
    if (contains(x)) {
        to_be_traversed.push(const_map_ref(x));
        traversed.insert(const_map_ref(x));
    }
    
    while (!to_be_traversed.empty()) {
        const T& curr{to_be_traversed.front()};
        to_be_traversed.pop();
        
        for (const Edge<T>& e: vertices.at(curr)) {
            const T& next{const_map_ref(e.endpoint)};
            
            if (traversed.find(next) == traversed.end()) {
                to_be_traversed.push(next);
                traversed.insert(next);
            }
        }
    }
    
    return vertices.size() == traversed.size();
}

template <typename T>
bool Graph<T>::makes_circuit(const T& x) const {
    std::unordered_set<ConstRef<T>> traversed;
    std::stack<ConstRef<T>> to_be_traversed;
    
    if (contains(x)) {
        to_be_traversed.push(const_map_ref(x));
        traversed.insert(const_map_ref(x));
    }
    
    while (!to_be_traversed.empty()) {
        const T& curr{to_be_traversed.top()};
        to_be_traversed.pop();
        
        for (const Edge<T>& e: vertices.at(curr)) {
            const T& next{const_map_ref(e.endpoint)};
            
            if (next == x) return true;
            
            if (traversed.find(next) == traversed.end()) {
                to_be_traversed.push(next);
                traversed.insert(next);
            }
        }
    }
    
    return false;
}
