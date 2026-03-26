#pragma once

#include "EngineAction.h"
#include "EventManager.h"
#include "GameMaster.h"

#include <iostream>

namespace Core {

	class GameEngine
	{
	public:
		GameEngine(GameMaster& gm, EventManager& em)
			: m_gameMaster{ gm }
			, m_eventManager{ em }
		{}

		void init()
		{
			LOG_DEBUG("[GameEngine] Initializing...");	
			m_eventManager.init();	
			m_gameMaster.init(m_eventManager);
		}

		void run()
		{
			LOG_DEBUG("[GameEngine] Engine running...\n");

			auto rules = m_gameMaster.getRules();
			std::cout << rules;

			while (true) 
			{
				auto actionVariantOpt = m_eventManager.onEvent();

				if (actionVariantOpt) 
				{
					auto actionVariant = *actionVariantOpt;

					if (auto engineAction = std::get_if<EngineAction>(&actionVariant))
					{
						auto action = *engineAction;

						if (action == EngineAction::PLAY) 
						{	// launch game (eg while true)
							LOG_DEBUG("[GameEngine] Play requested...");
							break;
						}
						else if (action == EngineAction::QUIT)
						{	// quit (eg exit run)
							quit();
							return;
						}
					}
				}
			}
			
			LOG_DEBUG("[GameEngine] Launching game...");

			while (m_gameMaster.isRunning())
			{
				// get events from event manager (controller)
				auto actionVariantOpt = m_eventManager.onEvent();
				
				// update with events
				if (actionVariantOpt) 
				{
					auto actionVariant = *actionVariantOpt;

					std::visit([this](auto&& action) 
					{
						using actionType = std::decay_t<decltype(action)>;

						if constexpr (std::is_same_v<actionType, EngineAction>) 
						{
							if (m_gameMaster.isPaused())
							{
								switch (action)
								{
								case EngineAction::RESUME:
									resume();
									break;
								case EngineAction::QUIT:
									quit();
									break;
								default:
									LOG_DEBUG("[GameEngine] EngineAction ignored while paused");
									break;
								}
								return;
							}

							// Game is running
							switch (action) 
							{
							case EngineAction::PAUSE:
								pause();
								break;
							case EngineAction::QUIT:
								quit();
								break;
							default: 
								LOG_DEBUG("[GameEngine] EngineAction ignored");
								break;
							}
						} 
						else // Game action
						{
							LOG_DEBUG("[GameEngine] GameAction propagated");
							m_gameMaster.update(action);
						}
					}, actionVariant); // std::visit
				}
				// get render data
				
				// render

				// win lose ?

				// continue

				// break
			}

			LOG_DEBUG("[GameEngine] Engine shutting down...");
		}

		void resume()
		{
			LOG_DEBUG("[GameEngine] Resume requested...");
			m_gameMaster.resume();
		}

		void pause()
		{
			LOG_DEBUG("[GameEngine] Pause requested...");
			m_gameMaster.pause();
		}

		void quit()
		{
			LOG_DEBUG("[GameEngine] Quit requested...");
			if (m_gameMaster.isRunning())
			{				
				m_gameMaster.stop();
			}
		}

	private:
		GameMaster& m_gameMaster;
		EventManager& m_eventManager;
	};
}