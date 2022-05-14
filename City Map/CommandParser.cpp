//
//  CommandParser.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 14.05.22.
//

#include "CommandParser.hpp"

CommandParser::CommandParser(const std::string& input) {
    parse(input);
}

const std::string& CommandParser::parsed_name() const {
    return name;
}

const std::vector<std::string>& CommandParser::parsed_arguments() const {
    return arguments;
}

void CommandParser::parse(const std::string& input) {
    std::istringstream ss{input};
    arguments.clear();
    
    ss >> name;
    
    std::copy(
        std::istream_iterator<std::string>{ss},
        std::istream_iterator<std::string>{},
        std::back_inserter(arguments)
    );
}
