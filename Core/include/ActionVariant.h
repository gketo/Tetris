#pragma once

#include "EngineAction.h"
#include "MenuAction.h"
#include "TetrisAction.h"

#include <variant>

namespace Core {

    using ActionVariant = std::variant<Core::MenuAction, Core::EngineAction, Game::Tetris::TetrisAction>;

}