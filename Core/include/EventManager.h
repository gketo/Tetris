#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "CtrlInterface.h"
#include "RendererInterface.h"

#include <iostream>
#include <map>
#include <optional>
#include <string>

namespace Core {

	template<typename TAction>
	class EventManager
	{
	public: 
		EventManager(const CtrlInterface& ci)
			: m_controller{ci}
		{ }

		void mapKey(KeyCode code, TAction action)
		{
			m_eventMapping[code] = action;
		}

		std::optional<TAction> onEvent(bool lockpolling)
		{
			std::cout << "EventManager onEvent()\n";
			InputEvent event = m_controller.readUserEvent(lockpolling);
			
			if (!event.isValid) 
				return std::nullopt;

			event.print();

			if (m_eventMapping.count(event.keyCode))
				return m_eventMapping[event.keyCode];

			return std::nullopt;
		}
	
	private:
		const CtrlInterface& m_controller;
		std::map<KeyCode, TAction> m_eventMapping;
	};
}

#endif