#pragma once

#include "Core/Engine/EngineSM/EngineStateContext.h"
#include "Core/StateMachine/IState.h"
#include "Core/Utils/Logger.h"

namespace Core::Engine {

    class EngineStateTerminated : public IState<EngineStateContext>
    {
    public:
        EngineStateTerminated(EngineStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    
    };

    inline void EngineStateTerminated::enter()
    {
        LOG_DEBUG("[EngineSM] EngineStateTerminated : enter()...");
        //do nothing
        m_isFinished = true;
    }

    inline void EngineStateTerminated::update()
    {
        LOG_EXTRA("[EngineSM] EngineStateTerminated : Updating...");
        //do nothing
    }

    inline void EngineStateTerminated::exit()
    {
        LOG_DEBUG("[EngineSM] EngineStateTerminated : exit()...");
        //do nothing
    }

    inline bool EngineStateTerminated::isFinished() const 
    { 
        return m_isFinished;
    }
}