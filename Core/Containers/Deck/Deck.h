#pragma once

// ==================== Includes ====================
#include <random>
#include <vector>

namespace Core::Container{

    template <typename TItem>
    class Deck
    {
    public:
        Deck() = default;

        Deck(std::vector<TItem> originalDeck)
        : m_orginalDeck{ originalDeck }
        , m_deck { originalDeck }
        {}

        void init()
        {
            reset();
        }

        bool empty() const 
        {
            return m_deck.empty();
        }

        void add(TItem item)
        {
            m_orginalDeck.emplace_back(item);
        }

        void shuffle()
        {
            std::shuffle(m_deck.begin(), m_deck.end(), m_randomGen);
        }

        TItem draw()
        {
            TItem item = m_deck.back();
            m_deck.pop_back();
            return item;
        }

        void reset()
        {
            m_deck = m_orginalDeck;
        }

    private:
        std::vector<TItem> m_orginalDeck;
        std::vector<TItem> m_deck;
        std::mt19937 m_randomGen{ std::random_device{}() };
    };
}
