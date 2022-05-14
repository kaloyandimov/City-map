//
//  Command.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 14.05.22.
//

#include "Command.hpp"

Command::Command(const std::string& _name, const std::string& _usage, const Function& _function):
    name{_name}, usage{_usage}, function{_function} {}

const std::string &Command::get_name() const { 
    return name;
}

const std::string &Command::get_usage() const { 
    return usage;
}

void Command::execute(Controller& ctrl, const std::vector<std::string>& args) const {
    function(ctrl, args);
}

void Command::operator()(Controller& ctrl, const std::vector<std::string>& args) const {
    execute(ctrl, args);
}
