#pragma once

#include "Action.h"
#include "Logger.h"

#include <string>

namespace Core {
    class EventManager; // forward declaration
    class IRenderable;
}

namespace Game {

    class Game
	{
    public:
        virtual ~Game() = default;

        virtual void init(Core::EventManager& em) = 0;
        virtual void bindKeys(Core::EventManager& em) = 0;
		virtual std::string rules() = 0;
        virtual bool update(Core::Action action) = 0;
        virtual bool isGameover() const = 0;
        virtual const Core::IRenderable& getRenderData() const = 0;
        void launch();
        void resume();
        void pause();
        void terminate();

    protected:
        bool terminationRequested{ false };
	};

    inline void Game::launch()
    {
        LOG_DEBUG("[Game] Launched...");
    }

    inline void Game::resume()
    {
        LOG_DEBUG("[Game] Resumed...");
    }

    inline void Game::pause()
    {
        LOG_DEBUG("[Game] Paused...");
    }

    inline void Game::terminate()
    {
        LOG_DEBUG("[Game] Received a termination request...");
        terminationRequested = true;
    }
}
