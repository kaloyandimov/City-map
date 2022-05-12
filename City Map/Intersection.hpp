//
//  Intersection.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 12.05.22.
//

#ifndef Intersection_hpp
#define Intersection_hpp

#include <string>
#include <vector>

#include "Street.hpp"

class Intersection {
 public:
    explicit Intersection(const std::string&);
    
    const std::string& get_name() const;
    const std::vector<Street>& get_streets() const;
    unsigned get_indegree() const;
    unsigned get_outdegree() const;
    
    void add_street(const Street&);
    void add_street(Intersection*, unsigned, Intersection*);
    
 private:
    std::vector<Street> streets;
    std::string name;
    unsigned indegree{0};
    unsigned outdegree{0};
};

#endif /* Intersection_hpp */
