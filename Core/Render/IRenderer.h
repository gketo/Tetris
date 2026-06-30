#pragma once

// ==================== Includes ====================
#include "Core/Render/RenderDataVariant.h"
#include "Core/Render/RenderQueue.h"
#include "Core/Render/RenderSystem.h"
#include "Core/Render/RenderVisitorVariant.h"

// ==================== Includes ====================
#include <memory>
#include <optional>

namespace Core {
    class MenuData; // forward declaration
}

namespace Core::Container {
    class Board;    // forward declaration
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

        void setVisitor(std::unique_ptr<RenderVisitorVariant> v);
        
        void submit(std::unique_ptr<RenderDataVariant> dataVar);
        void render();

        virtual void clearScreen() = 0;
        
        virtual void render(const Core::MenuData& menuData) = 0;
        // virtual void render(const App::Grid::Grid2D<App::Grid::Tile<char>>& frame) = 0;
        virtual void render(const Core::Container::Board& board) = 0;
        virtual void render(const Core::Help::HelpData& helpData) = 0;

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void quit() noexcept = 0;
        virtual void terminate() noexcept = 0;

    private:
        std::unique_ptr<RenderQueue> m_renderQueue;
        std::unique_ptr<RenderSystem> m_renderSystem;
		std::unique_ptr<RenderVisitorVariant> m_renderVisitor;

    };

}