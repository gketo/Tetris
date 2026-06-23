#pragma once

#include <string_view>

namespace Core::Graphics::Utils {
   
    enum class Attr
    {
        // for text based rendering
        BOLD,
        ITALICS,
        UNDERLINED,
        //
        Default
    }; 

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
}
