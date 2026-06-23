#include "Core/Controller/Keyboard/CtrlKeyboard.h"

#include "Core/Event/Events/DeviceEvent.h"
#include "Core/Event/Source/IEventSource.h"

#include <optional>

namespace Core {
	std::optional<DeviceEvent> CtrlKeyboard::readEvent() const
	{
        return m_eventSource.readEvent();
	}
}