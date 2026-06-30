#pragma once

// ==================== Includes ====================
#include "Core/Geometry/Rect.h"

#include "Core/Graphics/GfxUtils.h"

#include "Core/Menu/MenuData.h"

#include "Core/Render/MenuView.h"
#include "Core/Render/Surface.h"

#include "Core/Terminal/TerminalString.h"
#include "Core/Terminal/TerminalSurface.h"
#include "Core/Terminal/Termios/TermiosUtils.h"

#include "Core/Types/Index2D.h"
#include "Core/Types/Size2D.h"

#include "Core/Utils/Logger.h"

// ==================== Includes ====================
#include <stdexcept>
#include <string>
#include <variant>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;

    struct TermiosMenuView : public Core::Render::MenuView
    {
        void renderToSurface(const Core::MenuData& menuData, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const override;
    };

    void TermiosMenuView::renderToSurface(const Core::MenuData& menuData, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const
    {
        auto* termSurface = dynamic_cast<Core::Terminal::TerminalSurface*>(&surface);
        if (!termSurface)
        {
            throw std::runtime_error("[TermiosMenuView] renderToSurface() Invalid surface type");
        }
        if (termSurface->data.empty())
        {
            throw std::runtime_error("[TermiosMenuView] renderToSurface() must provide allocated surface");
        }

        if (menuData.empty())
        {
            return;
        }

        if (!surface.isValidPoint(rect.start))
        {
            throw std::out_of_range("[TermiosMenuView] renderToSurface() start position out of surface range");
        }

        Core::Type::Index2D at;
        at.row = rect.start.y;
        at.col = rect.start.x;

        Core::Type::Size2D bounds;
        bounds.rows = rect.size.height;
        bounds.cols = rect.size.width;

        const auto endRow = at.row + bounds.rows;
        
        // welcome message
        for (const auto& line : TermiosUtils::wrap(menuData.welcomeMsg, bounds.cols))
        {
            termSurface->drawText(at, bounds, line);
            ++at.row;
            if (at.row >= endRow)
            {
                return;
            }
        }

        // menu entries
        for (size_t i = 0; i < menuData.size(); ++i)
        {            
            const auto& entry = menuData.entries()[i];

            if (menuData.isHighlighted(i))
            {
                GfxUtils::Style style;
                style.fg = GfxUtils::Color::BRIGHT_ORANGE;

                Core::Terminal::TerminalString tstr;
                tstr.style = style;
                tstr.str = entry.name;
                termSurface->drawText(at, bounds, tstr);
            }
            else
            {
                termSurface->drawText(at, bounds, entry.name);
            }

            ++at.row;
            if (at.row >= endRow)
            {
                return;
            }
        }

        // commands message
        for (const auto& line : TermiosUtils::wrap(menuData.commandsMsg, bounds.cols))
        {
            termSurface->drawText(at, bounds, line);

            ++at.row;
            if (at.row >= endRow)
            {
                return;
            }
        }
    }
}