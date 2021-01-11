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

#include "Graph.hpp"

class CityMap {
 public:
    void add_intersection(const std::string&);
    void add_street(const std::string&, unsigned, const std::string&);
    
    bool has_road(const std::string&, const std::string&) const;
    bool reaches_all(const std::string&) const;
    bool makes_circuit(const std::string&) const;
    
    friend std::istream& operator>>(std::istream&, CityMap&);
    
 private:
    Graph<std::string> intersections;
    
    void parse_intersection(const std::string&);
};

#endif /* CityMap_hpp */
