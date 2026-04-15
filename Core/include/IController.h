#pragma once

#include "DeviceEvent.h"
#include "IEventSource.h"

#include <optional>

namespace Core {
	
	class EventManager; // forward declaration

	class IController
	{
	public:
		IController(const IEventSource& eventSource)
			: m_eventSource{ eventSource }
		{ }

		virtual ~IController() = default;

		// virtual void bind(EventManager& em) const = 0;
		virtual std::optional<DeviceEvent> readEvent() const = 0;

	protected:
		const IEventSource& m_eventSource;
	};
}