#pragma once

#include "ITerminalCore.h"
#include "MenuData.h"
#include "TermiosUtils.h"
#include "GraphicsUtils.h"

#include <cstddef>
#include <string>
#include <string_view>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios;

    struct TermiosMenuRenderHelper
    {
    public:
        // returns menu as terminal printable string
        static std::string to_string(const Core::ITerminalCore& terminal, const MenuData& menuData);

    private:
        static void appendColored(std::string& out, std::string_view text, GfxUtils::Color color);
    };

    std::string TermiosMenuRenderHelper::to_string(const Core::ITerminalCore& terminal, const MenuData& menuData)
    {
        std::string frameStr; 

        terminal.hideCursor(frameStr);
        terminal.cursorHome(frameStr);

        // get windows size 
        auto termConfig = terminal.getTerminalConfig();
        auto winHeight = termConfig.height;
        auto winWidth = termConfig.width;

        size_t row{ 0 };

        // if welcome msg is too long we wrap it vertically
        frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        for (const auto& line : TermiosUtils::wrap(menuData.welcomeMsg, winWidth))
        {
            frameStr += line;
            ++row;
            terminal.moveCursor(frameStr, row, 0);
            frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        }

        ++row;
        terminal.moveCursor(frameStr, row, 0);
        frameStr += TermiosUtils::ERASE_LINE_TORIGHT;

        for (size_t i = 0; i < menuData.size(); i++)
        {    
            const auto& entry = menuData.entries()[i];
            if (menuData.isHighlighted(i))
            {
                appendColored(frameStr, entry.name, GfxUtils::Color::BRIGHT_WHITE);
            }
            else
            {
                frameStr += entry.name;
            }

            ++row;
            terminal.moveCursor(frameStr, row, 0);
            frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        }

        // if commands message too long we wrap it
        frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        for (const auto& line : TermiosUtils::wrap(menuData.commandsMsg, winWidth))
        {
            frameStr += line;
            ++row;
            terminal.moveCursor(frameStr, row, 0);
            frameStr += TermiosUtils::ERASE_LINE_TORIGHT;
        }

        // for every other line in window erase
        frameStr += TermiosUtils::ERASE_SCREEN_TOBOTTOM;

        frameStr += TermiosUtils::RESET_ATTRS;
        frameStr += TermiosUtils::RESET_COLORS;
        terminal.cursorHome(frameStr);

        return frameStr;
    }

    void TermiosMenuRenderHelper::appendColored(std::string& out, std::string_view text, GfxUtils::Color color)
    {
        out += TermiosUtils::Termios_toAnsiFgColor(color);
        out += text;
        out += TermiosUtils::Termios_toAnsiFgColor(GfxUtils::Color::Fg_Default);
    }
}