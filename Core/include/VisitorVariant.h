#pragma once

#include "RenderVisitor.h"

#include <variant>

namespace Core {

    // add differents types of visitor
    using VisitorVariant = std::variant<TerminalVisitor>;

}
