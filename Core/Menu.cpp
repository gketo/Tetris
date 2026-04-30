#include "Menu.h"

#include "MenuData.h"
#include "MenuEntry.h"

#include <utility>
#include <string>

namespace Core {

    void Menu::clear()
    {
        m_menuData.clear();
        m_selectedIndex = 0;
    }

    void Menu::build(MenuData md)
    {
        clear();
        m_menuData = std::move(md);
    }

    int Menu::findIndexByName(std::string name) const
    {
        return m_menuData.findIndexByName(name);
    }

    const MenuData& Menu::getMenuData() const
    {
        return m_menuData;
    }

    void Menu::moveUp()
    {
        if (m_selectedIndex > 0)
        {
            --m_selectedIndex;
        }
        m_menuData.setSelectedIndex(m_selectedIndex);
    }

    void Menu::moveDown()
    {
        if (m_selectedIndex < m_menuData.size() - 1)
        {
            ++m_selectedIndex;
        }
        m_menuData.setSelectedIndex(m_selectedIndex);
    }

    const MenuEntry& Menu::getSelectedEntry()
    {
        return m_menuData.getEntry(m_selectedIndex);
    }

    void Menu::setSelectedIndex(size_t index)
    {
        if (m_menuData.isEmpty())
        {
            return;
        }
        m_selectedIndex = index;
        m_menuData.setSelectedIndex(index);
    }

    
}