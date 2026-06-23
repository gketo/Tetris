#pragma once

#include "Core/Event/CommandVariant.h"

#include <iostream>
#include <typeinfo>
#include <string>

namespace Core {
    class RenderQueue;  // forward declaration
}

namespace Core {

    template <typename TContext>
    class IState 
    {
    public:
        IState(TContext& context)
        : m_context{ context }
        {}
        
        virtual ~IState() = default;

        virtual bool handleEvent([[maybe_unused]] CommandVariant e) { return false; }
        virtual bool collectRenderData([[maybe_unused]] RenderQueue& out) const { return false ;}

        virtual void enter() = 0;
        virtual void exit() = 0;
        virtual void update() = 0;

        virtual bool isFinished() const = 0;

        virtual void pause() {};
        virtual void resume() {};

    protected:
        TContext& m_context;
        bool m_isFinished{ false };
    };
}
