#pragma once

// ==================== Includes ====================
#include "Core/Event/Events/DeviceEvent.h"

// ==================== Includes ====================
#include <optional>

namespace Core {
    class IEventSource; // forward declaration
}

namespace Core {
	
	class IController
	{
	public:
		IController(const IEventSource& s)
			: m_eventSource{ s }
		{ }

		virtual ~IController() = default;

		virtual std::optional<DeviceEvent> readEvent() const = 0;

	protected:
		const IEventSource& m_eventSource;
	};
}