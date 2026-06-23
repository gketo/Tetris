#pragma once

#include "Core/Engine/EngineSM/EngineStateContext.h"
#include "Core/StateMachine/IState.h"
#include "Core/Utils/Logger.h"

namespace Core::Engine {

    class EngineStateSuspended : public IState<EngineStateContext>
    {
    public:
        EngineStateSuspended(EngineStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

    };

    inline void EngineStateSuspended::enter()
    {
        LOG_DEBUG("[EngineSM] EngineStateSuspended : enter()...");
        //do nothing
    }

    inline void EngineStateSuspended::update()
    {
        LOG_EXTRA("[EngineSM] EngineStateSuspended : Updating...");
        //do nothing
    }

    inline void EngineStateSuspended::exit()
    {
        LOG_DEBUG("[EngineSM] EngineStateSuspended : exit()...");
        //do nothing
    }

    inline bool EngineStateSuspended::isFinished() const 
    { 
        return m_isFinished;
    }
}