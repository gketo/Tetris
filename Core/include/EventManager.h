#pragma once

#include "EventContext.h"
#include "EventLayer.h"
#include "EventPriorityQueue.h"
#include "CommandVariant.h"
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

	class EventManager
	{
	public: 
		// EventManager(const IController& ci)
		// 	: m_controller{ci}
		// { }

		void addController(IControllerPtr ctrlPtr);

	    void bindInputs(const std::vector<InputBinding>& toBind);
        void unbindInputs(const std::vector<InputBinding>& toUnbind);
		void clearInputs();

        void pushActiveLayer(EventLayer layer);
        void popActiveLayer(EventLayer layer);

		void pollInputEvents();
		std::optional<Core::CommandVariant> popEvent();
		void clearInputEvents();
	
	private:
		std::vector<IControllerPtr> m_controllers;
		std::vector<InputBinding> m_inputBindings;
        std::unordered_set<EventLayer> m_activeLayers; // todo maybe later lower level need to ask higher levels if they can change event context layer
		EventPriorityQueue m_inputEvents; // ephemeral

		void bindController();
        bool isActive(EventLayer layer) const;
	};

}