#pragma once

#include "Core/Graphics/GfxUtils.h"

#include <optional>
#include <unordered_set>
#include <variant>

namespace App::Grid {

    namespace GfxUtils = Core::Graphics::Utils;
    
    template <typename TContent>
    class Tile
    {
    public:
        std::optional<TContent> content;

        Tile() = default;

        Tile(GfxUtils::Color color)
        : m_style{ color, color }
        {}

        Tile(GfxUtils::Style style)
        : m_style{ style }
        {}

        Tile(std::optional<TContent> content, GfxUtils::Color color)
        : content{ content }
        , m_style{ color, color }
        {}

        Tile(std::optional<TContent> content, GfxUtils::Style style)
        : content{ content }
        , m_style{ style }
        {}

        // getter
        GfxUtils::Color fg() const { return m_style.fg; }
        GfxUtils::Color bg() const { return m_style.bg; }
        const std::unordered_set<GfxUtils::Attr>& attrs() const { return m_style.attrs; }
        const GfxUtils::Style& style() const { return m_style; }

        // setter
        void setFg(GfxUtils::Color color) { m_style.fg = color; }
        void setBg(GfxUtils::Color color) { m_style.bg = color; }

        void addAttr(GfxUtils::Attr attr)
        {
            m_style.addAttr(attr); 
        }

        void removeAttr(GfxUtils::Attr attr)
        {
            m_style.removeAttr(attr);
        }

        void clearAttrs()
        {
            m_style.clearAttrs();
        }

        bool hasAttr(GfxUtils::Attr attr) const
        {
            return m_style.hasAttr(attr);
        }

    protected:
        GfxUtils::Style m_style;
    };

    
}