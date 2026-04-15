#include "EventManager.h"

#include "ActionVariant.h"
#include "DeviceEvent.h" // KeyCode
#include "InputBinding.h"
#include "IController.h"
#include "Logger.h"

#include <queue>

namespace Core {

	void EventManager::addController(IControllerPtr ci)
	{
		// add if not exists
		if (std::find(m_controllers.begin(), m_controllers.end(), ci) == m_controllers.end()) 
		{
            m_controllers.emplace_back(std::move(ci));
        }
	}

	void EventManager::clearInputBindings()
	{
		m_registeredInputBindings.clear();
	}

	void EventManager::registerInputBindings(std::vector<InputBinding> bindings)
	{
		m_registeredInputBindings.insert(m_registeredInputBindings.end(), bindings.begin(), bindings.end());
	}

	void EventManager::pollEvents()
	{
		std::queue<Core::ActionVariant> tempActions;
		std::unordered_set<Core::ActionVariant> seenActions;

		for (const auto& controller : m_controllers)
		{
			auto deviceEventOpt = controller->readEvent();
			if (deviceEventOpt)
			{
				auto deviceEvent = *deviceEventOpt;

				// check if the event is known / allowed / registered (== if key value exists in m_registeredInputBindings)
				auto it = std::find_if(m_registeredInputBindings.begin(), m_registeredInputBindings.end(), 
							[&deviceEvent](const auto& binding)
							{
								return binding.event == deviceEvent;
							});

				if (it != m_registeredInputBindings.end())
				{ // found
					LOG_DEBUG("[EventManager] Registered event: %s", deviceEvent.to_string().c_str());
					
					auto action = it->action;

					// now check if event was just registered twice (eg on two connected controllers)
					if (seenActions.insert(action).second)
					{
						tempActions.push(action);
					}
				}
			}
		}

		while (!tempActions.empty()) 
		{
			m_pendingEvents.push(tempActions.front());
			tempActions.pop();
		}
	}
	
	std::optional<Core::ActionVariant> EventManager::popEvent()
	{
		if (!m_pendingEvents.empty())
		{
			auto action = m_pendingEvents.front();
			m_pendingEvents.pop();
			return action;
		}
		
		return std::nullopt;
	}

	void EventManager::clearPendingEvents()
	{
		m_pendingEvents = ActionQueue();
	}
}