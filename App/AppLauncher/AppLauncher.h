#pragma once 

// ==================== Includes ====================
#include "App/Game/GameType.h"

#include "Core/Engine/Engine.h"

#include "Core/Menu/Menu.h"

namespace App::Launcher {

    class AppLauncher
    {
    public:
        void launch();

    private:
        Core::Menu m_menu;
        App::Game::GameType m_gameChoice{ App::Game::GameType::None };
        std::unique_ptr<Core::Engine::Engine> m_gameEngine;
        
        void setGameChoice(App::Game::GameType gameType);
		void buildGameChoiceMenu();
    };

}