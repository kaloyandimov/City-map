//
//  Street.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 12.05.22.
//

#ifndef Street_hpp
#define Street_hpp

class Intersection;

struct Street {
    Intersection* head;
    unsigned distance;
    Intersection* tail;
};

#endif /* Street_hpp */
