#pragma once

#include "CommandVariant.h"
#include "Config_CoreInputBindings.h"
#include "DataVariant.h"
#include "EventLayer.h"
#include "EventManager.h"
#include "GameSession.h"
#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"
#include "Menu.h"
#include "MenuCommand.h"
#include "MenuData.h"
#include "RenderQueue.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace Core::Session {

    class GameStatePausedRules : public IState<IGameStateContext>
    {
    public:
        GameStatePausedRules(IGameStateContext& context)
        : IState(context)
        {}

        bool handleEvent(CommandVariant e) override;
        bool collectRenderData(RenderQueue& out) const override;

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

    private:
        Menu m_menu;
        void buildDisplayRulesMenu();
    };

    void GameStatePausedRules::buildDisplayRulesMenu()
	{
        auto rules = m_context.getGameSession().getGame()->getRules();
        
        MenuData md{};

        md.welcomeMsg = rules.welcomeMsg;

        for (const auto& rule : rules.rules)
        {
            if (rule == "Accept")
            {
                throw std::runtime_error("GameStatePausedRules : can't find another rule's name than 'Accept' jackass ?");
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

    inline bool GameStatePausedRules::handleEvent(CommandVariant e)
    {
        LOG_EXTRA("[GameSessionSM] GameStatePausedRules : handleEvent()...");
        if (auto* action = std::get_if<Core::MenuCommand>(&e))
        {
            switch (*action)
            {
            case MenuCommand::MENU_ACCEPT: 
                m_isFinished = true;
                return true;
            default:
                LOG_ERROR("[GameSessionSM] GameStatePausedRules: MenuCommand skipped");
                return false;
            }
        }
        return false;
    }

    inline bool GameStatePausedRules::collectRenderData(RenderQueue& out) const 
    {
        LOG_EXTRA("[GameSessionSM] GameStatePausedRules : collectRenderData()...");
        out.submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
        return true;
    }

    inline void GameStatePausedRules::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePausedRules : enter()...");
        buildDisplayRulesMenu();
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRulesRegisteredEvents);
    }

    inline void GameStatePausedRules::update()
    {
        LOG_EXTRA("[GameSessionSM] GameStatePausedRules : update()...");
        // do nothing
    }

    inline void GameStatePausedRules::exit()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePausedRules : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRulesRegisteredEvents);
    }

    inline bool GameStatePausedRules::isFinished() const 
    { 
        return m_isFinished; 
    }
}