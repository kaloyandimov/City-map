//
//  CityMap.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#include "CityMap.hpp"

Intersection* CityMap::get_intersection(const std::string& name) const {
    auto pos{std::find_if(intersections.begin(), intersections.end(), [&name](Intersection* intersection) {
        return intersection->get_name() == name;
    })};
    
    return pos != intersections.end() ? *pos : nullptr;
}

Intersection* CityMap::get_or_add_intersection(const std::string& name) {
    Intersection* intersection = get_intersection(name);
    
    if (intersection == nullptr) {
        intersection = new Intersection(name);
        intersections.push_back(intersection);
    }
    
    return intersection;
}

void CityMap::copy(const CityMap& other) {
    intersections.reserve(other.intersections.size());
    
    for (Intersection* intersection: other.intersections) {
        Intersection* head = get_or_add_intersection(intersection->get_name());
        
        for (auto street: intersection->get_streets()) {
            head->add_street(head, street.distance, get_or_add_intersection(street.tail->get_name()));
        }
    }
}

void CityMap::swap(CityMap& other) {
    std::swap(intersections, other.intersections);
}

void swap(CityMap& lhs, CityMap& rhs) {
    lhs.swap(rhs);
}

CityMap::CityMap(const CityMap& other) {
    copy(other);
}

CityMap& CityMap::operator=(const CityMap& other) {
    CityMap temp{other};
    swap(temp);
    
    return *this;
}

CityMap::~CityMap() {
    for (Intersection* intersection: intersections) {
        delete intersection;
    }
}

void CityMap::parse_intersection(const std::string& input) {
    std::istringstream ss{input};
    std::string headName;
    std::string tailName;
    unsigned distance;
    
    ss >> headName;
    
    Intersection* head{get_or_add_intersection(headName)};
    
    while (ss >> tailName >> distance) {
        head->add_street(head, distance, get_or_add_intersection(tailName));
    }
}

std::istream& operator>>(std::istream& in, CityMap& map) {
    std::string line;
    
    while (std::getline(in, line)) {
        map.parse_intersection(line);
    }
    
    return in;
}
