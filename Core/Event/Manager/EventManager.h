#pragma once

// ==================== Includes ====================
#include "Core/Controller/IController.h"

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Manager/EventLayer.h"
#include "Core/Event/Manager/EventPriorityQueue.h"
#include "Core/Event/Binding/InputBinding.h"

// ==================== Includes ====================
#include <memory>
#include <optional>
#include <unordered_set>
#include <vector>

namespace Core {

	class EventManager
	{
	public: 
		void addController(std::unique_ptr<IController> ctrlPtr);

	    void bindInputs(const std::vector<InputBinding>& toBind);
        void unbindInputs(const std::vector<InputBinding>& toUnbind);
		void unbindAllInputs();

        void pushActiveLayer(EventLayer layer);
        void popActiveLayer(EventLayer layer);

		void pollInputEvents();
		std::optional<Core::CommandVariant> popInputEvent();
		void clearInputEvents();
	
	private:
		std::vector<std::unique_ptr<IController>> m_controllers;
		std::vector<InputBinding> m_inputBindings;
        std::unordered_set<EventLayer> m_activeLayers; // todo maybe later lower level need to ask higher levels if they can change event context layer
		EventPriorityQueue m_inputEvents; // ephemeral events/inputs in there

        bool isActive(EventLayer layer) const;
	};

}