#pragma once

namespace Core {
    class EventManager; // forward declaration

    template <typename TContext>
    class StateMachine; // forward declaration
}

namespace Core::Session {
    class GameController; // forward declaration
}

namespace Core::Session {

    class GameStateContext
    {
    public:
        virtual ~GameStateContext() = default;

        virtual GameController& getGameController() = 0;
        virtual EventManager& getEventManager() = 0;
        virtual StateMachine<GameStateContext>& getStateMachine() = 0;
    };
}