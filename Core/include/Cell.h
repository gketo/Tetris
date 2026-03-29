#pragma once

#include "TextAttributs.h"

#include <vector>

namespace Core
{
    class Cell
    {
    public:
        char ch;
        Color fg;
        Color bg;

        // getter
        const std::vector<Attr>& attrs() const
        {
            return m_attrs;
        }

        void addAttr(const Attr& attr)
        {
            // Keep attrs sorted on insertion
            auto it = std::lower_bound(m_attrs.begin(), m_attrs.end(), attr);
            // only insert if not already present (optional)
            if (it == m_attrs.end() || *it != attr)
            {
                m_attrs.insert(it, attr);
            }
        }

        void clearAttrs()
        {
            m_attrs.clear();
        }

    private:
        std::vector<Attr> m_attrs;
    };

} // namespace Core::Data