#pragma once

namespace Core {
    
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

        virtual bool empty() const = 0;
    };
    
} 
