#pragma once

#include "Config_CoreInputBindings.h"
#include "GameEngine.h"
#include "IEngineStateContext.h"
#include "IState.h"
#include "Logger.h"
#include "EngineStateSuspended.h"

namespace Core::Engine {

    class EngineStateRunning : public IState<IEngineStateContext>
    {
    public:
        EngineStateRunning(IEngineStateContext& context) : IState(context) {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

        void pause() override;
        void resume() override;
    };

    inline void EngineStateRunning::enter()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateRunning : enter()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::Engine);
    }

    inline void EngineStateRunning::update()
    {
        LOG_EXTRA("[GameEngineSM] EngineStateRunning : update()...");
        m_context.getGameSession().update();
    }

    inline void EngineStateRunning::exit()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateRunning : exit()...");
    }

    inline bool EngineStateRunning::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void EngineStateRunning::pause()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateRunning : pause()...");
        m_isFinished = true;
    }

    inline void EngineStateRunning::resume()
    {
        LOG_DEBUG("[GameEngineSM] EngineStateRunning : resume()...");
        m_isFinished = false;
    }

}