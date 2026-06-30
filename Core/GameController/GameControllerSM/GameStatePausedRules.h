#pragma once

// ==================== Includes ====================
#include "Core/Event/CommandVariant.h"
#include "Core/Event/Binding/Config_CoreInputBindings.h"
#include "Core/Event/Manager/EventLayer.h"
#include "Core/Event/Manager/EventManager.h"

#include "Core/GameController/GameController.h"
#include "Core/GameController/GameControllerSM/GameStateContext.h"

#include "Core/Menu/Menu.h"
#include "Core/Menu/MenuCommand.h"
#include "Core/Menu/MenuData.h"

#include "Core/Render/RenderDataVariant.h"
#include "Core/Render/RenderQueue.h"

#include "Core/StateMachine/IState.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace Core::Session {

    class GameStatePausedRules : public IState<GameStateContext>
    {
    public:
        GameStatePausedRules(GameStateContext& context)
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
        auto rules = m_context.getGameController().getGame()->getRules();
        
        MenuData md{};

        md.welcomeMsg = rules.welcomeMsg;

        for (const auto& rule : rules.rules)
        {
            if (rule == "Accept")
            {
                throw std::runtime_error("[GameControllerSM] GameStatePausedRules : can't find another rule's name than 'Accept' jackass ?");
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
        
        if (auto found = m_menu.findIndexByName("Accept"))
        {
            m_menu.setSelectedIndex(*found);
        }
	}

    inline bool GameStatePausedRules::handleEvent(CommandVariant e)
    {
        LOG_EXTRA("[GameControllerSM] GameStatePausedRules : handleEvent()...");
        if (auto* action = std::get_if<Core::MenuCommand>(&e))
        {
            switch (*action)
            {
            case MenuCommand::MENU_ACCEPT: 
                m_isFinished = true;
                return true;
            default:
                LOG_ERROR("[GameControllerSM] GameStatePausedRules: MenuCommand skipped");
                return false;
            }
        }
        return false;
    }

    inline bool GameStatePausedRules::collectRenderData(RenderQueue& out) const 
    {
        LOG_EXTRA("[GameControllerSM] GameStatePausedRules : collectRenderData()...");
        out.submit(std::make_unique<RenderDataVariant>(std::move(m_menu.getMenuData())));
        return true;
    }

    inline void GameStatePausedRules::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePausedRules : enter()...");
        buildDisplayRulesMenu();
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRulesRegisteredEvents);
    }

    inline void GameStatePausedRules::update()
    {
        LOG_EXTRA("[GameControllerSM] GameStatePausedRules : Updating...");
        // do nothing
    }

    inline void GameStatePausedRules::exit()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePausedRules : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRulesRegisteredEvents);
    }

    inline bool GameStatePausedRules::isFinished() const 
    { 
        return m_isFinished; 
    }
}