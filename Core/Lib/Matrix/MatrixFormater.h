#pragma once

namespace Lib::Matrix {
    
    template <typename TCell>
    class MatrixFormatter
    {
    public:
        virtual std::string format(const Matrix<TCell>&) const = 0;
    };
}
