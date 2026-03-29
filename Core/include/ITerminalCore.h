#pragma once

#include "DeviceEvent.h"
#include "IEventSource.h"
#include "IRenderer.h"
#include "Lifecycle.h"
#include "Logger.h"

#include <memory>
#include <optional>

namespace Core {

	class ITerminalCore : public IEventSource, public IRenderer
	{
    public:
        virtual ~ITerminalCore() = default;

    protected:
        const char* caller() const override; // for clearer logging
        void onInit() override;
        void onTerminate() noexcept override;
		void onQuit() noexcept override;


    private:
        virtual bool enableRawMode() = 0;
        virtual bool disableRawMode() = 0;

        // virtual void clearScreen(std::string& framestr) const = 0;
        // virtual void hideCursor(std::string& framestr) const = 0;
        // virtual void showCursor(std::string& framestr) const = 0;
	};

    inline const char* ITerminalCore::caller() const  
    {
        return "ITerminalCore";
    }

    inline void ITerminalCore::onInit()
    {
        if (!enableRawMode())
        {
            throw std::runtime_error("[ERROR] Couldn't init MacOS Terminal.\n");
        }
    }

    inline void ITerminalCore::onTerminate() noexcept
    {
        LOG_DEBUG("[TerminalCore] Shutting down...");
        try 
        {
            disableRawMode();
        }
        catch (...) 
        {
            LOG_ERROR("[TerminalCore] Shutdown failed.\n");
            return;
        }
        LOG_DEBUG("[TerminalCore] Shutdown complete...");
    }

    inline void ITerminalCore::onQuit() noexcept
	{
		LOG_DEBUG("[TerminalCore] Quiting...");
        // save data here
	}

    std::unique_ptr<ITerminalCore> createTerminalCore();

}
