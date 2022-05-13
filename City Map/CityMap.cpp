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
    
    for (Intersection* intersection: intersections) {
        streets[intersection] = intersection->get_streets();
    }
    
    auto curr{find_eulerian_trail_start()};
    current_path.push(curr);
    
    while (!current_path.empty()) {
        if (!streets[curr].empty()) {
            Intersection* next{streets[curr].back().tail};
            streets[curr].pop_back();
            current_path.push(curr);
            curr = next;
        }
        else {
            trail.push_back(curr->get_name());
            curr = current_path.top();
            current_path.pop();
        }
    }
    
    std::reverse(trail.begin(), trail.end());
    
    return trail;
}

std::vector<std::pair<std::string, std::string>> CityMap::get_deadends() const {
    std::vector<std::pair<std::string, std::string>> deadends;
    
    for (Intersection* head: intersections) {
        for (const Street& street: head->get_streets()) {
            if (street.tail->get_outdegree() == 0) {
                deadends.emplace_back(head->get_name(), street.tail->get_name());
            }
        }
    }
    
    return deadends;
}

std::vector<std::vector<std::string>> CityMap::get_three_shortest_paths(const std::string& head, const std::string& tail, const std::vector<std::string>& closed) const {
    return get_k_shortest_paths(head, tail, 3, closed);
}

std::vector<std::vector<std::string>> CityMap::get_k_shortest_paths(const std::string& head, const std::string& tail, unsigned k, const std::vector<std::string>& closed) const {
    using Pair = std::pair<unsigned, std::vector<std::string>>;
    
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> potenial_paths;
    std::unordered_map<std::string, unsigned> path_counts;
    std::vector<std::vector<std::string>> paths;
    
    potenial_paths.emplace(0, std::vector{head});
    
    while (!potenial_paths.empty() && path_counts[tail] < k) {
        std::vector<std::string> curr_path{potenial_paths.top().second};
        unsigned curr_length{potenial_paths.top().first};
        std::string last{curr_path.back()};
        potenial_paths.pop();
        
        if (std::find(closed.begin(), closed.end(), last) != closed.end()) {
            continue;
        }
        
        path_counts[last]++;
        
        if (last == tail) {
            paths.push_back(curr_path);
        }
        else if (path_counts[last] <= k) {
            for (const Street& street: get_intersection(last)->get_streets()) {
                std::vector<std::string> new_path{curr_path};
                new_path.push_back(street.tail->get_name());
                potenial_paths.emplace(curr_length + street.distance, new_path);
            }
        }
    }
    
    return paths;
}

std::vector<std::string> CityMap::get_shortest_path(const std::string& beginName, const std::string& endName) const {
    using Pair = std::pair<unsigned, Intersection*>;
    
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> queue;
    std::unordered_map<Intersection*, unsigned> distances;
    std::unordered_map<Intersection*, Intersection*> parents;
    Intersection* begin{get_intersection(beginName)};
    Intersection* end{get_intersection(endName)};
    
    for (Intersection* intersection: intersections) {
        distances[intersection] = UINT_MAX;
        parents[intersection] = nullptr;
    }
    
    distances[begin] = 0;
    queue.emplace(0, begin);
    
    while (!queue.empty()) {
        Intersection* curr{queue.top().second};
        queue.pop();
        
        for (const Street& street : curr->get_streets()) {
            unsigned dist{distances[curr] + street.distance};
            
            if (dist < distances[street.tail]) {
                distances[street.tail] = dist;
                parents[street.tail] = curr;
                queue.emplace(dist, street.tail);
            }
        }
    }
    
    if (begin != end && parents[end] == nullptr) {
        return std::vector<std::string>{};
    }
    
    std::vector<std::string> shortest_path;
    
    for (auto current{end}; current != nullptr; current = parents[current]) {
        shortest_path.push_back(current->get_name());
    }
    
    std::reverse(shortest_path.begin(), shortest_path.end());
    
    return shortest_path;
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
