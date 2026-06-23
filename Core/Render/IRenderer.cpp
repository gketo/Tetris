#include "Core/Render/IRenderer.h"

#include "Core/Render/RenderDataVariant.h"
#include "Core/Render/RenderQueue.h"
#include "Core/Render/RenderSystem.h"
#include "Core/Render/RenderVisitorVariant.h"

#include <memory>
#include <utility>

namespace Core {

    void IRenderer::submit(std::unique_ptr<RenderDataVariant> dataVar)
    {
        m_renderQueue->submit(std::move(dataVar));
    }

    void IRenderer::setVisitor(std::unique_ptr<RenderVisitorVariant> v)
    {
        m_renderVisitor = std::move(v);
    }

    void IRenderer::render()
    {
        while (!m_renderQueue->empty())
        {
            auto data = m_renderQueue->popData();
            if (data)
            {
                m_renderSystem->render(*data, *m_renderVisitor);
            }
        }
    }
}