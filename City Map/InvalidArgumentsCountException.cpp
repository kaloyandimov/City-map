//
//  InvalidArgumentsCountException.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 15.05.22.
//

#include "InvalidArgumentsCountException.hpp"

InvalidArgumentsCountException::InvalidArgumentsCountException(const std::string& what_arg):
    CustomException{what_arg} {}
