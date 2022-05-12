//
//  CityMap.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 11.01.21.
//

#ifndef CityMap_hpp
#define CityMap_hpp

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
    
 private:
    std::vector<Intersection*> intersections;
    
    void copy(const CityMap&);
    void swap(CityMap&);
    
    Intersection* get_intersection(const std::string&) const;
};

#endif /* CityMap_hpp */
