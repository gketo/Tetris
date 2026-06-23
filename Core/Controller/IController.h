#pragma once

#include "Core/Event/Events/DeviceEvent.h"

#include <optional>

namespace Core {
    class IEventSource; // forward declaration
}

namespace Core {
	
	class IController
	{
	public:
		IController(const IEventSource& eventSource)
			: m_eventSource{ eventSource }
		{ }

		virtual ~IController() = default;

		virtual std::optional<DeviceEvent> readEvent() const = 0;

	protected:
		const IEventSource& m_eventSource;
	};
}