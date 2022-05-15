//
//  Command.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 14.05.22.
//

#ifndef Command_hpp
#define Command_hpp

#include <functional>
#include <string>
#include <vector>

#include "InvalidArgumentsCountException.hpp"

class Controller;

using Function = std::function<void(Controller&, std::vector<std::string>)>;

class Command {
 public:
    Command(const std::string&, const std::string&, unsigned, const Function&);
   
    const std::string& get_name() const;
    const std::string& get_usage() const;
    unsigned get_arguments_count() const;
    
    void execute(Controller&, const std::vector<std::string>&) const;
    void operator()(Controller&, const std::vector<std::string>&) const;
    
 private:
    std::string name;
    std::string usage;
    unsigned arguments_count;
    Function function;
};

#endif /* Command_hpp */
