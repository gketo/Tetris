#pragma once

// ==================== Includes ====================
#include "Core/Event/Events/DeviceEvent.h"

// ==================== Includes ====================
#include <optional>

namespace Core {

    class IEventSource
    {
    public:
        virtual ~IEventSource() = default;

        virtual std::optional<DeviceEvent> readEvent() const = 0;
    };
    
}