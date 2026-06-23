#pragma once

#include <string_view>

namespace App::Game::Tetris {

    enum class TetrominoType
    {
        I,
        J,
        L,
        O,
        S,
        T,
        Z,
    };

    constexpr TetrominoType allTetrominoTypes[] = {
        TetrominoType::I,
        TetrominoType::J,
        TetrominoType::L,
        TetrominoType::O,
        TetrominoType::S,
        TetrominoType::T,
        TetrominoType::Z
    };

    // Helper function to convert TetrominoType to string
	inline std::string_view dbg_to_string(TetrominoType tetro)
	{
		switch (tetro)
		{
		case TetrominoType::I:      return "I";
		case TetrominoType::J:      return "J";
		case TetrominoType::L:      return "L";
		case TetrominoType::O:      return "O";
		case TetrominoType::S:      return "S";
		case TetrominoType::T:      return "T";
		case TetrominoType::Z:      return "Z";
        }
        return "Unknown";
	}
}