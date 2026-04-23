#pragma once

#include "DataVariant.h"
#include "MenuData.h"

// forward declaration
namespace Core {
    class GameMaster;
}

namespace Core {

    class Menu
    {
    public:
        void clear();
        void build(MenuData md);
        void moveUp();
        void moveDown();
        
        int findIndexByName(std::string name) const;
        const MenuData& getMenuData() const;
        const MenuEntry& getSelectedEntry();
        void setSelectedIndex(size_t index);

    private:
        MenuData m_menuData;
        size_t m_selectedIndex{ 0 };
    };
}