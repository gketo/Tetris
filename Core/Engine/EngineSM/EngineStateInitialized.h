#pragma once

// ==================== Includes ====================
#include "App/Game/GameType.h"

#include "Core/Engine/EngineSM/EngineStateContext.h"
#include "Core/Engine/EngineSM/EngineStateRunning.h"

#include "Core/GameController/GameController.h"

#include "Core/Render/IRenderer.h"

#include "Core/StateMachine/IState.h"
#include "Core/StateMachine/StateMachine.h"

#include "Core/Utils/Logger.h"

namespace Core::Engine {

    class EngineStateInitialized : public IState<EngineStateContext>
    {
    public:
        EngineStateInitialized(EngineStateContext& context, App::Game::GameType gameType) 
        : IState(context)
        , m_gameType{ gameType }
        {}

        void enter() override;
        void update() override;
        void exit() override;

        bool isFinished() const override;

    private:
        App::Game::GameType m_gameType;
    };

    inline void EngineStateInitialized::enter()
    {
        LOG_DEBUG("[EngineSM] EngineStateInitialized : enter()...");
        m_context.getRenderer().clearScreen();
        m_context.getGameController().loadGame(m_gameType);
        m_isFinished = true;
        m_context.getStateMachine().push(std::make_unique<EngineStateRunning>(m_context));
    }

    inline void EngineStateInitialized::update()
    {
        LOG_EXTRA("[EngineSM] EngineStateInitialized : Updating...");
        // do nothing
    }

    inline void EngineStateInitialized::exit()
    {
        LOG_DEBUG("[EngineSM] EngineStateInitialized : exit()...");
        // do nothing
    }

    inline bool EngineStateInitialized::isFinished() const
    {
        return m_isFinished;
    }

}