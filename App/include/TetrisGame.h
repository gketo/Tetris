#ifndef TETRIS_H
#define TETRIS_H

#include "Game.h"

namespace Game {

	class TetrisGame : public Game
	{
	public:
		bool init(Core::EventManager<Action>& em) override;
		void mapKeys(Core::EventManager<Action>& em) override;
		bool update(Action action) override;

	};

}



#endif