#include "AppLauncher.h"

#include "Config_CoreInputBindings.h"
#include "CtrlKeyboard.h"
#include "EventManager.h"
#include "EventLayer.h"
#include "GameEngine.h"
#include "GameType.h"
#include "IRenderer.h"
#include "Logger.h"
#include "Menu.h"
#include "TerminalCoreTermios.h"
#include "VisitorVariant.h"

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>

namespace Core {
    void AppLauncher::setGameChoice(Game::GameType gameType)
    {
        m_gameChoice = gameType;
    }

    void AppLauncher::buildGameChoiceMenu()
	{
		MenuData md{};

        md.welcomeMsg = "Welcome ! Please chose a game in the following list:";//aaaaa bbbbb cccccc dddddd eeee fffffff ggg hhhhhhhh iiiii jjjj kkkkkk lllll mmmmmmm nnnn oooooo ppppp qqq rrrrrr sssss tttt uuuuuu vvvvv wwwwwww xxx yyyyyy zzzzz aaaaa bbbbb cccccc dddddd eeee fffffff ggg hhhhhhhh iiiii jjjj kkkkkk lllll mmmmmmm nnnn oooooo ppppp qqq rrrrrr sssss tttt uuuuuu vvvvv wwwwwww xxx yyyyyy zzzzz";

        for (int i = static_cast<int>(Game::GameType::None) + 1; i < static_cast<int>(Game::GameType::Count); ++i)
        {
            Game::GameType gameType = static_cast<Game::GameType>(i);

            MenuEntry entry;
            entry.name = dbg_to_string(gameType);

            // store a callback to set current game
            entry.callback = [this, gameType]() {
                setGameChoice(gameType);
            };

            md.addEntry(std::move(entry));
        }

        md.commandsMsg = "Use ARROW Up/Down to navigate. Press ENTER to select. Press Q to exit app.";

		m_menu.build(md);
	}

    void AppLauncher::launch()
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
        bool exitLauncher{ false };
        while (!exitLauncher)
        {
            buildGameChoiceMenu();
            em->unbindAllInputs();
            em->bindInputs(GameChoiceMenuRegisteredEvents);
            em->pushActiveLayer(EventLayer::Menu);

            bool userAnswered{ false };
            do
            {
                renderer->submit(std::make_unique<DataVariant>(std::move(m_menu.getMenuData())));
                renderer->update();
                renderer->render();

                // get events from event manager (controller)
                em->pollInputEvents();
                auto actionVariantOpt = em->popInputEvent();

                if (actionVariantOpt)
                {
                    auto actionVariant= *actionVariantOpt;
                    std::visit([this, &exitLauncher, &userAnswered](auto&& action)
                    {
                        using actionType = std::decay_t<decltype(action)>;

                        if constexpr (std::is_same_v<actionType, MenuCommand>) 
                        {
                            switch (action)
                            {
                            case MenuCommand::MENU_ACCEPT: break;
                            case MenuCommand::MENU_CANCEL:
                                exitLauncher = true;
                                userAnswered = true;
                                break;
                            case MenuCommand::MENU_MOVE_UP: 
                                m_menu.moveUp(); 
                                break;
                            case MenuCommand::MENU_MOVE_DOWN: 
                                m_menu.moveDown();
                                break;
                            case MenuCommand::MENU_SELECT:
                                auto entry = m_menu.getSelectedEntry();
                                if (entry.callback)
                                {
                                    (*entry.callback)();
                                    userAnswered = true;
                                }
                                else
                                {
                                    throw std::runtime_error("AppLauncher: Couldn't set game choice");
                                }
                                break;
                            }
                        }
                    }, actionVariant); // std::visit
                }
            } while (!userAnswered && !exitLauncher);

            // user cancelled
            if (m_gameChoice == Game::GameType::None || exitLauncher)
            {
                if (m_gameEngine)
                {
                    m_gameEngine->terminate();
                    m_gameEngine = nullptr;
                }
                break;
            }

            em->unbindInputs(GameChoiceMenuRegisteredEvents);
            em->popActiveLayer(EventLayer::Menu);

            m_gameEngine = std::make_unique<Core::Engine::GameEngine>(*em, *renderer);

            m_gameEngine->init(m_gameChoice);
            m_gameEngine->run();

            // user quitted game
            LOG_DEBUG("[AppLauncher] User quitted. Back to choice menu...");
            m_gameChoice = Game::GameType::None;
        }

        renderer->terminate();
    }
}