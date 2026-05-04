#pragma once

#include "Frame2D.h"
#include "MenuData.h"

#include <variant>

namespace Core {

    // add type of frame here aswell
    using DataVariant = std::variant<Core::MenuData, Core::Grid2D::Frame2D<char>>;

    // Helper function to convert DataVariant to string
    inline std::string dbg_to_string(const DataVariant& dataVar)
    {
        std::string dataStr = std::visit([](auto&& dataVar) -> std::string
            {
                using T = std::decay_t<decltype(dataVar)>;

                if constexpr (std::is_same_v<T, Core::MenuData>)
                    return std::string{ "MenuData" };

                else if constexpr (std::is_same_v<T, Core::Grid2D::Frame2D<char>>)
                    return std::string{ "Frame2D<char>" };

                else
                    return "Unknown";

            }, dataVar);

        return dataStr;
    }
}
