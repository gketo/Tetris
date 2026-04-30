#pragma once

#include "EngineCommand.h"
#include "MenuCommand.h"
#include "TetrisCommand.h"

#include <string>
#include <variant>

namespace Core {

    using CommandVariant = std::variant< Core::EngineCommand, Core::MenuCommand, Game::Tetris::TetrisCommand >;

    // Helper function to convert CommandVariant to string
    inline std::string dbg_to_string(CommandVariant cmdVar)
    {
        std::string cmdStr = std::visit([](auto&& cmdVar) -> std::string
            {
                return std::string{ dbg_to_string(cmdVar) };
            }, cmdVar);

        return cmdStr;
    }
}