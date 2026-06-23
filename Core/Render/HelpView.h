#pragma once

namespace Core::Help {
    class Help; // forward declaration
}

namespace Core::Geometry {
    struct Rect; // forward declaration
}

namespace Core::Render {

    struct Surface; // forward declaration

    class HelpView
    {
    public:
        virtual void renderToSurface(const Core::Help::HelpData& helpData, Surface& surface, const Core::Geometry::Rect& shape) const = 0;
    private:
    };
}