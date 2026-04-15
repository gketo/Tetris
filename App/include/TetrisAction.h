#pragma once

#include <string_view>

namespace Game::Tetris {

    enum class TetrisAction
    {
        // tetris
        ROTATE_LEFT,
        ROTATE_RIGHT
        //
    };

    // Helper function to convert TetrisAction enum to string
    inline std::string_view dbg_to_string(TetrisAction action)
    {
        switch (action)
        {
        case TetrisAction::ROTATE_LEFT: return "ROTATE_LEFT";
        case TetrisAction::ROTATE_RIGHT: return "ROTATE_RIGHT";
        }
    }
}