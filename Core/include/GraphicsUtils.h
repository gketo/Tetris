#pragma once

#include <format>
#include <string>
#include <string_view>
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

    // Helper function to convert Color to string
    inline std::string_view dbg_to_string(Color color)
    {
        switch (color)
        {
        case Color::BLACK:         return "BLACK";
        case Color::RED:           return "RED";
        case Color::GREEN:         return "GREEN";
        case Color::YELLOW:        return "YELLOW";
        case Color::BLUE:          return "BLUE";
        case Color::MAGENTA:       return "MAGENTA";
        case Color::CYAN:          return "CYAN";
        case Color::WHITE:         return "WHITE";
        case Color::BRIGHT_WHITE:  return "BRIGHT_WHITE";
        case Color::Fg_Default:    return "Fg_Default";
        case Color::Bg_Default:    return "Bg_Default";
        case Color::Invalid:       return "Invalid";
        }
        return "Unknown";
    }

    // Helper function to convert Attr to string
    inline std::string_view dbg_to_string(Attr attr)
    {
        switch (attr)
        {
        case Attr::BOLD:        return "BOLD";
        case Attr::ITALICS:     return "ITALICS";
        case Attr::UNDERLINED:  return "UNDERLINED";
        case Attr::Default:     return "Default";
        }
        return "Unknown";
    }

    struct Style
    {
        Color fg;
        Color bg;
        std::unordered_set<Attr> attrs{ Attr::Default };

        std::string to_string() const
        {
            std::string attrsStr;
            for (const auto& attr : attrs)
            {
                if (!attrsStr.empty())
                    attrsStr += ", ";
                attrsStr += dbg_to_string(attr);
            }

            return std::format(
                "[Style] -> fg: {}, bg: {}, attrs: [{}]",
                dbg_to_string(fg),
                dbg_to_string(bg),
                attrsStr.empty() ? "None" : attrsStr
            );
        }
    };
}
