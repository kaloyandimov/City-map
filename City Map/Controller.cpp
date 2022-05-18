//
//  Controller.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 13.05.22.
//

#include "Controller.hpp"

std::unordered_map<std::string, Command> Controller::commands;
std::vector<std::string> Controller::insertion_order;

bool Controller::init{Controller::init_commands()};

Controller::Controller(const std::string& path, const std::string& name, std::istream& _in, std::ostream& _out, std::ostream& _err): in{_in}, out{_out}, err{_err} {
    std::ifstream in{path};
    
    try {
        in >> map;
        parsed_successfully = true;
    } catch (const ParseException& e) {
        err << e.what() << "\n";
        parsed_successfully = false;
    }
    
    position = map.get_intersection(name);
}

void Controller::run() {
    if (!parsed_successfully) {
        return;
    }
    
    CommandParser parser;
    std::string input;
    
    running = true;
    
    while (running) {
        out << "> ";
        
        std::getline(in, input);
        parser.parse(input);
        
        if (!commands.contains(parser.parsed_name())) {
            err << "Invalid command\n"; continue;
        }
        
        try {
            commands.at(parser.parsed_name())(*this, parser.parsed_arguments());
        } catch (const CustomException& e) {
            err << e.what() << "\n";
        }
    }
}

void Controller::stop() { 
    running = false;
}

void Controller::register_command(const std::string& name, const std::string& usage, unsigned arguments_count, const Function& function) {
    commands.emplace(name, Command{name, usage, arguments_count, function});
    insertion_order.push_back(name);
}

bool Controller::init_commands() {
    register_command(
        "location",
        "print current position",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            ctrl.out << ctrl.position->get_name() << "\n";
        }
    );
    
    register_command(
        "neighbours",
        "print all adjacent intersections",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            for (const Street& street : ctrl.position->get_streets()) {
                ctrl.out << street.tail->get_name() << "\n";
            }
        }
    );
    
    register_command(
        "change",
        "change current position",
        1,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            Intersection* intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection\n"; return;
            }
            
            if (ctrl.closed_intersections.contains(args[0])) {
                ctrl.err << "Closed intersection\n"; return;
            }
            
            ctrl.position = intersection;
        }
    );
    
    register_command(
        "move",
        "change current position and print the path",
        1,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection\n"; return;
            }
            
            auto path{ctrl.map.get_shortest_path(ctrl.position->get_name(), args[0], ctrl.closed_intersections)};
            
            if (path.empty()) {
                ctrl.out << "No such path\n"; return;
            }
            
            for (const std::string& name : path) {
                ctrl.out << name << "\n";
            }
            
            ctrl.position = intersection;
        }
    );
    
    register_command(
        "close",
        "add intersection to the list of closed intersections",
        1,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection\n"; return;
            }
            
            if (intersection == ctrl.position) {
                ctrl.err << "Cannot close current intersection\n"; return;
            }
            
            ctrl.closed_intersections.insert(args[0]);
        }
    );
    
    register_command(
        "open",
        "remove intersection from the list of closed intersections",
        1,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto found{ctrl.map.get_intersection(args[0]) != nullptr};
            
            if (!found) {
                ctrl.err << "No such intersection\n"; return;
            }
            
            ctrl.closed_intersections.erase(args[0]);
        }
    );
    
    register_command(
        "closed",
        "print all closed intersections",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            for (const std::string& name : ctrl.closed_intersections) {
                ctrl.out << name << "\n";
            }
        }
    );
    
    register_command(
        "tour",
        "print a city tour",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            std::vector<std::string> tour{ctrl.map.get_eulerian_trail()};
            
            if (tour.empty()) {
                ctrl.err << "No such tour\n"; return;
            }
            
            for (const std::string& name : tour) {
                ctrl.out << name << "\n";
            }
        }
    );
    
    register_command(
        "help",
        "print this list",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            for (const std::string& name : ctrl.insertion_order) {
                ctrl.out << std::setw(14) << std::left << name;
                ctrl.out << ctrl.commands.at(name).get_usage() << "\n";
            }
        }
    );
    
    register_command(
        "exit",
        "exit the program",
        0,
        [](Controller& ctrl, const std::vector<std::string>& args) {
            ctrl.stop();
        }
    );
    
    return true;
}
