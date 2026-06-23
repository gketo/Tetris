#pragma once

namespace Core::Container {
    class Board; // forward declaration
}

namespace Core::Geometry {
    struct Rect; // forward declaration
}

namespace Core::Render {

    struct Surface; // forward declaration

    struct BoardView
    {
        virtual void renderToSurface(const Core::Container::Board& board, Surface& surface, const Core::Geometry::Rect& Shape) const = 0;
    };
}