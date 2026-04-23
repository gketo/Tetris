#pragma once

#include "ActionVariant.h"
#include "DataVariant.h"

#include <string>
#include <vector>

namespace Core {
    class EventManager; // forward declaration
}

namespace Game {

    struct Rules
    {
        std::string welcomeMsg;
        std::vector<std::string> rules;
        std::string commandsMsg;
    };

    class IGame
	{
    public:
        virtual ~IGame() = default;

        virtual void init(Core::EventManager& em) = 0;
        virtual void reset() = 0;
        virtual void bindKeys(Core::EventManager& em) = 0;
        virtual bool update(Core::ActionVariant action) = 0;
        virtual bool isGameOver() const = 0;

        virtual const Core::DataVariant& getData() const = 0;

		std::string_view getName() const;
        const Rules& getRules() const;

        // void launch();
        // void resume();
        // void pause();
        // void terminate();

    protected:
        Rules m_rules;
        Core::DataVariant m_data;    
        int m_minWindowHeight; // todo assert this exists
        int m_minWindowWidth;
        
        virtual void setRules() = 0;
	};

	inline const Rules& IGame::getRules() const
    {
        return m_rules;
    }

    // inline void IGame::launch()
    // {
    //     LOG_DEBUG("[Game] Launched...");
    // }

    // inline void IGame::resume()
    // {
    //     LOG_DEBUG("[Game] Resumed...");
    // }

    // inline void IGame::pause()
    // {
    //     LOG_DEBUG("[Game] Paused...");
    // }

    // inline void IGame::terminate()
    // {
    //     LOG_DEBUG("[Game] Received a termination request...");
    // }
}
