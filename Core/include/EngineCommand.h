#pragma once

#include <string_view>

namespace Core {

    enum class EngineCommand
    {
        // General
		PLAY,
		PAUSE,
        RESUME,
        DISP_RULES,
		QUIT,
        // Rules
        // ACCEPT_RULES,
        //
    };

    // Helper function to convert EngineCommand enum to string
    inline std::string_view dbg_to_string(EngineCommand action)
    {
        switch (action)
        {
        case EngineCommand::PLAY: return "PLAY";
        case EngineCommand::PAUSE: return "PAUSE";
        case EngineCommand::RESUME: return "RESUME";
        case EngineCommand::DISP_RULES: return "DISP_RULES";
        case EngineCommand::QUIT: return "QUIT";
        // case EngineCommand::ACCEPT_RULES: return "ACCEPT_RULES";
        }
    }

}