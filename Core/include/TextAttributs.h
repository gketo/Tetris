#pragma once

namespace Core
{
    enum class Color
    { 
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        Fg_Default,
        Bg_Default,
        Unvalid
    };
   
    enum class Attr
    {
        BOLD,
        ITALICS,
        UNDERLINED,
        Default
    }; 
} // namespace Core::Graphics::Utils::Typo
