#pragma once

#include "Core/Help/Help.h"
#include "Core/Render/HelpView.h"
#include "Core/Graphics/GfxUtils.h"
#include "Core/Geometry/Rect.h"
#include "Core/Render/Surface.h"
#include "Core/Terminal/TerminalSurface.h"
#include "Core/Terminal/Termios/TermiosUtils.h"
#include "Core/Types/Index2D.h"
#include "Core/Types/Size2D.h"

#include "Core/Utils/Logger.h"

#include <stdexcept>
#include <string>

namespace Core::Terminal::Termios {

    namespace GfxUtils = Core::Graphics::Utils;
    namespace TermiosUtils = Core::Terminal::Termios::Utils;

    class TermiosHelpView : public Core::Render::HelpView
    {
    public:
        void renderToSurface(const Core::Help::HelpData& helpData, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const override;
    };

    void TermiosHelpView::renderToSurface(const Core::Help::HelpData& helpData, Core::Render::Surface& surface, const Core::Geometry::Rect& rect) const
    {
        auto* termSurface = dynamic_cast<Core::Terminal::TerminalSurface*>(&surface);
        if (!termSurface)
        {
            throw std::runtime_error("[TermiosHelpView] renderToSurface() Invalid surface type");
        }
        if (termSurface->data.empty())
        {
            throw std::runtime_error("[TermiosHelpView] renderToSurface() must provide allocated surface");
        }

        if (helpData.empty())
        {
            return;
        }

        if (!surface.isValidPoint(rect.start))
        {
            throw std::out_of_range("[TermiosHelpView] renderToSurface() start position out of surface range");
        }

        Core::Type::Index2D at;
        at.row = rect.start.y;
        at.col = rect.start.x;

        Core::Type::Size2D bounds;
        bounds.rows = rect.size.height;
        bounds.cols = rect.size.width;

        const auto endRow = at.row + bounds.rows;

        for (const auto& entry : helpData.commands)
        {
            std::string allActionsStr;
            
            for (size_t i = 0; i < entry.actions.size(); ++i)
            {
                const auto& actionStr = entry.actions[i];
                allActionsStr += actionStr;
                if (i + 1 < entry.actions.size())
                {
                    allActionsStr += ", ";
                }
            }
            
            auto totalCmdLength = entry.description.size() + 1 + allActionsStr.size(); // +1 for the space separating descrip and commands

            // padding
            int padding = bounds.cols - totalCmdLength;

            auto entryStr = entry.description + " ";
            if (padding > 0)
            {
                entryStr += std::string(padding, ' ');
            }
            entryStr += allActionsStr;

            for (const auto& line : TermiosUtils::wrap(entryStr, bounds.cols))
            {
                termSurface->drawText(at, bounds, line);
                ++at.row;
                if (at.row >= endRow)
                {
                    return;
                }
            }
        }

        // for each row in rect
        // for (size_t shapeRow = startRow; shapeRow < (startRow + maxRow); ++shapeRow)
        // {
        //     auto dataRow = shapeRow - startRow;

        //     if (dataRow >= helpData.helpCommands.size())
        //     {
        //         return;
        //     }

        //     auto cmd = helpData.helpCommands[dataRow];

        //     std::string commandsStr;
            
        //     for (size_t i = 0; i < cmd.commands.size(); ++i)
        //     {
        //         const auto& cmd = cmd.commands[i];
        //         commandsStr += cmd;
        //         if (i + 1 < cmd.size())
        //         {
        //             commandsStr += ", ";
        //         }
        //     }
            
        //     auto totalCmdLength = cmd.description.size() + 1 + commandsStr.size(); // +1 for the space separating descrip and commands

        //     // padding
        //     int padding = maxCol - totalCmdLength;

        //     auto command = cmd.description + " ";
        //     if (padding > 0)
        //     {
        //         command += std::string(padding, ' ');
        //     }
        //     command += commandsStr;

        //     termSurface->drawText(shapeRow, startCol, maxRow, maxCol, toTerminalChars(command));
        // }
    }
};