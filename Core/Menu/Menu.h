#pragma once

// ==================== Includes ====================
#include "Core/Menu/MenuData.h"

// ==================== Includes ====================
#include <cstddef>
#include <optional>
#include <string>

namespace Core {
    struct MenuEntry;
}

namespace Core {

    class Menu
    {
    public:
        void clear();
        void build(MenuData md);
        void moveUp();
        void moveDown();
        
        std::optional<size_t> findIndexByName(const std::string& name) const;
        const MenuData& getMenuData() const;
        const MenuEntry& getSelectedEntry();
        void setSelectedIndex(size_t index);

    private:
        MenuData m_menuData;
        size_t m_selectedIndex{ 0 };
    };
}   