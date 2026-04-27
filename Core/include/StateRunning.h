#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "InputBinding.h"
#include "IState.h"
#include "Logger.h"
#include "StatePaused.h"

namespace Core::Engine {

    class StateRunning : public IState 
    {
    public:
        StateRunning(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;

        void pause() override;
        void resume() override;
    };

    inline void StateRunning::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateRunning : enter()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_eventManager->clearInputBindings();
            ge->m_eventManager->registerInputBindings(GameRunningRegisteredEvents);
            ge->m_renderer->submit(std::move(ge->m_gameMaster.getRenderData()));
            ge->m_renderer->update();
        }
    }

    inline void StateRunning::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateRunning : exit()...");
        // do nothing
    }

    inline void StateRunning::update()
    {
        LOG_DEBUG("[GameEngineSM] StateRunning : update()...");

        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            auto actionVariantOpt = ge->m_eventManager->popEvent();

            if (actionVariantOpt)
            {
                if (std::holds_alternative<EngineAction>(*actionVariantOpt))
                {
                    switch (std::get<EngineAction>(*actionVariantOpt))
                    {
                    case EngineAction::PAUSE:
                        ge->m_sm.push(std::make_unique<StatePaused>(m_context));
                        break;
                    default:
                        LOG_ERROR("[GameEngineSM] StateRunning: Unkown action");
                    }
                }
                else if (std::holds_alternative<MenuAction>(*actionVariantOpt))
                {
                    // do nothing
                }
                else
                {
                    ge->m_gameMaster.update(*actionVariantOpt);
                }
            }
            ge->m_renderer->submit(std::move(ge->m_gameMaster.getRenderData()));
            ge->m_renderer->update();

        }
    }

    inline bool StateRunning::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void StateRunning::pause()
    {
        LOG_DEBUG("[GameEngineSM] StateRunning : pause()...");
        m_isFinished = true;
    }

    inline void StateRunning::resume()
    {
        LOG_DEBUG("[GameEngineSM] StateRunning : resume()...");
        m_isFinished = false;
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_eventManager->clearInputBindings();
            ge->m_eventManager->registerInputBindings(GameRunningRegisteredEvents);
        }
    }

}