#pragma once

#include "VisitorVariant.h"
#include "DataVariant.h"

#include <variant>

namespace Core {

    class RenderSystem 
    {
    public:
        RenderSystem() = default; 

        void render(const DataVariant& data, const VisitorVariant& visitor) 
        {
            std::visit([&](auto& v) 
            {
                std::visit(v, data);
            }, visitor);
        }
    };
}