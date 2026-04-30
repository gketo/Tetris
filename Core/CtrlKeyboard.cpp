#include "CtrlKeyboard.h"

#include "DeviceEvent.h"
#include "IEventSource.h"

#include <optional>

namespace Core {
	std::optional<DeviceEvent> CtrlKeyboard::readEvent() const
	{
        return m_eventSource.readEvent();
	}
}