#include "Core/GameController/GameController.h"

#include "Core/Event/CommandVariant.h"
#include "Core/GameController/GameControllerSM/GameStateGameOver.h"
#include "Core/GameController/GameControllerSM/GameStateLoading.h"
#include "App/Game/GameType.h"
#include "Core/Game/IGame.h"
#include "Core/StateMachine/StateMachine.h"

#include <memory>
#include <utility>

namespace Core::Session {

    bool GameController::handleEvent(CommandVariant e)
    {
        return m_sm.handleEvent(e);
    }
    
    void GameController::collectRenderData(RenderQueue& out) const
    {
        m_sm.collectRenderData(out);
    }

    void GameController::loadGame(App::Game::GameType gameType)
    {
        LOG_DEBUG("[GameController] Trying to load <%s> as current game...", App::Game::dbg_to_string(gameType)); 
        m_sm.clearAndPush(std::make_unique<GameStateLoading>(*this, gameType));
    }

    App::Game::IGame* GameController::getGame() const
    {
        return m_game.get();
    }

    void GameController::setGame(std::unique_ptr<App::Game::IGame> game)
	{
        if (!game)
        {
            throw std::invalid_argument("[GameController] setGame() received null game");
        }

		m_game = std::move(game);
	}

	void GameController::clear()
	{
		m_game = nullptr;
        m_sm.clear();
	}

    void GameController::update()
	{
        m_sm.update();
	}

	bool GameController::shouldExit()
	{
		return dynamic_cast<const GameStateGameOver*>(m_sm.getState()) ||
            dynamic_cast<const GameStateQuitted*>(m_sm.getState());
	}
}