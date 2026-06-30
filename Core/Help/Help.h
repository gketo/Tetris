#pragma once

// ==================== Includes ====================
#include <string>
#include <vector>

namespace Core::Help {
    
    struct Entry
    {
        std::string description;
        std::vector<std::string> actions;
    };

    struct HelpData
    {
    public:
        std::vector<Entry> commands;
        
        bool empty() const { return commands.empty(); }
    };

}
