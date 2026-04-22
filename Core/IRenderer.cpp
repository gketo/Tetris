#include "IRenderer.h"

#include "DataVariant.h"
#include "Lifecycle.h"
#include "RenderSystem.h"
#include "VisitorVariant.h"

#include "Frame2D.h"

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
    // todo why do i have two versions
//     void IRenderer::render(const DataVariant& dataVar)
//     {
//         if (!m_renderVisitor)
//         {
//             throw std::runtime_error("IRenderer: Render() renderVisitor not set. Use setRenderVisitor()");
//         }

//         m_renderSystem->render(dataVar, *m_renderVisitor);
//     }



}

    // void IRenderer::render(const MenuData& menuData)
    // {
    //     if (!m_renderVisitor)
    //     {
    //         throw std::runtime_error("IRenderer: Render() renderVisitor not set. Use setRenderVisitor()");
    //     }

    //     m_renderSystem->render(menuData, *m_renderVisitor);
    // }

    // void IRenderer::render(const Game::RulesData& rules)
    // {
    //     if (!m_renderVisitor)
    //     {
    //         throw std::runtime_error("IRenderer: Render() renderVisitor not set. Use setRenderVisitor()");
    //     }

    //     m_renderSystem->render(rules, *m_renderVisitor);
    // }