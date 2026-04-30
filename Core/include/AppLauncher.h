#pragma once 

#include "GameType.h"
#include "GameEngine.h"
#include "Menu.h"

namespace Core {

    class AppLauncher
    {
    public:
        void launch();

    private:
        Menu m_menu;
        Game::GameType m_gameChoice{ Game::GameType::None };
        std::unique_ptr<Core::Engine::GameEngine> m_gameEngine{ nullptr };
        
        void setGameChoice(Game::GameType gameType);
		void buildGameChoiceMenu();
    };

}