//
//  CommandParser.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 14.05.22.
//

#ifndef CommandParser_hpp
#define CommandParser_hpp

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class CommandParser {
 public:
    CommandParser() = default;
    explicit CommandParser(const std::string&);
    
    const std::string& parsed_name() const;
    const std::vector<std::string>& parsed_arguments() const;
    
    void parse(const std::string&);
    
 private:
    std::string name;
    std::vector<std::string> arguments;
};

#endif /* CommandParser_hpp */
