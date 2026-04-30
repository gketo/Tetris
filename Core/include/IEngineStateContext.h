#pragma once

namespace Core {
    class EventManager; // forward declaration
    class IRenderer;

    template<typename TContext>
    class StateMachine; // forward declaration
}

namespace Core::Session {
    class GameSession; // forward declaration
}

namespace Core::Engine {

    class IEngineStateContext
    {
    public:
        virtual ~IEngineStateContext() = default;

        virtual EventManager& getEventManager() = 0;
        virtual Core::Session::GameSession& getGameSession() = 0;
        virtual IRenderer& getRenderer() = 0;
        virtual StateMachine<IEngineStateContext>& getStateMachine() = 0;
    };
}