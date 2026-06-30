#pragma once

// ==================== Includes ====================
#include <string_view>

namespace App::Game {

    enum class GameType
    {
		None,
        TETRIS,
		TEST, // debug dbg
		Count
    };

    // Helper function to convert GameType to string
	inline std::string_view dbg_to_string(GameType game)
	{
		switch (game)
		{
		case GameType::None:    return "None";
		case GameType::TETRIS:  return "TETRIS";
		case GameType::TEST:    return "TEST"; // debug dbg
		case GameType::Count:   return "Count"; // debug dbg
		}
        return "Unknown";
	}
}