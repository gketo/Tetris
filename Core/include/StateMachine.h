#pragma once

#include "IState.h"

#include <memory>
#include <stack>

namespace Core {
// to do add mutex for transition
    class StateMachine 
    {
    public:
        void update();

        const IState* getState();

        template <typename TState>
        void push(std::unique_ptr<TState> state);

        template <typename TState>
        void clearAndPush(std::unique_ptr<TState> state);

    private:
        std::stack<std::unique_ptr<IState>> m_stack;
        IState* m_currState;

        void transitionUp(); 
        void transitionDown(); 
    };

    inline void StateMachine::update() 
    {
        if (!m_stack.empty() && m_stack.top().get() != m_currState)
        {
            transitionUp();
            return;
        }
        else if (m_currState && m_currState->isFinished())
        {
            transitionDown();
            return;
        }

        if (m_currState)
        {
            m_currState->update();
        }
    }

    inline const IState* StateMachine::getState() 
    { 
        return m_currState;
    }

    template <typename TState>
    inline void StateMachine::push(std::unique_ptr<TState> state)
    {
        static_assert(std::is_base_of<IState, TState>::value, "StateMachine::push() TState must inherit from IState");
        m_stack.push(std::move(state));
    }

    template <typename TState>
    inline void StateMachine::clearAndPush(std::unique_ptr<TState> state)
    {
        static_assert(std::is_base_of<IState, TState>::value, "StateMachine::clearAndPush() TState must inherit from IState");

        while (!m_stack.empty())
        {
            if (m_stack.top())
            {
                m_stack.top()->exit();
            }
            m_stack.pop();
        }

        m_currState = nullptr;
        
        m_stack.push(std::move(state));
        
        m_currState = m_stack.top().get();

        if (m_currState)
        {
            m_currState->enter();
        }
    }

    inline void StateMachine::transitionUp() 
    {
        if (m_stack.empty() || m_stack.top().get() == m_currState)
        {
            return;
        }

        if (m_currState)
        { 
            m_currState->pause();
        }

        m_currState = m_stack.top().get();

        if (m_currState) 
        { 
            m_currState->enter();
        }
    }

    inline void StateMachine::transitionDown() 
    {
        if (m_currState) 
        { 
            m_currState->exit(); 
        }

        m_stack.pop();

        m_currState = nullptr;

        if (!m_stack.empty())
        {
            m_currState = m_stack.top().get();
        }

        if (m_currState)
        {
            m_currState->resume();
        }
    }
}