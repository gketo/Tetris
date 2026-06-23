#pragma once

#include "Core/Render/RenderVisitors.h"

#include <variant>

namespace Core {

    // add differents types of visitor
    using RenderVisitorVariant = std::variant<TerminalVisitor>;

}
