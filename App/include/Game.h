#pragma once

#include "Action.h"

#include <string>

namespace Core {
    class EventManager; // forward declaration
}

namespace Game {

    class Game
	{
    public:
        virtual ~Game() = default;

        virtual void bindKeys(Core::EventManager& em) = 0;
        virtual void init(Core::EventManager& em) = 0;
		virtual std::string rules() = 0;
        virtual bool update(Core::Action action) = 0;
        void resume();
        void pause();
        void stop();
        virtual bool isRunning() const = 0;
        virtual bool isPaused() const;

    protected:
        bool m_pauseRequested{ false };
        bool m_stopRequested{ false };
	};

    inline void Game::resume()
    {
        m_pauseRequested = false;
    }

    inline void Game::pause()
    {
        m_pauseRequested = true;
    }

    inline void Game::stop()
    {
        m_stopRequested = true;
    }

    inline bool Game::isPaused() const
    {
        return m_pauseRequested;
    }
}
