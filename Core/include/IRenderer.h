#pragma once

#include "DataVariant.h"
#include "RenderQueue.h"
#include "RenderSystem.h"
#include "VisitorVariant.h"

#include <memory>

namespace Core::Grid2D {
    template<typename TCell>
    class Frame2D;  // forward declaration
}

namespace Core {
    class MenuData; // forward declaration
}

namespace Core {

    class IRenderer
    {
    public:
        IRenderer()
        : m_renderQueue{ std::make_unique<RenderQueue>() }
        , m_renderSystem{ std::make_unique<RenderSystem>() }
        {}

        virtual ~IRenderer() = default;

        RenderQueue& getRenderQueue() { return *m_renderQueue; }

        void setVisitor(std::unique_ptr<VisitorVariant> v);
        
        void submit(std::unique_ptr<DataVariant> dataVar);
        void render();

        virtual void clearScreen() = 0;
        
        virtual void render(const Core::MenuData& menuData) = 0;
        virtual void render(const Core::Grid2D::Frame2D<char>& frame) = 0;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void quit() noexcept = 0;
        virtual void terminate() noexcept = 0;

    private:
        std::unique_ptr<RenderQueue> m_renderQueue;
        std::unique_ptr<RenderSystem> m_renderSystem;
		std::unique_ptr<VisitorVariant> m_renderVisitor;

    };

}