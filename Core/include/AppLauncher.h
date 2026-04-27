#pragma once 

#include "GameEngine.h"
#include "Menu.h"

namespace Core {
    enum class Devices
    {
        KEYBOARD
    };

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