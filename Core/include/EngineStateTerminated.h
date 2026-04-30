#pragma once

#include "GameEngine.h"
#include "IEngineStateContext.h"
#include "IState.h"
#include "Logger.h"

namespace Core::Engine {

    class EngineStateTerminated : public IState<IEngineStateContext>
    {
    public:
        EngineStateTerminated(IEngineStateContext& context) : IState(context) {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    
    };

    inline void EngineStateTerminated::enter()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateTerminated : enter()...");
        //do nothing
        m_isFinished = true;
    }

    inline void EngineStateTerminated::update()
    {
        LOG_EXTRA("[GameEngineSM] EngineStateTerminated : update()...");
        //do nothing
    }

    inline void EngineStateTerminated::exit()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateTerminated : exit()...");
        //do nothing
    }

    inline bool EngineStateTerminated::isFinished() const 
    { 
        return m_isFinished;
    }
}