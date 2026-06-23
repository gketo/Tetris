#pragma once

#include <string_view>

namespace App::Game::Tetris {

    enum class TetrisCommand
    {
        // tetris
        TRANSLATE_LEFT,
        TRANSLATE_RIGHT,
        SOFT_DROP,
        ROTATE_CLOCKWISE,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        HARD_DROP,
        HOLD
        //
    };

    // Helper function to convert TetrisCommand to string
    inline std::string_view dbg_to_string(TetrisCommand action)
    {
        switch (action)
        {
        case TetrisCommand::TRANSLATE_LEFT:     return "TRANSLATE_LEFT";
        case TetrisCommand::TRANSLATE_RIGHT:    return "TRANSLATE_RIGHT";
        case TetrisCommand::SOFT_DROP:          return "SOFT_DROP";
        case TetrisCommand::ROTATE_CLOCKWISE:   return "ROTATE_CLOCKWISE";
        case TetrisCommand::ROTATE_LEFT:        return "ROTATE_LEFT";
        case TetrisCommand::ROTATE_RIGHT:       return "ROTATE_RIGHT";
        case TetrisCommand::HARD_DROP:          return "HARD_DROP";
        case TetrisCommand::HOLD:               return "HOLD";
        }
        return "Unknown";
    }
}

// Left / Right arrows → Move piece left/right
// Down arrow → Soft drop (move down faster)
// Up arrow → Rotate piece (sometimes clockwise)
// Z / X → Rotate (counterclockwise / clockwise in many versions)
// Spacebar → Hard drop (instantly place piece)
// C or Shift → Hold piece (store for later)
