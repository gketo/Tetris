#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "InputBinding.h"
#include "IState.h"
#include "Logger.h"
#include "MenuAction.h"
#include "StateQuitted.h"
#include "StateRunning.h"

namespace Core::Engine {

    class StateDisplayRules : public IState 
    {
    public:
        StateDisplayRules(IContext* context) : IState(context) {}

        void enter() override;
        void exit() override;
        void update() override;

        bool isFinished() const override;
    };

    inline void StateDisplayRules::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateDisplayRules : enter()...");
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_eventManager->clearInputBindings();
            ge->m_eventManager->registerInputBindings(RulesDisplayRegisteredEvents);
        }
    }

    inline void StateDisplayRules::exit()
    {
        LOG_DEBUG("[GameEngineSM] StateDisplayRules : exit()...");
        // do nothing
    }

    inline void StateDisplayRules::update()
    {
        LOG_DEBUG("[GameEngineSM] StateDisplayRules : update()...");

        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            auto actionVariantOpt = ge->m_eventManager->popEvent();

            if (actionVariantOpt)
            {
                if (std::holds_alternative<MenuAction>(*actionVariantOpt))
                {
                    switch (std::get<MenuAction>(*actionVariantOpt))
                    {
                    case MenuAction::MENU_ACCEPT:
                        ge->m_sm.setNextState(std::make_unique<StatePaused>(m_context));
                        m_isFinished = true;
                        return;
                    // case MenuAction::MENU_CANCEL:
                        // ge->m_sm.setNextState(std::make_unique<StateQuitted>(m_context));
                        return;
                    default:
                        LOG_ERROR("[GameEngineSM] StateDisplayRules: Unkown action");
                    }
                }
            }
            ge->m_renderer->submit(std::move(ge->m_gameMaster.getRules()));
            ge->m_renderer->update();
        }
    }

    inline bool StateDisplayRules::isFinished() const 
    { 
        return m_isFinished; 
    }
}