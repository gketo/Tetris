#pragma once

#include "TextAttributs.h"

#include <string_view>

namespace Core {

    inline std::string_view Termios_toAnsiFg(Color c)
    {
        switch (c) 
        {
        case Color::BLACK:      return "\033[30m";
        case Color::RED:        return "\033[31m";
        case Color::GREEN:      return "\033[32m";
        case Color::YELLOW:     return "\033[33m";
        case Color::BLUE:       return "\033[34m";
        case Color::MAGENTA:    return "\033[35m";
        case Color::CYAN:       return "\033[36m";
        case Color::WHITE:      return "\033[37m";
        case Color::Fg_Default: return "\033[39m"; // back to default
        default:                return "";
        }
    }

    inline std::string_view Termios_toAnsiBg(Color c)
    {
        switch (c) 
        {
        case Color::BLACK:      return "\033[40m";
        case Color::RED:        return "\033[41m";
        case Color::GREEN:      return "\033[42m";
        case Color::YELLOW:     return "\033[43m";
        case Color::BLUE:       return "\033[44m";
        case Color::MAGENTA:    return "\033[45m";
        case Color::CYAN:       return "\033[46m";
        case Color::WHITE:      return "\033[47m";
        case Color::Bg_Default: return "\033[49m"; // back to default
        default:                return "";
        }
    }

    inline std::string_view Termios_toAnsiAttr(Attr attr)
    {
        switch (attr) 
        {
        case Attr::BOLD:        return "\033[1m";
        case Attr::ITALICS:     return "\033[3m";
        case Attr::UNDERLINED:  return "\033[4m";
        case Attr::Default:     return "\033[0m"; // reset all
        default:                return "";
        }
    }
}