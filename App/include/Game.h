#ifndef GAME_H
#define GAME_H

#include "EventManager.h"

namespace Game {

    enum class Action
    {
        // general
        PLAY,
        PAUSE,
        QUIT,
        // tetris
        ROTATE_LEFT,
        ROTATE_RIGHT,
        //
        max_user_actions
    };

    // Helper function to convert KeyCode enum to string
    inline std::string dbg_to_string(Action action)
    {
        switch (action)
        {
        case Action::PLAY: return "PLAY";
        case Action::PAUSE: return "PAUSE";
        case Action::ROTATE_LEFT: return "ROTATE_LEFT";
        case Action::ROTATE_RIGHT: return "ROTATE_RIGHT";
        case Action::QUIT: return "QUIT";
        default: return "Unknown Action";
        }
    }
	
	class Game
	{
    public:
        virtual ~Game() = default;

        virtual bool init(Core::EventManager<Action>& em) = 0;
        virtual void mapKeys(Core::EventManager<Action>& em) = 0;
        virtual bool update(Action action) = 0;
        bool isRunning()
        {
            return m_isRunning;
        }

    protected:
        bool m_isRunning{ false };
	};
}



#endif