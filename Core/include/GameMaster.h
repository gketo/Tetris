#pragma once

#include "Action.h"
#include "Game.h"
#include "GameLifecycle.h"

#include "TetrisGame.h" // debug dbg

#include <string>

namespace Core {

	class EventManager; // forward declaration
	class IRenderable;

	class GameMaster : public GameLifecycle
	{
	public:
		void init(Core::EventManager& em);
		std::string getRules();
		bool update(Action action);
		const IRenderable& getRenderData() const;

		const char* caller() const override;
		void onInit() override;
		void onLaunch() override;
		void onResume() override;
		void onPause() override;
		void onTerminate() noexcept override;
		void onQuit() noexcept override;

		bool isGameover();


	private:
		Tetris::TetrisGame m_tetris{}; // debug dbg
		Game::Game& m_currentGame{ m_tetris };
	};

}
