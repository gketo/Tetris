#pragma once

#include "Action.h"
#include "Game.h"

#include "TetrisGame.h" // debug dbg

#include <string>

namespace Core {
	class EventManager; // forward declaration

	class GameMaster
	{
	public:
		void init(Core::EventManager& em);
		std::string getRules();
		bool update(Action action);
		void resume();
		void pause();
		void stop();
		bool isRunning();
		bool isPaused();


	private:
		Tetris::TetrisGame m_tetris{}; // debug dbg
		Game::Game& m_currentGame{ m_tetris };
	};

}
