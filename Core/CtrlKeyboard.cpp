#include "CtrlKeyboard.h"

#include "CommandVariant.h"
#include "DeviceEvent.h"
#include "EngineCommand.h"
#include "EventManager.h"
#include "KeyCode.h"
#include "Logger.h"

#include <optional>

namespace Core {
	std::optional<DeviceEvent> CtrlKeyboard::readEvent() const
	{
        return m_eventSource.readEvent();
	}
}