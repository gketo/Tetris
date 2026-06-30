#pragma once

// ==================== Includes ====================
#include "Core/Containers/Board/CellVisual.h"

#include "Core/Graphics/Style.h"

#include "Core/Terminal/TerminalChar.h"

// ==================== Includes ====================
#include <string>
#include <string_view>
#include <vector>

namespace Core::Terminal::Utils {

    namespace GfxUtils = Core::Graphics::Utils;

    // todo in out paramter should be faster
    inline std::vector<Core::Terminal::TerminalChar> Terminal_StrToTerminalChars(const std::string_view str)
    {
        std::vector<Core::Terminal::TerminalChar> vect(str.size());
        for (size_t i = 0; i < str.size(); i++)
        {
            Core::Terminal::TerminalChar tch;
            tch.ch = str[i];
            vect[i] = tch;
        }
        return vect;
    }

    inline std::string Terminal_UnicodeToUtf8(uint32_t cp)
    {
        std::string s;
        if (cp <= 0x7F)
        {
            s += static_cast<char>(cp);
        }
        else if (cp <= 0x7FF)
        {
            s += static_cast<char>(0xC0 | (cp >> 6));
            s += static_cast<char>(0x80 | (cp & 0x3F));
        }
        else if (cp <= 0xFFFF)
        {
            s += static_cast<char>(0xE0 | (cp >> 12));
            s += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            s += static_cast<char>(0x80 | (cp & 0x3F));
        }
        else
        {
            s += static_cast<char>(0xF0 | (cp >> 18));
            s += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
            s += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            s += static_cast<char>(0x80 | (cp & 0x3F));
        }
        return s;
    }

    inline Core::Terminal::TerminalChar Terminal_CellVisualToTerminalChar(const Core::Container::CellVisual& cv)
    {
        Core::Terminal::TerminalChar tch;

        for (const auto& renderElem : cv.elements)
        {
            std::visit([&tch](const auto& re) 
            {
                using T = std::decay_t<decltype(re)>;

                if constexpr (std::is_same_v<T, Core::Container::BlockElement>)
                {
                    GfxUtils::Style style{};
                    style.fg = re.blockColor;
                    style.bg = re.blockColor;

                    tch.preStyle = style;
                    tch.ch = ' ';
                }
                else if constexpr (std::is_same_v<T, Core::Container::BorderElement>)
                {
                    return;
                }
                else if constexpr (std::is_same_v<T, Core::Container::GlyphElement>)
                {
                    tch.preStyle = re.style;

                    if (re.glyph)
                    {
                        tch.ch = Terminal_UnicodeToUtf8(*(re.glyph));
                    }
                    else
                    {
                        tch.ch = ' ';
                    }

                }
                else if constexpr (std::is_same_v<T, Core::Container::ImageElement>)
                {
                    // LOG_DEBUG("image elem %d", e.imageId);
                    return;
                }
                else
                {
                    LOG_ERROR("[TermiosBoardView] renderToSurface(): undefined/wrong visual type");
                }
            }, renderElem);
        }
        
        return tch;
    }
}