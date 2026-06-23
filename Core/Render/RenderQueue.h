#pragma once

#include "Core/Render/RenderDataVariant.h"

#include <memory>
#include <queue>
#include <utility>

namespace Core {

    class RenderQueue 
    {
    public:
        RenderQueue() = default;

        bool empty() const
        {
            return m_dataQueue.empty();
        }

        void submit(std::unique_ptr<RenderDataVariant> dataVar) 
        {
            m_dataQueue.push(std::move(dataVar));
        }

        std::unique_ptr<RenderDataVariant> popData() 
        {
            if (m_dataQueue.empty())
            {
                return nullptr;
            }
            auto data = std::move(m_dataQueue.front());
            m_dataQueue.pop();
            return data;            
        }

        void clearPendingData()
        {
            while (!m_dataQueue.empty())
            {
                m_dataQueue.pop();
            }
        }

    private:
        std::queue<std::unique_ptr<RenderDataVariant>> m_dataQueue;
    };

}