#pragma once

// ==================== Includes ====================
#include "Core/Graphics/GfxUtils.h"
#include "Core/Graphics/Style.h"

#include "Core/Terminal/TerminalChar.h"

// ==================== Includes ====================
#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace Core::Terminal::Termios::Utils {
    
    namespace GfxUtils = Core::Graphics::Utils;
    
    constexpr const std::string_view ALTERNATE_SCREEN_ENTER = "\x1b[?1049h";
    constexpr const std::string_view ALTERNATE_SCREEN_EXIT = "\x1b[?1049l";
    constexpr const std::string_view CLEAR_SCREEN = "\x1b[2J";
    constexpr const std::string_view CLEAR_SCROLLBACK = "\x1b[3J";
    constexpr const std::string_view CURSOR_HOME  = "\x1b[H";
    constexpr const std::string_view ERASE_LINE_TORIGHT = "\x1b[K";
    constexpr const std::string_view ERASE_SCREEN_TOBOTTOM = "\x1b[0J";
    constexpr const std::string_view HIDE_CURSOR  = "\x1b[?25l";
    constexpr const std::string_view SHOW_CURSOR  = "\x1b[?25h";
    constexpr const std::string_view RESET_COLORS = "\x1b[39m\x1b[49m";
    constexpr const std::string_view RESET_ATTRS = "\x1b[22m\x1b[23m\x1b[24m";
            


    inline void appendClearScreen(std::string& out)
    {
        out += CLEAR_SCREEN.data(); // clear screen
        out += CURSOR_HOME.data();  // move cursor to home
    }

    inline void appendHideCursor(std::string& out)
    {  
        out += HIDE_CURSOR.data();    
    }

    inline void appendShowCursor(std::string& out) 
    {
        out += SHOW_CURSOR.data();  
    }

    inline void appendMoveCursor(std::string& out, size_t r, size_t c)
    {
        // LOG_DEBUG("[TermiosCore] Move cursor to ( %d, %d )", row, col);
        out.reserve(out.size() + 16);

        out += "\x1b[";
        out += std::to_string(r + 1);
        out += ";";
        out += std::to_string(c + 1);
        out += "H";
    }

    inline void appendMoveCursorTerminalSafe(std::string& out, const Core::Terminal::TerminalConfig& termConfig, size_t r, size_t c)
    {
        // LOG_DEBUG("[TermiosCore] Move cursor to ( %d, %d )", row, col);
        if (!termConfig.size.width || !termConfig.size.height)
        {
            return; // todo
        }

        r = std::clamp(r, size_t{0}, termConfig.size.height - 1);
        c = std::clamp(c, size_t{0}, termConfig.size.width  - 1);

        appendMoveCursor(out, r, c);
    }

    inline std::string_view Termios_FgColorToAnsi(GfxUtils::Color c)
    {
        switch (c) 
        {
        case GfxUtils::Color::BLACK:            return "\x1b[30m";
        case GfxUtils::Color::RED:              return "\x1b[31m";
        case GfxUtils::Color::GREEN:            return "\x1b[32m";
        case GfxUtils::Color::ORANGE:
        case GfxUtils::Color::YELLOW:           return "\x1b[33m";
        case GfxUtils::Color::BLUE:             return "\x1b[34m";
        case GfxUtils::Color::MAGENTA:          return "\x1b[35m";
        case GfxUtils::Color::CYAN:             return "\x1b[36m";
        case GfxUtils::Color::WHITE:            return "\x1b[37m";
        case GfxUtils::Color::BRIGHT_BLACK:     return "\x1b[90m";
        case GfxUtils::Color::BRIGHT_RED:       return "\x1b[91m";
        case GfxUtils::Color::BRIGHT_GREEN:     return "\x1b[92m";
        case GfxUtils::Color::BRIGHT_ORANGE:
        case GfxUtils::Color::BRIGHT_YELLOW:    return "\x1b[93m";
        case GfxUtils::Color::BRIGHT_BLUE:      return "\x1b[94m";
        case GfxUtils::Color::BRIGHT_MAGENTA:   return "\x1b[95m";
        case GfxUtils::Color::BRIGHT_CYAN:      return "\x1b[96m";
        case GfxUtils::Color::BRIGHT_WHITE:     return "\x1b[97m";
        case GfxUtils::Color::Fg_Default:       return "\x1b[39m"; // back to default

        case GfxUtils::Color::Bg_Default:       break;
        case GfxUtils::Color::Invalid:          break;
        }

        return "\x1b[39m"; // default
    }

    inline std::string_view Termios_BgColorToAnsi(GfxUtils::Color c)
    {
        switch (c) 
        {
        case GfxUtils::Color::BLACK:            return "\x1b[40m";
        case GfxUtils::Color::RED:              return "\x1b[41m";
        case GfxUtils::Color::GREEN:            return "\x1b[42m";
        case GfxUtils::Color::ORANGE:
        case GfxUtils::Color::YELLOW:           return "\x1b[43m";
        case GfxUtils::Color::BLUE:             return "\x1b[44m";
        case GfxUtils::Color::MAGENTA:          return "\x1b[45m";
        case GfxUtils::Color::CYAN:             return "\x1b[46m";
        case GfxUtils::Color::WHITE:            return "\x1b[47m";
        case GfxUtils::Color::BRIGHT_BLACK:     return "\x1b[100m";
        case GfxUtils::Color::BRIGHT_RED:       return "\x1b[101m";
        case GfxUtils::Color::BRIGHT_GREEN:     return "\x1b[102m";
        case GfxUtils::Color::BRIGHT_ORANGE:
        case GfxUtils::Color::BRIGHT_YELLOW:    return "\x1b[103m";
        case GfxUtils::Color::BRIGHT_BLUE:      return "\x1b[104m";
        case GfxUtils::Color::BRIGHT_MAGENTA:   return "\x1b[105m";
        case GfxUtils::Color::BRIGHT_CYAN:      return "\x1b[106m";
        case GfxUtils::Color::BRIGHT_WHITE:     return "\x1b[107m";

        case GfxUtils::Color::Fg_Default:       break;
        case GfxUtils::Color::Bg_Default:       return "\x1b[49m"; // back to default
        case GfxUtils::Color::Invalid:          break;;
        }

        return "\x1b[49m"; // default
    }

    inline std::string_view Termios_TextAttrToAnsi(GfxUtils::Attr attr)
    {
        switch (attr) 
        {
        case GfxUtils::Attr::BOLD:        return "\x1b[1m";
        case GfxUtils::Attr::ITALICS:     return "\x1b[3m";
        case GfxUtils::Attr::UNDERLINED:  return "\x1b[4m";
        case GfxUtils::Attr::Default:     return "\x1b[22m\x1b[23m\x1b[24m"; // reset all
        }
        return "\x1b[22m\x1b[23m\x1b[24m"; // default
    }

    inline std::string Termios_GfxStyleToAnsi(const GfxUtils::Style& style)
    {
        std::string str;

        str += Termios_FgColorToAnsi(style.fg);
        str += Termios_BgColorToAnsi(style.bg);

        for (const auto& attr : style.attrs)
        {
            str += Termios_TextAttrToAnsi(attr);
        }
        
        return str;
    }

    inline std::string Termios_TerminalCharToStr(const Core::Terminal::TerminalChar& tch, GfxUtils::Style* prevStyle = nullptr)
    {
        std::string str;

        if (tch.preStyle)
        {
            if (prevStyle)
            {
                str += Termios_GfxStyleToAnsi(tch.preStyle->diff(*prevStyle));
                *prevStyle = *(tch.preStyle);
            }
            else
            {
                str += Termios_GfxStyleToAnsi(*(tch.preStyle));
                if (prevStyle)
                {
                    *prevStyle = *tch.preStyle;
                }
            }
        }

        str += tch.ch;

        if (tch.postStyle)
        {
            str += Termios_GfxStyleToAnsi(*(tch.postStyle));
            if (prevStyle)
            {
                *prevStyle = *(tch.postStyle);
            }
        }

        return str;
    }

    // when text is too long
    inline std::vector<std::string> wrap(std::string_view towrap, size_t maxsize)
    {
        if (towrap.size() <= maxsize)
        {
            return { std::string(towrap) };
        }

        std::vector<std::string> wrapped;
        auto offset{ 0 };
        auto rlen = towrap.size();
        while (rlen > 0)
        {
            auto plen = std::min(rlen, maxsize);
            wrapped.emplace_back(towrap.substr(offset, plen));

            offset += plen;
            rlen -= plen;
        }
        return wrapped;
    }

    #ifdef EXCLUDE_THIS
    void frameContent(const Core::ITerminalCore& terminal, std::string& out, const std::string& title, size_t rows, size_t cols)
    {
        constexpr const std::string BORDER_H{ '-' };
        constexpr const std::string BORDER_V{ '|' };
        constexpr const std::string CORNER_TL = "┌"; // U+250C
        constexpr const std::string CORNER_TR = "┐"; // U+2510
        constexpr const std::string CORNER_BL = "└"; // U+2514
        constexpr const std::string CORNER_BR = "┘"; // U+2518

        //
        std::string frameStr{};

        terminal.appendCursorHome(frameStr);

        size_t cursorRow = 0; // cursor position row
        size_t cursorCol = 0; // cursor position col

        // top border
        terminal.appendMoveCursor(frameStr, cursorRow, cursorCol);
        frameStr += ERASE_LINE_TORIGHT;
        frameStr += CORNER_TL;
        for (size_t c = 0; c < (cols - title.size())/2; ++c)
        {
            frameStr += BORDER_H;
        }
        frameStr += title;
        for (size_t c = cols/2 + title.size()/2; c < cols; ++c)
        {
            frameStr += BORDER_H;
        }
        frameStr += CORNER_TR;

        ++cursorRow;

        while (cursorRow <= rows)
        {
            cursorCol = 0;
            terminal.appendMoveCursor(frameStr, cursorRow, cursorCol);
            // clear line
            frameStr += ERASE_LINE_TORIGHT;
            // add border
            frameStr += BORDER_V;
            cursorCol += BORDER_V.size();
            // move to next border
            cursorCol += cols;
            terminal.appendMoveCursor(frameStr, cursorRow, cursorCol);
            // add border
            frameStr += BORDER_V;
            cursorCol += BORDER_V.size();
            // end of line
            ++cursorRow;
        }

        // bottom border
        cursorCol = 0;
        terminal.appendMoveCursor(frameStr, cursorRow, cursorCol);
        frameStr += ERASE_LINE_TORIGHT;
        frameStr += CORNER_BL;
        for (size_t c = 0; c < cols; ++c)
        {
            frameStr += BORDER_H;
        }
        frameStr += CORNER_BR;

        ++cursorRow;

        // reset
        frameStr += RESET_ATTRS;
        frameStr += RESET_COLORS;
        terminal.appendCursorHome(frameStr);

        out = frameStr;
    }
    #endif
}