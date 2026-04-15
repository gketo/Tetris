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

    using MenuEntries = std::vector<MenuEntry>;

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
        const MenuEntries& entries() const;
        
        void setSelectedIndex(size_t index);
        bool isHighlighted(size_t index) const;

    private:
        MenuEntries m_entries;
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

    inline const MenuEntries& MenuData::entries() const
    {
        return m_entries;
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