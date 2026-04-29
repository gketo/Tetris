#pragma once

namespace Core {
    class EventManager; // forward declaration

    template<typename TContext>
    class StateMachine; // forward declaration
}

namespace Core::Session {

    class GameSession; // forward declaration

    class IGameStateContext
    {
    public:
        virtual ~IGameStateContext() = default;

        virtual GameSession& getGameSession() = 0;
        virtual EventManager& getEventManager() = 0;
        virtual StateMachine<IGameStateContext>& getStateMachine() = 0;
    };
}