#pragma once

#include "Core/Graphics/Style.h"
#include "Core/Utils/Logger.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace Core::Terminal {

    namespace GfxUtils = Core::Graphics::Utils;

    struct TerminalChar
    {
        std::optional<GfxUtils::Style> preStyle;
        std::optional<GfxUtils::Style> postStyle;
        std::string ch; // for utf unicode etc compatibility we use string
    };
}


    // inline std::ostream& operator<<(std::ostream& os, const TerminalChar& tch)
    // { 
    //     for (const auto& pre : tch.preFormating)
    //     {
    //         os << pre;
    //     }
    //     os << tch.ch;
    //     for (const auto& post : tch.postFormating)
    //     {
    //         os << post;
    //     }
    //     return os;
    // }