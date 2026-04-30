#pragma once

namespace Core {
    class ITerminalCore;    // forward declaration
    class MenuData; // forward declaration
}

namespace Game {
    class RulesData;    // forward declaration
}

namespace Core::Grid2D {
    template<typename TCell>
    class Frame2D;  // forward declaration
}

namespace Core {
    class TerminalVisitor
    {
    public:
        TerminalVisitor(ITerminalCore& r) 
        : m_terminalRenderer(r) 
        {}

        void operator()(const Core::MenuData& menuData) const;
        void operator()(const Core::Grid2D::Frame2D<char>&frame) const;

        // implement other operator here for each specific type of frame renderable by terminal
    private:
        ITerminalCore& m_terminalRenderer;
    };

}