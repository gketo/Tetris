#pragma once

namespace Core {
    
    class IRenderer;

    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

        virtual void accept(IRenderer& renderer) const = 0;
    };
    
} // namespace Core
