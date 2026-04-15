#ifdef EXCLUDE_THIS_FILE

// chatgpt
#pragma once

#include "Lifecycle.h"

namespace Core {
    // GameLifecycle: adds pause/resume
    class GameLifecycle : public Lifecycle 
    {
    public:
        void launch() 
        {
            if (!m_isInitialized)
            {
                LOG_DEBUG("[Lifecycle] %s: Not initialized, ignoring launch...", caller());
                return;
            }

            if (m_isRunning)
            {
                LOG_DEBUG("[Lifecycle] %s: Game is already running, ignoring launch...", caller());
                return;
            }

            LOG_DEBUG("[Lifecycle] %s: Launching...", caller());
            onLaunch();
            m_isPaused = false;
            m_isRunning = true;
        }

        void pause() 
        {
            if (!m_isRunning)
            {
                LOG_DEBUG("[Lifecycle] %s: Game is not running, ignoring pause...", caller());
                return;
            }

            if (m_isPaused) 
            {
                LOG_DEBUG("[Lifecycle] %s: Game is not resumed, ignoring pause...", caller());
                return;
            }

            LOG_DEBUG("[Lifecycle] %s: Pausing...", caller());
            onPause();
            m_isPaused = true;
        }

        void resume() 
        {
            if (!m_isRunning)
            {
                LOG_DEBUG("[Lifecycle] %s: Game is not running, ignoring resume...", caller());
                return;
            }

            if (!m_isPaused) 
            {
                LOG_DEBUG("[Lifecycle] %s: Game is not paused, ignoring resume...", caller());
                return;
            }

            LOG_DEBUG("[Lifecycle] %s: Resuming...", caller());
            onResume();
            m_isPaused = false;
        }

    protected:
        bool m_isPaused{ false };


        virtual void onLaunch() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
    };

}

#endif