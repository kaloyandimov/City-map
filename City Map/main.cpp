//
//  main.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 21.12.20.
//

#include <cstring>
#include <string>

#include "Controller.hpp"

int main(int argc, const char* argv[]) {
    if (argc == 4 && std::strcmp(argv[1], "-i") == 0) {
        std::string path{argv[2]};
        std::string position{argv[3]};
        
        Controller ctrl{path, position};
        ctrl.run();
    }
    
    return 0;
}
