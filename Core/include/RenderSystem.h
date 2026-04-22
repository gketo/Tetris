#pragma once

#include "VisitorVariant.h"
#include "DataVariant.h"

#include <variant>

namespace Core {

    class RenderSystem 
    {
    public:
        RenderSystem() = default; 

        void render(const DataVariant& data, const VisitorVariant& visitor) 
        {
            std::visit([&](auto& v) 
            {
                std::visit(v, data);
            }, visitor);
        }
    };
}


        // void render(const MenuData& menuData, const VisitorVariant& visitor) const 
        // {
        //     std::visit([&](auto& v) 
        //     {
        //         v(std::move(menuData));
        //     }, visitor);
        // }

        // void render(const Game::RulesData& rules, const VisitorVariant& visitor) const 
        // {
        //     std::visit([&](auto& v) 
        //     {
        //         v(std::move(rules));
        //     }, visitor);
        // }