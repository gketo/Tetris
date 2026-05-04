#pragma once

#include "CommandVariant.h"
#include "Config_CoreInputBindings.h"
#include "DataVariant.h"
#include "EngineCommand.h"
#include "EventLayer.h"
#include "EventManager.h"
#include "GameStatePausedRules.h"
#include "GameStateQuitted.h"
#include "IGameStateContext.h"
#include "IState.h"
#include "Logger.h"
#include "Menu.h"
#include "MenuCommand.h"
#include "MenuData.h"
#include "RenderQueue.h"
#include "StateMachine.h"

#include <memory>
#include <stdexcept>
#include <utility>

namespace Core::Session {

    class GameStatePaused : public IState<IGameStateContext> 
    {
    public:
        GameStatePaused(IGameStateContext& context)
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
        LOG_EXTRA("[GameSessionSM] GameStatePaused : handleEvent()...");
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
                    throw std::runtime_error("GameStatePaused: Couldn't proceed action");
                }
                return true;
            }
            default:
                LOG_ERROR("[GameSessionSM] GameStatePaused: MenuCommand skipped");
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
                LOG_ERROR("[GameSessionSM] GameStatePaused: EngineCommand skipped");
                return false;
            }
        }
        return false;
    }

    inline bool GameStatePaused::collectRenderData(RenderQueue& out) const 
    {
        LOG_EXTRA("[GameSessionSM] GameStatePaused : collectRenderData()...");
        out.submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
        return true;
    }

    inline void GameStatePaused::enter()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePaused : enter()...");
        buildPausedMenu();
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRegisteredEvents);
    }

    inline void GameStatePaused::update()
    {
        LOG_EXTRA("[GameSessionSM] GameStatePaused : update()...");
        //do nothing
    }

    inline void GameStatePaused::exit()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePaused : exit()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRegisteredEvents);
    }

    inline bool GameStatePaused::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void GameStatePaused::pause()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePaused : pause()...");
        m_context.getEventManager().popActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().unbindInputs(GameStatePausedRegisteredEvents);
        m_isFinished = true;
    }

    inline void GameStatePaused::resume()
    {
        LOG_DEBUG("[GameSessionSM] GameStatePaused : resume()...");
        m_context.getEventManager().pushActiveLayer(EventLayer::GameMenu);
        m_context.getEventManager().bindInputs(GameStatePausedRegisteredEvents);
        m_isFinished = false;
    }

}