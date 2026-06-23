#pragma once

namespace Core {
    class MenuData; // forward declaration
}

namespace Core::Geometry {
    struct Rect; // forward declaration
}

namespace Core::Render {

    struct Surface; // forward declaration

    class MenuView
    {
    public:
        virtual void renderToSurface(const Core::MenuData& menuData, Surface& surface, const Core::Geometry::Rect& shape) const = 0;
    private:
    };
}