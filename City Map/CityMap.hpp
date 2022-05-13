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
#include <unordered_set>
#include <vector>

#include "Intersection.hpp"

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
    
    friend void swap(CityMap&, CityMap&);
    friend std::istream& operator>>(std::istream&, CityMap&);
    
 private:
    std::vector<Intersection*> intersections;
    
    void copy(const CityMap&);
    void swap(CityMap&);
    
    bool has_cycle_util(Intersection*, Intersection*, std::unordered_set<Intersection*>&) const;
    
    Intersection* get_intersection(const std::string&) const;
    Intersection* get_or_add_intersection(const std::string&);
    void parse_intersection(const std::string&);
};

#endif /* CityMap_hpp */
