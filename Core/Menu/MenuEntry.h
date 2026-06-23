#pragma once

#include <functional>
#include <string>
#include <optional>

namespace Core {

    struct MenuEntry
    {
        std::string name;
        std::optional<std::function<void()>> callback;
    };
}