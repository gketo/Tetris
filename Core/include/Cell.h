#pragma once

#include "GraphicsUtils.h"

#include <unordered_set>

namespace Core::Grid2D {

    namespace GfxUtils = Core::Graphics::Utils;
    
    template<typename T>
    class Cell
    {
    public:
        T content;

        // getter
        const GfxUtils::Color& fg() const { return m_style.fg; }
        const GfxUtils::Color& bg() const { return m_style.bg; }
        const std::unordered_set<GfxUtils::Attr>& attrs() const { return m_style.attrs; }

        // setter
        void setFg(GfxUtils::Color color) { m_style.fg = color; }
        void setBg(GfxUtils::Color color) { m_style.bg = color; }

        void addAttr(const GfxUtils::Attr& attr)
        {
            if (attr == GfxUtils::Attr::Default)
            {
                clearAttrs();
                return;
            }

            // only insert if not already present
            auto [it, inserted] = m_style.attrs.insert(attr);
            if (inserted)
            {
                removeAttr(GfxUtils::Attr::Default);
            }
        }

        void removeAttr(const GfxUtils::Attr& attr)
        {
            // erase the attribute if it exists
            m_style.attrs.erase(attr);

            // ensure at least one attribute exists
            if (m_style.attrs.empty())
            {
                m_style.attrs.insert(GfxUtils::Attr::Default);
            }
        }

        void clearAttrs()
        {
            m_style.attrs.clear();
            m_style.attrs.insert(GfxUtils::Attr::Default);
        }

        bool hasAttr(const GfxUtils::Attr& attr) const { return m_style.attrs.contains(attr); }

    private:
        GfxUtils::Style m_style;
    };

}