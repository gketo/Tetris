#include "RenderVisitor.h"

#include "Frame2D.h"
#include "ITerminalCore.h"

namespace Core {

    void TerminalVisitor::operator()(const Core::MenuData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    void TerminalVisitor::operator()(const Game::RulesData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }
    
    void TerminalVisitor::operator()(const Core::Grid2D::Frame2D<char>& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    // void RenderVisitor::operator()(const Core::Grid2D::Frame2D<char>& frame) const {
    //     m_renderer.render(frame);
    // }

    // template<typename T>
    // void RenderVisitor::operator()(const T&) const {
    //     static_assert(sizeof(T) == 0, "RenderVisitor: Unhandled variant type");
    // }

}