#pragma once

#include <unordered_set>

namespace Core::Graphics::Utils {
    
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
        BRIGHT_WHITE,
        Fg_Default,
        Bg_Default,
        Invalid
    };
   
    enum class Attr
    {
        // for text based rendering
        BOLD,
        ITALICS,
        UNDERLINED,
        //
        Default
    }; 

    struct Style
    {
        Color fg;
        Color bg;
        std::unordered_set<Attr> attrs{ Attr::Default };
    };
}
