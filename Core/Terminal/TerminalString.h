#pragma once

#include "Core/Terminal/TerminalChar.h"
#include "Core/Graphics/Style.h"
#include "Core/Utils/Logger.h"

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

    // inline std::vector<TerminalChar> toTerminalChars(const std::string& str)
    // {
    //     std::vector<TerminalChar> result;

    //     std::vector<std::string> pendingFormatting;
        
    //     for (size_t i = 0; i < str.size();)
    //     {
    //         if (str[i] == '\x1b')
    //         {
    //             size_t start = i;
    //             ++i;
    //             if (i < str.size() && str[i] == '[')
    //             {
    //                 ++i;
    //                 while (i < str.size())
    //                 {
    //                     char c = str[i++];
    //                     // CSI final byte
    //                     if ((c >= '@' && c <= '~'))
    //                     {
    //                         break;
    //                     }
    //                 }
    //                 pendingFormatting.emplace_back(str.substr(start, i - start));
    //                 continue;
    //             }
    //             // malformed escape sequence
    //             continue;
    //         }

    //         TerminalChar tc;
    //         tc.ch = str[i++];
    //         tc.preFormating = std::move(pendingFormatting);
    //         pendingFormatting.clear();
    //         result.push_back(std::move(tc));
    //     }
    //     return result;
    // }
}