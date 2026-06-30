#include "Core/Controller/Keyboard/CtrlKeyboard.h"

// ==================== Includes ====================
#include "Core/Event/Events/DeviceEvent.h"
#include "Core/Event/Source/IEventSource.h"

// ==================== Includes ====================
#include <optional>

namespace Core {
	std::optional<DeviceEvent> CtrlKeyboard::readEvent() const
	{
        return m_eventSource.readEvent();
	}
}