#pragma once

#include "CommandVariant.h"
#include "DataVariant.h"
#include "InputBinding.h"
#include "RenderQueue.h"

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
        IGame(int minWinHeight, int minWinWidth)
        : m_minWindowHeight{ minWinHeight }
        , m_minWindowWidth{ minWinWidth }
        {}

        virtual ~IGame() = default;

        virtual void init() = 0;
        virtual void pause(Core::EventManager& em) = 0;
        virtual void resume(Core::EventManager& em) = 0;
        virtual void reset(Core::EventManager& em) = 0;
        virtual bool update(Core::CommandVariant action) = 0;
        virtual bool isGameOver() const = 0;

        virtual void collectRenderData(Core::RenderQueue& out) const = 0;

        virtual const Rules& getRules() const = 0;
        virtual const std::vector<Core::InputBinding>& getBindings() const = 0;

    protected:
        Rules m_rules;
        Core::DataVariant m_data;    
        int m_minWindowHeight; // todo assert this exists
        int m_minWindowWidth;
	};

	// inline const Rules& IGame::getRules() const
    // {
    //     return m_rules;
    // }
}
