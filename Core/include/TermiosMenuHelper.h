#pragma once

#include "MenuData.h"
#include "TermiosUtils.h"
#include "GraphicsUtils.h"

#include <string>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios;

    struct TermiosMenuRenderHelper
    {
    public:
        // returns menu as terminal printable string
        static std::string to_string(const MenuData& menuData);

    private:
        static void appendColored(std::string& out, std::string_view text, GfxUtils::Color color);
    };

    std::string TermiosMenuRenderHelper::to_string(const MenuData& menuData)
    {
        std::string frameStr{};

        frameStr += menuData.welcomeMsg;
        frameStr += '\r';
        frameStr += '\n';

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

            frameStr += '\r';
            frameStr += '\n';
        }

        frameStr += menuData.commandsMsg;

        return frameStr;
    }

    void TermiosMenuRenderHelper::appendColored(std::string& out, std::string_view text, GfxUtils::Color color)
    {
        out += TermiosUtils::Termios_toAnsiFgColor(color);
        out += text;
        out += TermiosUtils::Termios_toAnsiFgColor(GfxUtils::Color::Fg_Default);
    }
}