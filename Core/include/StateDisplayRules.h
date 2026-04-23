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

    private:
        Menu m_menu;
        void buildDisplayRulesMenu();
    };

    void StateDisplayRules::buildDisplayRulesMenu()
	{
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            auto rules = ge->m_gameMaster.getRules();
            MenuData md{};

            md.welcomeMsg = rules.welcomeMsg;

            for (const auto& rule : rules.rules)
            {
                if (rule == "Accept")
                {
                    throw std::runtime_error("DisplayRulesMenu : can't find another name than 'Accept' jackass ?");
                }
                MenuEntry entry;
                entry.name = rule;
                md.addEntry(std::move(entry));
            }
            
            MenuEntry accept;
            accept.name = "Accept";
            md.addEntry(std::move(accept));

            md.commandsMsg = rules.commandsMsg;
        
		    m_menu.build(md);
            
            if (auto found = m_menu.findIndexByName("Accept"); found != -1)
            {
                m_menu.setSelectedIndex(static_cast<size_t>(found));
            }
        }
	}

    inline void StateDisplayRules::enter()
    {
        LOG_DEBUG("[GameEngineSM] StateDisplayRules : enter()...");
        buildDisplayRulesMenu();
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
                            break;
                        default:
                            LOG_ERROR("[GameEngineSM] StateDisplayRules : update() Invalid menu input");
                            break;
                        }
                }
            }

            ge->m_renderer->submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
            ge->m_renderer->update();
        }
    }

    inline bool StateDisplayRules::isFinished() const 
    { 
        return m_isFinished; 
    }
}