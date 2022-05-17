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
    Intersection* intersection{get_intersection(name)};
    
    if (intersection == nullptr) {
        intersection = new Intersection(name);
        intersections.push_back(intersection);
    }
    
    return intersection;
}

void CityMap::copy(const CityMap& other) {
    intersections.reserve(other.intersections.size());
    
    for (Intersection* intersection : other.intersections) {
        Intersection* head{get_or_add_intersection(intersection->get_name())};
        
        for (const Street& street : intersection->get_streets()) {
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
    for (Intersection* intersection : intersections) {
        delete intersection;
    }
}

bool CityMap::reaches_all(const std::string& name) const {
    Intersection* start{get_intersection(name)};
    std::unordered_set<Intersection*> visited;
    std::queue<Intersection*> to_be_visited;
    
    to_be_visited.push(start);
    visited.insert(start);
    
    while (!to_be_visited.empty()) {
        Intersection* current{to_be_visited.front()};
        to_be_visited.pop();
        
        for (const Street& street : current->get_streets()) {
            if (!visited.contains(street.tail)) {
                to_be_visited.push(street.tail);
                visited.insert(street.tail);
            }
        }
    }
    
    return visited.size() == intersections.size();
}

bool CityMap::has_path(const std::string& start_name, const std::string& end_name) const {
    Intersection* start{get_intersection(start_name)};
    Intersection* end{get_intersection(end_name)};
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

bool CityMap::has_cycle_util(Intersection* current, Intersection* end, std::unordered_set<Intersection*>& visited) const {
    if (current == end) {
        return true;
    }
    
    if (visited.contains(current)) {
        return false;
    }
    
    visited.insert(current);
    
    return std::any_of(current->get_streets().begin(), current->get_streets().end(), [&](const Street& street) {
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
    bool head_found{false};
    bool tail_found{false};
    
    for (Intersection* intersection : intersections) {
        if (intersection->get_outdegree() - intersection->get_indegree() == 1 && !head_found) {
            head_found = true;
        } else if (intersection->get_indegree() - intersection->get_outdegree() == 1 && !tail_found) {
            tail_found = true;
        } else if (intersection->get_indegree() != intersection->get_outdegree()) {
            return false;
        }
    }
    
    return true;
}

Intersection* CityMap::find_eulerian_trail_start() const {
    auto start{std::find_if(intersections.begin(), intersections.end(), [](Intersection* intersection) {
        return intersection->get_outdegree() - intersection->get_indegree() == 1;
    })};
    
    return start != intersections.end() ? *start : intersections.front();
}

std::vector<std::string> CityMap::get_eulerian_trail() const {
    if (intersections.empty() || !has_eulerian_trail()) {
        return std::vector<std::string>{};
    }
    
    std::unordered_map<Intersection*, std::vector<Street>> streets;
    std::stack<Intersection*> current_path;
    std::vector<std::string> trail;
    
    for (Intersection* intersection : intersections) {
        streets[intersection] = intersection->get_streets();
    }
    
    auto current{find_eulerian_trail_start()};
    current_path.push(current);
    
    while (!current_path.empty()) {
        if (!streets[current].empty()) {
            Intersection* next{streets[current].back().tail};
            streets[current].pop_back();
            current_path.push(current);
            current = next;
        } else {
            trail.push_back(current->get_name());
            current = current_path.top();
            current_path.pop();
        }
    }
    
    std::reverse(trail.begin(), trail.end());
    
    return trail;
}

std::vector<std::pair<std::string, std::string>> CityMap::get_deadends() const {
    std::vector<std::pair<std::string, std::string>> deadends;
    
    for (Intersection* head : intersections) {
        for (const Street& street : head->get_streets()) {
            if (street.tail->get_outdegree() == 0) {
                deadends.emplace_back(head->get_name(), street.tail->get_name());
            }
        }
    }
    
    return deadends;
}

std::vector<std::string> CityMap::get_shortest_path(const std::string& start, const std::string& end, const std::unordered_set<std::string>& closed) const {
    auto result{get_k_shortest_paths(start, end, 1, closed)};
    
    return !result.empty() ? result.front() : std::vector<std::string>{};
}

std::vector<std::vector<std::string>> CityMap::get_three_shortest_paths(const std::string& start, const std::string& end, const std::unordered_set<std::string>& closed) const {
    return get_k_shortest_paths(start, end, 3, closed);
}

std::vector<std::vector<std::string>> CityMap::get_k_shortest_paths(const std::string& start, const std::string& end, unsigned k, const std::unordered_set<std::string>& closed) const {
    using Pair = std::pair<unsigned, std::vector<std::string>>;
    
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> potential_paths;
    std::unordered_map<std::string, unsigned> paths_counts;
    std::vector<std::vector<std::string>> paths;
    
    potential_paths.emplace(0, std::vector{start});
    
    while (!potential_paths.empty() && paths_counts[end] < k) {
        std::vector<std::string> current_path{potential_paths.top().second};
        unsigned current_length{potential_paths.top().first};
        std::string last{current_path.back()};
        potential_paths.pop();
        
        if (closed.contains(last)) {
            continue;
        }
        
        paths_counts[last]++;
        
        if (last == end) {
            paths.push_back(current_path);
        } else if (paths_counts[last] <= k) {
            for (const Street& street : get_intersection(last)->get_streets()) {
                std::vector<std::string> new_path{current_path};
                new_path.push_back(street.tail->get_name());
                potential_paths.emplace(current_length + street.distance, new_path);
            }
        }
    }
    
    return paths;
}

void CityMap::parse_intersection(const std::string& input) {
    std::istringstream ss{input};
    std::string name;
    unsigned distance;
    
    ss >> name;
    
    Intersection* head{get_or_add_intersection(name)};
    
    while (ss >> distance >> name) {
        head->add_street(head, distance, get_or_add_intersection(name));
    }
}

std::istream& operator>>(std::istream& in, CityMap& map) {
    std::string line;
    
    while (std::getline(in, line)) {
        map.parse_intersection(line);
    }
    
    return in;
}
