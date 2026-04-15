#pragma once

#include "ActionVariant.h"
#include "DeviceEvent.h" // KeyCode
#include "InputBinding.h"
#include "IController.h"

#include <algorithm>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <unordered_set>
#include <vector>

namespace Core {


	using IControllerPtr = std::unique_ptr<IController>;
	using ActionQueue = std::queue<Core::ActionVariant>;

	class EventManager
	{
	public: 
		// EventManager(const IController& ci)
		// 	: m_controller{ci}
		// { }

		void addController(IControllerPtr ci);

		void clearInputBindings();
		void registerInputBindings(std::vector<InputBinding> bindings);
		// void bindKey(KeyCode code, ActionVariant action);

		void pollEvents();
		std::optional<Core::ActionVariant> popEvent();
		void clearPendingEvents();
	
	private:
		std::map<KeyCode, Core::ActionVariant> m_eventMapping;
		std::vector<InputBinding> m_registeredInputBindings;
		std::vector<IControllerPtr> m_controllers;
		ActionQueue m_pendingEvents;

		void bindController();
	};

}