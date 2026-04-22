#pragma once

#include "IState.h"

#include <memory>

namespace Core {
// to do add mutex for transition
    class StateMachine 
    {
    public:
        void update();
        const IState* getState();

        template <typename TState>
        void setNextState(std::unique_ptr<TState> state);

    private:
        std::unique_ptr<IState> m_state;
        std::unique_ptr<IState> m_nextState;
        bool m_isTransitioning{ false };

        void transitionTo(std::unique_ptr<IState> state); 
    };

    inline void StateMachine::update() 
    {
        if (m_isTransitioning)
        {
            return;
        }
        if (m_state)
        {
            m_state->update();
        }
        if (m_nextState && m_nextState != m_state)
        {
            transitionTo(std::move(m_nextState));
            m_nextState = nullptr;
        }
    }

    inline const IState* StateMachine::getState() 
    { 
        return m_state.get();
    }

    // todo attention if we want overwrite ignore or queue. currently overwriting
    template <typename TState>
    inline void StateMachine::setNextState(std::unique_ptr<TState> state)
    {
        static_assert(std::is_base_of<IState, TState>::value, "StateMachine::setNextState() TState must inherit from IState");
        m_nextState = std::move(state);
    }

    inline void StateMachine::transitionTo(std::unique_ptr<IState> state) 
    {
        if (m_state && !m_state->isFinished()) { return; }
        m_isTransitioning = true;
        if (m_state) { m_state->exit(); }
        m_state = std::move(state);
        if (m_state) { m_state->enter(); }
        m_isTransitioning = false;
    }
}