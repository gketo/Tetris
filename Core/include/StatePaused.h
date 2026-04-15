#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "InputBinding.h"
#include "IState.h"
#include "Logger.h"
#include "StateResumed.h"
#include "StateQuitted.h"

namespace Core::Engine {

    class StatePaused : public IState 
    {
    public:
        StatePaused(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StatePaused::enter()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : enter()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_eventManager->clearInputBindings();
            ge->m_eventManager->registerInputBindings(GamePausedRegisteredEvents);
        }
    }

    inline void StatePaused::exit()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : exit()...");
        //do nothing
    }

    inline void StatePaused::update()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : update()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            auto actionVariantOpt = ge->m_eventManager->popEvent();

            if (actionVariantOpt)
            {
                if (std::holds_alternative<EngineAction>(*actionVariantOpt))
                {
                    switch (std::get<EngineAction>(*actionVariantOpt))
                    {
                    case EngineAction::RESUME:
                        ge->m_sm.setNextState(std::make_unique<StateResumed>(m_context));
                        break;
                    case EngineAction::QUIT: // gerer lorsqu'on sort d'un jeu todo
                        ge->m_sm.setNextState(std::make_unique<StateQuitted>(m_context));
                        break;
                    default:
                        LOG_ERROR("[GameEngineSM] StatePaused: Unkown action");
                    }
                }
            }
        }
    }

    inline bool StatePaused::isFinished() const 
    { 
        return true; 
    }

}