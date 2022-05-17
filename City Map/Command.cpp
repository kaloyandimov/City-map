//
//  Command.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 14.05.22.
//

#include "Command.hpp"

Command::Command(const std::string& _name, const std::string& _usage, unsigned _arguments_count, const Function& _function):
    name{_name}, usage{_usage}, arguments_count{_arguments_count}, function{_function} {}

const std::string& Command::get_name() const {
    return name;
}

const std::string& Command::get_usage() const { 
    return usage;
}

unsigned Command::get_arguments_count() const {
    return arguments_count;
}

void Command::execute(Controller& ctrl, const std::vector<std::string>& args) const {
    if (arguments_count < args.size()) {
        throw InvalidArgumentsCountException{"Too few arguments"};
    }
    
    if (arguments_count > args.size()) {
        throw InvalidArgumentsCountException{"Too many arguments"};
    }
    
    function(ctrl, args);
}

void Command::operator()(Controller& ctrl, const std::vector<std::string>& args) const {
    execute(ctrl, args);
}
