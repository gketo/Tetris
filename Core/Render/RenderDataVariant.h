#pragma once

// ==================== Includes ====================
#include "Core/Containers/Board/Board.h"

#include "Core/Help/Help.h"

#include "Core/Menu/MenuData.h"

// ==================== Includes ====================
#include <optional>
#include <variant>

namespace Core {

    // add type of frame here aswell
    using RenderDataVariant = std::variant< 
                                Core::MenuData,
                                Core::Container::Board,
                                Core::Help::HelpData
                                >;

    // Helper function to convert RenderDataVariant to string
    inline std::string dbg_to_string(const RenderDataVariant& dataVar)
    {
        std::string dataStr = std::visit([](const auto& dataVar) -> std::string
            {
                using T = std::decay_t<decltype(dataVar)>;

                if constexpr (std::is_same_v<T, Core::MenuData>)
                {
                    return std::string{ "MenuData" };
                }
                else if constexpr (std::is_same_v<T, Core::Container::Board>)
                {
                    return std::string{ "Board" };
                }
                else if constexpr (std::is_same_v<T, Core::Help::HelpData>)
                {
                    return std::string{ "HelpData" };
                }
                else
                {
                    return "Unknown";
                }
            }, dataVar);

        return dataStr;
    }
}
