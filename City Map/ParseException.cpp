//
//  ParseException.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 17.05.22.
//

#include "ParseException.hpp"

ParseException::ParseException(const std::string& what_arg):
    CustomException{what_arg} {}
