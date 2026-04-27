#pragma once

#include "GameEngine.h"
#include "IContext.h"
#include "InputBinding.h"
#include "IState.h"
#include "Logger.h"
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
    
        void pause() override;
        void resume() override;

    private:
        Menu m_menu;
        void buildPausedMenu();
    };

    void StatePaused::buildPausedMenu()
	{
		MenuData md{};

        md.welcomeMsg = "Paused.";

        MenuEntry resume;
        resume.name = "Resume";
        // store a callback
        resume.callback = [this]() {
            if (auto ge = dynamic_cast<GameEngine*>(m_context))
            {
                m_isFinished = true;
            }
        };
        md.addEntry(std::move(resume));

        MenuEntry showRules;
        showRules.name = "Rules";
        // store a callback
        showRules.callback = [this]() {
            if (auto ge = dynamic_cast<GameEngine*>(m_context))
            {
                ge->m_sm.push(std::make_unique<StateDisplayRules>(m_context));
            }
        };
        md.addEntry(std::move(showRules));

        md.commandsMsg = "Use ARROW Up/Down to navigate. Press ENTER to select. Press Q to exit app.";

		m_menu.build(md);
	}

    inline void StatePaused::enter()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : enter()...");
        buildPausedMenu();
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
                if (std::holds_alternative<MenuAction>(*actionVariantOpt))
                {
                    switch (std::get<MenuAction>(*actionVariantOpt))
                        {
                        case MenuAction::MENU_ACCEPT: break;
                        case MenuAction::MENU_CANCEL: break;
                        case MenuAction::MENU_MOVE_UP: 
                            m_menu.moveUp(); 
                            break;
                        case MenuAction::MENU_MOVE_DOWN: 
                            m_menu.moveDown();
                            break;
                        case MenuAction::MENU_SELECT:
                            auto entry = m_menu.getSelectedEntry();
                            if (entry.callback)
                            {
                                (*entry.callback)();
                            }
                            else
                            {
                                throw std::runtime_error("StatePaused: Couldn't proceed action");
                            }
                            break;
                        }
                }
                else if (std::holds_alternative<EngineAction>(*actionVariantOpt))
                {
                    switch (std::get<EngineAction>(*actionVariantOpt))
                    {
                    case EngineAction::QUIT: // gerer lorsqu'on sort d'un jeu todo
                        m_isFinished = true;
                        ge->m_sm.clearAndPush(std::make_unique<StateQuitted>(m_context));
                        break;
                    default:
                        LOG_ERROR("[GameEngineSM] StatePaused: Unkown action");
                    }
                }
            }

            ge->m_renderer->submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
            ge->m_renderer->update();
        }
    }

    inline bool StatePaused::isFinished() const 
    { 
        return m_isFinished;
    }

    inline void StatePaused::pause()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : pause()...");
        m_isFinished = true;
    }

    inline void StatePaused::resume()
    {
        LOG_DEBUG("[GameEngineSM] StatePaused : resume()...");
        m_isFinished = false;
        if (auto ge = dynamic_cast<GameEngine*>(m_context))
        {
            ge->m_eventManager->clearInputBindings();
            ge->m_eventManager->registerInputBindings(GamePausedRegisteredEvents);
        }
    }

}