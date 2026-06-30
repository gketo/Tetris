#pragma once

// ==================== Includes ====================
#include "Core/Controller/IController.h"

#include "Core/Event/Events/DeviceEvent.h"

// ==================== Includes ====================
#include <optional>

namespace Core {
    class IEventSource; // forward declaration
}

namespace Core {

	class CtrlKeyboard : public IController
    {
	public:
		CtrlKeyboard(const IEventSource& s)
			: IController{ s }
		{ }

		std::optional<DeviceEvent> readEvent() const override;
	};
}