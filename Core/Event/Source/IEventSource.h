#pragma once

#include "Core/Event/Events/DeviceEvent.h"

#include <optional>

namespace Core {

    class IEventSource
    {
    public:
        virtual ~IEventSource() = default;

        virtual std::optional<DeviceEvent> readEvent() const = 0;
    };
    
}