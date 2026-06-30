#pragma once

// ==================== Includes ====================
#include "Core/Graphics/Style.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
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