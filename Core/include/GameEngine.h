#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "EventManager.h"
#include "GameMaster.h"

#include <iostream>

namespace Core {
	template<typename TActions>
	class GameEngine
	{
	public:
		GameEngine(GameMaster& gm, EventManager<TActions>& em)
			: m_gameMaster{ gm }
			, m_eventManager{ em }
		{
			std::cout << "GameEngine constructed.\n";
		};

		void run()
		{
			std::cout << "Engine running...\n";

			bool play_message_printed{ false };
			while (1)
			{
				if (!m_gameMaster.isRunning())
				{
					if (!play_message_printed)
					{
						std::cout << "press play\n";
						play_message_printed = true;
					}
				}

				// get events from event manager (controller)
				auto action = m_eventManager.onEvent(true);
				
				// update with events
				if (action)
					m_gameMaster.update(*action);

				// get render data
				// render
			}

			std::cout << "Engine shutting down...\n";
		}

		bool init()
		{
			return m_gameMaster.init(m_eventManager);
		}

	private:
		GameMaster& m_gameMaster{};
		EventManager<TActions>& m_eventManager{};
	};
}

#endif // !GAMEENGINE_H
