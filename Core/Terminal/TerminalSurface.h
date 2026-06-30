#pragma once

// ==================== Includes ====================
#include "Core/Geometry/Point.h"

#include "Core/Lib/Matrix/Matrix.h"

#include "Core/Render/Surface.h"

#include "Core/Terminal/TerminalChar.h"
#include "Core/Terminal/TerminalString.h"
#include "Core/Terminal/TerminalUtils.h"

#include "Core/Types/Index2D.h"
#include "Core/Types/Size2D.h"

// ==================== Includes ====================
#include <algorithm>
#include <cstddef>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

namespace Core::Terminal {
    
    struct TerminalSurface : public Core::Render::Surface
    {
        Lib::Matrix::Matrix<TerminalChar> data;

        TerminalSurface() = default;

        TerminalSurface(size_t rows, size_t cols)
        : data{ rows, cols }
        {}
        
        void clear() override { data.clear(); }
        void reset() override { data.reset(); }
        bool resize(size_t rows, size_t cols) override { return data.resize(rows, cols); }

        bool isValidIndex(const Core::Type::Index2D& idx) const override;
        bool isValidPoint(const Core::Geometry::Point& point) const override;

        void drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const std::vector<TerminalChar>& vect);
        void drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const std::string& txt);
        void drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const TerminalString& tstr);

    private:
    };

    inline bool TerminalSurface::isValidIndex(const Core::Type::Index2D& idx) const
    {
        return idx.row < data.rows() && idx.col < data.cols();
    }

    inline bool TerminalSurface::isValidPoint(const Core::Geometry::Point& point) const
    {
        return isValidIndex({ point.y, point.x });
    }
    
    inline void TerminalSurface::drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const std::vector<TerminalChar>& vect)
    {
        // out of range
        if (!isValidIndex(at))
        {
            throw std::out_of_range("TerminalSurface drawText() : out of range");
        }

        // if text fits both inside surface and provided bounds
        if ((at.col + vect.size() < data.cols()) && (at.col + vect.size() < bounds.cols))
        {
            data.replaceRowRangeAt(at.row, at.col, vect);
            return;
        }
        else
        {
            size_t linelenght = std::min(data.cols() - at.col, bounds.cols);
            size_t txtBegin = 0;

            for (size_t row = at.row; row < data.rows(); ++row)
            {
                if (row > at.row + bounds.rows)
                {
                    return;
                }
                if (txtBegin >= vect.size())
                {
                    return;
                }
                size_t count = std::min(txtBegin + linelenght, vect.size());
                std::span<const TerminalChar> slice(
                    vect.data() + txtBegin,
                    count
                );
                data.replaceRowRangeAt(row, at.col, slice);
                txtBegin = count;
            }
            return;
        }
    }

    inline void TerminalSurface::drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const std::string& txt)
    {
        drawText(at, bounds, Utils::Terminal_StrToTerminalChars(txt));
    }

    inline void TerminalSurface::drawText(Core::Type::Index2D at, Core::Type::Size2D bounds, const TerminalString& tstr)
    {
        drawText(at, bounds, tstr.toTerminalChars());
    }
}