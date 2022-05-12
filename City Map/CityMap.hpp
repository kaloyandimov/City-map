//
//  CityMap.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#ifndef CityMap_hpp
#define CityMap_hpp

#include <istream>
#include <sstream>
#include <string>
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
    
    friend void swap(CityMap&, CityMap&);
    friend std::istream& operator>>(std::istream&, CityMap&);
    
 private:
    std::vector<Intersection*> intersections;
    
    void copy(const CityMap&);
    void swap(CityMap&);
    
    Intersection* get_intersection(const std::string&) const;
    Intersection* get_or_add_intersection(const std::string&);
    void parse_intersection(const std::string&);
};

#endif /* CityMap_hpp */
