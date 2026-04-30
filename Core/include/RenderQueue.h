#pragma once

#include "DataVariant.h"

#include <memory>
#include <queue>
#include <utility>

namespace Core {

    class RenderQueue 
    {
    public:
        RenderQueue() = default;

        void submit(std::unique_ptr<DataVariant> dataVar) 
        {
            m_dataQueue.push(std::move(dataVar));
        }

        std::unique_ptr<DataVariant> popData() 
        {
            if (!m_dataQueue.empty())
            {
                auto data = std::move(m_dataQueue.front());
                m_dataQueue.pop();
                return std::move(data);
            }
            
            return nullptr;
        }

        void clearPendingData()
        {
            m_dataQueue = std::queue<std::unique_ptr<DataVariant>>();
        }

    private:
        std::queue<std::unique_ptr<DataVariant>> m_dataQueue;
    };

}