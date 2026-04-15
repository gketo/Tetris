#pragma once

#include "IRenderable.h"

#include <vector>
#include <string_view>

namespace Game {

    class RulesData : public Core::IRenderable
    {
    public:
        RulesData() = default;

        RulesData(std::initializer_list<std::string_view> rules)
        : m_rules {rules}
        {}

        bool isEmpty() const override;

        const std::vector<std::string_view>& getRules() const;
    
    private:
        std::vector<std::string_view> m_rules;
    };

    inline bool RulesData::isEmpty() const
    {
        return m_rules.empty();
    }

    inline const std::vector<std::string_view>& RulesData::getRules() const
    {
        return m_rules  ;
    }
    
}