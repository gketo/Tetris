#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include "Game.h"

#include "TetrisGame.h" // debug dbg

namespace Core {

	class GameMaster
	{
	public:
		bool init(Core::EventManager<Game::Action>& em);
		bool isRunning();
		bool update(Game::Action action);

	private:
		Game::TetrisGame m_tetris{}; // debug dbg
		Game::Game& m_currentGame{ m_tetris };
	};

}

#endif