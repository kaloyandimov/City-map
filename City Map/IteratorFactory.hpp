//
//  IteratorFactory.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 10.01.21.
//

#ifndef IteratorFactory_hpp
#define IteratorFactory_hpp

#include "BFSIterator.hpp"
#include "DFSIterator.hpp"
#include "Node.hpp"

template <typename T, template<typename> typename It>
class IteratorFactory {
 public:
    IteratorFactory(const Node<T>* = nullptr);

    It<T> begin();
    It<T> end();
    
 private:
    const Node<T>* node;
};

template <typename T, template<typename> typename It>
IteratorFactory<T, It>::IteratorFactory(const Node<T>* _node):
    node{_node} {}

template <typename T, template<typename> typename It>
It<T> IteratorFactory<T, It>::begin() {
    return It<T>{node};
}

template <typename T, template<typename> typename It>
It<T> IteratorFactory<T, It>::end() {
    return nullptr;
}

#endif /* IteratorFactory_hpp */
