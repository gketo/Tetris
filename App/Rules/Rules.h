#pragma once

// ==================== Includes ====================
#include <string>
#include <vector>

namespace App::Rules {

    struct Rules
    {
        std::string welcomeMsg;
        std::vector<std::string> rules;
        std::string commandsMsg;
    };
    
}