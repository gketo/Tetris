#pragma once

#include "IState.h"

#include <memory>
#include <stack>
#include <utility>

namespace Core {
// todo add mutex for transition

    template<typename TContext>
    class StateMachine 
    {
    public:
        bool handleEvent(const CommandVariant& e);
        bool collectRenderData(RenderQueue& out) const;
        void update();

        const IState<TContext>* getState();

        template <typename TState>
        void push(std::unique_ptr<TState> state);

        void clear();

        template <typename TState>
        void clearAndPush(std::unique_ptr<TState> state);


    private:
        std::stack<std::unique_ptr<IState<TContext>>> m_stack;
        IState<TContext>* m_currentState;

        void transitionUp(); 
        void transitionDown(); 
    };

    template<typename TContext>
    inline bool StateMachine<TContext>::handleEvent(const CommandVariant& e)
    {
        return m_currentState->handleEvent(e);
    }
    
    template<typename TContext>
    inline bool StateMachine<TContext>::collectRenderData(RenderQueue& out) const
    {
        return m_currentState->collectRenderData(out);
    }

    template<typename TContext>
    inline void StateMachine<TContext>::update() 
    {
        if (!m_stack.empty() && m_stack.top().get() != m_currentState)
        {
            transitionUp();
            return;
        }
        else if (m_currentState && m_currentState->isFinished())
        {
            transitionDown();
            return;
        }

        if (m_currentState)
        {
            m_currentState->update();
        }
    }

    template<typename TContext>
    inline const IState<TContext>* StateMachine<TContext>::getState() 
    { 
        return m_currentState;
    }

    template<typename TContext>
    template <typename TState>
    inline void StateMachine<TContext>::push(std::unique_ptr<TState> state)
    {
        static_assert(std::is_base_of<IState<TContext>, TState>::value, "StateMachine::push() TState must inherit from IState");
        m_stack.push(std::move(state));
    }

    template<typename TContext>
    inline void StateMachine<TContext>::clear()
    {
        while (!m_stack.empty())
        {
            if (m_stack.top())
            {
                m_stack.top()->exit();
            }
            m_stack.pop();
        }

        m_currentState = nullptr;
    }

    template<typename TContext>
    template <typename TState>
    inline void StateMachine<TContext>::clearAndPush(std::unique_ptr<TState> state)
    {
        static_assert(std::is_base_of<IState<TContext>, TState>::value, "StateMachine::clearAndPush() TState must inherit from IState");

        clear();

        m_stack.push(std::move(state));
        
        m_currentState = m_stack.top().get();

        if (m_currentState)
        {
            m_currentState->enter();
        }
    }

    template<typename TContext>
    inline void StateMachine<TContext>::transitionUp() 
    {
        if (m_stack.empty() || m_stack.top().get() == m_currentState)
        {
            return;
        }

        if (m_currentState)
        { 
            m_currentState->pause();
        }

        m_currentState = m_stack.top().get();

        if (m_currentState) 
        { 
            m_currentState->enter();
        }
    }

    template<typename TContext>
    inline void StateMachine<TContext>::transitionDown() 
    {
        if (m_currentState) 
        { 
            m_currentState->exit(); 
        }

        m_stack.pop();

        m_currentState = nullptr;

        if (!m_stack.empty())
        {
            m_currentState = m_stack.top().get();
        }

        if (m_currentState)
        {
            m_currentState->resume();
        }
    }
}