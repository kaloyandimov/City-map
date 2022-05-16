//
//  Controller.hpp
//  City Map
//
//  Created by Kaloyan Dimov on 13.05.22.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "CityMap.hpp"
#include "Command.hpp"
#include "CommandParser.hpp"
#include "CustomException.hpp"
#include "Intersection.hpp"
#include "Street.hpp"

class Controller {
 public:
    Controller(const std::string&, const std::string&, std::istream& = std::cin, std::ostream& = std::cout, std::ostream& = std::cerr);
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(Controller&&) = delete;
    ~Controller() = default;
    
    void run();
    void stop();
    
 private:
    CityMap map;
    Intersection* position;
    std::unordered_set<std::string> closed_intersections;
    bool running;
    
    std::istream& in;
    std::ostream& out;
    std::ostream& err;
    
    static std::unordered_map<std::string, Command> commands;
    static std::vector<std::string> insertion_order;
    static bool init;
    
    static void register_command(const std::string&, const std::string&, unsigned, const Function&);
    static bool init_commands();
};

#endif /* Controller_hpp */
