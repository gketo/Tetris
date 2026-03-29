#pragma once

#include "Action.h"
#include "DeviceEvent.h" // KeyCode
#include "IController.h"
#include "Logger.h"

#include <map>
#include <optional>

namespace Core {

	class EventManager
	{
	public: 
		EventManager(const IController& ci)
			: m_controller{ci}
		{ }

		void init()
		{
			LOG_DEBUG("[EventManager] Initializing...");
			bindController();
		}

		void bindKey(KeyCode code, Core::Action action)
		{
			m_eventMapping[code] = action;
		}

		std::optional<Core::Action> onEvent()
		{
			auto keycodeOpt = m_controller.readEvent();
			
			if (keycodeOpt) 
			{
				auto keycode = *keycodeOpt;
				// check if we registered the event (== if key value exists in m_eventMapping)
				auto it = m_eventMapping.find(keycode);
				if (it != m_eventMapping.end())
				{
					LOG_DEBUG("[EventManager] Registered event: %s", keycode_to_string(keycode).data());
					return it->second;
				}
			}

			return std::nullopt;
		}
	
	private:
		std::map<KeyCode, Core::Action> m_eventMapping;
		const IController& m_controller;

		void bindController()
		{
			m_controller.bind(*this);
		}
	};
}