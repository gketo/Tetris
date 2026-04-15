#pragma once

#include "Lifecycle.h"
#include "DataVariant.h"
#include "RenderQueue.h"
#include "RenderSystem.h"
#include "VisitorVariant.h"

#include <memory>

namespace Core {

    class IRenderer : virtual public Lifecycle
    {
    public:
        IRenderer()
        : m_renderQueue{ std::make_unique<RenderQueue>() }
        , m_renderSystem{ std::make_unique<RenderSystem>() }
        {}

        virtual ~IRenderer() = default;

        void setVisitor(std::unique_ptr<VisitorVariant> v);

        void submit(std::unique_ptr<DataVariant> dataVar);
        void render();

    private:
        std::unique_ptr<RenderQueue> m_renderQueue;
        std::unique_ptr<RenderSystem> m_renderSystem;
		std::unique_ptr<VisitorVariant> m_renderVisitor;

        void render(const DataVariant& dataVar);
        void render(const MenuData& menuData);
        void render(const Game::RulesData& rules);
    };

}