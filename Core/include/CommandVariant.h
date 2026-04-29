#pragma once

#include "EngineCommand.h"
#include "MenuCommand.h"
#include "TetrisCommand.h"

#include <string>
#include <variant>

namespace Core {

    using CommandVariant = std::variant<Core::MenuCommand, Core::EngineCommand, Game::Tetris::TetrisCommand>;

    inline std::string dbg_to_string(CommandVariant cmdVar)
    {
        std::string eventStr = std::visit([](auto&& cmdVar) -> std::string
            {
                using T = std::decay_t<decltype(cmdVar)>;

                if constexpr (std::is_same_v<T, MenuCommand>)
                    return std::string{ dbg_to_string(cmdVar) };

                else if constexpr (std::is_same_v<T, EngineCommand>)
                    return std::string{ dbg_to_string(cmdVar) };

                else if constexpr (std::is_same_v<T, Game::Tetris::TetrisCommand>)
                    return std::string{ dbg_to_string(cmdVar) };
                else
                    return "Unknown Event";

            }, cmdVar);

        return eventStr;
    }
}