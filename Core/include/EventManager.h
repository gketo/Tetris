#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "CtrlInterface.h"

#include <iostream>
#include <map>
#include <string>

namespace Core {

	template<typename TActions>
	class EventManager
	{
	public: 
		void mapEvent(InputEvent event, TActions action)
		{
			m_eventMapping[event] = action;
		}

		void onEvent()
		{
			std::cout << "EventManager onEvent()\n";
		}
	
	private:
		std::map<InputEvent, TActions> m_eventMapping;
	};
}

#endif