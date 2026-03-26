#pragma once

#include "EngineAction.h"
#include "TetrisAction.h"

#include <variant>

namespace Core {

    using Action = std::variant<Core::EngineAction, Tetris::TetrisAction>;

}