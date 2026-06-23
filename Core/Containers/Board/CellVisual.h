#pragma once

#include "Core/Graphics/GfxUtils.h"

#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace Core::Container {

    namespace GfxUtils = Core::Graphics::Utils;

    using GlyphId = uint32_t;
    using ImageId = uint32_t;

    struct BlockElement
    {
        GfxUtils::Color blockColor;
    };

    struct BorderElement
    {
        GfxUtils::Color borderColor;
    };

    struct GlyphElement
    {
        std::optional<GlyphId> glyph;  // for emojies etc char32_t
        GfxUtils::Style style;

        GlyphElement(GlyphId g, GfxUtils::Style s = {})
        : glyph(g)
        , style(std::move(s))
        {}
        
    };

    struct ImageElement
    {
        ImageId imageId;
    };
    
    using RenderElement = std::variant<
                            BlockElement,
                            BorderElement,
                            GlyphElement,
                            ImageElement
                        >;

    struct CellVisual
    {
        CellVisual() = default;
        
        CellVisual(const RenderElement& re)
        : elements{ re }
        {}

        CellVisual(const std::vector<RenderElement>& vre)
        : elements{ vre }
        {}

        std::vector<RenderElement> elements;
    };

    // Helper function to convert RenderElement to string
    inline std::string dbg_to_string(const RenderElement& re)
    {
        std::string reStr = std::visit([](const auto& r) -> std::string
        {
            using T = std::decay_t<decltype(r)>;

            if constexpr (std::is_same_v<T, BlockElement>)
            {
                return std::string{ "BlockElement" };
            }
            else if constexpr (std::is_same_v<T, BorderElement>)
            {
                return std::string{ "BorderElement" };
            }
            else if constexpr (std::is_same_v<T, GlyphElement>)
            {
                return std::string{ "GlyphElement" };
            }
            else if constexpr (std::is_same_v<T, ImageElement>)
            {
                return std::string{ "ImageElement" };
            }
            else
            {
                return "Unknown";
            }
        }, re);

        return reStr;
    }

    inline std::ostream& operator<<(std::ostream& os, const CellVisual& c)
    { 
        for (const auto& elem : c.elements)
        {
            std::visit([&os](const auto& re)
            {
                using T = std::decay_t<decltype(re)>;

                if constexpr (std::is_same_v<T, BlockElement>)
                {
                    os << std::format( "BlockElement: BlockColor->{}", 
                        dbg_to_string(re.blockColor)
                    );
                }
                else if constexpr (std::is_same_v<T, BorderElement>)
                {
                    os << std::format( "BorderElement: BorderColor->{}",
                        dbg_to_string(re.borderColor)
                    );
                }
                else if constexpr (std::is_same_v<T, GlyphElement>)
                {
                    os << std::format( "GlyphElement: GlyphID->{}, Style->{}", 
                        re.glyph ? std::to_string(*(re.glyph)) : "None",
                        re.style.toString()
                    );
                }
                else if constexpr (std::is_same_v<T, ImageElement>)
                {
                    os << std::format( "ImageElement: ImageID->{}",
                        std::to_string(re.imageId)
                    );
                }
                else
                {
                    os << "Unknown";
                }
            }, elem);

        }
        return os;
    }

    // class CellRenderData
    // {
    // public:
    //     CellRenderData() = default;

    //     CellRenderData(CellVisual)
    //     : m_style{ color, color }
    //     {}

    //     CellRenderData(GfxUtils::Style style)
    //     : m_style{ style }
    //     {}
    //     // style
    //     GfxUtils::Color fg() const { return m_style.fg; }
    //     GfxUtils::Color bg() const { return m_style.bg; }
    //     const std::unordered_set<GfxUtils::Attr>& attrs() const { return m_style.attrs; }
    //     const GfxUtils::Style& style() const { return m_style; }

    //     void setColor(GfxUtils::Color c) { m_style.fg = c; m_style.bg = c; }
    //     void setFg(GfxUtils::Color color) { m_style.fg = color; }
    //     void setBg(GfxUtils::Color color) { m_style.bg = color; }
    //     void addAttr(GfxUtils::Attr attr) { m_style.addAttr(attr); }
    //     void removeAttr(GfxUtils::Attr attr) { m_style.removeAttr(attr); }
    //     void clearAttrs() { m_style.clearAttrs(); }

    //     bool hasAttr(GfxUtils::Attr attr) const { return m_style.hasAttr(attr); }

    // private:
    //     GfxUtils::Style m_style;
    // };

    // inline BlockVisual GfxColorToBlockVisual(GfxUtils::Color c)
    // {
    //     switch (color)
    //     {
    //     case GfxUtils::Color::BLACK:          return ;
    //     case GfxUtils::Color::RED:            return ;
    //     case GfxUtils::Color::GREEN:          return ;
    //     case GfxUtils::Color::ORANGE:         return ;
    //     case GfxUtils::Color::YELLOW:         return ;
    //     case GfxUtils::Color::BLUE:           return ;
    //     case GfxUtils::Color::MAGENTA:        return ;
    //     case GfxUtils::Color::CYAN:           return ;
    //     case GfxUtils::Color::WHITE:          return ;
    //     case GfxUtils::Color::BRIGHT_BLACK:   return ;
    //     case GfxUtils::Color::BRIGHT_RED:     return ;
    //     case GfxUtils::Color::BRIGHT_GREEN:   return ;
    //     case GfxUtils::Color::BRIGHT_ORANGE:  return ;
    //     case GfxUtils::Color::BRIGHT_YELLOW:  return ;
    //     case GfxUtils::Color::BRIGHT_BLUE:    return ;
    //     case GfxUtils::Color::BRIGHT_MAGENTA: return ;
    //     case GfxUtils::Color::BRIGHT_CYAN:    return ;
    //     case GfxUtils::Color::BRIGHT_WHITE:   return ;
    //     case GfxUtils::Color::Fg_Default:     return ;
    //     case GfxUtils::Color::Bg_Default:     return ;
    //     case GfxUtils::Color::Invalid:        return ;
    //     }
    //     return "Unknown";
    // }
}