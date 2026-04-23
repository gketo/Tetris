#pragma once

#include "Frame2D.h"
#include "MenuData.h"

#include <memory>
#include <variant>

namespace Core {

    // add type of frame here aswell
    using DataVariant = std::variant<Core::MenuData, Core::Grid2D::Frame2D<char>>;

}
