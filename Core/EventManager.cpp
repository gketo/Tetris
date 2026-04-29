#include "EventManager.h"

#include "EventLayer.h"
#include "CommandVariant.h"
#include "DeviceEvent.h" // KeyCode
#include "InputBinding.h"
#include "IController.h"
#include "Logger.h"

#include <algorithm>
#include <queue>
#include <unordered_set>

namespace Core {

	void EventManager::addController(IControllerPtr ctrlPtr)
	{
		// add if not exists
		if (std::find(m_controllers.begin(), m_controllers.end(), ctrlPtr) == m_controllers.end()) 
		{
            m_controllers.emplace_back(std::move(ctrlPtr));
        }
	}

	void EventManager::bindInputs(const std::vector<InputBinding>& toBind)
    {
        auto exists = [&](const Core::InputBinding& b) {
            return std::find(m_inputBindings.begin(), m_inputBindings.end(), b)
                != m_inputBindings.end();
        };

        for (const auto& b : toBind)
        {
            if (!exists(b))
            {
                m_inputBindings.push_back(b);
            }
        }
    }

    void EventManager::unbindInputs(const std::vector<InputBinding>& toUnbind)
    {
        for (const auto& toRemove : toUnbind)
        {
            m_inputBindings.erase(
                std::remove_if(m_inputBindings.begin(), m_inputBindings.end(),
                    [&](const InputBinding& registered)
                    {
                        return registered == toRemove;
                    }),
                m_inputBindings.end()
            );
        }
    }

	void EventManager::clearInputs()
	{
		m_inputBindings.clear();
	}
    
    void EventManager::pushActiveLayer(EventLayer layer)
    {
        m_activeLayers.insert(layer);
    }

    void EventManager::popActiveLayer(EventLayer layer)
    {
        m_activeLayers.erase(layer);
    }

    bool EventManager::isActive(EventLayer layer) const
    {
        return m_activeLayers.contains(layer);
    }

	void EventManager::pollInputEvents()
	{
		std::unordered_set<Core::CommandVariant> seenActions;

        for (const auto& controller : m_controllers)
        {
            auto deviceEventOpt = controller->readEvent();
            if (deviceEventOpt)
            {
                // there is a device event
                auto deviceEvent = *deviceEventOpt;

                // for all registered events matching
                for (const auto& binding : m_inputBindings)
                {
                    // we do weak compare because timestamp don't matter here
                    if (binding.weakCompare(deviceEvent))
                    {
                        // prevent event registering twice from different controllers
                        if (seenActions.insert(binding.commandVar).second)
                        {
                            // filter events (layer not active, valid for input events)
                            if (isActive(binding.layer))
                            {
                                Event event;
                                event.timestamp = deviceEvent.timestamp;
                                event.layer = binding.layer;
                                event.commandVar = binding.commandVar;
                                LOG_DEBUG("[EventManager] %s", event.to_string().c_str());
                                m_inputEvents.push(event);
                            }
                        } 
                    }
                }
            }
        }
	}
	
	std::optional<Core::CommandVariant> EventManager::popEvent()
	{
        while (!m_inputEvents.empty())
        {
            auto event = m_inputEvents.top();
            m_inputEvents.pop();

            if (isActive(event.layer))
            {
                return event.commandVar;
            }
            // ephemeral safe to drop if not consumed
        }
        return std::nullopt;
	}

	void EventManager::clearInputEvents()
	{
		m_inputEvents = EventPriorityQueue();
	}
}