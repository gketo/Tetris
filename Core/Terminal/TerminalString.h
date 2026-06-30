#pragma once

// ==================== Includes ====================
#include "Core/Graphics/Style.h"

#include "Core/Terminal/TerminalChar.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace Core::Terminal {

    namespace GfxUtils = Core::Graphics::Utils;

    struct TerminalString
    {
        std::optional<GfxUtils::Style> style;
        std::string str;

        std::vector<TerminalChar> toTerminalChars() const
        {
            std::vector<TerminalChar> v(str.size());
            for (size_t i = 0; i < str.size(); ++i)
            {
                TerminalChar ch;
                if (style && i == 0)
                {
                    ch.preStyle = *style;
                }
                ch.ch = str[i];
                if (i == str.size() - 1)
                {
                    ch.postStyle = GfxUtils::Style{};
                }
                v[i] = ch;
            }
            return v;
        }
    };

}