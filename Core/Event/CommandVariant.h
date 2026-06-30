#pragma once

// ==================== Includes ====================
#include "App/Game/Tetris/TetrisCommand.h"

#include "Core/Engine/EngineCommand.h"

#include "Core/Menu/MenuCommand.h"

// ==================== Includes ====================
#include <string>
#include <variant>

namespace Core {

    using CommandVariant = std::variant< Core::EngineCommand, Core::MenuCommand, App::Game::Tetris::TetrisCommand >;

    // Helper function to convert CommandVariant to string
    inline std::string dbg_to_string(CommandVariant cmdVar)
    {
        std::string cmdStr = std::visit([](const auto& cmdVar) -> std::string
            {
                return std::string{ dbg_to_string(cmdVar) };
            }, cmdVar);

        return cmdStr;
    }
}