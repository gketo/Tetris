#pragma once

#include "Core/Event/Manager/EventManager.h"
#include "Core/GameController/GameController.h"
#include "Core/Engine/EngineSM/EngineStateContext.h"
#include "Core/StateMachine/IState.h"
#include "Core/Utils/Logger.h"

namespace Core::Engine {

    class EngineStateRunning : public IState<EngineStateContext>
    {
    public:
        EngineStateRunning(EngineStateContext& context)
        : IState(context)
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

        void pause() override;
        void resume() override;

    };

    inline void EngineStateRunning::enter()
    {
        LOG_DEBUG("[EngineSM] EngineStateRunning : enter()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::EngineRunning);
    }

    inline void EngineStateRunning::update()
    {
        LOG_EXTRA("[EngineSM] EngineStateRunning : Updating...");
        m_context.getGameController().update();
    }

    inline void EngineStateRunning::exit()
    {
        LOG_DEBUG("[EngineSM] EngineStateRunning : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::EngineRunning);
    }

    inline bool EngineStateRunning::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void EngineStateRunning::pause()
    {
        LOG_DEBUG("[EngineSM] EngineStateRunning : pause()...");
        m_isFinished = true;
        m_context.getEventManager().popActiveLayer(EventLayer::EngineRunning);
    }

    inline void EngineStateRunning::resume()
    {
        LOG_DEBUG("[EngineSM] EngineStateRunning : resume()...");
        m_isFinished = false;
        m_context.getEventManager().pushActiveLayer(EventLayer::EngineRunning);
    }

}