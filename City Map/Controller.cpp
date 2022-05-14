//
//  Controller.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 13.05.22.
//

#include "Controller.hpp"

std::unordered_map<std::string, Command> Controller::commands;

bool Controller::init{Controller::init_commands()};

Controller::Controller(const std::string& path, const std::string& starting_position, std::istream& _in, std::ostream& _out, std::ostream& _err): in{_in}, out{_out}, err{_err} {
    std::ifstream in{path};
    
    in >> map;
    
    position = map.get_intersection(starting_position);
}

void Controller::run() { 
    CommandParser parser;
    std::string input;
    
    running = true;
    
    while (running) {
        out << "> ";
        
        std::getline(in, input);
        parser.parse(input);
        
        if (commands.contains(parser.parsed_name())) {
            commands.at(parser.parsed_name())(*this, parser.parsed_arguments());
        }
        else {
            err << "Invalid command" << std::endl;
        }
    }
}

void Controller::stop() { 
    running = false;
}

void Controller::register_command(const std::string& name, const std::string& usage, const Function& function) {
    commands.emplace(name, Command{name, usage, function});
}

bool Controller::init_commands() {
    register_command(
        "location",
        "print current position",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            ctrl.out << ctrl.position->get_name() << std::endl;
        }
    );
    
    register_command(
        "neighbours",
        "print all adjacent intersections",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            for (const Street& street: ctrl.position->get_streets()) {
                ctrl.out << street.tail->get_name() << "\n";
            }
                         
            ctrl.out.flush();
        }
    );
    
    register_command(
        "change",
        "change current position",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            Intersection* intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection" << std::endl; return;
            }
            
            auto pos{std::find(ctrl.closed_intersections.begin(), ctrl.closed_intersections.end(), args[0])};
            
            if (pos != ctrl.closed_intersections.end()) {
                ctrl.err << "Closed intersection" << std::endl; return;
            }
            
            ctrl.position = intersection;
        }
    );
    
    register_command(
        "move",
        "change current position and print the path",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection" << std::endl; return;
            }
            
            auto path{ctrl.map.get_shortest_path(ctrl.position->get_name(), args[0], ctrl.closed_intersections)};
            
            if (path.empty()) {
                ctrl.out << "No such path" << std::endl; return;
            }
            
            for (const std::string& name: path) {
                ctrl.out << name << "\n";
            }
            
            ctrl.out.flush();
            
            ctrl.position = intersection;
        }
    );
    
    register_command(
        "close",
        "add intersection to the list of closed intersections",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto intersection{ctrl.map.get_intersection(args[0])};
            
            if (intersection == nullptr) {
                ctrl.err << "No such intersection" << std::endl; return;
            }
            
            if (intersection == ctrl.position) {
                ctrl.err << "Cannot close current intersection" << std::endl; return;
            }
            
            ctrl.closed_intersections.push_back(args[0]);
        }
    );
    
    register_command(
        "open",
        "remove intersection from the list of closed intersections",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            auto found{ctrl.map.get_intersection(args[0]) != nullptr};
            
            if (!found) {
                ctrl.err << "No such intersection" << std::endl; return;
                
            }
            
            auto pos{std::find_if(ctrl.closed_intersections.begin(), ctrl.closed_intersections.end(), [&args](const std::string& name) {
                return name == args[0];
            })};
            
            if (pos != ctrl.closed_intersections.end()) {
                ctrl.closed_intersections.erase(pos);
            }
        }
    );
    
    register_command(
        "closed",
        "print all closed intersections",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            for (const std::string& name: ctrl.closed_intersections) {
                ctrl.out << name << "\n";
            }
            
            ctrl.out.flush();
        }
    );
    
    register_command(
        "tour",
        "print a city tour",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            std::vector<std::string> tour{ctrl.map.get_eulerian_trail()};
            
            if (tour.empty()) {
                ctrl.err << "No such tour" << std::endl; return;
            }
            
            for (const std::string& name: tour) {
                ctrl.out << name << "\n";
            }
            
            ctrl.out.flush();
        }
    );
    
    register_command(
        "exit",
        "exit the program",
        [](Controller& ctrl, const std::vector<std::string>& args) {
            ctrl.stop();
        }
    );
    
    return true;
}
