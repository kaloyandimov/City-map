//
//  BFSIterator.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 10.01.21.
//

#ifndef BFSIterator_hpp
#define BFSIterator_hpp

#include <unordered_set>
#include <queue>

#include "Iterator.hpp"
#include "Edge.hpp"
#include "Node.hpp"

template <typename T>
class BFSIterator: public Iterator<T, BFSIterator> {
 public:
    BFSIterator(const Node<T>* node = nullptr);

    BFSIterator<T>& operator++();
    
private:
    std::unordered_set<const Node<T>*> visited;
    std::queue<const Node<T>*> to_be_visited;

    void push(const Node<T>*);
};

template <typename T>
BFSIterator<T>::BFSIterator(const Node<T>* node):
    Iterator<T, BFSIterator>{node} {
        if (node) push(node);
}

template <typename T>
BFSIterator<T>& BFSIterator<T>::operator++() {
    if (!to_be_visited.empty()) {
        this->current = to_be_visited.front();
        to_be_visited.pop();
        
        push(this->current);
    }
    else {
        this->current = nullptr;
    }

    return *this;
}

template <typename T>
void BFSIterator<T>::push(const Node<T>* v) {
    visited.insert(v);
    
    for (const Edge<T>& x: v->get_edges()) {
        const Node<T>* adj{&x.endpoint.get()};
        
        if (visited.find(adj) == visited.end()) {
            to_be_visited.push(adj);
            visited.insert(adj);
        }
    }
}

#endif /* BFSIterator_hpp */
