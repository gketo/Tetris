#ifdef EXCLUDE_THIS_FILE

#include "archiveGameEngine.h"

#include "EngineAction.h"
#include "EventManager.h"
#include "GameMaster.h"
#include "InputBinding.h"
#include "IRenderer.h"
#include "Menu.h"
#include "MenuAction.h"
#include "MenuData.h"

#include <memory>
#include <string>

namespace Core::archiveGameEngine {

    void GameEngine::init(Game::GameType gameType)
	{
		LOG_DEBUG("[GameEngine] Initializing...");
		
		m_eventManager->clearInputBindings();
		m_gameMaster.setCurrentGame(gameType);
        m_gameMaster.initGame(*m_eventManager);

		m_state = EngineState::INITIALIZED;
	}

	void GameEngine::run()
	{		
		if (m_state == EngineState::UNINITIALIZED)
		{
			throw std::runtime_error("GameEngine: run() called but Engine is uninitialized");
		}

		LOG_DEBUG("[GameEngine] Engine running...");

		// main loop on game
		while (m_state != EngineState::TERMINATED)
		{
			switch (m_state)
			{
			case EngineState::INITIALIZED: 
				m_state = EngineState::DISPLAY_RULES;
				break;
			case EngineState::DISPLAY_RULES:
			{
				onDisplayRules();
				break;
			}
			case EngineState::RUNNING:
			{
				onRun();
				break;
			}
			case EngineState::PAUSED:
			{
				onPause();
				break;
			}
			case EngineState::RESUMED:
			{
				onResume();
				break;
			}
			case EngineState::QUITTED:
			{
				onQuit();
				break;
			}
			case EngineState::TERMINATED:
				onTerminate();
				return;
			default:
				LOG_ERROR("[GameEngine] run: Engine state should not be reachable here");
			}
		}
	}

	bool GameEngine::isGameOver()
	{
		return m_gameMaster.isGameOver() ;
	}
	
	void GameEngine::handleOnDisplayRulesAction(MenuAction action)
	{
		switch (action)
		{
		case MenuAction::MENU_ACCEPT:
			m_state = EngineState::RUNNING;
			break;
		case MenuAction::MENU_CANCEL:
			m_state = EngineState::QUITTED;
			break;
		default:
			LOG_ERROR("[GameEngine] onDisplayRules: Unkown action");
		}
	}

	void GameEngine::handleOnRunAction(EngineAction action)
	{
		switch (action) 
		{
		case EngineAction::PAUSE:
			m_state = EngineState::PAUSED;
			break;
		default:
			LOG_ERROR("[GameEngine] onRun: Unkown action");
		}
	}
	
	void GameEngine::handleOnPauseAction(EngineAction action)
	{
		switch (action)
		{
		case EngineAction::RESUME:
			m_state = EngineState::RESUMED;
			break;
		case EngineAction::QUIT: // gerer lorsqu'on sort d'un jeu todo
			m_state = EngineState::QUITTED;
			break;
		default:
			LOG_ERROR("[GameEngine] onPause: Unkown action");
		}
	}

	void GameEngine::handleOnMenuAction(MenuAction action)
	{
		switch (m_state)
		{
		case EngineState::DISPLAY_RULES: handleOnDisplayRulesAction(action); break;
		default:
			LOG_ERROR("[GameEngine] onMenuAction: No menu action expected");
		}
	}

	void GameEngine::handleOnEngineAction(EngineAction action)
	{
		switch (m_state)
		{
		case EngineState::RUNNING: handleOnRunAction(action); break;
		case EngineState::PAUSED: handleOnPauseAction(action); break;
		default:
			LOG_ERROR("[GameEngine] onEngineAction: No engine action expected");
		}
	}

	template<typename T>
	void GameEngine::handleOnGameAction(const T& action)
	{
		if (m_state == EngineState::RUNNING)
		{
			LOG_DEBUG("[GameEngine] GameAction propagated");
			m_gameMaster.update(action);
		}
	}

	void GameEngine::processEvents()
	{
		// get events from event manager (controller)
		m_eventManager->pollEvents();
		auto actionVariantOpt = m_eventManager->popEvent();

		if (actionVariantOpt)
		{
			auto actionVariant= *actionVariantOpt;

			std::visit([this](auto&& action)
			{
				using actionType = std::decay_t<decltype(action)>;

				if constexpr (std::is_same_v<actionType, EngineAction>) 
				{
					handleOnEngineAction(action);
				}
				else if constexpr (std::is_same_v<actionType, MenuAction>)
				{
					handleOnMenuAction(action);
				}
				else // Game action
				{
					handleOnGameAction(action);
				}
			}, actionVariant); // std::visit
		}
	}

//todo safe rendering with data empty

	void GameEngine::render()
	{
		switch (m_state)
		{
		case EngineState::DISPLAY_RULES: 
        {
            m_renderer->render(m_gameMaster.getRules());
            break;
        }
		case EngineState::RUNNING: 
        {
            m_renderer->render(m_gameMaster.getRenderData()); 
            break;
        }
		default:
			LOG_ERROR("[GameEngine] render: Not in a rendering state");
		}
	}

	void GameEngine::save()
	{
		LOG_DEBUG("[GameEngine] Save requested... ========TODO");
	}

	void GameEngine::reset()
	{
		LOG_DEBUG("[GameEngine] Reset requested... ========TODO");
		m_eventManager->clearPendingEvents();
		m_gameMaster.unsetCurrentGame();
		m_menu.clear();
	}

	void GameEngine::onDisplayRules()
	{
		LOG_DEBUG("[GameEngine] onDisplayRules...");
		if (m_prevState != EngineState::DISPLAY_RULES)
		{
			m_eventManager->clearInputBindings();
			m_eventManager->registerInputBindings(RulesDisplayRegisteredEvents);
		}
		m_prevState = m_state;
		
		processEvents();
		render();
    }

	void GameEngine::onRun()
	{
		LOG_DEBUG("[GameEngine] onRun...");
		if (m_prevState != EngineState::RUNNING)
		{
			m_eventManager->clearInputBindings();
			m_eventManager->registerInputBindings(GameRunningRegisteredEvents);
		}
		m_prevState = m_state;
		
		processEvents();
		render();
	}

	void GameEngine::onPause()
	{
		LOG_DEBUG("[GameEngine] onPause...");
		if (m_prevState != EngineState::PAUSED)
		{
			m_eventManager->clearInputBindings();
			m_eventManager->registerInputBindings(GamePausedRegisteredEvents);
		}
		m_prevState = m_state;
		processEvents();

	}

	void GameEngine::onResume()
	{
		LOG_DEBUG("[GameEngine] onResume...");
		m_prevState = m_state;
		m_state = EngineState::RUNNING;
	}

	void GameEngine::onQuit()
	{
		LOG_DEBUG("[GameEngine] onQuit...");
		save();
		// show score todo debug
		m_state = EngineState::TERMINATED;
	}
	
	void GameEngine::onTerminate()
	{
		LOG_DEBUG("[GameEngine] onTerminate...");
		LOG_DEBUG("[GameEngine] Termination requested, shutting down...");
		m_renderer->terminate();
		LOG_DEBUG("[GameEngine] Shutdown complete...");
	}

}
#endif
