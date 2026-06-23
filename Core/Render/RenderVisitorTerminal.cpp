#include "Core/Render/RenderVisitors.h"

// #include "Core/Grid2D.h"
#include "Core/Containers/Board/Board.h"
#include "Core/Menu/MenuData.h"
#include "Core/Help/Help.h"
#include "Core/Terminal/ITerminalCore.h"
// #include "Core/Tile.h"

#include <optional>
#include <utility>

namespace Core {

    void TerminalVisitor::operator()(const Core::MenuData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    // void TerminalVisitor::operator()(const App::Grid::Grid2D<App::Grid::Tile<char>>& data) const
    // {
    //     m_terminalRenderer.render(std::move(data));
    // }

    void TerminalVisitor::operator()(const Core::Container::Board& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    void TerminalVisitor::operator()(const Core::Help::HelpData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }
    // void RenderVisitor::operator()(const Grid::Grid2D<char>& frame) const {
    //     m_renderer.render(frame);
    // }

    // template <typename T>
    // void RenderVisitor::operator()(const T&) const {
    //     static_assert(sizeof(T) == 0, "RenderVisitor: Unhandled variant type");
    // }

}