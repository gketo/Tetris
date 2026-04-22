#include "LauncherApp.h"

#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "GameEngine.h"
#include "GameMaster.h"
#include "GameType.h"
#include "InputBinding.h"
#include "IRenderer.h"
#include "Logger.h"
#include "Menu.h"
#include "TerminalCoreTermios.h"
#include "VisitorVariant.h"

// Games
#include "TetrisGame.h"

#include <memory>

namespace Core {
    void LauncherApp::setGameChoice(Game::GameType gameType)
    {
        m_gameChoice = gameType;
    }

    void LauncherApp::buildGameChoiceMenu()
	{
		MenuData md{};

        md.welcomeMsg = "Welcome ! Please chose a game in the following list:";//aaaaa bbbbb cccccc dddddd eeee fffffff ggg hhhhhhhh iiiii jjjj kkkkkk lllll mmmmmmm nnnn oooooo ppppp qqq rrrrrr sssss tttt uuuuuu vvvvv wwwwwww xxx yyyyyy zzzzz aaaaa bbbbb cccccc dddddd eeee fffffff ggg hhhhhhhh iiiii jjjj kkkkkk lllll mmmmmmm nnnn oooooo ppppp qqq rrrrrr sssss tttt uuuuuu vvvvv wwwwwww xxx yyyyyy zzzzz";

        for (int i = static_cast<int>(Game::GameType::None) + 1; i < static_cast<int>(Game::GameType::Count); ++i)
        {
            Game::GameType gameType = static_cast<Game::GameType>(i);

            MenuEntry entry;
            entry.name = gametype_to_string(gameType);

            // store a callback to set current game
            entry.callback = [this, gameType]() {
                setGameChoice(gameType);
            };

            md.addEntry(std::move(entry));
        }

        md.commandsMsg = "Use ARROW Up/Down to navigate. Press ENTER to select. Press Q to exit app.";

		m_menu.build(md);
	}

    void LauncherApp::launch()
    {
        // create a terminal for user choice input, and init
        auto terminal = Terminal::Termios::createTerminalCore();
        if (terminal)
        {
            terminal->init();
        }

        // create a keyboard controller for user choice input, and init
        auto controller = std::make_unique<CtrlKeyboard>(*terminal);

        // event manager owns controller
        auto em = std::make_unique<EventManager>();
        em->addController(std::move(controller));

        // todo ask user what renderer and controller in relation to the game  
        std::unique_ptr<IRenderer> renderer;
        std::unique_ptr<VisitorVariant> renderVisitor;

        auto userChoice = SourceType::TERMINAL;
        if (userChoice == SourceType::TERMINAL)
        {   // not the other way around or dangling pointer
            renderVisitor = std::make_unique<VisitorVariant>(TerminalVisitor(*terminal));
            renderer = std::unique_ptr<IRenderer>(std::move(terminal)); // transfering ownership
        }

        renderer->setVisitor(std::move(renderVisitor));

        // ask user what game they want to play
        buildGameChoiceMenu();
        em->clearInputBindings();
        em->registerInputBindings(GameChoiceMenuRegisteredEvents);

        bool userAnswered{ false };
        do
        {
            renderer->submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
            renderer->update();
		    renderer->render();

            // get events from event manager (controller)
            em->pollEvents();
            auto actionVariantOpt = em->popEvent();

            if (actionVariantOpt)
            {
                auto actionVariant= *actionVariantOpt;
                std::visit([this, &userAnswered](auto&& action)
                {
                    using actionType = std::decay_t<decltype(action)>;

                    if constexpr (std::is_same_v<actionType, MenuAction>) 
                    {
                        switch (action)
                        {
                        case MenuAction::MENU_ACCEPT: break;
                        case MenuAction::MENU_CANCEL:
                            userAnswered = true;
                            break;
                        case MenuAction::MENU_MOVE_UP: 
                            m_menu.moveUp(); 
                            break;
                        case MenuAction::MENU_MOVE_DOWN: 
                            m_menu.moveDown();
                            break;
                        case MenuAction::MENU_SELECT:
                            auto entry = m_menu.getSelectedEntry();
                            if (entry.callback)
                            {
                                (*entry.callback)();
                                userAnswered = true;
                            }
                            else
                            {
                                throw std::runtime_error("LauncherApp: Couldn't set game choice");
                            }
                            break;
                        }
                    }
                }, actionVariant); // std::visit
            }
        } while (!userAnswered);

        // user cancelled
        if (m_gameChoice == Game::GameType::None)
        {
            return;
        }

        m_gameEngine = std::make_unique<Core::Engine::GameEngine>(em.get() , renderer.get());

        m_gameEngine->init(m_gameChoice);
        m_gameEngine->run();
    }
}