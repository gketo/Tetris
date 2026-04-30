#pragma once

#include <string>
#include <vector>

namespace Game {

    struct Rules
    {
        std::string welcomeMsg;
        std::vector<std::string> rules;
        std::string commandsMsg;
    };
    
}