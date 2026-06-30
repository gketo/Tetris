#pragma once

// ==================== Includes ====================
#include "Core/Containers/Board/CellVisual.h"

#include "Core/Graphics/GfxUtils.h"

// ==================== Includes ====================
#include <cstddef>
#include <optional>
#include <unordered_set>
#include <vector>

namespace Core::Container {
    
    namespace GfxUtils = Core::Graphics::Utils;

    class Cell
    {
    public:
        CellVisual visual;

        Cell() = default;

        Cell(const RenderElement& re)
        : visual{ re }
        {}

        Cell(const std::vector<RenderElement>& reVect)
        : visual{ reVect }
        {}

        bool claimed() const { return m_isClaimed; }
    
        void claim() { m_isClaimed = true; }
        void unclaim() { m_isClaimed = false; }

    protected:
        bool m_isClaimed{ false };
    };

    inline std::ostream& operator<<(std::ostream& os, const Cell& c)
    { 
        os << c.visual;
        return os;
    }

    // template<TerminalChar>
    // class Cell<void> : public CellBase
    // {
    // public:
    //     Cell() = default;

    //     Cell(GfxUtils::Color color)
    //     : CellBase{ color }
    //     {}

    //     Cell(GfxUtils::Style style)
    //     : CellBase{ style }
    //     {}
    // };
}