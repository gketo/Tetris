#pragma once

namespace Core {
    class EventManager; // forward declaration
    class IRenderer;

    template <typename TContext>
    class StateMachine; // forward declaration
}

namespace Core::Session {
    class GameController; // forward declaration
}

namespace Core::Engine {

    class EngineStateContext
    {
    public:
        virtual ~EngineStateContext() = default;

        virtual EventManager& getEventManager() = 0;
        virtual Core::Session::GameController& getGameController() = 0;
        virtual IRenderer& getRenderer() = 0;
        virtual StateMachine<EngineStateContext>& getStateMachine() = 0;
    };
}