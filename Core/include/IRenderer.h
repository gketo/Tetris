#pragma once

#include <string>

namespace Core {

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void renderText(std::string text) = 0;
    };
}