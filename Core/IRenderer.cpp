#include "IRenderer.h"

#include "DataVariant.h"
#include "RenderQueue.h"
#include "RenderSystem.h"
#include "VisitorVariant.h"

#include <memory>
#include <utility>

namespace Core {

    void IRenderer::submit(std::unique_ptr<DataVariant> dataVar)
    {
        m_renderQueue->submit(std::move(dataVar));
    }

    void IRenderer::setVisitor(std::unique_ptr<VisitorVariant> v)
    {
        m_renderVisitor = std::move(v);
    }

    void IRenderer::render()
    {
        auto data = m_renderQueue->popData();
        if (data)
        {
            m_renderSystem->render(*data, *m_renderVisitor);
        }
    }
}