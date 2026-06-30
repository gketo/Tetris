#pragma once

// ==================== Includes ====================
#include "Core/Render/RenderDataVariant.h"
#include "Core/Render/RenderVisitorVariant.h"

// ==================== Includes ====================
#include <variant>

namespace Core {

    class RenderSystem 
    {
    public:
        RenderSystem() = default; 

        void render(const RenderDataVariant& data, const RenderVisitorVariant& visitor) 
        {
            std::visit([&](auto& v) 
            {
                std::visit(v, data);
            }, visitor);
        }
    };
}