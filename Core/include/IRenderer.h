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

        virtual void update() = 0;

        void submit(std::unique_ptr<DataVariant> dataVar);
        void render();

        virtual void clearScreen() = 0;
        
        // rendering
        virtual void render(const Core::MenuData& menuData) = 0;
        virtual void render(const Game::RulesData& rules) = 0;
        virtual void render(const Core::Grid2D::Frame2D<char>& frame) = 0;

    private:
        std::unique_ptr<RenderQueue> m_renderQueue;
        std::unique_ptr<RenderSystem> m_renderSystem;
		std::unique_ptr<VisitorVariant> m_renderVisitor;

        // void render(const DataVariant& dataVar);
    };

}