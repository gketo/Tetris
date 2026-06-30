#pragma once

// ==================== Includes ====================
#include <string_view>

namespace Core {

    enum class EngineCommand
    {
        // General
		PLAY,
		PAUSE,
        RESUME,
		QUIT,
        //
    };

    // Helper function to convert EngineCommand to string
    inline std::string_view dbg_to_string(EngineCommand cmd)
    {
        switch (cmd)
        {
        case EngineCommand::PLAY:   return "PLAY";
        case EngineCommand::PAUSE:  return "PAUSE";
        case EngineCommand::RESUME: return "RESUME";
        case EngineCommand::QUIT:   return "QUIT";
        }
        return "Unknown";
    }

}