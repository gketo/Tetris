#pragma once

namespace Core {
    
    class IRenderable
    {
    public:
        virtual ~IRenderable() = default;

        virtual bool isEmpty() const = 0;
    };
    
} 
