#pragma once

#include <string_view>

namespace Core {

    enum class EngineAction
    {
        // General
		PLAY,
		PAUSE,
        RESUME,
		QUIT
        //
    };

    // Helper function to convert EngineAction enum to string
    inline std::string_view dbg_to_string(EngineAction action)
    {
        switch (action)
        {
        case EngineAction::PLAY: return "PLAY";
        case EngineAction::PAUSE: return "PAUSE";
        case EngineAction::RESUME: return "RESUME";
        case EngineAction::QUIT: return "QUIT";
        default: return "Unknown EngineAction";
        }
    }

}