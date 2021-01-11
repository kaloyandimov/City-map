//
//  DFSIterator.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#ifndef DFSIterator_hpp
#define DFSIterator_hpp

#include <unordered_set>
#include <stack>

#include "Iterator.hpp"
#include "Edge.hpp"
#include "Node.hpp"

template <typename T>
class DFSIterator: public Iterator<T, DFSIterator> {
 public:
    DFSIterator(const Node<T>* node = nullptr);

    DFSIterator<T>& operator++();
    
private:
    std::unordered_set<const Node<T>*> visited;
    std::stack<const Node<T>*> to_be_visited;

    void push(const Node<T>*);
};

template <typename T>
DFSIterator<T>::DFSIterator(const Node<T>* node):
    Iterator<T, DFSIterator>{node} {
        if (node) push(node);
}

template <typename T>
DFSIterator<T>& DFSIterator<T>::operator++() {
    if (!to_be_visited.empty()) {
        this->current = to_be_visited.top();
        to_be_visited.pop();
        
        push(this->current);
    }
    else {
        this->current = nullptr;
    }

    return *this;
}

template <typename T>
void DFSIterator<T>::push(const Node<T>* v) {
    visited.insert(v);
    
    for (const Edge<T>& x: v->get_edges()) {
        const Node<T>* adj{&x.endpoint.get()};
        
        if (visited.find(adj) == visited.end()) {
            to_be_visited.push(adj);
            visited.insert(adj);
        }
    }
}

#endif /* DFSIterator_hpp */
