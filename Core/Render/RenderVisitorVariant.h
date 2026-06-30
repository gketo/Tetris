#pragma once

// ==================== Includes ====================
#include "Core/Render/RenderVisitors.h"

// ==================== Includes ====================
#include <variant>

namespace Core {

    // add differents types of visitor
    using RenderVisitorVariant = std::variant<TerminalVisitor>;

}
