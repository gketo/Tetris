#include "Core/Render/RenderVisitors.h"

// ==================== Includes ====================
#include "Core/Containers/Board/Board.h"

#include "Core/Menu/MenuData.h"

#include "Core/Help/Help.h"

#include "Core/Terminal/ITerminalCore.h"

// ==================== Includes ====================
#include <optional>
#include <utility>

namespace Core {

    void TerminalVisitor::operator()(const Core::MenuData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    void TerminalVisitor::operator()(const Core::Container::Board& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

    void TerminalVisitor::operator()(const Core::Help::HelpData& data) const
    {
        m_terminalRenderer.render(std::move(data));
    }

}