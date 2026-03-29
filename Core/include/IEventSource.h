#pragma once

#include "DeviceEvent.h"
#include "Lifecycle.h"

#include <optional>

namespace Core {

    class IEventSource : virtual public Lifecycle
    {
    public:
        virtual ~IEventSource() = default;

        virtual std::optional<DeviceEvent> readEvent() const = 0;
    };
    
}