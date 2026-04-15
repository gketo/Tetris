#pragma once

#include "GraphicsUtils.h"

#include <string_view>

namespace Core::Terminal::Termios {
    
    namespace GfxUtils = Core::Graphics::Utils;

    constexpr const std::string_view ERASE_RIGHT = "\x1b[K";
    constexpr const std::string_view CLEAR_SCREEN = "\x1b[2J";
    constexpr const std::string_view CLEAR_SCROLLBACK = "\x1b[3J";
    constexpr const std::string_view CURSOR_HOME  = "\x1b[H";
    constexpr const std::string_view HIDE_CURSOR  = "\x1b[?25l";
    constexpr const std::string_view SHOW_CURSOR  = "\x1b[?25h";
    constexpr const std::string_view RESET_COLORS = "\x1b[39m\x1b[49m";

    inline std::string_view Termios_toAnsiFgColor(GfxUtils::Color c)
    {
        switch (c) 
        {
        case GfxUtils::Color::BLACK:        return "\x1b[30m";
        case GfxUtils::Color::RED:          return "\x1b[31m";
        case GfxUtils::Color::GREEN:        return "\x1b[32m";
        case GfxUtils::Color::YELLOW:       return "\x1b[33m";
        case GfxUtils::Color::BLUE:         return "\x1b[34m";
        case GfxUtils::Color::MAGENTA:      return "\x1b[35m";
        case GfxUtils::Color::CYAN:         return "\x1b[36m";
        case GfxUtils::Color::WHITE:        return "\x1b[37m";
        case GfxUtils::Color::BRIGHT_WHITE: return "\x1b[31m";//dbg debug return "\x1b[97m";
        case GfxUtils::Color::Fg_Default:   return "\x1b[39m"; // back to default

        case GfxUtils::Color::Bg_Default:   break;
        case GfxUtils::Color::Invalid:      break;
        }

        return "\x1b[39m"; // default
    }

    inline std::string_view Termios_toAnsiBgColor(GfxUtils::Color c)
    {
        switch (c) 
        {
        case GfxUtils::Color::BLACK:        return "\x1b[40m";
        case GfxUtils::Color::RED:          return "\x1b[41m";
        case GfxUtils::Color::GREEN:        return "\x1b[42m";
        case GfxUtils::Color::YELLOW:       return "\x1b[43m";
        case GfxUtils::Color::BLUE:         return "\x1b[44m";
        case GfxUtils::Color::MAGENTA:      return "\x1b[45m";
        case GfxUtils::Color::CYAN:         return "\x1b[46m";
        case GfxUtils::Color::WHITE:        return "\x1b[47m";

        case GfxUtils::Color::BRIGHT_WHITE: break;
        case GfxUtils::Color::Fg_Default:   break;
        
        case GfxUtils::Color::Bg_Default:   return "\x1b[49m"; // back to default
        
        case GfxUtils::Color::Invalid:      break;;
        }

        return "\x1b[49m"; // default
    }

    inline std::string_view Termios_toAnsiTextAttr(GfxUtils::Attr attr)
    {
        switch (attr) 
        {
        case GfxUtils::Attr::BOLD:        return "\x1b[1m";
        case GfxUtils::Attr::ITALICS:     return "\x1b[3m";
        case GfxUtils::Attr::UNDERLINED:  return "\x1b[4m";
        case GfxUtils::Attr::Default:     return "\x1b[0m"; // reset all
        }
    }

    
}