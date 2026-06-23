#pragma once

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Binding/Config_CoreInputBindings.h"
#include "Core/Render/RenderDataVariant.h"
#include "Core/Engine/EngineCommand.h"
#include "Core/Event/Manager/EventLayer.h"
#include "Core/Event/Manager/EventManager.h"
#include "Core/GameController/GameControllerSM/GameStatePausedRules.h"
#include "Core/GameController/GameControllerSM/GameStateQuitted.h"
#include "Core/GameController/GameControllerSM/GameStateContext.h"
#include "Core/StateMachine/IState.h"
#include "Core/Utils/Logger.h"
#include "Core/Menu/Menu.h"
#include "Core/Menu/MenuCommand.h"
#include "Core/Menu/MenuData.h"
#include "Core/Render/RenderQueue.h"
#include "Core/StateMachine/StateMachine.h"

#include <memory>
#include <stdexcept>
#include <utility>

namespace Core::Session {

    class GameStatePaused : public IState<GameStateContext> 
    {
    public:
        GameStatePaused(GameStateContext& context)
        : IState(context)
        {}

        bool handleEvent(CommandVariant e) override;
        bool collectRenderData(RenderQueue& out) const override;
        
        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;
    
        void pause() override;
        void resume() override;

    private:
        Menu m_menu;
        void buildPausedMenu();
    };

    void GameStatePaused::buildPausedMenu()
	{
		MenuData md{};

        md.welcomeMsg = "Paused.";

        MenuEntry resume;
        resume.name = "Resume";
        resume.callback = [this]() {
            m_isFinished = true;
        };
        md.addEntry(std::move(resume));

        MenuEntry showRules;
        showRules.name = "Rules";
        showRules.callback = [this]() {
            m_context.getStateMachine().push(std::make_unique<GameStatePausedRules>(m_context));
        };
        md.addEntry(std::move(showRules));

        md.commandsMsg = "Use ARROW Up/Down to navigate. Press ENTER to select. Press Q to exit app.";

		m_menu.build(md);
	}

    inline bool GameStatePaused::handleEvent(CommandVariant e)
    {
        LOG_EXTRA("[GameControllerSM] GameStatePaused : handleEvent()...");
        if (auto* action = std::get_if<Core::MenuCommand>(&e))
        {
            switch (*action)
            {
            case MenuCommand::MENU_ACCEPT: break;
            case MenuCommand::MENU_CANCEL: break;
            case MenuCommand::MENU_MOVE_UP: 
                m_menu.moveUp();
                return true;
            case MenuCommand::MENU_MOVE_DOWN: 
                m_menu.moveDown();
                return true;
            case MenuCommand::MENU_SELECT:
            {
                auto entry = m_menu.getSelectedEntry();
                if (entry.callback)
                {
                    (*entry.callback)();
                }
                else
                {
                    throw std::runtime_error("[GameControllerSM] GameStatePaused : Couldn't proceed action");
                }
                return true;
            }
            default:
                LOG_ERROR("[GameControllerSM] GameStatePaused : MenuCommand skipped");
                return false;
            }
        }
        else if (auto* action = std::get_if<Core::EngineCommand>(&e))
        {
            switch (*action)
            {
            case EngineCommand::QUIT:
                m_isFinished = true;
                m_context.getStateMachine().push(std::make_unique<GameStateQuitted>(m_context));
                return true;
            default:
                LOG_ERROR("[GameControllerSM] GameStatePaused : EngineCommand skipped");
                return false;
            }
        }
        return false;
    }

    inline bool GameStatePaused::collectRenderData(RenderQueue& out) const 
    {
        LOG_EXTRA("[GameControllerSM] GameStatePaused : collectRenderData()...");
        out.submit(std::make_unique<RenderDataVariant>(std::move(m_menu.getMenuData())));
        return true;
    }

    inline void GameStatePaused::enter()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePaused : enter()...");
        buildPausedMenu();
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRegisteredEvents);
    }

    inline void GameStatePaused::update()
    {
        LOG_EXTRA("[GameControllerSM] GameStatePaused : Updating...");
        //do nothing
    }

    inline void GameStatePaused::exit()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePaused : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRegisteredEvents);
    }

    inline bool GameStatePaused::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void GameStatePaused::pause()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePaused : pause()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRegisteredEvents);
        m_isFinished = true;
    }

    inline void GameStatePaused::resume()
    {
        LOG_DEBUG("[GameControllerSM] GameStatePaused : resume()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRegisteredEvents);
        m_isFinished = false;
    }

}