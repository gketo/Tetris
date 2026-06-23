#pragma once

namespace Core::Geometry {
    struct Point;   // forward declaration
}

namespace Core::Render {
    
    struct Surface
    {
        virtual ~Surface() = default;

        virtual void clear() = 0;
        virtual void reset() = 0;
        virtual bool resize(size_t rows, size_t cols) = 0;
        
        virtual bool isValidIndex(const Core::Type::Index2D& idx) const = 0;
        virtual bool isValidPoint(const Core::Geometry::Point& point) const = 0;
    };

}