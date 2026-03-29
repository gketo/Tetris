#pragma once

#include "EngineAction.h"
#include "EventManager.h"
#include "GameMaster.h"
#include "IRenderer.h"

#include <iostream>

namespace Core {

	class GameEngine
	{
	public:
		GameEngine(GameMaster& gm, EventManager& em, IRenderer& re)
			: m_gameMaster{ gm }
			, m_eventManager{ em }
			, m_renderer{ re }
		{}

		void init()
		{
			LOG_DEBUG("[GameEngine] Initializing...");
			m_eventManager.init();	
			m_gameMaster.init(m_eventManager);
		}

		void run()
		{
			LOG_DEBUG("[GameEngine] Engine running...");

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
			
			launch();

			while (!m_gameMaster.isGameover())
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
							switch (action) 
							{
							case EngineAction::RESUME:
								resume();
								break;
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
				const auto& renderData = m_gameMaster.getRenderData();

				// render
				renderData.accept(m_renderer); // polymorphic dispatch

				// win lose ?

				// continue

				// break
			}
		}

	private:
		GameMaster& m_gameMaster;
		EventManager& m_eventManager;
		IRenderer& m_renderer;

		void save()
		{
			LOG_DEBUG("[GameEngine] Save requested... ========TODO");
		}

		void launch()
		{
			LOG_DEBUG("[GameEngine] Launch requested...");
			m_gameMaster.launch();
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

		void terminate()
		{
			LOG_DEBUG("[GameEngine] Shutting down...");		
			m_gameMaster.terminate();
			m_renderer.terminate();
			LOG_DEBUG("[GameEngine] Shutdown complete...");
		}

		void quit()
		{
			LOG_DEBUG("[GameEngine] Quiting...");
			save();
			terminate();
		}
	};
}