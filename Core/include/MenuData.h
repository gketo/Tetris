#pragma once

#include "GameType.h"
#include "IRenderable.h"

#include <functional>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

namespace Core {

    struct MenuEntry {
        std::string name;
        std::optional<std::function<void()>> callback;
    };

    class MenuData : public IRenderable
    {
    public:
        std::string welcomeMsg;
        std::string commandsMsg;

        void clear();
        bool isEmpty() const override;
        size_t size() const;

        void addEntry(MenuEntry entry);
        const MenuEntry& getEntry(size_t index);
        const std::vector<MenuEntry>& entries() const;
        int findIndexByName(std::string name) const;

        void setSelectedIndex(size_t index);
        bool isHighlighted(size_t index) const;

    private:
        std::vector<MenuEntry> m_entries;
        std::unordered_set<std::string> m_seen;
        size_t m_selectedIndex;
    };
    
    inline void MenuData::clear()
    {
        m_entries.clear();
        m_seen.clear();

        welcomeMsg.clear();
        commandsMsg.clear();
    }

    inline bool MenuData::isEmpty() const 
    { 
        return m_entries.empty(); 
    }

    inline size_t MenuData::size() const
    {
        return m_entries.size();
    }

    inline void MenuData::addEntry(MenuEntry entry)
    {
        if (m_seen.insert(entry.name).second) 
        {
            m_entries.push_back(std::move(entry));
        }
    }

    inline const MenuEntry& MenuData::getEntry(size_t index)
    {
        if (index >= m_entries.size())
        {
            throw std::runtime_error("MenuData executeCallback(): index out of bounds");
        }

        return m_entries[index];
    }

    inline const std::vector<MenuEntry>& MenuData::entries() const
    {
        return m_entries;
    }

    inline int MenuData::findIndexByName(std::string name) const
    {
        if (m_entries.empty())
        {
            return -1;
        }

        auto it = std::find_if(m_entries.begin(), m_entries.end(),
            [&name](const MenuEntry& e) {
                return e.name == name;
            });
        
        if (it != m_entries.end())
        {
            return static_cast<int>(std::distance(m_entries.begin(), it));
        }

        return -1;
    }

    inline void MenuData::setSelectedIndex(size_t index)
    {
        if (index < 0 || index >= m_entries.size())
        {
            throw std::runtime_error("MenuData setSelectedIndex(): index out of bounds");
        }

        m_selectedIndex = index;
    }

    inline bool MenuData::isHighlighted(size_t index) const
    {
        if (index < 0 || index >= m_entries.size())
        {
            throw std::runtime_error("MenuData isHighlighted(): index out of bounds");
        }
        
        return index == m_selectedIndex;
    }

}