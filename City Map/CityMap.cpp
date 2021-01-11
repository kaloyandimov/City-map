//
//  CityMap.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#include "CityMap.hpp"

void CityMap::add_intersection(const std::string& intersection) {
    intersections.add_node(intersection);
}

void CityMap::add_street(const std::string& from, unsigned length, const std::string& to) {
    intersections.add_edge(from, length, to);
}

bool CityMap::has_road(const std::string& from, const std::string& to) const {
    if (!intersections.contains(from) || !intersections.contains(to)) {
        return false;
    }
    
    for (const std::string& curr : intersections.bfs(from)) {
        if (curr == to) {
            return true;
        }
    }
    
    return false;
}

bool CityMap::reaches_all(const std::string& from) const {
    if (!intersections.contains(from)) return false;
    
    std::unordered_set<
        Reference<std::string>,
        std::hash<std::string>,
        std::equal_to<std::string>
    > reached;
    
    for (const std::string& curr : intersections.bfs(from)) {
        reached.insert(curr);
    }
    
    return reached.size() == intersections.size();
}

bool CityMap::makes_circuit(const std::string& from) const {
    if (!intersections.contains(from)) return false;
    
    BFSIterator<std::string> next{++intersections.bfs(from).begin()};
    
    if (!next) return false;
    
    for (const std::string& curr: intersections.bfs(*next)) {
        if (curr == from) {
            return true;
        }
    }
    
    return false;
}

void CityMap::parse_intersection(const std::string& input) {
    std::istringstream ss{input};
    std::string from;
    std::string to;
    unsigned length;
    
    ss >> from;
    
    while (ss >> to >> length) {
        add_street(from, length, to);
    }
}

std::istream& operator>>(std::istream& in, CityMap& map) {
    std::string line;
    
    while (std::getline(in, line)) {
        map.parse_intersection(line);
    }
    
    return in;
}
