#pragma once

// ==================== Includes ====================
#include "App/Rules/Rules.h"

#include "Core/Event/CommandVariant.h"
#include "Core/Event/Binding/InputBinding.h"

#include "Core/Render/RenderDataVariant.h"
#include "Core/Render/RenderQueue.h"
#include "Core/Render/WindowSize.h"

// ==================== Includes ====================
#include <string>
#include <vector>

namespace Core {
    class EventManager; // forward declaration
}

namespace App::Game {

    class IGame
	{
    public:
        IGame(Core::WindowSize minWinSize)
        : m_minWindowSize{ minWinSize }
        {}

        virtual ~IGame() = default;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void reset() = 0;
        virtual bool isGameOver() const = 0;

        virtual bool handleEvent(Core::CommandVariant e) = 0;
        virtual void collectRenderData(Core::RenderQueue& out) const = 0;

        virtual const App::Rules::Rules& getRules() const = 0;
        virtual const Core::Help::HelpData& getHelpData() const = 0;
        virtual const std::vector<Core::InputBinding>& getBindings() const = 0;

        const Core::WindowSize& getMinWindowSize() const { return m_minWindowSize; }
        
    protected:
        App::Rules::Rules m_rules;
        Core::WindowSize m_minWindowSize; // todo assert this exists and use it
	};

}
