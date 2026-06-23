#pragma once

#include <optional>

namespace Core {
    class MenuData; // forward declaration
}

namespace Core::Container {
    class Board;    // forward declaration
}

namespace Core::Help {
    struct HelpData; // forward declaration
}

namespace Core::Terminal {
    class ITerminalCore;    // forward declaration
}

namespace App::Game {//todo 
    class RulesData;    // forward declaration
}

// namespace App::Grid {
//     template <typename TTile>
//     class Grid2D;  // forward declaration

//     template <typename TContent>
//     class Tile;  // forward declaration
// }

// namespace App::Game::Tetris {
//     class TetrisBoard;   // forward declaration
// }

namespace Core {
    class TerminalVisitor
    {
    public:
        TerminalVisitor(Core::Terminal::ITerminalCore& r) 
        : m_terminalRenderer(r) 
        {}

        void operator()(const Core::MenuData& data) const;
        // void operator()(const App::Grid::Grid2D<App::Grid::Tile<char>>& frame) const;
        // void operator()(const App::Game::Tetris::TetrisBoard& board) const;
        void operator()(const Core::Container::Board& data) const;
        void operator()(const Core::Help::HelpData& data) const;

        // implement other operator here for each specific type of frame renderable by terminal
    private:
        Core::Terminal::ITerminalCore& m_terminalRenderer;
    };

}