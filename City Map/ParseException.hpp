//
//  ParseException.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 17.05.22.
//

#ifndef ParseException_hpp
#define ParseException_hpp

#include "CustomException.hpp"

class ParseException : public CustomException {
 public:
    ParseException(const std::string&);
};

#endif /* ParseException_hpp */
