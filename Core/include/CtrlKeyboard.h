#pragma once

#include "DeviceEvent.h"
#include "IController.h"

#include <optional>

namespace Core {
    class IEventSource; // forward declaration
}

namespace Core {

	class CtrlKeyboard : public IController
    {
	public:
		CtrlKeyboard(const IEventSource& eventSource)
			: IController{ eventSource }
		{ }

		std::optional<DeviceEvent> readEvent() const override;
	};
}