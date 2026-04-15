//chatgpt

// todo implement as statemachine
#pragma once

#include "Logger.h"

#include <string>

namespace Core {

class Lifecycle 
{
    public:
        virtual ~Lifecycle() = default;

        virtual const char* caller() const = 0; // for clearer logging

        void init() 
        {
            if (m_isInitialized)
            {
                LOG_DEBUG("[Lifecycle] %s: Already initialized, ignoring...", caller());
                return;
            }

            LOG_DEBUG("[Lifecycle] %s: Initialization requested...", caller());
            onInit();   // propagate exceptions
            LOG_DEBUG("[Lifecycle] %s: Initialization completed...", caller());

            m_isInitialized = true;
            m_isTerminated = false;
        }

        void terminate() noexcept 
        {
            if (!m_isInitialized) 
            {
                LOG_DEBUG("[%s] Not initialized, ignoring shutdown...", caller());
                return;
            }
            if (m_isTerminated)
            {
                LOG_DEBUG("[Lifecycle] %s: Already shutdown, ignoring...", caller());
                return;
            }

            LOG_DEBUG("[Lifecycle] %s: Termination requested...", caller());
            onTerminate();
            LOG_DEBUG("[Lifecycle] %s: Termination completed...", caller());

            m_isRunning = false;
            m_isTerminated = true;
        }

        void quit() noexcept
        {
            LOG_DEBUG("[Lifecycle] %s: Quitting requested...", caller());
            onQuit();
            LOG_DEBUG("[Lifecycle] %s: Quitting completed...", caller());
        }

    protected:
        bool m_isInitialized{ false };
        bool m_isTerminated{ true }; // unready
        bool m_isRunning{ false };

        virtual void onInit() = 0;   // derived classes implement
        virtual void onTerminate() noexcept = 0;
        virtual void onQuit() noexcept = 0;

    };
}
