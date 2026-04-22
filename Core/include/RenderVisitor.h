#pragma once

// forward declaration
namespace Core {
    class MenuData;
}

namespace Game {
    class RulesData;
}

namespace Core::Grid2D {
    template<typename T>
    class Frame2D;
}

namespace Core {

    class ITerminalCore; // forward declare

    class TerminalVisitor
    {
    public:
        TerminalVisitor(ITerminalCore& r) 
        : m_terminalRenderer(r) 
        {}

        void operator()(const Core::MenuData& menuData) const;
        void operator()(const Game::RulesData& rules) const;
        void operator()(const Core::Grid2D::Frame2D<char>&frame) const;

        // implement other operator here for each specific type of frame renderable by terminal
    private:
        ITerminalCore& m_terminalRenderer;
    };

}