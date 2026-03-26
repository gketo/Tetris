#pragma once

#include "DeviceEvent.h"
#include "IEventSource.h"

#include <memory>
#include <optional>

namespace Core {

	class ITerminalCore : public IEventSource
	{
    public:
        virtual void init();
        virtual std::optional<DeviceEvent> readEvent() const = 0;
        virtual ~ITerminalCore() = default;
 
    private:
        virtual bool enableRawMode() = 0;
        virtual bool disableRawMode() = 0;
	};

    inline void ITerminalCore::init()
    {
        if (!enableRawMode())
        {
            throw std::runtime_error("[ERROR] Couldn't init MacOS Terminal.\n");
        }
    }

    std::unique_ptr<ITerminalCore> createTerminalCore();

}
