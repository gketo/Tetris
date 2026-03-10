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
		GameEngine(GameMaster& gm, EventManager<TActions>& em, CtrlInterface& ci)
			: m_gameMaster{ gm }
			, m_eventManager{ em }
			, m_ctrlInterface{ ci }
		{
			std::cout << "GameEngine constructed.\n";
		};

		void run()
		{
			std::cout << "Engine running...\n";

			while (m_gameMaster.isRunning())
			{
				// get events
				m_eventManager.onEvent();
				// update with events
				//m_gameMaster.onEvent(event);
				// get render data
				// render
				break;
			}

			std::cout << "Engine shutting down...\n";
		}

		void init()
		{ }

	private:
		CtrlInterface& m_ctrlInterface{};
		EventManager<TActions>& m_eventManager{};
		GameMaster& m_gameMaster{};

	};
}

#endif // !GAMEENGINE_H
