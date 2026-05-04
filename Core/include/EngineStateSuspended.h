#pragma once

#include "IEngineStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Engine {

    class EngineStateSuspended : public IState<IEngineStateContext>
    {
    public:
        EngineStateSuspended(IEngineStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

    };

    inline void EngineStateSuspended::enter()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateSuspended : enter()...");
        //do nothing
    }

    inline void EngineStateSuspended::update()
    {
        LOG_EXTRA("[GameEngineSM] EngineStateSuspended : update()...");
        //do nothing
    }

    inline void EngineStateSuspended::exit()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateSuspended : exit()...");
        //do nothing
    }

    inline bool EngineStateSuspended::isFinished() const 
    { 
        return m_isFinished;
    }
}