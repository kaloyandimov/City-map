//
//  Graph.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <unordered_map>

#include "IteratorFactory.hpp"
#include "Node.hpp"

template <typename T>
class Graph {
 public:
    bool empty() const;
    std::size_t size() const;
    bool contains(const T&) const;
    
    void add_node(const T&);
    void add_edge(const T&, unsigned, const T&);
    
    IteratorFactory<T, BFSIterator> bfs(const T&) const;
    IteratorFactory<T, DFSIterator> dfs(const T&) const;
    
 private:
    std::unordered_map<T, Node<T>> nodes;
    
    const T& referenced(const T&) const;
};

template <typename T>
Graph(T) -> Graph<T>;

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
void Graph<T>::add_node(const T& x) {
    if (!contains(x)) {
        nodes[x];
        
        nodes[x] = {referenced(x)};
    }
}

template <typename T>
void Graph<T>::add_edge(const T& head, unsigned weight, const T& tail) {
    add_node(head);
    add_node(tail);

    nodes[head].add_edge(nodes[tail], weight);
}

template <typename T>
IteratorFactory<T, BFSIterator> Graph<T>::bfs(const T& begin) const {
    if (!contains(begin)) return {};
    
    return {&nodes.at(begin)};
}

template <typename T>
IteratorFactory<T, DFSIterator> Graph<T>::dfs(const T& begin) const {
    if (!contains(begin)) return {};
    
    return {&nodes.at(begin)};
}

template <typename T>
const T& Graph<T>::referenced(const T& x) const {
    return nodes.find(x)->first;
}

#endif /* Graph_hpp */
