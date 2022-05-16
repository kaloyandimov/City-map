//
//  CityMap.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#ifndef CityMap_hpp
#define CityMap_hpp

#include <algorithm>
#include <istream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Intersection.hpp"
#include "Street.hpp"

class Controller;

class CityMap {
 public:
    CityMap() = default;
    CityMap(const CityMap&);
    CityMap& operator=(const CityMap&);
    CityMap(CityMap&&) = default;
    CityMap& operator=(CityMap&&) = default;
    ~CityMap();
    
    bool reaches_all(const std::string&) const;
    bool has_path(const std::string&, const std::string&) const;
    bool has_cycle(const std::string&) const;
    bool has_eulerian_trail() const;
    
    std::vector<std::string> get_eulerian_trail() const;
    std::vector<std::pair<std::string, std::string>> get_deadends() const;
    std::vector<std::string> get_shortest_path(const std::string&, const std::string&, const std::unordered_set<std::string>& = {}) const;
    std::vector<std::vector<std::string>> get_three_shortest_paths(const std::string&, const std::string&, const std::unordered_set<std::string>& = {}) const;
    std::vector<std::vector<std::string>> get_k_shortest_paths(const std::string&, const std::string&, unsigned k, const std::unordered_set<std::string>& = {}) const;
    
    friend void swap(CityMap&, CityMap&);
    friend std::istream& operator>>(std::istream&, CityMap&);
    friend class Controller;
    
 private:
    std::vector<Intersection*> intersections;
    
    void copy(const CityMap&);
    void swap(CityMap&);
    
    bool has_cycle_util(Intersection*, Intersection*, std::unordered_set<Intersection*>&) const;
    
    Intersection* find_eulerian_trail_start() const;
    
    Intersection* get_intersection(const std::string&) const;
    Intersection* get_or_add_intersection(const std::string&);
    void parse_intersection(const std::string&);
};

#endif /* CityMap_hpp */
