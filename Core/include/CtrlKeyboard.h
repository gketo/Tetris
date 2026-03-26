#pragma once

#include "DeviceEvent.h" // KeyCode
#include "IController.h"
#include "IEventSource.h"

#include <optional>

namespace Core {
	class EventManager; // forward declaration

	class CtrlKeyboard : public IController {
	public:
		CtrlKeyboard(const IEventSource& eventSource)
			: IController{ eventSource }
		{ }

		void bind(EventManager& em) const override;
		std::optional<KeyCode> readEvent() const override;
	};
}