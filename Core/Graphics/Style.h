#pragma once

#include "Core/Graphics/Color.h"
#include "Core/Graphics/Attr.h"

#include <format>
#include <string>
#include <unordered_set>

namespace Core::Graphics::Utils {
    
    struct Style
    {
        Color fg{ Color::Fg_Default };
        Color bg{ Color::Bg_Default };
        std::unordered_set<Attr> attrs{ Attr::Default };

        bool hasAttr(Attr attr) const
        {
            return attrs.contains(attr);
        }

        void addAttr(Attr attr)
        {
            if (attr == Attr::Default)
            {
                clearAttrs();
                return;
            }

            // only insert if not already present
            auto [it, inserted] = attrs.insert(attr);
            if (inserted)
            {
                removeAttr(Attr::Default);
            }
        }

        void removeAttr(Attr attr)
        {
            // erase the attribute if it exists
            attrs.erase(attr);

            // ensure at least one attribute exists
            if (attrs.empty())
            {
                attrs.insert(Attr::Default);
            }
        }

        void clearAttrs()
        {
            attrs.clear();
            attrs.insert(Attr::Default);
        }

        std::string toString() const
        {
            std::string attrsStr;
            for (const auto& attr : attrs)
            {
                if (!attrsStr.empty())
                    attrsStr += ", ";
                attrsStr += dbg_to_string(attr);
            }

            return std::format(
                "fg: {}, bg: {}, attrs: [{}]",
                dbg_to_string(fg),
                dbg_to_string(bg),
                attrsStr.empty() ? "None" : attrsStr
            );
        }

        Style diff(const Style& other) const
        {
            // style different escape sequences
            Style styleDiff{};

            // foreground
            styleDiff.fg = fg;
            // background
            styleDiff.bg = bg;
            
            // typographic attributs
            // compute difference: elements in this but not in other
            styleDiff.attrs.clear();
            for (const auto& a : attrs)
            {
                if (!other.hasAttr(a)) {
                    styleDiff.attrs.insert(a);
                }
            }

            return styleDiff;
        }
    };
}
