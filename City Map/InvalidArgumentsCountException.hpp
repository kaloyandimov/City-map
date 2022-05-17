//
//  InvalidArgumentsCountException.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 15.05.22.
//

#ifndef InvalidArgumentsCountException_hpp
#define InvalidArgumentsCountException_hpp

#include "CustomException.hpp"

class InvalidArgumentsCountException : public CustomException {
 public:
   InvalidArgumentsCountException(const std::string&);
};

#endif /* InvalidArgumentsCountException_hpp */
