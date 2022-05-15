//
//  CustomException.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 15.05.22.
//

#include "CustomException.hpp"

CustomException::CustomException(const std::string& what_arg):
    std::logic_error{what_arg} {}

char const* CustomException::what() const noexcept {
    return std::logic_error::what();
}
