#pragma once

#include <string_view>

namespace Core::Graphics::Utils {
    
    enum class Color
    {
        BLACK,
        RED,
        GREEN,
        ORANGE,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,   
        WHITE,
        BRIGHT_BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_ORANGE,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE,
        Fg_Default,
        Bg_Default,
        Invalid
    };

    // Helper function to convert Color to string
    inline std::string_view dbg_to_string(Color color)
    {
        switch (color)
        {
        case Color::BLACK:          return "BLACK";
        case Color::RED:            return "RED";
        case Color::GREEN:          return "GREEN";
        case Color::ORANGE:         return "ORANGE";
        case Color::YELLOW:         return "YELLOW";
        case Color::BLUE:           return "BLUE";
        case Color::MAGENTA:        return "MAGENTA";
        case Color::CYAN:           return "CYAN";
        case Color::WHITE:          return "WHITE";
        case Color::BRIGHT_BLACK:   return "BRIGHT_BLACK";
        case Color::BRIGHT_RED:     return "BRIGHT_RED";
        case Color::BRIGHT_GREEN:   return "BRIGHT_GREEN";
        case Color::BRIGHT_ORANGE:  return "BRIGHT_ORANGE";
        case Color::BRIGHT_YELLOW:  return "BRIGHT_YELLOW";
        case Color::BRIGHT_BLUE:    return "BRIGHT_BLUE";
        case Color::BRIGHT_MAGENTA: return "BRIGHT_MAGENTA";
        case Color::BRIGHT_CYAN:    return "BRIGHT_CYAN";
        case Color::BRIGHT_WHITE:   return "BRIGHT_WHITE";
        case Color::Fg_Default:     return "Fg_Default";
        case Color::Bg_Default:     return "Bg_Default";
        case Color::Invalid:        return "Invalid";
        }
        return "Unknown";
    }
}
