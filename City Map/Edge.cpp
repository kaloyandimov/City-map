//
//  Edge.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#include "Edge.hpp"

template <typename T>
Edge<T>::Edge(const T& _endpoint, unsigned _weight):
    endpoint{_endpoint},
    weight{_weight} {}

template <typename T>
bool operator==(const Edge<T>& lhs, const Edge<T>& rhs) {
    return lhs.endpoint == rhs.endpoint;
}

namespace std {
    template <typename T>
    struct hash<Edge<T>> {
        size_t operator()(const Edge<T>& e) const noexcept {
            return hash<T>{}(e.endpoint);
        }
    };
}
