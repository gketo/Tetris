#pragma once

#include "Frame2D.h"
#include "Lifecycle.h"

namespace Core {

    class IRenderer : virtual public Lifecycle
    {
    public:
        virtual ~IRenderer() = default;
        
        // virtual void render(const IRenderable& renderable) const = 0;
        virtual void render(const Frame2D& frame) const = 0;

    };
}