//
//  Iterator.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 10.01.21.
//

#ifndef Iterator_hpp
#define Iterator_hpp

#include "Node.hpp"

template <typename T, template<typename> typename It>
class Iterator {
 public:
    Iterator(const Node<T>*);
    
    const T& operator*() const;
    
    operator bool() const;
    bool operator==(const It<T>&) const;
    bool operator!=(const It<T>&) const;
    
 protected:
    const Node<T>* current;
};

template <typename T, template<typename> typename It>
Iterator<T, It>::Iterator(const Node<T>* node):
    current{node} {}

template <typename T, template<typename> typename It>
const T& Iterator<T, It>::operator*() const {
    return current->get_data();
}

template <typename T, template<typename> typename It>
Iterator<T, It>::operator bool() const {
    return current != nullptr;
}

template <typename T, template<typename> typename It>
bool Iterator<T, It>::operator==(const It<T>& other) const {
    return current == other.current;
}

template <typename T, template<typename> typename It>
bool Iterator<T, It>::operator!=(const It<T>& other) const {
    return !(*this == other);
}

#endif /* Iterator_hpp */
