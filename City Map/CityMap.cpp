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

bool CityMap::reaches_all(const std::string& startName) const {
    Intersection* start = get_intersection(startName);
    std::unordered_set<Intersection*> visited;
    std::queue<Intersection*> to_be_visited;
    
    to_be_visited.push(start);
    visited.insert(start);
    
    while (!to_be_visited.empty()) {
        Intersection* current{to_be_visited.front()};
        to_be_visited.pop();
        
        for (const Street& street: current->get_streets()) {
            if (!visited.contains(street.tail)) {
                to_be_visited.push(street.tail);
                visited.insert(street.tail);
            }
        }
    }
    
    return visited.size() == intersections.size();
}

bool CityMap::has_path(const std::string& startName, const std::string& endName) const {
    Intersection* start = get_intersection(startName);
    Intersection* end = get_intersection(endName);
    std::unordered_set<Intersection*> visited;
    std::queue<Intersection*> to_be_visited;
    
    to_be_visited.push(start);
    visited.insert(start);
    
    while (!to_be_visited.empty()) {
        Intersection* current{to_be_visited.front()};
        to_be_visited.pop();
        
        for (const Street& street : current->get_streets()) {
            if (street.tail == end) {
                return true;
            }
                
            if (!visited.contains(street.tail)) {
                to_be_visited.push(street.tail);
                visited.insert(street.tail);
            }
        }
    }
    
    return false;
}

bool CityMap::has_cycle_util(Intersection* curr, Intersection* end, std::unordered_set<Intersection*>& visited) const {
    if (curr == end) {
        return true;
    }
    
    if (visited.contains(curr)) {
        return false;
    }
    
    visited.insert(curr);
    
    return std::any_of(curr->get_streets().begin(), curr->get_streets().end(), [&](const Street& street) {
        return has_cycle_util(street.tail, end, visited);
    });
}

bool CityMap::has_cycle(const std::string& name) const {
    std::unordered_set<Intersection*> visited;
    Intersection* start{get_intersection(name)};
    
    return std::any_of(start->get_streets().begin(), start->get_streets().end(), [&](const Street& street) {
        return has_cycle_util(street.tail, start, visited);
    });
}

bool CityMap::has_eulerian_trail() const {
    bool headFound{false};
    bool tailFound{false};
    
    for (Intersection* intersection: intersections) {
        if (intersection->get_outdegree() - intersection->get_indegree() == 1 && !headFound) {
            headFound = true;
        }
        else if (intersection->get_indegree() - intersection->get_outdegree() == 1 && !tailFound) {
            tailFound = true;
        }
        else if (intersection->get_indegree() != intersection->get_outdegree()) {
            return false;
        }
    }
    
    return true;
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
